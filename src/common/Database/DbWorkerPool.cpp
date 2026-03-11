#include "DbWorkerPool.h"
#include "DbConnection.h"
#include "PreparedStatement.h"
#include "StatementTask.h"
#include "Operation.h"
#include "ZoneDbConnection.h"

#include "Logging/Logger.h"

#include <stdexcept>
#include <thread>

class PingOperation : public Sapphire::Db::Operation
{
  bool execute() override
  {
    m_pConn->ping();
    return true;
  }
};

template< class T >
Sapphire::Db::DbWorkerPool< T >::DbWorkerPool() :
  m_queue( new Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >() ),
  m_asyncThreads( 0 ),
  m_synchThreads( 0 )
{
}

template< class T >
Sapphire::Db::DbWorkerPool< T >::~DbWorkerPool()
{
  m_queue->cancel();
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::setConnectionInfo( const ConnectionInfo& info,
                                                         uint8_t asyncThreads,
                                                         uint8_t synchThreads )
{
  m_connectionInfo = info;
  m_asyncThreads = asyncThreads;
  m_synchThreads = synchThreads;
}

template< class T >
uint32_t Sapphire::Db::DbWorkerPool< T >::open()
{
  Logger::info( "[DbPool] Opening DatabasePool {0} Asynchronous connections: {1} Synchronous connections: {2}",
                getDatabaseName(), m_asyncThreads, m_synchThreads );

  uint32_t error = openConnections( IDX_ASYNC, m_asyncThreads );

  if( error )
    return error;

  error = openConnections( IDX_SYNCH, m_synchThreads );

  if( !error )
  {
    Logger::info( "[DbPool] DatabasePool '{0}' opened successfully. {1} total connections running.",
                  getDatabaseName(), ( m_connections[ IDX_SYNCH ].size() + m_connections[ IDX_ASYNC ].size() ) );
  }

  return error;
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::close()
{
  Logger::info( "[DbPool] Closing down DatabasePool {0}", getDatabaseName() );
  m_connections[ IDX_ASYNC ].clear();
  m_connections[ IDX_SYNCH ].clear();
  Logger::info( "[DbPool] All connections on DatabasePool {0} closed.", getDatabaseName() );
}

template< class T >
bool Sapphire::Db::DbWorkerPool< T >::prepareStatements()
{
  for( auto& connections : m_connections )
    for( auto& connection : connections )
    {
      while( !connection->lockIfReady() )
        std::this_thread::yield();

      if( !connection->prepareStatements() )
      {
        connection->unlock();
        close();
        return false;
      }

      connection->unlock();
    }

  return true;
}

template< class T >
std::shared_ptr< Mysql::ResultSet >
Sapphire::Db::DbWorkerPool< T >::query( const std::string& sql, std::shared_ptr< T > connection, bool streaming )
{
  if( !connection )
    connection = getFreeConnection();

  return connection->query( sql, streaming );
}

template< class T >
std::shared_ptr< Mysql::PreparedResultSet >
Sapphire::Db::DbWorkerPool< T >::query( std::shared_ptr< PreparedStatement > stmt )
{
  auto connection = getFreeConnection();
  return std::static_pointer_cast< Mysql::PreparedResultSet >( connection->query( stmt ) );
}

template< class T >
std::shared_ptr< Sapphire::Db::PreparedStatement >
Sapphire::Db::DbWorkerPool< T >::getPreparedStatement( PreparedStatementIndex index )
{
  return std::make_shared< PreparedStatement >( index );
}

template< class T >
std::string Sapphire::Db::DbWorkerPool< T >::escapeString( std::string_view str )
{
  auto connection = getFreeConnection();

  try
  {
    auto escaped = connection->getConnection()->escapeString( str );
    connection->unlock();
    return escaped;
  }
  catch( ... )
  {
    connection->unlock();
    throw;
  }
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::keepAlive()
{
  for( auto& connection : m_connections[ IDX_SYNCH ] )
  {
    if( connection->lockIfReady() )
    {
      connection->ping();
      connection->unlock();
    }
  }

  const auto count = m_connections[ IDX_ASYNC ].size();
  for( uint8_t i = 0; i < count; ++i )
    enqueue( std::make_shared< PingOperation >() );
}

template< class T >
uint32_t Sapphire::Db::DbWorkerPool< T >::openConnections( InternalIndex type, uint8_t numConnections )
{
  for( uint8_t i = 0; i < numConnections; ++i )
  {
    // Create the connection
    auto connection = [ & ] {
      switch( type )
      {
        case IDX_ASYNC:
          return std::make_shared< T >( m_queue.get(), m_connectionInfo );
        case IDX_SYNCH:
          return std::make_shared< T >( m_connectionInfo );
        default:
          return std::shared_ptr< T >( nullptr );
      }
    }();

    if( uint32_t error = connection->open() )
    {
      // Failed to open a connection or invalid version, abort and cleanup
      m_connections[ type ].clear();
      return error;
    }
    m_connections[ type ].push_back( connection );
  }

  return 0;
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::enqueue( std::shared_ptr< Operation > op )
{
  m_queue->push( op );
}

template< class T >
std::shared_ptr< T > Sapphire::Db::DbWorkerPool< T >::getFreeConnection()
{
  uint8_t i = 0;
  const auto numCons = m_connections[ IDX_SYNCH ].size();
  std::shared_ptr< T > connection = nullptr;

  if( numCons == 0 )
    throw std::runtime_error( "DbWorkerPool::getFreeConnection requires at least one synchronous connection" );

  while( true )
  {
    connection = m_connections[ IDX_SYNCH ][ i++ % numCons ];

    if( connection->lockIfReady() )
      break;

    std::this_thread::yield();
  }

  return connection;
}

template< class T >
const std::string& Sapphire::Db::DbWorkerPool< T >::getDatabaseName() const
{
  return m_connectionInfo.database;
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::execute( const std::string& sql )
{
  auto task = std::make_shared< StatementTask >( sql );
  enqueue( task );
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::execute( std::shared_ptr< PreparedStatement > stmt )
{
  auto task = std::make_shared< PreparedStatementTask >( stmt );
  enqueue( task );
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::directExecute( const std::string& sql )
{
  auto connection = getFreeConnection();
  connection->execute( sql );
  connection->unlock();
}

template< class T >
void Sapphire::Db::DbWorkerPool< T >::directExecute( std::shared_ptr< PreparedStatement > stmt )
{
  auto connection = getFreeConnection();
  connection->execute( stmt );
  connection->unlock();
}

template class Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection >;
