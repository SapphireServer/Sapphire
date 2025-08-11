#pragma once

#include <cstdint>

#include "TimelineActorState.h"
#include "Timepoint.h"

namespace Sapphire
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
    BNpcHasFlags,

    GetAction,
    ScheduleActive
  };

  class Schedule : public std::enable_shared_from_this< Schedule >
  {
  public:
    // todo: getters/setters
    std::string m_name;
    std::vector< Timepoint > m_timepoints;
    std::string m_description;

    void execute( ConditionState& state, TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const;

    void reset( ConditionState& state ) const;

    bool completed( const ConditionState& state ) const;
  };
  using SchedulePtr = std::shared_ptr< Schedule >;

  class ScheduleCondition : public std::enable_shared_from_this< ScheduleCondition >
  {
  protected:
    ConditionType m_conditionType{ 0 };
    Schedule m_schedule;
    std::string m_description;
    uint32_t m_cooldown{ 0 };
    bool m_loop{ false };
    bool m_enabled{ true };
    uint32_t m_id{ 0 };

  public:
    ScheduleCondition() {}
    ~ScheduleCondition() {}

    virtual void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors )
    {
      this->m_conditionType = condition;
      this->m_loop = json.at( "loop" ).get< bool >();
      //this->m_cooldown = json.at( "cooldown" ).get< uint32_t >();
      this->m_schedule = phase;
      this->m_description = json.at( "description" ).get< std::string >();
      this->m_enabled = json.at( "enabled" ).get< bool >();
      this->m_id = json.at( "id" ).get< uint32_t >();
    }

    const std::string& getScheduleName()
    {
      return m_schedule.m_name;
    }

    void execute( ConditionState& state, TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
    {
      m_schedule.execute( state, self, pack, pEncounter, time );
    };

    void update( ConditionState& state, TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
    {
      m_schedule.execute( state, self, pack, pEncounter, time );
    }

    void setEnabled( ConditionState& state, bool enabled )
    {
      state.m_enabled = enabled;
    }

    void reset( ConditionState& state, bool toDefaults = false ) const
    {
      state.m_startTime = 0;

      if( toDefaults )
        state.m_enabled = isDefaultEnabled();

      m_schedule.reset( state );
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
      return m_schedule.completed( state );
    }

    bool isLoopable() const
    {
      return m_loop;
    }

    bool loopReady( ConditionState& state, uint64_t time ) const
    {
      return m_schedule.completed( state ) && m_loop && ( state.m_startTime + m_cooldown <= time );
    }

    virtual bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
    {
      return false;
    };

    uint32_t getId() const
    {
      return m_id;
    }
  };
  using ScheduleConditionPtr = std::shared_ptr< ScheduleCondition >;

  //
  // Conditions
  //
  class ConditionHp : public ScheduleCondition
  {
  public:
    uint32_t m_layoutId;
    union
    {
      uint8_t val;
      struct
      {
        uint8_t min, max;
      };
    } m_hp;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;

    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionDirectorVar : public ScheduleCondition
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
    } m_param;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionEncounterTimeElapsed : public ScheduleCondition
  {
  public:
    uint64_t m_duration;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionCombatState : public ScheduleCondition
  {
  public:
    uint32_t m_layoutId;
    CombatStateType m_combatState;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionBNpcFlags : public ScheduleCondition
  {
  public:
    uint32_t m_layoutId;
    uint32_t m_flags;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionGetAction : public ScheduleCondition
  {
  public:
    uint32_t m_layoutId;
    uint32_t m_actionId;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionScheduleActive : public ScheduleCondition
  {
  public:
    std::string m_actorName;
    std::string m_scheduleName;

    void from_json( nlohmann::json& json, Schedule& phase, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( ConditionState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

}// namespace Sapphire::Encounter