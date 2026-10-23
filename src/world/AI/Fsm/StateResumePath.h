#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "State.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class StateResumePath : public State
  {
  public:
    virtual ~StateResumePath() = default;

    void onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount ) override;
    void onEnter( Entity::GameObjectPtr& pEntity ) override;
    void onExit( Entity::GameObjectPtr& pEntity ) override;

  };
}