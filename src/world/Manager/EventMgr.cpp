#include <Common.h>
#include <Util/Util.h>
#include <Service.h>

#include "EventMgr.h"
#include "PlayerMgr.h"
#include "ShopMgr.h"
#include "Event/EventHandler.h"
#include "Event/EventDefs.h"

#include <Exd/ExdData.h>
#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventPlayPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/EventResumePacket.h"
#include "Network/PacketWrappers/EventNoticePacket.h"

#include "Territory/InstanceObjectCache.h"

#include "Territory/Territory.h"
#include "Territory/InstanceContent.h"

#include "Action/EventAction.h"
#include "Action/EventItemAction.h"
#include "WorldServer.h"
#include "Actor/Player.h"
#include <Script/ScriptMgr.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

std::string EventMgr::getEventName( uint32_t eventId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  uint16_t eventType = eventId >> 16;

  auto unknown = std::string{ "unknown" };

  switch( eventType )
  {
    case Event::EventHandler::EventHandlerType::Quest:
    {
      auto questInfo = exdData.getRow< Excel::Quest >( eventId );
      if( !questInfo )
        return unknown + "Quest";

      std::string name = questInfo->getString( questInfo->data().Script );
      std::size_t pos = name.find_first_of( '_' );

      return name.substr( 0, pos );
    }
    case Event::EventHandler::EventHandlerType::CustomTalk:
    {
      auto customTalkInfo = exdData.getRow< Excel::CustomTalk >( eventId );
      if( !customTalkInfo )
        return unknown + "CustomTalk";

      std::string name = customTalkInfo->getString( customTalkInfo->data().Script );
      std::size_t pos = name.find_first_of( '_' );

      return name.substr( 0, pos );
    }
    case Event::EventHandler::EventHandlerType::Opening:
    {
      auto openingInfo = exdData.getRow< Excel::Opening >( eventId );
      if( openingInfo )
        return openingInfo->getString( openingInfo->data().Script );
      return unknown + "Opening";
    }
    case Event::EventHandler::EventHandlerType::Aetheryte:
    {
      auto aetherInfo = exdData.getRow< Excel::Aetheryte >( eventId & 0xFFFF );
      if( aetherInfo->data().Telepo )
        return "Aetheryte";
      return "Aethernet";
    }
    case Event::EventHandler::EventHandlerType::ICDirector:
    {
      // auto contentInfo = pExdData->get< Sapphire::Data::InstanceContent >( eventId & 0xFFFF );
      return "InstanceContentDirector#" + std::to_string( eventId & 0xFFFF );
    }
    case Event::EventHandler::EventHandlerType::QuestBattleDirector:
    {

      auto qbInfo = exdData.getRow< Excel::QuestBattle >( eventId & 0xFFFF );
      if( !qbInfo )
        return "unknown";
      auto questInfo = exdData.getRow< Excel::Quest >( qbInfo->data().Quest );
      if( !questInfo )
        return "unknown";

      std::string name = questInfo->getString( questInfo->data().Text.Name );
      std::string remove( ",â˜…_ '()[]-\x1a\x1\x2\x1f\x1\x3.:" );
      Common::Util::eraseAllIn( name, remove );
      name[ 0 ] = toupper( name[ 0 ] );
      return name;
    }


    case Event::EventHandler::EventHandlerType::Warp:
    {
      auto warpInfo = exdData.getRow< Excel::Warp >( eventId );
      if( warpInfo )
      {
        auto warpLogic = exdData.getRow< Excel::WarpLogic >( warpInfo->data().Logic );
        if( warpLogic )
        {
          if( warpLogic->getString( warpLogic->data().Script ).empty() )
            return "WarpTaxi";
          else
            return warpLogic->getString( warpLogic->data().Script );
        }
      }

      return unknown + "Warp";//who know
    }

    case Event::EventHandler::EventHandlerType::Shop:
    {
      return "GilShop" + std::to_string( eventId );
    }

    case Event::EventHandler::EventHandlerType::SwitchTalk:
    {
      return "FcTalk";
    }
    default:
    {
      return unknown;
    }
  }
}

std::string EventMgr::getErrorCodeName( uint8_t errorCode )
{
  switch( errorCode )
  {
    case Common::EventSceneError::EVENT_SCENE_SUCCESS:
    {
      return "SUCCESS";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_LUA_ERRRUN:
    {
      return "LUA_ERRRUN";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_LUA_ERRSYNTAX:
    {
      return "LUA_ERRSYNTAX";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_LUA_ERRMEM:
    {
      return "LUA_ERRMEM";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_LUA_ERRERR:
    {
      return "LUA_ERRERR";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_USER_CANCEL:
    {
      return "USER_CANCEL";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_SERVER_ABORT:
    {
      return "SERVER_ABORT";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_RELOAD:
    {
      return "RELOAD";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_LUA_THREAD_BUSY:
    {
      return "LUA_THREAD_BUSY";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_TARGET_CHANGED:
    {
      return "TARGET_CHANGED";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_CLIENT_ABORT:
    {
      return "CLIENT_ABORT";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_TARGET_LOST:
    {
      return "TARGET_LOST";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_BEFORE_PLAY:
    {
      return "BEFORE_PLAY";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_BIND_CHARACTER:
    {
      return "BIND_CHARACTER";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_TARGET_MOVE:
    {
      return "TARGET_MOVE";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_SCRIPT_NOT_READY:
    {
      return "SCRIPT_NOT_READY";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_TARGET_WARP:
    {
      return "TARGET_WARP";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_BIND_OBJECT:
    {
      return "BIND_OBJECT";
    }
    case Common::EventSceneError::EVENT_SCENE_ERROR_MAX:
    {
      return "MAX";
    }
    default:
    {
      return std::string{ "unknown" };
    }
  }
}

uint32_t EventMgr::mapEventActorToRealActor( uint32_t eventActorId )
{
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto levelInfo = exdData.getRow< Excel::Level >( eventActorId );
  if( levelInfo )
    return levelInfo->data().BaseId;
  else if( auto pObj = instanceObjectCache.getEObj( eventActorId ) )
    return pObj->data.BaseId;
  else if( auto pNpc = instanceObjectCache.getENpc( eventActorId ) )
    return pNpc->data.enpcId;

  return 0;
}

void EventMgr::handleReturnEventScene( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t errorCode,
                                       uint8_t numOfResults, const std::vector< uint32_t >& results )
{
  std::string eventName = getEventName( eventId );

  PlayerMgr::sendDebug( player, "eventId: {0} ({0:08X}) scene: {1}, errorCode: {2} numArgs: {3}",
                        eventId, sceneId, getErrorCodeName( errorCode ), numOfResults );

  uint8_t index = 0;
  for( auto r : results )
  {
    PlayerMgr::sendDebug( player, "arg#{0}: {1} ({1:08X})", index++, r );
  }

  auto eventType = static_cast< uint16_t >( eventId >> 16 );

  auto pEvent = player.getEvent( eventId );
  if( pEvent )
  {
    pEvent->setPlayedScene( false );
    // try to retrieve a stored callback
    // if there is one, proceed to call it
    Event::SceneResult result;
    result.actorId = pEvent->getActorId();
    result.eventId = eventId;
    result.sceneId = sceneId;
    result.errorCode = errorCode;
    result.numOfResults = numOfResults;
    result.results = results;

    if( eventType == Event::EventHandler::EventHandlerType::Quest )
    {
      auto questId = static_cast< uint16_t >( eventId );
      auto eventCallback = pEvent->getQuestEventReturnCallback();
      if( eventCallback )
      {
        World::Quest preQ;
        if( player.hasQuest( eventId ) )
        {
          auto questIdx = player.getQuestIndex( questId );
          auto& quest = player.getQuestByIndex( questIdx );
          preQ = quest;
          eventCallback( quest, player, result );
          if( quest != preQ )
            player.updateQuest( quest );
        }
        else
        {
          auto newQuest = World::Quest( questId, 0, 0 );
          preQ = newQuest;
          eventCallback( newQuest, player, result );
          if( newQuest != preQ )
            player.updateQuest( newQuest );
        }
      }
      else if( auto chainCallback = pEvent->getQuestSceneChainCallback() )
      {
        if( player.hasQuest( eventId ) )
        {
          auto questIdx = player.getQuestIndex( questId );
          auto& quest = player.getQuestByIndex( questIdx );
          chainCallback( quest, player );
        }
        else
        {
          auto newQuest = World::Quest( questId, 0, 0 );
          chainCallback( newQuest, player );
        }
      }
    }
    else
    {
      auto eventCallback = pEvent->getEventReturnCallback();
      if( eventCallback )
      {
        eventCallback( player, result );
      }

      // we might have a scene chain callback instead so check for that too
      else if( auto chainCallback = pEvent->getSceneChainCallback() )
        chainCallback( player );
    }
  }

  checkEvent( player, eventId );
}

void EventMgr::handleYieldEventScene( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t resumeId,
                                      uint8_t numOfResults, const std::vector< uint32_t >& results )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  std::string eventName = getEventName( eventId );

  PlayerMgr::sendDebug( player, "eventId: {0} ({0:08X}) scene: {1}, resumeId: {2} numArgs: {3}",
                        eventId, sceneId, resumeId, numOfResults );

  uint8_t index = 0;
  for( auto r : results )
  {
    PlayerMgr::sendDebug( player, "arg#{0}: {1} ({1:08X})", index++, r );
  }

  std::string tmp{};
  if( !scriptMgr.onYield( player, eventId, sceneId, resumeId, tmp, 0 ) )
  {
    PlayerMgr::sendDebug( player, "Yield not implemented in script, sending default" );
  }
}

void EventMgr::handleYieldStringEventScene( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t resumeId, const std::string& resultString )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  std::string eventName = getEventName( eventId );

  PlayerMgr::sendDebug( player, "eventId: {0} ({0:08X}) scene: {1}, resumeId: {2} resultString: {3}",
                        eventId, sceneId, resumeId, resultString );

  if( !scriptMgr.onYield( player, eventId, sceneId, resumeId, resultString, 0 ) )
  {
    PlayerMgr::sendDebug( player, "Yield not implemented in script, sending default" );
  }
}

void EventMgr::handleYieldStringIntEventScene( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t resumeId,
                                               const std::string& resultString, uint64_t resultInt )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  std::string eventName = getEventName( eventId );

  PlayerMgr::sendDebug( player, "eventId: {0} ({0:08X}) scene: {1}, resumeId: {2} resultString: {3} resultInt: {4}",
                        eventId, sceneId, resumeId, resultString, resultInt );

  if( !scriptMgr.onYield( player, eventId, sceneId, resumeId, resultString, resultInt ) )
  {
    PlayerMgr::sendDebug( player, "Yield not implemented in script, sending default" );
  }
}

void EventMgr::handleReturnStringEventScene( Entity::Player& player, uint32_t eventId, uint16_t sceneId, const std::string& resultString )
{
  std::string eventName = getEventName( eventId );

  PlayerMgr::sendDebug( player, "eventId: {0} ({0:08X}) scene: {1}, string: {2} ", eventId, sceneId, resultString );

  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto pEvent = player.getEvent( eventId );

  if( pEvent )
  {
    pEvent->setPlayedScene( false );
    // try to retrieve a stored callback
    // if there is one, proceed to call it
    Event::SceneResult result;
    result.actorId = pEvent->getActorId();
    result.eventId = eventId;
    result.sceneId = sceneId;
    result.resultString = resultString;

    if( eventType == Event::EventHandler::EventHandlerType::Quest )
    {
      auto questId = static_cast< uint16_t >( eventId );
      auto eventCallback = pEvent->getQuestEventReturnCallback();
      if( eventCallback )
      {
        World::Quest preQ;
        if( player.hasQuest( eventId ) )
        {
          auto questIdx = player.getQuestIndex( questId );
          auto& quest = player.getQuestByIndex( questIdx );
          preQ = quest;
          eventCallback( quest, player, result );
          if( quest != preQ )
            player.updateQuest( quest );
        }
        else
        {
          auto newQuest = World::Quest( questId, 0, 0 );
          preQ = newQuest;
          eventCallback( newQuest, player, result );
          if( newQuest != preQ )
            player.updateQuest( newQuest );
        }
      }
      else if( auto chainCallback = pEvent->getQuestSceneChainCallback() )
      {
        if( player.hasQuest( eventId ) )
        {
          auto questIdx = player.getQuestIndex( questId );
          auto& quest = player.getQuestByIndex( questIdx );
          chainCallback( quest, player );
        }
        else
        {
          auto newQuest = World::Quest( questId, 0, 0 );
          chainCallback( newQuest, player );
        }
      }
    }
    else
    {
      auto eventCallback = pEvent->getEventReturnCallback();
      if( eventCallback )
      {
        eventCallback( player, result );
      }

      // we might have a scene chain callback instead so check for that too
      else if( auto chainCallback = pEvent->getSceneChainCallback() )
        chainCallback( player );
    }
  }

  checkEvent( player, eventId );
}

void EventMgr::handleReturnIntAndStringEventScene( Entity::Player& player, uint32_t eventId, uint16_t sceneId, const std::string& resultString, uint64_t resultInt )
{
  std::string eventName = getEventName( eventId );

  PlayerMgr::sendDebug( player, "eventId: {0} ({0:08X}) scene: {1}, string: {2}, resultInt: {3}", eventId, sceneId, resultString, resultInt );

  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto pEvent = player.getEvent( eventId );

  if( pEvent )
  {
    pEvent->setPlayedScene( false );
    // try to retrieve a stored callback
    // if there is one, proceed to call it
    Event::SceneResult result;
    result.actorId = pEvent->getActorId();
    result.eventId = eventId;
    result.sceneId = sceneId;
    result.resultString = resultString;
    result.intResult = resultInt;

    auto eventCallback = pEvent->getEventReturnCallback();
    if( eventCallback )
    {
      eventCallback( player, result );
    }

    // we might have a scene chain callback instead so check for that too
    else if( auto chainCallback = pEvent->getSceneChainCallback() )
      chainCallback( player );
  }
}


void EventMgr::checkEvent( Sapphire::Entity::Player& player, uint32_t eventId )
{
  auto pEvent = player.getEvent( eventId );

  if( pEvent && !pEvent->hasPlayedScene() )
    eventFinish( player, eventId, 1 );
}


void EventMgr::eventFinish( Sapphire::Entity::Player& player, uint32_t eventId, uint32_t freePlayer )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto pEvent = player.getEvent( eventId );

  if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return;
  }

  if( player.getEventCount() > 1 && pEvent->getEventType() != Event::EventHandler::Nest )
  {
    // this is the parent of a nested event, we can't finish it until the parent finishes
    return;
  }

  switch( pEvent->getEventType() )
  {
    case Event::EventHandler::Nest:
    {
      server.queueForPlayer( player.getCharacterId(), std::make_shared< EventFinishPacket >( player.getId(), pEvent->getId(), pEvent->getEventType(), pEvent->getEventParam() ) );
      player.removeEvent( pEvent->getId() );

      auto callback = pEvent->getEventFinishCallback();

      if( callback )
        callback( player, pEvent->getActorId() );
      else
      {
        auto events = player.getEventListRef();
        for( const auto& it : events )
        {
          if( !it.second->hasPlayedScene() )
          {
            server.queueForPlayer( player.getCharacterId(),
                                   std::make_shared< EventFinishPacket >( player.getId(), it.second->getId(), it.second->getEventType(),
                                                                          it.second->getEventParam() ) );
            player.removeEvent( it.second->getId() );
          }
        }
      }
      break;
    }
    default:
    {
      server.queueForPlayer( player.getCharacterId(),
                             std::make_shared< EventFinishPacket >( player.getId(), pEvent->getId(), pEvent->getEventType(), pEvent->getEventParam() ) );
      break;
    }
  }

  if( player.hasStateFlag( Common::PlayerCondition::WatchingCutscene ) )
    Common::Service< World::Manager::PlayerMgr >::ref().removeCondition( player, Common::PlayerCondition::WatchingCutscene );

  player.removeEvent( pEvent->getId() );

  if( freePlayer == 1 )
    Common::Service< World::Manager::PlayerMgr >::ref().removeCondition( player, Common::PlayerCondition::InNpcEvent );
}

void EventMgr::eventStart( Entity::Player& player, uint64_t actorId, uint32_t eventId, Event::EventHandler::EventType eventType, uint8_t eventParam1,
                           uint32_t eventParam2, Event::EventHandler::EventFinishCallback callback )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto newEvent = Event::make_EventHandler( actorId, eventId, eventType, eventParam2 );
  newEvent->setEventFinishCallback( std::move( callback ) );
  player.addEvent( newEvent );

  Common::Service< World::Manager::PlayerMgr >::ref().setCondition( player, Common::PlayerCondition::InNpcEvent );

  server.queueForPlayer( player.getCharacterId(), std::make_shared< EventStartPacket >( player.getId(), actorId,
                                                                                        eventId, eventType, eventParam1, eventParam2 ) );
}

void EventMgr::eventActionStart( Entity::Player& player, uint32_t eventId, uint32_t action,
                                 World::Action::ActionCallback finishCallback, World::Action::ActionCallback interruptCallback,
                                 uint64_t additional )
{
  auto pEventAction = World::Action::make_EventAction( player.getAsChara(), eventId, action, finishCallback, interruptCallback, additional );

  auto pEvent = player.getEvent( eventId );

  if( !pEvent && player.getEventCount() )
  {
    // We're trying to play a nested event, need to start it first.
    eventStart( player, player.getId(), eventId, Event::EventHandler::Nest, 0, 0 );
    pEvent = player.getEvent( eventId );
  }
  else if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return;
  }

  if( pEvent )
    pEvent->setPlayedScene( true );

  player.setCurrentAction( pEventAction );
  pEventAction->start();
}

void EventMgr::eventItemActionStart( Entity::Player& player, uint32_t eventId, uint32_t action,
                                     uint32_t sequence, uint64_t targetId )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto eventItemData = exdData.getRow< Excel::EventItem >( action );
  if( !eventItemData )
  {
    Logger::error( "Could not find eventItem #{0}", action );
    return;
  }

  auto pEventItemAction = World::Action::make_EventItemAction( player.getAsChara(), eventId, exdData.getRow< Excel::EventItem >( action ), sequence, targetId );

  player.setCurrentAction( pEventItemAction );

  pEventItemAction->onStart();
}


void EventMgr::playGilShop( Entity::Player& player, uint32_t eventId, uint32_t flags, uint32_t param1, Event::EventHandler::SceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  if( param1 == 0 )//list items
  {
    auto& shopMgr = Common::Service< ShopMgr >::ref();
    std::vector< uint32_t > params = std::vector< uint32_t >();

    params.push_back( 201 );//unknown
    params.push_back( 1 );  //command id
    params.push_back( 40 ); //max items for sell
    params.push_back( 0 );  //flag
    uint8_t index;
    for( index = 0; index < 40; index++ )
    {
      if( uint32_t price = shopMgr.getShopItemPrices( eventId, index ) )
        params.push_back( price );
      else
        break;
    }
    params[ 2 ] = static_cast< uint32_t >( params.size() - 4 );//new max item size
    auto& exdData = Common::Service< Data::ExdData >::ref();

    for( auto it : *player.getSoldItems() )
    {
      auto item = exdData.getRow< Excel::Item >( it.first );
      params.push_back( it.first );          //itemCatalogId
      params.push_back( it.second );         //stack
      params.push_back( item->data().Price );//price
      params.push_back( 0 );                 //flag isHQ
      params.push_back( 0 );                 //numOfMateria
      params.push_back( eventId );           //shopId

      params.push_back( 0 );//signatureId
      params.push_back( 0 );//signatureId

      params.push_back( ( 1000 << 16 ) + 1000 );//durability + refine
      params.push_back( 0 );                    //stain
      params.push_back( 0 );                    //pattern

      for( uint8_t slot = 0; slot < 5; slot++ )//materia
      {
        params.push_back( 0 );
      }
    }

    playScene( player, eventId, 40, flags, params, std::move( eventCallback ) );
  }
  else if( param1 == 2 )//sell item
  {
  }
}

void EventMgr::playScene( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags, std::vector< uint32_t > values,
                          Event::EventHandler::SceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setEventReturnCallback( eventCallback );
  pEvent->setSceneChainCallback( nullptr );
  pEvent->getScenePlayParams()->setParams( scene, values );

  sendEventPlay( player, eventId, scene, flags );
}

void EventMgr::resumeScene( Entity::Player& player, uint32_t eventId, uint32_t scene, uint8_t yieldId, std::vector< uint32_t > values )
{
  FFXIVPacketBasePtr pPacket = nullptr;
  size_t paramCount = values.size();

  assert( paramCount <= 255 );

  if( paramCount < 2 )
    pPacket = std::move( std::make_shared< EventResume2Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 4 )
    pPacket = std::move( std::make_shared< EventResume4Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 8 )
    pPacket = std::move( std::make_shared< EventResume8Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 16 )
    pPacket = std::move( std::make_shared< EventResume16Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 32 )
    pPacket = std::move( std::make_shared< EventResume32Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 64 )
    pPacket = std::move( std::make_shared< EventResume64Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 128 )
    pPacket = std::move( std::make_shared< EventResume128Packet >( player, eventId, scene, yieldId, values ) );
  else if( paramCount < 255 )
    pPacket = std::move( std::make_shared< EventResume255Packet >( player, eventId, scene, yieldId, values ) );

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), pPacket );
}

void EventMgr::playScene( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags, Event::EventHandler::SceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setEventReturnCallback( std::move( eventCallback ) );
  pEvent->setSceneChainCallback( nullptr );

  sendEventPlay( player, eventId, scene, flags );
}

void EventMgr::playQuestScene( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags, Event::EventHandler::QuestSceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setQuestEventReturnCallback( std::move( eventCallback ) );
  pEvent->setSceneChainCallback( nullptr );

  sendEventPlay( player, eventId, scene, flags );
}

void EventMgr::playSceneChain( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags,
                               Sapphire::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setSceneChainCallback( std::move( sceneChainCallback ) );
  pEvent->setEventReturnCallback( nullptr );

  sendEventPlay( player, eventId, scene, flags );
}

void EventMgr::playSceneChain( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags, std::vector< uint32_t > values,
                               Sapphire::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setSceneChainCallback( sceneChainCallback );
  pEvent->setEventReturnCallback( nullptr );
  pEvent->getScenePlayParams()->setParams( scene, values );

  sendEventPlay( player, eventId, scene, flags );
}

void EventMgr::playQuestSceneChain( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags,
                                    Sapphire::Event::EventHandler::QuestSceneChainCallback sceneChainCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setQuestSceneChainCallback( std::move( sceneChainCallback ) );
  pEvent->setEventReturnCallback( nullptr );
  pEvent->setQuestEventReturnCallback( nullptr );

  sendEventPlay( player, eventId, scene, flags );
}

bool EventMgr::sendEventPlay( Entity::Player& player, uint32_t eventId, uint32_t scene, uint32_t flags )
{
  auto pEvent = player.getEvent( eventId );

  if( !pEvent )
    return false;

  FFXIVPacketBasePtr pPacket = nullptr;
  size_t paramCount = 0;
  if( auto pEventParams = pEvent->getScenePlayParams()->getParams( scene ) )
    paramCount = pEventParams->size();

  assert( paramCount <= 255 );

  if( paramCount < 2 )
    pPacket = std::move( std::make_shared< EventPlayPacket2 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 4 )
    pPacket = std::move( std::make_shared< EventPlayPacket4 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 8 )
    pPacket = std::move( std::make_shared< EventPlayPacket8 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 16 )
    pPacket = std::move( std::make_shared< EventPlayPacket16 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 32 )
    pPacket = std::move( std::make_shared< EventPlayPacket32 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 64 )
    pPacket = std::move( std::make_shared< EventPlayPacket64 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 128 )
    pPacket = std::move( std::make_shared< EventPlayPacket128 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  else if( paramCount < 255 )
    pPacket = std::move( std::make_shared< EventPlayPacket255 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), pPacket );

  return true;
}


Sapphire::Event::EventHandlerPtr EventMgr::bootstrapSceneEvent( Entity::Player& player, uint32_t eventId, uint32_t flags )
{

  auto pEvent = player.getEvent( eventId );
  if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return nullptr;
  }

  if( flags & CONDITION_CUTSCENE )
    Common::Service< World::Manager::PlayerMgr >::ref().setCondition( player, Common::PlayerCondition::WatchingCutscene );

  return pEvent;
}

void EventMgr::sendEventNotice( Entity::Player& player, uint32_t questId, int8_t noticeId, uint8_t numOfArgs, uint32_t var1, uint32_t var2 )
{
  std::vector< uint32_t > args{ var1, var2 };
  auto noticePacket = std::make_shared< EventNotice2Packet >( player, questId, noticeId, args );
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), noticePacket );
}

void EventMgr::sendNotice( Entity::Player& player, uint32_t questId, int8_t noticeId, std::vector< uint32_t > args )
{
  FFXIVPacketBasePtr pPacket = nullptr;
  size_t paramCount = args.size();

  assert( paramCount <= 32 );

  if( paramCount < 2 )
    pPacket = std::move( std::make_shared< EventNotice2Packet >( player, questId, noticeId, args ) );
  else if( paramCount < 4 )
    pPacket = std::move( std::make_shared< EventNotice4Packet >( player, questId, noticeId, args ) );
  else if( paramCount < 8 )
    pPacket = std::move( std::make_shared< EventNotice8Packet >( player, questId, noticeId, args ) );
  else if( paramCount < 16 )
    pPacket = std::move( std::make_shared< EventNotice16Packet >( player, questId, noticeId, args ) );
  else if( paramCount < 32 )
    pPacket = std::move( std::make_shared< EventNotice32Packet >( player, questId, noticeId, args ) );

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), pPacket );
}
