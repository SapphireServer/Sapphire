#ifndef INVENTORY_H_
#define INVENTORY_H_
#include <map>
#include <Common.h>
#include "Forwards.h"

namespace Core
{

class ItemContainer;

using InventoryMap = std::map< uint16_t, ItemContainerPtr >;
class Inventory
{
public:
   Inventory( Entity::Player* pOwner );
   ~Inventory();

   using InvSlotPair = std::pair< uint16_t, int8_t >;
   typedef std::vector< InvSlotPair > InvSlotPairVec;

   InvSlotPairVec getSlotsOfItemsInInventory( uint32_t catalogId );
   InvSlotPair getFreeBagSlot();
   int16_t addItem( uint16_t inventoryId, int8_t slotId, uint32_t catalogId, uint16_t quantity = 1, bool isHq = false, bool silent = false );
   void moveItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot );
   void swapItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot );
   void discardItem( uint16_t fromInventoryId, uint8_t fromSlotId );
   void splitItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot, uint16_t splitCount );
   void mergeItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot );

   ItemPtr createItem( uint32_t catalogId, uint16_t quantity = 1 );

   ItemPtr loadItem( uint64_t uId );

   ItemPtr getItemAt( uint16_t containerId, uint8_t slotId );

   bool updateContainer( uint16_t containerId, uint8_t slotId, ItemPtr pItem );

   /*! heck if weapon category qualifies the weapon as onehanded */
   bool isOneHandedWeapon( Common::ItemUICategory weaponCategory );
   /*! calculate and return player ilvl based off equipped gear */
   uint16_t calculateEquippedGearItemLevel();
   /*! return the current amount of currency of type */
   uint32_t getCurrency( Common::CurrencyType type );
   /*! add amount to the current of type */
   bool addCurrency( Common::CurrencyType type, uint32_t amount );
   /*! remove amount from the currency of type */
   bool removeCurrency( Common::CurrencyType type, uint32_t amount );

   void updateCurrencyDb();
   void updateBagDb( Common::InventoryType type );
   void updateMannequinDb( Common::InventoryType type );
   void updateItemDb( ItemPtr pItem ) const;
   void deleteItemDb( ItemPtr pItem ) const;

   bool isArmory( uint16_t containerId );
   bool isEquipment( uint16_t containerId );
   uint16_t getArmoryToEquipSlot( uint8_t slotId );

   /*! return the crystal amount of currency of type */
   uint32_t getCrystal( Common::CrystalType type );
   /*! add amount to the crystal of type */
   bool addCrystal( Common::CrystalType type, uint32_t amount );
   /*! remove amount from the crystals of type */
   bool removeCrystal( Common::CrystalType type, uint32_t amount );
   bool isObtainable( uint32_t catalogId, uint8_t quantity );

   void updateCrystalDb();

   bool load();

   void send();

   uint8_t getFreeSlotsInBags();

   Common::ContainerType getContainerType( uint32_t containerId );

   uint32_t getNextUId();


private:
   Entity::Player* m_pOwner;
   InventoryMap m_inventoryMap;
   const uint32_t m_maxSlotSize = 999;
};

}
#endif
