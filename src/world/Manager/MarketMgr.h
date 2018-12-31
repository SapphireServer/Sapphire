#ifndef SAPPHIRE_MARKETMGR_H
#define SAPPHIRE_MARKETMGR_H

#include "ForwardsZone.h"
#include "BaseManager.h"

namespace Sapphire::World::Manager
{
  class MarketMgr : public Manager::BaseManager
  {
  public:
    explicit MarketMgr( FrameworkPtr pFw );

    bool init();

    void searchMarketboard( Entity::Player& player, uint8_t itemSearchCategory, uint8_t maxEquipLevel, uint8_t classJob );

  };
}


#endif //SAPPHIRE_MARKETMGR_H
