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
#include <cmath>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Util/CrashHandler.h>

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>

#include <Exd/ExdData.h>
#include <Logging/Logger.h>

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <filesystem>

#include "vec3.h"
#include "matrix4.h"

[[maybe_unused]] Sapphire::Common::Util::CrashHandler crashHandler;
Sapphire::Data::ExdData g_exdData;

using namespace Sapphire;
using namespace std::chrono_literals;
namespace fs = std::filesystem;

// garbage to ignore models
bool ignoreModels = false;
//std::string gamePath( "/mnt/c/Program Files (x86)/Steam/steamapps/common/FINAL FANTASY XIV Online/game/sqpack" );
//std::string gamePath( "C:\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
std::string gamePath( "D:\\ffxiv3.35\\game\\sqpack" );
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

  auto it = g_nameMap.find( Common::Util::toLowerCopy( name ) );
  if( it != g_nameMap.end() )
    return it->second;

  auto teriIdList = g_exdData.getIdList< Excel::TerritoryType >();
  for( auto teriId : teriIdList )
  {
    auto teri = g_exdData.getRow< Excel::TerritoryType >( teriId );
    if( !teri )
      continue;
    
    auto teriName = teri->getString( teri->data().Name );
    auto teriPath = teri->getString( teri->data().LVB );
    
    if( teriName.empty() )
      continue;
    
    if( Common::Util::toLowerCopy( name ) == Common::Util::toLowerCopy( teriName ) )
    {
      path = teriPath;
      break;
    }
  }

  if( !path.empty() )
  {
    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );
    Logger::debug( "Found path for {0}: {1}", name, path );
    g_nameMap[ Common::Util::toLowerCopy( name ) ] = path;
  }
  else
  {
    throw std::runtime_error( "Unable to find path for " + name );
  }

  return path;
}

void loadEobjNames()
{
  auto nameIdList = g_exdData.getIdList< Excel::EObj >();
  for( auto id : nameIdList )
  {
    auto eObjName = g_exdData.getRow< Excel::EObj >( id );
    if( !eObjName )
      continue;

    if( !eObjName->getString( eObjName->data().Text.SGL ).empty() )
      eobjNameMap[ id ] = eObjName->getString( eObjName->data().Text.SGL );
  }
}

void loadAllInstanceContentEntries()
{
  auto cfcIdList = g_exdData.getIdList< Excel::InstanceContent >();
  for( auto cfcId : cfcIdList )
  {

    auto cfc = g_exdData.getRow< Excel::InstanceContent >( cfcId );
    if( !cfc )
      continue;
    
    uint16_t teriId = cfc->data().TerritoryType;
    auto tt = g_exdData.getRow< Excel::TerritoryType >( teriId );
    if( !tt )
      continue;
    uint16_t contentId = cfcId;
    uint8_t type;
    std::string name;

    type = cfc->data().Type;
    name = cfc->getString( cfc->data().Text.Name );

  /*  else if( cfc->contentLinkType == 5 )
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
      continue;*/
    
    if( name.empty() )
      continue;
    
    auto i = 0;
    while( ( i = name.find( ' ' ) ) != std::string::npos )
      name = name.replace( name.begin() + i, name.begin() + i + 1, { '_' } );
    
    std::string remove = ",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:";
    Common::Util::eraseAllIn( name, remove );
    name[ 0 ] = toupper( name[ 0 ] );
    contentList.push_back( { contentId, name, tt->getString( tt->data().Name ), type } );
  }

  auto qbIdList = g_exdData.getIdList< Excel::QuestBattle >();
  for( auto qbId : qbIdList )
  {
    uint8_t type = 7;
    std::string name;
    auto qb = g_exdData.getRow< Excel::QuestBattle >( qbId );
    if( !qb )
      continue;

    auto quest = g_exdData.getRow< Excel::Quest >( qb->data().Quest );

    if( !quest )
      continue;

    name = quest->getString( quest->data().Text.Name );
    if( name.empty() )
      continue;
    auto i = 0;
    while( ( i = name.find( ' ' ) ) != std::string::npos )
      name = name.replace( name.begin() + i, name.begin() + i + 1, { '_' } );

    std::string remove = ",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:\"";
    Common::Util::eraseAllIn( name, remove );
    name[ 0 ] = toupper( name[ 0 ] );

    contentList.push_back( { qbId, name, fmt::format( "e0{:03d}", qbId + 1 ), type } );

  }
}

bool invalidChar (char c)
{
  return !isprint((unsigned)c);
}

void stripUnicode(std::string & str)
{
  str.erase(remove_if(str.begin(),str.end(), invalidChar), str.end());
}

// todo: i don't trust the overloads enough
template< typename TVec >
vec3 toVec3( const TVec& value )
{
  return { value.x, value.y, value.z };
}

vec3 applyRotation( vec3 value, const vec3& rotation )
{
  value = value * matrix4::rotateX( rotation.x );
  value = value * matrix4::rotateY( rotation.y );
  value = value * matrix4::rotateZ( rotation.z );
  return value;
}

vec3 applyTransform( vec3 value, const vec3& scale, const vec3& rotation, const vec3& translation )
{
  value.x *= scale.x;
  value.y *= scale.y;
  value.z *= scale.z;

  value = applyRotation( value, rotation );

  value.x += translation.x;
  value.y += translation.y;
  value.z += translation.z;

  return value;
}

vec3 scaleExtents( const vec3& extents, const vec3& scale )
{
  return { std::fabs( extents.x * scale.x ), std::fabs( extents.y * scale.y ), std::fabs( extents.z * scale.z ) };
}

float wrapAngle( float angle )
{
  return std::atan2( std::sin( angle ), std::cos( angle ) );
}

float toGameYaw( float yaw )
{
  return wrapAngle( -yaw );
}

float directionFromForward( const vec3& forward )
{
  return wrapAngle( std::atan2( -forward.x, forward.z ) );
}

float composeCollisionRotation( const vec3& parentRotation, const vec3& localRotation )
{
  auto forward = applyRotation( vec3{ 0.0f, 0.0f, 1.0f }, localRotation );
  forward = applyRotation( forward, parentRotation );
  return directionFromForward( forward );
}

int main( int argc, char* argv[] )
{
  auto startTime = std::chrono::system_clock::now();
  auto entryStartTime = std::chrono::system_clock::now();

  Logger::init( "Event Object Parser" );

  std::vector< std::string > argVec( argv + 1, argv + argc );
  // todo: support expansions
  std::string zoneName = "r2t2";
  ignoreModels = true;
  if( argc > 1 )
  {
    std::string tmpPath( argv[ 1 ] );
    if( !tmpPath.empty() )
      gamePath = argv[ 1 ];
  }

  if( argc > 2 )
  {
    zoneName = argv[ 2 ];
  }

  Logger::info( "Setting up EXD data" );
  if( !g_exdData.init( gamePath ) )
  {
    Logger::fatal( "Error setting up EXD data " );
    return 0;
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
    std::string eobjects = "    Entity::EventObjectPtr pEObj;\n\n";
    entryStartTime = std::chrono::system_clock::now();
    zoneName = entry.zoneName;
    try
    {
      std::unordered_map< uint32_t, SharedGroupEntry* > m_sharedGroupMap;
      std::unordered_map< uint32_t, EventObjectEntry* > m_eventObjectMap;
      std::map< uint32_t, std::string > m_eventObjectStrings;

      const auto& zonePath = zoneNameToPath( zoneName );
      std::string bgLgbPath( zonePath + "/level/bg.lgb" );
      std::string planmapLgbPath( zonePath + "/level/planmap.lgb" );
      std::string planeventLgbPath( zonePath + "/level/planevent.lgb" );
      std::string plannerFilePath( zonePath + "/level/planner.lgb" );

      auto bgFile = g_gameData->getFile( bgLgbPath );
      auto planmapFile = g_gameData->getFile( planmapLgbPath );
      auto planeventFile = g_gameData->getFile( planeventLgbPath );
      //auto plannerFile = g_gameData->getFile( plannerFilePath );
      
      auto bgData = bgFile->access_data_sections().at( 0 );
      auto planmapData = planmapFile->access_data_sections().at( 0 );
      auto planeventData = planeventFile->access_data_sections().at( 0 );
      //auto plannerData = plannerFile->access_data_sections().at( 0 );

      LGB_FILE bgLgb( &bgData[ 0 ], "bg" );
      LGB_FILE planmapLgb( &planmapData[ 0 ], "planmap" );
      LGB_FILE planeventLgb( &planeventData[ 0 ], "planevent" );
      //LGB_FILE planerLgb( &plannerData[ 0 ], "planner" );

      std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb, planeventLgb };

      uint32_t totalGroups = 0;
      uint32_t totalGroupEntries = 0;
      uint32_t count = 0;

      uint8_t permissionInv = 0;
      for( const auto& lgb : lgbList )
      {
        std::map< std::string, uint32_t > nameMap;
        for( const auto& group : lgb.groups )
        {
          totalGroups++;
          for( const auto& pEntry : group.entries )
          {
            if( pEntry->getType() == SharedGroup )
            {
              auto pGimmick = dynamic_cast< SharedGroupEntry* >( pEntry.get() );
              m_sharedGroupMap.emplace( pEntry->header.InstanceID, pGimmick );
            }
            else if( pEntry->getType() == eAssetType::EventObject )
            {
              auto pObj = pEntry.get();
              uint32_t id;
              uint32_t instanceId;
              std::string name;
              uint32_t eobjlevelHierachyId = 0;

              auto pEobj = reinterpret_cast< EventObjectEntry* >( pObj );
              id = pEobj->header.BaseId;
              instanceId = pEobj->header.InstanceID;

              eobjlevelHierachyId = pEobj->header.BoundInstanceID;

              std::string states = "";
              std::string gimmickName = "";
              for( const auto& pEntry1 : group.entries )
              {
                auto pGObj = pEntry1.get();
                if( pGObj->getType() == eAssetType::SharedGroup && pGObj->header.InstanceID == pEobj->header.BoundInstanceID )
                {
                  auto pGObjR = reinterpret_cast< SharedGroupEntry* >( pGObj );
                  char* dataSection = nullptr;

                  auto file = g_gameData->getFile( pGObjR->AssetPath );
                  auto sections = file->get_data_sections();
                  dataSection = &sections.at( 0 )[ 0 ];
                  auto sgbFile = SGB_FILE( &dataSection[ 0 ] );

                  auto pos = pGObjR->AssetPath.find_last_of( "/" );

                  if( pos != std::string::npos )
                  {
                    name = pGObjR->AssetPath.substr( pos + 1 );
                    name = name.substr( 0, name.length() - 4 );
                    gimmickName = name;
                  }

                  if( sgbFile.timelines.size() > 0 )
                  {
                    states = "    // States -> ";
                    for( auto i = 0; i < sgbFile.timelines.size(); ++i )
                    {
                      auto entries1 = sgbFile.timelines[ i ];
                      auto name = sgbFile.timelineNames[ i ];
                      states += name + " (id: " + std::to_string( entries1.MemberID ) + ") ";
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
                stripUnicode( name );
                std::string remove = ",★_ '()[]-\xae\x1a\x1\x2\x1f\x1\x3.:";
                Common::Util::eraseAllIn( name, remove );
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

              std::string eobjLine;
              eobjLine += "    pEObj = instance.addEObj( \"" + name + "\", " + std::to_string( id ) +
                          ", " + std::to_string( eobjlevelHierachyId ) +
                          ", " + std::to_string( instanceId ) + ", " + std::to_string( state ) +
                          ", " + "{ " + std::to_string( pObj->header.Transformation.Translation.x ) + "f, " + std::to_string( pObj->header.Transformation.Translation.y ) + "f, " + std::to_string( pObj->header.Transformation.Translation.z ) + "f }, " + std::to_string( pObj->header.Transformation.Scale.x ) + "f, "

                          // the rotation inside the sgbs is the inverse of what the game uses
                          + std::to_string( toGameYaw( pObj->header.Transformation.Rotation.y ) ) + "f" + ", " + std::to_string( permissionInv ) + " ); \n" + states;

              m_eventObjectStrings.emplace( instanceId, eobjLine );
              m_eventObjectMap.emplace( instanceId, pEobj );
            }
          }
        }
	      Logger::info( "Total Groups {}, Total Entries {}", totalGroups, totalGroupEntries );
      }
     
      // gather dynamic collisions controlled by eobj
      for( auto [ instanceId, object ] : m_eventObjectMap )
      {

        if( object->header.BoundInstanceID != 0 )
        {
          auto pBoundGroup = m_sharedGroupMap[ object->header.BoundInstanceID ];
          if( !pBoundGroup )
            continue;

          std::cout << "Found BoundInstanceID " << object->header.BoundInstanceID << " to " << object->header.BaseId << "\n";
          std::cout << "\t " << pBoundGroup->AssetPath << "\n";

          if( auto pSgbFile = g_gameData->getFile( pBoundGroup->AssetPath ) )
          {
            auto sgbFile = SGB_FILE( pSgbFile->access_data_sections().at( 0 ).data() );
            int memberIdx = 0;

            for( auto& [ layerId, layers ] : sgbFile.layerInstanceObjects )
            {
              for( auto& instanceObject : layers )
              {
                if( instanceObject->getType() == CollisionBox )
                {
                  auto eobjLineIt = m_eventObjectStrings.find( instanceId );
                  if( eobjLineIt == m_eventObjectStrings.end() )
                    continue;

                  auto& eobjLine = eobjLineIt->second;

                  auto collisionBox = static_cast< CollisionBoxEntry* >( instanceObject.get() );
                  const char* shapeStr = "Unknown";

                  const auto parentScale = toVec3( object->header.Transformation.Scale );
                  const auto parentRotation = toVec3( object->header.Transformation.Rotation );
                  const auto parentTranslation = toVec3( object->header.Transformation.Translation );

                  const auto pos = applyTransform(
                    toVec3( collisionBox->header.Transformation.Translation ),
                    parentScale,
                    parentRotation,
                    parentTranslation );

                  switch( collisionBox->header.triggerBoxShape )
                  {
                    case TriggerBoxShapeBox:
                    {
                      shapeStr = "Box";
                      const auto rot = composeCollisionRotation( parentRotation, toVec3( collisionBox->header.Transformation.Rotation ) );
                      const auto box = scaleExtents( toVec3( collisionBox->header.Transformation.Scale ), parentScale );
                      eobjLine += "    pEObj->addCollisionBox( { " +
                                  std::to_string( pos.x ) + ", " + std::to_string( pos.y ) + ", " + std::to_string( pos.z ) + " }, " +
                                  std::to_string( rot ) + ", " +
                                  std::to_string( box.x ) + ", " + std::to_string( box.y ) + ", " + std::to_string( box.z ) + " );\n";
                    }
                    break;
                    case TriggerBoxShapeSphere:
                      shapeStr = "Sphere";
                      // todo:
                      // eobjLine += "    pEObj->addCollisionSphere( { " +
                      //             std::to_string( pos.x ) + ", " + std::to_string( pos.y ) + ", " + std::to_string( pos.z ) + " }, " +
                      //             std::to_string( radius ) + " );\n";
                      break;
                    case TriggerBoxShapeCylinder:
                      shapeStr = "Cylinder";
                      // todo:
                      // eobjLine += "    pEObj->addCollisionCylinder( { " +
                      //             std::to_string( pos.x ) + ", " + std::to_string( pos.y ) + ", " + std::to_string( pos.z ) + " }, " +
                      //             std::to_string( radius ) + ", " + std::to_string( height ) + " );\n"
                      break;
                    case TriggerBoxShapeBoard:
                      shapeStr = "Board";
                      break;
                    case TriggerBoxShapeMesh:
                      shapeStr = "Mesh";
                      break;
                    case TriggerBoxShapeBoardBothSides:
                      shapeStr = "Board Both Sides";
                      break;
                    default:
                      shapeStr = "Unknown";
                      break;
                  }
                  std::cout << "\t\t " << "- " << instanceObject->header.InstanceID << " CollisionBox Shape:" << shapeStr << "\n";
                }
              }
            }

            if( !sgbFile.timelines.empty() )
              std::cout << "\t\tTimelines: " << "\n";
            for( auto& timeline : sgbFile.timelines )
            {


              std::cout << "\t\t-- " << timeline.MemberID << " - " << sgbFile.timelineNames[ memberIdx ] << "\n";
              const char* collisionStateStr = "Unknown";
              switch( timeline.CollisionState )
              {
                case eTimelineCollisionState::NoChange:
                  collisionStateStr = "No Change";
                  break;
                case eTimelineCollisionState::On:
                  collisionStateStr = "On";
                  break;
                case eTimelineCollisionState::Off:
                  collisionStateStr = "Off";
                  break;
              }
              std::cout << "\t\t\t-- CollisionState:" << collisionStateStr << "\n";

              ++memberIdx;
            }
          }
        }
      }

      // append all strings to the main eobj string
      for( auto [ id, str ] : m_eventObjectStrings )
        eobjects += str + "\n";

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

      auto qb = g_exdData.getRow< Excel::QuestBattle >( entry.id );
      if( !qb )
        continue;

      std::string instruction;
      for( int i = 0; i < 100; ++i )
      {
        if( qb->getString( qb->data().Define[i].DefineName ).empty() )
          continue;
        instruction += "  static constexpr auto " + qb->getString( qb->data().Define[i].DefineName ) + " = " +
                       std::to_string( qb->data().Define[i].DefineValue ) + ";\n";
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
