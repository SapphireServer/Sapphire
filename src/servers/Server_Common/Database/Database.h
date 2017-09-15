#ifndef _DATABASE_H
#define _DATABASE_H

#include <mutex>
#include <stdio.h>

#include <mysql.h>

#include <boost/shared_ptr.hpp>
#include <string.h>

namespace Core {
namespace Db {

   class Field
   {
   public:

      // set value
      void setValue( char* value );
      void setLength( uint32_t value );

      std::string getString() const;
      void getBinary( char* dstBuf, uint16_t size ) const;
      float getFloat() const;
      bool getBool() const;

      template< class T >
      __inline T get() const
      {
         if( !m_pValue )
            return 0;

         return static_cast< T >( atol( m_pValue ) );
      }
	  
         uint64_t getUInt64()
         {
            if( m_pValue )
            {
        #ifdef _WIN32
               uint64_t value;
               sscanf( m_pValue, "%I64d", &value );
               return value;
        #else
           uint64_t value;
               sscanf( m_pValue, "%Lu", &value );
               return value;

        #endif
            }
            else
               return 0;
         }
		 
      uint32_t getLength() const;

   private:
      char *m_pValue;
      uint32_t m_size;
   };


   class QueryResult
   {
   public:
      QueryResult( MYSQL_RES *res, uint32_t fields, uint32_t rows );
      ~QueryResult();

      bool nextRow();

      Field* fetch();
      uint32_t getFieldCount() const;
      uint32_t getRowCount() const;

   protected:
      uint32_t m_fieldCount;
      uint32_t m_rowCount;
      Field *m_currentRow;
      MYSQL_RES *m_result;
   };

   struct DatabaseConnection
   {
      std::mutex lock;
      MYSQL *conn;
   };

   struct DatabaseParams
   {
      std::string hostname;
      std::string username;
      std::string password;
      std::string databaseName;
      uint16_t port;
      uint32_t bufferSize;
      uint32_t connectionCount;
   };

   class Database
   {
   public:
      Database();
      virtual ~Database();

      bool initialize( const DatabaseParams& params );

      void shutdown();

      boost::shared_ptr< QueryResult > query( const std::string& QueryString );
      bool waitExecuteNA( const char* QueryString );//Wait For Request Completion
      bool execute( const char* QueryString, ... );
      bool execute( const std::string& QueryString );

      const std::string& getHostName();

      const std::string& getDatabaseName();

      std::string escapeString( std::string Escape );
      void escapeLongString( const char * str, uint32_t len, std::stringstream& out );
      std::string escapeString( const char * esc, DatabaseConnection *con );

      void freeQueryResult( QueryResult * p );

      DatabaseConnection *getFreeConnection();

      void cleanupLibs();

      /* database is killed off manually. */
      void onShutdown() {}

      uint64_t getNextUId();

   protected:

      // actual query function
      bool sendQuery( DatabaseConnection *con, const std::string &sql, bool Self );
      QueryResult * storeQueryResult( DatabaseConnection * con );
      bool handleError( DatabaseConnection *conn, uint32_t ErrorNumber );
      bool reconnect( DatabaseConnection *conn );

      DatabaseConnection *m_pConnections;

      uint32_t m_counter;
      ///////////////////////////////

      int32_t m_connectionCount;

      // For reconnecting a broken connection
      std::string m_hostname;
      std::string m_username;
      std::string m_password;
      std::string m_databaseName;
      uint32_t m_port;

   };

}
}
#endif
