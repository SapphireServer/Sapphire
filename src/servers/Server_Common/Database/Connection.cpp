#include "Connection.h"
#include "MySqlBase.h"

Core::Db::Connection::Connection( MySqlBase * pBase, 
                                  const std::string& hostName, 
                                  const std::string& userName,
                                  const std::string& password ) : 
    m_pBase( pBase ),
    m_bConnected( false )
{
   m_pRawCon = mysql_init( nullptr );
   if( mysql_real_connect( m_pRawCon, hostName.c_str(), userName.c_str(), password.c_str(),
                          nullptr, 3306, nullptr, 0) == nullptr )
   {
      throw std::runtime_error( mysql_error( m_pRawCon ) );
   }
   m_bConnected = true;

}

Core::Db::Connection::Connection( MySqlBase * pBase,
                                  const std::string& hostName,
                                  const std::string& userName,
                                  const std::string& password,
                                  const optionMap& options ) : 
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
                           nullptr, 3306, nullptr, 0) == nullptr )
   {
      throw std::runtime_error( mysql_error( m_pRawCon ) );
   }

}


Core::Db::Connection::~Connection()
{
}

void Core::Db::Connection::setOption( enum mysql_option option, const void *arg )
{

   if( mysql_options( m_pRawCon, option, arg ) != 0  )
      throw std::runtime_error( "Connection::setOption failed!" );

}

void Core::Db::Connection::setOption( enum mysql_option option, uint32_t arg )
{
 
   if( mysql_options( m_pRawCon, option, &arg ) != 0  )
      throw std::runtime_error( "Connection::setOption failed!" );

}

void Core::Db::Connection::setOption( enum mysql_option option, const std::string& arg )
{

   if( mysql_options( m_pRawCon, option, arg.c_str() ) != 0 )
      throw std::runtime_error( "Connection::setOption failed!" );

}

void Core::Db::Connection::close()
{
   mysql_close( m_pRawCon );
   m_bConnected = false;
}

bool Core::Db::Connection::isClosed() const
{
   return !m_bConnected;
}

Core::Db::MySqlBase* Core::Db::Connection::getMySqlBase() const
{
   return m_pBase;
}

void Core::Db::Connection::setAutoCommit( bool autoCommit )
{
   auto b = static_cast< my_bool >( autoCommit == true ? 1 : 0 );
   if( mysql_autocommit( m_pRawCon, b ) != 0 )
      throw std::runtime_error( "Connection::setAutoCommit failed!" );
}

bool Core::Db::Connection::getAutoCommit()
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

