#include <Server_Common/Common.h>
#include <Server_Common/Network/GamePacket.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Network/PacketContainer.h>
#include <Server_Common/Config/XMLConfig.h>

#include "Player.h"

#include "Zone/Zone.h"

#include "Forwards.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventPlayPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"

#include "Action/EventAction.h"
#include "Action/EventItemAction.h"

#include "Event/Event.h"
#include "Event/Event.h"
#include "ServerZone.h"

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Entity::Player::addEvent( Event::EventPtr pEvent )
{
   m_eventMap[pEvent->getId()] = pEvent;
}

std::map< uint32_t, Core::Event::EventPtr >& Core::Entity::Player::eventList()
{
   return m_eventMap;
}

Core::Event::EventPtr Core::Entity::Player::getEvent( uint32_t eventId )
{
   auto it = m_eventMap.find( eventId );
   if( it != m_eventMap.end() )
      return it->second;

   return Event::EventPtr( nullptr );
}

size_t Core::Entity::Player::getEventCount()
{
   return m_eventMap.size();
}

void Core::Entity::Player::removeEvent( uint32_t eventId )
{
   auto it = m_eventMap.find( eventId );
   if( it != m_eventMap.end() )
   {
      auto tmpEvent = it->second;
      m_eventMap.erase( it );
   }
}

void Core::Entity::Player::checkEvent( uint32_t eventId )
{
   auto pEvent = getEvent( eventId );

   if( pEvent && !pEvent->hasPlayedScene() )
      eventFinish( eventId, 1 );
}


void Core::Entity::Player::eventStart( uint64_t actorId, uint32_t eventId, 
                                       uint8_t eventType, uint8_t eventParam1, 
                                       uint32_t eventParam2 )
{
   Event::EventPtr newEvent( new Event::Event( actorId, eventId, eventType, eventParam1, eventParam2 ) );
   addEvent( newEvent );

   setStateFlag( PlayerStateFlag::Occupied2 );
   sendStateFlags();

   EventStartPacket eventStart( getId(), actorId, eventId, eventType, eventParam1, eventParam2 );
   
   queuePacket( eventStart );
   
}

void Core::Entity::Player::eventPlay( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, uint32_t eventParam2,
                                      uint32_t eventParam3 )
{
   eventPlay( eventId, scene, flags, eventParam2, eventParam3, nullptr );
}

void Core::Entity::Player::eventPlay( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, Scripting::EventReturnCallback eventCallback )
{
   eventPlay( eventId, scene, flags, 0, 0, eventCallback );
}

void Core::Entity::Player::eventPlay( uint32_t eventId, uint32_t scene, uint32_t flags )
{
   eventPlay( eventId, scene, flags, 0, 0, nullptr );
}

void Core::Entity::Player::eventPlay( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, uint32_t eventParam2,
                                      uint32_t eventParam3, Scripting::EventReturnCallback eventCallback )
{
   if( flags & 0x02 )
   {
      setStateFlag( PlayerStateFlag::WatchingCutscene );
      sendToInRangeSet( ActorControlPacket142( getId(), SetStatusIcon,
                                               static_cast< uint8_t >( getOnlineStatus() ) ), true );
   }

   auto pEvent = getEvent( eventId );
   if( !pEvent && getEventCount() )
   {
      // We're trying to play a nested event, need to start it first.
      eventStart( getId(), eventId, Event::Event::Nest, 0, 0 );
      pEvent = getEvent( eventId );
   }
   else if( !pEvent )
   {
      g_log.error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
      return;
   }

   pEvent->setPlayedScene( true );
   pEvent->setEventReturnCallback( eventCallback );
   EventPlayPacket eventPlay( getId(), pEvent->getActorId(), pEvent->getId(),
                              scene, flags, eventParam2, eventParam3 );

   queuePacket( eventPlay );
}

void Core::Entity::Player::eventPlay( uint32_t eventId, uint32_t scene,
                                      uint32_t flags, uint32_t eventParam2,
                                      uint32_t eventParam3, uint32_t eventParam4, Scripting::EventReturnCallback eventCallback )
{
   if( flags & 0x02 )
   {
      setStateFlag( PlayerStateFlag::WatchingCutscene );
      sendToInRangeSet( ActorControlPacket142( getId(), SetStatusIcon,
                                               static_cast< uint8_t >( getOnlineStatus() ) ), true );
   }

   auto pEvent = getEvent( eventId );
   if( !pEvent && getEventCount() )
   {
      // We're trying to play a nested event, need to start it first.
      eventStart( getId(), eventId, Event::Event::Nest, 0, 0 );
      pEvent = getEvent( eventId );
   }
   else if( !pEvent )
   {
      g_log.error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
      return;
   }

   pEvent->setPlayedScene( true );
   pEvent->setEventReturnCallback( eventCallback );
   EventPlayPacket eventPlay( getId(), pEvent->getActorId(), pEvent->getId(),
                              scene, flags, eventParam2, eventParam3, eventParam4 );

   queuePacket( eventPlay );
}

void Core::Entity::Player::eventFinish( uint32_t eventId, uint32_t freePlayer )
{
   auto pEvent = getEvent( eventId );

   if( !pEvent )
   {
      g_log.error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
      return;
   }

   if( getEventCount() > 1 && pEvent->getEventType() != Event::Event::Nest )
   {
      // this is the parent of a nested event, we can't finish it until the parent finishes
      return;
   }

   switch( pEvent->getEventType() )
   {
   case Event::Event::Nest:
   {
      queuePacket( EventFinishPacket( getId(), pEvent->getId(), pEvent->getEventType(), pEvent->getEventParam3() ) );
      removeEvent( pEvent->getId() );

      auto events = eventList();

      for( auto it : events )
      {

         if( it.second->hasPlayedScene() == false )
         {
            // TODO: not happy with this, this is also prone to break wit more than one remaining event in there
            queuePacket( EventFinishPacket( getId(), it.second->getId(), it.second->getEventType(), it.second->getEventParam3() ) );
            removeEvent( it.second->getId() );
         }
      }

      break;
   }
   default:
   {
      queuePacket( EventFinishPacket( getId(), pEvent->getId(), pEvent->getEventType(), pEvent->getEventParam3() ) );
      break;
   }
   }

   if( hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
   {
      unsetStateFlag( PlayerStateFlag::WatchingCutscene );
      sendToInRangeSet( ActorControlPacket142( getId(), SetStatusIcon,
                                               static_cast< uint8_t >( getOnlineStatus() ) ), true );
   }

   removeEvent( pEvent->getId() );

   if( freePlayer == 1 )
   {
      unsetStateFlag( PlayerStateFlag::Occupied2 );
      sendStateFlags();
   }
}

void Core::Entity::Player::eventActionStart( uint32_t eventId,
                                             uint32_t action,
                                             ActionCallback finishCallback,
                                             ActionCallback interruptCallback,
                                             uint64_t additional )
{
   Action::ActionPtr pEventAction( new Action::EventAction( shared_from_this(), eventId, action,
                                                            finishCallback, interruptCallback, additional ) );

   setCurrentAction( pEventAction );
   auto pEvent = getEvent( eventId );

   if( !pEvent && getEventCount() )
   {
      // We're trying to play a nested event, need to start it first.
      eventStart( getId(), eventId, Event::Event::Nest, 0, 0 );
      pEvent = getEvent( eventId );
   }
   else if( !pEvent )
   {
      g_log.error( "Could not find event " + std::to_string( eventId ) + ", event has not been started!" );
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
   Action::ActionPtr pEventItemAction( new Action::EventItemAction( shared_from_this(), eventId, action,
                                                                    finishCallback, interruptCallback, additional ) );

   setCurrentAction( pEventItemAction );

   pEventItemAction->onStart();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Core::Entity::Player::onLogin()
{
   for( auto& child : g_serverZone.getConfig()->getChild( "Settings.Parameters.MotDArray" ) )
   {
      sendNotice( child.second.data() );
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
