#include "ShopMgr.h"

#include <Exd/ExdData.h>
#include <Actor/Player.h>
#include <Inventory/Item.h>
#include <Common.h>
#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;

void ShopMgr::cacheShop( uint32_t shopId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto itemShopList = exdData.getRows< Excel::Shop >();
  uint8_t count = 0;
  for( const auto& [ itemShop, shop ] : itemShopList )
  {
    if( shopId == itemShop )
    {
      for( auto shopItemId : shop->data().Item )
      {
        auto shopItem = exdData.getRow< Excel::ShopItem >( shopItemId );
        if( !shopItem )
          continue;

        auto item = exdData.getRow< Excel::Item >( shopItem->data().ItemId );
        if( !item || item->data().Price == 0 )
          continue;

        m_shopItemPrices[ shopId ][ count ] = item->data().Price;
        count++;
      }
      Logger::debug( "ShopMgr: cached itemShop {0} with {1} items", shopId, count );
      break;
    }
  }
}

uint32_t ShopMgr::getShopItemPrices( uint32_t shopId, uint8_t index )
{
  if( index > 40 )
    return 0;

  auto it = m_shopItemPrices.find( shopId );
  if( it != m_shopItemPrices.end() )
  {
    return it->second[ index ];
  }
  else
  {
    cacheShop( shopId );
    return getShopItemPrices( shopId, index );
  }

}

bool ShopMgr::purchaseBuybackItem( Entity::Player& player, uint32_t soldItemSlot, uint32_t quantity, uint32_t basePrice )
{
  auto soldItems = player.getSoldItems();

  if( !soldItems || soldItems->size() < soldItemSlot )
    return false;

  auto refund = basePrice * quantity;

  if( player.getCurrency( Common::CurrencyType::Gil ) < refund )
    return false;

  auto itemId = soldItems->at( soldItemSlot ).first;

  if( !player.addItem( itemId, quantity ) )
    return false;

  player.removeCurrency( Common::CurrencyType::Gil, refund );

  player.rebaseSoldItems( static_cast< size_t >( soldItemSlot ) );

  return true;
}

bool ShopMgr::purchaseGilShopItem( Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto item = exdData.getRow< Excel::Item >( itemId );
  if( !item )
    return false;

  auto price = item->data().Price * quantity;

  if( player.getCurrency( Common::CurrencyType::Gil ) < price )
    return false;

  if( !player.addItem( itemId, quantity ) )
    return false;

  player.removeCurrency( Common::CurrencyType::Gil, price );

  return true;
}

bool ShopMgr::sellGilShopItem( Entity::Player& player, uint16_t container, uint8_t fromSlot, uint16_t itemId, uint32_t quantity )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto item = exdData.getRow< Excel::Item >( itemId );
  if( !item )
    return false;

  auto payback = ( item->data().PriceMin ) * quantity;

  auto inventoryItem = player.getItemAt( container, fromSlot );

  // todo: adding stack remove
  //if( quantity > 1 )
  //  return false;

  player.discardItem( ( Common::InventoryType )container, fromSlot );
  player.addSoldItem( itemId, quantity );

  player.addCurrency( Common::CurrencyType::Gil, payback );

  return true;
}
