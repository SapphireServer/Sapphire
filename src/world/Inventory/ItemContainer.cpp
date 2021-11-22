#include <Common.h>
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>
#include <Service.h>

#include "Actor/Player.h"

#include "Item.h"
#include "Forwards.h"
#include "ItemContainer.h"

Sapphire::ItemContainer::ItemContainer( uint16_t storageId, uint8_t maxSize, const std::string& tableName,
                                        bool isMultiStorage, bool isPersistentStorage ) :
  m_id( storageId ),
  m_size( maxSize ),
  m_tableName( tableName ),
  m_bMultiStorage( isMultiStorage ),
  m_isPersistentStorage( isPersistentStorage )
{

}

Sapphire::ItemContainer::~ItemContainer()
{

}

uint16_t Sapphire::ItemContainer::getId() const
{
  return m_id;
}

uint8_t Sapphire::ItemContainer::getEntryCount() const
{
  return static_cast< uint8_t >( m_itemMap.size() );
}

void Sapphire::ItemContainer::removeItem( uint8_t slotId, bool removeFromDb )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto it = m_itemMap.find( slotId );

  if( it != m_itemMap.end() )
  {
    if( m_isPersistentStorage && removeFromDb )
      db.execute( "DELETE FROM charaglobalitem WHERE itemId = " + std::to_string( it->second->getUId() ) );

    m_itemMap.erase( it );

    Logger::debug( "Dropped item from slot {0}", slotId );
  }
  else
  {
    Logger::debug( "Item could not be dropped from slot {0}", slotId );
  }
}

Sapphire::ItemMap& Sapphire::ItemContainer::getItemMap()
{
  return m_itemMap;
}

const Sapphire::ItemMap& Sapphire::ItemContainer::getItemMap() const
{
  return m_itemMap;
}

int8_t Sapphire::ItemContainer::getFreeSlot()
{
  for( uint16_t slotId = 0; slotId < m_size; slotId++ )
  {
    ItemMap::iterator it = m_itemMap.find( slotId );
    if( it == m_itemMap.end() ||
        it->second == nullptr )
      return slotId;
  }
  return -1;
}

Sapphire::ItemPtr Sapphire::ItemContainer::getItem( uint8_t slotId )
{

  if( ( slotId > m_size ) )
  {
    Logger::error( "Slot out of range {0}", slotId );
    return nullptr;
  }

  return m_itemMap[ slotId ];
}

void Sapphire::ItemContainer::setItem( uint8_t slotId, ItemPtr pItem )
{
  if( slotId > m_size )
  {
    Logger::error( "Slot out of range {0}", slotId );
    return;
  }

  m_itemMap[ slotId ] = pItem;
}

uint8_t Sapphire::ItemContainer::getMaxSize() const
{
  return m_size;
}

std::string Sapphire::ItemContainer::getTableName() const
{
  return m_tableName;
}

bool Sapphire::ItemContainer::isMultiStorage() const
{
  return m_bMultiStorage;
}

bool Sapphire::ItemContainer::isPersistentStorage() const
{
  return m_isPersistentStorage;
}


