#include "InventoryMgr.h"

#include <Common.h>
#include "Actor/Player.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/Item.h"
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacketNew.h>

using namespace Sapphire::Network::Packets;

void Sapphire::World::Manager::InventoryMgr::sendInventoryContainer( Sapphire::Entity::Player& player,
                                                                     Sapphire::ItemContainerPtr container,
                                                                     uint32_t sequence )
{
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
      itemInfoPacket->data().spiritBond = 0;
      itemInfoPacket->data().hqFlag = itM->second->isHq() ? 1 : 0;
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