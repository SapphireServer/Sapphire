#include "InstanceObjectCache.h"
#include "Exd/ExdData.h"

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>

#include <algorithm>
#include <execution>

#include <Logging/Logger.h>
#include <Service.h>
#include <Util/UtilMath.h>

Sapphire::InstanceObjectCache::InstanceObjectCache()
{
  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto teriList = exdData.getRows< Excel::TerritoryType >();

  for( const auto& [ id, territoryType ] : teriList )
  {
    auto path = territoryType->getString( territoryType->data().LVB );

    if( path.empty() )
      continue;

    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );

    std::unique_ptr< xiv::dat::File > bgFile;
    std::unique_ptr< xiv::dat::File > planmap_file;
    std::unique_ptr< xiv::dat::File > planevent_file;
    std::unique_ptr< xiv::dat::File > planner_file;

    try
    {
      if( exdData.getGameData()->doesFileExist( path + "/level/bg.lgb" ) )
        bgFile = loadFile( path + "/level/bg.lgb" );
      else
        continue;

      planmap_file = loadFile( path + "/level/planmap.lgb" );
      planevent_file = loadFile( path + "/level/planevent.lgb" );
    } catch( std::runtime_error& )
    {
      continue;
    }

    std::vector< char > bgSection;
    bgSection.reserve( bgFile->access_data_sections().at( 0 ).size() );
    bgSection.assign( bgFile->access_data_sections().at( 0 ).begin(), bgFile->access_data_sections().at( 0 ).end() );

    std::vector< char > planmapSection;
    planmapSection.reserve( planmap_file->access_data_sections().at( 0 ).size() );
    planmapSection.assign( planmap_file->access_data_sections().at( 0 ).begin(), planmap_file->access_data_sections().at( 0 ).end() );

    std::vector< char > planeventSection;
    planeventSection.reserve( planevent_file->access_data_sections().at( 0 ).size() );
    planeventSection.assign( planevent_file->access_data_sections().at( 0 ).begin(), planevent_file->access_data_sections().at( 0 ).end() );


    LGB_FILE bgLgb( bgSection.data(), "bg" );
    LGB_FILE planmapLgb( planmapSection.data(), "planmap" );
    LGB_FILE planeventLgb( planeventSection.data(), "planevent" );

    std::vector< LGB_FILE > lgbList;

    try
    {
      planner_file = loadFile( path + "/level/planner.lgb" );

      std::vector< char > plannerSection;
      plannerSection.reserve( planner_file->access_data_sections().at( 0 ).size() );
      plannerSection.assign( planner_file->access_data_sections().at( 0 ).begin(), planner_file->access_data_sections().at( 0 ).end() );

      LGB_FILE plannerLgb( plannerSection.data(), "planner" );

      lgbList.reserve( 4 );
      lgbList.emplace_back( bgLgb );
      lgbList.emplace_back( planmapLgb );
      lgbList.emplace_back( planeventLgb );
      lgbList.emplace_back( plannerLgb );
    } catch( std::runtime_error& )
    {
      lgbList.reserve( 3 );
      lgbList.emplace_back( bgLgb );
      lgbList.emplace_back( planmapLgb );
      lgbList.emplace_back( planeventLgb );
    }

    for( const auto& lgb : lgbList )
    {
      for( const auto& group : lgb.groups )
      {
        for( const auto& pEntry : group.entries )
        {
          switch( pEntry->getType() )
          {
            case LgbEntryType::MapRange:
            {
              auto pMapRange = std::reinterpret_pointer_cast< LGB_MAP_RANGE_ENTRY >( pEntry );
              m_mapRangeCache.insert( id, pMapRange );

              break;
            }
            case LgbEntryType::ExitRange:
            {
              auto pExitRange = std::reinterpret_pointer_cast< LGB_EXIT_RANGE_ENTRY >( pEntry );
              m_exitRangeCache.insert( id, pExitRange );

              break;
            }
            case LgbEntryType::PopRange:
            {
              auto pPopRange = std::reinterpret_pointer_cast< LGB_POP_RANGE_ENTRY >( pEntry );
              m_popRangeCache.insert( id, pPopRange );
              break;
            }
            case LgbEntryType::CollisionBox:
            {
              break;
            }
            case LgbEntryType::EventObject:
            {
              auto pEObj = std::reinterpret_pointer_cast< LGB_EOBJ_ENTRY >( pEntry );
              m_eobjCache.insert( id, pEObj );
              break;
            }
            case LgbEntryType::EventNpc:
            {
              auto pENpc = std::reinterpret_pointer_cast< LGB_ENPC_ENTRY >( pEntry );
              m_enpcCache.insert( id, pENpc );
              break;
            }
            case LgbEntryType::EventRange:
            {
              auto pEventRange = std::reinterpret_pointer_cast< LGB_EVENT_RANGE_ENTRY >( pEntry );
              m_eventRangeCache.insert( 0, pEventRange );
              break;
            }
          }
        }
      }
    }
  }

  Logger::debug(
          "InstanceObjectCache Cached: MapRange: {} ExitRange: {} PopRange: {} EventObj: {} EventNpc: {} EventRange: {}",
          m_mapRangeCache.size(), m_exitRangeCache.size(), m_popRangeCache.size(), m_eobjCache.size(), m_enpcCache.size(),
          m_eventRangeCache.size() );
}

std::unique_ptr< xiv::dat::File > Sapphire::InstanceObjectCache::loadFile( const std::string& filePath ) const
{
  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  if( exdData.getGameData()->doesFileExist( filePath ) )
    return exdData.getGameData()->getFile( filePath );

  throw std::runtime_error( "File not found: " + filePath );
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

  popInfo->m_pos = Common::FFXIVARR_POSITION3 { popRange->header.transform.translation.x,
                                               popRange->header.transform.translation.y,
                                               popRange->header.transform.translation.z };

  auto targetRot = Common::FFXIVARR_POSITION3 { popRange->header.transform.rotation.x,
                                                popRange->header.transform.rotation.y,
                                                popRange->header.transform.rotation.z };

  popInfo->m_rotation = Common::Util::eulerToDirection( targetRot );

  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto levelData = exdData.getRow< Excel::Level >( popRangeId );
  if( levelData )
    popInfo->m_territoryTypeId = levelData->data().TerritoryType;

  return popInfo;
}
