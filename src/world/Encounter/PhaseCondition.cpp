#include "PhaseCondition.h"

#include "EncounterTimeline.h"
#include "TimelineActor.h"
#include "TimelineActorState.h"

#include <Actor/Chara.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>

#include <Territory/Territory.h>
#include <Territory/InstanceContent.h>
#include <Territory/QuestBattle.h>

namespace Sapphire::Encounter
{
  bool ConditionHp::isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( layoutId );
    if( !pBNpc )
      return false;

    // todo: check time elapsed

    switch( m_conditionType )
    {
      case ConditionType::HpPctLessThan:
        return pBNpc->getHpPercent() < hp.val;
      case ConditionType::HpPctBetween:
      {
        auto hpPct = pBNpc->getHpPercent();
        return hpPct >= hp.min && hpPct <= hp.max;
      }
    }
    return false;
  };

  bool ConditionDirectorVar::isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {

    Event::DirectorPtr pDirector = pTeri->getAsInstanceContent();
    if( pDirector == nullptr )
      pDirector = pTeri->getAsQuestBattle();

    switch( m_conditionType )
    {
      case ConditionType::DirectorVarEquals:
        return pDirector->getDirectorVar( param.index ) == param.value;
      case ConditionType::DirectorVarGreaterThan:
        return pDirector->getDirectorVar( param.index ) > param.value;
      case ConditionType::DirectorFlagsEquals:
        return pDirector->getFlags() == param.flags;
      case ConditionType::DirectorFlagsGreaterThan:
        return pDirector->getFlags() > param.flags;
      case ConditionType::DirectorSeqEquals:
        return pDirector->getSequence() == param.seq;
      case ConditionType::DirectorSeqGreaterThan:
        return pDirector->getSequence() > param.seq;
    }
    return false;
  }

  bool ConditionCombatState::isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    auto pBattleNpc = pTeri->getActiveBNpcByLayoutId( this->layoutId );

    // todo: these should really use callbacks when the state transitions or we could miss this tick
    switch( combatState )
    {
      case CombatStateType::Idle:
        return pBattleNpc->getState() == Entity::BNpcState::Idle;
      case CombatStateType::Combat:
        return pBattleNpc->getState() == Entity::BNpcState::Combat;
      case CombatStateType::Retreat:
        return pBattleNpc->getState() == Entity::BNpcState::Retreat;
      case CombatStateType::Roaming:
        return pBattleNpc->getState() == Entity::BNpcState::Roaming;
      case CombatStateType::JustDied:
        return pBattleNpc->getState() == Entity::BNpcState::JustDied;
      case CombatStateType::Dead:
        return pBattleNpc->getState() == Entity::BNpcState::Dead;
      default:
        break;
    }
    return false;
  }

  bool ConditionEncounterTimeElapsed::isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    auto elapsed = time - pack.getStartTime();
    // todo: check encounter time
    return elapsed >= this->duration;
  }

  bool ConditionBNpcFlags::isConditionMet( ConditionState& state, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( this->layoutId );
    return pBNpc && pBNpc->hasFlag( this->flags );
  }

  void ConditionHp::from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
                                                  const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose hp we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionHp::from_json unable to find actor by name: %s" ), actorRef ) );

    switch( condition )
    {
      case ConditionType::HpPctLessThan:
        this->hp.val = paramData.at( "hp" ).get< uint32_t >();
        break;
      case ConditionType::HpPctBetween:
        this->hp.min = paramData.at( "hpMin" ).get< uint32_t >(),
        this->hp.max = paramData.at( "hpMax" ).get< uint32_t >();
        break;
      default:
        break;
    }
  }

  void ConditionDirectorVar::from_json( nlohmann::json& json, Phase& phase, ConditionType condition )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto& paramData = json.at( "paramData" );

    switch( condition )
    {
      case ConditionType::DirectorVarEquals:
      case ConditionType::DirectorVarGreaterThan:
      {
        param.index = paramData.at( "idx" ).get< uint32_t >();
        param.value = paramData.at( "val" ).get< uint32_t >();
      }
      break;
      case ConditionType::DirectorFlagsEquals:
      case ConditionType::DirectorFlagsGreaterThan:
      {
        param.flags = paramData.at( "flags" ).get< uint32_t >();
      }
      break;
      case ConditionType::DirectorSeqEquals:
      case ConditionType::DirectorSeqGreaterThan:
      {
        param.seq = paramData.at( "seq" ).get< uint32_t >();
      }
      break;
      default:
        break;
    }
  }

  void ConditionCombatState::from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
                                                           const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionCombatState::from_json unable to find actor by name: %s" ), actorRef ) );

    this->combatState = paramData.at( "combatState" ).get< CombatStateType >();
  }

  void ConditionEncounterTimeElapsed::from_json( nlohmann::json& json, Phase& phase, ConditionType condition )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto& paramData = json.at( "paramData" );
    auto duration = paramData.at( "duration" ).get< uint64_t >();

    this->duration = duration;
  }

  void ConditionBNpcFlags::from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
                                                         const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, condition );
    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionBNpcFlags::from_json unable to find actor by name: %s" ), actorRef ) );

    this->flags = json.at( "flags" ).get< uint32_t >();
    // todo: BNpcHasFlags
  }

  // todo: i wrote this very sleep deprived, ensure it is actually sane

  void Phase::execute( ConditionState& state, TimelineActor& self, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    if( state.m_startTime == 0 )
    {
      state.m_startTime = time;
      self.spawnAllSubActors( pTeri );
    }

    if( state.m_phaseInfo.m_startTime == 0 )
      state.m_phaseInfo.m_startTime = time;

    if( state.m_phaseInfo.m_lastTimepointTime == 0 )
    {
      state.m_phaseInfo.m_lastTimepointTime = time;
      state.m_phaseInfo.m_timepointStates.clear();
      state.m_phaseInfo.m_timepointStates.resize( m_timepoints.size() );
    }

    for( auto i = state.m_phaseInfo.m_lastTimepointIndex; i < m_timepoints.size(); )
    {
      uint64_t phaseElapsed = time - state.m_phaseInfo.m_startTime;
      uint64_t timepointElapsed = time - state.m_phaseInfo.m_lastTimepointTime;

      auto& tpState = state.m_phaseInfo.m_timepointStates[ i ];
      auto& timepoint = m_timepoints[ i ];

      if( timepoint.canExecute( tpState, timepointElapsed ) )
      {
        timepoint.execute( tpState, self, pack, pTeri, time );
        state.m_phaseInfo.m_lastTimepointTime = time;
      }
      else if( !timepoint.finished( tpState, timepointElapsed ) )
      {
        timepoint.update( tpState, self, pack, pTeri, time );
      }

      if( timepoint.durationElapsed( timepointElapsed ) && timepoint.finished( tpState, timepointElapsed ) )
      {
        // timepoint.reset( tpState );
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

  void Phase::reset( ConditionState& state ) const
  {
    state.m_phaseInfo.m_startTime = 0;
    state.m_phaseInfo.m_lastTimepointIndex = 0;
    state.m_phaseInfo.m_lastTimepointTime = 0;
  }

  bool Phase::completed( const ConditionState& state ) const
  {
    return state.m_phaseInfo.m_lastTimepointIndex > m_timepoints.size();
  }
  }// namespace Sapphire::Encounter