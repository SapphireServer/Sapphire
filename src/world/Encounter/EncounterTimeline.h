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

    //
    // State tracking objects (per actor)
    //
    // todo: move ConditionState/TimepointState to Chara::GambitState?

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
      bool m_enabled{ false };

      struct
      {
        uint64_t m_startTime{ 0 };
        uint64_t m_lastTimepointTime{ 0 };
        uint32_t m_lastTimepointIndex{ 0 };

        std::vector< TimepointState > m_timepointStates;
      } m_phaseInfo;
    };

    //
    // Enums
    // 
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
      Set, // idx = val
      Add, // idx += val
      Sub, // idx -= val
      Mul, // idx *= val
      Div, // idx /= val
      Mod, // idx %= val
      Sll, // idx << val
      Srl, // idx >> val
      Or,  // idx |= val
      Xor, // idx ^= val
      Nor, // idx ~= val
      And  // idx &= val
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

      DirectorVar,
      DirectorVarLR,
      DirectorSeq,
      DirectorFlags,

      AddStatusEffect,
      RemoveStatusEffect,

      SpawnBNpc,
      SetBNpcFlags,
      SetEObjState,
      SetBgm,

      SetCondition
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

    //
    // Timepoint.m_pData objects
    //
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
      uint32_t m_layoutId{ 0xE0000000 };
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
      uint32_t m_layoutId{ 0xE0000000 };
      uint32_t m_actionId;
      //TimepointCallbacks m_callbacks;

      TimepointDataAction( uint32_t layoutId, uint32_t actionId ) :
        TimepointData( TimepointDataType::CastAction ),
        m_layoutId( layoutId ),
        m_actionId( actionId )
        //m_callbacks( callbacks )
      {
      }
    };

    struct TimepointDataMoveTo : public TimepointData
    {
      uint32_t m_layoutId{ 0xE0000000 };
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
      uint32_t m_params[ 5 ]{ 0 };

      TimepointDataLogMessage( uint32_t messageId, const std::vector< uint32_t >& params ) :
        TimepointData( TimepointDataType::LogMessage ),
        m_messageId( messageId )
      {
        for( auto i = 0; i < params.size() && i < 5; ++i )
          m_params[i] = params[i];
      }
    };

    struct TimepointDataBattleTalk : public TimepointData
    {
      uint32_t m_battleTalkId;
      uint32_t m_handlerId;
      uint32_t m_kind;
      uint32_t m_nameId;
      uint32_t m_talkerId;

      uint32_t m_params[ 8 ]{ 0 };

      TimepointDataBattleTalk( const std::vector< uint32_t >& params ) :
        TimepointData( TimepointDataType::BattleTalk )
      {
        for( auto i = 0; i < params.size() && i < 8; ++i )
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

      TimepointDataDirector( TimepointDataType type, DirectorOpId op ) :
        TimepointData( type ),
        m_directorOp( op )
      {

      }
    };

    struct TimepointDataSpawnBNpc : public TimepointData
    {
      uint32_t m_layoutId{ 0xE0000000 };
      uint32_t m_flags{ 0 };
      // todo: hate type, source

      TimepointDataSpawnBNpc( uint32_t layoutId, uint32_t flags ) :
        TimepointData( TimepointDataType::SpawnBNpc ),
        m_layoutId( layoutId ),
        m_flags( flags)
      {
      }
    };

    struct TimepointDataBNpcFlags : public TimepointData
    {
      uint32_t m_layoutId{ 0xE0000000 };
      uint32_t m_flags{ 0 };

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

    struct TimepointDataCondition : public TimepointData
    {
      // todo: rng?
      uint32_t m_index;
      bool m_enabled;

      TimepointDataCondition( uint32_t index, bool enabled ) :
        TimepointData( TimepointDataType::SetCondition ),
        m_index( index ),
        m_enabled( enabled )
      {
      }
    };

    // todo: refactor all this to allow solo actor to use
    class Timepoint :
      public std::enable_shared_from_this< Timepoint >
    {
    public:
      TimepointDataType m_type;
      uint64_t m_duration{ 0 }; // milliseconds
      TimepointOverrideFlags m_overrideFlags;
      TimepointDataPtr m_pData;
      std::string m_description;

      // todo: repeatable?

      const TimepointDataPtr getData() const
      {
        return m_pData;
      }

      bool canExecute( const TimepointState& state, uint64_t elapsed ) const
      {
        return state.m_startTime == 0; // & &m_duration <= elapsed;
      }

      bool durationElapsed( uint64_t elapsed ) const
      {
        return m_duration < elapsed;
      }

      bool finished( const TimepointState& state, uint64_t elapsed ) const
      {
        return durationElapsed( elapsed ) || state.m_finished;
      }

      void reset( TimepointState& state ) const
      {
        state.m_startTime = 0;
        state.m_lastTick = 0;
        state.m_finished = false;
      }

      void from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor >& actors, uint32_t selfLayoutId );
      // todo: separate execute/update into onStart and onTick?
      void update( TimepointState& state, TimelineActor& self, InstanceContentPtr pInstance, uint64_t time ) const;
      void execute( TimepointState& state, TimelineActor& self, InstanceContentPtr pInstance, uint64_t time ) const;
    };

    class Phase :
      public std::enable_shared_from_this< Phase >
    {
    public:

      // todo: allow callbacks to push timepoints

      std::string m_name;
      std::vector< Timepoint > m_timepoints;

      // todo: i wrote this very sleep deprived, ensure it is actually sane
      void execute( ConditionState& state, TimelineActor& self, InstanceContentPtr pInstance, uint64_t time ) const
      {
        if( state.m_startTime == 0 )
          state.m_startTime = time;
        if( state.m_phaseInfo.m_startTime == 0 )
          state.m_phaseInfo.m_startTime = time;

        if( state.m_phaseInfo.m_lastTimepointTime == 0 )
        {
          state.m_phaseInfo.m_lastTimepointTime = time;
          state.m_phaseInfo.m_timepointStates.clear();
          state.m_phaseInfo.m_timepointStates.resize( m_timepoints.size() );
        }

        for( auto i = state.m_phaseInfo.m_lastTimepointIndex; i < m_timepoints.size();  )
        {
          uint64_t phaseElapsed = time - state.m_phaseInfo.m_startTime;
          uint64_t timepointElapsed = time - state.m_phaseInfo.m_lastTimepointTime;

          auto& tpState = state.m_phaseInfo.m_timepointStates[ i ];
          auto& timepoint = m_timepoints[ i ];

          if( timepoint.canExecute( tpState, timepointElapsed ) )
          {
            timepoint.execute( tpState, self, pInstance, time );
            state.m_phaseInfo.m_lastTimepointTime = time;
          }
          else if( !timepoint.finished( tpState, timepointElapsed ) )
          {
            timepoint.update( tpState, self, pInstance, time );
          }

          if( timepoint.durationElapsed( timepointElapsed ) && timepoint.finished( tpState, timepointElapsed ) )
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
        state.m_phaseInfo.m_timepointStates.resize( m_timepoints.size() );
      }

      bool completed( const ConditionState& state ) const
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
      bool m_enabled{ true };

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
        this->m_enabled = json.at( "enabled" ).get< bool >();
      }

      void execute( ConditionState& state, TimelineActor& self, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
      {
        state.m_startTime = time;
        m_phase.execute( state, self, pInstance, time );
      };

      void update( ConditionState& state, TimelineActor& self, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
      {
        m_phase.execute( state, self, pInstance, time );
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

      TimelineActor() { }
      TimelineActor( const TimelineActor& rhs ) :
        m_layoutId( rhs.m_layoutId ),
        m_hp( rhs.m_hp ),
        m_name( rhs.m_name ),
        m_phaseConditions( rhs.m_phaseConditions ),
        m_conditionStates( rhs.m_conditionStates )
      {

      }

      void addPhaseCondition( PhaseConditionPtr pCondition )
      {
        m_phaseConditions.push_back( pCondition );
        m_conditionStates.push_back( {} );
        m_conditionStates[ m_conditionStates.size() - 1 ].m_enabled = pCondition->isDefaultEnabled();
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

          // ignore if not enabled, unless overriden to enable
          if( !pCondition->isDefaultEnabled() && !pCondition->isStateEnabled( state ) )
            continue;

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
            pCondition->update( state, *this, pInstance, pack, time );
          }
          else if( pCondition->isConditionMet( state, pInstance, pack, time ) )
          {
            pCondition->execute( state, *this, pInstance, pack, time );
            m_phaseHistory.push( pCondition );

            if( pack.getStartTime() == 0 )
              pack.setStartTime( state.m_startTime );
          }
        }
      }

      void resetConditionState( uint32_t conditionIdx )
      {
        assert( conditionIdx < m_phaseConditions.size() );

        const auto& pCondition = m_phaseConditions[ conditionIdx ];
        auto& state = m_conditionStates[ conditionIdx ];

        pCondition->reset( state );
      }

      void setConditionStateEnabled( uint32_t conditionIdx, bool enabled )
      {
        assert( conditionIdx < m_conditionStates.size() );

        auto& state = m_conditionStates[ conditionIdx ];
        state.m_enabled = enabled;
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
      TimelinePack( const TimelinePack& rhs ) :
        m_type( rhs.m_type ),
        m_name( rhs.m_name ),
        m_actors( rhs.m_actors ),
        m_startTime( 0 )
      {

      }
      TimelinePack( TimelinePackType type ) : m_type( type ) {}

      void setName( const std::string& name )
      {
        m_name = name;
      }

      void addTimelineActor( const TimelineActor& actor )
      {
        m_actors.push_back( actor );
      }

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

    TimelinePack getEncounterPack( uint32_t encounterId, bool reload = false );
  };
}// namespace Sapphire