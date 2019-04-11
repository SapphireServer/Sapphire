
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

#include <Exd/StructureDef/pcb.h>
#include <Exd/StructureDef/lgb.h>
#include <Exd/StructureDef/sgb.h>

#include <Util/CrashHandler.h>

#include <experimental/filesystem>

Sapphire::Common::Util::CrashHandler crashHandler;

Sapphire::Data::ExdDataGenerated g_exdData;
xiv::dat::GameData* gameData = nullptr;

using namespace Sapphire;

namespace fs = std::experimental::filesystem;

//const std::string datLocation( "/opt/sapphire_3_15_0/bin/sqpack" );
const std::string datLocation( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );

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

struct DupeResult
{
  std::string groupName;
  std::string lgb;
  uint32_t id;
};

int main( int argc, char* argv[] )
{

  Logger::init( "struct_test" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( datLocation ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }

  gameData = new xiv::dat::GameData( datLocation );

  if( argc > 1 )
  {
    while( argc-- > 1 )
    {
      Logger::info( "Exporting file: {}", argv[ argc ] );
      exportFile( argv[ argc ] );
    }

    return 0;
  }

  std::vector< std::string > levelNames;
  std::vector< std::string > paths;
  
  std::vector< uint32_t > lgbGroupIds;
  std::vector< DupeResult > lgbGroupDupes;

  paths.emplace_back( "level/bg.lgb" );
  paths.emplace_back( "level/planmap.lgb" );
  paths.emplace_back( "level/planevent.lgb" );
  paths.emplace_back( "level/planlive.lgb" );
  paths.emplace_back( "level/sound.lgb" );
  paths.emplace_back( "level/planner.lgb" );

  auto ids = g_exdData.getTerritoryTypeIdList();

  for( auto id : ids )
  {
    auto territoryType = g_exdData.get< Data::TerritoryType >( id );
    if( !territoryType )
      continue;

    auto bg = territoryType->bg;
    bg = bg.substr( 0, bg.find( "/level/" ) );

    if( bg.empty() )
      continue;

    if( std::find( levelNames.begin(), levelNames.end(), bg ) != levelNames.end() )
      continue;

    levelNames.push_back( bg );

    Logger::info( "LGB groups for: {}", bg );

    for( const auto& path : paths )
    {
      auto filePath = fmt::format( "bg/{}/{}", bg, path );

      try
      {
        auto file = gameData->getFile( filePath );
        auto data = file->access_data_sections().at( 0 );

        LGB_FILE lgb( &data[ 0 ], "wtf" );

        Logger::info(" {} groups: {}", path, lgb.header.groupCount );

        for( const auto& group : lgb.groups )
        {
          Logger::info( " - {:<7} {:<25} children: {}", group.header.unknown, group.name, group.header.entryCount );

          if( std::find( lgbGroupIds.begin(), lgbGroupIds.end(), group.header.unknown ) == lgbGroupIds.end() )
          {
            lgbGroupIds.emplace_back( group.header.unknown );
          }
          else
          {
            lgbGroupDupes.push_back( { group.name, filePath, group.header.unknown } );
          }
        }
        Logger::info( "" );
      }
      catch( const std::exception& ex )
      {
        Logger::warn( "Failed on file {}, error: {}", path, ex.what() );
      }
    }
  }

  if( !lgbGroupDupes.empty() )
  {
    Logger::info( "Found duplicate LGB group ids: " );

    for( const auto& result : lgbGroupDupes )
    {
      Logger::info( " - file: {:<50} group: {:<30} id: {}", result.lgb, result.groupName, result.id );
    }
  }

  return 0;
}
