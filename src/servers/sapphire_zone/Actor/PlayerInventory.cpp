#include <Common.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>

#include "Zone/Zone.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

#include "Inventory/Inventory.h"
#include "Inventory/Item.h"

#include "Player.h"
#include "Framework.h"

extern Core::Framework g_framework;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::InventoryPtr Core::Entity::Player::getInventory() const
{
   return m_pInventory;
}

void Core::Entity::Player::sendItemLevel()
{
   queuePacket( ActorControlPacket142( getId(), SetItemLevel, getItemLevel(), 0 ) );
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
void Core::Entity::Player::equipItem( Inventory::EquipSlot equipSlotId, ItemPtr pItem, bool sendUpdate )
{

   //g_framework.getLogger().debug( "Equipping into slot " + std::to_string( equipSlotId ) );

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

   if( sendUpdate )
   { 
      this->sendModel();
      m_itemLevel = getInventory()->calculateEquippedGearItemLevel();
      sendItemLevel();
   }
}

void Core::Entity::Player::unequipItem( Inventory::EquipSlot equipSlotId, ItemPtr pItem )
{
   m_modelEquip[static_cast< uint8_t >( equipSlotId )] = 0;
   sendModel();

   m_itemLevel = getInventory()->calculateEquippedGearItemLevel();
   sendItemLevel();
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

   ZoneChannelPacket< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
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

   ZoneChannelPacket< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
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

   ZoneChannelPacket< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
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

   ZoneChannelPacket< FFXIVIpcUpdateInventorySlot > invUpPacket( getId() );
   invUpPacket.data().containerId = Inventory::InventoryType::Crystal;
   invUpPacket.data().catalogId = static_cast< uint8_t >( type ) + 1;
   invUpPacket.data().quantity = m_pInventory->getCrystal( static_cast< Inventory::CrystalType >( type ) );
   invUpPacket.data().slot = static_cast< uint8_t >( type ) - 1;

   queuePacket( invUpPacket );
}

bool Core::Entity::Player::tryAddItem( uint16_t catalogId, uint32_t quantity )
{

   for( uint16_t i = 0; i < 4; i++ )
   {
      if( m_pInventory->addItem( i, -1, catalogId, quantity ) != -1 )
         return true;
   }
   return false;
}

bool Core::Entity::Player::addItem( uint16_t containerId, uint16_t catalogId, uint32_t quantity )
{
   if( m_pInventory->addItem( containerId, -1, catalogId, quantity ) != -1 )
      return true;

   return false;
}

void Core::Entity::Player::sendInventory() const
{
   m_pInventory->send();
}

