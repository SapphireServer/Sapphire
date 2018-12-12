
#include <iostream>
#include <cctype>
#include <set>
#include <common/Logging/Logger.h>
#include <experimental/filesystem>
#include <MySqlConnector.h>


namespace filesys = std::experimental::filesystem;

#include <fstream>
#include <streambuf>
#include <regex>
#include <map>

#include "DbManager.h"

Sapphire::Logger g_log;

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
  g_log.info( " Usage: sapphire_dbm " );
  g_log.info( "\t --mode" );
  g_log.info( "\t\t initialize -> Creates DB if not present and inserts default tables/data" );
  g_log.info( "\t\t check -> Checks if Sapphire DB-Version matches your DB-Version" );
  g_log.info( "\t\t update -> Updates your DB-Version to Sapphire DB-Version" );
  g_log.info( "\t\t clearchars -> Removes all character data from DB. Accounts will stay untouched" );
  g_log.info( "\t\t liquidate -> Removes all tables and deletes the DB" );
  g_log.info( "\t --user <mysqlUserName>" );
  g_log.info( "\t --pass <mysqlPassword> ( default empty )" );
  g_log.info( "\t --host <mysqlHost> ( default 127.0.0.1 )" );
  g_log.info( "\t --port <mysqlPort> ( default 3306 )" );
  g_log.info( "\t --database <mysqlDatabase>" );
  g_log.info( "\t --sfile <path/to/schemafile> ( default sql/schema/schema.sql )" );
  g_log.info( "\t --force ( skips user input / auto Yes )" );
}

int main( int32_t argc, char* argv[] )
{
  std::string arg( "" );
  std::string val( "" );

  std::string mode;
  std::string user;
  std::string host;
  std::string database;
  
  g_log.setLogPath( "log/SapphireDbm" );
  g_log.init();

  std::string sFile;
  std::string iFile;

  bool force = false;

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
    else if( arg == "sfile" )
      sFile = val;
    else if( arg == "ifile" )
      iFile = val;
    else if( arg == "force" )
      force = true;	    
  }	  

  if( host.empty() )
    host = "127.0.0.1";

  if( mode.empty() || user.empty() || database.empty() )
  {
    printUsage();
    return 0;
  }

  auto dbm = DbManager( host, database, user, "", 3306 );
  
  if( !sFile.empty() && !iFile.empty() )
  {
    dbm.setInsertFile( iFile );
    dbm.setSchemaFile( sFile );
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
  else if( mode.find( "update" ) != std::string::npos )
  {
    dbm.setMode( Mode::UPDATE );
  }
  else if( mode.find( "clearchars" ) != std::string::npos )
  {
    dbm.setMode( Mode::CLEAN_CHARS );
  }
  else if( mode.find( "liquidate" ) != std::string::npos )
  {
    dbm.setMode( Mode::LIQUIDATE );
  }
  else
  { 
    g_log.fatal( "Not a valid mode: " + mode + " !" );
    return 1;
  }	  
	
  g_log.info( "Launching in " + mode + " mode..." );

  if( !dbm.connect() )
  {
    g_log.fatal( "Could not connect to server!" );
    g_log.fatal( dbm.getLastError() );
    return 1;
  }

  if( !dbm.performAction() )
  {
    g_log.fatal( "Could not perform action!" );
    g_log.fatal( dbm.getLastError() );
    return 1;
  }


  return 0;
}
