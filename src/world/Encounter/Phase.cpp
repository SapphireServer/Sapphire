#include "Phase.h"
#include "Phase.h"

#include "Encounter/Encounter.h"

#include "Schedule.h"
#include "TimelineActor.h"
#include "TimelineActorState.h"
#include "Trigger.h"
#include "TriggerCondition.h"

namespace Sapphire
{
  void Phase::from_json( const nlohmann::json& json )
  {
    auto id = json.at( "id" ).get< uint32_t >();
    auto name = json.at( "name" ).get< std::string >();

    m_id = id;
    m_name = name;
  }

  uint32_t Phase::getId() const
  {
    return m_id;
  }

  const std::string& Phase::getName() const
  {
    return m_name;
  }

  void Phase::onEnter( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time )
  {
    // fire off everything for onEnter
    for( const auto& timepoint : m_onEnter )
      timepoint.execute( self, pack, pEncounter, time );

    state.m_scheduleInfo.clear();
  }

  void Phase::onExit( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time )
  {
    // fire off everything for onEnter
    for( const auto& timepoint : m_onExit )
      timepoint.execute( self, pack, pEncounter, time );

    state.m_scheduleInfo.clear();
  }

  void Phase::update( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time )
  {
    for( const auto& [ id, schedule ] : m_schedules )
    {
      schedule.execute( self, pack, state, pEncounter, time );
    }
  }

  const std::map< uint32_t, Trigger >& Phase::getTriggers() const
  {
    return m_triggers;
  }

  void Phase::addSchedule( uint32_t id, const Schedule& schedule )
  {
    m_schedules.emplace( id, schedule );
  }

  void Phase::addTimepointOnEnter( const Timepoint& timepoint )
  {
    m_onEnter.emplace_back( timepoint );
  }

  void Phase::addTimepointOnExit( const Timepoint& timepoint )
  {
    m_onExit.emplace_back( timepoint );
  }

  void Phase::addTrigger( const Trigger& trigger )
  {
    m_triggers.emplace( trigger.getId(), trigger );
  }
};