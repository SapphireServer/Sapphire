#ifndef _ITEMCONTAINER_H_
#define _ITEMCONTAINER_H_

#include <map>

#include <Common.h>

#include "Forwards.h"

namespace Core
{

   typedef std::map< uint8_t, ItemPtr > ItemMap;

   class ItemContainer 
   {

   public:
      ItemContainer( uint16_t locationId );
      ~ItemContainer();

      uint16_t getId() const;

      uint8_t getEntryCount() const;

      void removeItem( uint8_t slotId );

      ItemMap& getItemMap();

      const ItemMap& getItemMap() const;

      ItemPtr getItem( uint8_t slotId );

      void setItem( uint8_t slotId, ItemPtr item );

      int16_t getFreeSlot();

   private:
      uint16_t m_id;
      uint8_t m_size;
      ItemMap m_itemMap;
      Entity::PlayerPtr m_pOwner;
   };

}

#endif
