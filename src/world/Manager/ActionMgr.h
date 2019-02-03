#ifndef SAPPHIRE_ACTIONMGR_H
#define SAPPHIRE_ACTIONMGR_H

#include "BaseManager.h"
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{
  class ActionMgr : public Manager::BaseManager
  {
  public:
    explicit ActionMgr( FrameworkPtr pFw );
    ~ActionMgr() = default;

    void handleTargetedPlayerAction( Entity::Player& player, uint8_t type, uint32_t actionId, uint64_t targetId );
    void handleAoEPlayerAction( Entity::Player& player, uint8_t type, uint32_t actionId, Common::FFXIVARR_POSITION3 pos );
  };
}

#endif //SAPPHIRE_ACTIONMGR_H
