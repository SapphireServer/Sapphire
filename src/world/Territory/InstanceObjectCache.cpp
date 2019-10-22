#include "InstanceObjectCache.h"
#include "Exd/ExdDataGenerated.h"
#include <Framework.h>

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

Sapphire::InstanceObjectCache::InstanceObjectCache( std::shared_ptr< Framework > pFramework ) :
  m_pFramework( pFramework )
{

  auto pExd = pFramework->get< Sapphire::Data::ExdDataGenerated >();
  auto idList = pExd->getTerritoryTypeIdList();

  size_t count = 0;
  for( const auto& id : idList )
  {
    // show some loading indication...
    if( count++ % 10 == 0 )
      std::cout << ".";

    auto territoryType = pExd->get< Sapphire::Data::TerritoryType >( id );
    if( !territoryType )
      continue;

    auto path = territoryType->bg;

    if( path.empty() )
      continue;

    // TODO: Horrible workaround... Fails if expansion is not installed
    if( path.find( "ex3" ) != std::string::npos )
      continue;

    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );

    // TODO: it does feel like this needs to be streamlined into the datReader instead of being done here...
    std::string bgLgbPath( path + "/level/bg.lgb" );
    std::string planmapLgbPath( path + "/level/planmap.lgb" );
    std::vector< char > bgSection;
    std::vector< char > planmapSection;

    auto test_file = pExd->getGameData()->getFile( bgLgbPath );
    bgSection = test_file->access_data_sections().at( 0 );

    auto planmap_file = pExd->getGameData()->getFile( planmapLgbPath );
    planmapSection = planmap_file->access_data_sections().at( 0 );

    std::vector< std::string > stringList;

    uint32_t offset1 = 0x20;

    LGB_FILE bgLgb( &bgSection[ 0 ], "bg" );
    LGB_FILE planmapLgb( &planmapSection[ 0 ], "planmap" );

    std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb };
    uint32_t max_index = 0;

    for( const auto& lgb : lgbList )
    {
      for( const auto& group : lgb.groups )
      {
        for( const auto& pEntry : group.entries )
        {
          if( pEntry->getType() == LgbEntryType::MapRange )
          {
            auto pMapRange = reinterpret_cast< LGB_MAP_RANGE_ENTRY* >( pEntry.get() );
            m_mapRangeCache.insert( id, *pMapRange );
          }
          else if( pEntry->getType() == LgbEntryType::ExitRange )
          {
            auto pExitRange = reinterpret_cast< LGB_EXIT_RANGE_ENTRY* >( pEntry.get() );
            m_exitRangeCache.insert( id, *pExitRange);
          }
          else if( pEntry->getType() == LgbEntryType::PopRange )
          {
            auto pPopRange = reinterpret_cast< LGB_POP_RANGE_ENTRY* >( pEntry.get() );
            m_popRangeCache.insert( id, *pPopRange );
          }
        }
      }
    }
  }
  std::cout << "\n";
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