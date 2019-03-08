#include "InventoryMgr.h"

#include <Common.h>
#include "Actor/Player.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/HousingItem.h"
#include "Manager/ItemMgr.h"
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacket.h>

#include <Database/DatabaseDef.h>
#include <Exd/ExdDataGenerated.h>

#include "Framework.h"

using namespace Sapphire::Network::Packets;

Sapphire::World::Manager::InventoryMgr::InventoryMgr( Sapphire::FrameworkPtr pFw ) :
  BaseManager( pFw )
{ }

void Sapphire::World::Manager::InventoryMgr::sendInventoryContainer( Sapphire::Entity::Player& player,
                                                                     Sapphire::ItemContainerPtr container )
{
  auto sequence = player.getNextInventorySequence();
  auto pMap = container->getItemMap();

  for( auto itM = pMap.begin(); itM != pMap.end(); ++itM )
  {
    if( !itM->second )
      return;

    if( container->getId() == Common::InventoryType::Currency || container->getId() == Common::InventoryType::Crystal )
    {
      auto currencyInfoPacket = makeZonePacket< Server::FFXIVIpcCurrencyCrystalInfo >( player.getId() );
      currencyInfoPacket->data().containerSequence = sequence;
      currencyInfoPacket->data().catalogId = itM->second->getId();
      currencyInfoPacket->data().unknown = 1;
      currencyInfoPacket->data().quantity = itM->second->getStackSize();
      currencyInfoPacket->data().containerId = container->getId();
      currencyInfoPacket->data().slot = 0;

      player.queuePacket( currencyInfoPacket );
    }
    else
    {
      auto itemInfoPacket = makeZonePacket< Server::FFXIVIpcItemInfo >( player.getId() );
      itemInfoPacket->data().containerSequence = sequence;
      itemInfoPacket->data().containerId = container->getId();
      itemInfoPacket->data().slot = itM->first;
      itemInfoPacket->data().quantity = itM->second->getStackSize();
      itemInfoPacket->data().catalogId = itM->second->getId();
      itemInfoPacket->data().condition = itM->second->getDurability();
      itemInfoPacket->data().spiritBond = itM->second->getSpiritbond();
      itemInfoPacket->data().reservedFlag = itM->second->getReservedFlag();
      itemInfoPacket->data().hqFlag = static_cast< uint8_t >( itM->second->isHq() ? 1 : 0 );
      itemInfoPacket->data().stain = itM->second->getStain();

      player.queuePacket( itemInfoPacket );
    }
  }

  auto containerInfoPacket = makeZonePacket< Server::FFXIVIpcContainerInfo >( player.getId() );
  containerInfoPacket->data().containerSequence = sequence;
  containerInfoPacket->data().numItems = container->getEntryCount();
  containerInfoPacket->data().containerId = container->getId();

  player.queuePacket( containerInfoPacket );
}

Sapphire::ItemPtr Sapphire::World::Manager::InventoryMgr::createItem( Entity::Player& player,
                                                                      uint32_t catalogId, uint32_t quantity )
{
  auto pExdData = framework()->get< Data::ExdDataGenerated >();
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto itemMgr = framework()->get< Manager::ItemMgr >();
  auto itemInfo = pExdData->get< Sapphire::Data::Item >( catalogId );

  if( !itemInfo )
    return nullptr;

  auto item = make_Item( itemMgr->getNextUId(), catalogId, framework() );

  item->setStackSize( std::max< uint32_t >( 1, quantity ) );

  saveItem( player, item );

  return item;
}

void Sapphire::World::Manager::InventoryMgr::saveHousingContainer( Common::LandIdent ident,
                                                                   Sapphire::ItemContainerPtr container )
{
  auto u64ident = *reinterpret_cast< uint64_t* >( &ident );

  for( auto& item : container->getItemMap() )
  {
    saveHousingContainerItem( u64ident, container->getId(), item.first, item.second->getUId() );
  }
}

void Sapphire::World::Manager::InventoryMgr::removeItemFromHousingContainer( Sapphire::Common::LandIdent ident,
                                                                             uint16_t containerId,
                                                                             uint16_t slotId )
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::LAND_INV_DEL );

  auto u64ident = *reinterpret_cast< uint64_t* >( &ident );

  stmt->setUInt64( 1, u64ident );
  stmt->setUInt( 2, containerId );
  stmt->setUInt( 3, slotId );

  pDb->directExecute( stmt );
}

void Sapphire::World::Manager::InventoryMgr::saveHousingContainerItem( uint64_t ident,
                                                                       uint16_t containerId, uint16_t slotId,
                                                                       uint64_t itemId )
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::LAND_INV_UP );
  // LandIdent, ContainerId, SlotId, ItemId, ItemId

  stmt->setUInt64( 1, ident );
  stmt->setUInt( 2, containerId );
  stmt->setUInt( 3, slotId );
  stmt->setUInt64( 4, itemId );

  // see query, we have to pass itemid in twice
  // the second time is for the ON DUPLICATE KEY UPDATE condition
  stmt->setUInt64( 5, itemId );

  pDb->directExecute( stmt );
}

void Sapphire::World::Manager::InventoryMgr::updateHousingItemPosition( Sapphire::Inventory::HousingItemPtr item )
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::LAND_INV_UP_ITEMPOS );
  // ItemId, PosX, PosY, PosZ, Rotation, PosX, PosY, PosZ, Rotation

  auto pos = item->getPos();
  auto rot = item->getRot();

  stmt->setUInt64( 1, item->getUId() );

  stmt->setUInt( 2, pos.x );
  stmt->setUInt( 3, pos.y );
  stmt->setUInt( 4, pos.z );
  stmt->setInt( 5, rot );

  stmt->setUInt( 6, pos.x );
  stmt->setUInt( 7, pos.y );
  stmt->setUInt( 8, pos.z );
  stmt->setInt( 9, rot );

  pDb->execute( stmt );
}

void Sapphire::World::Manager::InventoryMgr::removeHousingItemPosition( Sapphire::Inventory::HousingItem& item )
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDb->getPreparedStatement( Db::LAND_INV_DEL_ITEMPOS );

  stmt->setUInt64( 1, item.getUId() );

  pDb->directExecute( stmt );
}

void Sapphire::World::Manager::InventoryMgr::saveItem( Sapphire::Entity::Player& player, Sapphire::ItemPtr item )
{
  auto pDb = framework()->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto stmt = pDb->getPreparedStatement( Db::CHARA_ITEMGLOBAL_INS );

  stmt->setUInt( 1, player.getId() );
  stmt->setUInt64( 2, item->getUId() );
  stmt->setUInt( 3, item->getId() );
  stmt->setUInt( 4, item->getStackSize() );

  pDb->directExecute( stmt );
}
