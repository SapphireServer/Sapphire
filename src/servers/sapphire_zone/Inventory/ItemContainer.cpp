#include <common/Common.h>
#include <common/Logging/Logger.h>
#include <common/Database/DatabaseDef.h>

#include "Actor/Player.h"

#include "Item.h"
#include "Framework.h"
#include "Forwards.h"
#include "ItemContainer.h"

extern Core::Framework g_framework;

Core::ItemContainer::ItemContainer( uint16_t locationId ) : 
   m_id( locationId ),
   m_size( 25 )
{

}

Core::ItemContainer::~ItemContainer()
{

}

uint16_t Core::ItemContainer::getId() const
{
   return m_id;
}

uint8_t Core::ItemContainer::getEntryCount() const
{
   return static_cast< uint8_t >( m_itemMap.size() );
}

void Core::ItemContainer::removeItem( uint8_t slotId )
{
   ItemMap::iterator it = m_itemMap.find( slotId );

   if( it != m_itemMap.end() )
   {
      g_framework.getCharaDb().execute( "DELETE FROM charaglobalitem WHERE itemId = " + std::to_string( it->second->getUId() ) );

      m_itemMap.erase( it );

      g_framework.getLogger().debug( "Dropped item from slot " + std::to_string( slotId ) );
   }
   else
   {
      g_framework.getLogger().debug( "Item could not be dropped from slot " + std::to_string( slotId ) );
   }
}

Core::ItemMap & Core::ItemContainer::getItemMap()
{
   return m_itemMap;
}

const Core::ItemMap & Core::ItemContainer::getItemMap() const
{
   return m_itemMap;
}

int16_t Core::ItemContainer::getFreeSlot()
{
   for( uint8_t slotId = 0; slotId < m_size; slotId++ )
   {
      ItemMap::iterator it = m_itemMap.find( slotId );
      if( it == m_itemMap.end() ||
          it->second == nullptr )
         return slotId;
   }
   return -1;
}

Core::ItemPtr Core::ItemContainer::getItem( uint8_t slotId )
{

   if( ( slotId > m_size ) || ( slotId == -1 ) )
   {
      g_framework.getLogger().error( "Slot out of range " + std::to_string( slotId ) );
      return nullptr;
   }

   return m_itemMap[slotId];
}

void Core::ItemContainer::setItem( uint8_t slotId, ItemPtr pItem )
{
   if( ( slotId > m_size ) )
      return;

   m_itemMap[slotId] = pItem;
}
