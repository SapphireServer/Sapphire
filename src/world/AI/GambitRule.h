#include <cstdint>
#include <ForwardsZone.h>
#include "GambitTargetCondition.h"

#pragma once

namespace Sapphire::World::AI
{
  class GambitRule
  {
  public:
    GambitRule( GambitTargetConditionPtr targetCondition, Action::ActionPtr action, uint32_t coolDown );
    ~GambitRule() = default;

    bool isEnabled() const;
    void toggleEnabled();

    uint64_t getLastExecutionMs() const;
    void setLastExecutionMs( uint64_t lastExecution );

    uint32_t getCoolDown() const;

    GambitTargetConditionPtr getGambitTargetCondition();

    Action::ActionPtr getActionPtr();
  private:
    GambitTargetConditionPtr m_targetCondition;
    Action::ActionPtr m_pAction;
    uint32_t m_coolDownMs;
    uint64_t m_lastExecutionMs;
    bool m_isEnabled;
  };
}