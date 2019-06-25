
#include <iostream>
#include <cctype>
#include <set>
#include <common/Logging/Logger.h>
#include <experimental/filesystem>
#include <MySqlConnector.h>
#include <common/Util/CrashHandler.h>
#include <common/Config/ConfigMgr.h>

Sapphire::Common::Util::CrashHandler crashHandler;

namespace filesys = std::experimental::filesystem;

#include <fstream>
#include <streambuf>
#include <regex>
#include <map>

#include "DbManager.h"

using namespace Sapphire;

std::vector< std::string > getAllFilesInDir( const std::string& dirPath,
                                             const std::vector< std::string > dirSkipList = {} )
{

  // Create a vector of string
  std::vector< std::string > listOfFiles;
  try
  {
    // Check if given path exists and points to a directory
    if( filesys::exists( dirPath ) && filesys::is_directory( dirPath ) )
    {
      // Create a Recursive Directory Iterator object and points to the starting of directory
      filesys::recursive_directory_iterator iter( dirPath );

      // Create a Recursive Directory Iterator object pointing to end.
      filesys::recursive_directory_iterator end;

      // Iterate till end
      while( iter != end )
      {
        // Check if current entry is a directory and if exists in skip list
        if( filesys::is_directory( iter->path() ) &&
            ( std::find( dirSkipList.begin(), dirSkipList.end(), iter->path().filename() ) != dirSkipList.end() ) )
        {
          // Skip the iteration of current directory pointed by iterator
          // c++17 Filesystem API to skip current directory iteration
          iter.disable_recursion_pending();
        }
        else
        {
          // Add the name in vector
          listOfFiles.push_back( iter->path().string() );
        }

        std::error_code ec;
        // Increment the iterator to point to next entry in recursive iteration
        iter.increment( ec );
        if( ec )
        {
          std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
        }
      }
    }
  }
  catch( std::system_error& e )
  {
    std::cerr << "Exception :: " << e.what();
  }
  return listOfFiles;
}

std::string delChar( std::string &str, char del )
{
  str.erase( std::remove( str.begin(), str.end(), del ), str.end() );
  return str;
}

void printUsage()
{
  Logger::info( " Usage: dbm " );
  Logger::info( "\t --mode" );
  Logger::info( "\t\t initialize -> Creates DB if not present and inserts default tables/data" );
  Logger::info( "\t\t check -> Checks if Sapphire DB-Version matches your DB-Version" );
  Logger::info( "\t\t migrate -> Updates your DB-Version to Sapphire DB-Version" );
  Logger::info( "\t\t clearchars -> Removes all character data from DB. Accounts will stay untouched" );
  Logger::info( "\t\t liquidate -> Removes all tables and deletes the DB" );
  Logger::info( "\t\t add-migration -> Creates a new migration with the assoicated up/down sql files" );
  Logger::info( "\t --user <mysqlUserName>" );
  Logger::info( "\t --pass <mysqlPassword> ( default empty )" );
  Logger::info( "\t --host <mysqlHost> ( default 127.0.0.1 )" );
  Logger::info( "\t --port <mysqlPort> ( default 3306 )" );
  Logger::info( "\t --database <mysqlDatabase>" );
  Logger::info( "\t --sfile <path/to/schemafile> ( default sql/schema/schema.sql )" );
  Logger::info( "\t --force ( skips user input / auto Yes )" );
  Logger::info( "\t --name <migration name>" );
}

int main( int32_t argc, char* argv[] )
{
  std::string arg( "" );
  std::string val( "" );

  std::string mode;
  std::string user;
  std::string host;
  std::string database;
  std::string pass;

  Logger::init( "log/dbm" );

  std::string sFile;
  std::string iFile;

  std::string migrationName;

  bool force = false;

  // load config first so it can still be overridden if required
  Common::ConfigMgr configMgr;
  Common::Config::GlobalConfig globalConfig;
  if( configMgr.loadGlobalConfig( globalConfig ) )
  {
    host = globalConfig.database.host;
    database = globalConfig.database.database;
    user = globalConfig.database.user;
    pass = globalConfig.database.password;
  }

  std::vector< std::string > args( argv + 1, argv + argc );
  for( uint32_t i = 0; i + 1 < args.size(); i += 2 )
  {
    arg = std::string( args[ i ] );
    val = std::string( args[ i + 1 ] );

      // trim '-' from start of arg
    arg = arg.erase( 0, arg.find_first_not_of( '-' ) );
    if( arg == "mode" )
      mode = val;
    else if( arg == "initialize" || arg == "liquidate" )
      mode = arg;
    else if( arg == "user" )
      user = val;
    else if( arg == "host" )
      host = val;
    else if( arg == "database" )
      database = val;
    else if( arg == "pass" )
      pass = val;
    else if( arg == "sfile" )
      sFile = val;
    else if( arg == "ifile" )
      iFile = val;
    else if( arg == "force" )
      force = true;
    else if( arg == "name" )
      migrationName = val;
  }

  if( host.empty() )
    host = "127.0.0.1";

  if( mode.empty() || user.empty() || database.empty() )
  {
    printUsage();
    return 0;
  }

  auto dbm = DbManager( host, database, user, pass, 3306 );

  if( !sFile.empty() && !iFile.empty() )
  {
    dbm.setInsertFile( iFile );
    dbm.setSchemaFile( sFile );
  }

  if( !migrationName.empty() )
  {
    dbm.setMigratioName( migrationName );
  }

  if( force )
    dbm.setForceMode( true );
  //initialize|check|update|clearchars|liquidate
  if( mode.find( "initialize" ) != std::string::npos )
  {
    dbm.setMode( Mode::INIT );
  }
  else if( mode.find( "check" ) != std::string::npos )
  {
    dbm.setMode( Mode::CHECK );
  }
  else if( mode.find( "migrate" ) != std::string::npos )
  {
    dbm.setMode( Mode::MIGRATE );
  }
  else if( mode.find( "clearchars" ) != std::string::npos )
  {
    dbm.setMode( Mode::CLEAN_CHARS );
  }
  else if( mode.find( "liquidate" ) != std::string::npos )
  {
    dbm.setMode( Mode::LIQUIDATE );
  }
  else if( mode.find( "add-migration" ) != std::string::npos )
  {
    dbm.setMode( Mode::ADD_MIGRATION );
  }
  else
  {
    Logger::fatal( "Not a valid mode: {0} !", mode );
    return 1;
  }

  Logger::info( "Launching in {0} mode...", mode );

  if( !dbm.connect() )
  {
    Logger::fatal( "Could not connect to server!" );
    Logger::fatal( dbm.getLastError() );
    return 1;
  }

  if( !dbm.performAction() )
  {
    Logger::fatal( "Could not perform action!" );
    Logger::fatal( dbm.getLastError() );
    return 1;
  }


  return 0;
}
