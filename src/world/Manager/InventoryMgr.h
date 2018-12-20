#ifndef SAPPHIRE_INVENTORYMGR_H
#define SAPPHIRE_INVENTORYMGR_H

#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{

  class InventoryMgr
  {
  public:
    void sendInventoryContainer( Sapphire::Entity::Player& player, Sapphire::ItemContainerPtr container );
  };

}

#endif //SAPPHIRE_INVENTORYMGR_H
