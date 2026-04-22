#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "Encounter/Forwards.h"

#include "TimelineActorState.h"

#include <nlohmann/json.hpp>

namespace Sapphire
{
  class Schedule : public std::enable_shared_from_this< Schedule >
  {
  public:
    enum class LoopType : uint32_t
    {
      None,
      Infinite,
      Finite
    };

    // todo: getters/setters
    uint32_t m_id;
    std::string m_name;
    std::vector< Timepoint > m_timepoints;
    std::string m_description;
    uint32_t m_loopCount;
    LoopType m_loopType;

    void from_json( const nlohmann::json& json );

    void addTimepoint( const Timepoint& timepoint );

    void execute( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time ) const;

    void resetForLoop( PhaseState& state ) const;

    void reset( PhaseState& state ) const;

    bool completed( PhaseState& state ) const;
  };
};