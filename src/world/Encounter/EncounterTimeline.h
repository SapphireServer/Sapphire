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
    class TimelinePack;

    struct TimepointState
    {
      uint64_t m_startTime{ 0 };
      uint64_t m_lastTick{ 0 };
      bool m_finished{ false };
    };

    struct ConditionState
    {
      uint64_t m_startTime{ 0 };
      bool m_loop{ false };
      bool m_completed{ false };

      struct
      {
        uint64_t m_startTime{ 0 };
        uint64_t m_lastTimepointTime{ 0 };
        uint32_t m_lastTimepointIndex{ 0 };

        std::vector< TimepointState > m_timepointStates;
      } m_phaseInfo;
    };

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

      EncounterTimeElapsed,
      CombatState,
      BNpcHasFlags
    };

    enum class DirectorOpId
    {
      SetDirectorVar,
      SetDirectorVarLR,
      SetDirectorSeq,
      SetDirectorFlag,
      ClearDirector
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
      SetDirectorVarLR,
      SetDirectorSeq,
      SetDirectorFlag,

      AddStatusEffect,
      RemoveStatusEffect,

      SetBNpcFlags,
      SetEObjState,
      SetBgm
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


    using TimepointCallbackFunc = std::function< void( InstanceContentPtr, uint64_t ) >;
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
      uint32_t m_layoutId;
      uint64_t m_durationMs;

      TimepointDataIdle( uint32_t layoutId, uint64_t durationMs ) :
        TimepointData( TimepointDataType::Idle ),
        m_layoutId( layoutId ),
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
      uint32_t m_layoutId;
      uint32_t m_actionId;
      TimepointCallbacks m_callbacks;

      TimepointDataAction( uint32_t layoutId, uint32_t actionId, TimepointCallbacks callbacks ) :
        TimepointData( TimepointDataType::CastAction ),
        m_layoutId( layoutId ),
        m_actionId( actionId ),
        m_callbacks( callbacks )
      {
      }
    };

    struct TimepointDataMoveTo : public TimepointData
    {
      uint32_t m_layoutId;
      MoveType m_moveType;
      float m_x, m_y, m_z, m_rot;

      TimepointDataMoveTo( uint32_t layoutId, MoveType moveType, float x, float y, float z, float rot ) :
        TimepointData( TimepointDataType::MoveTo ),
        m_layoutId( layoutId ),
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
      DirectorOpId m_directorOp{ 0 };
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
      } m_data{ 0 };

      TimepointDataDirector( TimepointDataType type ) :
        TimepointData( type )
      {
        switch( type )
        {
          case TimepointDataType::SetDirectorVar:
            m_directorOp = DirectorOpId::SetDirectorVar;
            break;
          case TimepointDataType::SetDirectorVarLR:
            m_directorOp = DirectorOpId::SetDirectorVarLR;
            break;
          case TimepointDataType::SetDirectorFlag:
            m_directorOp = DirectorOpId::SetDirectorFlag;
            break;
          case TimepointDataType::SetDirectorSeq:
            m_directorOp = DirectorOpId::SetDirectorSeq;
            break;
        }
      }
    };

    struct TimepointDataBNpcFlags : public TimepointData
    {
      uint32_t m_layoutId;
      uint32_t m_flags;

      TimepointDataBNpcFlags( uint32_t layoutId, uint32_t flags ) :
        TimepointData( TimepointDataType::SetBNpcFlags ),
        m_layoutId( layoutId ),
        m_flags( flags )
      {
      }
    };

    struct TimepointDataEObjState : public TimepointData
    {
      uint32_t m_eobjId{ 0xE0000000 };
      uint32_t m_state{ 0 };

      TimepointDataEObjState( uint32_t eobjId, uint32_t state ) :
        TimepointData( TimepointDataType::SetEObjState ),
        m_eobjId( eobjId ),
        m_state( state )
      {
      }
    };

    struct TimepointDataBGM : public TimepointData
    {
      uint32_t m_bgmId{ 0 };

      TimepointDataBGM( uint32_t bgmId ):
        TimepointData( TimepointDataType::SetBgm ),
        m_bgmId( bgmId )
      {
      }
    };

    // todo: refactor all this to allow solo actor to use
    class Timepoint :
      public std::enable_shared_from_this< Timepoint >
    {
    public:
      TimepointDataType m_type;
      uint64_t m_duration{ 0 };
      TimepointOverrideFlags m_overrideFlags;
      TimepointDataPtr m_pData;
      std::string m_description;

      // todo: repeatable?

      const TimepointDataPtr getData() const
      {
        return m_pData;
      }

      bool canExecute( TimepointState& state, uint64_t elapsed ) const
      {
        return state.m_startTime == 0; // & &m_duration <= elapsed;
      }

      bool finished( TimepointState& state, uint64_t time ) const
      {
        return state.m_startTime + m_duration <= time || state.m_finished;
      }

      void reset( TimepointState& state ) const
      {
        state.m_startTime = 0;
        state.m_lastTick = 0;
        state.m_finished = false;
      }

      void from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor >& actors, uint32_t selfLayoutId );
      // todo: separate execute/update into onStart and onTick?
      void update( TimepointState& state, InstanceContentPtr pInstance, uint64_t time ) const;
      void execute( TimepointState& state, InstanceContentPtr pInstance, uint64_t time ) const;
    };

    class Phase :
      public std::enable_shared_from_this< Phase >
    {
    public:

      // todo: respect looping phases, allow callbacks to push timepoints

      std::string m_name;
      std::vector< Timepoint > m_timepoints;

      // todo: i wrote this very sleep deprived, ensure it is actually sane
      void execute( ConditionState& state, InstanceContentPtr pInstance, uint64_t time ) const
      {
        if( state.m_startTime == 0 )
          state.m_startTime = time;
        if( state.m_phaseInfo.m_startTime == 0 )
          state.m_phaseInfo.m_startTime = time;
        if( state.m_phaseInfo.m_lastTimepointTime == 0 )
          state.m_phaseInfo.m_lastTimepointTime = time;

        for( auto i = state.m_phaseInfo.m_lastTimepointIndex; i < m_timepoints.size();  )
        {
          uint64_t phaseElapsed = time - state.m_phaseInfo.m_startTime;
          uint64_t timepointElapsed = time - state.m_phaseInfo.m_lastTimepointTime;

          auto& tpState = state.m_phaseInfo.m_timepointStates[ i ];
          auto& timepoint = m_timepoints[ i ];
          if( timepoint.canExecute( tpState, timepointElapsed ) )
          {
            timepoint.execute( tpState, pInstance, time );
            state.m_phaseInfo.m_lastTimepointTime = time;
          }
          else if( !timepoint.finished( tpState, timepointElapsed ) )
          {
            timepoint.update( tpState, pInstance, time );
          }

          if( timepoint.finished( tpState, timepointElapsed ) )
          {
            timepoint.reset( tpState );
            // make sure this timepoint isnt run again unless phase loops
            ++i;
            state.m_phaseInfo.m_lastTimepointIndex = i;

            if( i == m_timepoints.size() )
            {
              state.m_phaseInfo.m_lastTimepointIndex++;
            }
            continue;
          }
          break;
        }
      }

      void reset( ConditionState& state ) const
      {
        state.m_phaseInfo.m_startTime = 0;
        state.m_phaseInfo.m_lastTimepointIndex = 0;
        state.m_phaseInfo.m_lastTimepointTime = 0;

        state.m_phaseInfo.m_timepointStates.clear();
        for( auto i = 0; i < m_timepoints.size(); ++i )
          state.m_phaseInfo.m_timepointStates.push_back( {} );
      }

      bool completed( ConditionState& state ) const
      {
        return state.m_phaseInfo.m_lastTimepointIndex > m_timepoints.size();
      }
    };
    using PhasePtr = std::shared_ptr< Phase >;

    class PhaseCondition :
      public std::enable_shared_from_this< PhaseCondition >
    {
    protected:
      ConditionId m_conditionId{ 0 };
      Phase m_phase;
      std::string m_description;
      uint32_t m_cooldown{ 0 };
      bool m_loop{ false };
    public:
      PhaseCondition() {}
      ~PhaseCondition() {}

      virtual void from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId )
      {
        this->m_conditionId = conditionId;
        this->m_loop = json.at( "loop" ).get< bool >();
        //this->m_cooldown = json.at( "cooldown" ).get< uint32_t >();
        this->m_phase = phase;
        this->m_description = json.at( "description" ).get< std::string >();
      }

      void execute( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
      {
        state.m_startTime = time;
        m_phase.execute( state, pInstance, time );
      };

      void update( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
      {
        m_phase.execute( state, pInstance, time );
      }

      void reset( ConditionState& state ) const
      {
        state.m_startTime = 0;
        m_phase.reset( state );
      }

      bool inProgress( ConditionState& state ) const
      {
        return state.m_startTime != 0;
      }

      bool completed( ConditionState& state ) const
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

      virtual bool isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
      {
        return false;
      };

    };
    using PhaseConditionPtr = std::shared_ptr< PhaseCondition >;

    class TimelineActor
    {
    protected:
      std::vector< PhaseConditionPtr > m_phaseConditions;
      std::queue< PhaseConditionPtr > m_phaseHistory;
      std::vector< ConditionState > m_conditionStates;
    public:
      uint32_t m_layoutId{ 0 };
      uint32_t m_hp{ 0 };
      std::string m_name;

      void addPhaseCondition( PhaseConditionPtr pCondition )
      {
        m_phaseConditions.push_back( pCondition );
        m_conditionStates.push_back( {} );
      }

      // todo: make this sane and pass info down
      void update( InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time )
      {
        // todo: handle auto attacks and make it so they dont fire during boss intermission phases
        // todo: handle interrupts
        for( auto i = 0; i < m_phaseConditions.size(); ++i )
        {
          const auto& pCondition = m_phaseConditions[ i ];
          auto& state = m_conditionStates[ i ];

          if( pCondition->completed( state ) )
          {
            if( pCondition->isLoopable() )
            {
              if( pCondition->loopReady( state, time ) )
                pCondition->reset( state );
            }
          }
          else if( pCondition->inProgress( state ) )
          {
            pCondition->update( state, pInstance, pack, time );
          }
          else if( pCondition->isConditionMet( state, pInstance, pack, time ) )
          {
            pCondition->execute( state, pInstance, pack, time );
            m_phaseHistory.push( pCondition );
          }
        }
      }
    };

    // todo: actually handle solo stuff properly (or tie to zone director/content director at least)
    class TimelinePack
    {
      TimelinePackType m_type{TimelinePackType::Solo};
      std::vector< TimelineActor > m_actors;
      std::string m_name;

      uint64_t m_startTime{ 0 };
    public:
      TimelinePack() { }
      TimelinePack( TimelinePackType type ) : m_type( type ) {}

      void setStartTime( uint64_t time )
      {
        m_startTime = time;
      }

      uint64_t getStartTime() const
      {
        return m_startTime;
      }

      void update( InstanceContentPtr pInstance, uint64_t time )
      {
        for( auto& actor : m_actors )
          actor.update( pInstance, *this, time );
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

      void from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId,
        const std::unordered_map< std::string, TimelineActor >& actors );

      bool isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const override;
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

      void from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId );
      bool isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const override;
    };

    class ConditionEncounterTimeElapsed : PhaseCondition
    {
    public:
      uint64_t duration;

      void from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId );
      bool isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const override;
    };

    class ConditionCombatState : PhaseCondition
    {
    public:
      uint32_t layoutId;
      CombatStateType combatState;

      void from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId, const std::unordered_map< std::string, TimelineActor >& actors );
      bool isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const override;
    };

    class ConditionBNpcFlags : PhaseCondition
    {
    public:
      uint32_t layoutId;
      uint32_t flags;

      void from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId, const std::unordered_map< std::string, TimelineActor >& actors );
      bool isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const override;
    };

  public:

    TimelinePack buildEncounterTimeline( uint32_t encounterId, bool reload = false );
  };
}// namespace Sapphire