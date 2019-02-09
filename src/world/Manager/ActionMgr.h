#ifndef SAPPHIRE_ACTIONMGR_H
#define SAPPHIRE_ACTIONMGR_H

#include "BaseManager.h"
#include "ForwardsZone.h"

namespace Sapphire::Data
{
  class Action;
  using ActionPtr = std::shared_ptr< Action >;
}

namespace Sapphire::World::Manager
{
  class ActionMgr : public Manager::BaseManager
  {
  public:
    explicit ActionMgr( FrameworkPtr pFw );
    ~ActionMgr() = default;

    void handleTargetedPlayerAction( Entity::Player& player, uint8_t type, Data::ActionPtr action, uint64_t targetId );
    void handleAoEPlayerAction( Entity::Player& player, uint8_t type, Data::ActionPtr action, Common::FFXIVARR_POSITION3 pos );
  };
}

#endif //SAPPHIRE_ACTIONMGR_H
