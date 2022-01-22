#include "InstanceObjectCache.h"
#include "Exd/ExdData.h"

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <Logging/Logger.h>
#include <Service.h>

Sapphire::InstanceObjectCache::InstanceObjectCache()
{

  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto idList = exdData.getIdList< Component::Excel::TerritoryType >();

  size_t count = 0;
  for( const auto& id : idList )
  {
    // show some loading indication...
    if( count++ % 10 == 0 )
      std::cout << ".";

    auto territoryType = exdData.getRow< Component::Excel::TerritoryType >( id );
    if( !territoryType )
      continue;

    auto path = territoryType->getString( territoryType->data().LVB );

    if( path.empty() )
      continue;

    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );

    // TODO: it does feel like this needs to be streamlined into the datReader instead of being done here...
    std::string bgLgbPath( path + "/level/bg.lgb" );
    std::string planmapLgbPath( path + "/level/planmap.lgb" );
    std::string planeventLgbPath( path + "/level/planevent.lgb" );
    std::vector< char > bgSection;
    std::vector< char > planmapSection;
    std::vector< char > planeventSection;

    std::unique_ptr< xiv::dat::File > bgFile;
    std::unique_ptr< xiv::dat::File > planmap_file;
    std::unique_ptr< xiv::dat::File > planevent_file;

    try
    {
      bgFile = exdData.getGameData()->getFile( bgLgbPath );
      planmap_file = exdData.getGameData()->getFile( planmapLgbPath );
      planevent_file = exdData.getGameData()->getFile( planeventLgbPath );
    }
    catch( std::runtime_error& )
    {
      // ignore files that aren't found
      continue;
    }

    bgSection = bgFile->access_data_sections().at( 0 );
    planmapSection = planmap_file->access_data_sections().at( 0 );
    planeventSection = planevent_file->access_data_sections().at( 0 );

    std::vector< std::string > stringList;

    uint32_t offset1 = 0x20;

    LGB_FILE bgLgb( &bgSection[ 0 ], "bg" );
    LGB_FILE planmapLgb( &planmapSection[ 0 ], "planmap" );
    LGB_FILE planeventLgb( &planeventSection[ 0 ], "planevent" );

    std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb, planeventLgb };
    uint32_t max_index = 0;

    for( const auto& lgb : lgbList )
    {
      for( const auto& group : lgb.groups )
      {
        for( const auto& pEntry : group.entries )
        {
          if( pEntry->getType() == LgbEntryType::MapRange )
          {
            auto pMapRange = std::reinterpret_pointer_cast< LGB_MAP_RANGE_ENTRY >( pEntry );
            m_mapRangeCache.insert( id, pMapRange );
          }
          else if( pEntry->getType() == LgbEntryType::ExitRange )
          {
            auto pExitRange = std::reinterpret_pointer_cast< LGB_EXIT_RANGE_ENTRY >( pEntry );
            m_exitRangeCache.insert( id, pExitRange );
          }
          else if( pEntry->getType() == LgbEntryType::PopRange )
          {
            auto pPopRange = std::reinterpret_pointer_cast< LGB_POP_RANGE_ENTRY >( pEntry );
            m_popRangeCache.insert( id, pPopRange );
          }
          else if( pEntry->getType() == LgbEntryType::SharedGroup6 )
          {

          }
        }
      }
    }
  }
  std::cout << "\n";

  Logger::debug(
    "InstanceObjectCache Cached: MapRange: {} ExitRange: {} PopRange: {}",
    m_mapRangeCache.size(), m_exitRangeCache.size(), m_popRangeCache.size()
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
  Sapphire::InstanceObjectCache::getPopRange( uint16_t zoneId, uint32_t popRangeId )
{
  return m_popRangeCache.get( zoneId, popRangeId );
}