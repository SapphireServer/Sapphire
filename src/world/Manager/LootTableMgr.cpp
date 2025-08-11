#include <iterator>
#include <fstream>
#include <filesystem>
#include <iostream>

#include <Common.h>
#include <Service.h>
#include <Logging/Logger.h>

#include "RNGMgr.h"
#include "LootTableMgr.h"

using namespace Sapphire;
using namespace Sapphire::World::Loot;
using namespace Sapphire::World::Manager;
namespace fs = std::filesystem;

bool LootTableMgr::cacheLootTables()
{
  std::fstream f;

  for( auto& p : fs::recursive_directory_iterator( "data/lootTables/" ) )
  {
    if( p.path().extension() == ".json" )
    {
      std::ifstream f( p.path() );
      if( !f )
        return false;

      nlohmann::json j;
      f >> j;

      LootTable lootTable = j.get< LootTable >();

      m_lootTableMap.try_emplace( lootTable.lootTable, std::make_shared< LootTable >( lootTable ) );
    }
  }

  return true;
}

LootTablePtr LootTableMgr::getLootTableByName( const std::string& name )
{
  auto it = m_lootTableMap.find( name );
  if( it == m_lootTableMap.end() )
    return nullptr;
  else
    return it->second;
}

LootTableResult LootTableMgr::rollLoot( const std::string& name )
{
  auto& RNGMgr = Common::Service< World::Manager::RNGMgr >::ref();

  LootTableResult result;

  if( auto pLootTable = getLootTableByName( name ); pLootTable )
  {
    Logger::info( "LootTableMgr: Rolling for " + name );
    result.name = pLootTable->lootTable;

    for( const auto& pool : pLootTable->pools )
    {
      if( !pool.enabled )
        continue;

      auto pickCountGen = RNGMgr.getRandGenerator< uint32_t >( pool.pick.min, pool.pick.max );
      uint32_t picks = pickCountGen.next();

      std::vector< LootTableItem > available = pool.items;

      for( auto i = 0; i < picks && !available.empty(); ++i )
      {
        const auto& item = pickWeightedItem( available );

        auto itemCountGen = RNGMgr.getRandGenerator< uint32_t >( item.quantity.min, item.quantity.max );
        uint32_t qty = itemCountGen.next();

        result.items.push_back( { item.id, qty, item.isHq } );

        if( !pool.duplicates )
        {
          available.erase( std::remove_if( available.begin(), available.end(),
                  [ & ]( const auto& x ) { return x.id == item.id; } ),
                  available.end() );
        }
      }
    }

    Logger::debug( "LootTableMgr: Rolled total of {0} item results", result.count() );
  }
    
  return result;
}

const LootTableItem& LootTableMgr::pickWeightedItem( const std::vector< LootTableItem >& items )
{
  auto& RNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
  // calc total weight
  uint32_t totalWeight = 0;
  for( const auto& it : items )
    totalWeight += it.weight;

  // roll for [1, totalWeight]
  auto randGen = RNGMgr.getRandGenerator< uint32_t >( 1, totalWeight );
  uint32_t roll = randGen.next();

  // get item pick
  uint32_t cumulative = 0;
  for( const auto& it : items )
  {
    cumulative += it.weight;
    if( roll <= cumulative )
      return it;
  }

  throw std::runtime_error( "LootTableMgr: pickWeightedItem roll exceeded total weight" );
}
