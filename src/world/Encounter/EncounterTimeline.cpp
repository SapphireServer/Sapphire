#include "EncounterFight.h"
#include "EncounterTimeline.h"

#include <Action/Action.h>

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Actor/EventObject.h>
#include <Actor/Player.h>

#include <Event/Director.h>

#include <Manager/ActionMgr.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

#include <Territory/QuestBattle.h>
#include <Util/UtilMath.h>

namespace Sapphire
{
  bool EncounterTimeline::ConditionHp::isConditionMet( ConditionState& state, TerritoryPtr pTeri, TimelinePack& pack, uint64_t time ) const
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

  bool EncounterTimeline::ConditionDirectorVar::isConditionMet( ConditionState& state, TerritoryPtr pTeri, TimelinePack& pack, uint64_t time ) const
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

  bool EncounterTimeline::ConditionCombatState::isConditionMet( ConditionState& state, TerritoryPtr pTeri, TimelinePack& pack, uint64_t time ) const
  {
    auto pBattleNpc = pTeri->getActiveBNpcByLayoutId( this->layoutId );

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

  bool EncounterTimeline::ConditionEncounterTimeElapsed::isConditionMet( ConditionState& state, TerritoryPtr pTeri, TimelinePack& pack, uint64_t time ) const
  {
    auto elapsed = time - pack.getStartTime();
    // todo: check encounter time
    return elapsed >= this->duration;
  }

  bool EncounterTimeline::ConditionBNpcFlags::isConditionMet( ConditionState& state, TerritoryPtr pTeri, TimelinePack& pack, uint64_t time ) const
  {
    auto pBNpc = pTeri->getActiveBNpcByLayoutId( this->layoutId );
    return pBNpc && pBNpc->hasFlag( this->flags );
  }

  void EncounterTimeline::Timepoint::update( TimepointState& state, TimelineActor& self, TerritoryPtr pTeri, uint64_t time ) const
  {
    state.m_lastTick = time;

    // todo: separate execute and update?
    if( state.m_finished )
      return;

    switch( m_type )
    {
      case TimepointDataType::Idle:
      {
        auto pIdleData = std::dynamic_pointer_cast< TimepointDataIdle, TimepointData >( getData() );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pIdleData->m_layoutId );

        if( pBNpc )
        {
          // todo: idle
          
        }
      }
      break;
      case TimepointDataType::CastAction:
      {
        auto pActionData = std::dynamic_pointer_cast< TimepointDataAction, TimepointData >( getData() );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pActionData->m_layoutId );
        // todo: filter the correct target
        // todo: tie to mechanic script?
        // todo: mechanic should probably just be an Action::onTick, with instance/director passed to it
        if( pBNpc)
        {
          auto actionMgr = Common::Service< Sapphire::World::Manager::ActionMgr >::ref();

          // todo: this is probably wrong
          if( pBNpc->getCurrentAction() && pBNpc->getCurrentAction()->getId() != pActionData->m_actionId )
            actionMgr.handleTargetedAction( *pBNpc.get(), pActionData->m_actionId, pBNpc->getTargetId(), 0 );
        }
      }
      break;
      case TimepointDataType::MoveTo:
      {
        auto pMoveToData = std::dynamic_pointer_cast< TimepointDataMoveTo, TimepointData >( getData() );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pMoveToData->m_layoutId );

        if( pBNpc )
        {
          auto currPos = pBNpc->getPos();
          Common::FFXIVARR_POSITION3 targetPos = { pMoveToData->m_x, pMoveToData->m_y, pMoveToData->m_z };

          auto distance = Common::Util::distance( currPos, targetPos );
          if( distance > 0.5f )
          {
            if( pMoveToData->m_moveType == MoveType::WalkPath )
              pBNpc->moveTo( targetPos );
            else
              pBNpc->setPos( pMoveToData->m_x, pMoveToData->m_y, pMoveToData->m_z );
          }
          else
          {
            // if we are at the pos, stop waiting
            state.m_finished = true;
          }
          pBNpc->setRot( pMoveToData->m_rot );
        }
      }
      break;
      case TimepointDataType::LogMessage:
      {
        auto pLogMessage = std::dynamic_pointer_cast< TimepointDataLogMessage, TimepointData >( getData() );
        auto params = pLogMessage->m_params;

        // todo: probably should use ContentDirector
        
        {
          auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();
          for( auto player : pTeri->getPlayers() )
          {
            auto pPlayer = player.second;
            if( pPlayer )
              playerMgr.sendLogMessage( *pPlayer.get(), pLogMessage->m_messageId,
                                        params[ 0 ], params[ 1 ], params[ 2 ], params[ 3 ], params[ 4 ] );
          }
        }
      }
      break;
      case TimepointDataType::BattleTalk:
      {
        // todo: BattleTalk
        auto pBtData = std::dynamic_pointer_cast< TimepointDataBattleTalk, TimepointData >( getData() );
        auto params = pBtData->m_params;


        auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();
        for( auto player : pTeri->getPlayers() )
        {
          auto pPlayer = player.second;
          if( pPlayer )
            playerMgr.sendBattleTalk( *pPlayer.get(), pBtData->m_battleTalkId, pBtData->m_handlerId,
                                      pBtData->m_kind, pBtData->m_nameId, pBtData->m_talkerId,
                                      params[ 0 ], params[ 1 ], params[ 2 ], params[ 3 ],
                                      params[ 4 ], params[ 5 ], params[ 6 ], params[ 7 ] );
        }
      }
      break;
      case TimepointDataType::DirectorSeq:
      case TimepointDataType::DirectorVar:
      case TimepointDataType::DirectorVarLR:
      case TimepointDataType::DirectorFlags:
      {
        auto pDirectorData = std::dynamic_pointer_cast< TimepointDataDirector, TimepointData >( getData() );

        uint32_t val = 0;
        uint32_t param = 0;

        // todo: expand for fates
        Event::DirectorPtr pDirector = pTeri->getAsInstanceContent();
        if( pDirector == nullptr )
          pDirector = pTeri->getAsQuestBattle();

        // todo: this should never not be set?
        // todo: probably should use ContentDirector
        // todo: this needs to resend packets too
        if( pDirector )
        {
          switch( m_type )
          {
            case TimepointDataType::DirectorVar:
              val = pDirector->getDirectorVar( pDirectorData->m_data.index );
              param = pDirectorData->m_data.value.val;
              break;
            case TimepointDataType::DirectorFlags:
              val = pDirector->getFlags();
              param = pDirectorData->m_data.flags;
              break;
            case TimepointDataType::DirectorSeq:
              val = pDirector->getSequence();
              param = pDirectorData->m_data.seq;
              break;
            default:
              break;
          }

          switch( pDirectorData->m_directorOp )
          {
            case DirectorOpId::Set: val = param;  break;
            case DirectorOpId::Add: val += param; break;
            case DirectorOpId::Sub: val -= param; break;
            case DirectorOpId::Mul: val *= param; break;
            case DirectorOpId::Div: val /= param; break;
            case DirectorOpId::Mod: val %= param; break;
            case DirectorOpId::Sll: val = val << param; break;
            case DirectorOpId::Srl: val = val >> param; break;
            case DirectorOpId::Or:  val |= param; break;
            case DirectorOpId::Xor: val ^= param; break;
            case DirectorOpId::Nor: val = ~( val | param ); break;
            case DirectorOpId::And: val &= param; break;
            default: break;
          }

          // todo: resend packets
          switch( m_type )
          {
            case TimepointDataType::DirectorVar:
              pDirector->setDirectorVar( pDirectorData->m_data.index, val );
              break;
            case TimepointDataType::DirectorFlags:
              pDirector->setDirectorFlags( val );
              break;
            case TimepointDataType::DirectorSeq:
              pDirector->setDirectorSequence( val );
              break;
            default:
              break;
          }
        }
      }
      break;
      case TimepointDataType::AddStatusEffect:
      {
        // todo:
      }
      break;
      case TimepointDataType::RemoveStatusEffect:
      {

      }
      break;
      case TimepointDataType::SpawnBNpc:
      {
        auto pSpawnData = std::dynamic_pointer_cast< TimepointDataSpawnBNpc, TimepointData >( getData() );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pSpawnData->m_layoutId );

        if( pBNpc )
        {
          pBNpc->clearFlags();
          pBNpc->setFlag( pSpawnData->m_flags );
          pBNpc->init();
        }
      }
      break;
      case TimepointDataType::SetBNpcFlags:
      {
        auto pBNpcFlagData = std::dynamic_pointer_cast< TimepointDataBNpcFlags, TimepointData >( getData() );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pBNpcFlagData->m_layoutId );

        if( pBNpc )
        {
          pBNpc->clearFlags();
          pBNpc->setFlag( pBNpcFlagData->m_flags );
          // todo: resend some bnpc packet/actrl?
        }
      }
      break;
      case TimepointDataType::SetEObjState:
      {
        auto pEObjData = std::dynamic_pointer_cast< TimepointDataEObjState, TimepointData >( getData() );

        auto pInstance = pTeri->getAsInstanceContent();
        auto pQBattle = pTeri->getAsQuestBattle();
        
        // todo: event objects on quest battles
        // todo: SetEObjAnimationFlag?

        if( pInstance )
        {
          auto pEObj = pInstance->getEObjById( pEObjData->m_eobjId );
          if( pEObj )
          {
            pEObj->setState( pEObjData->m_state );
            // todo: resend the eobj spawn packet?
          }
        }
      }
      break;
      case TimepointDataType::SetBgm:
      {
        auto pBgmData = std::dynamic_pointer_cast< TimepointDataBGM, TimepointData >( getData() );
        auto pInstance = pTeri->getAsInstanceContent();
        auto pQBattle = pTeri->getAsQuestBattle();

        // todo: quest battles refactor to inherit InstanceContent
        if( pInstance )
        {
          pInstance->setCurrentBGM( pBgmData->m_bgmId );
        }
      }
      break;
      case TimepointDataType::SetCondition:
      {
        auto pConditionData = std::dynamic_pointer_cast< TimepointDataCondition, TimepointData >( getData() );

        // todo: dont reset so things can resume? idk
        self.resetConditionState( pConditionData->m_conditionId );
        self.setConditionStateEnabled( pConditionData->m_conditionId, pConditionData->m_enabled );
      }
    }

    if( m_type != TimepointDataType::MoveTo && m_type != TimepointDataType::CastAction )
      state.m_finished = true;

    state.m_finished = state.m_finished || state.m_startTime + m_duration <= time;
  }

  /*
  class RngCondition : TimepointCondition
  {
    EncounterTimepointcondition m_type;
    std::vector< uint32_t > m_params
    
    RngCondition( EncounterTimepointcondition condition std::vector< uint32_t params ) : m_type( condition ), m_params( params ){}
    bool isConditionMet( uint32_t shit )
    {
      switch( m_type )
      {
        case EncounterTimepointcondition::RngMinMax:
          return RNGMgr::generate( params[0], params[1] ) == params[2];
      }
      return false;
    }
  }
  enum class ActionCallbackType : uint32_t
  {
    OnActionInit,
    OnActionStart,
    OnActionInterrupt,
    OnActionExecute
  };

  using CallbackFunc = std::function< void < CharaPtr, Action > >;

  std::unordered_map< ActionCallbackType, CallbackFunc > m_actionCallbacks;
  void Chara::registerActionCallback( ActionCallbackType type, CallbackFunc callback )
  {
    m_actionCallbacks[ type ].push_back( callback );
  }

  // call this when changing EncounterPack
  void Chara::clearActionCallbacks()
  {
    for( auto& callback : m_actionCallbacks )
      callback.second.clear()
  }

  void Chara::onActionInterrupt()
  {
    auto action = getCurrentAction();
    for( auto& callback : m_actionCallbacks[ ActionCallbackType::OnActionInterrupt ] )
      callback( this, action );
  }

  void EncounterTimeline::Timepoint::execute( TerritoryPtr pTeri, uint64_t time )
  {
    switch( m_type )
    {
      case TimepointDataType::CastAction:
      {
        auto pActionData = std::dynamic_pointer_cast< TimepointDataAction, TimepointData >( getData() );

        // todo: filter the correct target
        // todo: tie to mechanic script?
      }
    }
  }
  */

  void EncounterTimeline::Timepoint::execute( TimepointState& state, TimelineActor& self, TerritoryPtr pTeri, uint64_t time ) const
  {
    state.m_startTime = time;
    update( state, self, pTeri, time );
  }

  //
  // parsing stuff below
  //

  void EncounterTimeline::ConditionHp::from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
    const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto paramData = json.at( "paramData" );
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

  void EncounterTimeline::ConditionDirectorVar::from_json( nlohmann::json& json, Phase& phase, ConditionType condition )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto paramData = json.at( "paramData" );

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

  void EncounterTimeline::ConditionCombatState::from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
    const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionCombatState::from_json unable to find actor by name: %s" ), actorRef ) );

    this->combatState = paramData.at( "combatState" ).get< CombatStateType >();
  }

  void EncounterTimeline::ConditionEncounterTimeElapsed::from_json( nlohmann::json& json, Phase& phase, ConditionType condition )
  {
    PhaseCondition::from_json( json, phase, condition );

    auto paramData = json.at( "paramData" );
    auto duration = paramData.at( "duration" ).get< uint64_t >();

    this->duration = duration;
  }

  void EncounterTimeline::ConditionBNpcFlags::from_json( nlohmann::json& json, Phase& phase, ConditionType condition,
                                                           const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, condition );
    auto actorRef = json.at( "actor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionBNpcFlags::from_json unable to find actor by name: %s" ), actorRef ) );

    this->flags = json.at( "flags" ).get< uint32_t >();
    // todo: BNpcHasFlags
  }

  void EncounterTimeline::Timepoint::from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor>& actors, uint32_t selfLayoutId )
  {
    const static std::unordered_map< std::string, TimepointDataType > timepointTypeMap =
    {
      { "idle",               TimepointDataType::Idle },
      { "castAction",         TimepointDataType::CastAction },
      { "moveTo",             TimepointDataType::MoveTo },
      { "logMessage",         TimepointDataType::LogMessage },
      { "battleTalk",         TimepointDataType::BattleTalk  },
      { "directorVar",        TimepointDataType::DirectorVar },
      { "directorSeq",        TimepointDataType::DirectorSeq },
      { "directorFlags",      TimepointDataType::DirectorFlags },
      { "addStatusEffect",    TimepointDataType::AddStatusEffect },
      { "removeStatusEffect", TimepointDataType::RemoveStatusEffect },
      { "spawnBNpc",          TimepointDataType::SpawnBNpc },
      { "bNpcFlags",          TimepointDataType::SetBNpcFlags },
      { "setEObjState",       TimepointDataType::SetEObjState },
      { "setCondition",       TimepointDataType::SetCondition }
    };

    const static std::unordered_map< std::string, TimepointOverrideFlags > overrideFlagMap =
    {
      {}
    };

    const static std::unordered_map< std::string, TargetSelectFilterFlags > targetFilterMap =
    {
      { "self",       TargetSelectFilterFlags::Self },
      { "tank",       TargetSelectFilterFlags::Tank },
      { "healer",     TargetSelectFilterFlags::Healer },
      { "dps",        TargetSelectFilterFlags::Dps },
      { "melee",      TargetSelectFilterFlags::Melee },
      { "ranged",     TargetSelectFilterFlags::Ranged },
      { "furthest",   TargetSelectFilterFlags::Furthest },
      { "aggro1",     TargetSelectFilterFlags::Aggro1 },
      { "aggro2",     TargetSelectFilterFlags::Aggro2 }
    };

    const static std::unordered_map< std::string, TimepointCallbackType > callbackTypeMap =
    {
      { "onActionInit",       TimepointCallbackType::OnActionInit },
      { "onActionStart",      TimepointCallbackType::OnActionStart },
      { "onActionInterrupt",  TimepointCallbackType::OnActionInterrupt },
      { "onActionExecute",    TimepointCallbackType::OnActionExecute },
    };

    const static std::unordered_map< std::string, DirectorOpId > directorOpMap =
    {
      { "set", DirectorOpId::Set },
      { "add", DirectorOpId::Add },
      { "sub", DirectorOpId::Sub },
      { "mul", DirectorOpId::Mul },
      { "div", DirectorOpId::Div },
      { "mod", DirectorOpId::Mod },
      { "sll", DirectorOpId::Sll },
      { "srl", DirectorOpId::Srl },
      { "or",  DirectorOpId::Or },
      { "xor", DirectorOpId::Xor },
      { "nor", DirectorOpId::Nor },
      { "and", DirectorOpId::And }
    };

    TimepointDataType tpType{ 0 };

    auto typeStr = json.at( "type" ).get< std::string >();
    if( auto it = timepointTypeMap.find( typeStr ); it != timepointTypeMap.end() )
      tpType = it->second;
    else
      throw std::runtime_error( fmt::format( "Timepoint::from_json unable to find timepoint by type: %s", typeStr ) );

    m_duration = json.at( "duration" ).get< uint64_t >();
    //m_overrideFlags = json.at( "overrideFlags" ).get< TimepointOverrideFlags >();
    m_description = json.at( "description" ).get< std::string >();

    switch( tpType )
    {
      case TimepointDataType::Idle:
      {
        m_pData = std::make_shared< TimepointDataIdle >( selfLayoutId, m_duration );
      }
      break;
      case TimepointDataType::CastAction:
      {
        // todo: CastAction
        // todo: parse and build callback funcs
        auto& dataJ = json.at( "data" );
        auto actorRef = json.at( "sourceActor" ).get< std::string >();
        auto actionId = json.at( "actionId" ).get< uint32_t >();

        uint32_t layoutId = 0xE0000000;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( "EncounterTimeline::Timepoint::from_json: CastAction invalid actor ref: %s", actorRef ) );

        m_pData = std::make_shared< TimepointDataAction >( layoutId, actionId );
      }
      break;
      case TimepointDataType::MoveTo:
      {
        auto& dataJ = json.at( "data" );
        auto pos = dataJ.at( "pos" ).get< std::vector< float > >();
        auto rot = dataJ.at( "rot" ).get< float >();
        auto pathReq = dataJ.at( "pathRequested" ).get< bool >() ? MoveType::WalkPath : MoveType::Teleport;
        
        m_pData = std::make_shared< TimepointDataMoveTo >( selfLayoutId, pathReq, pos[ 0 ], pos[ 1 ], pos[ 2 ], rot );
      }
      break;
      case TimepointDataType::LogMessage:
      {
        auto& dataJ = json.at( "data" );
        auto messageId = dataJ.at( "messageId" ).get< uint32_t >();
        auto params = dataJ.at( "params" ).get< std::vector< uint32_t > >();

        m_pData = std::make_shared< TimepointDataLogMessage >( messageId, params );
      }
      break;
      case TimepointDataType::BattleTalk:
      {
        auto& dataJ = json.at( "data" );
        auto params = dataJ.at( "params" ).get< std::vector< uint32_t > >();

        auto pBattleTalkData = std::make_shared< TimepointDataBattleTalk >( params );

        pBattleTalkData->m_battleTalkId = dataJ.at( "battleTalkId" ).get< uint32_t >();
        pBattleTalkData->m_handlerId = dataJ.at( "handlerId" ).get< uint32_t >();
        pBattleTalkData->m_kind = dataJ.at( "kind" ).get< uint32_t >();
        pBattleTalkData->m_nameId = dataJ.at( "nameId" ).get< uint32_t >();
        pBattleTalkData->m_talkerId = dataJ.at( "talkerId" ).get< uint32_t >();

        m_pData = pBattleTalkData;
      }
      break;

      //
      // Directors
      //
      case TimepointDataType::DirectorVar:
      {
        auto& dataJ = json.at( "data" );
        auto index = dataJ.at( "idx" ).get< uint32_t >();
        auto val = dataJ.at( "val" ).get< uint32_t >();
        auto opStr = dataJ.at( "opc" ).get< std::string >();
        DirectorOpId op = directorOpMap.find( opStr )->second;

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType, op );
        pDirectorData->m_data.index = index;
        pDirectorData->m_data.value.val = val;

        m_pData = pDirectorData;
      }
      break;
      case TimepointDataType::DirectorVarLR:
      {
        auto& dataJ = json.at( "data" );
        auto index = dataJ.at( "idx" ).get< uint32_t >();
        auto left = dataJ.at( "left" ).get< uint32_t >();
        auto right = dataJ.at( "right" ).get< uint32_t >();
        auto opStr = dataJ.at( "opc" ).get< std::string >();
        DirectorOpId op = directorOpMap.find( opStr )->second;

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType, op );
        pDirectorData->m_data.index = index;
        pDirectorData->m_data.value.left = left;
        pDirectorData->m_data.value.right = right;

        m_pData = pDirectorData;
      }
      break;
      case TimepointDataType::DirectorSeq:
      {
        auto& dataJ = json.at( "data" );
        auto seq = dataJ.at( "val" ).get< uint32_t >();
        auto opStr = dataJ.at( "opc" ).get< std::string >();
        DirectorOpId op = directorOpMap.find( opStr )->second;

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType, op );
        pDirectorData->m_data.seq = seq;

        m_pData = pDirectorData;
      }
      break;
      case TimepointDataType::DirectorFlags:
      {
        auto& dataJ = json.at( "data" );
        auto flags = dataJ.at( "val" ).get< uint32_t >();
        auto opStr = dataJ.at( "opc" ).get< std::string >();
        DirectorOpId op = directorOpMap.find( opStr )->second;

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType, op );
        pDirectorData->m_data.flags = flags;

        m_pData = pDirectorData;
      }
      break;

      //
      // Status Effects
      //
      case TimepointDataType::AddStatusEffect:
      case TimepointDataType::RemoveStatusEffect:
      {
        // todo: add/remove status effects
      }
      break;


      case TimepointDataType::SpawnBNpc:
      {
        auto& dataJ = json.at( "data" );
        auto hateSrcJ = dataJ.at( "hateSrc" );
        auto actorRef = dataJ.at( "spawnActor" ).get< std::string >();
        auto flags = dataJ.at( "flags" ).get< uint32_t >();

        // todo: hateSrc

        uint32_t layoutId = 0xE0000000;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::Timepoint::from_json: SpawnBNpc invalid actor ref: %s" ), actorRef ) );

        m_pData = std::make_shared< TimepointDataSpawnBNpc >( layoutId, flags );
      }
      break;
      case TimepointDataType::SetBNpcFlags:
      {
        auto& dataJ = json.at( "data" );
        auto actorRef = dataJ.at( "spawnActor" ).get< std::string >();
        auto flags = dataJ.at( "flags" ).get< uint32_t >();

        // todo: hateSrc

        uint32_t layoutId = 0xE0000000;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::Timepoint::from_json: SetBNpcFlags invalid actor ref: %s" ), actorRef ) );

        m_pData = std::make_shared< TimepointDataBNpcFlags >( layoutId, flags );
        // todo: SetBNpcFlags
      }
      break;

      case TimepointDataType::SetEObjState:
      {
        auto& dataJ = json.at( "data" );

        // todo: SetEObjState
      }
      break;

      case TimepointDataType::SetCondition:
      {
        auto& dataJ = json.at( "data" );
        auto conditionId = dataJ.at( "conditionId" ).get< uint32_t >();
        auto enabled = dataJ.at( "enabled" ).get< bool >();

        m_pData = std::make_shared< TimepointDataCondition >( conditionId, enabled );
      }
      break;

      default:
        break;
    }
  }

  EncounterTimeline::TimelinePack EncounterTimeline::getEncounterPack( const std::string& name, bool reload )
  {
    static std::map< std::string, TimelinePack > cache = {};
    const static std::unordered_map< std::string, ConditionType > conditionMap =
    {
      { "hpPctLessThan",            ConditionType::HpPctLessThan },
      { "hpPctBetween",             ConditionType::HpPctBetween },

      { "directorVarEquals",        ConditionType::DirectorVarEquals },
      { "directorVarGreaterThan",   ConditionType::DirectorVarGreaterThan },

      { "directorSeqEquals",        ConditionType::DirectorSeqEquals },
      { "directorSeqGreaterThan",   ConditionType::DirectorSeqGreaterThan },

      { "directorFlagsEquals",      ConditionType::DirectorFlagsEquals },
      { "directorFlagsGreaterThan", ConditionType::DirectorFlagsGreaterThan },

      { "encounterTimeElapsed",     ConditionType::EncounterTimeElapsed },

      { "combatState",              ConditionType::CombatState },
      { "bnpcHasFlags",             ConditionType::BNpcHasFlags }
    };

    TimelinePack pack;
    if( cache.find( name ) != cache.end() && !reload )
      return cache.at( name );

    std::string encounter_name( fmt::format( std::string( "data/EncounterTimelines/%s.json" ), name ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return pack;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< std::string, Phase > > actorNamePhaseMap;

    // first run through cache actor info
    for( const auto& actorJ : json.at( "actors" ).items() )
    {
      TimelineActor actor;
      auto& actorV = actorJ.value();
      actor.m_hp = actorV.at( "hp" ).get< uint32_t >();
      actor.m_layoutId = actorV.at( "layoutId" ).get< uint32_t >();
      actor.m_name = actorV.at( "name" ).get< std::string >();

      actorNameMap.emplace( std::make_pair( actor.m_name, actor ) );
    }

    // build timeline info per actor
    for( const auto& actorJ : json.at( "actors" ).items() )
    {
      // < actorName, < phasename, phase > >
      std::map< std::string, Phase > phaseNameMap;

      auto actorV = actorJ.value();
      std::string actorName = actorV.at( "name" );

      TimelineActor& actor = actorNameMap[ actorName ];
      // todo: are phases linked by actor, or global in the json
      for( const auto& phaseJ : json.at( "phases" ).items() )
      {
        auto& phaseV = phaseJ.value();
        const auto id = phaseV.at( "id" ).get< uint32_t >();
        const auto& phaseName = phaseV.at( "name" ).get< std::string >();
        const auto& timepointsJ = phaseV.at( "timepoints" );

        Phase phase;
        for( const auto& timepointJ : timepointsJ.items() )
        {
          auto timepointV = timepointJ.value();
          Timepoint timepoint;
          timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

          phase.m_timepoints.push_back( timepoint );
        }

        if( phaseNameMap.find( phaseName ) != phaseNameMap.end() )
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - duplicate phase by name: %s" ), phaseName ) );

        phaseNameMap.emplace( std::make_pair( phaseName, phase ) );
      }
      actorNamePhaseMap[ actorName ] = phaseNameMap;
      if( actorNameMap.find( actorName ) != actorNameMap.end() )
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - duplicate actor by name: %s" ), actorName ) );

      actorNameMap.emplace( std::make_pair( actorName, actor ) );
    }

    // build the condition list
    for( const auto& pcJ : json.at( "conditions" ).items() )
    {
      auto& pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string >();
      auto phaseRef = pcV.at( "targetPhase" ).get< std::string >();
      auto actorRef = pcV.at( "targetActor" ).get< std::string >();
      
      ConditionType condition;

      // make sure condition exists
      if( auto it = conditionMap.find( conditionName ); it != conditionMap.end() )
        condition = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no condition id found by name: %s" ), conditionName ) );

      // make sure the actor we're referencing exists
      if( auto actorIt = actorNameMap.find( actorRef ); actorIt != actorNameMap.end() )
      {
        auto& phaseNameMap = actorNamePhaseMap[ actorRef ];

        TimelineActor& actor = actorIt->second;

        // make sure phase we're referencing exists
        if( auto phaseIt = phaseNameMap.find( phaseRef ); phaseIt != phaseNameMap.end() )
        {
          Phase& phase = phaseIt->second;

          // build the condition
          PhaseConditionPtr pCondition;
          switch( condition )
          {
            case ConditionType::HpPctLessThan:
            case ConditionType::HpPctBetween:
            {
              auto pHpCondition = std::make_shared< ConditionHp >();
              pHpCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            case ConditionType::DirectorVarEquals:
            case ConditionType::DirectorVarGreaterThan:
            case ConditionType::DirectorFlagsEquals:
            case ConditionType::DirectorFlagsGreaterThan:
            case ConditionType::DirectorSeqEquals:
            case ConditionType::DirectorSeqGreaterThan:
            {
              auto pDirectorCondition = std::make_shared< ConditionDirectorVar >();
              pDirectorCondition->from_json( pcV, phase, condition );
            }
            break;
            case ConditionType::EncounterTimeElapsed:
            {
              auto pEncounterCondition = std::make_shared< ConditionEncounterTimeElapsed >();
              pEncounterCondition->from_json( pcV, phase, condition );
            }
            break;
            case ConditionType::CombatState:
            {
              auto pCombatStateCondition = std::make_shared< ConditionCombatState >();
              pCombatStateCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            default:
              break;
          }
          actor.addPhaseCondition( pCondition );
        }
      }
      else
      {
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no state found by name: %s" ), phaseRef ) );
      }
    }

    for( const auto& actor : actorNameMap )
      pack.addTimelineActor( actor.second );

    pack.setName( name );

    // todo: reload will probably kill the server when CastAction.callbacks are added
    if( reload )
      cache[ name ] = pack;
    else
      cache.emplace( std::make_pair( name, pack ) );
    return pack;
  }

  Entity::BNpcPtr EncounterTimeline::TimelineActor::spawnSubActor( TerritoryPtr pTeri, const std::string& name )
  {
    // todo: retail straight up respawns sub actors, even bnpc parts (qarn adjudicator body parts respawn each time with new ids)
    auto flags = Entity::BNpcFlag::Invincible | Entity::BNpcFlag::Untargetable |
                 Entity::BNpcFlag::Immobile | Entity::BNpcFlag::AutoAttackDisabled |
                 Entity::BNpcFlag::TurningDisabled;

    auto pActor = getSubActor( name );
    if( pActor == nullptr )
    {
      auto pParent = pTeri->getActiveBNpcByLayoutId( m_layoutId );
      pActor = pTeri->createBNpcFromLayoutId( m_layoutId, 1000, pParent->getBNpcType() );
      m_subActors[ name ] = pActor;
    }
    pActor->setInvincibilityType( Common::InvincibilityIgnoreDamage );
    pActor->setFlag( flags );
    pActor->init();

    pTeri->pushActor( pActor );
    return pActor;
  }

  Entity::BNpcPtr EncounterTimeline::TimelineActor::getSubActor( const std::string& name )
  {
    if( auto it = m_subActors.find( name ); it != m_subActors.end() )
      return it->second;
    return nullptr;
  }

  void EncounterTimeline::TimelineActor::resetSubActors( TerritoryPtr pTeri )
  {
    for( auto& subActor : m_subActors )
    {
      if( subActor.second )
      {
        auto pBNpc = subActor.second;
        pTeri->removeActor( pBNpc );
        // todo: despawn?
        subActor.second = nullptr;
      }
    }
  }

}// namespace Sapphire