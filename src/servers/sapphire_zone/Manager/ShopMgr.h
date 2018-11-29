#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{
  class ShopMgr
  {
  public:
    bool purchaseGilShopItem( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity );
  };
}