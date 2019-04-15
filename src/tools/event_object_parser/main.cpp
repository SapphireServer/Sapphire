#include <stdio.h>
#include <cstdint>
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <variant>
#include <Util/Util.h>
#include <Util/CrashHandler.h>

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <experimental/filesystem>

Sapphire::Common::Util::CrashHandler crashHandler;
Sapphire::Data::ExdDataGenerated g_exdData;

using namespace Sapphire;
using namespace std::chrono_literals;
namespace fs = std::experimental::filesystem;

// garbage to ignore models
bool ignoreModels = false;
std::string gamePath( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );
//std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::unordered_map< uint32_t, std::string > eobjNameMap;

struct instanceContent
{
  uint32_t id;
  std::string name;
  std::string zoneName;
  uint8_t type;
};

std::vector< instanceContent > contentList;
xiv::dat::GameData* g_gameData = nullptr;

void initExd( const std::string& gamePath )
{
  g_gameData = g_gameData ? g_gameData : new xiv::dat::GameData( gamePath );
}

std::unordered_map< std::string, std::string > g_nameMap;
std::string zoneNameToPath( const std::string& name )
{
  std::string path;

  auto it = g_nameMap.find( Sapphire::Util::toLowerCopy( name ) );
  if( it != g_nameMap.end() )
    return it->second;

  auto teriIdList = g_exdData.getTerritoryTypeIdList();
  for( auto teriId : teriIdList )
  {
    auto teri = g_exdData.get< Sapphire::Data::TerritoryType >( teriId );
    if( !teri )
      continue;
    
    auto teriName = teri->name;
    auto teriPath = teri->bg;
    
    if( teriName.empty() )
      continue;
    
    if( Sapphire::Util::toLowerCopy( name ) == Sapphire::Util::toLowerCopy( teriName ) )
    {
      path = teriPath;
      break;
    }
  }

  if( !path.empty() )
  {
    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );
    Logger::debug( "Found path for {0}: {1}", name, path );
    g_nameMap[ Sapphire::Util::toLowerCopy( name ) ] = path; 
  }
  else
  {
    throw std::runtime_error( "Unable to find path for " + name );
  }

  return path;
}

void loadEobjNames()
{
  auto nameIdList = g_exdData.getEObjNameIdList();
  for( auto id : nameIdList )
  {
    auto eObjName = g_exdData.get< Sapphire::Data::EObjName >( id );
    if( !eObjName )
      continue;

    if( !eObjName->singular.empty() )
      eobjNameMap[ id ] = eObjName->singular;
  }
}

void loadAllInstanceContentEntries()
{
  auto cfcIdList = g_exdData.getContentFinderConditionIdList();
  for( auto cfcId : cfcIdList )
  {
    auto cfc = g_exdData.get< Sapphire::Data::ContentFinderCondition >( cfcId );
    if( !cfc )
      continue;
    
    uint16_t teriId = cfc->territoryType;
    auto tt = g_exdData.get< Sapphire::Data::TerritoryType >( teriId );
    if( !tt )
      continue;
    uint16_t contentId = cfc->content;
    uint8_t type;
    std::string name;
    
    if( cfc->contentLinkType == 1 )
    {
      auto ic = g_exdData.get< Sapphire::Data::InstanceContent >( cfc->content );
      if( !ic )
        continue;
      type = ic->instanceContentType;
      name = ic->name;
    }
    else if( cfc->contentLinkType == 5 )
    { 
      auto qb = g_exdData.get< Sapphire::Data::QuestBattle >( cfc->content );
      if( !qb )
        continue;
      auto q = g_exdData.get< Sapphire::Data::Quest >( qb->quest );
      if( !q )
        continue;
      type = 7;
      name = q->name;
    }
    else
      continue;
    
    if( name.empty() )
      continue;
    
    auto i = 0;
    while( ( i = name.find( ' ' ) ) != std::string::npos )
      name = name.replace( name.begin() + i, name.begin() + i + 1, { '_' } );
    
    std::string remove = ",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:";
    Sapphire::Util::eraseAllIn( name, remove );
    name[ 0 ] = toupper( name[ 0 ] );
    contentList.push_back( { contentId, name, tt->name, type } );
  }
}

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::system_clock::now();
  auto entryStartTime = std::chrono::system_clock::now();

  Logger::init( "Event Object Parser" );

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( gamePath ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
  }

  std::vector< std::string > argVec( argv + 1, argv + argc );
  // todo: support expansions
  std::string zoneName = "r2t2";
  ignoreModels = true;
  if( argc > 1 )
  {
    zoneName = argv[ 1 ];
    if( argc > 2 )
    {
      std::string tmpPath( argv[ 2 ] );
      if( !tmpPath.empty() )
        gamePath = argv[ 2 ];
    }
  }

  std::map< uint8_t, std::string > instanceContentTypeMap;
  instanceContentTypeMap[ 0 ] = "";
  instanceContentTypeMap[ 1 ] = "raids";
  instanceContentTypeMap[ 2 ] = "dungeons";
  instanceContentTypeMap[ 3 ] = "guildhests";
  instanceContentTypeMap[ 4 ] = "trials";
  instanceContentTypeMap[ 5 ] = "pvp/thefeast";
  instanceContentTypeMap[ 6 ] = "pvp";
  instanceContentTypeMap[ 7 ] = "questbattles";
  instanceContentTypeMap[ 8 ] = "hallofthenovice";
  instanceContentTypeMap[ 9 ] = "deepdungeon";
  instanceContentTypeMap[ 10 ] = "treasurehunt";
  instanceContentTypeMap[ 11 ] = "events";
  instanceContentTypeMap[ 12 ] = "pvp/rivalwings";
  instanceContentTypeMap[ 13 ] = "maskedcarnivale"; // todo: better name?
  instanceContentTypeMap[ 14 ] = "goldsaucer/mahjong";
  instanceContentTypeMap[ 15 ] = "goldsaucer";

  if( !fs::exists( "instance.tmpl" ) )
    throw std::runtime_error( "instance.tmpl is missing in working directory" );

  try
  {
    initExd( gamePath );
  }
  catch( std::runtime_error error )
  {
    Logger::error( error.what() );
  }
  
  loadAllInstanceContentEntries();
  loadEobjNames();

  for( auto entry : contentList )
  {
    std::string eobjects = "";
    entryStartTime = std::chrono::system_clock::now();
    zoneName = entry.zoneName;
    try
    {
      const auto& zonePath = zoneNameToPath( zoneName );
      std::string bgLgbPath( zonePath + "/level/bg.lgb" );
      std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
      std::string planeventLgbPath( zonePath + "/level/planevent.lgb" );
      std::string plannerFilePath( zonePath + "/level/planner.lgb" );

      auto bgFile = g_gameData->getFile( bgLgbPath );
      auto planmapFile = g_gameData->getFile( planmapLgbPath );
      auto planeventFile = g_gameData->getFile( planeventLgbPath );
      auto plannerFile = g_gameData->getFile( plannerFilePath );
      
      auto bgData = bgFile->access_data_sections().at( 0 );
      auto planmapData = planmapFile->access_data_sections().at( 0 );
      auto planeventData = planeventFile->access_data_sections().at( 0 );
      auto plannerData = plannerFile->access_data_sections().at( 0 );

      LGB_FILE bgLgb( &bgData[ 0 ], "bg" );
      LGB_FILE planmapLgb( &planmapData[ 0 ], "planmap" );
      LGB_FILE planeventLgb( &planeventData[ 0 ], "planevent" );
      LGB_FILE planerLgb( &plannerData[ 0 ], "planner" );

      std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb };

      uint32_t totalGroups = 0;
      uint32_t totalGroupEntries = 0;
      uint32_t count = 0;
      for( const auto& lgb : lgbList )
      {
        std::map< std::string, uint32_t > nameMap;
        for( const auto& group : lgb.groups )
        {
          totalGroups++;
          for( const auto& pEntry : group.entries )
          {
            auto pGimmick = dynamic_cast< LGB_GIMMICK_ENTRY* >( pEntry.get() );
            auto pBgParts = dynamic_cast< LGB_BGPARTS_ENTRY* >( pEntry.get() );
            totalGroupEntries++;

            if( pEntry->getType() == LgbEntryType::EventObject )
            {
              auto pObj = pEntry.get();
              static std::string eobjStr( "\"EObj\", " );
              uint32_t id;
              uint32_t unknown = 0, unknown2 = 0;
              std::string name;
              uint32_t eobjlevelHierachyId = 0;

              auto pEobj = reinterpret_cast< LGB_EOBJ_ENTRY* >( pObj );
              id = pEobj->header.eobjId;
              unknown = pEobj->header.unknown;

              eobjlevelHierachyId = pEobj->header.levelHierachyId;

              std::string states = "";
              std::string gimmickName = "";
              for( const auto& pEntry1 : group.entries )
              {
                auto pGObj = pEntry1.get();
                if( pGObj->getType() == LgbEntryType::Gimmick &&
                    pGObj->header.unknown == pEobj->header.levelHierachyId )
                {
                  auto pGObjR = reinterpret_cast< LGB_GIMMICK_ENTRY* >( pGObj );
                  char* dataSection = nullptr;

                  auto file = g_gameData->getFile( pGObjR->gimmickFileName );
                  auto sections = file->get_data_sections();
                  dataSection = &sections.at( 0 )[ 0 ];
                  auto sgbFile = SGB_FILE( &dataSection[ 0 ] );

                  auto pos = pGObjR->gimmickFileName.find_last_of( "/" );

                  if( pos != std::string::npos )
                  {
                    name = pGObjR->gimmickFileName.substr( pos + 1 );
                    name = name.substr( 0, name.length() - 4 );
                    gimmickName = name;
                  }

                  if( sgbFile.stateEntries.size() > 0 )
                  {
                    states = "    // States -> ";
                    for( auto entries1 : sgbFile.stateEntries )
                    {
                      states += entries1.name + " (id: " + std::to_string( entries1.header.id ) + ") ";
                    }
                    states += "\n";
                  }
                  break;
                }
              }
              int state = 4;

              if( eobjNameMap.find( id ) != eobjNameMap.end() )
              {
                name = eobjNameMap[ id ];
                std::string remove = ",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:";
                Sapphire::Util::eraseAllIn( name, remove );
                name[ 0 ] = toupper( name[ 0 ] );
              }
              if( name.empty() )
                name = "unknown_" + std::to_string( count++ );

              if( id == 2000182 || gimmickName == "sgvf_w_lvd_b0095" )
              {
                state = 5;
                name = "Entrance";
              }

              auto count1 = 0;
              if( nameMap.find( name ) == nameMap.end() )
              {
                nameMap[ name ] = 0;
              }
              else
              {
                nameMap[ name ] = ++nameMap[ name ];
                count1 = nameMap[ name ];
              }

              if( count1 > 0 )
                name = name + "_" + std::to_string( count1 );

              eobjects += "    instance.registerEObj( \"" + name + "\", " + std::to_string( id ) +
                            ", " + std::to_string( eobjlevelHierachyId ) + ", " + std::to_string( state ) +
                            ", " +
                            "{ " + std::to_string( pObj->header.translation.x ) + "f, "
                            + std::to_string( pObj->header.translation.y ) + "f, "
                            + std::to_string( pObj->header.translation.z ) + "f }, " +
                            std::to_string( pObj->header.scale.x ) + "f, " +

                            // the rotation inside the sgbs is the inverse of what the game uses
                            std::to_string( pObj->header.rotation.y * -1.f ) + "f ); \n" + states;
            }
          }
        }
	Logger::info( "Total Groups {}, Total Entries {}", totalGroups, totalGroupEntries );
      }
      Logger::info( "Exported {} in {} seconds", zoneName, 
                std::chrono::duration_cast< std::chrono::seconds >(
                  std::chrono::system_clock::now() - entryStartTime ).count() );
    }
    catch( std::exception& e )
    {
      Logger::error( "{}", e.what() );
    }

    std::ifstream t;
    if( entry.type == 7 )
    {
      t = std::ifstream ( "questbattle.tmpl" );
    }
    else
      t = std::ifstream ( "instance.tmpl" );

    std::string instanceTpl( ( std::istreambuf_iterator< char >( t ) ),
                             std::istreambuf_iterator< char >() );

    auto result = std::regex_replace( instanceTpl, std::regex( "\\INSTANCE_NAME" ), entry.name );
    result = std::regex_replace( result, std::regex( "\\INSTANCE_ID" ), std::to_string( entry.id ) );
    result = std::regex_replace( result, std::regex( "\\EOBJ_INIT" ), eobjects );

    if( entry.type == 7 )
    {
      if( entry.id > 200 )
        continue;

      auto qb = g_exdData.get< Sapphire::Data::QuestBattle >( entry.id );
      if( !qb )
        continue;

      std::string instruction;
      for( int i = 0; i < 149; ++i )
      {
        if( qb->scriptInstruction[ i ].empty() )
          continue;
        instruction += "  static constexpr auto " + qb->scriptInstruction[ i ] + " = " +
                       std::to_string( qb->scriptValue[ i ] ) + ";\n";
      }

      result = std::regex_replace( result, std::regex( "\\SCRIPT_INSTRUCTIONS" ), instruction );
    }

    std::string subdir = "";

    auto subdirIt = instanceContentTypeMap.find( entry.type );
    if( subdirIt != instanceContentTypeMap.end() )
      subdir = subdirIt->second + "/";

    fs::path outDir( "instances/" + subdir );
    fs::create_directories( outDir );

    std::ofstream outH( outDir.string() + entry.name + ".cpp" );
    outH << result;
    outH.close();

  }

  Logger::info( "Finished all tasks in {} seconds", 
            std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now() - startTime ).count() );

  if( g_gameData )
    delete g_gameData;
  return 0;
}
