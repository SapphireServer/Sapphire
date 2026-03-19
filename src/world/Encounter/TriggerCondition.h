#pragma once

#include <cstdint>

#include "Encounter/Forwards.h"

#include "Encounter/Encounter.h"

#include "TimelinePack.h"
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
    PhaseActive,
    InterruptedAction,

    VarEquals
  };

  class TriggerCondition : public std::enable_shared_from_this< TriggerCondition >
  {
  protected:
    ConditionType m_conditionType{ 0 };
    std::string m_description;
    uint32_t m_id{ 0 };

  public:
    TriggerCondition() {}
    ~TriggerCondition() {}

    uint32_t getId() const
    {
      return m_id;
    }

    const std::string& getDescription() const
    {
      return m_description;
    }

    virtual void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors )
    {
      this->m_conditionType = condition;
      this->m_description = json.at( "description" ).get< std::string >();
      this->m_id = json.at( "id" ).get< uint32_t >();
    }

    virtual bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
    {
      return false;
    };

  };

  //
  // Conditions
  //
  class ConditionHp : public TriggerCondition
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

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;

    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionDirectorVar : public TriggerCondition
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

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionEncounterTimeElapsed : public TriggerCondition
  {
  public:
    uint64_t m_duration;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionCombatState : public TriggerCondition
  {
  public:
    uint32_t m_layoutId;
    CombatStateType m_combatState;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionBNpcFlags : public TriggerCondition
  {
  public:
    uint32_t m_layoutId;
    uint32_t m_flags;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionGetAction : public TriggerCondition
  {
  public:
    uint32_t m_layoutId;
    uint32_t m_actionId;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionPhaseActive : public TriggerCondition
  {
  public:
    std::string m_actorName;
    uint32_t m_phaseId;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionInterruptedAction : public TriggerCondition
  {
  public:
    uint32_t m_layoutId;
    uint32_t m_actionId;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

  class ConditionVarEquals : public TriggerCondition
  {
  public:
    uint32_t m_index;
    uint32_t m_val;

    VarType m_type;

    void from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors ) override;
    bool isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const override;
  };

}// namespace Sapphire