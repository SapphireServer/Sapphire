#include "Connection.h"
#include "MySqlBase.h"
#include "Statement.h"
#include "PreparedStatement.h"
#include <mysql.h>

#include <stdexcept>
#include <vector>

Mysql::Connection::Connection( std::shared_ptr< MySqlBase > pBase,
                               const std::string& hostName, 
                               const std::string& userName,
                               const std::string& password,
                               uint16_t port ) :
    m_pBase( pBase ),
    m_bConnected( false )
{
   m_pRawCon = mysql_init( nullptr );
   if( mysql_real_connect( m_pRawCon, hostName.c_str(), userName.c_str(), password.c_str(),
                          nullptr, port, nullptr, 0) == nullptr )
      throw std::runtime_error( mysql_error( m_pRawCon ) );
   m_bConnected = true;

}

Mysql::Connection::Connection( std::shared_ptr< MySqlBase > pBase,
                               const std::string& hostName,
                               const std::string& userName,
                               const std::string& password,
                               const optionMap& options,
                               uint16_t port ) :
    m_pBase( pBase )
{
   m_pRawCon = mysql_init( nullptr );
   // Different mysql versions support different options, for now whatever was unsupporter here was commented out
   // but left there.
   for( auto entry : options )
   {
      switch( entry.first )
      {
      // integer based options
      case MYSQL_OPT_CONNECT_TIMEOUT:
      case MYSQL_OPT_PROTOCOL:
      case MYSQL_OPT_READ_TIMEOUT:
      //    case MYSQL_OPT_SSL_MODE:
      //    case MYSQL_OPT_RETRY_COUNT:
      case MYSQL_OPT_WRITE_TIMEOUT:
      //    case MYSQL_OPT_MAX_ALLOWED_PACKET:
      //    case MYSQL_OPT_NET_BUFFER_LENGTH:
      {
         uint32_t optVal = std::stoi( entry.second, nullptr, 10 );
         setOption( entry.first, optVal );
      }
      break;

      // bool based options
      //    case MYSQL_ENABLE_CLEARTEXT_PLUGIN:
      //    case MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS:
      case MYSQL_OPT_COMPRESS:
      case MYSQL_OPT_GUESS_CONNECTION:
      case MYSQL_OPT_LOCAL_INFILE:
      case MYSQL_OPT_RECONNECT:
      //    case MYSQL_OPT_SSL_ENFORCE:
      //    case MYSQL_OPT_SSL_VERIFY_SERVER_CERT:
      case MYSQL_OPT_USE_EMBEDDED_CONNECTION:
      case MYSQL_OPT_USE_REMOTE_CONNECTION:
      case MYSQL_REPORT_DATA_TRUNCATION:
      case MYSQL_SECURE_AUTH:
      {
         my_bool optVal = entry.second == "0" ? 0 : 1;
         setOption( entry.first, &optVal );
      }
      break;

      // string based options
      //    case MYSQL_DEFAULT_AUTH:
      //    case MYSQL_OPT_BIND:
      //    case MYSQL_OPT_SSL_CA:
      //    case MYSQL_OPT_SSL_CAPATH:
      //    case MYSQL_OPT_SSL_CERT:
      //    case MYSQL_OPT_SSL_CIPHER:
      //    case MYSQL_OPT_SSL_CRL:
      //    case MYSQL_OPT_SSL_CRLPATH:
      //    case MYSQL_OPT_SSL_KEY:
      //    case MYSQL_OPT_TLS_VERSION:
      //    case MYSQL_PLUGIN_DIR:
      case MYSQL_READ_DEFAULT_FILE:
      case MYSQL_READ_DEFAULT_GROUP:
      //    case MYSQL_SERVER_PUBLIC_KEY:
      case MYSQL_SET_CHARSET_DIR:
      case MYSQL_SET_CHARSET_NAME:
      case MYSQL_SET_CLIENT_IP:
      case MYSQL_SHARED_MEMORY_BASE_NAME:
      {
         setOption( entry.first, entry.second.c_str() );
      }
      break;

      default:
         throw std::runtime_error( "Unknown option: " + std::to_string( entry.first ) );
    }

   }


   if( mysql_real_connect( m_pRawCon, hostName.c_str(), userName.c_str(), password.c_str(),
                           nullptr, port, nullptr, 0) == nullptr )
      throw std::runtime_error( mysql_error( m_pRawCon ) );

}


Mysql::Connection::~Connection()
{
}

void Mysql::Connection::setOption( enum mysqlOption option, const void *arg )
{

   if( mysql_options( m_pRawCon, static_cast< mysql_option>( option ), arg ) != 0  )
      throw std::runtime_error( "Connection::setOption failed!" );

}

void Mysql::Connection::setOption( enum mysqlOption option, uint32_t arg )
{
 
   if( mysql_options( m_pRawCon,  static_cast< mysql_option>( option ), &arg ) != 0  )
      throw std::runtime_error( "Connection::setOption failed!" );

}

void Mysql::Connection::setOption( enum mysqlOption option, const std::string& arg )
{

   if( mysql_options( m_pRawCon,  static_cast< mysql_option>( option ), arg.c_str() ) != 0 )
      throw std::runtime_error( "Connection::setOption failed!" );

}

void Mysql::Connection::close()
{
   mysql_close( m_pRawCon );
   m_bConnected = false;
}

bool Mysql::Connection::isClosed() const
{
   return !m_bConnected;
}

std::shared_ptr< Mysql::MySqlBase > Mysql::Connection::getMySqlBase() const
{
   return m_pBase;
}

void Mysql::Connection::setAutoCommit( bool autoCommit )
{
   auto b = static_cast< my_bool >( autoCommit == true ? 1 : 0 );
   if( mysql_autocommit( m_pRawCon, b ) != 0 )
      throw std::runtime_error( "Connection::setAutoCommit failed!" );
}

bool Mysql::Connection::getAutoCommit()
{
   // TODO: should be replaced with wrapped sql query function once available
   std::string query("SELECT @@autocommit");
   auto res = mysql_real_query( m_pRawCon, query.c_str(), query.length() );

   if( res != 0 )
      throw std::runtime_error( "Query failed!" );

   auto pRes = mysql_store_result( m_pRawCon );
   auto row = mysql_fetch_row( pRes );

   uint32_t ac = atoi( row[0] );

   return ac != 0;
}

void Mysql::Connection::beginTransaction()
{
   auto stmt = createStatement();
   stmt->execute( "START TRANSACTION;" );
}

void Mysql::Connection::commitTransaction()
{
   auto stmt = createStatement();
   stmt->execute( "COMMIT" );
}

void Mysql::Connection::rollbackTransaction()
{
   auto stmt = createStatement();
   stmt->execute( "ROLLBACK" );
}

std::string Mysql::Connection::escapeString( const std::string &inData )
{
   std::unique_ptr< char[] > buffer( new char[inData.length() * 2 + 1] );
   if( !buffer.get() )
      return "";
   unsigned long return_len = mysql_real_escape_string( m_pRawCon, buffer.get(),
                                                        inData.c_str(), static_cast< unsigned long > ( inData.length() ) );
   return std::string( buffer.get(), return_len );
}

void Mysql::Connection::setSchema( const std::string &schema )
{
   if( mysql_select_db( m_pRawCon, schema.c_str() ) != 0 )
      throw std::runtime_error( "Current database could not be changed to " + schema );
}

std::shared_ptr< Mysql::Statement > Mysql::Connection::createStatement()
{
   return std::make_shared< Mysql::Statement >( shared_from_this() );
}

MYSQL* Mysql::Connection::getRawCon()
{
   return m_pRawCon;
}

std::string Mysql::Connection::getError()
{
   auto mysqlError = mysql_error( m_pRawCon );
   if( mysqlError )
      return std::string( mysqlError );
   return "";
}

std::shared_ptr< Mysql::PreparedStatement > Mysql::Connection::prepareStatement( const std::string &sql )
{
   MYSQL_STMT* stmt = mysql_stmt_init( getRawCon() );

   if( !stmt )
      throw std::runtime_error( "Could not init prepared statement: " + getError() );

   if( mysql_stmt_prepare( stmt, sql.c_str(), sql.size() ) )
      throw std::runtime_error( "Could not prepare statement: " + getError() );

   return std::make_shared< PreparedStatement >( stmt, shared_from_this() );
}

uint32_t Mysql::Connection::getErrorNo()
{
   return mysql_errno( m_pRawCon );
}

bool Mysql::Connection::ping()
{
   return mysql_ping( m_pRawCon ) != 0;
}

