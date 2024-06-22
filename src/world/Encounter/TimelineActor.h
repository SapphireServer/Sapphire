#pragma once

#include <cstdint>

#include "PhaseCondition.h"
#include "TimelineActorState.h"

namespace Sapphire::Encounter
{
  enum class TimelineActorType : uint32_t
  {
    LayerSetObject,
    BattleNpc
  };

  class TimelineActor
  {
  protected:
    std::unordered_map< uint32_t, PhaseConditionPtr > m_phaseConditions;
    std::unordered_map< uint32_t, ConditionState > m_conditionStates;

    // PARENTNAME_SUBACTOR_1, ..., PARENTNAME_SUBACTOR_69
    std::unordered_map< std::string, Entity::BNpcPtr > m_subActors;

  public:
    uint32_t m_layoutId{ 0 };
    uint32_t m_hp{ 0 };
    std::string m_name;

    TimelineActor() {}
    TimelineActor( const TimelineActor& rhs ) :
      m_layoutId( rhs.m_layoutId ),
      m_hp( rhs.m_hp ),
      m_name( rhs.m_name ),
      m_phaseConditions( rhs.m_phaseConditions )
    {
      // yeah
      for( const auto& subActor : rhs.m_subActors )
        m_subActors.emplace( std::make_pair( subActor.first, nullptr ) );

      m_conditionStates = rhs.m_conditionStates;
      for( const auto& state : rhs.m_phaseConditions )
        state.second->reset( m_conditionStates[ state.first ] );
    }

    void addPhaseCondition( PhaseConditionPtr pCondition );

    // todo: make this sane
    void update( TerritoryPtr pTeri, TimelinePack& pack, uint64_t time );

    void resetConditionState( uint32_t conditionId );

    void setConditionStateEnabled( uint32_t conditionId, bool enabled );

    void resetAllConditionStates();

    void spawnAllSubActors( TerritoryPtr pTeri );

    void resetAllSubActors( TerritoryPtr pTeri );

    // get self or subactor
    Entity::BNpcPtr getBNpcByRef( const std::string& name, TerritoryPtr pTeri ) const;

    // todo: i hate this but it's the only way to ref subactors while staying self contained
    void addPlaceholderSubactor( const std::string& name );

    Entity::BNpcPtr spawnSubActor( const std::string& name, TerritoryPtr pTeri );
    Entity::BNpcPtr getSubActor( const std::string& name ) const;
    void resetSubActors( TerritoryPtr pTeri );
  };
}