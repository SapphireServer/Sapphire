#include <fstream>
#include <memory>
#include <map>
#include <optional>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace Sapphire
{
  class EncounterTimeline
  {
  public:
    // EncounterFight::OnTick() { switch EncounterTimepointConditionId }
    enum class EncounterConditionId : uint32_t
    {
      HpPctLessThan,
      HpPctBetween,
      DirectorVarEquals,
      DirectorVarGreaterThan
    };

    // TODO: what should this do?
    enum class EncounterTimepointOverrideFlags
    {
      None,
      Invulnerable
    };

    enum class EncounterTimepointDataType : uint32_t
    {
      Idle,
      CastAction,
      MoveTo,
      LogMessage,
      BattleTalk,
      SetDirectorVar,
      AddStatusEffect,
      RemoveStatusEffect
    };

    enum class EncounterTimepointCallbackType : uint32_t
    {
      OnActionInit,
      OnActionStart,
      OnActionInterrupt,
      OnActionExecute
    };

    enum class TargetSelectFilterIds
    {
      Self,
      Tank,
      Healer,
      Dps,
      DpsMelee,
      DpsRanged,
      Furthest,

      Aggro1,
      Aggro2
    };

    enum class MoveType
    {
      WalkPath,
      Teleport
    };

    struct TargetSelectFilter
    {
      TargetSelectFilterIds m_flags;
    };


    // Generated Structures

    // Generated Callback Structure
    struct EncounterTimepointCallbackData :
      public std::enable_shared_from_this< EncounterTimepointCallbackData >
    {
      EncounterTimepointCallbackType m_type;
    };
    using EncounterTimepointCallbackDataPtr = std::shared_ptr< EncounterTimepointCallbackData >;
    using EncounterTimepointCallbacks = std::map< EncounterTimepointCallbackType, EncounterTimepointCallbackDataPtr >;


    // Generated State Objects
    struct EncounterTimepointData :
      public std::enable_shared_from_this< EncounterTimepointData >
    {
      EncounterTimepointDataType m_type;
    };
    using EncounterTimepointDataPtr = std::shared_ptr< EncounterTimepointData >;


    // Generated State Data Objects
    struct EncounterTimepointDataStatusEffect : EncounterTimepointData
    {
      uint32_t m_statusEffectId;
      TargetSelectFilter m_targetFilter;
      uint32_t m_durationMs;
    };

    struct EncounterTimepointDataAction : EncounterTimepointData
    {
      uint32_t m_actionId;
      EncounterTimepointCallbacks m_callbacks;
    };

    struct EncounterTimepointDataMoveTo : EncounterTimepointData
    {
      float x, y, z, rot;
    };

    struct EncounterTimepoint :
      public std::enable_shared_from_this< EncounterTimepoint >
    {
    public:
      EncounterTimepointDataType m_type;
      uint32_t m_duration;
      EncounterTimepointOverrideFlags m_overrideFlags;
      EncounterTimepointDataPtr m_pData;
      std::string m_description;

      // switch( m_type )
      virtual void execute( EncounterFightPtr pFight, uint64_t time );
    };
    using EncounterTimepointPtr = std::shared_ptr< EncounterTimepoint >;

    class EncounterPhase :
      public std::enable_shared_from_this< EncounterPhase >
    {
    public:
      std::string m_name;
      std::map< std::string, EncounterTimepointPtr > m_timepoints;
      uint64_t m_startTime{ 0 };
      uint64_t m_currTime{ 0 };
      void execute( EncounterFightPtr pFight, uint64_t time )
      {
        uint64_t durationMs = time - m_currTime;
        for( const auto& timepoint : m_timepoints )
          timepoint.second->execute( pFight, time );

        if( m_startTime == 0 )
          m_startTime = time;

        m_currTime = time;
      }
    };
    using EncounterPhasePtr = std::shared_ptr< EncounterPhase >;

    class EncounterTimepointCondition :
      public std::enable_shared_from_this< EncounterTimepointCondition >
    {
    public:
      EncounterConditionId m_conditionId{ 0 };
      EncounterPhasePtr m_pPhase{ nullptr };
      bool m_loop{ false };
      uint64_t m_startTime{ 0 };
      uint32_t m_cooldown{ 0 };

      EncounterTimepointCondition() {}
      ~EncounterTimepointCondition() {}

      virtual void from_json( nlohmann::json& json, EncounterPhasePtr pPhase, EncounterConditionId conditionId )
      {
        this->m_conditionId = conditionId;
        this->m_loop = json.at( "loop" ).get< bool >();
        this->m_cooldown = json.at( "cooldown" ).get< uint32_t >();
        this->m_pPhase = pPhase;
      }

      void execute( EncounterFightPtr pFight, uint64_t time )
      {
        m_startTime = time;
        m_pPhase->execute( pFight, time );
      };

      virtual bool canExecute( EncounterFightPtr pFight, uint64_t time )
      {
        return false;
      };

    };
    using EncounterTimepointConditionPtr = std::shared_ptr< EncounterTimepointCondition >;

    class EncounterConditionHp : EncounterTimepointCondition
    {
    public:
      uint32_t actorId;
      union
      {
        uint8_t val;
        struct
        {
          uint8_t min, max; 
        };
      } hp;

      void from_json( nlohmann::json& json, EncounterPhasePtr pPhase, EncounterConditionId conditionId );
      bool canExecute( EncounterFightPtr pFight, uint64_t time ) override;
    };

    class EncounterConditionDirectorVar : EncounterTimepointCondition
    {
    public:
      uint32_t directorVar;
      uint32_t value;

      void from_json( nlohmann::json& json, EncounterPhasePtr pPhase, EncounterConditionId conditionId );
      bool canExecute( EncounterFightPtr pFight, uint64_t time ) override;
    };

    using EncounterTimelineInfo = std::stack< EncounterTimepointConditionPtr >;

  public:

    EncounterTimelineInfo buildEncounterTimeline( uint32_t encounterId, bool reload = false );
  };
}// namespace Sapphire