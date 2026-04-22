#include "TriggerCondition.h"

#include "Encounter.h"
#include "TimelinePack.h"
#include "TimelineActor.h"
#include "TimelineActorState.h"

#include <Action/Action.h>

#include <Actor/Chara.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>

#include <Territory/Territory.h>
#include <Territory/InstanceContent.h>
#include <Territory/QuestBattle.h>

namespace Sapphire
{
  bool ConditionHp::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pTeri = pEncounter->getTeriPtr();
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( m_layoutId );
    if( !pBNpc )
      return false;

    switch( m_conditionType )
    {
      case ConditionType::HpPctLessThan:
        return pBNpc->getHpPercent() < m_hp.val;
      case ConditionType::HpPctBetween:
      {
        auto hpPct = pBNpc->getHpPercent();
        return hpPct > m_hp.min && hpPct < m_hp.max;
      }
      default:
        break;
    }
    return false;
  };

  bool ConditionDirectorVar::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pDirector = pEncounter->getDirector();

    switch( m_conditionType )
    {
      case ConditionType::DirectorVarEquals:
        return pDirector->getDirectorVar( m_param.index ) == m_param.value;
      case ConditionType::DirectorVarGreaterThan:
        return pDirector->getDirectorVar( m_param.index ) > m_param.value;
      case ConditionType::DirectorFlagsEquals:
        return pDirector->getFlags() == m_param.flags;
      case ConditionType::DirectorFlagsGreaterThan:
        return pDirector->getFlags() > m_param.flags;
      case ConditionType::DirectorSeqEquals:
        return pDirector->getSequence() == m_param.seq;
      case ConditionType::DirectorSeqGreaterThan:
        return pDirector->getSequence() > m_param.seq;
      default:
        break;
    }
    return false;
  }

  bool ConditionCombatState::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pTeri = pEncounter->getTeriPtr();
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( m_layoutId );

    if( !pBNpc )
    {
      return false;
    }

    // todo: these should really use callbacks when the state transitions or we could miss this tick
    switch( m_combatState )
    {
      case CombatStateType::Idle:
        return pBNpc->getState() == Entity::BNpcState::Idle;
      case CombatStateType::Combat:
        return pBNpc->getState() == Entity::BNpcState::Combat;
      case CombatStateType::Retreat:
        return pBNpc->getState() == Entity::BNpcState::Retreat;
      case CombatStateType::Roaming:
        return pBNpc->getState() == Entity::BNpcState::Roaming;
      case CombatStateType::JustDied:
      case CombatStateType::Dead:
        return pBNpc->getState() == Entity::BNpcState::Dead ||
               pBNpc->getState() == Entity::BNpcState::JustDied ||
               pBNpc->getStatus() == Common::ActorStatus::Dead;
      default:
        break;
    }
    return false;
  }

  bool ConditionEncounterTimeElapsed::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto startTime = pEncounter->getStartTime();

    if( startTime == 0 )
      return false;

    auto elapsed = time - startTime;

    return elapsed >= m_duration;
  }

  bool ConditionBNpcFlags::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pTeri = pEncounter->getTeriPtr();
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( m_layoutId );
    return pBNpc && pBNpc->hasFlag( m_flags );
  }

  bool ConditionGetAction::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pTeri = pEncounter->getTeriPtr();
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( m_layoutId );

    if( pBNpc )
    {
      auto pAction = pBNpc->getCurrentAction();
      return pAction && pAction->getId() == m_actionId && !pAction->isInterrupted();
    }
    return false;
  }

  bool ConditionPhaseActive::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    return pack.isPhaseActive( m_actorName, m_phaseId );
  }

  bool ConditionInterruptedAction::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pTeri = pEncounter->getTeriPtr();
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( m_layoutId );

    if( pBNpc )
    {
      auto pAction = pBNpc->getCurrentAction();
      return pAction && pAction->getId() == m_actionId && pAction->isInterrupted();
    }
    return false;
  }

  bool ConditionVarEquals::isConditionMet( PhaseState& state, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pDirector = pEncounter->getDirector();

    switch( m_type )
    {
      case VarType::Director:
      {
        if( pDirector )
          return pDirector->getDirectorVar( m_index ) == m_val;
      }
      break;
      case VarType::Custom:
      {
        if( pDirector )
          return pDirector->getCustomVar( m_index ) == m_val;
      }
      break;
      case VarType::Pack:
      {
        return pack.getVar( m_index ) == m_val;
      }
      break;
      default:
        break;
    }
    return false;
  }

  void ConditionHp::from_json( nlohmann::json& json, ConditionType condition,
                               const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose hp we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      m_layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "ConditionHp::from_json unable to find actor by name: %s" ), actorRef ) );

    switch( condition )
    {
      case ConditionType::HpPctLessThan:
        m_hp.val = paramData.at( "hp" ).get< uint32_t >();
        break;
      case ConditionType::HpPctBetween:
        m_hp.min = paramData.at( "hpMin" ).get< uint32_t >(),
        m_hp.max = paramData.at( "hpMax" ).get< uint32_t >();
        break;
      default:
        break;
    }
  }

  void ConditionDirectorVar::from_json( nlohmann::json& json, ConditionType condition,
                                        const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );

    switch( condition )
    {
      case ConditionType::DirectorVarEquals:
      case ConditionType::DirectorVarGreaterThan:
      {
        m_param.index = paramData.at( "idx" ).get< uint32_t >();
        m_param.value = paramData.at( "val" ).get< uint32_t >();
      }
      break;
      case ConditionType::DirectorFlagsEquals:
      case ConditionType::DirectorFlagsGreaterThan:
      {
        m_param.flags = paramData.at( "flags" ).get< uint32_t >();
      }
      break;
      case ConditionType::DirectorSeqEquals:
      case ConditionType::DirectorSeqGreaterThan:
      {
        m_param.seq = paramData.at( "seq" ).get< uint32_t >();
      }
      break;
      default:
        break;
    }
  }

  void ConditionCombatState::from_json( nlohmann::json& json, ConditionType condition,
                                        const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      m_layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "ConditionCombatState::from_json unable to find actor by name: %s" ), actorRef ) );

    m_combatState = paramData.at( "combatState" ).get< CombatStateType >();
  }

  void ConditionEncounterTimeElapsed::from_json( nlohmann::json& json, ConditionType condition,
                                                 const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto duration = paramData.at( "duration" ).get< uint64_t >();

    m_duration = duration;
  }

  void ConditionBNpcFlags::from_json( nlohmann::json& json, ConditionType condition,
                                      const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      m_layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "ConditionBNpcFlags::from_json unable to find actor by name: %s" ), actorRef ) );

    m_flags = paramData.at( "flags" ).get< uint32_t >();
    // todo: BNpcHasFlags
  }

  void ConditionGetAction::from_json( nlohmann::json& json, ConditionType condition,
                                      const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();
    auto actionId = paramData.at( "actionId" ).get< uint32_t >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      m_layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "ConditionGetAction::from_json unable to find actor by name: %s" ), actorRef ) );

    m_actionId = actionId;
  }

  void ConditionPhaseActive::from_json( nlohmann::json& json, ConditionType condition,
                                        const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();
    auto scheduleName = paramData.at( "phaseId" ).get< uint32_t >();

    m_actorName = actorRef;
    m_phaseId = scheduleName;
  }

  void ConditionInterruptedAction::from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();
    auto actionId = paramData.at( "actionId" ).get< std::uint32_t >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      m_layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "ConditionInterruptedAction::from_json unable to find actor by name: %s" ), actorRef ) );

    m_actionId = actionId;
  }

  void ConditionVarEquals::from_json( nlohmann::json& json, ConditionType condition, const std::unordered_map< std::string, TimelineActor >& actors )
  {
    TriggerCondition::from_json( json, condition, actors );

    auto& paramData = json.at( "paramData" );
    auto index = paramData.at( "index" ).get< uint32_t >();
    auto val = paramData.at( "val" ).get< uint32_t >();
    auto type = paramData.at( "type" ).get< std::string >();

    if( type == "director" )
      m_type = VarType::Director;
    else if( type == "custom" )
      m_type = VarType::Custom;
    else
      m_type = VarType::Pack;

    m_index = index;
    m_val = val;
  }

}// namespace Sapphire