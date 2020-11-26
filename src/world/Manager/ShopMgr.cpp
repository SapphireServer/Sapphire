#include "ShopMgr.h"

#include <Exd/ExdDataGenerated.h>
#include <Actor/Player.h>
#include <Common.h>
#include <Service.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Inventory/Item.h"
#include "Inventory/ItemContainer.h"

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

bool Sapphire::World::Manager::ShopMgr::purchaseGilShopItem( Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto gilShopItem = exdData.get< Data::GilShopItem >( shopId, itemId );
  if( !gilShopItem )
    return false;

  auto item = exdData.get< Data::Item >( gilShopItem->item );
  if( !item )
    return false;

  auto price = item->priceMid * quantity;

  if( player.getCurrency( Common::CurrencyType::Gil ) < price )
    return false;

  if( !player.addItem( gilShopItem->item, quantity ) )
    return false;

  player.removeCurrency( Common::CurrencyType::Gil, price );

  auto packet = makeZonePacket< FFXIVIpcShopMessage >( player.getId() );
  packet->data().shopId = shopId;
  packet->data().msgType = 1687;
  packet->data().unknown2 = 3;
  packet->data().itemId = gilShopItem->item;
  packet->data().amount = quantity;
  packet->data().price = price;
  packet->data().unknown6 = 0;
  packet->data().unknown7 = 0;
  player.queuePacket( packet );

  return true;
}

bool Sapphire::World::Manager::ShopMgr::shopSellItem( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t containerId, uint16_t slotId )
{
  auto item = player.getItemAt( containerId, slotId );
  if( item )
  {
    auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
    auto itemData = exdData.get< Data::Item >( item->getId() );
    if( itemData && !itemData->isIndisposable )
    {
      auto value = itemData->priceLow * item->getStackSize();
      player.dropInventoryItem( static_cast< Common::InventoryType >( containerId ), slotId );
      player.addCurrency( Common::CurrencyType::Gil, value );
      Entity::ShopBuyBackEntry entry =
      {
        item,
        item->getStackSize(),
        itemData->priceLow
      };
      player.addBuyBackItemForShop( shopId, entry );
      auto packet = makeZonePacket< FFXIVIpcShopMessage >( player.getId() );
      packet->data().shopId = shopId;
      packet->data().msgType = 1688;
      packet->data().unknown2 = 3;
      packet->data().itemId = item->getId();
      packet->data().amount = item->getStackSize();
      packet->data().price = value;
      packet->data().unknown6 = 0;
      packet->data().unknown7 = 0;
      player.queuePacket( packet );

      return true;
    }
  }
  return false;
}

bool Sapphire::World::Manager::ShopMgr::shopBuyBack( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t index )
{
  auto& buyBackList = player.getBuyBackListForShop( shopId );
  if( buyBackList.size() > index )
  {
    auto& entry = buyBackList[ index ];
    auto originalStack = entry.item->getStackSize();
    auto price = entry.pricePerItem * originalStack;
    if( player.getCurrency( Common::CurrencyType::Gil ) < price )
      return false;

    if( !player.addItem( entry.item ) )
      return false;

    player.removeCurrency( Common::CurrencyType::Gil, price );

    buyBackList.erase( buyBackList.begin() + index );

    auto packet = makeZonePacket< FFXIVIpcShopMessage >( player.getId() );
    packet->data().shopId = shopId;
    packet->data().msgType = 1689;
    packet->data().unknown2 = 3;
    packet->data().itemId = entry.item->getId();
    packet->data().amount = originalStack;
    packet->data().price = price;
    packet->data().unknown6 = 0;
    packet->data().unknown7 = 0;
    player.queuePacket( packet );

    return true;
  }
  return false;
}
