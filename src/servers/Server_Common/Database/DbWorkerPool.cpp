#include "DbWorkerPool.h"
#include "DbConnection.h"
#include "PreparedStatement.h"
#include <libraries/sapphire/mysqlConnector/MySqlConnector.h>
#include "StatementTask.h"
#include "Operation.h"
#include "CharaDbConnection.h"

#include <Server_Common/Logging/Logger.h>
extern Core::Logger g_log;

class PingOperation : public Core::Db::Operation
{
   bool execute() override
   {
      m_pConn->ping();
      return true;
   }
};

template< class T >
Core::Db::DbWorkerPool<T>::DbWorkerPool()
        : m_queue( new Core::LockedWaitQueue< Operation* >() ),
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
void Core::Db::DbWorkerPool<T>::setConnectionInfo( const ConnectionInfo& info,
                                                   uint8_t asyncThreads,
                                                   uint8_t synchThreads)
{
   m_connectionInfo = info;
   m_asyncThreads = asyncThreads;
   m_synchThreads = synchThreads;
}

template< class T >
uint32_t Core::Db::DbWorkerPool< T >::open()
{
   g_log.info( "[DbPool] Opening DatabasePool " + getDatabaseName() +
               " Asynchronous connections: " + std::to_string( m_asyncThreads ) +
               " Synchronous connections: " + std::to_string( m_synchThreads ) );

   uint32_t error = openConnections( IDX_ASYNC, m_asyncThreads );

   if( error )
      return error;

   error = openConnections( IDX_SYNCH, m_synchThreads );

   if( !error )
   {
      g_log.info( "[DbPool] DatabasePool " + getDatabaseName() + " opened successfully. " +
                  std::to_string( ( m_connections[IDX_SYNCH].size() + m_connections[IDX_ASYNC].size() ) ) +
                  " total connections running." );
   }

   return error;
}

template< class T >
void Core::Db::DbWorkerPool< T >::close()
{
   g_log.info("[DbPool] Closing down DatabasePool " + getDatabaseName() );
   m_connections[IDX_ASYNC].clear();
   m_connections[IDX_SYNCH].clear();
   g_log.info("[DbPool] All connections on DatabasePool " + getDatabaseName() + "closed." );
}

template< class T >
bool Core::Db::DbWorkerPool<T>::prepareStatements()
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
Mysql::ResultSet* Core::Db::DbWorkerPool<T>::query( const std::string& sql, T* connection )
{
   if( !connection )
      connection = getFreeConnection();

   Mysql::ResultSet* result = connection->query( sql );
   connection->unlock();

   return result;
}

template< class T >
Mysql::PreparedResultSet* Core::Db::DbWorkerPool<T>::query( PreparedStatement* stmt )
{
   auto connection = getFreeConnection();
   auto ret = dynamic_cast< Mysql::PreparedResultSet* >( connection->query( stmt ) );
   connection->unlock();

   return ret;
}

template< class T >
Core::Db::PreparedStatement* Core::Db::DbWorkerPool< T >::getPreparedStatement( PreparedStatementIndex index )
{
   return new PreparedStatement( index );
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
   for( auto& connection : m_connections[IDX_SYNCH] )
   {
      if( connection->lockIfReady() )
      {
         connection->ping();
         connection->unlock();
      }
   }

   const auto count = m_connections[IDX_ASYNC].size();
   for( uint8_t i = 0; i < count; ++i )
      enqueue( new PingOperation );
}

template< class T >
uint32_t Core::Db::DbWorkerPool< T >::openConnections( InternalIndex type, uint8_t numConnections )
{
   for( uint8_t i = 0; i < numConnections; ++i )
   {
      // Create the connection
      auto connection = [&] {
         switch (type)
         {
            case IDX_ASYNC:
               return std::unique_ptr<T>( new T( m_queue.get(), m_connectionInfo ) );
            case IDX_SYNCH:
               return std::unique_ptr<T>( new T( m_connectionInfo ) );
            default:
               return std::unique_ptr<T>();
         }
      }();

      if( uint32_t error = connection->open() )
      {
         // Failed to open a connection or invalid version, abort and cleanup
         m_connections[type].clear();
         return error;
      }
      else
      {
         m_connections[type].push_back( std::move( connection ) );
      }
   }

   return 0;
}

template< class T >
unsigned long Core::Db::DbWorkerPool< T >::escapeString( char *to, const char *from, unsigned long length )
{
   if (!to || !from || !length)
      return 0;

   return mysql_real_escape_string(
           m_connections[IDX_SYNCH].front()->getConnection()->getRawCon(), to, from, length);
}

template< class T >
void Core::Db::DbWorkerPool< T >::enqueue( Operation* op )
{
   m_queue->push( op );
}

template< class T >
T* Core::Db::DbWorkerPool< T >::getFreeConnection()
{
   uint8_t i = 0;
   const auto numCons = m_connections[IDX_SYNCH].size();
   T* connection = nullptr;

   while( true )
   {
      connection = m_connections[IDX_SYNCH][i++ % numCons].get();

      if (connection->lockIfReady())
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
   StatementTask* task = new StatementTask( sql );
   enqueue( task );
}

template< class T >
void Core::Db::DbWorkerPool< T >::execute( PreparedStatement* stmt )
{
   PreparedStatementTask* task = new PreparedStatementTask(stmt);
   enqueue( task );
}

template< class T >
void Core::Db::DbWorkerPool< T >::directExecute( const std::string& sql )
{
   T* connection = getFreeConnection();
   connection->execute( sql );
   connection->unlock();
}

template< class T >
void Core::Db::DbWorkerPool< T >::directExecute( PreparedStatement* stmt )
{
   T* connection = getFreeConnection();
   connection->execute( stmt );
   connection->unlock();

   //! Delete proxy-class. Not needed anymore
   delete stmt;
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

template class Core::Db::DbWorkerPool< Core::Db::CharaDbConnection >;
//template class TC_DATABASE_API DatabaseWorkerPool<LoginDatabaseConnection>;
//template class TC_DATABASE_API DatabaseWorkerPool<WorldDatabaseConnection>;
//template class TC_DATABASE_API DatabaseWorkerPool<CharacterDatabaseConnection>;
