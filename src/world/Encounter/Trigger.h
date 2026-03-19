#pragma once

#include <memory>
#include <string>

#include "Encounter/Forwards.h"

#include "TriggerCondition.h"
#include "TimelineActorState.h"

#include <nlohmann/json.hpp>

namespace Sapphire
{
  
  class TriggerAction
  {
  public:
    enum class Type
    {
      TransitionPhase,
      FireTimepoint
    };

    Type m_type;
    uint32_t m_phaseId;
    Timepoint m_timepoint;
  };

  class Trigger : public std::enable_shared_from_this< Trigger >
  {
  private:
    uint32_t m_id;
    TriggerActionPtr m_pAction;
    TriggerConditionPtr m_pCondition;

    bool m_enabled{ true };
  public:
    uint32_t getId() const;
    void setId( uint32_t id );
    void setAction( const TriggerActionPtr& pAction );
    void setCondition( const TriggerConditionPtr& pCondition );

    bool isEnabled( PhaseState& state ) const;
    bool isConditionMet( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time ) const;
    void execute( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time ) const;
    void setEnabled( PhaseState& state, bool enabled ) const;

    uint32_t getTransitionPhaseId() const;
  };
}