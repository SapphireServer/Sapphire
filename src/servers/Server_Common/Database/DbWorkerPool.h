#ifndef SAPPHIRE_DBWORKERPOOL_H
#define SAPPHIRE_DBWORKERPOOL_H

#include <array>
#include <string>
#include <vector>
#include <ResultSet.h>
#include <Server_Common/Util/LockedWaitQueue.h>
#include "DbConnection.h"
namespace Core
{
namespace Db
{

template< typename T >
class LockedWaitQueue;
class Operation;
class PreparedStatement;
struct ConnectionInfo;

template< class T >
class DbWorkerPool
{
private:
   enum InternalIndex
   {
      IDX_ASYNC,
      IDX_SYNCH,
      IDX_SIZE
   };

public:
   DbWorkerPool();

   ~DbWorkerPool();

   void setConnectionInfo( const ConnectionInfo& info, uint8_t asyncThreads, uint8_t synchThreads);

   uint32_t open();

   void close();

   bool prepareStatements();

   inline ConnectionInfo getConnectionInfo() const
   {
      return m_connectionInfo;
   }

   // Async execution
   void execute( const std::string& sql );
   void execute( PreparedStatement* stmt );

   // Sync execution
   void directExecute( const std::string& sql );
   void directExecute( PreparedStatement* stmt );
   Mysql::ResultSet* query( const std::string& sql, T* connection = nullptr );
   Mysql::PreparedResultSet* query( PreparedStatement* stmt );

   typedef typename T::Statements PreparedStatementIndex;

   PreparedStatement* getPreparedStatement( PreparedStatementIndex index );

   void escapeString( std::string& str );

   void keepAlive();

private:
   uint32_t openConnections( InternalIndex type, uint8_t numConnections );

   unsigned long escapeString( char *to, const char *from, unsigned long length );

   void enqueue( Operation* op );

   T* getFreeConnection();

   const std::string& getDatabaseName() const;

   std::unique_ptr< Core::LockedWaitQueue< Operation* > > m_queue;
   std::array< std::vector< std::unique_ptr< T > >, IDX_SIZE > m_connections;
   ConnectionInfo m_connectionInfo;
   uint8_t m_asyncThreads;
   uint8_t m_synchThreads;
};

}
}

#endif //SAPPHIRE_DBWORKERPOOL_H
