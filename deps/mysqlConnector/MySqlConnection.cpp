#include "MySqlConnection.h"
#include "MySqlBase.h"
#include "MySqlStatement.h"
#include "MySqlPreparedStatement.h"
#include "detail/MySqlNative.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

#include <utility>

namespace
{
  using MysqlBindBool = Mysql::BindBool;

  MYSQL* nativeConnection( Mysql::NativeConnectionHandle handle )
  {
    return static_cast< MYSQL* >( handle );
  }

  enum class OptionValueKind
  {
    Bool,
    UInt32,
    String,
    NoValue,
    KeyValue,
    KeyOnly,
    SslMode,
  };

  std::string toLower( std::string value )
  {
    std::transform( value.begin(), value.end(), value.begin(),
                    []( unsigned char c ) { return static_cast< char >( std::tolower( c ) ); } );
    return value;
  }

  bool parseBool( const std::string& value )
  {
    const std::string normalized = toLower( value );
    if( normalized == "1" || normalized == "true" || normalized == "yes" || normalized == "on" )
      return true;
    if( normalized == "0" || normalized == "false" || normalized == "no" || normalized == "off" )
      return false;

    throw std::runtime_error( "Invalid boolean MySQL option value: " + value );
  }

  uint32_t parseUInt32( const std::string& value )
  {
    return static_cast< uint32_t >( std::stoul( value, nullptr, 10 ) );
  }

  OptionValueKind getOptionValueKind( Mysql::Option option )
  {
    switch( option )
    {
      case Mysql::Option::OptCompress:
      case Mysql::Option::OptNamedPipe:
      case Mysql::Option::OptLocalInfile:
      case Mysql::Option::OptUseRemoteConnection:
      case Mysql::Option::OptUseEmbeddedConnection:
      case Mysql::Option::OptGuessConnection:
      case Mysql::Option::SecureAuth:
      case Mysql::Option::ReportDataTruncation:
      case Mysql::Option::OptReconnect:
      case Mysql::Option::OptSslVerifyServerCert:
      case Mysql::Option::EnableCleartextPlugin:
      case Mysql::Option::OptCanHandleExpiredPasswords:
      case Mysql::Option::OptSslEnforce:
        return OptionValueKind::Bool;

      case Mysql::Option::OptConnectTimeout:
      case Mysql::Option::OptProtocol:
      case Mysql::Option::OptReadTimeout:
      case Mysql::Option::OptWriteTimeout:
      case Mysql::Option::OptMaxAllowedPacket:
      case Mysql::Option::OptNetBufferLength:
        return OptionValueKind::UInt32;

      case Mysql::Option::InitCommand:
      case Mysql::Option::ReadDefaultFile:
      case Mysql::Option::ReadDefaultGroup:
      case Mysql::Option::SetCharsetDir:
      case Mysql::Option::SetCharsetName:
      case Mysql::Option::SharedMemoryBaseName:
      case Mysql::Option::SetClientIp:
      case Mysql::Option::PluginDir:
      case Mysql::Option::DefaultAuth:
      case Mysql::Option::OptBind:
      case Mysql::Option::OptSslKey:
      case Mysql::Option::OptSslCert:
      case Mysql::Option::OptSslCa:
      case Mysql::Option::OptSslCapath:
      case Mysql::Option::OptSslCipher:
      case Mysql::Option::OptSslCrl:
      case Mysql::Option::OptSslCrlpath:
      case Mysql::Option::ServerPublicKey:
      case Mysql::Option::OptTlsVersion:
        return OptionValueKind::String;

      case Mysql::Option::OptUseResult:
      case Mysql::Option::OptConnectAttrReset:
        return OptionValueKind::NoValue;

      case Mysql::Option::OptConnectAttrAdd:
        return OptionValueKind::KeyValue;

      case Mysql::Option::OptConnectAttrDelete:
        return OptionValueKind::KeyOnly;

      case Mysql::Option::OptSslMode:
        return OptionValueKind::SslMode;
    }

    throw std::runtime_error( "Unsupported MySQL option kind lookup: " + std::to_string( static_cast< int >( option ) ) );
  }

#if !defined( MARIADB_PACKAGE_VERSION_ID )
  mysql_ssl_mode parseSslMode( const std::string& value )
  {
    const std::string normalized = toLower( value );
    if( normalized == "1" || normalized == "disabled" )
      return SSL_MODE_DISABLED;
    if( normalized == "2" || normalized == "preferred" )
      return SSL_MODE_PREFERRED;
    if( normalized == "3" || normalized == "required" )
      return SSL_MODE_REQUIRED;
    if( normalized == "4" || normalized == "verify_ca" )
      return SSL_MODE_VERIFY_CA;
    if( normalized == "5" || normalized == "verify_identity" )
      return SSL_MODE_VERIFY_IDENTITY;

    throw std::runtime_error( "Invalid MySQL SSL mode value: " + value );
  }
#endif

  mysql_option toNativeOption( Mysql::Option option )
  {
    switch( option )
    {
      case Mysql::Option::OptConnectTimeout:
        return MYSQL_OPT_CONNECT_TIMEOUT;
      case Mysql::Option::OptCompress:
        return MYSQL_OPT_COMPRESS;
      case Mysql::Option::OptNamedPipe:
        return MYSQL_OPT_NAMED_PIPE;
      case Mysql::Option::InitCommand:
        return MYSQL_INIT_COMMAND;
      case Mysql::Option::ReadDefaultFile:
        return MYSQL_READ_DEFAULT_FILE;
      case Mysql::Option::ReadDefaultGroup:
        return MYSQL_READ_DEFAULT_GROUP;
      case Mysql::Option::SetCharsetDir:
        return MYSQL_SET_CHARSET_DIR;
      case Mysql::Option::SetCharsetName:
        return MYSQL_SET_CHARSET_NAME;
      case Mysql::Option::OptLocalInfile:
        return MYSQL_OPT_LOCAL_INFILE;
      case Mysql::Option::OptProtocol:
        return MYSQL_OPT_PROTOCOL;
      case Mysql::Option::SharedMemoryBaseName:
        return MYSQL_SHARED_MEMORY_BASE_NAME;
      case Mysql::Option::OptReadTimeout:
        return MYSQL_OPT_READ_TIMEOUT;
      case Mysql::Option::OptWriteTimeout:
        return MYSQL_OPT_WRITE_TIMEOUT;
      case Mysql::Option::OptUseResult:
        return MYSQL_OPT_USE_RESULT;
      case Mysql::Option::ReportDataTruncation:
        return MYSQL_REPORT_DATA_TRUNCATION;
      case Mysql::Option::OptReconnect:
        return MYSQL_OPT_RECONNECT;
      case Mysql::Option::PluginDir:
        return MYSQL_PLUGIN_DIR;
      case Mysql::Option::DefaultAuth:
        return MYSQL_DEFAULT_AUTH;
      case Mysql::Option::OptBind:
        return MYSQL_OPT_BIND;
      case Mysql::Option::OptSslKey:
        return MYSQL_OPT_SSL_KEY;
      case Mysql::Option::OptSslCert:
        return MYSQL_OPT_SSL_CERT;
      case Mysql::Option::OptSslCa:
        return MYSQL_OPT_SSL_CA;
      case Mysql::Option::OptSslCapath:
        return MYSQL_OPT_SSL_CAPATH;
      case Mysql::Option::OptSslCipher:
        return MYSQL_OPT_SSL_CIPHER;
      case Mysql::Option::OptSslCrl:
        return MYSQL_OPT_SSL_CRL;
      case Mysql::Option::OptSslCrlpath:
        return MYSQL_OPT_SSL_CRLPATH;
      case Mysql::Option::OptConnectAttrReset:
        return MYSQL_OPT_CONNECT_ATTR_RESET;
      case Mysql::Option::OptConnectAttrAdd:
        return MYSQL_OPT_CONNECT_ATTR_ADD;
      case Mysql::Option::OptConnectAttrDelete:
        return MYSQL_OPT_CONNECT_ATTR_DELETE;
      case Mysql::Option::ServerPublicKey:
        return MYSQL_SERVER_PUBLIC_KEY;
      case Mysql::Option::EnableCleartextPlugin:
        return MYSQL_ENABLE_CLEARTEXT_PLUGIN;
      case Mysql::Option::OptCanHandleExpiredPasswords:
        return MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS;
      case Mysql::Option::OptMaxAllowedPacket:
        return MYSQL_OPT_MAX_ALLOWED_PACKET;
      case Mysql::Option::OptNetBufferLength:
        return MYSQL_OPT_NET_BUFFER_LENGTH;
      case Mysql::Option::OptTlsVersion:
        return MYSQL_OPT_TLS_VERSION;

#if defined( MARIADB_PACKAGE_VERSION_ID ) || ( defined( MYSQL_VERSION_ID ) && MYSQL_VERSION_ID < 80000 )
      case Mysql::Option::OptUseRemoteConnection:
        return MYSQL_OPT_USE_REMOTE_CONNECTION;
      case Mysql::Option::OptUseEmbeddedConnection:
        return MYSQL_OPT_USE_EMBEDDED_CONNECTION;
      case Mysql::Option::OptGuessConnection:
        return MYSQL_OPT_GUESS_CONNECTION;
      case Mysql::Option::SetClientIp:
        return MYSQL_SET_CLIENT_IP;
      case Mysql::Option::SecureAuth:
        return MYSQL_SECURE_AUTH;
      case Mysql::Option::OptSslVerifyServerCert:
        return MYSQL_OPT_SSL_VERIFY_SERVER_CERT;
      case Mysql::Option::OptSslEnforce:
        return MYSQL_OPT_SSL_ENFORCE;
#endif

#if !defined( MARIADB_PACKAGE_VERSION_ID )
      case Mysql::Option::OptSslMode:
        return MYSQL_OPT_SSL_MODE;
#endif
      default:
        break;
    }

    throw std::runtime_error( "Unsupported MySQL client option: " + std::to_string( static_cast< int >( option ) ) );
  }
}// namespace

Mysql::Connection::Connection( std::shared_ptr< MySqlBase > pBase,
                               const std::string& hostName,
                               const std::string& userName,
                               const std::string& password,
                               uint16_t port ) : m_pBase( std::move( pBase ) ),
                                                 m_bConnected( false )
{
  m_pRawCon = static_cast< Mysql::NativeConnectionHandle >( mysql_init( nullptr ) );
  if( mysql_real_connect( nativeConnection( m_pRawCon ), hostName.c_str(), userName.c_str(), password.c_str(),
                          nullptr, port, nullptr, 0 ) == nullptr )
    throw std::runtime_error( mysql_error( nativeConnection( m_pRawCon ) ) );
  m_bConnected = true;
}

Mysql::Connection::Connection( std::shared_ptr< MySqlBase > pBase,
                               const std::string& hostName,
                               const std::string& userName,
                               const std::string& password,
                               const OptionMap& options,
                               uint16_t port ) : m_pBase( std::move( pBase ) )
{
  m_pRawCon = static_cast< Mysql::NativeConnectionHandle >( mysql_init( nullptr ) );
  for( const auto& entry : options )
    setOption( entry.first, entry.second );


  if( mysql_real_connect( nativeConnection( m_pRawCon ), hostName.c_str(), userName.c_str(), password.c_str(),
                          nullptr, port, nullptr, 0 ) == nullptr )
    throw std::runtime_error( mysql_error( nativeConnection( m_pRawCon ) ) );
}


Mysql::Connection::~Connection() = default;

void Mysql::Connection::setOption( Option option, const void* arg )
{

  if( mysql_options( nativeConnection( m_pRawCon ), toNativeOption( option ), arg ) != 0 )
    throw std::runtime_error( "Connection::setOption failed!" );
}

void Mysql::Connection::setOption( Option option, bool arg )
{
  MysqlBindBool nativeArg = static_cast< MysqlBindBool >( arg ? 1 : 0 );
  setOption( option, &nativeArg );
}

void Mysql::Connection::setOption( Option option, uint32_t arg )
{
  if( mysql_options( nativeConnection( m_pRawCon ), toNativeOption( option ), &arg ) != 0 )
    throw std::runtime_error( "Connection::setOption failed!" );
}

void Mysql::Connection::setOption( Option option, const std::string& arg )
{
  switch( getOptionValueKind( option ) )
  {
    case OptionValueKind::Bool:
      setOption( option, parseBool( arg ) );
      return;

    case OptionValueKind::UInt32:
      setOption( option, parseUInt32( arg ) );
      return;

    case OptionValueKind::String:
      if( mysql_options( nativeConnection( m_pRawCon ), toNativeOption( option ), arg.c_str() ) != 0 )
        throw std::runtime_error( "Connection::setOption failed!" );
      return;

    case OptionValueKind::NoValue:
      if( mysql_options( nativeConnection( m_pRawCon ), toNativeOption( option ), nullptr ) != 0 )
        throw std::runtime_error( "Connection::setOption failed!" );
      return;

    case OptionValueKind::KeyValue:
    {
      const size_t separator = arg.find( '=' );
      if( separator == std::string::npos )
        throw std::runtime_error( "Connection::setOption requires key=value format" );

      const std::string key = arg.substr( 0, separator );
      const std::string value = arg.substr( separator + 1 );
      if( key.empty() )
        throw std::runtime_error( "Connection::setOption requires a non-empty attribute key" );

      if( mysql_options4( nativeConnection( m_pRawCon ), toNativeOption( option ), key.c_str(), value.c_str() ) != 0 )
        throw std::runtime_error( "Connection::setOption failed!" );
      return;
    }

    case OptionValueKind::KeyOnly:
      if( arg.empty() )
        throw std::runtime_error( "Connection::setOption requires a non-empty attribute key" );
      if( mysql_options4( nativeConnection( m_pRawCon ), toNativeOption( option ), arg.c_str(), nullptr ) != 0 )
        throw std::runtime_error( "Connection::setOption failed!" );
      return;

    case OptionValueKind::SslMode:
    {
#if !defined( MARIADB_PACKAGE_VERSION_ID )
      mysql_ssl_mode mode = parseSslMode( arg );
      if( mysql_options( nativeConnection( m_pRawCon ), toNativeOption( option ), &mode ) != 0 )
        throw std::runtime_error( "Connection::setOption failed!" );
      return;
#else
      ( void ) arg;
      throw std::runtime_error( "Connection::setOption failed! MYSQL_OPT_SSL_MODE is not supported by this client library" );
#endif
    }
  }
}

void Mysql::Connection::close()
{
  mysql_close( nativeConnection( m_pRawCon ) );
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
  auto b = static_cast< MysqlBindBool >( autoCommit ? 1 : 0 );
  if( mysql_autocommit( nativeConnection( m_pRawCon ), b ) != 0 )
    throw std::runtime_error( "Connection::setAutoCommit failed!" );
}

bool Mysql::Connection::getAutoCommit()
{
  // TODO: should be replaced with wrapped sql query function once available
  std::string query( "SELECT @@autocommit" );
  auto res = mysql_real_query( nativeConnection( m_pRawCon ), query.c_str(), static_cast< unsigned long >( query.length() ) );

  if( res != 0 )
    throw std::runtime_error( "Query failed!" );

  auto pRes = mysql_store_result( nativeConnection( m_pRawCon ) );
  auto row = mysql_fetch_row( pRes );

  uint32_t ac = atoi( row[ 0 ] );

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

std::string Mysql::Connection::escapeString( std::string_view inData )
{
  std::string out( inData.length() * 2 + 1, '\0' );

  auto length = mysql_real_escape_string(
          nativeConnection( m_pRawCon ),
          out.data(),
          inData.data(),
          static_cast< unsigned long >( inData.length() ) );

  out.resize( length );
  return out;
}

void Mysql::Connection::setSchema( const std::string& schema )
{
  if( mysql_select_db( nativeConnection( m_pRawCon ), schema.c_str() ) != 0 )
    throw std::runtime_error( "Current database could not be changed to " + schema );
}

std::shared_ptr< Mysql::Statement > Mysql::Connection::createStatement()
{
  return std::make_shared< Mysql::Statement >( shared_from_this() );
}

std::string Mysql::Connection::getError()
{
  auto mysqlError = mysql_error( nativeConnection( m_pRawCon ) );
  if( mysqlError )
    return std::string( mysqlError );
  return "";
}

std::shared_ptr< Mysql::PreparedStatement > Mysql::Connection::prepareStatement( const std::string& sql )
{
  MYSQL_STMT* stmt = mysql_stmt_init( nativeConnection( m_pRawCon ) );

  if( !stmt )
    throw std::runtime_error( "Could not init prepared statement: " + getError() );

  if( mysql_stmt_prepare( stmt, sql.c_str(), static_cast< unsigned long >( sql.size() ) ) )
    throw std::runtime_error( "Could not prepare statement: " + sql + "\n" + getError() );

  return std::make_shared< PreparedStatement >( stmt, shared_from_this() );
}

uint32_t Mysql::Connection::getErrorNo()
{
  return mysql_errno( nativeConnection( m_pRawCon ) );
}

bool Mysql::Connection::ping()
{
  return mysql_ping( nativeConnection( m_pRawCon ) ) != 0;
}
