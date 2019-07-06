#include "DbManager.h"
#include <MySqlConnector.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <Logging/Logger.h>
#include <experimental/filesystem>

#include <common/Util/Util.h>

using namespace Sapphire;
using namespace Sapphire::Common;

namespace fs = std::experimental::filesystem;

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
    case Mode::MIGRATE:
      result = modeMigrate();
      break;
    case Mode::CHECK:
      result = modeCheck();
      break;
    case Mode::ADD_MIGRATION:
      result = modeAddMigration();
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

  Logger::info( "======================================================" );
  Logger::info( "Inserting default values..." );


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

  Logger::info( "======================================================" );
  Logger::info( "Running migrations..." );

  return modeMigrate();
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
      Logger::info( "DROP TABLE `{}`;", resultSet->getString( 1 ) );
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

void DbManager::setMigratioName( const std::string& name )
{
  m_migrationName = name;
}

bool DbManager::modeCheck()
{
  if( !selectSchema() )
    return false;

  std::string query = "SELECT MigrationName FROM __Migration;";

  std::vector< std::string > appliedMigrations;

  try
  {
    auto stmt = m_pConnection->createStatement();
    auto resultSet = stmt->executeQuery( query );

    while( resultSet->next() )
    {
      appliedMigrations.emplace_back( resultSet->getString( 1 ) );
    }
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }

  uint32_t missing = 0;
  for( auto& entry : fs::directory_iterator( "sql/migrations" ) )
  {
    auto& path = entry.path();

    // just in case...
    if( path.extension() != ".sql" )
      continue;

    if( std::find( appliedMigrations.begin(), appliedMigrations.end(), path.filename().string() ) == appliedMigrations.end() )
    {
      Logger::info( "Missing migration: {}", path.filename().string() );
      missing++;
    }
  }

  if( missing > 0 )
  {
    Logger::warn( "Database is missing {} migration(s).", missing );
  }
  else
  {
    Logger::info( "All available migrations have been applied." );
  }

  return true;
}

bool DbManager::modeMigrate()
{
  if( !selectSchema() )
    return false;

  std::string query = "SELECT MigrationName FROM __Migration;";

  std::vector< std::string > appliedMigrations;

  try
  {
    auto stmt = m_pConnection->createStatement();
    auto resultSet = stmt->executeQuery( query );

    while( resultSet->next() )
    {
      appliedMigrations.emplace_back( resultSet->getString( 1 ) );
    }
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }

  std::vector< std::string > migrations;
  for( auto& entry : fs::directory_iterator( "sql/migrations" ) )
  {
    auto& path = entry.path();

    // just in case...
    if( path.extension() != ".sql" )
      continue;

    migrations.emplace_back( path.string() );
  }

  std::sort( migrations.begin(), migrations.end() );

  for( auto& entry : migrations )
  {
    auto path = fs::path( entry );

    if( std::find( appliedMigrations.begin(), appliedMigrations.end(), path.filename().string() ) == appliedMigrations.end() )
    {
      Logger::info( "Applying migration: {}", path.filename().string() );

      std::ifstream mFile( path.string() );
      if( !mFile.is_open() )
      {
        m_lastError = "File " + path.string() + " does not exist!";
        return false;
      }
      std::string sql( ( std::istreambuf_iterator< char >( mFile ) ),
                       ( std::istreambuf_iterator< char >( ) ) );

      try
      {
        auto stmt = m_pConnection->createStatement();
        stmt->executeQuery( sql );
      }
      catch( std::runtime_error& e )
      {
        m_lastError = e.what();
        return false;
      }

      // insert into migrations table
      if( !execute( fmt::format( "INSERT INTO __Migration (`MigrationName`) VALUES ('{}');", path.filename().string() ) ) )
        return false;
    }
  }



  return true;
}

bool DbManager::modeAddMigration()
{
  if( !selectSchema() )
    return false;

  fs::create_directories( "sql/migrations" );

  auto filename = fmt::format( "{}_{}.sql", Util::fmtUtcTime( "%Y%m%d%H%M%S" ), m_migrationName );

  if( filename.size() > 250 )
  {
    Logger::error( "Migration name '{}' is longer than 250 characters, please shorten its name.", filename );
    return false;
  }

  auto path = fmt::format( "sql/migrations/{}", filename );

  if( fs::exists( path ) )
  {
    Logger::error( "Migration '{}' already exists.", filename );
    return false;
  }

  std::ofstream mFile( path );

  mFile << fmt::format( "-- Migration generated at {}", Util::fmtUtcTime( "%Y/%m/%d %H:%M:%S" ) ) << std::endl;
  mFile << fmt::format( "-- {}", filename ) << std::endl << std::endl;

  mFile.close();

  Logger::info( "New migration created: {}", path );

  return true;
}


