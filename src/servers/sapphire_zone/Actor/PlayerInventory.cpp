#include <Common.h>
#include <Logging/Logger.h>
#include <Network/CommonActorControl.h>

#include "Zone/Zone.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

#include "Inventory/Item.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/ItemUtil.h"

#include "Player.h"
#include "Framework.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/clamp.hpp>

#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Database/DatabaseDef.h>

#include "Actor/Player.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"


#include "Framework.h"
#include <Network/CommonActorControl.h>

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;




void Core::Entity::Player::initInventory()
{
   auto setupContainer = [this]( InventoryType type, uint8_t maxSize, const std::string& tableName, bool isMultiStorage )
   { m_inventoryMap[type] = make_ItemContainer( type, maxSize, tableName, isMultiStorage ); };

   // main bags
   setupContainer( Bag0, 34, "charaiteminventory", true );
   setupContainer( Bag1, 34, "charaiteminventory", true );
   setupContainer( Bag2, 34, "charaiteminventory", true );
   setupContainer( Bag3, 34, "charaiteminventory", true );

   // gear set
   setupContainer( GearSet0, 13, "charaitemgearset", true );

   // gil contianer
   setupContainer( Currency, 11, "charaitemcurrency", false );

   // crystals??
   setupContainer( Crystal, 11, "charaitemcrystal", false );

   // armory weapons - 0
   setupContainer( ArmoryMain, 34, "charaiteminventory", true );

   // armory offhand - 1
   setupContainer( ArmoryOff, 34, "charaiteminventory", true );

   //armory head - 2
   setupContainer( ArmoryHead, 34, "charaiteminventory", true );

   //armory body - 3
   setupContainer( ArmoryBody, 34, "charaiteminventory", true );

   //armory hand - 4
   setupContainer( ArmoryHand, 34, "charaiteminventory", true );

   //armory waist - 5
   setupContainer( ArmoryWaist, 34, "charaiteminventory", true );

   //armory legs - 6
   setupContainer( ArmoryLegs, 34, "charaiteminventory", true );

   //armory feet - 7
   setupContainer( ArmoryFeet, 34, "charaiteminventory", true );

   //neck
   setupContainer( ArmotyNeck, 34, "charaiteminventory", true );

   //earring
   setupContainer( ArmoryEar, 34, "charaiteminventory", true );

   //wrist
   setupContainer( ArmoryWrist, 34, "charaiteminventory", true );

   //armory rings - 11
   setupContainer( ArmoryRing, 34, "charaiteminventory", true );

   //soul crystals - 13
   setupContainer( ArmorySoulCrystal, 34, "charaiteminventory", true );

   loadInventory();

}

void Core::Entity::Player::sendItemLevel()
{
   queuePacket( boost::make_shared< ActorControlPacket142 >( getId(), SetItemLevel, getItemLevel(), 0 ) );
}

// TODO: This has to be redone and simplified
void Core::Entity::Player::equipWeapon( ItemPtr pItem )
{
   ClassJob currentClass = static_cast< ClassJob >( getClass() );

   switch( pItem->getCategory() )
   {
   case ItemUICategory::PugilistsArm:
      if( currentClass != ClassJob::Pugilist &&
          currentClass != ClassJob::Monk )
         setClassJob( ClassJob::Pugilist );
      break;
   case ItemUICategory::GladiatorsArm:
      if( currentClass != ClassJob::Gladiator &&
          currentClass != ClassJob::Paladin )
         setClassJob( ClassJob::Gladiator );
      break;
   case ItemUICategory::MaraudersArm:
      if( currentClass != ClassJob::Marauder &&
          currentClass != ClassJob::Warrior )
         setClassJob( ClassJob::Marauder );
      break;
   case ItemUICategory::ArchersArm:
      if( currentClass != ClassJob::Archer &&
          currentClass != ClassJob::Bard )
         setClassJob( ClassJob::Archer );
      break;
   case ItemUICategory::LancersArm:
      if( currentClass != ClassJob::Lancer &&
          currentClass != ClassJob::Dragoon )
         setClassJob( ClassJob::Lancer );
      break;
   case ItemUICategory::OnehandedThaumaturgesArm:
   case ItemUICategory::TwohandedThaumaturgesArm:
      if( currentClass != ClassJob::Thaumaturge &&
          currentClass != ClassJob::Blackmage )
         setClassJob( ClassJob::Thaumaturge );
      break;
   case ItemUICategory::OnehandedConjurersArm:
   case ItemUICategory::TwohandedConjurersArm:
      if( currentClass != ClassJob::Conjurer &&
          currentClass != ClassJob::Whitemage )
         setClassJob( ClassJob::Conjurer );
      break;
   case ItemUICategory::ArcanistsGrimoire:
      if( currentClass != ClassJob::Arcanist &&
          currentClass != ClassJob::Summoner &&
          currentClass != ClassJob::Scholar )
         setClassJob( ClassJob::Arcanist );
      break;
   default:
      break;
   }
}

// equip an item
void Core::Entity::Player::equipItem( Common::EquipSlot equipSlotId, ItemPtr pItem, bool sendUpdate )
{

   //g_framework.getLogger().debug( "Equipping into slot " + std::to_string( equipSlotId ) );

   uint64_t model = pItem->getModelId1();
   uint64_t model2 = pItem->getModelId2();

   switch( equipSlotId )
   {
   case Common::EquipSlot::MainHand:
      m_modelMainWeapon = model;
      m_modelSubWeapon = model2;
      // TODO: add job change upon changing weapon if needed
      // equipWeapon( pItem );
      break;

   case Common::EquipSlot::OffHand:
      m_modelSubWeapon = model;
      break;

   case Common::EquipSlot::SoulCrystal:
      // TODO: add Job change on equipping crystal
      // change job
      break;

   default: // any other slot
      m_modelEquip[static_cast< uint8_t >( equipSlotId )] = static_cast< uint32_t >( model );
      break;

   }

   if( sendUpdate )
   { 
      this->sendModel();
      m_itemLevel = calculateEquippedGearItemLevel();
      sendItemLevel();
   }
}

void Core::Entity::Player::unequipItem( Common::EquipSlot equipSlotId, ItemPtr pItem )
{
   m_modelEquip[static_cast< uint8_t >( equipSlotId )] = 0;
   sendModel();

   m_itemLevel = calculateEquippedGearItemLevel();
   sendItemLevel();
}

// TODO: these next functions are so similar that they could likely be simplified
void Core::Entity::Player::addCurrency( CurrencyType type, uint32_t amount )
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

   auto invUpPacket = makeZonePacket< FFXIVIpcUpdateInventorySlot >( getId() );
   invUpPacket->data().containerId = Common::InventoryType::Currency;
   invUpPacket->data().catalogId = 1;
   invUpPacket->data().quantity = getCurrency( type );
   invUpPacket->data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}

void Core::Entity::Player::removeCurrency( Common::CurrencyType type, uint32_t amount )
{

   auto currItem = m_inventoryMap[Currency]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return;

   uint32_t currentAmount = currItem->getStackSize();
   if( amount > currentAmount )
      currItem->setStackSize( 0 );
   else
      currItem->setStackSize( currentAmount - amount );

   updateItemDb( currItem );
   auto invUpPacket = makeZonePacket< FFXIVIpcUpdateInventorySlot >( getId() );
   invUpPacket->data().containerId = Common::InventoryType::Currency;
   invUpPacket->data().catalogId = 1;
   invUpPacket->data().quantity = getCurrency( type );
   invUpPacket->data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}


void Core::Entity::Player::addCrystal( Common::CrystalType type, uint32_t amount )
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

   auto invUpPacket = makeZonePacket< FFXIVIpcUpdateInventorySlot >( getId() );
   invUpPacket->data().containerId = Common::InventoryType::Crystal;
   invUpPacket->data().catalogId = static_cast< uint8_t >( type ) + 1;
   invUpPacket->data().quantity = getCrystal( type );
   invUpPacket->data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );

   queuePacket( boost::make_shared< ActorControlPacket143 >( getId(), ItemObtainIcon,
                                                             static_cast< uint8_t >( type ) + 1, amount ) );
}

void Core::Entity::Player::removeCrystal( Common::CrystalType type, uint32_t amount )
{
   auto currItem = m_inventoryMap[Crystal]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return;

   uint32_t currentAmount = currItem->getStackSize();
   if( amount > currentAmount )
      currItem->setStackSize( 0 );
   else
      currItem->setStackSize( currentAmount - amount );

   updateItemDb( currItem );

   auto invUpPacket = makeZonePacket< FFXIVIpcUpdateInventorySlot >( getId() );
   invUpPacket->data().containerId = Common::InventoryType::Crystal;
   invUpPacket->data().catalogId = static_cast< uint8_t >( type ) + 1;
   invUpPacket->data().quantity = getCrystal( type );
   invUpPacket->data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}

bool Core::Entity::Player::tryAddItem( uint16_t catalogId, uint32_t quantity )
{

   for( uint16_t i = 0; i < 4; i++ )
   {
      if( addItem( i, -1, catalogId, quantity ) != -1 )
         return true;
   }
   return false;
}

void Core::Entity::Player::sendInventory()
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
            auto currencyInfoPacket = makeZonePacket< FFXIVIpcCurrencyCrystalInfo >( getId() );
            currencyInfoPacket->data().sequence = count;
            currencyInfoPacket->data().catalogId = itM->second->getId();
            currencyInfoPacket->data().unknown = 1;
            currencyInfoPacket->data().quantity = itM->second->getStackSize();
            currencyInfoPacket->data().containerId = it->second->getId();
            currencyInfoPacket->data().slot = 0;
            queuePacket( currencyInfoPacket );
         }
         else
         {
            auto itemInfoPacket = makeZonePacket< FFXIVIpcItemInfo >( getId() );
            itemInfoPacket->data().sequence = count;
            itemInfoPacket->data().containerId = it->second->getId();
            itemInfoPacket->data().slot = itM->first;
            itemInfoPacket->data().quantity = itM->second->getStackSize();
            itemInfoPacket->data().catalogId = itM->second->getId();
            itemInfoPacket->data().condition = 30000;
            itemInfoPacket->data().spiritBond = 0;
            itemInfoPacket->data().hqFlag = itM->second->isHq() ? 1 : 0;
            queuePacket( itemInfoPacket );
         }
      }

      auto containerInfoPacket = makeZonePacket< FFXIVIpcContainerInfo >( getId() );
      containerInfoPacket->data().sequence = count;
      containerInfoPacket->data().numItems = it->second->getEntryCount();
      containerInfoPacket->data().containerId = it->second->getId();
      queuePacket( containerInfoPacket );


   }

}

Core::Entity::Player::InvSlotPairVec Core::Entity::Player::getSlotsOfItemsInInventory( uint32_t catalogId )
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

Core::Entity::Player::InvSlotPair Core::Entity::Player::getFreeBagSlot()
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

Core::ItemPtr Core::Entity::Player::getItemAt( uint16_t containerId, uint8_t slotId )
{
   return m_inventoryMap[containerId]->getItem( slotId );
}


uint32_t Core::Entity::Player::getCurrency( CurrencyType type )
{

   auto currItem = m_inventoryMap[Currency]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return 0;

   return currItem->getStackSize();

}

uint32_t Core::Entity::Player::getCrystal( CrystalType type )
{

   auto currItem = m_inventoryMap[Crystal]->getItem( static_cast< uint8_t >( type ) - 1 );

   if( !currItem )
      return 0;

   return currItem->getStackSize();

}

void Core::Entity::Player::updateCurrencyDb()
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

   query += " WHERE CharacterId = " + std::to_string( getId() );

   pDb->execute( query );
}


void Core::Entity::Player::updateCrystalDb()
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

   query += " WHERE CharacterId = " + std::to_string( getId() );

   pDb->execute( query );
}

void Core::Entity::Player::updateBagDb( InventoryType type )
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

   query += " WHERE CharacterId = " + std::to_string( getId() ) +
            " AND storageId = " + std::to_string( static_cast< uint16_t >( type ) );

   pDb->execute( query );
}


void Core::Entity::Player::updateMannequinDb( InventoryType type )
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

   query += " WHERE CharacterId = " + std::to_string( getId() ) +
            " AND storageId = " + std::to_string( static_cast< uint16_t >( type ) );

   pLog->debug( query );
   pDb->execute( query );
}


void Core::Entity::Player::updateItemDb( Core::ItemPtr pItem ) const
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   pDb->execute( "UPDATE charaglobalitem SET stack = " + std::to_string( pItem->getStackSize() ) + " " +
                 // TODO: add other attributes
                 " WHERE itemId = " + std::to_string( pItem->getUId() ) );
}

void Core::Entity::Player::deleteItemDb( Core::ItemPtr item ) const
{
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
   pDb->execute( "UPDATE charaglobalitem SET IS_DELETE = 1 WHERE itemId = " + std::to_string( item->getUId() ) );
}


bool Core::Entity::Player::isObtainable( uint32_t catalogId, uint8_t quantity )
{

   return true;
}


int16_t Core::Entity::Player::addItem( uint16_t inventoryId, int8_t slotId, uint32_t catalogId, uint16_t quantity, bool isHq, bool silent )
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
      auto freeSlot = getFreeBagSlot();
      inventoryId = freeSlot.first;
      rSlotId = freeSlot.second;

      if( rSlotId == -1 )
         return -1;
   }

   auto item = createItem( catalogId, quantity );

   item->setHq( isHq );

   if( rSlotId != -1 )
   {

      m_inventoryMap[inventoryId]->setItem( rSlotId, item );

      pDb->execute( "UPDATE charaiteminventory SET container_" + std::to_string( rSlotId ) + " = " + std::to_string( item->getUId() ) +
                    " WHERE storageId = " + std::to_string( inventoryId ) +
                    " AND CharacterId = " + std::to_string( getId() ) );


      auto invUpPacket = makeZonePacket< FFXIVIpcUpdateInventorySlot >( getId() );
      invUpPacket->data().containerId = inventoryId;
      invUpPacket->data().catalogId = catalogId;
      invUpPacket->data().quantity = item->getStackSize();
      invUpPacket->data().hqFlag = item->isHq() ? 1 : 0;
      invUpPacket->data().slot = rSlotId;
      invUpPacket->data().condition = 30000;
      queuePacket( invUpPacket );

      if( !silent )
         queuePacket( boost::make_shared< ActorControlPacket143 >( getId(), ItemObtainIcon,
                                                                   catalogId, item->getStackSize() ) );

   }

   return rSlotId;

}

void Core::Entity::Player::moveItem( uint16_t fromInventoryId, uint8_t fromSlotId, uint16_t toInventoryId, uint8_t toSlot )
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
      equipItem( static_cast< EquipSlot >( toSlot ), tmpItem, true );
      updateMannequinDb( static_cast< InventoryType >( toInventoryId ) );
   }

   if( static_cast< InventoryType >( fromInventoryId ) == GearSet0 )
   {
      unequipItem( static_cast< EquipSlot >( fromSlotId ), tmpItem );
      updateMannequinDb( static_cast< InventoryType >( fromInventoryId ) );
   }


}

bool Core::Entity::Player::updateContainer( uint16_t containerId, uint8_t slotId, ItemPtr pItem )
{
   auto containerType = Items::Util::getContainerType( containerId );

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
            equipItem( static_cast< EquipSlot >( slotId ), pItem, true );
         else
            unequipItem( static_cast< EquipSlot >( slotId ), pItem );

         updateMannequinDb( static_cast< InventoryType >( containerId ) );
         break;
      }
      default:
         break;
   }

   return true;
}

void Core::Entity::Player::splitItem( uint16_t fromInventoryId, uint8_t fromSlotId,
                                      uint16_t toInventoryId, uint8_t toSlot, uint16_t itemCount )
{
   auto fromItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );
   if( !fromItem )
      return;

   // check we have enough items in the origin slot
   // nb: don't let the client 'split' a whole stack into another slot
   if( fromItem->getStackSize() < itemCount )
      // todo: correct the invalid item split? does retail do this or does it just ignore it?
      return;

   // make sure toInventoryId & toSlot are actually free so we don't orphan an item
   if( m_inventoryMap[toInventoryId]->getItem( toSlot ) )
      // todo: correct invalid move? again, not sure what retail does here
      return;

   auto newSlot = addItem( toInventoryId, toSlot, fromItem->getId(), itemCount, fromItem->isHq(), true );
   if( newSlot == -1 )
      return;

   auto newItem = m_inventoryMap[toInventoryId]->getItem( static_cast< uint8_t >( newSlot ) );

   fromItem->setStackSize( fromItem->getStackSize() - itemCount );

   updateContainer( fromInventoryId, fromSlotId, fromItem );
   updateContainer( toInventoryId, toSlot, newItem );

   updateItemDb( fromItem );
}

void Core::Entity::Player::mergeItem( uint16_t fromInventoryId, uint8_t fromSlotId,
                                      uint16_t toInventoryId, uint8_t toSlot )
{
   auto fromItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );
   auto toItem = m_inventoryMap[toInventoryId]->getItem( toSlot );

   if( !fromItem || !toItem )
      return;

   if( fromItem->getId() != toItem->getId() )
      return;

   uint32_t stackSize = fromItem->getStackSize() + toItem->getStackSize();
   uint32_t stackOverflow = stackSize - std::min< uint32_t >( fromItem->getMaxStackSize(), stackSize );

   // we can destroy the original stack if there's no overflow
   if( stackOverflow == 0 )
   {
      m_inventoryMap[fromInventoryId]->removeItem( fromSlotId );
      deleteItemDb( fromItem );
   }
   else
   {
      fromItem->setStackSize( stackOverflow );
      updateItemDb( fromItem );
   }


   toItem->setStackSize( stackSize );
   updateItemDb( toItem );

   updateContainer( fromInventoryId, fromSlotId, fromItem );
   updateContainer( toInventoryId, toSlot, toItem );
}

void Core::Entity::Player::swapItem( uint16_t fromInventoryId, uint8_t fromSlotId,
                                     uint16_t toInventoryId, uint8_t toSlot )
{
   auto fromItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );
   auto toItem = m_inventoryMap[toInventoryId]->getItem( toSlot );
   auto& itemMap = m_inventoryMap[fromInventoryId]->getItemMap();

   if( fromItem == nullptr || toItem == nullptr )
      return;

   // An item is being moved from bag0-3 to equippment, meaning
   // the swapped out item will be placed in the matching armory.
   if( Items::Util::isEquipment( toInventoryId )
       && !Items::Util::isEquipment( fromInventoryId )
       && !Items::Util::isArmory( fromInventoryId ) )
   {
      updateContainer( fromInventoryId, fromSlotId, nullptr );
      fromInventoryId = Items::Util::getArmoryToEquipSlot( toSlot );
      fromSlotId = static_cast < uint8_t >( m_inventoryMap[fromInventoryId]->getFreeSlot() );
   }

   auto containerTypeFrom = Items::Util::getContainerType( fromInventoryId );
   auto containerTypeTo = Items::Util::getContainerType( toInventoryId );

   updateContainer( toInventoryId, toSlot, fromItem );
   updateContainer( fromInventoryId, fromSlotId, toItem );
}

void Core::Entity::Player::discardItem( uint16_t fromInventoryId, uint8_t fromSlotId )
{
   // i am not entirely sure how this should be generated or if it even is important for us...
   uint32_t transactionId = 1;

   auto fromItem = m_inventoryMap[fromInventoryId]->getItem( fromSlotId );

   deleteItemDb( fromItem );

   m_inventoryMap[fromInventoryId]->removeItem( fromSlotId );
   updateContainer( fromInventoryId, fromSlotId, nullptr );

   auto invTransPacket = makeZonePacket< FFXIVIpcInventoryTransaction >( getId() );
   invTransPacket->data().transactionId = transactionId;
   invTransPacket->data().ownerId = getId();
   invTransPacket->data().storageId = fromInventoryId;
   invTransPacket->data().catalogId = fromItem->getId();
   invTransPacket->data().stackSize = fromItem->getStackSize();
   invTransPacket->data().slotId = fromSlotId;
   invTransPacket->data().type = 7;
   queuePacket( invTransPacket );

   auto invTransFinPacket = makeZonePacket< FFXIVIpcInventoryTransactionFinish >( getId() );
   invTransFinPacket->data().transactionId = transactionId;
   invTransFinPacket->data().transactionId1 = transactionId;
   queuePacket( invTransFinPacket );
}

uint16_t Core::Entity::Player::calculateEquippedGearItemLevel()
{
   uint32_t iLvlResult = 0;

   auto gearSetMap = m_inventoryMap[GearSet0]->getItemMap();

   auto it = gearSetMap.begin();

   while( it != gearSetMap.end() )
   {
      auto currItem = it->second;

      if( currItem )
      {
         iLvlResult += currItem->getItemLevel();

         // If item is weapon and isn't one-handed
         if( currItem->isWeapon() && !Items::Util::isOneHandedWeapon( currItem->getCategory() ) )
         {
            iLvlResult += currItem->getItemLevel();
         }
      }

      it++;
   }

   return boost::algorithm::clamp( iLvlResult / 13, 0, 9999 );
}


uint8_t Core::Entity::Player::getFreeSlotsInBags()
{
   uint8_t slots = 0;
   for( uint8_t container : { 0, 1, 2, 3 } )
   {
      // TODO: this feels hackish at best
      slots += 34 - m_inventoryMap[container]->getEntryCount();
   }
   return slots;
}
