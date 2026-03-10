#include "InstanceObjectCache.h"
#include "Exd/ExdData.h"

#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <algorithm>
#include <execution>

#include <Logging/Logger.h>
#include <Service.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>

#include "DatCategories/DatCommon.h"
#include "datReader/DatCategories/bg/lgb.h"

Sapphire::InstanceObjectCache::InstanceObjectCache()
{
  const auto startMs = Common::Util::getTimeMs();

  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto teriList = exdData.getRows< Excel::TerritoryType >();
  LGB_FILE::AssetTypeFilter lgbAssetFilter = []( eAssetType type )
  {
    switch( type )
    {
      case eAssetType::MapRange:
      case eAssetType::ExitRange:
      case eAssetType::PopRange:
      case eAssetType::EventObject:
      case eAssetType::EventNPC:
      case eAssetType::EventRange:
        return true;
      default:
        return false;
    }
  };

  size_t scannedTerritoryCount = 0;
  size_t parsedTerritoryCount = 0;
  for( const auto& [ id, territoryType ] : teriList ) {
    ++scannedTerritoryCount;

    auto path = territoryType->getString( territoryType->data().LVB );

    if( path.empty() )
      continue;

    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );

    // TODO: it does feel like this needs to be streamlined into the datReader instead of being done here...
    std::string bgLgbPath( path + "/level/bg.lgb" );
    std::string planmapLgbPath( path + "/level/planmap.lgb" );
    std::string planeventLgbPath( path + "/level/planevent.lgb" );
    std::string plannerLgbPath( path + "/level/planner.lgb" );
    std::vector< char > bgSection;
    std::vector< char > planmapSection;
    std::vector< char > planeventSection;
    std::vector< char > plannerSection;

    std::unique_ptr< xiv::dat::File > bgFile;
    std::unique_ptr< xiv::dat::File > planmap_file;
    std::unique_ptr< xiv::dat::File > planevent_file;
    std::unique_ptr< xiv::dat::File > planner_file;

    try
    {
      if( exdData.getGameData()->doesFileExist( bgLgbPath ) )
        bgFile = exdData.getGameData()->getFile( bgLgbPath );
      else
        continue;

      if( !exdData.getGameData()->doesFileExist( planmapLgbPath ) ||
          !exdData.getGameData()->doesFileExist( planeventLgbPath ) )
        continue;

      planmap_file = exdData.getGameData()->getFile( planmapLgbPath );
      planevent_file = exdData.getGameData()->getFile( planeventLgbPath );
    }
    catch( std::runtime_error& )
    {
      // ignore files that aren't found
      continue;
    }

    ++parsedTerritoryCount;

    bgSection = bgFile->access_data_sections().at( 0 );
    planmapSection = planmap_file->access_data_sections().at( 0 );
    planeventSection = planevent_file->access_data_sections().at( 0 );

    LGB_FILE bgLgb( &bgSection[ 0 ], "bg", &lgbAssetFilter );
    LGB_FILE planmapLgb( &planmapSection[ 0 ], "planmap", &lgbAssetFilter );
    LGB_FILE planeventLgb( &planeventSection[ 0 ], "planevent", &lgbAssetFilter );

    std::vector< const LGB_FILE* > lgbList;

    try
    {
      if( exdData.getGameData()->doesFileExist( plannerLgbPath ) )
      {
        planner_file = exdData.getGameData()->getFile( plannerLgbPath );
        plannerSection = planner_file->access_data_sections().at( 0 );
        LGB_FILE plannerLgb( &plannerSection[ 0 ], "planner", &lgbAssetFilter );

        lgbList = { &bgLgb, &planmapLgb, &planeventLgb, &plannerLgb };

        for( const auto* lgb : lgbList )
        {
          for( const auto& group : lgb->groups )
          {
            for( const auto& pEntry : group.entries )
            {
              switch( pEntry->getType() )
              {
                case eAssetType::MapRange:
                {
                  auto pMapRange = std::reinterpret_pointer_cast< MapRangeEntry >( pEntry );
                  m_mapRangeCache.insert( id, pMapRange );

                  break;
                }
                case eAssetType::ExitRange:
                {
                  auto pExitRange = std::reinterpret_pointer_cast< ExitRangeEntry >( pEntry );
                  m_exitRangeCache.insert( id, pExitRange );

                  break;
                }
                case eAssetType::PopRange:
                {
                  auto pPopRange = std::reinterpret_pointer_cast< PopRangeEntry >( pEntry );
                  m_popRangeCache.insert( id, pPopRange );
                  break;
                }
                case eAssetType::CollisionBox:
                {
                  break;
                }
                case eAssetType::EventObject:
                {
                  auto pEObj = std::reinterpret_pointer_cast< EventObjectEntry >( pEntry );
                  m_eobjCache.insert( 0, pEObj );
                  m_eobjBaseInstanceMap.emplace( std::make_pair( id, pEObj->header.BaseId ), pEObj->header.InstanceID );
                  break;
                }
                case eAssetType::EventNPC:
                {
                  auto pENpc = std::reinterpret_pointer_cast< EventNPCEntry >( pEntry );
                  m_enpcCache.insert( id, pENpc );
                  break;
                }
                case eAssetType::EventRange:
                {
                  auto pEventRange = std::reinterpret_pointer_cast< EventRangeEntry >( pEntry );
                  m_eventRangeCache.insert( 0, pEventRange );
                  break;
                }
              }
            }
          }
        }

        continue;
      }

      lgbList = { &bgLgb, &planmapLgb, &planeventLgb };
    }
    catch( std::runtime_error& )
    {
      lgbList = { &bgLgb, &planmapLgb, &planeventLgb };
    }

    for( const auto* lgb : lgbList )
    {
      for( const auto& group : lgb->groups )
      {
        for( const auto& pEntry : group.entries )
        {
          switch( pEntry->getType() )
          {
            case eAssetType::MapRange:
            {
              auto pMapRange = std::reinterpret_pointer_cast< MapRangeEntry >( pEntry );
              m_mapRangeCache.insert( id, pMapRange );

              break;
            }
            case eAssetType::ExitRange:
            {
              auto pExitRange = std::reinterpret_pointer_cast< ExitRangeEntry >( pEntry );
              m_exitRangeCache.insert( id, pExitRange );

              break;
            }
            case eAssetType::PopRange:
            {
              auto pPopRange = std::reinterpret_pointer_cast< PopRangeEntry >( pEntry );
              m_popRangeCache.insert( id, pPopRange );
              break;
            }
            case eAssetType::CollisionBox:
            {
              //auto pEObj = std::reinterpret_pointer_cast< LGB_ENPC_ENTRY >( pEntry );

              //Logger::debug( "CollisionBox {}", pEntry->header.nameOffset );
              break;
            }
            case eAssetType::EventObject:
            {
              auto pEObj = std::reinterpret_pointer_cast< EventObjectEntry >( pEntry );
              m_eobjCache.insert( 0, pEObj );
              m_eobjBaseInstanceMap.emplace( std::make_pair( id, pEObj->header.BaseId ), pEObj->header.InstanceID );
              break;
            }
            case eAssetType::EventNPC:
            {
              auto pENpc = std::reinterpret_pointer_cast< EventNPCEntry >( pEntry );
              m_enpcCache.insert( id, pENpc );
              break;
            }
            case eAssetType::EventRange:
            {
              auto pEventRange = std::reinterpret_pointer_cast< EventRangeEntry >( pEntry );
              m_eventRangeCache.insert( 0, pEventRange );
              break;
            }
          }
        }
      }
    }
  }

  Logger::info(
    "InstanceObjectCache: scanned {} territories, parsed {} with scene data in {}ms",
    scannedTerritoryCount,
    parsedTerritoryCount,
    Common::Util::getTimeMs() - startMs );

  Logger::debug(
    "InstanceObjectCache Cached: MapRange: {} ExitRange: {} PopRange: {} EventObj: {} EventNpc: {} EventRange: {}",
    m_mapRangeCache.size(), m_exitRangeCache.size(), m_popRangeCache.size(), m_eobjCache.size(), m_enpcCache.size(), m_eventRangeCache.size()
  );
}


Sapphire::InstanceObjectCache::MapRangePtr
  Sapphire::InstanceObjectCache::getMapRange( uint16_t zoneId, uint32_t mapRangeId )
{
  return m_mapRangeCache.get( zoneId, mapRangeId );
}

Sapphire::InstanceObjectCache::ExitRangePtr
  Sapphire::InstanceObjectCache::getExitRange( uint16_t zoneId, uint32_t exitRangeId )
{
  return m_exitRangeCache.get( zoneId, exitRangeId );
}

Sapphire::InstanceObjectCache::PopRangePtr
  Sapphire::InstanceObjectCache::getPopRange( uint32_t popRangeId )
{
  return m_popRangeCache.get( 0, popRangeId );
}

Sapphire::InstanceObjectCache::EObjPtr
  Sapphire::InstanceObjectCache::getEObj( uint32_t eObjId )
{
  return m_eobjCache.get( 0, eObjId );
}

Sapphire::InstanceObjectCache::EObjPtr
Sapphire::InstanceObjectCache::getEObjByBaseId( uint16_t zoneId, uint32_t baseId )
{
  auto find = std::make_pair( zoneId, baseId );
  auto it = m_eobjBaseInstanceMap.find( find );
  if( it != m_eobjBaseInstanceMap.end() )
    return getEObj( it->second );
  return nullptr;
}

Sapphire::InstanceObjectCache::ENpcPtr
  Sapphire::InstanceObjectCache::getENpc( uint32_t eNpcId )
{
  return m_enpcCache.get( 0, eNpcId );
}

Sapphire::InstanceObjectCache::EObjMapPtr
  Sapphire::InstanceObjectCache::getAllEObj( uint16_t zoneId )
{
  return m_eobjCache.getAll( zoneId );
}

Sapphire::InstanceObjectCache::ENpcMapPtr
  Sapphire::InstanceObjectCache::getAllENpc( uint16_t zoneId )
{
  return m_enpcCache.getAll( zoneId );
}

Sapphire::InstanceObjectCache::EventRangePtr Sapphire::InstanceObjectCache::getEventRange( uint32_t eventRangeId )
{
  return m_eventRangeCache.get( 0, eventRangeId );
}

std::shared_ptr< Sapphire::InstanceObjectCache::PopRangeInfo > Sapphire::InstanceObjectCache::getPopRangeInfo( uint32_t popRangeId )
{
  auto popRange = getPopRange( popRangeId );
  if( !popRange )
    return nullptr;

  auto popInfo = std::make_shared< Sapphire::InstanceObjectCache::PopRangeInfo >();

  popInfo->m_pos = Common::Vector3 { popRange->header.Transformation.Translation.x,
                                                popRange->header.Transformation.Translation.y,
                                                popRange->header.Transformation.Translation.z };

  auto targetRot = Common::Vector3 { popRange->header.Transformation.Rotation.x,
                                                popRange->header.Transformation.Rotation.y,
                                                popRange->header.Transformation.Rotation.z };

  popInfo->m_rotation = Common::Util::eulerToDirection( targetRot );

  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto levelData = exdData.getRow< Excel::Level >( popRangeId );
  if( levelData )
    popInfo->m_territoryTypeId = levelData->data().TerritoryType;

  return popInfo;
}
