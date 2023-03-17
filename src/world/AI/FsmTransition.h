#include <cstdint>
#include <ForwardsZone.h>
#include <Actor/BNpc.h>
#include "FsmCondition.h"

#pragma once

namespace Sapphire::World::AI
{
  class FsmTransition
  {
  public:
    FsmTransition( FsmStatePtr targetState, FsmConditionPtr condition ) : m_pTargetState( targetState ), m_pCondition( condition ) { }
    virtual ~FsmTransition() = default;

    FsmStatePtr getTargetState() { return m_pTargetState; }
    bool hasTriggered( Entity::BNpc& bnpc ) { return m_pCondition->isConditionMet( bnpc ); }
  private:
    FsmStatePtr m_pTargetState;
    FsmConditionPtr m_pCondition;
  };
}