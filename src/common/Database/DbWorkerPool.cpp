#include "DbWorkerPool.h"
#include "DbConnection.h"
#include "PreparedStatement.h"
#include <MySqlConnector.h>
#include "StatementTask.h"
#include "Operation.h"
#include "ZoneDbConnection.h"
#include <boost/make_shared.hpp>
#include "Framework.h"

#include "Logging/Logger.h"

extern Core::Framework g_fw;

class PingOperation :
  public Core::Db::Operation
{
  bool execute() override
  {
    m_pConn->ping();
    return true;
  }
};

template< class T >
Core::Db::DbWorkerPool< T >::DbWorkerPool()
  :
  m_queue( new Core::LockedWaitQueue< boost::shared_ptr< Operation > >() ),
  m_asyncThreads( 0 ),
  m_synchThreads( 0 )
{
}

template< class T >
Core::Db::DbWorkerPool< T >::~DbWorkerPool()
{
  m_queue->cancel();
}

template< class T >
void Core::Db::DbWorkerPool< T >::setConnectionInfo( const ConnectionInfo& info,
                                                     uint8_t asyncThreads,
                                                     uint8_t synchThreads )
{
  m_connectionInfo = info;
  m_asyncThreads = asyncThreads;
  m_synchThreads = synchThreads;
}

template< class T >
uint32_t Core::Db::DbWorkerPool< T >::open()
{
  auto pLog = g_fw.get< Logger >();
  pLog->info( "[DbPool] Opening DatabasePool " + getDatabaseName() +
              " Asynchronous connections: " + std::to_string( m_asyncThreads ) +
              " Synchronous connections: " + std::to_string( m_synchThreads ) );

  uint32_t error = openConnections( IDX_ASYNC, m_asyncThreads );

  if( error )
    return error;

  error = openConnections( IDX_SYNCH, m_synchThreads );

  if( !error )
  {
    pLog->info( "[DbPool] DatabasePool " + getDatabaseName() + " opened successfully. " +
                std::to_string( ( m_connections[ IDX_SYNCH ].size() + m_connections[ IDX_ASYNC ].size() ) ) +
                " total connections running." );
  }

  return error;
}

template< class T >
void Core::Db::DbWorkerPool< T >::close()
{
  auto pLog = g_fw.get< Logger >();
  pLog->info( "[DbPool] Closing down DatabasePool " + getDatabaseName() );
  m_connections[ IDX_ASYNC ].clear();
  m_connections[ IDX_SYNCH ].clear();
  pLog->info( "[DbPool] All connections on DatabasePool " + getDatabaseName() + "closed." );
}

template< class T >
bool Core::Db::DbWorkerPool< T >::prepareStatements()
{
  for( auto& connections : m_connections )
    for( auto& connection : connections )
    {
      connection->lockIfReady();
      if( !connection->prepareStatements() )
      {
        connection->unlock();
        close();
        return false;
      }
      else
        connection->unlock();
    }

  return true;
}

template< class T >
boost::shared_ptr< Mysql::ResultSet >
Core::Db::DbWorkerPool< T >::query( const std::string& sql, boost::shared_ptr< T > connection )
{
  if( !connection )
    connection = getFreeConnection();

  boost::shared_ptr< Mysql::ResultSet > result = connection->query( sql );
  connection->unlock();

  return result;
}

template< class T >
boost::shared_ptr< Mysql::PreparedResultSet >
Core::Db::DbWorkerPool< T >::query( boost::shared_ptr< PreparedStatement > stmt )
{
  auto connection = getFreeConnection();
  auto ret = boost::static_pointer_cast< Mysql::PreparedResultSet >( connection->query( stmt ) );
  connection->unlock();

  return ret;
}

template< class T >
boost::shared_ptr< Core::Db::PreparedStatement >
Core::Db::DbWorkerPool< T >::getPreparedStatement( PreparedStatementIndex index )
{
  return boost::make_shared< PreparedStatement >( index );
}

template< class T >
void Core::Db::DbWorkerPool< T >::escapeString( std::string& str )
{
  if( str.empty() )
    return;

  char* buf = new char[str.size() * 2 + 1];
  escapeString( buf, str.c_str(), str.size() );
  str = buf;
  delete[] buf;
}

template< class T >
void Core::Db::DbWorkerPool< T >::keepAlive()
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
    enqueue( boost::make_shared< PingOperation >() );
}

template< class T >
uint32_t Core::Db::DbWorkerPool< T >::openConnections( InternalIndex type, uint8_t numConnections )
{
  for( uint8_t i = 0; i < numConnections; ++i )
  {
    // Create the connection
    auto connection = [ & ]
    {
      switch( type )
      {
        case IDX_ASYNC:
          return boost::make_shared< T >( m_queue.get(), m_connectionInfo );
        case IDX_SYNCH:
          return boost::make_shared< T >( m_connectionInfo );
        default:
          return boost::shared_ptr< T >( nullptr );
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
unsigned long Core::Db::DbWorkerPool< T >::escapeString( char* to, const char* from, unsigned long length )
{
  if( !to || !from || !length )
    return 0;

  return mysql_real_escape_string(
    m_connections[ IDX_SYNCH ].front()->getConnection()->getRawCon(), to, from, length );
}

template< class T >
void Core::Db::DbWorkerPool< T >::enqueue( boost::shared_ptr< Operation > op )
{
  m_queue->push( op );
}

template< class T >
boost::shared_ptr< T > Core::Db::DbWorkerPool< T >::getFreeConnection()
{
  uint8_t i = 0;
  const auto numCons = m_connections[ IDX_SYNCH ].size();
  boost::shared_ptr< T > connection = nullptr;

  while( true )
  {
    connection = m_connections[ IDX_SYNCH ][ i++ % numCons ];

    if( connection->lockIfReady() )
      break;
  }

  return connection;
}

template< class T >
const std::string& Core::Db::DbWorkerPool< T >::getDatabaseName() const
{
  return m_connectionInfo.database;
}

template< class T >
void Core::Db::DbWorkerPool< T >::execute( const std::string& sql )
{
  auto task = boost::make_shared< StatementTask >( sql );
  enqueue( task );
}

template< class T >
void Core::Db::DbWorkerPool< T >::execute( boost::shared_ptr< PreparedStatement > stmt )
{
  auto task = boost::make_shared< PreparedStatementTask >( stmt );
  enqueue( task );
}

template< class T >
void Core::Db::DbWorkerPool< T >::directExecute( const std::string& sql )
{
  auto connection = getFreeConnection();
  connection->execute( sql );
  connection->unlock();
}

template< class T >
void Core::Db::DbWorkerPool< T >::directExecute( boost::shared_ptr< PreparedStatement > stmt )
{
  auto connection = getFreeConnection();
  connection->execute( stmt );
  connection->unlock();
}

/*
template <class T>
void DatabaseWorkerPool<T>::ExecuteOrAppend(SQLTransaction& trans, const char* sql)
{
   if (!trans)
      Execute(sql);
   else
      trans->Append(sql);
}

template <class T>
void DatabaseWorkerPool<T>::ExecuteOrAppend(SQLTransaction& trans, PreparedStatement* stmt)
{
   if (!trans)
      Execute(stmt);
   else
      trans->Append(stmt);
}
*/

template
class Core::Db::DbWorkerPool< Core::Db::ZoneDbConnection >;
