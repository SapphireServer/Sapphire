#ifndef SAPPHIRE_PLAYERMGR_H
#define SAPPHIRE_PLAYERMGR_H

#include "ForwardsZone.h"
#include "BaseManager.h"

namespace Sapphire::World::Manager
{
class PlayerMgr : public Manager::BaseManager
  {
  public:
    PlayerMgr( FrameworkPtr pFw );

    void movePlayerToLandDestination( Sapphire::Entity::Player& player, uint32_t landId, uint16_t param = 0 );
  };
}

#endif // SAPPHIRE_PLAYERMGR_H