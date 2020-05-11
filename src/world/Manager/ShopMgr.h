#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{
  class ShopMgr
  {
  public:
    ShopMgr() = default;
    bool purchaseGilShopItem( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity );
    bool shopSellItem( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t containerId, uint16_t slotId );
    bool shopBuyBack( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t index );
  };
}