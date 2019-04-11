
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

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>

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

const std::string getTypeString( uint32_t type )
{
  switch( type )
  {
    case 1: return "BgParts";
    case 3: return "Light";
    case 4: return "Vfx";
    case 5: return "PositionMarker";
    case 6: return "Gimmick/SharedGroup6";
    case 7: return "Sound";
    case 8: return "EventNpc";
    case 9: return "BattleNpc";
    case 12: return "Aetheryte";
    case 13: return "EnvSpace";
    case 14: return "Gathering";
    case 15: return "SharedGroup15";
    case 16: return "Treasure";
    case 39: return "Weapon";
    case 40: return "PopRange";
    case 41: return "ExitRange";
    case 43: return "MapRange";
    case 44: return "NaviMeshRange";
    case 45: return "EventObject";
    case 47: return "EnvLocation";
    case 49: return "EventRange";
    case 51: return "QuestMarker";
    case 57: return "CollisionBox";
    case 58: return "DoorRange";
    case 59: return "LineVfx";
    case 65: return "ClientPath";
    case 66: return "ServerPath";
    case 67: return "GimmickRange";
    case 68: return "TargetMarker";
    case 69: return "ChairMarker";
    case 70: return "ClickableRange";
    case 71: return "PrefetchRange";
    case 72: return "FateRange";
    case 75: return "SphereCastRange";

    default: return "";
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
  std::vector< uint32_t > foundTypes;

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
          std::vector< uint32_t > types;

          for( const auto& entry : group.entries )
          {
            types.emplace_back( static_cast< uint32_t >( entry->getType() ) );
          }

          std::string typeStr;

          std::sort( types.begin(), types.end() );
          auto end = std::unique( types.begin(), types.end() );
          types.erase( end, types.end() );

          foundTypes.insert( foundTypes.end(), types.begin(), types.end() );

          for( auto type : types )
          {
            typeStr.append( " " + std::to_string( type ) );
          }

          Logger::info( " - {:<7} {:<25} groups: {:<3} types:{}",
                        group.header.id, group.name, group.header.entryCount, typeStr );

          if( std::find( lgbGroupIds.begin(), lgbGroupIds.end(), group.header.id ) == lgbGroupIds.end() )
          {
            lgbGroupIds.emplace_back( group.header.id );
          }
          else
          {
            lgbGroupDupes.push_back( { group.name, filePath, group.header.id } );
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
      Logger::info( " - id: {:<7} group: {:<30} file: {} ", result.id, result.groupName, result.lgb );
    }
  }

  Logger::info( "Found LGB entry types:" );

  std::sort( foundTypes.begin(), foundTypes.end() );
  auto end = std::unique( foundTypes.begin(), foundTypes.end() );
  foundTypes.erase( end, foundTypes.end() );

  for( auto type : foundTypes )
  {
    Logger::info( " - {:<3} {}", type, getTypeString( type ) );
  }

  return 0;
}
