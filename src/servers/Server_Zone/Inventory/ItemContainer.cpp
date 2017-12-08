#include "../Forwards.h"
#include "ItemContainer.h"

#include <Server_Common/Common.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Database/DatabaseDef.h>

#include "Actor/Player.h"

#include "Item.h"


extern Core::Logger g_log;

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
      g_charaDb.execute( "DELETE FROM charaglobalitem WHERE itemId = " + std::to_string( it->second->getUId() ) );

      m_itemMap.erase( it );

      g_log.debug( "Dropped item from slot " + std::to_string( slotId ) );
   }
   else
   {
      g_log.debug( "Item could not be dropped from slot " + std::to_string( slotId ) );
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
      g_log.error( "Slot out of range " + std::to_string( slotId ) );
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
