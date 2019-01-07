#include <Common.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventPlayPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/DirectorPlayScenePacket.h"

#include "Action/EventAction.h"
#include "Action/EventItemAction.h"

#include "Territory/Zone.h"
#include "ServerMgr.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

void Sapphire::Entity::Player::addEvent( Event::EventHandlerPtr pEvent )
{
  m_eventHandlerMap[ pEvent->getId() ] = pEvent;
}

std::map< uint32_t, Sapphire::Event::EventHandlerPtr >& Sapphire::Entity::Player::eventList()
{
  return m_eventHandlerMap;
}

Sapphire::Event::EventHandlerPtr Sapphire::Entity::Player::getEvent( uint32_t eventId )
{
  auto it = m_eventHandlerMap.find( eventId );
  if( it != m_eventHandlerMap.end() )
    return it->second;

  return Event::EventHandlerPtr( nullptr );
}

size_t Sapphire::Entity::Player::getEventCount()
{
  return m_eventHandlerMap.size();
}

void Sapphire::Entity::Player::removeEvent( uint32_t eventId )
{
  auto it = m_eventHandlerMap.find( eventId );
  if( it != m_eventHandlerMap.end() )
  {
    auto tmpEvent = it->second;
    m_eventHandlerMap.erase( it );
  }
}

void Sapphire::Entity::Player::checkEvent( uint32_t eventId )
{
  auto pEvent = getEvent( eventId );

  if( pEvent && !pEvent->hasPlayedScene() )
    eventFinish( eventId, 1 );
}


void Sapphire::Entity::Player::directorPlayScene( uint32_t eventId, uint32_t scene, uint32_t flags, uint32_t eventParam3,
                                                  uint32_t eventParam4, uint32_t eventParam5 )
{
  if( flags & 0x02 )
    setStateFlag( PlayerStateFlag::WatchingCutscene );

  auto pEvent = getEvent( eventId );
  if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return;
  }

  pEvent->setPlayedScene( true );
  pEvent->setEventReturnCallback( nullptr );
  auto eventPlay = std::make_shared< DirectorPlayScenePacket >( getId(), getId(), pEvent->getId(),
                                                                scene, flags, eventParam3, eventParam4, eventParam5 );

  queuePacket( eventPlay );
}

void Sapphire::Entity::Player::eventStart( uint64_t actorId, uint32_t eventId,
                                           Event::EventHandler::EventType eventType, uint8_t eventParam1,
                                           uint32_t eventParam2, Event::EventHandler::EventFinishCallback callback )
{

  auto newEvent = Event::make_EventHandler( this, actorId, eventId, eventType, eventParam2 );

  newEvent->setEventFinishCallback( callback );

  addEvent( newEvent );

  setStateFlag( PlayerStateFlag::InNpcEvent );

  auto eventStart = std::make_shared< EventStartPacket >( getId(), actorId, eventId,
                                                          eventType, eventParam1, eventParam2 );

  queuePacket( eventStart );

}

void Sapphire::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                          uint32_t flags, uint32_t eventParam2,
                                          uint32_t eventParam3 )
{
  playScene( eventId, scene, flags, eventParam2, eventParam3, nullptr );
}

void Sapphire::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                          uint32_t flags, Event::EventHandler::SceneReturnCallback eventCallback )
{
  playScene( eventId, scene, flags, 0, 0, eventCallback );
}

void Sapphire::Entity::Player::playScene( uint32_t eventId, uint32_t scene, uint32_t flags )
{
  playScene( eventId, scene, flags, 0, 0, nullptr );
}

void Sapphire::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                          uint32_t flags, uint32_t eventParam2,
                                          uint32_t eventParam3, Event::EventHandler::SceneReturnCallback eventCallback )
{
  playScene( eventId, scene, flags, eventParam2, eventParam3, 0, eventCallback );
}

void Sapphire::Entity::Player::playGilShop( uint32_t eventId, uint32_t flags,
                                            Event::EventHandler::SceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setEventReturnCallback( eventCallback );
  pEvent->setSceneChainCallback( nullptr );

  auto openGilShopPacket = makeZonePacket< Server::FFXIVIpcEventOpenGilShop >( getId() );
  openGilShopPacket->data().eventId = eventId;
  openGilShopPacket->data().sceneFlags = flags;
  openGilShopPacket->data().actorId = getId();

  openGilShopPacket->data().scene = 10;

  queuePacket( openGilShopPacket );
}

Sapphire::Event::EventHandlerPtr Sapphire::Entity::Player::bootstrapSceneEvent( uint32_t eventId, uint32_t flags )
{

  auto pEvent = getEvent( eventId );
  if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return nullptr;
  }

  if( flags & 0x02 )
    setStateFlag( PlayerStateFlag::WatchingCutscene );

  return pEvent;
}

void Sapphire::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                          uint32_t flags, uint32_t eventParam2,
                                          uint32_t eventParam3, uint32_t eventParam4,
                                          Event::EventHandler::SceneReturnCallback eventCallback )
{
  auto pEvent = bootstrapSceneEvent( eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setEventReturnCallback( eventCallback );
  pEvent->setSceneChainCallback( nullptr );
  auto eventPlay = std::make_shared< EventPlayPacket >( getId(), pEvent->getActorId(), pEvent->getId(),
                                                        scene, flags, eventParam2, eventParam3, eventParam4 );

  queuePacket( eventPlay );
}

void Sapphire::Entity::Player::playSceneChain( uint32_t eventId, uint32_t scene, uint32_t flags,
                                               uint32_t eventParam2, uint32_t eventParam3, uint32_t eventParam4,
                                               Sapphire::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
  auto pEvent = bootstrapSceneEvent( eventId, flags );
  if( !pEvent )
    return;

  pEvent->setPlayedScene( true );
  pEvent->setSceneChainCallback( sceneChainCallback );
  pEvent->setEventReturnCallback( nullptr );
  auto eventPlay = std::make_shared< EventPlayPacket >( getId(), pEvent->getActorId(), pEvent->getId(),
                                                        scene, flags, eventParam2, eventParam3, eventParam4 );

  queuePacket( eventPlay );
}

void Sapphire::Entity::Player::playSceneChain( uint32_t eventId, uint32_t scene, uint32_t flags,
                                               uint32_t eventParam2, uint32_t eventParam3,
                                               Sapphire::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
  playSceneChain( eventId, scene, flags, eventParam2, eventParam3, 0, sceneChainCallback );
}

void Sapphire::Entity::Player::playSceneChain( uint32_t eventId, uint32_t scene, uint32_t flags,
                                               Sapphire::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
  playSceneChain( eventId, scene, flags, 0, 0, 0, sceneChainCallback );
}

void Sapphire::Entity::Player::eventFinish( uint32_t eventId, uint32_t freePlayer )
{
  auto pEvent = getEvent( eventId );

  if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return;
  }

  if( getEventCount() > 1 && pEvent->getEventType() != Event::EventHandler::Nest )
  {
    // this is the parent of a nested event, we can't finish it until the parent finishes
    return;
  }

  switch( pEvent->getEventType() )
  {
    case Event::EventHandler::Nest:
    {
      queuePacket( std::make_shared< EventFinishPacket >( getId(), pEvent->getId(),
                                                          pEvent->getEventType(), pEvent->getEventParam() ) );
      removeEvent( pEvent->getId() );

      auto callback = pEvent->getEventFinishCallback();

      if( callback )
        callback( *this, pEvent->getActorId() );
      else
      {
        auto events = eventList();
        for( auto it : events )
        {
          if( !it.second->hasPlayedScene() )
          {
            queuePacket( std::make_shared< EventFinishPacket >( getId(), it.second->getId(),
                                                                it.second->getEventType(),
                                                                it.second->getEventParam() ) );
            removeEvent( it.second->getId() );
          }
        }
      }
      break;
    }
    default:
    {
      queuePacket( std::make_shared< EventFinishPacket >( getId(), pEvent->getId(),
                                                          pEvent->getEventType(), pEvent->getEventParam() ) );
      break;
    }
  }

  if( hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
    unsetStateFlag( PlayerStateFlag::WatchingCutscene );

  removeEvent( pEvent->getId() );

  if( freePlayer == 1 )
    unsetStateFlag( PlayerStateFlag::InNpcEvent );
}

void Sapphire::Entity::Player::eventActionStart( uint32_t eventId,
                                                 uint32_t action,
                                                 ActionCallback finishCallback,
                                                 ActionCallback interruptCallback,
                                                 uint64_t additional )
{
  auto pEventAction = Action::make_EventAction( getAsChara(), eventId, action,
                                                finishCallback, interruptCallback, additional, m_pFw );

  setCurrentAction( pEventAction );
  auto pEvent = getEvent( eventId );

  if( !pEvent && getEventCount() )
  {
    // We're trying to play a nested event, need to start it first.
    eventStart( getId(), eventId, Event::EventHandler::Nest, 0, 0 );
    pEvent = getEvent( eventId );
  }
  else if( !pEvent )
  {
    Logger::error( "Could not find event #{0}, event has not been started!", eventId );
    return;
  }

  if( pEvent )
    pEvent->setPlayedScene( true );
  pEventAction->onStart();
}


void Sapphire::Entity::Player::eventItemActionStart( uint32_t eventId,
                                                     uint32_t action,
                                                     ActionCallback finishCallback,
                                                     ActionCallback interruptCallback,
                                                     uint64_t additional )
{
  Action::ActionPtr pEventItemAction = Action::make_EventItemAction( getAsChara(), eventId, action,
                                                                     finishCallback, interruptCallback, additional );

  setCurrentAction( pEventItemAction );

  pEventItemAction->onStart();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sapphire::Entity::Player::onLogin()
{
  auto pServerMgr = m_pFw->get< Sapphire::World::ServerMgr >();
  auto motd = pServerMgr->getConfig().motd;

  std::istringstream ss( motd );
  std::string msg;
  while( std::getline( ss, msg, ';' ) )
  {
    sendNotice( msg );
  }
}

void Sapphire::Entity::Player::onZoneStart()
{

}

void Sapphire::Entity::Player::onZoneDone()
{

}

void Sapphire::Entity::Player::onDeath()
{

}

// TODO: slightly ugly here and way too static. Needs too be done properly
void Sapphire::Entity::Player::onTick()
{

  bool sendUpdate = false;

  if( !isAlive() || !isLoadingComplete() )
    return;

  uint32_t addHp = static_cast< uint32_t >( getMaxHp() * 0.1f + 1 );
  uint32_t addMp = static_cast< uint32_t >( getMaxMp() * 0.06f + 1 );
  uint32_t addTp = 100;

  if( !m_actorIdTohateSlotMap.empty() )
  {
    addHp = static_cast< uint32_t >( getMaxHp() * 0.01f + 1 );
    addMp = static_cast< uint32_t >( getMaxMp() * 0.02f + 1 );
    addTp = 60;
  }

  if( m_hp < getMaxHp() )
  {

    if( m_hp + addHp < getMaxHp() )
      m_hp += addHp;
    else
      m_hp = getMaxHp();

    sendUpdate = true;
  }

  if( m_mp < getMaxMp() )
  {

    if( m_mp + addMp < getMaxMp() )
      m_mp += addMp;
    else
      m_mp = getMaxMp();

    sendUpdate = true;
  }

  if( m_tp < 1000 )
  {
    if( m_tp + addTp < 1000 )
      m_tp += addTp;
    else
      m_tp = 1000;

    sendUpdate = true;
  }

  if( sendUpdate )
    sendStatusUpdate();
}
