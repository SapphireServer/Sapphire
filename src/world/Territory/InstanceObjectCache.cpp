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
      case eAssetType::SharedGroup:
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
    // probably add a LVB parser and use that to build the file list. for now this will do
    std::string bgLgbPath( path + "/level/bg.lgb" );
    std::string planmapLgbPath( path + "/level/planmap.lgb" );
    std::string planeventLgbPath( path + "/level/planevent.lgb" );
    std::string plannerLgbPath( path + "/level/planner.lgb" );
    std::string vfxLgbPath( path + "/level/vfx.lgb" );

    std::map< std::string, LGB_FILE* > lgbFileMap =
    {
      { bgLgbPath, nullptr },
      { planmapLgbPath, nullptr },
      { planeventLgbPath, nullptr },
      { plannerLgbPath, nullptr },
      { vfxLgbPath, nullptr }
    };

    for( auto& [ path, pLgbFile ] : lgbFileMap )
    {
      try
      {
        auto pFile = exdData.getGameData()->getFile( path );

        if( pFile )
        {
          auto section = pFile->get_data_sections().at( 0 );
          pLgbFile = new LGB_FILE( &section[ 0 ], &lgbAssetFilter );
        }
      }
      catch( std::runtime_error& e )
      {
        Logger::trace( "[InstanceObjectCache] Failed to load file for Zone: {} LGB File: {} Error: {}", id, path, e.what() );
      }
    }

    for( const auto& [ path, lgb ] : lgbFileMap )
    {
      if( !lgb )
        continue;

      for( const auto& group : lgb->groups )
      {
        for( const auto& pEntry : group.entries )
        {
          switch( pEntry->getType() )
          {
            case eAssetType::SharedGroup:
            {
              auto pSharedGroup = std::reinterpret_pointer_cast< SharedGroupEntry >( pEntry );
              m_sharedGroupCache.insert( 0, pSharedGroup );
              m_sharedGroupCache.insert( id, pSharedGroup );
            }
            break;
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
            default:
              break;
          }
        }
      }
    }

    // free up any LGB files as we dont need them anymore
    for( auto& [ path, pLgb ] : lgbFileMap )
      if( pLgb )
        delete pLgb;
  }

  Logger::info(
    "InstanceObjectCache: scanned {} territories, parsed {} with scene data in {}ms",
    scannedTerritoryCount,
    parsedTerritoryCount,
    Common::Util::getTimeMs() - startMs );

  Logger::debug(
    "InstanceObjectCache Cached: MapRange: {} ExitRange: {} PopRange: {} EventObj: {} EventNpc: {} EventRange: {} SharedGroup: {}",
    m_mapRangeCache.size(), m_exitRangeCache.size(), m_popRangeCache.size(), m_eobjCache.size(), m_enpcCache.size(), m_eventRangeCache.size(), m_sharedGroupCache.size()
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

Sapphire::InstanceObjectCache::SharedGroupMapPtr Sapphire::InstanceObjectCache::getAllSharedGroups( uint16_t zoneId )
{
  return m_sharedGroupCache.getAll( zoneId );
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

Sapphire::InstanceObjectCache::SharedGroupPtr Sapphire::InstanceObjectCache::getSharedGroup( uint16_t zoneId, uint32_t instanceId )
{
  return m_sharedGroupCache.get( zoneId, instanceId );
}