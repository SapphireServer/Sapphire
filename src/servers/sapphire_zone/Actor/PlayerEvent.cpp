#include <Common.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Config/ConfigMgr.h>

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

#include "Zone/Zone.h"
#include "ServerZone.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Entity::Player::addEvent( Event::EventHandlerPtr pEvent )
{
   m_eventHandlerMap[pEvent->getId()] = pEvent;
}

std::map< uint32_t, Core::Event::EventHandlerPtr >& Core::Entity::Player::eventList()
{
   return m_eventHandlerMap;
}

Core::Event::EventHandlerPtr Core::Entity::Player::getEvent( uint32_t eventId )
{
   auto it = m_eventHandlerMap.find( eventId );
   if( it != m_eventHandlerMap.end() )
      return it->second;

   return Event::EventHandlerPtr( nullptr );
}

size_t Core::Entity::Player::getEventCount()
{
   return m_eventHandlerMap.size();
}

void Core::Entity::Player::removeEvent( uint32_t eventId )
{
   auto it = m_eventHandlerMap.find( eventId );
   if( it != m_eventHandlerMap.end() )
   {
      auto tmpEvent = it->second;
      m_eventHandlerMap.erase( it );
   }
}

void Core::Entity::Player::checkEvent( uint32_t eventId )
{
   auto pEvent = getEvent( eventId );

   if( pEvent && !pEvent->hasPlayedScene() )
      eventFinish( eventId, 1 );
}


void Core::Entity::Player::directorPlayScene( uint32_t eventId, uint32_t scene, uint32_t flags, uint32_t eventParam3,
                                              uint32_t eventParam4, uint32_t eventParam5 )
{
   if( flags & 0x02 )
      setStateFlag( PlayerStateFlag::WatchingCutscene );

   auto pEvent = getEvent( eventId );
   if( !pEvent )
   {
      auto pLog = g_fw.get< Logger >();
      pLog->error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
      return;
   }

   pEvent->setPlayedScene( true );
   pEvent->setEventReturnCallback( nullptr );
   DirectorPlayScenePacket eventPlay( getId(), getId(), pEvent->getId(),
                                      scene, flags, eventParam3, eventParam4, eventParam5 );

   queuePacket( eventPlay );
}

void Core::Entity::Player::eventStart( uint64_t actorId, uint32_t eventId, 
                                       Event::EventHandler::EventType eventType, uint8_t eventParam1,
                                       uint32_t eventParam2 )
{

   auto newEvent = Event::make_EventHandler( this, actorId, eventId, eventType, eventParam2 );

   addEvent( newEvent );

   setStateFlag( PlayerStateFlag::InNpcEvent );

   EventStartPacket eventStart( getId(), actorId, eventId, eventType, eventParam1, eventParam2 );
   
   queuePacket( eventStart );
   
}

void Core::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, uint32_t eventParam2,
                                      uint32_t eventParam3 )
{
   playScene( eventId, scene, flags, eventParam2, eventParam3, nullptr );
}

void Core::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, Event::EventHandler::SceneReturnCallback eventCallback )
{
   playScene( eventId, scene, flags, 0, 0, eventCallback );
}

void Core::Entity::Player::playScene( uint32_t eventId, uint32_t scene, uint32_t flags )
{
   playScene( eventId, scene, flags, 0, 0, nullptr );
}

void Core::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, uint32_t eventParam2,
                                      uint32_t eventParam3, Event::EventHandler::SceneReturnCallback eventCallback )
{
   playScene( eventId, scene, flags, eventParam2, eventParam3, 0, eventCallback );
}

Core::Event::EventHandlerPtr Core::Entity::Player::bootstrapSceneEvent( uint32_t eventId, uint32_t flags )
{
   if( flags & 0x02 )
      setStateFlag( PlayerStateFlag::WatchingCutscene );

   auto pEvent = getEvent( eventId );
   if( !pEvent && getEventCount() )
   {
      // We're trying to play a nested event, need to start it first.
      eventStart( getId(), eventId, Event::EventHandler::Nest, 0, 0 );
      pEvent = getEvent( eventId );
   }
   else if( !pEvent )
   {
      auto pLog = g_fw.get< Logger >();
      pLog->error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
      return nullptr;
   }

   return pEvent;
}

void Core::Entity::Player::playScene( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, uint32_t eventParam2,
                                      uint32_t eventParam3, uint32_t eventParam4, Event::EventHandler::SceneReturnCallback eventCallback )
{
   auto pEvent = bootstrapSceneEvent( eventId, flags );
   if( !pEvent )
      return;

   pEvent->setPlayedScene( true );
   pEvent->setEventReturnCallback( eventCallback );
   pEvent->setSceneChainCallback( nullptr );
   EventPlayPacket eventPlay( getId(), pEvent->getActorId(), pEvent->getId(),
                              scene, flags, eventParam2, eventParam3, eventParam4 );

   queuePacket( eventPlay );
}

void Core::Entity::Player::playSceneChain( uint32_t eventId, uint32_t scene, uint32_t flags,
                                           uint32_t eventParam2, uint32_t eventParam3, uint32_t eventParam4,
                                           Core::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
   auto pEvent = bootstrapSceneEvent( eventId, flags );
   if( !pEvent )
      return;

   pEvent->setPlayedScene( true );
   pEvent->setSceneChainCallback( sceneChainCallback );
   pEvent->setEventReturnCallback( nullptr );
   EventPlayPacket eventPlay( getId(), pEvent->getActorId(), pEvent->getId(),
                              scene, flags, eventParam2, eventParam3, eventParam4 );

   queuePacket( eventPlay );
}

void Core::Entity::Player::playSceneChain( uint32_t eventId, uint32_t scene, uint32_t flags,
                                           uint32_t eventParam2, uint32_t eventParam3,
                                           Core::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
   playSceneChain( eventId, scene, flags, eventParam2, eventParam3, 0, sceneChainCallback );
}

void Core::Entity::Player::playSceneChain( uint32_t eventId, uint32_t scene, uint32_t flags,
                                           Core::Event::EventHandler::SceneChainCallback sceneChainCallback )
{
   playSceneChain( eventId, scene, flags, 0, 0, 0, sceneChainCallback );
}

void Core::Entity::Player::eventFinish( uint32_t eventId, uint32_t freePlayer )
{
   auto pEvent = getEvent( eventId );

   if( !pEvent )
   {
      auto pLog = g_fw.get< Logger >();
      pLog->error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
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
      queuePacket( EventFinishPacket( getId(), pEvent->getId(), pEvent->getEventType(), pEvent->getEventParam() ) );
      removeEvent( pEvent->getId() );

      auto events = eventList();

      for( auto it : events )
      {

         if( it.second->hasPlayedScene() == false )
         {
            // TODO: not happy with this, this is also prone to break wit more than one remaining event in there
            queuePacket( EventFinishPacket( getId(), it.second->getId(), it.second->getEventType(),
                                            it.second->getEventParam() ) );
            removeEvent( it.second->getId() );
         }
      }

      break;
   }
   default:
   {
      queuePacket( EventFinishPacket( getId(), pEvent->getId(), pEvent->getEventType(), pEvent->getEventParam() ) );
      break;
   }
   }

   if( hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
      unsetStateFlag( PlayerStateFlag::WatchingCutscene );

   removeEvent( pEvent->getId() );

   if( freePlayer == 1 )
      unsetStateFlag( PlayerStateFlag::InNpcEvent );
}

void Core::Entity::Player::eventActionStart( uint32_t eventId,
                                             uint32_t action,
                                             ActionCallback finishCallback,
                                             ActionCallback interruptCallback,
                                             uint64_t additional )
{
   auto pEventAction = Action::make_EventAction( getAsChara(), eventId, action,
                                                 finishCallback, interruptCallback, additional );

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
      auto pLog = g_fw.get< Logger >();
      pLog->error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
      return;
   }

   if( pEvent )
      pEvent->setPlayedScene( true );
   pEventAction->onStart();
}


void Core::Entity::Player::eventItemActionStart( uint32_t eventId,
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

void Core::Entity::Player::onLogin()
{
   auto pConfig = g_fw.get< ConfigMgr >();
   auto motd = pConfig->getValue< std::string >( "General.MotD", "" );

   std::istringstream ss( motd );
   std::string msg;
   while( std::getline( ss, msg, ';' ) )
   {
      sendNotice( msg );
   }
}

void Core::Entity::Player::onZoneStart()
{

}

void Core::Entity::Player::onZoneDone()
{

}

void Core::Entity::Player::onDeath()
{

}

// TODO: slightly ugly here and way too static. Needs too be done properly
void Core::Entity::Player::onTick()
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
