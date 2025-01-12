#include "Timepoint.h"
#include "TimelineActor.h"
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
#include <Territory/InstanceContent.h>
#include <Util/UtilMath.h>

namespace Sapphire::Encounter
{
  const TimepointDataPtr Timepoint::getData() const
  {
    return m_pData;
  }

  bool Timepoint::canExecute( const TimepointState& state, uint64_t elapsed ) const
  {
    return state.m_startTime == 0;
  }

  bool Timepoint::durationElapsed( uint64_t elapsed ) const
  {
    return m_duration <= elapsed;
  }

  bool Timepoint::finished( const TimepointState& state, uint64_t elapsed ) const
  {
    return durationElapsed( elapsed ) || state.m_finished;
  }

  void Timepoint::reset( TimepointState& state ) const
  {
    state.m_startTime = 0;
    state.m_lastTick = 0;
    state.m_finished = false;
  }

  void Timepoint::from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor >& actors, uint32_t selfLayoutId )
  {
    const static std::unordered_map< std::string, TimepointDataType > timepointTypeMap =
    {
      { "idle",          TimepointDataType::Idle },
      { "castAction",    TimepointDataType::CastAction },
      { "setPos",        TimepointDataType::SetPos },

      { "logMessage",    TimepointDataType::LogMessage },
      { "battleTalk",    TimepointDataType::BattleTalk },

      { "directorVar",   TimepointDataType::DirectorVar },
      { "directorSeq",   TimepointDataType::DirectorSeq },
      { "directorFlags", TimepointDataType::DirectorFlags },

      { "bNpcDespawn",   TimepointDataType::BNpcDespawn },
      { "bNpcSpawn",     TimepointDataType::BNpcSpawn },
      { "bNpcFlags",     TimepointDataType::BNpcFlags },
      { "setEObjState",  TimepointDataType::SetEObjState },
      { "setBGM",        TimepointDataType::SetBgm },

      { "setCondition",  TimepointDataType::SetCondition },
      { "snapshot",      TimepointDataType::Snapshot }
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

    const static std::unordered_map< std::string, Common::BNpcType > bnpcTypeMap =
    {
      { "bnpc", Common::BNpcType::Enemy },
      { "ally", Common::BNpcType::Friendly }// todo: rename this
    };

    const static std::unordered_map< std::string, ActionTargetType > actionTypeMap =
    {
      { "none",     ActionTargetType::None },
      { "self",     ActionTargetType::Self },
      { "target",   ActionTargetType::Target },
      { "selector", ActionTargetType::Selector }
    };

    TimepointDataType tpType{ 0 };

    auto typeStr = json.at( "type" ).get< std::string >();
    if( auto it = timepointTypeMap.find( typeStr ); it != timepointTypeMap.end() )
      tpType = it->second;
    else
      throw std::runtime_error( fmt::format( "Timepoint::from_json unable to find timepoint by type: {}", typeStr ) );

    m_duration = json.at( "duration" ).get< uint64_t >();
    //m_overrideFlags = json.at( "overrideFlags" ).get< TimepointOverrideFlags >();
    m_description = json.at( "description" ).get< std::string >();
    m_type = tpType;

    switch( tpType )
    {
      case TimepointDataType::Idle:
      {
        m_pData = std::make_shared< TimepointDataIdle >( m_duration );
      }
      break;
      case TimepointDataType::CastAction:
      {
        // todo: CastAction
        // todo: parse and build callback funcs
        auto& dataJ = json.at( "data" );
        auto sourceRef = dataJ.at( "sourceActor" ).get< std::string >();
        auto actionId = dataJ.at( "actionId" ).get< uint32_t >();
        auto targetType = actionTypeMap.find( dataJ.at( "targetType" ).get< std::string >() )->second;
        auto selectorRef = dataJ.at( "selectorName" ).get< std::string >();
        auto selectorIndex = dataJ.at( "selectorIndex" ).get< uint32_t >();

        m_pData = std::make_shared< TimepointDataAction >( sourceRef, actionId, targetType,
                                                           selectorRef, selectorIndex - 1 );
      }
      break;
      case TimepointDataType::SetPos:
      {
        auto& dataJ = json.at( "data" );
        auto pos = dataJ.at( "pos" ).get< std::vector< float > >();
        auto rot = dataJ.at( "rot" ).get< float >();
        auto actorRef = dataJ.at( "actorName" ).get< std::string >();

        m_pData = std::make_shared< TimepointDataSetPos >( actorRef, MoveType::SetPos,
                                                           pos[ 0 ], pos[ 1 ], pos[ 2 ], rot );
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
        pBattleTalkData->m_handlerRef = dataJ.at( "handlerActorName" ).get< std::string >();
        pBattleTalkData->m_kind = dataJ.at( "kind" ).get< uint32_t >();
        pBattleTalkData->m_nameId = dataJ.at( "nameId" ).get< uint32_t >();
        pBattleTalkData->m_talkerRef = dataJ.at( "talkerActorName" ).get< std::string >();

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
        DirectorOpId op = directorOpMap.at( opStr );

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
        DirectorOpId op = directorOpMap.at( opStr );

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
        DirectorOpId op = directorOpMap.at( opStr );

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
        DirectorOpId op = directorOpMap.at( opStr );

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

      case TimepointDataType::BNpcDespawn:
      {
        auto& dataJ = json.at( "data" );
        auto actorRef = dataJ.at( "despawnActor" ).get< std::string >();

        uint32_t layoutId = 0xE0000000;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( std::string( "Timepoint::from_json: SpawnBNpc invalid actor ref: {}" ), actorRef ) );

        m_pData = std::make_shared< TimepointDataBNpcDespawn >( layoutId );
      }
      break;
      case TimepointDataType::BNpcSpawn:
      {
        auto& dataJ = json.at( "data" );
        // auto hateSrcJ = dataJ.at( "hateSrc" );
        auto actorRef = dataJ.at( "spawnActor" ).get< std::string >();
        auto flags = dataJ.at( "flags" ).get< uint32_t >();
        // todo: batallion
        // auto battalion = dataJ.at( "batallion" ).get< uint32_t >();
        auto bnpcType = Common::BNpcType::Enemy;//bnpcTypeMap.at( dataJ.at( "type" ).get< std::string >() );

        // todo: hateSrc

        uint32_t layoutId = 0xE0000000;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( std::string( "Timepoint::from_json: SpawnBNpc invalid actor ref: {}" ), actorRef ) );

        m_pData = std::make_shared< TimepointDataBNpcSpawn >( layoutId, flags, bnpcType );
      }
      break;
      case TimepointDataType::BNpcFlags:
      {
        auto& dataJ = json.at( "data" );
        auto actorRef = dataJ.at( "targetActor" ).get< std::string >();
        auto flags = dataJ.at( "flags" ).get< uint32_t >();

        // todo: hateSrc

        uint32_t layoutId = selfLayoutId;
        //if( auto it = actors.find( actorRef ); it != actors.end() )
        //  layoutId = it->second.m_layoutId;
        //else
        //  throw std::runtime_error( fmt::format( std::string( "Timepoint::from_json: SetBNpcFlags invalid actor ref: {}" ), actorRef ) );

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
      case TimepointDataType::SetBgm:
      {
        auto& dataJ = json.at( "data" );
        auto bgmId = dataJ.at( "bgmId" ).get< uint32_t >();

        m_pData = std::make_shared< TimepointDataBGM >( bgmId );
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

      case TimepointDataType::Snapshot:
      {
        auto& dataJ = json.at( "data" );
        auto selectorName = dataJ.at( "selectorName" ).get< std::string >();
        auto actorRef = dataJ.at( "sourceActor" ).get< std::string >();
        auto excludeSelector = std::string(); // dataJ.at( "excludeSelectorName" ).get< std::string >();
        // todo: use exclude selector when added to ui

        m_pData = std::make_shared< TimepointDataSnapshot >( selectorName, actorRef, excludeSelector );
      }
      break;
      default:
        break;
    }
  }

  bool Timepoint::execute( TimepointState& state, TimelineActor& self, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    if( update( state, self, pack, pTeri, time ) )
    {
      state.m_startTime = time;
      state.m_finished = true;

      const auto& players = pTeri->getPlayers();
      // send debug msg
      if( !m_description.empty() )
      {
        auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();

        for( const auto& player : players )
          playerMgr.sendDebug( *player.second, m_description );
      }

      return true;
    }
    return false;
  }

  bool Timepoint::update( TimepointState& state, TimelineActor& self, TimelinePack& pack, TerritoryPtr pTeri, uint64_t time ) const
  {
    state.m_lastTick = time;

    // todo: separate execute and update?
    if( state.m_finished )
      return true;

    switch( m_type )
    {
      case TimepointDataType::Idle:
      {
        // just wait up the duration of this timepoint
      }
      break;
      case TimepointDataType::CastAction:
      {
        auto pActionData = std::dynamic_pointer_cast< TimepointDataAction, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pActionData->m_sourceRef, pTeri );
        // todo: filter the correct target
        // todo: tie to mechanic script?
        // todo: mechanic should probably just be an Action::onTick, with instance/director passed to it
        if( pBNpc )
        {
          uint32_t targetId = pBNpc->getId();
          switch( pActionData->m_targetType )
          {
            case ActionTargetType::None:
              targetId = 0xE0000000;
              break;
            case ActionTargetType::Target:
              targetId = static_cast< uint32_t >( pBNpc->getTargetId() );
              break;
            case ActionTargetType::Self:
              targetId = pBNpc->getId();
              break;
            case ActionTargetType::Selector:
            {
              const auto& results = pack.getSnapshotTargetIds( pActionData->m_selectorRef );
              if( pActionData->m_selectorIndex < results.size() )
                targetId = results[ pActionData->m_selectorIndex ];
            }
            break;
            default:
              break;
          }
          auto& actionMgr = Common::Service< Sapphire::World::Manager::ActionMgr >::ref();
          auto pAction = pBNpc->getCurrentAction();

          // todo: this is probably wrong
          if( !pAction || pAction->isInterrupted() )
          {
            actionMgr.handleTargetedAction( *pBNpc, pActionData->m_actionId, targetId, pTeri->getNextActionResultId() );
            //actionMgr.handlePlacedAction( *pBNpc, pActionData->m_actionId, pBNpc->getPos(), pTeri->getNextActionResultId() );
          }
          // todo: this really shouldnt exist, but need to figure out why actions interrupt
          else if( pAction->getId() == pActionData->m_actionId )
          {
       //     pAction->setInterrupted( Common::ActionInterruptType::RegularInterrupt );
       //     pAction->interrupt();
       //     pBNpc->setCurrentAction( nullptr );
       //     return false;
          }
          else
          {
            return false;
          }
        }
      }
      break;
      case TimepointDataType::SetPos:
      {
        auto pSetPosData = std::dynamic_pointer_cast< TimepointDataSetPos, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pSetPosData->m_actorRef, pTeri );

        if( pBNpc )
        {
          pBNpc->setRot( pSetPosData->m_rot );
          pBNpc->setPos( pSetPosData->m_x, pSetPosData->m_y, pSetPosData->m_z, true );
        }
      }
      break;
      /*
      case TimepointDataType::MoveTo:
      {
        auto pMoveToData = std::dynamic_pointer_cast< TimepointDataMoveTo, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pMoveToData->m_actorRef, pTeri );

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
            //state.m_finished = true;
          }
          pBNpc->setRot( pMoveToData->m_rot );
        }
      }
      break;
      */
      case TimepointDataType::LogMessage:
      {
        auto pLogMessage = std::dynamic_pointer_cast< TimepointDataLogMessage, TimepointData >( m_pData );
        auto params = pLogMessage->m_params;

        // todo: probably should use ContentDirector

        {
          auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();
          for( auto& player : pTeri->getPlayers() )
          {
            auto& pPlayer = player.second;
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
        auto pBtData = std::dynamic_pointer_cast< TimepointDataBattleTalk, TimepointData >( m_pData );
        auto params = pBtData->m_params;

        auto pHandler = pack.getBNpcByRef( pBtData->m_handlerRef , pTeri );
        auto pTalker = pack.getBNpcByRef( pBtData->m_talkerRef, pTeri );

        auto handlerId = pHandler ? pHandler->getId() : 0xE0000000;
        auto talkerId = pTalker ? pTalker->getId() : 0xE0000000;

        // todo: use Actrl EventBattleDialog = 0x39C maybe?,
        auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();

        // todo: this does not always need to be a director, and can also be an eventhandler
        //       needs further investigation
        Event::DirectorPtr pDirector = pTeri->getAsInstanceContent();
        if( pDirector == nullptr )
          pDirector = pTeri->getAsQuestBattle();

        if( pDirector )
          handlerId = pDirector->getDirectorId();

        for( auto& player : pTeri->getPlayers() )
        {

          auto& pPlayer = player.second;
          if( pPlayer )
            playerMgr.sendBattleTalk( *pPlayer.get(), pBtData->m_battleTalkId, handlerId,
                                      pBtData->m_kind, pBtData->m_nameId, talkerId, m_duration,
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
        auto pDirectorData = std::dynamic_pointer_cast< TimepointDataDirector, TimepointData >( m_pData );

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
            case DirectorOpId::Set:
              val = param;
              break;
            case DirectorOpId::Add:
              val += param;
              break;
            case DirectorOpId::Sub:
              val -= param;
              break;
            case DirectorOpId::Mul:
              val *= param;
              break;
            case DirectorOpId::Div:
              val /= param;
              break;
            case DirectorOpId::Mod:
              val %= param;
              break;
            case DirectorOpId::Sll:
              val = val << param;
              break;
            case DirectorOpId::Srl:
              val = val >> param;
              break;
            case DirectorOpId::Or:
              val |= param;
              break;
            case DirectorOpId::Xor:
              val ^= param;
              break;
            case DirectorOpId::Nor:
              val = ~( val | param );
              break;
            case DirectorOpId::And:
              val &= param;
              break;
            default:
              break;
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
      case TimepointDataType::BNpcDespawn:
      {
        auto pDespawnData = std::dynamic_pointer_cast< TimepointDataBNpcDespawn, TimepointData >( m_pData );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pDespawnData->m_layoutId );

        if( pBNpc )
        {
          for( const auto& player : pTeri->getPlayers() )
            pBNpc->despawn( player.second );

          pTeri->removeActor( pBNpc );
        }
      }
      break;
      case TimepointDataType::BNpcSpawn:
      {
        auto pSpawnData = std::dynamic_pointer_cast< TimepointDataBNpcSpawn, TimepointData >( m_pData );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pSpawnData->m_layoutId );

        // todo: probably have this info in the timepoint data
        if( !pBNpc )
          pBNpc = pTeri->createBNpcFromLayoutIdNoPush( pSpawnData->m_layoutId, 100, Common::BNpcType::Enemy );

        if( pBNpc )
        {
          pBNpc->resetFlags( pSpawnData->m_flags );
          pBNpc->init();

          pTeri->pushActor( pBNpc );
        }
      }
      break;
      case TimepointDataType::BNpcFlags:
      {
        auto pBNpcFlagData = std::dynamic_pointer_cast< TimepointDataBNpcFlags, TimepointData >( m_pData );
        auto pBNpc = pTeri->getActiveBNpcByLayoutId( pBNpcFlagData->m_layoutId );

        if( pBNpc )
        {
          pBNpc->resetFlags( pBNpcFlagData->m_flags );
          // todo: resend some bnpc packet/actrl?
        }
      }
      break;
      case TimepointDataType::SetEObjState:
      {
        auto pEObjData = std::dynamic_pointer_cast< TimepointDataEObjState, TimepointData >( m_pData );

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
        auto pBgmData = std::dynamic_pointer_cast< TimepointDataBGM, TimepointData >( m_pData );
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
        auto pConditionData = std::dynamic_pointer_cast< TimepointDataCondition, TimepointData >( m_pData );

        // todo: dont reset so things can resume? idk
        pack.resetConditionState( pConditionData->m_conditionId );
        pack.setConditionStateEnabled( pConditionData->m_conditionId, pConditionData->m_enabled );
      }
      break;
      case TimepointDataType::Snapshot:
      {
        auto pSnapshotData = std::dynamic_pointer_cast< TimepointDataSnapshot, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pSnapshotData->m_actorRef, pTeri );

        if( pBNpc )
        {
          const auto& exclude = pack.getSnapshotTargetIds( pSnapshotData->m_excludeSelector );
          pack.createSnapshot( pSnapshotData->m_selector, pBNpc, exclude );
        }
      }
      break;
      default:
        break;
    }
    return true;
  }
}