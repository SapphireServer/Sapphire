#include <boost/lexical_cast.hpp>
#include <boost/algorithm/clamp.hpp>

#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>

#include "Actor/Player.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

#include "ItemContainer.h"
#include "Item.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Inventory::Inventory( Core::Entity::Player* pOwner )
{

   m_pOwner = pOwner;

   // shortcut for setting up inventory
   // TODO: use a loop to set theese up?
   auto setupContainer = []( InventoryMap& map, InventoryType type )
   { map[type] = make_ItemContainer( type ); };

   // main bags
   setupContainer( m_inventoryMap, Bag0 );
   setupContainer( m_inventoryMap, Bag1 );
   setupContainer( m_inventoryMap, Bag2 );
   setupContainer( m_inventoryMap, Bag3 );

   // gear set
   setupContainer( m_inventoryMap, GearSet0 );

   // gil contianer
   setupContainer( m_inventoryMap, Currency );

   // crystals??
   setupContainer( m_inventoryMap, Crystal );
   //m_inventoryMap[0x07D3] = ItemContainerPtr( new ItemContainer( UNKNOWN_0 ) );
   //m_inventoryMap[0x07D8] = ItemContainerPtr( new ItemContainer( UNKNOWN_1 ) );

   // armory weapons - 0
   setupContainer( m_inventoryMap, ArmoryMain );

   // armory offhand - 1
   setupContainer( m_inventoryMap, ArmoryOff );

   //armory head - 2
   setupContainer( m_inventoryMap, ArmoryHead );

   //armory body - 3
   setupContainer( m_inventoryMap, ArmoryBody );

   //armory hand - 4
   setupContainer( m_inventoryMap, ArmoryHand );

   //armory waist - 5
   setupContainer( m_inventoryMap, ArmoryWaist );

   //armory legs - 6
   setupContainer( m_inventoryMap, ArmoryLegs );

   //armory feet - 7
   setupContainer( m_inventoryMap, ArmoryFeet );

   //neck
   setupContainer( m_inventoryMap, ArmotyNeck );

   //earring
   setupContainer( m_inventoryMap, ArmoryEar );

   //wrist
   setupContainer( m_inventoryMap, ArmoryWrist );

   //armory rings - 11
   setupContainer( m_inventoryMap, ArmoryRing );

   //soul crystals - 13
   setupContainer( m_inventoryMap, ArmorySoulCrystal );
}


Core::Inventory::~Inventory()
{
}

Core::Inventory::InvSlotPairVec Core::Inventory::getSlotsOfItemsInInventory( uint32_t catalogId )
{
   InvSlotPairVec outVec;
   for( auto i : { Bag0, Bag1, Bag2, Bag3 } )
   {
      auto inv = m_inventoryMap[i];
      for( auto item : inv->getItemMap() )
      {
         if( item.second && item.second->getId() == catalogId )
            outVec.push_back( std::make_pair( i, static_cast< int8_t >( item.first ) ) );
      }
   }
   return outVec;
}

Core::Inventory::InvSlotPair Core::Inventory::getFreeBagSlot()
{
   for( auto i : { Bag0, Bag1, Bag2, Bag3 } )
   {
      auto freeSlot = static_cast< int8_t >( m_inventoryMap[i]->getFreeSlot() );

      if( freeSlot != -1 )
         return std::make_pair( i, freeSlot );
   }
   // no room in inventory
   return std::make_pair( 0, -1 );
}

Core::ItemPtr Core::Inventory::getItemAt( uint16_t containerId, uint8_t slotId )
{
   return m_inventoryMap[containerId]->getItem( slotId );
}

Core::ItemPtr Core::Inventory::createItem( uint32_t catalogId, uint8_t quantity )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   auto itemInfo = pExdData->get< Core::Data::Item >( catalogId );

   uint8_t itemAmount = quantity;

   if( itemInfo->stackSize == 1 )
      itemAmount = 1;

   if( !itemInfo )
      return nullptr;

   uint8_t flags = 0;

   std::string itemName( itemInfo->name );

   ItemPtr pItem( new Item( catalogId ) );

   pItem->setStackSize( itemAmount );
   pItem->setUId( getNextUId() );
   pItem->setModelIds( itemInfo->modelMain, itemInfo->modelSub );
   pItem->setCategory( static_cast< ItemUICategory >( itemInfo->itemUICategory ) );

  pDb->execute( "INSERT INTO charaglobalitem ( CharacterId, itemId, catalogId, stack, flags ) VALUES ( " +
                      std::to_string( m_pOwner->getId() ) + ", " +
                      std::to_string( pItem->getUId() ) + ", " +
                      std::to_string( pItem->getId() ) + ", " +
                      std::to_string( itemAmount ) + ", " +
                      std::to_string( flags ) + ");" );

   return pItem;

}


uint32_t Core::Inventory::getCurrency( CurrencyType type )
{

   auto currItem = m_inventoryMap[Currency]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return 0;

   return currItem->getStackSize();

}

uint32_t Core::Inventory::getCrystal( CrystalType type )
{

   auto currItem = m_inventoryMap[Crystal]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return 0;

   return currItem->getStackSize();

}

bool Core::Inventory::addCrystal( CrystalType type, uint32_t amount )
{
   auto currItem = m_inventoryMap[Crystal]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
   {
      // TODO: map currency type to itemid
      currItem = createItem( static_cast< uint8_t >( type ) + 1 );
      m_inventoryMap[Crystal]->setItem( static_cast< uint8_t >( type ) - 1, currItem );
      updateCrystalDb();
   }

   uint32_t currentAmount = currItem->getStackSize();

   currItem->setStackSize( currentAmount + amount );

   updateItemDb( currItem );

   return true;

}

bool Core::Inventory::addCurrency( CurrencyType type, uint32_t amount )
{
   auto currItem = m_inventoryMap[Currency]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
   {
      // TODO: map currency type to itemid
      currItem = createItem( 1 );
      m_inventoryMap[Currency]->setItem( static_cast< uint8_t >( type ) - 1, currItem );
      updateCurrencyDb();
   }

   uint32_t currentAmount = currItem->getStackSize();

   currItem->setStackSize( currentAmount + amount );

   updateItemDb( currItem );

   return true;

}

void Core::Inventory::updateCurrencyDb()
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   int32_t firstItemPos = -1;
   std::string query = "UPDATE charaitemcurrency SET ";

   for( int32_t i = 0; i <= 11; i++ )
   {
      auto currItem = m_inventoryMap[Currency]->getItem( i );

      if( currItem )
      {
         if( firstItemPos == -1 )
            firstItemPos = i;

         if( i > firstItemPos )
            query += ", ";

         query += "container_" + std::to_string( i ) + " = " + std::to_string( currItem->getUId() );
      }
   }

   query += " WHERE CharacterId = " + std::to_string( m_pOwner->getId() );

   pDb->execute( query );
}


void Core::Inventory::updateCrystalDb()
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   int32_t firstItemPos = -1;
   std::string query = "UPDATE charaitemcrystal SET ";

   for( int32_t i = 0; i <= 11; i++ )
   {
      auto currItem = m_inventoryMap[Crystal]->getItem( i );

      if( currItem )
      {
         if( firstItemPos == -1 )
            firstItemPos = i;

         if( i > firstItemPos )
            query += ", ";

         query += "container_" + std::to_string( i ) + " = " + std::to_string( currItem->getUId() );
      }
   }

   query += " WHERE CharacterId = " + std::to_string( m_pOwner->getId() );

   pDb->execute( query );
}

void Core::Inventory::updateBagDb( InventoryType type )
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   std::string query = "UPDATE charaiteminventory SET ";

   for( int32_t i = 0; i <= 34; i++ )
   {
      auto currItem = m_inventoryMap[type]->getItem( i );

      if( i > 0 )
         query += ", ";

      query += "container_" + std::to_string( i ) + " = " + std::to_string( currItem ? currItem->getUId() : 0 );
   }

   query += " WHERE CharacterId = " + std::to_string( m_pOwner->getId() ) +
      " AND storageId = " + std::to_string( static_cast< uint16_t >( type ) );

   pDb->execute( query );
}

bool Core::Inventory::isArmory( uint16_t containerId )
{
   return 
      containerId == ArmoryBody ||
      containerId == ArmoryEar ||
      containerId == ArmoryFeet ||
      containerId == ArmoryHand ||
      containerId == ArmoryHead ||
      containerId == ArmoryLegs ||
      containerId == ArmoryMain ||
      containerId == ArmoryOff ||
      containerId == ArmoryRing ||
      containerId == ArmoryWaist ||
      containerId == ArmoryWrist;
}

uint16_t Core::Inventory::getArmoryToEquipSlot( uint8_t slotId )
{
   switch( slotId )
   {
   case Body:
      return ArmoryBody;

   case Ear:
      return ArmoryEar;

   case Feet:
      return ArmoryFeet;

   case Hands:
      return ArmoryHand;

   case Legs:
      return ArmoryLegs;

   case MainHand:
      return ArmoryMain;

   case OffHand:
      return ArmoryOff;

   case Ring2:
   case Ring1:
      return ArmoryRing;

   case Waist:
      return ArmoryWaist;

   case Wrist:
      return ArmoryWrist;
   }

   return 0;
}



bool Core::Inventory::isEquipment( uint16_t containerId )
{
   return containerId == GearSet0;
}


void Core::Inventory::updateMannequinDb( InventoryType type )
{
   auto pLog = g_fw.get< Logger >();
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   std::string query = "UPDATE charaitemgearset SET ";

   for( int32_t i = 0; i <= 13; i++ )
   {
      auto currItem = m_inventoryMap[type]->getItem( i );

      if( i > 0 )
         query += ", ";

      query += "container_" + std::to_string( i ) + " = " + std::to_string( currItem ? currItem->getUId() : 0 );
   }

   query += " WHERE CharacterId = " + std::to_string( m_pOwner->getId() ) +
      " AND storageId = " + std::to_string( static_cast< uint16_t >( type ) );

   pLog->debug( query );
   pDb->execute( query );
}


void Core::Inventory::updateItemDb( Core::ItemPtr pItem ) const
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   pDb->execute( "UPDATE charaglobalitem SET stack = " + std::to_string( pItem->getStackSize() ) + " " +
                     // TODO: add other attributes
                     " WHERE itemId = " + std::to_string( pItem->getUId() ) );
}

bool Core::Inventory::removeCurrency( CurrencyType type, uint32_t amount )
{

   auto currItem = m_inventoryMap[Currency]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return false;

   uint32_t currentAmount = currItem->getStackSize();
   if( amount > currentAmount )
      currItem->setStackSize( 0 );
   else
      currItem->setStackSize( currentAmount - amount );

   updateItemDb( currItem );

   return true;
}

bool Core::Inventory::removeCrystal( CrystalType type, uint32_t amount )
{

   auto currItem = m_inventoryMap[Crystal]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return false;

   uint32_t currentAmount = currItem->getStackSize();
   if( amount > currentAmount )
      currItem->setStackSize( 0 );
   else
      currItem->setStackSize( currentAmount - amount );

   updateItemDb( currItem );

   return true;
}

bool Core::Inventory::isOneHandedWeapon( ItemUICategory weaponCategory )
{
   switch ( weaponCategory )
   {
   case ItemUICategory::AlchemistsPrimaryTool:
   case ItemUICategory::ArmorersPrimaryTool:
   case ItemUICategory::BotanistsPrimaryTool:
   case ItemUICategory::CulinariansPrimaryTool:
   case ItemUICategory::OnehandedConjurersArm:
   case ItemUICategory::CarpentersPrimaryTool:
   case ItemUICategory::FishersPrimaryTool:
   case ItemUICategory::GladiatorsArm:
   case ItemUICategory::GoldsmithsPrimaryTool:
   case ItemUICategory::LeatherworkersPrimaryTool:
   case ItemUICategory::MinersPrimaryTool:
   case ItemUICategory::OnehandedThaumaturgesArm:
   case ItemUICategory::WeaversPrimaryTool:
   case ItemUICategory::BlacksmithsPrimaryTool:
      return true;
   default:
      return false;
   }
}

bool Core::Inventory::isObtainable( uint32_t catalogId, uint8_t quantity )
{
   
   return true;
}


int16_t Core::Inventory::addItem( uint16_t inventoryId, int8_t slotId, uint32_t catalogId, uint8_t quantity )
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto itemInfo = pExdData->get< Core::Data::Item >( catalogId );

   // if item data doesn't exist or it's a blank field
   if( !itemInfo || itemInfo->levelItem == 0 )
   {
      return -1;
   }

   int8_t rSlotId = -1;

   //if( itemInfo->stack_size > 1 )
   //{
   //   auto itemList = this->getSlotsOfItemsInInventory( catalogId );
   //   // TODO: this is a stacked item so we need to see if the item is already in inventory and
   //   //       check how much free space we have on existing stacks before looking for empty slots.
   //}
   //else
   {
      auto freeSlot = this->getFreeBagSlot();
      inventoryId = freeSlot.first;
      rSlotId = freeSlot.second;

      if( rSlotId == -1 )
         return -1;
   }

   auto item = createItem( catalogId, quantity );
   
   if( rSlotId != -1 )
   {

      m_inventoryMap[inventoryId]->setItem( rSlotId, item );

      pDb->execute( "UPDATE charaiteminventory SET container_" + std::to_string( rSlotId ) + " = " + std::to_string( item->getUId() ) +
                         " WHERE storageId = " + std::to_string( inventoryId ) +
                         " AND CharacterId = " + std::to_string( m_pOwner->getId() ) );

      ZoneChannelPacket< FFXIVIpcUpdateInventorySlot > invUpPacket( m_pOwner->getId() );
      invUpPacket.data().containerId = inventoryId;
      invUpPacket.data().catalogId = catalogId;
      invUpPacket.data().quantity = item->getStackSize();
      invUpPacket.data().hqFlag = item->isHq() ? 1 : 0;
      invUpPacket.data().slot = rSlotId;
      invUpPacket.data().condition = 30000;
      m_pOwner->queuePacket( invUpPacket );

      m_pOwner->queuePacket( ActorControlPacket143( m_pOwner->getId(), ItemObtainIcon, catalogId, item->getStackSize() ) );

   }

   return rSlotId;

}

void Core::Inventory::moveItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot )
{

   auto tmpItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );
   auto& itemMap = m_inventoryMap[fromInventoryId]->getItemMap();

   if( tmpItem == nullptr )
      return;

   itemMap[fromSlotId].reset();

   m_inventoryMap[toInventoryId]->setItem( toSlot, tmpItem );

   if( toInventoryId != GearSet0 )
      updateBagDb( static_cast< InventoryType >( toInventoryId ) );

   if( fromInventoryId != GearSet0 && fromInventoryId != toInventoryId )
      updateBagDb( static_cast< InventoryType >( fromInventoryId ) );

   if( static_cast< InventoryType >( toInventoryId ) == GearSet0 )
   {
      m_pOwner->equipItem( static_cast< EquipSlot >( toSlot ), tmpItem, true );
      updateMannequinDb( static_cast< InventoryType >( toInventoryId ) );
   }

   if( static_cast< InventoryType >( fromInventoryId ) == GearSet0 )
   {
      m_pOwner->unequipItem( static_cast< EquipSlot >( fromSlotId ), tmpItem );
      updateMannequinDb( static_cast< InventoryType >( fromInventoryId ) );
   }


}

bool Core::Inventory::updateContainer( uint16_t containerId, uint8_t slotId, ItemPtr pItem )
{
   auto containerType = getContainerType( containerId );

   m_inventoryMap[containerId]->setItem( slotId, pItem );

   switch( containerType )
   {
      case Armory:
      case CurrencyCrystal:
      case Bag:
      {
         updateBagDb( static_cast< InventoryType >( containerId ) );
         break;
      }

      case GearSet:
      {
         if( pItem )
            m_pOwner->equipItem( static_cast< EquipSlot >( slotId ), pItem, true );
         else
            m_pOwner->unequipItem( static_cast< EquipSlot >( slotId ), pItem );

         updateMannequinDb( static_cast< InventoryType >( containerId ) );
         break;
      }
      default:
         break;
   }

   return true;
}

void Core::Inventory::swapItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot )
{
   auto fromItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );
   auto toItem = m_inventoryMap[toInventoryId]->getItem( toSlot );
   auto& itemMap = m_inventoryMap[fromInventoryId]->getItemMap();

   if( fromItem == nullptr || toItem == nullptr )
      return;

   // An item is being moved from bag0-3 to equippment, meaning
   // the swapped out item will be placed in the matching armory.
   if( isEquipment( toInventoryId ) 
       && !isEquipment( fromInventoryId )
       && !isArmory( fromInventoryId ) )
   {
      updateContainer( fromInventoryId, fromSlotId, nullptr );
      fromInventoryId = getArmoryToEquipSlot( toSlot );
      fromSlotId = static_cast < uint8_t >( m_inventoryMap[fromInventoryId]->getFreeSlot() );
   }

   auto containerTypeFrom = getContainerType( fromInventoryId );
   auto containerTypeTo = getContainerType( toInventoryId );

   updateContainer( toInventoryId, toSlot, fromItem );
   updateContainer( fromInventoryId, fromSlotId, toItem );
}

void Core::Inventory::discardItem( uint16_t fromInventoryId, uint8_t fromSlotId )
{
   // i am not entirely sure how this should be generated or if it even is important for us...
   uint32_t transactionId = 1;

   auto fromItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );

   m_inventoryMap[fromInventoryId]->removeItem( fromSlotId );
   updateContainer( fromInventoryId, fromSlotId, nullptr );

   ZoneChannelPacket< FFXIVIpcInventoryTransaction > invTransPacket( m_pOwner->getId() );
   invTransPacket.data().transactionId = transactionId;
   invTransPacket.data().ownerId = m_pOwner->getId();
   invTransPacket.data().storageId = fromInventoryId;
   invTransPacket.data().catalogId = fromItem->getId();
   invTransPacket.data().stackSize = fromItem->getStackSize();
   invTransPacket.data().slotId = fromSlotId;
   invTransPacket.data().type = 7;
   m_pOwner->queuePacket( invTransPacket );

   ZoneChannelPacket< FFXIVIpcInventoryTransactionFinish > invTransFinPacket( m_pOwner->getId() );
   invTransFinPacket.data().transactionId = transactionId;
   invTransFinPacket.data().transactionId1 = transactionId;
   m_pOwner->queuePacket( invTransFinPacket );
}

Core::ItemPtr Core::Inventory::loadItem( uint64_t uId )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   // load actual item 
   auto itemRes = pDb->query( "SELECT catalogId, stack, flags FROM charaglobalitem WHERE itemId = " + std::to_string( uId ) + ";" );
   if( !itemRes->next() )
      return nullptr;

   try
   {
      auto itemInfo = pExdData->get< Core::Data::Item >( itemRes->getUInt( 1 ) );
      bool isHq = itemRes->getUInt( 3 ) == 1 ? true : false;
      ItemPtr pItem( new Item( uId, 
                               itemRes->getUInt( 1 ),
                               itemInfo->modelMain,
                               itemInfo->modelSub, 
                               static_cast< ItemUICategory >( itemInfo->itemUICategory ),
                               isHq ) );
      pItem->setStackSize( itemRes->getUInt( 2 ) );

      return pItem;
   }
   catch( ... )
   {
      return nullptr;
   }
}

bool Core::Inventory::load()
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   //////////////////////////////////////////////////////////////////////////////////////////////////////
   // load active gearset
   auto res = pDb->query( "SELECT storageId, container_0, container_1, container_2, container_3, "
                               "container_4, container_5, container_6, container_7, "
                               "container_8, container_9, container_10, container_11, "
                               "container_12, container_13 "
                               "FROM charaitemgearset " \
                               "WHERE CharacterId =  " + std::to_string( m_pOwner->getId() ) + " " \
                               "ORDER BY storageId ASC;" );

   while( res->next() )
   {
      uint16_t storageId = res->getUInt16( 1 );

      for( uint32_t i = 1; i <= 14; i++ )
      {
         uint64_t uItemId = res->getUInt64( i + 1 );
         if( uItemId == 0 )
            continue;

         ItemPtr pItem = loadItem( uItemId );

         if( pItem == nullptr )
            continue;

         m_inventoryMap[storageId]->getItemMap()[i - 1] = pItem;
         m_pOwner->equipItem( static_cast< EquipSlot >( i - 1 ), pItem, false );
      }
   }

   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Load Bags
   auto bagRes = pDb->query( "SELECT storageId, "
                                  "container_0, container_1, container_2, container_3, container_4, "
                                  "container_5, container_6, container_7, container_8, container_9, "
                                  "container_10, container_11, container_12, container_13, container_14, "
                                  "container_15, container_16, container_17, container_18, container_19, "
                                  "container_20, container_21, container_22, container_23, container_24, "
                                  "container_25, container_26, container_27, container_28, container_29, "
                                  "container_30, container_31, container_32, container_33, container_34 "
                                  "FROM charaiteminventory " \
                                  "WHERE CharacterId =  " + std::to_string( m_pOwner->getId() ) + " " \
                                  "ORDER BY storageId ASC;" );

   while( bagRes->next() )
   {
      uint16_t storageId = bagRes->getUInt16( 1 );
      for( uint32_t i = 1; i <= 35; i++ )
      {
         uint64_t uItemId = bagRes->getUInt64( i + 1 );
         if( uItemId == 0 )
            continue;

         ItemPtr pItem = loadItem( uItemId );

         if( pItem == nullptr )
            continue;

         m_inventoryMap[storageId]->getItemMap()[i - 1] = pItem;
      }
   }


   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Load Currency
   auto curRes = pDb->query( "SELECT storageId, "
                                  "container_0, container_1, container_2, container_3, container_4, "
                                  "container_5, container_6, container_7, container_8, container_9, "
                                  "container_10, container_11 "
                                  "FROM charaitemcurrency " \
                                  "WHERE CharacterId =  " + std::to_string( m_pOwner->getId() ) + " " \
                                  "ORDER BY storageId ASC;" );

   while( curRes->next() )
   {
      uint16_t storageId = curRes->getUInt16( 1 );
      for( uint32_t i = 1; i <= 12; i++ )
      {
         uint64_t uItemId = curRes->getUInt64( i + 1 );
         if( uItemId == 0 )
            continue;

         ItemPtr pItem = loadItem( uItemId );

         if( pItem == nullptr )
            continue;

         m_inventoryMap[storageId]->getItemMap()[i - 1] = pItem;
      }
   }


   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   // Load Crystals
   auto crystalRes = pDb->query( "SELECT storageId, "
                                      "container_0, container_1, container_2, container_3, container_4, "
                                      "container_5, container_6, container_7, container_8, container_9, "
                                      "container_10, container_11, container_12, container_13, container_14, "
                                      "container_15, container_16, container_17 "
                                      "FROM charaitemcrystal " \
                                      "WHERE CharacterId =  " + std::to_string( m_pOwner->getId() ) + " " \
                                      "ORDER BY storageId ASC;" );

   while( crystalRes->next() )
   {
      uint16_t storageId = crystalRes->getUInt16( 1 );
      for( int32_t i = 1; i <= 17; i++ )
      {
         uint64_t uItemId = crystalRes->getUInt64( i + 1 );
         if( uItemId == 0 )
            continue;

         ItemPtr pItem = loadItem( uItemId );

         if( pItem == nullptr )
            continue;

         m_inventoryMap[storageId]->getItemMap()[i - 1] = pItem;
      }
   }

   return true;
}


void Core::Inventory::send()
{
   InventoryMap::iterator it;

   int32_t count = 0;
   for( it = m_inventoryMap.begin(); it != m_inventoryMap.end(); ++it, count++ )
   {

      auto pMap = it->second->getItemMap();
      auto itM = pMap.begin();

      for( ; itM != pMap.end(); ++itM )
      {
         if( !itM->second )
            return;

         if( it->second->getId() == InventoryType::Currency || it->second->getId() == InventoryType::Crystal )
         {
            ZoneChannelPacket< FFXIVIpcCurrencyCrystalInfo > currencyInfoPacket( m_pOwner->getId() );
            currencyInfoPacket.data().sequence = count;
            currencyInfoPacket.data().catalogId = itM->second->getId();
            currencyInfoPacket.data().unknown = 1;
            currencyInfoPacket.data().quantity = itM->second->getStackSize();
            currencyInfoPacket.data().containerId = it->second->getId();
            currencyInfoPacket.data().slot = 0;
            m_pOwner->queuePacket( currencyInfoPacket );
         }
         else
         {
            ZoneChannelPacket< FFXIVIpcItemInfo > itemInfoPacket( m_pOwner->getId() );
            itemInfoPacket.data().sequence = count;
            itemInfoPacket.data().containerId = it->second->getId();
            itemInfoPacket.data().slot = itM->first;
            itemInfoPacket.data().quantity = itM->second->getStackSize();
            itemInfoPacket.data().catalogId = itM->second->getId();
            itemInfoPacket.data().condition = 30000;
            itemInfoPacket.data().spiritBond = 0;
            itemInfoPacket.data().hqFlag = itM->second->isHq() ? 1 : 0;
            m_pOwner->queuePacket( itemInfoPacket );
         }
      }

      ZoneChannelPacket< FFXIVIpcContainerInfo > containerInfoPacket( m_pOwner->getId() );
      containerInfoPacket.data().sequence = count;
      containerInfoPacket.data().numItems = it->second->getEntryCount();
      containerInfoPacket.data().containerId = it->second->getId();
      m_pOwner->queuePacket( containerInfoPacket );


   }

}

uint16_t Core::Inventory::calculateEquippedGearItemLevel()
{
   uint32_t iLvlResult = 0;

   auto gearSetMap = m_inventoryMap[GearSet0]->getItemMap();

   auto it = gearSetMap.begin();

   while ( it != gearSetMap.end() )
   {
      auto currItem = it->second;

      if ( currItem )
      {
         iLvlResult += currItem->getItemLevel();

         // If item is weapon and isn't one-handed
         if ( currItem->isWeapon() && !isOneHandedWeapon( currItem->getCategory() ) )
         {
            iLvlResult += currItem->getItemLevel();
         }
         else
         {
            auto pLog = g_fw.get< Logger >();
            pLog->debug( "Is one handed" );
         }
      }

      it++;
   }

   return boost::algorithm::clamp( iLvlResult / 13, 0, 9999 );
}


uint8_t Core::Inventory::getFreeSlotsInBags()
{
   uint8_t slots = 0;
   for( uint8_t container : { 0, 1, 2, 3 } )
   {
      slots += 34 - m_inventoryMap[container]->getEntryCount();
   }
   return slots;
}


Core::Inventory::ContainerType Core::Inventory::getContainerType( uint32_t containerId )
{
   if( containerId < 5 )
   {
      return Bag;
   }
   else if( containerId < 2000 )
   {
      return GearSet;
   }
   else if( containerId < 3200 )
   {
      return CurrencyCrystal;
   }
   else if( containerId < 3600 )
   {
      return Armory;
   }
   else
   {
      return Unknown;
   }
}

uint32_t Core::Inventory::getNextUId()
{
   uint32_t charId = 0;
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   auto pQR = pDb->query( "SELECT MAX(ItemId) FROM charaglobalitem" );

   if( !pQR->next() )
      return 0x00500001;

   charId = pQR->getUInt( 1 ) + 1;
   if( charId < 0x00500001 )
      return 0x00500001;

   return charId;
}
