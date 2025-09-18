#pragma once
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{
  class ShopMgr
  {
  private:
    std::unordered_map< uint32_t, std::array< uint32_t, 40 > > m_shopItemPrices;

    void cacheShop( uint32_t shopId );
  public:
    ShopMgr() = default;

    uint32_t getShopItemPrices( uint32_t shopId, uint8_t index );

    bool purchaseBuybackItem( Sapphire::Entity::Player& player, uint32_t soldItemSlot, uint32_t quantity, uint32_t refund );
    bool purchaseGilShopItem( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity );
    bool sellGilShopItem( Sapphire::Entity::Player & player, uint16_t container, uint8_t fromSlot, uint16_t item, uint32_t quantity );
  };
}