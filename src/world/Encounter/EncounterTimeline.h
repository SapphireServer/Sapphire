#include <fstream>
#include <memory>
#include <map>
#include <optional>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>

#include <Common.h>
#include <Forwards.h>
#include <nlohmann/json.hpp>

namespace Sapphire
{
  class EncounterTimeline
  {
  public:
    // forwards
    class TimelineActor;

    // EncounterFight::OnTick() { switch EncounterTimepointConditionId }
    enum class ConditionId : uint32_t
    {
      HpPctLessThan,
      HpPctBetween,
      DirectorVarEquals,
      DirectorVarGreaterThan,
      DirectorSeqEquals,
      DirectorSeqGreaterThan,
      DirectorFlagsEquals,
      DirectorFlagsGreaterThan,
      PhaseTimeElapsed,
      EncounterTimeElapsed,
      CombatState
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

    enum class TargetSelectFilterId : uint32_t
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

    enum class MoveType : uint32_t
    {
      WalkPath,
      Teleport
    };

    enum class TimelineActorType : uint32_t
    {
      LayerSetObject,
      BattleNpc
    };

    enum class CombatStateType
    {
      Idle,
      Combat,
      Retreat,
      Roaming,
      JustDied,
      Dead
    };

    enum class TimelinePackType : uint32_t
    {
      Solo,
      EncounterFight
    };

    struct TargetSelectFilter
    {
      TargetSelectFilterId m_flags;
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
      TimepointData( TimepointDataType type ) : m_type( type ) {}
      virtual ~TimepointData(){};
      TimepointDataType m_type{ 0 };
    };
    using TimepointDataPtr = std::shared_ptr< TimepointData >;

    struct TimepointDataIdle : public TimepointData
    {
      uint32_t m_actorId;
      uint64_t m_durationMs;

      TimepointDataIdle( uint32_t actorId, uint64_t durationMs ) :
        TimepointData( TimepointDataType::Idle ),
        m_actorId( actorId ),
        m_durationMs( durationMs )
      {
      } 
    };

    struct TimepointDataAddStatusEffect : public TimepointData
    {
      uint32_t m_statusEffectId;
      TargetSelectFilter m_targetFilter;
      uint32_t m_durationMs;

      TimepointDataAddStatusEffect( uint32_t statusId, TargetSelectFilter targFilter, uint32_t durationMs ) :
        TimepointData( TimepointDataType::AddStatusEffect ),
        m_statusEffectId( statusId ),
        m_targetFilter( targFilter ),
        m_durationMs( durationMs )
      {
      } 
    };

    struct TimepointDataRemoveStatusEffect : public TimepointData
    {
      uint32_t m_statusEffectId;
      TargetSelectFilter m_targetFilter;

      TimepointDataRemoveStatusEffect( uint32_t statusId, TargetSelectFilter targFilter ) :
        TimepointData( TimepointDataType::RemoveStatusEffect ),
        m_statusEffectId( statusId ),
        m_targetFilter( targFilter )
      {
      }
    };

    struct TimepointDataAction : public TimepointData
    {
      uint32_t m_actorId;
      uint32_t m_actionId;
      TimepointCallbacks m_callbacks;

      TimepointDataAction( uint32_t actorId, uint32_t actionId, TimepointCallbacks callbacks ) :
        TimepointData( TimepointDataType::CastAction ),
        m_actorId( actorId ),
        m_actionId( actionId ),
        m_callbacks( callbacks )
      {
      }
    };

    struct TimepointDataMoveTo : public TimepointData
    {
      uint32_t m_actorId;
      MoveType m_moveType;
      float m_x, m_y, m_z, m_rot;

      TimepointDataMoveTo( uint32_t actorId, MoveType moveType, float x, float y, float z, float rot ) :
        TimepointData( TimepointDataType::MoveTo ),
        m_actorId( actorId ),
        m_moveType( moveType ),
        m_x( x ), m_y( y ), m_z( z ), m_rot( rot )
      {
      }
    };


    struct TimepointDataLogMessage : public TimepointData
    {
      uint32_t m_messageId;
      uint32_t m_params[ 6 ]{ 0 };

      TimepointDataLogMessage( uint32_t messageId, std::vector< uint32_t > params ) :
        TimepointData( TimepointDataType::LogMessage ),
        m_messageId( messageId )
      {
        for( auto i = 0; i < params.size(); ++i )
          m_params[i] = params[i];
      }
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

    // todo: refactor all this to allow solo actor to use
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

      const TimepointDataPtr getData() const
      {
        return m_pData;
      }

      bool canExecute( uint64_t elapsed )
      {
        return m_executeTime == 0 && m_duration <= elapsed;
      }

      bool finished( uint64_t time )
      {
        return m_executeTime + m_duration <= time;
      }

      void from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor >& actors, uint32_t selfLayoutId );
      void execute( EncounterFightPtr pFight, uint64_t time );
    };

    class Phase :
      public std::enable_shared_from_this< Phase >
    {
    public:

      // todo: respect looping phases, allow callbacks to push timepoints

      std::string m_name;
      std::vector< Timepoint > m_timepoints;
      uint32_t m_lastTimepointIndex{ 0 };
      uint64_t m_startTime{ 0 };
      uint64_t m_lastTimepointTime{ 0 };

      std::queue< Timepoint > m_executed;

      // todo: i wrote this very sleep deprived, ensure it is actually sane
      void execute( EncounterFightPtr pFight, uint64_t time )
      {
        if( m_startTime == 0 )
          m_startTime = time;
        if( m_lastTimepointTime == 0 )
          m_lastTimepointTime = time;

        for( auto i = m_lastTimepointIndex; i < m_timepoints.size();  )
        {
          uint64_t phaseElapsed = time - m_startTime;
          uint64_t timepointElapsed = time - m_lastTimepointTime;
          
          auto& timepoint = m_timepoints[ i ];
          if( timepoint.canExecute( timepointElapsed ) )
          {
            timepoint.execute( pFight, time );
            m_lastTimepointTime = time;
            m_executed.push( timepoint );
          }

          // fire off all timepoints 
          if( timepoint.finished( timepointElapsed ) )
          {
            // todo: this is stupid, temp workaround for allowing phases to loop
            timepoint.m_executeTime = 0;
            m_lastTimepointIndex = i;
            ++i;
            continue;
          }
          break;
        }
      }

      bool completed()
      {
        return m_timepoints.size() == 0;
      }
    };
    using PhasePtr = std::shared_ptr< Phase >;

    class PhaseCondition :
      public std::enable_shared_from_this< PhaseCondition >
    {
    public:
      ConditionId m_conditionId{ 0 };
      Phase m_phase;
      bool m_loop{ false };
      uint64_t m_startTime{ 0 };
      uint32_t m_cooldown{ 0 };
      std::string m_description;

      PhaseCondition() {}
      ~PhaseCondition() {}

      virtual void from_json( nlohmann::json& json, Phase phase, ConditionId conditionId )
      {
        this->m_conditionId = conditionId;
        this->m_loop = json.at( "loop" ).get< bool >();
        //this->m_cooldown = json.at( "cooldown" ).get< uint32_t >();
        this->m_phase = phase;
      }

      void execute( EncounterFightPtr pFight, uint64_t time )
      {
        m_startTime = time;
        m_phase.execute( pFight, time );
      };

      void update( EncounterFightPtr pFight, uint64_t time )
      {
        m_phase.execute( pFight, time );
      }

      void reset()
      {
        m_startTime = 0;
      }

      bool inProgress()
      {
        return m_startTime != 0;
      }

      bool completed()
      {
        return m_phase.completed();
      }

      bool isLoopable()
      {
        return m_loop;
      }

      bool loopReady( uint64_t time )
      {
        return m_phase.completed() && m_loop && ( m_startTime + m_cooldown <= time );
      }

      virtual bool isConditionMet( EncounterFightPtr pFight, uint64_t time )
      {
        return false;
      };

    };
    using PhaseConditionPtr = std::shared_ptr< PhaseCondition >;

    class TimelineActor
    {
    public:
      uint32_t m_layoutId{ 0 };
      uint32_t m_hp{ 0 };
      std::string m_name;

      std::vector< PhaseConditionPtr > m_phaseConditions;
      std::queue< PhaseConditionPtr > m_phaseHistory;

      void update( EncounterFightPtr pFight, uint64_t time )
      {
        // todo: handle auto attacks and make it so they dont fire during boss intermission phases
        // todo: handle interrupts
        for( const auto& pCondition : m_phaseConditions )
        {
          if( pCondition->completed() )
          {
            if( pCondition->isLoopable() )
            {
              if( pCondition->loopReady( time ) )
                pCondition->reset();
            }
          }
          else if( pCondition->inProgress() )
          {
            pCondition->update( pFight, time );
          }
          else if( pCondition->isConditionMet( pFight, time ) )
          {
            pCondition->execute( pFight, time );
            m_phaseHistory.push( pCondition );
          }
        }
      }
    };

    class TimelinePack
    {
      TimelinePackType m_type{TimelinePackType::Solo};
      std::vector< TimelineActor > m_actors;
      std::string m_name;

    public:
      TimelinePack() { }
      TimelinePack( TimelinePackType type ) : m_type( type ) {}
      void update( EncounterFightPtr pFight, uint64_t time )
      {
        for( auto& actor : m_actors )
          actor.update( pFight, time );
      }
    };

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

      void from_json( nlohmann::json& json, Phase phase, ConditionId conditionId,
        const std::unordered_map< std::string, TimelineActor >& actors );

      bool isConditionMet( EncounterFightPtr pFight, uint64_t time ) override;
    };

    class ConditionDirectorVar : PhaseCondition
    {
    public:
      union
      {
        struct
        {
          uint32_t var;
          uint32_t value;
        };
        uint8_t seq;
        uint8_t flag;
      } param;

      void from_json( nlohmann::json& json, Phase phase, ConditionId conditionId );
      bool isConditionMet( EncounterFightPtr pFight, uint64_t time ) override;
    };

    class ConditionCombatState : PhaseCondition
    {
    public:
      uint32_t layoutId;
      CombatStateType combatState;

      void from_json( nlohmann::json& json, Phase phase, ConditionId conditionId, const std::unordered_map< std::string, TimelineActor >& actors );
      bool isConditionMet( EncounterFightPtr pFight, uint64_t time ) override;
    };

  public:

    TimelinePack buildEncounterTimeline( uint32_t encounterId, bool reload = false );
  };
}// namespace Sapphire