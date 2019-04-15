
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>

#include <fstream>
#include <streambuf>
#include <regex>

#include <Util/CrashHandler.h>

#include <experimental/filesystem>

Sapphire::Common::Util::CrashHandler crashHandler;

Sapphire::Data::ExdDataGenerated g_exdData;
xiv::dat::GameData* gameData = nullptr;

using namespace Sapphire;

namespace fs = std::experimental::filesystem;

//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
//const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );
std::string datLocation( "C:/SquareEnix/FINAL FANTASY XIV - A Realm Reborn/game/sqpack" );

void exportFile( const std::string& path )
{
  try
  {
    auto file = gameData->getFile( path );

    if( !file )
    {
      return;
    }
    auto p = fs::path( path );
    fs::create_directories( p.parent_path() );
    file->exportToFile( p );
  }
  catch( const std::exception& ex )
  {
    Logger::error( "Failed to export file {0}, error: {1}", path, ex.what() );
  }
}

bool replace( std::string& str, const std::string& from, const std::string& to )
{
  size_t start_pos = str.find( from );

  if( start_pos == std::string::npos )
    return false;

  str.replace( start_pos, from.length(), to );

  return true;
}

int main( int argc, char* argv[] )
{

  Logger::init( "questbattle_bruteforce" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }

  fs::create_directory( "questbattle_scripts" );

  std::vector< std::string > luabFiles;

  gameData = new xiv::dat::GameData( datLocation );

  auto questExdIds = g_exdData.getQuestIdList();

  for( auto id : questExdIds )
  {
    auto quest = g_exdData.get< Data::Quest >( id );

    if( !quest )
      continue;

    auto idString = quest->id;

    if( idString.empty() )
      continue;

    // galaxy brain shit right here
    auto folderId = fmt::format( "{:06d}", id & 0xFFFF ).substr( 1, 3 );

    replace( idString, "_", "Btl_" );

    auto path = fmt::format( "game_script/quest/{}/{}.luab", folderId, idString );

    try
    {
      auto file = gameData->getFile( path );

      if( !file )
      {
         continue;
      }

      auto filename = fmt::format( "questbattle_scripts/{}.luab", idString );

      luabFiles.emplace_back( filename );
      file->exportToFile( filename );

      Logger::info( "Exported file: {}", filename );
    }
    catch( const std::exception& ex )
    {

    }
  }

  Logger::info( "Decompiling luab scripts, pls wait..." );

  int i = 0;

  for( auto& filename : luabFiles )
  {
    filename.pop_back();

    system( fmt::format( "java -jar unluac_2015_06_13.jar {}b > {}", filename, filename ).c_str() );

    Logger::info( "Decompiling luab files - {} of {}", ++i, luabFiles.size() );
  }


  return 0;
}
