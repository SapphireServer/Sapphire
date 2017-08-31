#include "Database.h"

#include <stdio.h>
#include <stdarg.h> 

#include <thread>
#include <chrono>
#include <sstream>

#include "src/servers/Server_Common/Logging/Logger.h"

extern Core::Logger g_log;

namespace Core {
namespace Db {

QueryResult::QueryResult( MYSQL_RES *res, uint32_t fields, uint32_t rows )
   : m_result( res ),
   m_fieldCount( fields ),
   m_rowCount( rows )
{
   m_currentRow = new Field[fields];
}

QueryResult::~QueryResult()
{
   mysql_free_result( m_result );
   delete[] m_currentRow;
}

bool QueryResult::nextRow()
{

   MYSQL_ROW row = mysql_fetch_row( m_result );
   auto length = mysql_fetch_lengths( m_result );
   if( row == nullptr )
   {
      return false;
   }

   for( uint32_t i = 0; i < m_fieldCount; ++i )
   {
      m_currentRow[i].setValue( row[i] );
      m_currentRow[i].setLength( 0 );
      if( length )
         m_currentRow[i].setLength( length[i] );
   }

   return true;
}

Database::Database()
{
   m_port = 0;
   m_counter = 0;
   m_pConnections = nullptr;
   m_connectionCount = -1;   // Not connected.
}

Database::~Database()
{
   for( int32_t i = 0; i < m_connectionCount; ++i )
   {
      if( m_pConnections[i].conn != nullptr )
      {
         mysql_close( m_pConnections[i].conn );
      }
   }

   delete[] m_pConnections;
}

bool Database::initialize( const DatabaseParams& params )
{
   uint32_t i;
   MYSQL * temp;
   MYSQL * temp2;
   my_bool my_true = true;

   g_log.info( "Database: Connecting to " + params.hostname + ", database " + params.databaseName + "..." );

   m_pConnections = new DatabaseConnection[params.connectionCount];
   for( i = 0; i < params.connectionCount; ++i )
   {
      temp = mysql_init( nullptr );
      if( mysql_options( temp, MYSQL_SET_CHARSET_NAME, "utf8" ) )
      {
         g_log.error( "Database: Could not set utf8 character set." );
      }

      if( mysql_options( temp, MYSQL_OPT_RECONNECT, &my_true ) )
      {
         g_log.error( "Database: MYSQL_OPT_RECONNECT could not be set, "
                      "connection drops may occur but will be counteracted." );
      }

      temp2 = mysql_real_connect( temp,
                                  params.hostname.c_str(),
                                  params.username.c_str(),
                                  params.password.c_str(),
                                  params.databaseName.c_str(),
                                  params.port,
                                  NULL,
                                  0 );
      if( temp2 == NULL )
      {
         g_log.fatal( "Database: Connection failed due to: `%s`" + std::string( mysql_error( temp ) ) );
         return false;
      }

      m_pConnections[i].conn = temp2;
   }


   return true;
}

uint64_t Database::getNextUId()
{
   execute( std::string( "INSERT INTO uniqueiddata( IdName ) VALUES( 'NOT_SET' );" ) );
   auto res = query( "SELECT LAST_INSERT_ID();" );

   if( !res )
   {
      return 0;
   }

   Db::Field *field = res->fetch();

   return field[0].get< uint64_t >();
}

DatabaseConnection * Database::getFreeConnection()
{
   uint32_t i = 0;
   for( ;;)
   {
      DatabaseConnection * con = &m_pConnections[( ( i++ ) % m_connectionCount )];
      if( con->lock.try_lock() )
      {
         return con;
      }

      // sleep every 20 iterations, otherwise this can cause 100% cpu if the db link goes dead
      if( !( i % 20 ) )
      {
         std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
      }
   }

   // shouldn't be reached
   return NULL;
}

boost::shared_ptr<QueryResult> Database::query( const std::string& QueryString )
{

   // Send the query
   boost::shared_ptr<QueryResult> qResult( nullptr );
   DatabaseConnection * con = getFreeConnection();

   if( sendQuery(con, QueryString.c_str(), false) )
   {
      qResult = boost::shared_ptr<QueryResult>( _StoreQueryResult( con ) );
   }

   con->lock.unlock();
   return qResult;
}


bool Database::execute( const std::string& QueryString )
{
   DatabaseConnection * con = getFreeConnection();
   bool Result = sendQuery(con, QueryString, false);
   con->lock.unlock();
   return Result;
}

void Database::freeQueryResult( QueryResult * p )
{
   delete p;
}

std::string Database::escapeString( std::string Escape )
{
   char a2[16384] = { 0 };

   DatabaseConnection * con = getFreeConnection();
   const char * ret;
   if( mysql_real_escape_string( con->conn, a2, Escape.c_str(), ( uint32_t ) Escape.length() ) == 0 )
   {
      ret = Escape.c_str();
   }
   else {
      ret = a2;
   }

   con->lock.unlock();
   return std::string( ret );
}

void Database::escapeLongString( const char * str, uint32_t len, std::stringstream& out )
{
   char a2[65536 * 3] = { 0 };

   DatabaseConnection * con = getFreeConnection();
   mysql_real_escape_string( con->conn, a2, str, ( uint32_t ) len );

   out.write( a2, ( std::streamsize )strlen( a2 ) );
   con->lock.unlock();
}

std::string Database::escapeString( const char * esc, DatabaseConnection * con )
{
   char a2[16384] = { 0 };
   const char * ret;
   if( mysql_real_escape_string( con->conn, a2, ( char* ) esc, ( uint32_t ) strlen( esc ) ) == 0 )
   {
      ret = esc;
   }
   else
   {
      ret = a2;
   }

   return std::string( ret );
}

bool Database::sendQuery( DatabaseConnection *con, const std::string &sql, bool Self )
{
   int32_t result = mysql_query( con->conn, sql.c_str() );
   if( result > 0 )
   {
      if( Self == false && handleError( con, mysql_errno( con->conn ) ) )
      {
         // Re-send the query, the connection was successful.
         // The true on the end will prevent an endless loop here, as it will
         // stop after sending the query twice.
         result = sendQuery(con, sql, true);
      }
      else
      {
         g_log.error( "Database: query failed " + std::string( mysql_error( con->conn ) ) );
         g_log.error( "\t" + std::string( sql ) );
      }
   }

   return ( result == 0 ? true : false );
}

bool Database::handleError( DatabaseConnection *con, uint32_t ErrorNumber )
{
   // Handle errors that should cause a reconnect to the CDatabase.
   switch( ErrorNumber ) {
   case 2006:  // Mysql server has gone away
   case 2008:  // Client ran out of memory
   case 2013:  // Lost connection to sql server during query
   case 2055:  // Lost connection to sql server - system error
   {
      // Let's instruct a reconnect to the db when we encounter these errors.
      return _Reconnect( con );
   }break;
   }

   return false;
}

QueryResult * Database::_StoreQueryResult( DatabaseConnection * con )
{
   QueryResult *res;
   MYSQL_RES * pRes = mysql_store_result( con->conn );
   uint32_t uRows = ( uint32_t ) mysql_affected_rows( con->conn );
   uint32_t uFields = ( uint32_t ) mysql_field_count( con->conn );

   if( uRows == 0 || uFields == 0 || pRes == 0 )
   {
      if( pRes != NULL )
      {
         mysql_free_result( pRes );
      }

      return NULL;
   }

   res = new QueryResult( pRes, uFields, uRows );
   res->nextRow();

   return res;
}

bool Database::_Reconnect( DatabaseConnection * conn )
{
   MYSQL * temp;
   MYSQL * temp2;

   temp = mysql_init( NULL );

   temp2 = mysql_real_connect( temp,
                               m_hostname.c_str(),
                               m_username.c_str(),
                               m_password.c_str(),
                               m_databaseName.c_str(),
                               m_port,
                               NULL,
                               0 );
   if( temp2 == NULL )
   {
      g_log.error( "Database: Could not reconnect to database because of " + std::string( mysql_error( temp ) ) );
      mysql_close( temp );
      return false;
   }

   if( conn->conn != NULL )
   {
      mysql_close( conn->conn );
   }

   conn->conn = temp;
   return true;
}

void Database::cleanupLibs()
{
   mysql_library_end();
}



void Database::shutdown()
{
   for( int32_t i = 0; i < m_connectionCount; ++i )
   {
      if( m_pConnections[i].conn != NULL )
      {
         mysql_close( m_pConnections[i].conn );
         m_pConnections[i].conn = NULL;
      }
   }
}

}
}
