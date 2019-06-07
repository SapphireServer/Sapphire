#include "DbManager.h"
#include <MySqlConnector.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

DbManager::DbManager( const std::string& host, const std::string& database, const std::string& user, const std::string& pw, uint16_t port ) :
  m_host( host ),
  m_database( database ),
  m_user( user ),
  m_password( pw ),
  m_port( port ),	
  m_sFile( "sql/schema/schema.sql" ),
  m_iFile( "sql/schema/inserts.sql" ),
  m_force( false )
{
}

DbManager::~DbManager() = default;

bool DbManager::execute( const std::string& sql )
{
  try
  {
    auto stmt = m_pConnection->createStatement();
    bool result = stmt->execute( sql );
    return result;
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
}

void DbManager::setForceMode( bool mode )
{
  m_force = mode;
}

bool DbManager::connect()
{
  std::shared_ptr< Mysql::MySqlBase > base( new Mysql::MySqlBase() );
  Mysql::optionMap options;
  options[ Mysql::MYSQL_OPT_RECONNECT ] = "1";
  options[ Mysql::MYSQL_SET_CHARSET_NAME ] = "utf8";

  try
  {
    m_pConnection = base->connect( m_host, m_user, m_password, options, m_port );
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
  return true;
}

bool DbManager::selectSchema()
{
  if( !m_pConnection )
  {
    m_lastError = "No valid db connection!";	  
    return false;
  }

  try
  {
    m_pConnection->setSchema( m_database );
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
  return true;
}

const std::string& DbManager::getLastError()
{
  return m_lastError;
}

void DbManager::setMode( Mode mode )
{
  m_mode = mode;
}

Mode DbManager::getMode() const
{
  return m_mode;
}

bool DbManager::performAction()
{
  bool result = false;
  execute( " SET autocommit = 0 " );
  m_pConnection->beginTransaction();

  switch( m_mode )
  {
    case Mode::INIT:
      result = modeInit();
      break;
    case Mode::LIQUIDATE:
      result = modeLiquidate();
      break;
    case Mode::UPDATE:
      break;
    case Mode::CHECK:
      break;
    case Mode::CLEAN_CHARS:
      break;
  }
  if( !result )
    m_pConnection->rollbackTransaction();
  else
    m_pConnection->commitTransaction();

  return result;
}

bool DbManager::modeInit()
{


  bool result = false;
  bool dbCreated = false;

  if( selectSchema() )
  {
    std::string query = "SELECT COUNT(*) "
                        "FROM information_schema.tables "
                        "WHERE table_type = 'BASE TABLE' "
                        "AND table_schema = '" + m_database + "';";
    dbCreated = true;
    try
    {
      auto stmt = m_pConnection->createStatement();
      auto resultSet = stmt->executeQuery( query );

      if( !resultSet->next() )
        return false;

      auto count = resultSet->getUInt( 1 );
      if( count )
      {
        m_lastError = "Database " + m_database + " still contains tables. <Liquidate> it first!";
        return false;
      }

    }
    catch( std::runtime_error& e )
    {
      m_lastError = e.what();
      return false;
    }
  }

  if( !dbCreated )
    if( !execute( "CREATE DATABASE " + m_database ) )
      return false;

  if( !selectSchema() )
  {
    m_lastError = "Database not created.";
    return false;
  }

  std::ifstream t( m_sFile );
  if( !t.is_open() )
  {
    m_lastError = "File " + m_sFile + " does not exist!";
    return false;
  }
  std::string content( ( std::istreambuf_iterator< char >( t ) ),
                       ( std::istreambuf_iterator< char >( ) ) );
  std::string delimiter = ";";

  size_t pos = 0;
  std::string token;
  while( ( pos = content.find( delimiter ) ) != std::string::npos )
  {
    token = content.substr( 1, pos );
    size_t pos1 = token.find_first_not_of( "\r\n" );
    token = token.substr( pos1, token.size() );
    size_t pos2 = token.find_first_of( "\r\n" );
    std::cout << token.substr( 0, pos2 - 1 ) << std::endl;

    if( !execute( token ) )
      return false;

    content.erase( 0, pos + delimiter.length() );
  }

  std::cout << "======================================================" << std::endl;
  std::cout << "Inserting default values..." << std::endl;


  std::ifstream t1( m_iFile );
  if( !t1.is_open() )
  {
    m_lastError = "File " + m_iFile + " does not exist!";
    return false;
  }
  std::string content1( ( std::istreambuf_iterator< char >( t1 ) ),
                        ( std::istreambuf_iterator< char >( ) ) );
  std::string delimiter1 = ";";

  size_t pos_ = 0;
  std::string token1;
  while( ( pos_ = content1.find( delimiter1 ) ) != std::string::npos )
  {
    token1 = content1.substr( 1, pos_ );
    size_t pos_1 = token1.find_first_not_of( "\r\n" );
    token1 = token1.substr( pos_1, token1.size() );
    size_t pos_2 = token1.find_first_of( "(" );
    std::cout << token1.substr( 0, pos_2 - 1 ) << std::endl;

    if( !execute( token1 ) )
      return false;

    content1.erase( 0, pos_ + delimiter1.length() );
  }

  return true;
}

bool promptForChar( const char* prompt, char& readch )
{
  std::string tmp;
  std::cout << prompt << std::endl;
  if( std::getline( std::cin, tmp ) )
  {
    if( tmp.length() == 1 )
    {
      readch = tmp[ 0 ];
    }
    else
    {
      readch = '\0';
    }
    return true;
  }
  return false;
}

bool DbManager::modeLiquidate()
{
  if( !selectSchema() )
    return false;

  char type = '\0';
/*  if( !m_force )
    while( promptForChar( "This action will drop all tables in the database. Are you sure? [y/n]", type ) )
    {
      if( type == 'y' )
        break;
      if( type == 'n' )
        return true;
    }*/

  std::string query = "SELECT TABLE_NAME "
                      "FROM information_schema.tables "
                      "WHERE table_type = 'BASE TABLE' "
                      "AND table_schema = '" + m_database + "';";
  try
  {
    auto stmt = m_pConnection->createStatement();
    auto resultSet = stmt->executeQuery( query );

    while( resultSet->next() )
    {
      std::cout << "DROP TABLE `" + resultSet->getString( 1 ) + "`;" << "\n";
      if( !execute( "DROP TABLE `" + resultSet->getString( 1 ) + "`;" ) )
        return false;
    }
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }

  return true;
}

void DbManager::setInsertFile( const std::string& iFile )
{
  m_iFile = iFile;
}

void DbManager::setSchemaFile( const std::string& sFile )
{
  m_sFile = sFile;
}


