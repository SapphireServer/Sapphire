#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "Actor/GameObject.h"
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
    bool hasTriggered( Entity::GameObjectPtr& pObject ) { return m_pCondition->isConditionMet( pObject ); }
  private:
    StatePtr m_pTargetState;
    ConditionPtr m_pCondition;
  };
}