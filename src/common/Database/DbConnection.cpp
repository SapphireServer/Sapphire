#include "DbConnection.h"
#include "DbWorker.h"
#include "Logging/Logger.h"
#include <cassert>

#include "PreparedStatement.h"

namespace
{
  struct ConnectionLease
  {
    explicit ConnectionLease( std::shared_ptr< Sapphire::Db::DbConnection > connection ) :
      m_connection( std::move( connection ) )
    {
    }

    ~ConnectionLease()
    {
      if( m_connection )
        m_connection->unlock();
    }

    std::shared_ptr< Sapphire::Db::DbConnection > m_connection;
  };

  std::shared_ptr< void > makeConnectionLease( const std::shared_ptr< Sapphire::Db::DbConnection >& connection )
  {
    if( !connection )
      return nullptr;

    return std::static_pointer_cast< void >( std::make_shared< ConnectionLease >( connection ) );
  }
}

Sapphire::Db::DbConnection::DbConnection( ConnectionInfo& connInfo ) :
  m_reconnecting( false ),
  m_prepareError( false ),
  m_queue( nullptr ),
  m_pConnection( nullptr ),
  m_connectionInfo( connInfo ),
  m_connectionFlags( CONNECTION_SYNC )
{

}

Sapphire::Db::DbConnection::DbConnection( Common::Util::LockedWaitQueue< std::shared_ptr< Operation > >* queue,
                                          Sapphire::Db::ConnectionInfo& connInfo ) :
  m_reconnecting( false ),
  m_prepareError( false ),
  m_queue( queue ),
  m_pConnection( nullptr ),
  m_connectionInfo( connInfo ),
  m_connectionFlags( CONNECTION_ASYNC )
{
  m_worker = std::make_shared< DbWorker >( m_queue, this );
}

Sapphire::Db::DbConnection::~DbConnection()
{
  close();
}

void Sapphire::Db::DbConnection::close()
{
  m_worker.reset();
  m_stmts.clear();

  if( m_pConnection )
  {
    m_pConnection->close();
    m_pConnection.reset();
  }


}

uint32_t Sapphire::Db::DbConnection::open()
{
  std::shared_ptr< Mysql::MySqlBase > base( new Mysql::MySqlBase() );
  Mysql::OptionMap options;
  options[ Mysql::Option::OptReconnect ] = "1";
  options[ Mysql::Option::SetCharsetName ] = "utf8";

  try
  {
    m_pConnection = base->connect( m_connectionInfo.host, m_connectionInfo.user, m_connectionInfo.password,
                                   options, m_connectionInfo.port );

    m_pConnection->setSchema( m_connectionInfo.database );
  }
  catch( std::runtime_error& e )
  {
    Logger::error( e.what() );
    return 1;
  }

  return 0;
}

uint32_t Sapphire::Db::DbConnection::getLastError()
{
  return m_pConnection->getErrorNo();
}

bool Sapphire::Db::DbConnection::ping()
{
  return m_pConnection->ping();
}

bool Sapphire::Db::DbConnection::lockIfReady()
{
  bool expected = false;
  return m_inUse.compare_exchange_strong( expected, true, std::memory_order_acquire );
}

void Sapphire::Db::DbConnection::unlock()
{
  m_inUse.store( false, std::memory_order_release );
}

void Sapphire::Db::DbConnection::beginTransaction()
{
  m_pConnection->beginTransaction();
}

void Sapphire::Db::DbConnection::rollbackTransaction()
{
  m_pConnection->rollbackTransaction();
}

void Sapphire::Db::DbConnection::commitTransaction()
{
  m_pConnection->commitTransaction();
}

bool Sapphire::Db::DbConnection::execute( const std::string& sql )
{
  try
  {
    auto stmt = m_pConnection->createStatement();
    bool result = stmt->execute( sql );
    return result;
  }
  catch( std::runtime_error& e )
  {
    Logger::error( e.what() );
    return false;
  }
}

std::shared_ptr< Mysql::ResultSet > Sapphire::Db::DbConnection::query( const std::string& sql, bool streaming )
{
  auto self = shared_from_this();

  try
  {
    auto stmt = m_pConnection->createStatement();
    auto result = stmt->executeQuery( sql, streaming );

    if( !result )
    {
      unlock();
      return nullptr;
    }

    if( streaming )
      result->setLifetimeGuard( makeConnectionLease( self ) );
    else
      unlock();

    return result;
  }
  catch( std::runtime_error& e )
  {
    unlock();
    Logger::error( e.what() );
    return nullptr;
  }
}


std::shared_ptr< Mysql::ResultSet >
Sapphire::Db::DbConnection::query( std::shared_ptr< Sapphire::Db::PreparedStatement > stmt )
{
  auto self = shared_from_this();

  if( !stmt )
  {
    unlock();
    return nullptr;
  }

  if( !ping() )
  {
    // getFreeConnection() already holds this connection mutex
    if( open() != 0 )
    {
      unlock();
      return nullptr;
    }

    if( !prepareStatements() )
    {
      unlock();
      return nullptr;
    }
  }

  const uint32_t index = stmt->getIndex();
  auto pStmt = getPreparedStatement( index );

  if( !pStmt )
  {
    unlock();
    return nullptr;
  }

  stmt->setMysqlPS( pStmt );
  try
  {
    stmt->bindParameters();
    auto result = pStmt->executeQuery();

    if( !result )
    {
      unlock();
      return nullptr;
    }

    // Prepared results keep using the MYSQL_STMT while fetching, so keep the
    // connection leased until the result is destroyed.
    result->setLifetimeGuard( makeConnectionLease( self ) );

    return result;
  }
  catch( std::runtime_error& e )
  {
    unlock();
    Logger::error( e.what() );
    return nullptr;
  }
}

bool Sapphire::Db::DbConnection::execute( std::shared_ptr< Sapphire::Db::PreparedStatement > stmt )
{
  if( !stmt )
    return false;

  uint32_t index = stmt->getIndex();

  auto pStmt = getPreparedStatement( index );

  if( !pStmt )
    return false;

  stmt->setMysqlPS( pStmt );
  try
  {
    stmt->bindParameters();
    return pStmt->execute();
  }
  catch( std::runtime_error& e )
  {
    Logger::error( e.what() );
    return false;
  }
}

std::shared_ptr< Mysql::PreparedStatement > Sapphire::Db::DbConnection::getPreparedStatement( uint32_t index )
{
  assert( index < m_stmts.size() );
  auto ret = m_stmts[ index ];
  if( !ret )
    return nullptr;

  return ret;
}

void Sapphire::Db::DbConnection::prepareStatement( uint32_t index,
                                                   const std::string& sql,
                                                   Sapphire::Db::ConnectionFlags flags )
{
  m_queries.insert( PreparedStatementMap::value_type( index, std::make_pair( sql, flags ) ) );

  // Check if specified query should be prepared on this connection
  // i.e. don't prepare async statements on synchronous connections
  // to save memory that will not be used.
  if( !( m_connectionFlags & flags ) )
  {
    m_stmts[ index ].reset();
    return;
  }

  std::shared_ptr< Mysql::PreparedStatement > pStmt( nullptr );

  try
  {
    pStmt = m_pConnection->prepareStatement( sql );
  }
  catch( std::runtime_error& e )
  {
    Logger::error( e.what() );
    m_prepareError = true;
  }

  m_stmts[ index ] = std::shared_ptr< Mysql::PreparedStatement >( pStmt );

}

bool Sapphire::Db::DbConnection::prepareStatements()
{
  doPrepareStatements();
  return !m_prepareError;
}






