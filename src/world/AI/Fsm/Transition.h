#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "AI/Fsm/Condition.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class Transition
  {
  public:
    Transition( StatePtr targetState, ConditionPtr condition ) : m_pTargetState( targetState ), m_pCondition( condition ) { }
    virtual ~Transition() = default;

    StatePtr getTargetState() { return m_pTargetState; }
    bool hasTriggered( Entity::BNpc& bnpc ) { return m_pCondition->isConditionMet( bnpc ); }
  private:
    StatePtr m_pTargetState;
    ConditionPtr m_pCondition;
  };
}