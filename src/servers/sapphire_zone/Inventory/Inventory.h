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

   enum ContainerType : uint16_t
   {
      Unknown = 0,
      Bag = 1,
      GearSet = 2,
      CurrencyCrystal = 3,
      Armory = 4
   };

   enum InventoryType : uint16_t
   {
      Bag0 = 0,
      Bag1 = 1,
      Bag2 = 2,
      Bag3 = 3,

      GearSet0 = 1000,
      GearSet1 = 1001,

      Currency = 2000,
      Crystal = 2001,
      //UNKNOWN_0 = 2003,
      KeyItem = 2004,
      DamagedGear = 2007,
      //UNKNOWN_1 = 2008,

      ArmoryOff = 3200,
      ArmoryHead = 3201,
      ArmoryBody = 3202,
      ArmoryHand = 3203,
      ArmoryWaist = 3204,
      ArmoryLegs = 3205,
      ArmoryFeet = 3206,
      ArmotyNeck = 3207,
      ArmoryEar = 3208,
      ArmoryWrist = 3209,
      ArmoryRing = 3300,

      ArmorySoulCrystal = 3400,
      ArmoryMain = 3500,

      RetainerBag0 = 10000,
      RetainerBag1 = 10001,
      RetainerBag2 = 10002,
      RetainerBag3 = 10003,
      RetainerBag4 = 10004,
      RetainerBag5 = 10005,
      RetainerBag6 = 10006,
      RetainerEquippedGear = 11000,
      RetainerGil = 12000,
      RetainerCrystal = 12001,
      RetainerMarket = 12002,

      FreeCompanyBag0 = 20000,
      FreeCompanyBag1 = 20001,
      FreeCompanyBag2 = 20002,
      FreeCompanyGil = 22000,
      FreeCompanyCrystal = 22001
   };

   enum CurrencyType : uint8_t
   {
      Gil = 0x01,
      StormSeal = 0x02,
      SerpentSeal = 0x03,
      FlameSeal = 0x04,
      TomestonePhilo = 0x05,
      TomestoneMytho = 0x06,
      WolfMark = 0x07,
      TomestoneSold = 0x08,
      AlliedSeal = 0x09,
      TomestonePoet = 0x0A,
      Mgp = 0x0B,
      TomestoneLaw = 0x0C,
      TomestoneEso = 0x0D,
      TomestoneLore = 0x0E
   };

   enum CrystalType : uint8_t
   {
      FireShard = 0x01,
      IceShard = 0x02,
      WindShard = 0x03,
      EarthShard = 0x04,
      LightningShard = 0x05,
      WaterShard = 0x06,

      FireCrystal = 0x07,
      IceCrystal = 0x08,
      WindCrystal = 0x09,
      EarthCrystal = 0x0A,
      LightningCrystal = 0x0B,
      WaterCrystal = 0x0C,

      FireCluster = 0x0D,
      IceCluster = 0x0E,
      WindCluster = 0x0F,
      EarthCluster = 0x10,
      LightningCluster = 0x11,
      WaterCluster = 0x12
   };

   enum EquipSlot : uint8_t
   {
      MainHand = 0,
      OffHand = 1,
      Head = 2,
      Body = 3,
      Hands = 4,
      Waist = 5,
      Legs = 6,
      Feet = 7,
      Neck = 8,
      Ear = 9,
      Wrist = 10,
      Ring1 = 11,
      Ring2 = 12,
      SoulCrystal = 13,
   };
   using InvSlotPair = std::pair< uint16_t, int8_t >;
   typedef std::vector< InvSlotPair > InvSlotPairVec;

   InvSlotPairVec getSlotsOfItemsInInventory( uint32_t catalogId );
   InvSlotPair getFreeBagSlot();
   int16_t addItem( uint16_t inventoryId, int8_t slotId, uint32_t catalogId, uint8_t quantity = 1 );
   void moveItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot );
   void swapItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot );
   void discardItem( uint16_t fromInventoryId, uint8_t fromSlotId );

   ItemPtr createItem( uint32_t catalogId, uint8_t quantity = 1 );

   ItemPtr loadItem( uint64_t uId );

   ItemPtr getItemAt( uint16_t containerId, uint8_t slotId );

   bool updateContainer( uint16_t containerId, uint8_t slotId, ItemPtr pItem );

   /*! heck if weapon category qualifies the weapon as onehanded */
   bool isOneHandedWeapon( Common::ItemUICategory weaponCategory );
   /*! calculate and return player ilvl based off equipped gear */
   uint16_t calculateEquippedGearItemLevel();
   /*! return the current amount of currency of type */
   uint32_t getCurrency( CurrencyType type );
   /*! add amount to the current of type */
   bool addCurrency( CurrencyType type, uint32_t amount );
   /*! remove amount from the currency of type */
   bool removeCurrency( CurrencyType type, uint32_t amount );

   void updateCurrencyDb();
   void updateBagDb( InventoryType type );
   void updateMannequinDb( InventoryType type );
   void updateItemDb( ItemPtr pItem ) const;

   bool isArmory( uint16_t containerId );
   bool isEquipment( uint16_t containerId );
   uint16_t getArmoryToEquipSlot( uint8_t slotId );

   /*! return the crystal amount of currency of type */
   uint32_t getCrystal( CrystalType type );
   /*! add amount to the crystal of type */
   bool addCrystal( CrystalType type, uint32_t amount );
   /*! remove amount from the crystals of type */
   bool removeCrystal( CrystalType type, uint32_t amount );
   bool isObtainable( uint32_t catalogId, uint8_t quantity );

   void updateCrystalDb();

   bool load();

   void send();

   uint8_t getFreeSlotsInBags();

   ContainerType getContainerType( uint32_t containerId );

   uint32_t getNextUId();


private:
   Entity::Player* m_pOwner;
   InventoryMap m_inventoryMap;
};

}
#endif
