#include "Trigger.h"

#include "Encounter/Encounter.h"
#include "Timepoint.h"
#include "TimelineActor.h"

namespace Sapphire
{
  uint32_t Trigger::getId() const
  {
    return m_id;
  }

  void Trigger::setId( uint32_t id )
  {
    m_id = id;
  }

  void Trigger::setAction( const TriggerActionPtr& pAction )
  {
    m_pAction = pAction;
  }

  void Trigger::setCondition( const TriggerConditionPtr& pCondition )
  {
    m_pCondition = pCondition;
  }

  void Trigger::setDefaultEnabled( bool enabled )
  {
    m_enabled = enabled;
  }

  bool Trigger::getDefaultEnabled() const
  {
    return m_enabled;
  }

  bool Trigger::isEnabled( PhaseState& state ) const
  {
    return state.m_triggerStates[ m_id ];
  }

  bool Trigger::isConditionMet( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time ) const
  {
    return m_pCondition->isConditionMet( state, pack, pEncounter, time );
  }

  void Trigger::execute( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time ) const
  {
    switch( m_pAction->m_type )
    {
      case TriggerAction::Type::TransitionPhase:
      {
        self.transitionPhase( pEncounter, pack, time, self.getPhaseById( m_pAction->m_phaseId ) );
      }
      break;
      case TriggerAction::Type::FireTimepoint:
      {
        m_pAction->m_timepoint.execute( self, pack, pEncounter, time );
      }
      break;
    }
    // only fire once
    setEnabled( state, false );
  }

  void Trigger::setEnabled( PhaseState& state, bool enabled ) const
  {
    state.m_triggerStates[ m_id ] = enabled;
  }

  uint32_t Trigger::getTransitionPhaseId() const
  {
    return m_pAction->m_phaseId;
  }
};