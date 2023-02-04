#pragma once

#include <map>
#include <Common.h>
#include "ForwardsZone.h"

namespace Sapphire
{

  using ItemMap = std::map< uint16_t, ItemPtr >;

  class ItemContainer
  {

  public:
    ItemContainer( uint16_t storageId, uint16_t maxSize, const std::string& tableName, bool isMultiStorage,
                   bool isPersistentStorage = true );

    ~ItemContainer();

    uint16_t getId() const;

    uint16_t getEntryCount() const;

    void removeItem( uint16_t slotId, bool removeFromDb = true );

    ItemMap& getItemMap();

    const ItemMap& getItemMap() const;

    ItemPtr getItem( uint16_t slotId );

    void setItem( uint16_t slotId, ItemPtr item );

    int16_t getFreeSlot();

    uint16_t getMaxSize() const;

    std::string getTableName() const;

    bool isMultiStorage() const;

    bool isPersistentStorage() const;

  private:
    uint16_t m_id;
    uint16_t m_size;
    std::string m_tableName;
    bool m_bMultiStorage;
    bool m_isPersistentStorage;
    ItemMap m_itemMap;
    Entity::PlayerPtr m_pOwner;
  };

}