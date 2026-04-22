#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <unordered_map>

#include "Encounter/Forwards.h"
#include "Actor/BNpc.h"

#include "Phase.h"

#include "TimelineActorState.h"

#include <nlohmann/json.hpp>

namespace Sapphire
{
  enum class TimelineActorType : uint32_t
  {
    EventObject,
    BattleNpc
  };

  class TimelineActor
  {
  protected:
    std::map< uint32_t, PhasePtr > m_phases;
    // PARENTNAME_SUBACTOR_1, ..., PARENTNAME_SUBACTOR_69
    std::unordered_map< std::string, Entity::BNpcPtr > m_subActors;

    PhasePtr m_pPhase;

    TimelineActorState m_state;

  public:
    uint32_t m_layoutId{ 0 };
    uint32_t m_hp{ 0 };
    std::string m_name;
    uint32_t m_initialPhaseId{ 1 };

    TimelineActor() {}
    TimelineActor( const TimelineActor& rhs ) :
      m_layoutId( rhs.m_layoutId ),
      m_hp( rhs.m_hp ),
      m_name( rhs.m_name )
    {
      // yeah
      for( const auto& subActor : rhs.m_subActors )
        m_subActors.emplace( std::make_pair( subActor.first, nullptr ) );

      m_phases = rhs.m_phases;
    }

    void addPhase( PhasePtr pPhase );

    const std::string& getName() const;

    uint32_t getLayoutId() const;

    bool isPhaseActive( uint32_t phaseId ) const;

    PhasePtr getPhaseById( uint32_t phaseId );

    uint64_t getPhaseElapsed() const;

    // todo: make this sane
    void update( EncounterPtr pEncounter, TimelinePack& pack, uint64_t time );

    void transitionPhase( EncounterPtr pEncounter, TimelinePack& pack, uint64_t time, PhasePtr pPhase );

    void spawnAllSubActors( TerritoryPtr pTeri );

    void resetAllSubActors( TerritoryPtr pTeri );

    void setTriggerEnabled( uint32_t phaseId, uint32_t triggerId, bool enabled );

    // get self or subactor
    Entity::BNpcPtr getBNpcByRef( const std::string& name, TerritoryPtr pTeri ) const;

    // todo: i hate this but it's the only way to ref subactors while staying self contained
    void addPlaceholderSubactor( const std::string& name );

    Entity::BNpcPtr spawnSubActor( const std::string& name, TerritoryPtr pTeri );
    Entity::BNpcPtr getSubActor( const std::string& name ) const;
    void resetSubActors( TerritoryPtr pTeri );
  };
}