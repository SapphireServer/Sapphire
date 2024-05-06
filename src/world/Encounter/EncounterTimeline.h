#include <fstream>
#include <memory>
#include <map>
#include <optional>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>

#include <nlohmann/json.hpp>

namespace Sapphire
{
  class EncounterTimeline
  {
  public:
    // EncounterFight::OnTick() { switch EncounterTimepointConditionId }
    enum class ConditionId : uint32_t
    {
      HpPctLessThan,
      HpPctBetween,
      DirectorVarEquals,
      DirectorVarGreaterThan,
      PhaseTimeElapsed,
      EncounterTimeElapsed
    };

    enum class DirectorOpId
    {
      SetDirectorVar,
      SetDirectorVarLR,
      SetDirectorSeq,
      SetDirectorFlag,
      ClearDirectorFlag
    };

    // TODO: what should this do?
    enum class TimepointOverrideFlags : uint32_t
    {
      None,
      Invulnerable
    };

    enum class TimepointDataType : uint32_t
    {
      Idle,
      CastAction,
      MoveTo,
      LogMessage,
      BattleTalk,
      SetDirectorVar,
      SetDirectorSeq,
      SetDirectorFlag,
      AddStatusEffect,
      RemoveStatusEffect
    };

    enum class TimepointCallbackType : uint32_t
    {
      OnActionInit,
      OnActionStart,
      OnActionInterrupt,
      OnActionExecute
    };

    enum class TargetSelectFilterIds : uint32_t
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


    using TimepointCallbackFunc = std::function< void( EncounterFightPtr, uint64_t ) >;
    // Timepoint Data Objects
    struct TimepointCallbackData :
      public std::enable_shared_from_this< TimepointCallbackData >
    {
      TimepointCallbackType m_type;
      std::vector < TimepointCallbackFunc > m_callbacks;
    };
    using TimebackCallbackDataPtr = std::shared_ptr< TimepointCallbackData >;
    using TimepointCallbacks = std::map< TimepointCallbackType, TimebackCallbackDataPtr >;


    struct TimepointData :
      public std::enable_shared_from_this< TimepointData >
    {
      TimepointData( TimepointDataType) {}
      virtual ~TimepointData() = 0;
      TimepointDataType m_type;
    };
    using TimepointDataPtr = std::shared_ptr< TimepointData >;

    struct TimepointDataIdle : public TimepointData
    {
      uint32_t m_actorId;
      uint64_t m_durationMs;
    };

    struct TimepointDataStatusEffect : public TimepointData
    {
      uint32_t m_statusEffectId;
      TargetSelectFilter m_targetFilter;
      uint32_t m_durationMs;
    };

    struct TimepointDataAction : public TimepointData
    {
      uint32_t m_actorId;
      uint32_t m_actionId;
      TimepointCallbacks m_callbacks;
    };

    struct TimepointDataMoveTo : public TimepointData
    {
      uint32_t m_actorId;
      MoveType m_moveType;
      float m_x, m_y, m_z, m_rot;
    };


    struct TimepointDataLogMessage : public TimepointData
    {
      uint32_t m_logMessageType;
      uint32_t m_logMessageId;
      std::string m_message;
    };

    struct TimepointDataDirector : public TimepointData
    {
      DirectorOpId m_directorOp;
      union
      {
        struct
        {
          uint8_t index;
          union
          {
            uint8_t val;
            struct
            {
              uint8_t left, right;
            };
          } value;
        };
        uint8_t seq;
        uint8_t flags;
      } m_data;
    };

    class Timepoint :
      public std::enable_shared_from_this< Timepoint >
    {
    public:
      TimepointDataType m_type;
      uint64_t m_duration{ 0 };
      uint64_t m_executeTime{ 0 };
      TimepointOverrideFlags m_overrideFlags;
      TimepointDataPtr m_pData;
      std::string m_description;

      // todo: repeatable?

      bool canExecute()
      {
        return m_executeTime == 0;
      }

      bool finished( uint64_t time )
      {
        return m_executeTime + m_duration <= time;
      }

      void execute( EncounterFightPtr pFight, uint64_t time );
    };
    using TimepointPtr = std::shared_ptr< Timepoint >;

    class Phase :
      public std::enable_shared_from_this< Phase >
    {
    public:

      // todo: respect looping phases, allow callbacks to push timepoints

      std::string m_name;
      std::queue< TimepointPtr > m_timepoints;
      uint64_t m_startTime{ 0 };
      uint64_t m_lastTimepoint{ 0 };

      std::queue< TimepointPtr > m_executed;

      // todo: i wrote this very sleep deprived, ensure it is actually sane
      void execute( EncounterFightPtr pFight, uint64_t time )
      {
        if( m_startTime == 0 )
          m_startTime = time;
        if( m_lastTimepoint == 0 )
          m_lastTimepoint = time;

        // todo: this is stupid
        while( m_timepoints.size() > 0 )
        {
          uint64_t phaseElapsed = time - m_startTime;
          uint64_t timepointElapsed = time - m_lastTimepoint;

          auto& pTimepoint = m_timepoints.front();
          if( pTimepoint->canExecute() )
          {
            pTimepoint->execute( pFight, time );
            m_lastTimepoint = time;
            m_executed.push( pTimepoint );
          }
          else if( pTimepoint->finished( timepointElapsed ) )
          {
            // todo: this is stupid, temp workaround for allowing phases to loop
            pTimepoint->m_executeTime = 0;
            m_timepoints.pop();
          }
          else
          {
            break;
          }
        }
      }
    };
    using PhasePtr = std::shared_ptr< Phase >;

    class TimepointCondition :
      public std::enable_shared_from_this< TimepointCondition >
    {
    public:
      ConditionId m_conditionId{ 0 };
      PhasePtr m_pPhase{ nullptr };
      bool m_loop{ false };
      uint64_t m_startTime{ 0 };
      uint32_t m_cooldown{ 0 };

      TimepointCondition() {}
      ~TimepointCondition() {}

      virtual void from_json( nlohmann::json& json, PhasePtr pPhase, ConditionId conditionId )
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
    using TimepointConditionPtr = std::shared_ptr< TimepointCondition >;

    class ConditionHp : TimepointCondition
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

      void from_json( nlohmann::json& json, PhasePtr pPhase, ConditionId conditionId );
      bool canExecute( EncounterFightPtr pFight, uint64_t time ) override;
    };

    class ConditionDirectorVar : TimepointCondition
    {
    public:
      uint32_t directorVar;
      uint32_t value;

      void from_json( nlohmann::json& json, PhasePtr pPhase, ConditionId conditionId );
      bool canExecute( EncounterFightPtr pFight, uint64_t time ) override;
    };

    using EncounterTimelineInfo = std::queue< TimepointConditionPtr >;

  public:

    EncounterTimelineInfo buildEncounterTimeline( uint32_t encounterId, bool reload = false );
  };
}// namespace Sapphire