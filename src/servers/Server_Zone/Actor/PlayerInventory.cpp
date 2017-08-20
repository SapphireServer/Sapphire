#include <src/servers/Server_Common/Common.h>

#include "Player.h"

#include "src/servers/Server_Zone/Zone/ZoneMgr.h"
#include "src/servers/Server_Zone/Zone/Zone.h"

#include <src/servers/Server_Common/Network/GamePacket.h>

#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"

#include "src/servers/Server_Zone/Inventory/Inventory.h"
#include "src/servers/Server_Zone/Inventory/Item.h"

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::InventoryPtr Core::Entity::Player::getInvetory() const
{
   return m_pInventory;
}

// TODO: This has to be redone and simplified
void Core::Entity::Player::equipWeapon( Core::ItemPtr pItem )
{
   ClassJob currentClass = static_cast< ClassJob >( getClass() );

   switch( pItem->getCategory() )
   {
   case ItemCategory::PugWep:
      if( currentClass != ClassJob::CLASS_PUGILIST &&
          currentClass != ClassJob::JOB_MONK )
         setClassJob( ClassJob::CLASS_PUGILIST );
      break;
   case ItemCategory::GlaWep:
      if( currentClass != ClassJob::CLASS_GLADIATOR &&
          currentClass != ClassJob::JOB_KNIGHT )
         setClassJob( ClassJob::CLASS_GLADIATOR );
      break;
   case ItemCategory::MrdWep:
      if( currentClass != ClassJob::CLASS_MARAUDER &&
          currentClass != ClassJob::JOB_WARRIOR )
         setClassJob( ClassJob::CLASS_MARAUDER );
      break;
   case ItemCategory::ArcWep:
      if( currentClass != ClassJob::CLASS_ARCHER &&
          currentClass != ClassJob::JOB_BARD )
         setClassJob( ClassJob::CLASS_ARCHER );
      break;
   case ItemCategory::LncWep:
      if( currentClass != ClassJob::CLASS_LANCER &&
          currentClass != ClassJob::JOB_DRAGON )
         setClassJob( ClassJob::CLASS_LANCER );
      break;
   case ItemCategory::ThmWep:
   case ItemCategory::Thm2Wep:
      if( currentClass != ClassJob::CLASS_THAUMATURGE &&
          currentClass != ClassJob::JOB_BLACKMAGE )
         setClassJob( ClassJob::CLASS_THAUMATURGE );
      break;
   case ItemCategory::CnjWep:
   case ItemCategory::Cnj2Wep:
      if( currentClass != ClassJob::CLASS_CONJURER &&
          currentClass != ClassJob::JOB_WHITEMAGE )
         setClassJob( ClassJob::CLASS_CONJURER );
      break;
   case ItemCategory::ArnWep:
      if( currentClass != ClassJob::CLASS_ARCANIST &&
          currentClass != ClassJob::JOB_SUMMONER &&
          currentClass != ClassJob::JOB_SCHOLAR )
         setClassJob( ClassJob::CLASS_ARCANIST );
      break;
   default:
      break;
   }
}

// equip an item
void Core::Entity::Player::equipItem( Inventory::EquipSlot equipSlotId, Core::ItemPtr pItem, bool sendModel )
{

   //  Console->outDebOnly("Equipping into slot %i", equipSlotID);

   uint64_t model = pItem->getModelId1();
   uint64_t model2 = pItem->getModelId2();

   switch( equipSlotId )
   {
   case Inventory::EquipSlot::MainHand:
      m_modelMainWeapon = model;
      m_modelSubWeapon = model2;
      // TODO: add job change upon changing weapon if needed
      // equipWeapon( pItem );
      break;

   case Inventory::EquipSlot::OffHand:
      m_modelSubWeapon = model;
      break;

   case Inventory::EquipSlot::SoulCrystal:
      // TODO: add Job change on equipping crystal
      // change job
      break;

   default: // any other slot
      m_modelEquip[static_cast< uint8_t >( equipSlotId )] = static_cast< uint32_t >( model );
      break;

   }

   if( sendModel )
      this->sendModel();
}

void Core::Entity::Player::unequipItem( Inventory::EquipSlot equipSlotId, ItemPtr pItem )
{
   m_modelEquip[static_cast< uint8_t >( equipSlotId )] = 0;
   sendModel();
}

uint32_t Core::Entity::Player::getCurrency( uint8_t type ) const
{
   return m_pInventory->getCurrency( static_cast< Inventory::CurrencyType >( type ) );
}

// TODO: these next functions are so similar that they could likely be simplified
void Core::Entity::Player::addCurrency( uint8_t type, uint32_t amount )
{
   if( !m_pInventory->addCurrency( static_cast< Inventory::CurrencyType >( type ), amount ) )
      return;

   GamePacketNew< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
   invUpPacket.data().containerId = Inventory::InventoryType::Currency;
   invUpPacket.data().catalogId = 1;
   invUpPacket.data().quantity = m_pInventory->getCurrency( static_cast< Inventory::CurrencyType >( type ) );
   invUpPacket.data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}

void Core::Entity::Player::removeCurrency( uint8_t type, uint32_t amount )
{
   if( !m_pInventory->removeCurrency( static_cast< Inventory::CurrencyType >( type ), amount ) )
      return;

   GamePacketNew< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
   invUpPacket.data().containerId = Inventory::InventoryType::Currency;
   invUpPacket.data().catalogId = 1;
   invUpPacket.data().quantity = m_pInventory->getCurrency( static_cast< Inventory::CurrencyType >( type ) );
   invUpPacket.data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}


uint32_t Core::Entity::Player::getCrystal( uint8_t type ) const
{
   return m_pInventory->getCrystal( static_cast< Inventory::CrystalType >( type ) );
}

void Core::Entity::Player::addCrystal( uint8_t type, uint32_t amount )
{
   if( !m_pInventory->addCrystal( static_cast< Inventory::CrystalType >( type ), amount ) )
      return;

   GamePacketNew< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
   invUpPacket.data().containerId = Inventory::InventoryType::Crystal;
   invUpPacket.data().catalogId = static_cast< uint8_t >( type ) + 1;
   invUpPacket.data().quantity = m_pInventory->getCrystal( static_cast< Inventory::CrystalType >( type ) );
   invUpPacket.data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );

   queuePacket( ActorControlPacket143( getId(), ItemObtainIcon, static_cast< uint8_t >( type ) + 1, amount ) );
}

void Core::Entity::Player::removeCrystal( uint8_t type, uint32_t amount )
{
   if( !m_pInventory->removeCrystal( static_cast< Inventory::CrystalType >( type ), amount ) )
      return;

   GamePacketNew< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
   invUpPacket.data().containerId = Inventory::InventoryType::Crystal;
   invUpPacket.data().catalogId = static_cast< uint8_t >( type ) + 1;
   invUpPacket.data().quantity = m_pInventory->getCrystal( static_cast< Inventory::CrystalType >( type ) );
   invUpPacket.data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}

bool Core::Entity::Player::tryAddItem( uint16_t catalogId, uint16_t quantity )
{

   for( uint8_t i = 0; i < 4; i++ )
   {
      if( m_pInventory->addItem( i, -1, catalogId, quantity ) != -1 )
      {
         return true;
      }
   }
   return false;
}

bool Core::Entity::Player::addItem( uint16_t containerId, uint16_t catalogId, uint16_t quantity )
{
   if( m_pInventory->addItem( containerId, -1, catalogId, quantity ) != -1 )
      return true;

   return false;
}

void Core::Entity::Player::sendInventory() const
{
   m_pInventory->send();
}

