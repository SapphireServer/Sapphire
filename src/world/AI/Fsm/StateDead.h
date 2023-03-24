#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "State.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class StateDead : public State
  {
  public:
    virtual ~StateDead() = default;

    void onUpdate( Entity::BNpc& bnpc, uint64_t tickCount );
    void onEnter( Entity::BNpc& bnpc );
    void onExit( Entity::BNpc& bnpc );

  };
}