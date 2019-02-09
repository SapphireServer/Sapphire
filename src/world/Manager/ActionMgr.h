#ifndef SAPPHIRE_ACTIONMGR_H
#define SAPPHIRE_ACTIONMGR_H

#include "BaseManager.h"
#include "ForwardsZone.h"

namespace Sapphire::Data
{
  struct Action;
  using ActionPtr = std::shared_ptr< Action >;
}

namespace Sapphire::World::Manager
{
  class ActionMgr : public Manager::BaseManager
  {
  public:
    explicit ActionMgr( FrameworkPtr pFw );
    ~ActionMgr() = default;

    void handleTargetedPlayerAction( Entity::Player& player, uint8_t type, uint32_t actionId,
                                     Data::ActionPtr actionData, uint64_t targetId );
    void handleAoEPlayerAction( Entity::Player& player, uint8_t type, uint32_t actionId,
                                Data::ActionPtr actionData, Common::FFXIVARR_POSITION3 pos );

  private:
    void bootstrapAction( Entity::Player& player, Action::ActionPtr currentAction, Data::Action& actionData );
    bool canPlayerUseAction( Entity::Player& player, Action::Action& currentAction, Data::Action& actionData );
  };
}

#endif //SAPPHIRE_ACTIONMGR_H
