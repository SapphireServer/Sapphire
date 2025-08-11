#pragma once

#include <memory>
#include <map>
#include <vector>
#include "ForwardsZone.h"

#include <nlohmann/json.hpp>

namespace Sapphire::World::Loot
{
  struct LootTableItem {
    uint32_t id;
    uint32_t weight;
    bool isHq;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE( LootTableItem, id, weight, isHq )
  };

  struct LootTablePool {
    std::string name;
    bool enabled;
    bool duplicates;
    uint32_t pickMin;
    uint32_t pickMax;
    std::vector< LootTableItem > items;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE( LootTablePool, name, enabled, duplicates, pickMin, pickMax, items )
  };

  struct LootTable {
    std::string lootTable;
    std::vector< LootTablePool > pools;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE( LootTable, lootTable, pools )
  };

  struct LootTableResultItem {
    uint32_t id;
    uint32_t quantity;
    bool isHq;
  };

  struct LootTableResult {
    std::string name;
    std::vector< LootTableResultItem > items;

    bool isEmpty() const { return items.empty(); }
    size_t count() const { return items.size(); }
  };

  using LootTablePtr = std::shared_ptr< LootTable >;
}


namespace Sapphire::World::Manager
{

  class LootTableMgr
  {
  public:
    LootTableMgr() = default;
    ~LootTableMgr() = default;

    /// <summary>
    /// initialize loot tables from JSON into a map
    /// </summary>
    bool cacheLootTables();

    /// <summary>
    /// returns LootTable ptr by its name
    /// </summary>
    /// <param name="name"></param>
    /// <returns>ptr to LootTable or null</returns>
    Loot::LootTablePtr getLootTableByName( const std::string& name );

    /// <summary>
    /// rolls a given loot table by name
    /// internally processes given pools and items
    /// returns a LootTableStruct with resolved loot table results
    /// may throw if loot table is not found
    /// </summary>
    /// <param name="name"></param>
    /// <returns>struct of loot table rolls</returns>
    Loot::LootTableResult rollLoot( const std::string& name );

  private:
    std::map< std::string, Loot::LootTablePtr > m_lootTableMap;

    /// <summary>
    /// picks a single item per weight out of a total weight of vector of items
    /// uses weighted system and RNGMgr to select a roll
    /// may throw if roll > total weight
    /// </summary>
    /// <param name="items"></param>
    /// <returns>singular item pick from given items</returns>
    const Loot::LootTableItem& pickWeightedItem( const std::vector< Loot::LootTableItem >& items );
  };

}
