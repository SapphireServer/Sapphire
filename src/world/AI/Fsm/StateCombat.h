#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "State.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class StateCombat : public State
  {
  private:
    uint64_t m_lastTick{ 0 };
    uint64_t m_lastMoveTime{ 0 };
    uint64_t m_lastRotTime{ 0 };
  public:
    virtual ~StateCombat() = default;

    void onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount ) override;
    void onEnter( Entity::GameObjectPtr& pEntity ) override;
    void onExit( Entity::GameObjectPtr& pEntity ) override;

  };
}