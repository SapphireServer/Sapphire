#include <Common.h>
#include <Util/Util.h>
#include <Service.h>

#include "EventMgr.h"
#include "PlayerMgr.h"
#include "ShopMgr.h"
#include "Event/EventHandler.h"
#include "Event/Director.h"
#include "Event/EventDefs.h"

#include <Exd/ExdData.h>
#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventPlayPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/Notice2Packet.h"

#include "Territory/InstanceObjectCache.h"

#include "Territory/Territory.h"
#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"

#include "Action/EventAction.h"
#include "WorldServer.h"
#include "Actor/Player.h"

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

      std::string name = questInfo->getString( questInfo->data().Text.Name );
      std::size_t pos = name.find_first_of( "_" );

      return name.substr( 0, pos );
    }
    case Event::EventHandler::EventHandlerType::CustomTalk:
    {
      auto customTalkInfo = exdData.getRow< Excel::CustomTalk >( eventId );
      if( !customTalkInfo )
        return unknown + "CustomTalk";

      std::string name = customTalkInfo->getString( customTalkInfo->data().Text.Name );
      std::size_t pos = name.find_first_of( "_" );

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
        return "WarpTaxi";
      return unknown + "ChocoboWarp"; //who know
    }

    case Event::EventHandler::EventHandlerType::Shop:
    {
      //auto shopInfo = exdData.getRow< Excel::ShopStruct >( eventId );

      return "GilShop" + std::to_string( eventId );
      /*if( shopInfo )
      {
        if( shopInfo->name.empty() || shopInfo->name == " " )
          return "GilShop" + std::to_string( eventId );
        return shopInfo->name;
      }*/
      //return unknown + "GilShop";
    }
    default:
    {
      return unknown;
    }
  }
}

std::string EventMgr::getErrorCodeName( uint8_t errorCode )
{
  switch ( errorCode )
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


void EventMgr::checkEvent( Sapphire::Entity::Player &player, uint32_t eventId )
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

  if( player.hasStateFlag( Common::PlayerStateFlag::WatchingCutscene ) )
    player.unsetStateFlag( Common::PlayerStateFlag::WatchingCutscene );

  player.removeEvent( pEvent->getId() );

  if( freePlayer == 1 )
    player.unsetStateFlag( Common::PlayerStateFlag::InNpcEvent );
}

void EventMgr::eventStart( Entity::Player& player, uint64_t actorId, uint32_t eventId, Event::EventHandler::EventType eventType, uint8_t eventParam1,
                           uint32_t eventParam2, Event::EventHandler::EventFinishCallback callback )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto newEvent = Event::make_EventHandler( actorId, eventId, eventType, eventParam2 );
  newEvent->setEventFinishCallback( std::move( callback ) );
  player.addEvent( newEvent );

  player.setStateFlag( Common::PlayerStateFlag::InNpcEvent );

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

void EventMgr::eventItemActionStart( Entity::Player& player, uint32_t eventId, uint32_t action, World::Action::ActionCallback finishCallback,
                                     World::Action::ActionCallback interruptCallback, uint64_t additional )
{
//  Action::ActionPtr pEventItemAction = Action::make_EventItemAction( getAsChara(), eventId, action,
//                                                                     finishCallback, interruptCallback, additional );
//
//  setCurrentAction( pEventItemAction );
//
//  pEventItemAction->onStart();
}


void EventMgr::playGilShop( Entity::Player& player, uint32_t eventId, uint32_t flags, uint32_t param1, Event::EventHandler::SceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, flags );
  if( !pEvent )
    return;

  if( param1 == 0 ) //list items
  {
    auto& shopMgr = Common::Service< ShopMgr >::ref();
    std::vector< uint32_t > params = std::vector< uint32_t >();

    params.push_back( 1 ); //command id
    params.push_back( 40 ); //max items for sell
    params.push_back( 1 ); //flag
    uint8_t index;
    for( index = 0; index < 40; index++ )
    {
      if( uint32_t price = shopMgr.getShopItemPrices( eventId, index ) )
        params.push_back( price );
      else
        break;
    }
    params[ 1 ] = static_cast< uint32_t >( params.size() - 3 ); //new max item size
    auto& exdData = Common::Service< Data::ExdData >::ref();

    for( auto it = player.getSoldItems()->cbegin(); it != player.getSoldItems()->cend(); ++it )
    {
      auto item = exdData.getRow< Excel::Item >( it->first );
      params.push_back( it->first ); //itemCatalogId
      params.push_back( it->second ); //stack
      params.push_back( item->data().Price ); //price
      params.push_back( 0 );//flag isHQ
      params.push_back( 0 );//numOfMateria
      params.push_back( eventId ); //shopId

      params.push_back( 0 );//signatureId
      params.push_back( 0 );//signatureId

      params.push_back( ( 1000 << 16 ) + 1000 );//durability + refine
      params.push_back( 0 );//stain
      params.push_back( 0 );//pattern

      for( uint8_t slot = 0; slot < 5; slot++ ) //materia
      {
        params.push_back( 0 );
      }
    }

    playScene( player, eventId, 40, flags, params, std::move( eventCallback ) );
  }
  else if( param1 == 2 ) //sell item
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

void EventMgr::resumeScene( Entity::Player& player, uint32_t eventId, uint32_t scene, std::vector< uint32_t > values, bool resetCallback )
{
  auto pEvent = bootstrapSceneEvent( player, eventId, 0 );
  if( !pEvent )
    return;

  if( resetCallback )
    pEvent->setEventReturnCallback( nullptr );

  auto resumeEvent = makeZonePacket< FFXIVIpcResumeEventScene2 >( player.getId() );
  resumeEvent->data().handlerId = eventId;
  resumeEvent->data().sceneId = static_cast< uint8_t >( scene );
  resumeEvent->data().numOfArgs = static_cast< uint8_t >( values.size() );
  int i = 0;
  for( auto& val : values )
  {
    resumeEvent->data().args[ i++ ] = val;
  }
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), resumeEvent );
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
  {
    pPacket = std::move( std::make_shared< EventPlayPacket2 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if( paramCount < 4 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket4 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if( paramCount < 8 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket8 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if( paramCount < 16 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket16 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if( paramCount < 32 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket32 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if( paramCount < 64 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket64 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if( paramCount < 128 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket128 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }
  else if ( paramCount < 255 )
  {
    pPacket = std::move( std::make_shared< EventPlayPacket255 >( player, pEvent->getActorId(), pEvent->getId(), scene, flags ) );
  }

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
    player.setStateFlag( Common::PlayerStateFlag::WatchingCutscene );

  return pEvent;
}

void EventMgr::sendEventNotice( Entity::Player& player, uint32_t questId, int8_t noticeId, uint8_t numOfArgs, uint32_t var1, uint32_t var2 )
{
  auto noticePacket = std::make_shared< Notice2Packet >( player.getId(), questId, noticeId, numOfArgs, var1, var2 );
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), noticePacket );
}
