#pragma once

#include <map>
#include <memory>
#include <string>
#include <map>
#include <vector>

#include "Encounter/Forwards.h"

#include "TimelineActorState.h"

#include <nlohmann/json.hpp>

namespace Sapphire
{
  class Phase : public std::enable_shared_from_this< Phase >
  {
  private:
    uint32_t m_id;
    std::string m_name;
    std::vector< Timepoint > m_onEnter;
    std::vector< Timepoint > m_onExit;
    std::map< uint32_t, Schedule > m_schedules;
    std::map< uint32_t, Trigger > m_triggers;

  public:
    void from_json( const nlohmann::json& json );

    uint32_t getId() const;

    const std::string& getName() const;

    void update( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time );

    void onEnter( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time );

    void onExit( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time );

    const std::map< uint32_t, Trigger >& getTriggers() const;

    void addSchedule( uint32_t id, const Schedule& schedule );

    void addTimepointOnEnter( const Timepoint& timepoint );

    void addTimepointOnExit( const Timepoint& timepoint );

    void addTrigger( const Trigger& trigger );
  };
}// namespace Sapphire