#pragma once

#include <cstdint>

#include "TimelineActorState.h"
#include "Timepoint.h"

namespace Sapphire::Encounter
{
  // todo: just use the actual combat state return type
  enum class CombatStateType
  {
    Idle,
    Combat,
    Retreat,
    Roaming,
    JustDied,
    Dead
  };

  enum class ConditionType : uint32_t
  {
    HpPctLessThan,
    HpPctBetween,

    DirectorVarEquals,
    DirectorVarGreaterThan,
    DirectorSeqEquals,
    DirectorSeqGreaterThan,
    DirectorFlagsEquals,
    DirectorFlagsGreaterThan,

    EncounterTimeElapsed,
    CombatState,
    BNpcHasFlags
  };

  class Phase : public std::enable_shared_from_this< Phase >
  {
  public:
    // todo: getters/setters
    std::string m_name;
    std::vector< Timepoint > m_timepoints;

    void execute( ConditionState& state, TimelineActor& self, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const;

    void reset( ConditionState& state ) const;

    bool completed( const ConditionState& state ) const;
  };
  using PhasePtr = std::shared_ptr< Phase >;

  class PhaseCondition : public std::enable_shared_from_this< PhaseCondition >
  {
  protected:
    ConditionType m_conditionType{ 0 };
    Phase m_phase;
    std::string m_description;
    uint32_t m_cooldown{ 0 };
    bool m_loop{ false };
    bool m_enabled{ true };
    uint32_t m_id{ 0 };

  public:
    PhaseCondition() {}
    ~PhaseCondition() {}

    virtual void from_json( nlohmann::json& json, Phase& phase, ConditionType condition )
    {
      this->m_conditionType = condition;
      this->m_loop = json.at( "loop" ).get< bool >();
      //this->m_cooldown = json.at( "cooldown" ).get< uint32_t >();
      this->m_phase = phase;
      this->m_description = json.at( "description" ).get< std::string >();
      this->m_enabled = json.at( "enabled" ).get< bool >();
      this->m_id = json.at( "id" ).get< uint32_t >();
    }

    void execute( ConditionState& state, TimelineActor& self, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
    {
      state.m_startTime = time;
      m_phase.execute( state, self, pack, pTeri, time );
    };

    void update( ConditionState& state, TimelineActor& self, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
    {
      m_phase.execute( state, self, pack, pTeri, time );
    }

    void setEnabled( ConditionState& state, bool enabled )
    {
      state.m_enabled = enabled;
    }

    void reset( ConditionState& state ) const
    {
      state.m_startTime = 0;
      state.m_enabled = isDefaultEnabled();
      m_phase.reset( state );
    }

    bool inProgress( const ConditionState& state ) const
    {
      return state.m_startTime != 0;
    }

    // todo: better naming
    bool isStateEnabled( const ConditionState& state ) const
    {
      return state.m_enabled;
    }

    bool isDefaultEnabled() const
    {
      return m_enabled;
    }

    bool completed( const ConditionState& state ) const
    {
      return m_phase.completed( state );
    }

    bool isLoopable() const
    {
      return m_loop;
    }

    bool loopReady( ConditionState& state, uint64_t time ) const
    {
      return m_phase.completed( state ) && m_loop && ( state.m_startTime + m_cooldown <= time );
    }

    virtual bool isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
    {
      return false;
    };

    uint32_t getId() const
    {
      return m_id;
    }
  };
  using PhaseConditionPtr = std::shared_ptr< PhaseCondition >;

  //
  // Conditions
  //
  class ConditionHp : PhaseCondition
  {
  public:
    uint32_t layoutId;
    union
    {
      uint8_t val;
      struct
      {
        uint8_t min, max;
      };
    } hp;

    void from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
                    const std::unordered_map< std::string, TimelineActor >& actors );

    bool isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const override;
  };

  class ConditionDirectorVar : PhaseCondition
  {
  public:
    union
    {
      struct
      {
        uint32_t index;
        uint32_t value;
      };
      uint8_t seq;
      uint8_t flags;
    } param;

    void from_json( nlohmann::json& json, Phase& phase, ConditionType condition );
    bool isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const override;
  };

  class ConditionEncounterTimeElapsed : PhaseCondition
  {
  public:
    uint64_t duration;

    void from_json( nlohmann::json& json, Phase& phase, ConditionType condition );
    bool isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const override;
  };

  class ConditionCombatState : PhaseCondition
  {
  public:
    uint32_t layoutId;
    CombatStateType combatState;

    void from_json( nlohmann::json& json, Phase& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors );
    bool isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const override;
  };

  class ConditionBNpcFlags : PhaseCondition
  {
  public:
    uint32_t layoutId;
    uint32_t flags;

    void from_json( nlohmann::json& json, Phase& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors );
    bool isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const override;
  };

}// namespace Sapphire::Encounter