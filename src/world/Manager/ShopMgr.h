#include "ForwardsZone.h"
#include "BaseManager.h"

namespace Sapphire::World::Manager
{
  class ShopMgr : public Manager::BaseManager
  {
  public:
    ShopMgr( FrameworkPtr pFw );
    bool purchaseGilShopItem( Sapphire::Entity::Player& player, uint32_t shopId, uint16_t itemId, uint32_t quantity );
  };
}