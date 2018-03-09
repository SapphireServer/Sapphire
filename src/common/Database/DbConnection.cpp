#include "DbConnection.h"
#include "DbWorker.h"
#include <MySqlConnector.h>
#include "Logging/Logger.h"

#include "PreparedStatement.h"
#include <boost/make_shared.hpp>
#include "Framework.h"

extern Core::Framework g_fw;

Core::Db::DbConnection::DbConnection( ConnectionInfo &connInfo ) :
   m_reconnecting( false ),
   m_prepareError( false ),
   m_queue( nullptr ),
   m_pConnection( nullptr ),
   m_connectionInfo( connInfo ),
   m_connectionFlags( CONNECTION_SYNC )
{

}

Core::Db::DbConnection::DbConnection( Core::LockedWaitQueue< boost::shared_ptr< Operation > >* queue,
                                      Core::Db::ConnectionInfo& connInfo ) :
   m_reconnecting( false ),
   m_prepareError( false ),
   m_queue( queue ),
   m_pConnection( nullptr ),
   m_connectionInfo( connInfo ),
   m_connectionFlags( CONNECTION_ASYNC )
{
   m_worker = boost::make_shared< DbWorker >( m_queue, this );
}

Core::Db::DbConnection::~DbConnection()
{
   close();
}

void Core::Db::DbConnection::close()
{
   m_worker.reset();
   m_stmts.clear();

   if( m_pConnection )
   {
      m_pConnection->close();
      m_pConnection.reset();
   }


}

uint32_t Core::Db::DbConnection::open()
{
   boost::shared_ptr< Mysql::MySqlBase > base( new Mysql::MySqlBase() );
   Mysql::optionMap options;
   options[ MYSQL_OPT_RECONNECT ] = "1";
   options[ MYSQL_SET_CHARSET_NAME ] = "utf8";

   try
   {
      m_pConnection = base->connect( m_connectionInfo.host, m_connectionInfo.user, m_connectionInfo.password,
                                     options, m_connectionInfo.port );

      m_pConnection->setSchema( m_connectionInfo.database );
   }
   catch( std::runtime_error& e )
   {
      g_fw.get< Logger >()->error( e.what() );
      return 1;
   }

   return 0;
}

uint32_t Core::Db::DbConnection::getLastError()
{
   return m_pConnection->getErrorNo();
}

bool Core::Db::DbConnection::ping()
{
   return m_pConnection->ping();
}

bool Core::Db::DbConnection::lockIfReady()
{
   return m_mutex.try_lock();
}

void Core::Db::DbConnection::unlock()
{
   m_mutex.unlock();
}

void Core::Db::DbConnection::beginTransaction()
{
   m_pConnection->beginTransaction();
}

void Core::Db::DbConnection::rollbackTransaction()
{
   m_pConnection->rollbackTransaction();
}

void Core::Db::DbConnection::commitTransaction()
{
   m_pConnection->commitTransaction();
}

bool Core::Db::DbConnection::execute( const std::string& sql )
{
   try
   {
      auto stmt = m_pConnection->createStatement();
      bool result = stmt->execute( sql );
      return result;
   }
   catch( std::runtime_error& e )
   {
      g_fw.get< Logger >()->error( e.what() );
      return false;
   }
}

boost::shared_ptr< Mysql::ResultSet > Core::Db::DbConnection::query( const std::string& sql )
{
   try
   {
      auto stmt = m_pConnection->createStatement();
      auto result = stmt->executeQuery( sql );
      return result;
   }
   catch( std::runtime_error& e )
   {
      g_fw.get< Logger >()->error( e.what() );
      return nullptr;
   }
}


boost::shared_ptr< Mysql::ResultSet > Core::Db::DbConnection::query( boost::shared_ptr< Core::Db::PreparedStatement > stmt )
{
   boost::shared_ptr< Mysql::ResultSet > res( nullptr );
   if( !stmt )
      return nullptr;

   if( !ping() )
   {
      // naivly reconnect and hope for the best
      open();
      lockIfReady();
      if( !prepareStatements() )
         return nullptr;
   }

   uint32_t index = stmt->getIndex();

   auto pStmt = getPreparedStatement( index );

   if( !pStmt )
      return nullptr;

   stmt->setMysqlPS( pStmt );
   try
   {
      stmt->bindParameters();
      return pStmt->executeQuery();
   }
   catch( std::runtime_error& e )
   {
      g_fw.get< Logger >()->error( e.what() );
      return nullptr;
   }
   
}

bool Core::Db::DbConnection::execute( boost::shared_ptr< Core::Db::PreparedStatement > stmt )
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
      g_fw.get< Logger >()->error( e.what() );
      return false;
   }
}

boost::shared_ptr< Mysql::PreparedStatement > Core::Db::DbConnection::getPreparedStatement( uint32_t index )
{
   assert( index < m_stmts.size() );
   auto ret = m_stmts[index];
   if( !ret )
     nullptr;

   return ret;
}

void Core::Db::DbConnection::prepareStatement( uint32_t index, const std::string &sql, Core::Db::ConnectionFlags flags )
{
   m_queries.insert( PreparedStatementMap::value_type( index, std::make_pair( sql, flags ) ) );

   // Check if specified query should be prepared on this connection
   // i.e. don't prepare async statements on synchronous connections
   // to save memory that will not be used.
   if( !( m_connectionFlags & flags ) )
   {
      m_stmts[index].reset();
      return;
   }

   boost::shared_ptr< Mysql::PreparedStatement > pStmt( nullptr );

   try
   {
      pStmt = m_pConnection->prepareStatement( sql );
   }
   catch( std::runtime_error& e )
   {
      g_fw.get< Logger >()->error( e.what() );
      m_prepareError = true;
   }

   m_stmts[index] = boost::shared_ptr< Mysql::PreparedStatement >( pStmt );

}

bool Core::Db::DbConnection::prepareStatements()
{
   doPrepareStatements();
   return !m_prepareError;
}






