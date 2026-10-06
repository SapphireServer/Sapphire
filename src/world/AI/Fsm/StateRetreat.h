#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "State.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class StateRetreat : public State
  {
  public:
    virtual ~StateRetreat() = default;

    void onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount );
    void onEnter( Entity::GameObjectPtr& pEntity );
    void onExit( Entity::GameObjectPtr& pEntity );

  };
}