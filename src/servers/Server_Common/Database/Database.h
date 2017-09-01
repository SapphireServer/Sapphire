#ifndef _DATABASE_H
#define _DATABASE_H

#include <mutex>
#include <stdio.h>

#include <mysql.h>

#include <boost/shared_ptr.hpp>
#include <string.h>

namespace Core {
   namespace Db {

      // CField is used to access db-query resultsets
      class Field
      {
      public:

         // set value
         __inline void setValue( char* value )
         {
            m_pValue = value;
         }

         // set value
         __inline void setLength( uint32_t value )
         {
            m_size = value;
         }

         // return as string
         __inline std::string getString() const
         {
            if( !m_pValue )
               return "";
            return std::string( m_pValue );
         }

         // return as string
         __inline void getBinary( char* dstBuf, uint16_t size ) const
         {
            if( m_pValue )
            {
               memcpy( dstBuf, m_pValue, size );
            }
            else
            {
               dstBuf = NULL;
            }
         }

         //  return as float
         __inline float getFloat() const
         {
            return m_pValue ? static_cast< float >( atof( m_pValue ) ) : 0;
         }

         // return as bool
         __inline bool getBool() const
         {
            return m_pValue ? atoi( m_pValue ) > 0 : false;
         }

         template< class T >
         __inline T get() const
         {
            if( !m_pValue )
               return 0;

            return static_cast< T >( atol( m_pValue ) );
         }

         __inline uint32_t getLength() const
         {
            return m_size;
         }


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

         __inline Field* fetch()
         {
            return m_currentRow;
         }
         __inline uint32_t getFieldCount() const
         {
            return m_fieldCount;
         }
         __inline uint32_t getRowCount() const
         {
            return m_rowCount;
         }

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

         /************************************************************************/
         /* Virtual Functions                                                    */
         /************************************************************************/
         bool initialize( const DatabaseParams& params );

         void shutdown();

         boost::shared_ptr<QueryResult> query( const std::string& QueryString );
         bool waitExecuteNA( const char* QueryString );//Wait For Request Completion
         bool execute( const char* QueryString, ... );
         bool execute( const std::string& QueryString );

         __inline const std::string& getHostName()
         {
            return m_hostname;
         }

         __inline const std::string& getDatabaseName()
         {
            return m_databaseName;
         }

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
