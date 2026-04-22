#include "Trigger.h"

#include "Encounter/Encounter.h"
#include "Timepoint.h"
#include "TimelineActor.h"

#include "Logging/Logger.h"
#include "spdlog/fmt/fmt.h"

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
        auto pPhase = self.getPhaseById( m_pAction->m_phaseId );
        // make sure the phase exists, die if not so we don't miss this bug
        if( !pPhase )
        {
          auto msg = std::string( "Trigger::execute: Invalid Phase ID {0} for LayoutId {1}" );
          msg = fmt::format( msg, m_pAction->m_phaseId, self.getLayoutId() );
          Logger::error( msg );
          throw std::runtime_error( msg );
        }

        self.transitionPhase( pEncounter, pack, time, pPhase );
      }
      break;
      case TriggerAction::Type::FireTimepoint:
      {
        m_pAction->m_timepoint.execute( self, pack, pEncounter, time );
      }
      break;
      default:
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