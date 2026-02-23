#include "Timepoint.h"
#include "TimelineActor.h"
#include "TimelinePack.h"
#include "Encounter.h"

#include <Action/Action.h>

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Actor/EventObject.h>
#include <Actor/Player.h>

#include <Event/Director.h>

#include <Manager/ActionMgr.h>
#include <Manager/PlayerMgr.h>

#include <Random/RNGMgr.h>

#include <Service.h>

#include <Territory/QuestBattle.h>
#include <Territory/InstanceContent.h>
#include <Util/UtilMath.h>

#include <Network/CommonActorControl.h>
#include <Network/Util/PacketUtil.h>

namespace Sapphire
{
  const TimepointDataPtr Timepoint::getData() const
  {
    return m_pData;
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
      { "idle",                TimepointDataType::Idle },
      { "castAction",          TimepointDataType::CastAction },
      { "setPos",              TimepointDataType::SetPos },
      { "actionTimeline",      TimepointDataType::ActionTimeline },

      { "logMessage",          TimepointDataType::LogMessage },
      { "battleTalk",          TimepointDataType::BattleTalk },

      { "directorVar",         TimepointDataType::DirectorVar },
      { "directorSeq",         TimepointDataType::DirectorSeq },
      { "directorFlags",       TimepointDataType::DirectorFlags },

      { "bNpcDespawn",         TimepointDataType::BNpcDespawn },
      { "bNpcSpawn",           TimepointDataType::BNpcSpawn },
      { "bNpcFlags",           TimepointDataType::BNpcFlags },
      { "setEObjState",        TimepointDataType::SetEObjState },
      { "setBGM",              TimepointDataType::SetBgm },

      { "setCondition",        TimepointDataType::SetCondition },
      { "snapshot",            TimepointDataType::Snapshot },
      { "interruptAction",     TimepointDataType::InterruptAction },
      { "rollRNG",             TimepointDataType::RollRNG }
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
      { "none",           ActionTargetType::None },
      { "self",           ActionTargetType::Self },
      { "target",         ActionTargetType::Target },
      { "selectorPos",    ActionTargetType::SelectorPos },
      { "selectorTarget", ActionTargetType::SelectorTarget },
    };

    const static std::unordered_map< std::string, SetPosType > setPosTypeMap =
    {
      { "absolute", SetPosType::Absolute },
      { "relative", SetPosType::Relative }
    };

    const static std::unordered_map< std::string, SetPosTargetType > setPosTargetTypeMap =
    {
      { "none",           SetPosTargetType::None },
      { "self",           SetPosTargetType::Self },
      { "target",         SetPosTargetType::Target },
      { "selectorPos",    SetPosTargetType::SelectorPos },
      { "selectorTarget", SetPosTargetType::SelectorTarget }
    };

    const static std::unordered_map< std::string, VarType > varTypeMap =
    {
      { "director", VarType::Director },
      { "custom",   VarType::Custom },
      { "pack",     VarType::Pack }
    };

    TimepointDataType tpType{ 0 };

    auto typeStr = json.at( "type" ).get< std::string >();
    if( auto it = timepointTypeMap.find( typeStr ); it != timepointTypeMap.end() )
      tpType = it->second;
    else
      throw std::runtime_error( fmt::format( "Timepoint::from_json unable to find timepoint by type: {}", typeStr ) );
    
    m_offset = json.at( "startTime" ).get< uint64_t >();
    //m_overrideFlags = json.at( "overrideFlags" ).get< TimepointOverrideFlags >();
    m_description = json.at( "description" ).get< std::string >();
    m_type = tpType;

    switch( tpType )
    {
      case TimepointDataType::CastAction:
      {
        // todo: CastAction
        // todo: parse and build callback funcs
        auto& dataJ = json.at( "data" );
        auto sourceRef = dataJ.at( "sourceActor" ).get< std::string >();
        auto actionId = dataJ.at( "actionId" ).get< uint32_t >();
        auto targetType = actionTypeMap.at( dataJ.at( "targetType" ).get< std::string >() );
        auto selectorRef = dataJ.at( "selectorName" ).get< std::string >();
        auto selectorIndex = dataJ.at( "selectorIndex" ).get< uint32_t >();

        m_pData = std::make_shared< TimepointDataAction >( sourceRef, actionId, targetType,
                                                           selectorRef, selectorIndex );
      }
      break;
      case TimepointDataType::SetPos:
      {
        auto& dataJ = json.at( "data" );
        auto pos = dataJ.at( "pos" ).get< std::vector< float > >();
        auto rot = dataJ.at( "rot" ).get< float >();
        auto actorRef = dataJ.at( "actorName" ).get< std::string >();
        auto selectorName = dataJ.at( "selectorName" ).get< std::string >();
        auto selectorIndex = dataJ.at( "selectorIndex" ).get< uint32_t >();
        auto targetType = setPosTargetTypeMap.at( dataJ.at( "targetType" ).get< std::string >() );
        auto posType = setPosTypeMap.at( dataJ.at( "positionType" ).get< std::string >() );

        m_pData = std::make_shared< TimepointDataSetPos >( actorRef, posType, targetType, MoveType::SetPos,
                                                           selectorName, selectorIndex,
                                                           pos[ 0 ], pos[ 1 ], pos[ 2 ], rot );
      }
      break;
      case TimepointDataType::ActionTimeline:
      {
        auto& dataJ = json.at( "data" );
        auto action = dataJ.at( "actionTimelineId" ).get< uint32_t >();
        auto actorRef = dataJ.at( "actorName" ).get< std::string >();

        m_pData = std::make_shared< TimepointDataActionTimeLine >( actorRef, action );
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
        pBattleTalkData->m_kind = dataJ.at( "kind" ).get< uint32_t >();
        pBattleTalkData->m_nameId = dataJ.at( "nameId" ).get< uint32_t >();
        pBattleTalkData->m_talkerRef = dataJ.at( "talkerActorName" ).get< std::string >();
        pBattleTalkData->m_length = dataJ.at( "length" ).get< uint32_t >();

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

        uint32_t layoutId = Common::INVALID_GAME_OBJECT_ID;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( std::string( "Timepoint::from_json: BNpcDespawn invalid actor ref: {}" ), actorRef ) );

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
        auto flagsMaskJ = dataJ.at( "flagsMask" );
        auto flagsMask = 0xFFFFFFFF;
        auto invulnJ = dataJ.at( "invulnType" );
        auto invincibilityType = Common::InvincibilityNone;

        if( !flagsMaskJ.is_null() )
          flagsMask = flagsMaskJ.get< uint32_t >();

        if( !invulnJ.is_null() )
          invincibilityType = invulnJ.get< Common::InvincibilityType >();
        // todo: hateSrc

        uint32_t layoutId = Common::INVALID_GAME_OBJECT_ID;
        if( auto it = actors.find( actorRef ); it != actors.end() )
          layoutId = it->second.m_layoutId;
        else
          throw std::runtime_error( fmt::format( std::string( "Timepoint::from_json: BNpcSpawn invalid actor ref: {}" ), actorRef ) );

        m_pData = std::make_shared< TimepointDataBNpcSpawn >( layoutId, flags, flagsMask, invincibilityType, bnpcType );
      }
      break;
      case TimepointDataType::BNpcFlags:
      {
        auto& dataJ = json.at( "data" );
        auto actorRef = dataJ.at( "targetActor" ).get< std::string >();
        auto flags = dataJ.at( "flags" ).get< uint32_t >();
        auto flagsMaskJ = dataJ.at( "flagsMask" );
        auto flagsMask = 0xFFFFFFFF;
        auto invulnJ =  dataJ.at( "invulnType" );
        auto invincibilityType = Common::InvincibilityNone;

        if( !flagsMaskJ.is_null() )
          flagsMask = flagsMaskJ.get< uint32_t >();

        if( !invulnJ.is_null() )
          invincibilityType = invulnJ.get< Common::InvincibilityType >();

        // todo: hateSrc

        uint32_t layoutId = selfLayoutId;
        //if( auto it = actors.find( actorRef ); it != actors.end() )
        //  layoutId = it->second.m_layoutId;
        //else
        //  throw std::runtime_error( fmt::format( std::string( "Timepoint::from_json: BNpcFlags invalid actor ref: {}" ), actorRef ) );

        m_pData = std::make_shared< TimepointDataBNpcFlags >( layoutId, flags, flagsMask, invincibilityType );
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
      case TimepointDataType::InterruptAction:
      {
        auto& dataJ = json.at( "data" );
        auto actorRef = dataJ.at( "sourceActor" ).get< std::string >();
        auto actionId = dataJ.at( "actionId" ).get< uint32_t >();

        m_pData = std::make_shared< TimepointDataInterruptAction >( actorRef, actionId );
      }
      break;
      case TimepointDataType::RollRNG:
      {
        auto& dataJ = json.at( "data" );
        auto min = dataJ.at( "min" ).get< uint32_t >();
        auto max = dataJ.at( "max" ).get< uint32_t >();
        auto type = varTypeMap.at( dataJ.at( "type" ).get< std::string >() );
        auto idx = dataJ.at( "index" ).get< uint32_t >();

        m_pData = std::make_shared< TimepointDataRollRNG >( min, max, type, idx );
      }
      break;
      default:
        break;
    }
  }

  bool Timepoint::execute( TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    if( update( self, pack, pEncounter, time ) )
    {
      auto pTeri = pEncounter->getTeriPtr();
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

  bool Timepoint::update( TimelineActor& self, TimelinePack& pack, EncounterPtr pEncounter, uint64_t time ) const
  {
    auto pTeri = pEncounter->getTeriPtr();
    // todo: separate execute and update?
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
        auto pBNpc = pack.getBNpcByRef( pActionData->m_sourceRef, pEncounter );
        Common::Vector3 pos = pBNpc->getPos();
        // todo: filter the correct target
        // todo: tie to mechanic script?
        // todo: mechanic should probably just be an Action::onTick, with instance/director passed to it
        if( pBNpc )
        {
          uint32_t targetId = pBNpc->getId();
          switch( pActionData->m_targetType )
          {
            case ActionTargetType::None:
              targetId = Common::INVALID_GAME_OBJECT_ID;
              break;
            case ActionTargetType::Target:
              targetId = static_cast< uint32_t >( pBNpc->getTargetId() );
              break;
            case ActionTargetType::Self:
              targetId = pBNpc->getId();
              break;
            case ActionTargetType::SelectorPos:
            case ActionTargetType::SelectorTarget:
            {
              const auto& results = pack.getSnapshotResults( pActionData->m_selectorRef );

              if( pActionData->m_selectorIndex < results.size() )
              {
                const auto& res = results[ pActionData->m_selectorIndex ];
                targetId = res.m_entityId;
                pos = res.m_pos;
              }
            }
            break;
            default:
              break;
          }
          auto& actionMgr = Common::Service< Sapphire::World::Manager::ActionMgr >::ref();
          auto pAction = pBNpc->getCurrentAction();

          // todo: probably a flag on TimelinePack for PauseIfOutOfRange? idk
          // we need to pause the timeline if the player is out of range
          auto topHateId = pBNpc->getTargetId();
          {
            auto pTargetActor = pEncounter->getTeriPtr()->getEntityById( topHateId );

            if( pTargetActor )
            {
              if( auto pTargetChara = pTargetActor->getAsChara() )
              {
                if( targetId != pBNpc->getId() )
                {
                  // stall if not facing target
                  if( !pBNpc->isFacingTarget( *pTargetChara, 0.99f ) )
                    return false;

                  auto bnpcPos = pBNpc->getPos();
                  auto targPos = pTargetChara->getPos();

                  auto distance = Common::Util::distance( bnpcPos.x, bnpcPos.y, bnpcPos.z, targPos.x, targPos.y, targPos.z );
                  if( distance >= 3.f + pBNpc->getRadius() + pTargetChara->getRadius() )
                  {
                    // pause at this timepoint
                    return false;
                  }
                }
              }
            }
          }

          if( pAction )
            return false;

          // todo: this is probably wrong
          //if( !pAction || pAction->isInterrupted() )
          {
            if( pActionData->m_targetType == ActionTargetType::SelectorPos )
              actionMgr.handlePlacedAction( *pBNpc, pActionData->m_actionId, pos, pTeri->getNextActionResultId(), targetId );
            else
              actionMgr.handleTargetedAction( *pBNpc, pActionData->m_actionId, targetId, pTeri->getNextActionResultId() );
          }
        }
      }
      break;
      case TimepointDataType::SetPos:
      {
        auto pSetPosData = std::dynamic_pointer_cast< TimepointDataSetPos, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pSetPosData->m_actorRef, pEncounter );

        if( pBNpc )
        {
          auto pos = pBNpc->getPos();
          float rot = 0.f;
          switch( pSetPosData->m_targetType )
          {
            case SetPosTargetType::Target:
            {
              auto inRange = pBNpc->getInRangeActors();
              for( const auto& pActor : inRange )
              {
                if( pActor->getId() == pBNpc->getTargetId() )
                {
                  pos = pActor->getPos();
                  rot = pActor->getRot();
                  break;
                }
              }
            }
            break;
            case SetPosTargetType::SelectorPos:
            {
              const auto& results = pack.getSnapshotResults( pSetPosData->m_selectorName );
              if( pSetPosData->m_selectorIndex < results.size() )
              {
                pos = results[ pSetPosData->m_selectorIndex ].m_pos;
                rot = results[ pSetPosData->m_selectorIndex ].m_rot;
              }
            }
            break;
            // todo: idk what i was thinking here but should this just be the snapshotted position as above rather than live pos?
            case SetPosTargetType::SelectorTarget:
            {
              const auto& results = pack.getSnapshotResults( pSetPosData->m_selectorName );
              if( pSetPosData->m_selectorIndex < results.size() )
              {
                // find the target by id and copy their pos
                auto targetId = results[ pSetPosData->m_selectorIndex ].m_entityId;
                for( const auto& pActor : pBNpc->getInRangeActors() )
                {
                  if( pActor->getId() == targetId )
                  {
                    pos = pActor->getPos();
                    rot = pActor->getRot();
                    break;
                  }
                }
              }
            }
            break;
            default:
              break;
          }

          switch( pSetPosData->m_posType )
          {
            case SetPosType::Absolute:
            {
              // dont use absolute pos for selector, just use the selector pos
              if( pSetPosData->m_targetType == SetPosTargetType::SelectorPos || pSetPosData->m_targetType == SetPosTargetType::SelectorTarget )
              {
                pBNpc->setRot( rot );
                pBNpc->setPos( pos, true );
              }
              else
              {
                pos = { pSetPosData->m_x, pSetPosData->m_y, pSetPosData->m_z };
                rot = pSetPosData->m_rot;
              }
            }
            break;
            case SetPosType::Relative:
            {
              auto offsetPos = Common::Util::getOffsettedPosition( pos, rot, pSetPosData->m_x, pSetPosData->m_y, pSetPosData->m_z );
              pos = offsetPos;
            }
            break;
            default:
              break;
          }

          // todo: handling agent should really be somewhere else
          if( pBNpc->getAgentId() != -1 )
          {
            auto pNavi = pTeri->getNaviProvider();
            if( pNavi )
              pBNpc->setAgentId( pNavi->updateAgentPosition( pBNpc->getAgentId(), pos, pBNpc->getRadius(), pNavi->getAgentSpeed( pBNpc->getAgentId() ) ) );
          }
          pBNpc->setRot( rot );
          pBNpc->setPos( pos, true );
        }
      }
      break;

      case TimepointDataType::ActionTimeline:
      {
        auto pActionTimelineData = std::dynamic_pointer_cast< TimepointDataActionTimeLine, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pActionTimelineData->m_actorRef, pEncounter );
        auto action = pActionTimelineData->m_actionId;

        if( pBNpc )
        {
          Network::Util::Packet::sendActorControl( pBNpc->getInRangePlayerIds(), pBNpc->getId(),
                                                   Network::ActorControl::PlayActionTimeline, action );
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
      //*/
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

        auto pHandler = pack.getBNpcByRef( pBtData->m_handlerRef, pEncounter );
        auto pTalker = pack.getBNpcByRef( pBtData->m_talkerRef, pEncounter );

        auto handlerId = pHandler ? pHandler->getId() : Common::INVALID_GAME_OBJECT_ID;
        auto talkerId = pTalker ? pTalker->getId() : Common::INVALID_GAME_OBJECT_ID;

        // todo: use Actrl EventBattleDialog = 0x39C maybe?,
        auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();

        // todo: this does not always need to be a director, and can also be an eventhandler
        //       needs further investigation
        Event::DirectorPtr pDirector = pEncounter->getDirector();

        if( pDirector )
          handlerId = pDirector->getDirectorId();

        for( auto& player : pTeri->getPlayers() )
        {

          auto& pPlayer = player.second;
          if( pPlayer )
            playerMgr.sendBattleTalk( *pPlayer.get(), pBtData->m_battleTalkId, handlerId,
                                      pBtData->m_kind, pBtData->m_nameId, talkerId, static_cast< uint32_t >( pBtData->m_length ),
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
        Event::DirectorPtr pDirector = pEncounter->getDirector();

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

          for( const auto& player : pTeri->getPlayers() )
            pDirector->sendDirectorVars( *player.second );
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
          auto flagsMask = pSpawnData->m_flagsMask;
          auto currFlag = pBNpc->getFlags();
          auto flags = ( currFlag & ~flagsMask ) | ( pSpawnData->m_flags & flagsMask );

          pBNpc->resetFlags( flags );
          pBNpc->setInvincibilityType( static_cast< Common::InvincibilityType >( pSpawnData->m_invincibilityType ) );
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
          auto flagsMask = pBNpcFlagData->m_flagsMask;
          auto currFlag = pBNpc->getFlags();
          auto flags = ( currFlag & ~flagsMask ) | ( pBNpcFlagData->m_flags & flagsMask );
          
          pBNpc->resetFlags( flags );
          pBNpc->setInvincibilityType( static_cast< Common::InvincibilityType >( pBNpcFlagData->m_invincibilityType ) );
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
        auto pBNpc = pack.getBNpcByRef( pSnapshotData->m_actorRef, pEncounter );

        if( pBNpc )
        {
          const auto& exclude = pack.getSnapshotTargetIds( pSnapshotData->m_excludeSelector );
          pack.createSnapshot( pSnapshotData->m_selector, *pBNpc, exclude );
        }
      }
      break;
      case TimepointDataType::InterruptAction:
      {
        auto pInterruptData = std::dynamic_pointer_cast< TimepointDataInterruptAction, TimepointData >( m_pData );
        auto pBNpc = pack.getBNpcByRef( pInterruptData->m_actorRef, pEncounter );

        if( pBNpc )
        {
          auto pAction = pBNpc->getCurrentAction();
          if( pAction && pAction->getId() == pInterruptData->m_actionId )
          {
            pAction->setInterrupted( Common::ActionInterruptType::RegularInterrupt );
            pAction->interrupt();
          }
        }
      }
      break;
      case TimepointDataType::RollRNG:
      {
        auto pRNGData = std::dynamic_pointer_cast< TimepointDataRollRNG, TimepointData >( m_pData );

        auto& rngMgr = Common::Service< Common::Random::RNGMgr >::ref();
        auto val = rngMgr.getRandGenerator( pRNGData->m_min, pRNGData->m_max ).next();

        switch( pRNGData->m_type )
        {
          case VarType::Director:
          {
            auto pDirector = pEncounter->getDirector();
            if( pDirector)
              pDirector->setDirectorVar( pRNGData->m_idx, val );
          }
          break;
          case VarType::Custom:
          {
            auto pDirector = pEncounter->getDirector();
            if( pDirector )
              pDirector->setCustomVar( pRNGData->m_idx, val );
          }
          break;
          case VarType::Pack:
          {
            // todo: probably get rid of this?
            pack.setVar( pRNGData->m_idx, val );
          }
          break;
        }
      }
      break;

      default:
        break;
    }
    return true;
  }
}