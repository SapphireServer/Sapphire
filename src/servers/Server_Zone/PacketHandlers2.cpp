#include <Server_Common/Common.h>
#include <Server_Common/CommonNetwork.h>
#include <Server_Common/Database.h>
#include <Server_Common/GamePacketNew.h>
#include <Server_Common/PacketContainer.h>

#include <boost/format.hpp>


#include "GameConnection.h"

#include "Session.h"
#include "Zone.h"
#include "ZonePosition.h"

#include "InitUIPacket.h"
#include "PingPacket.h"
#include "MoveActorPacket.h"
#include "ChatPacket.h"
#include "ServerNoticePacket.h"
#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"
#include "ActorControlPacket144.h"
#include "EventStartPacket.h"
#include "EventFinishPacket.h"
#include "PlayerStateFlagsPacket.h"


#include "GameCommandHandler.h"

#include "Player.h"
#include "Inventory.h"

#include "Globals.h"

#include "Forwards.h"

#include "EventHelper.h"

#include "Action.h"
#include "ActionTeleport.h"
#include "ActionCast.h"


extern Core::GameCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::skillHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                  Core::Entity::PlayerPtr pPlayer )
{

   uint32_t action = pInPacket->getValAt< uint32_t >( 0x24 );
   uint32_t useCount = pInPacket->getValAt< uint32_t >( 0x28 );

   uint64_t targetId = pInPacket->getValAt< uint64_t >( 0x30 );


   if( action < 1000000 ) // normal action
   {
      std::string actionIdStr = boost::str( boost::format( "%|04X|" ) % action );
      pPlayer->sendDebug( "---------------------------------------" );
      pPlayer->sendDebug( "ActionHandler ( " + actionIdStr + " | " + g_exdData.m_actionInfoMap[action].name + " | " + std::to_string( targetId ) + " )" );

      if( action == 5 )
      {
         auto currentAction = pPlayer->getCurrentAction();

         // we should always have an action here, if not there is a bug
         assert( currentAction );
         currentAction->onStart();
      }
      else
      {
         Core::Entity::ActorPtr targetActor;

         auto inRange = pPlayer->getInRangeActors( true );
         for( auto actor : inRange )
         {
            if( actor->getId() == targetId )
            {
               targetActor = actor;
            }
         }

         if( targetActor )
         {
            Action::ActionCastPtr pActionCast( new Action::ActionCast( pPlayer, targetActor, action ) );
            pPlayer->setCurrentAction(pActionCast);
            pPlayer->sendDebug( "setCurrentAction()" );
            pPlayer->getCurrentAction()->onStart();
         }
      }
   }
   else if( action < 2000000 ) // craft action
   {

   }
   else if( action < 3000000 ) // item action
   {
      auto info = g_exdData.getEventItemInfo( action );
      if( info )
      {
         g_log.debug( info->name );
         g_scriptMgr.onEventItem( pPlayer, action, info->eventId, info->castTime, targetId );
      }
   }
   else if( action > 3000000 ) // unknown
   {

   }

}

void Core::Network::GameConnection::eventHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                  Core::Entity::PlayerPtr pPlayer )
{
   uint16_t eventHandlerId = pInPacket->getValAt< uint16_t >( 0x12 );

   // we need to abort the event in case it has not been scripted so the player wont be locked up
   auto abortEventFunc = []( Core::Entity::PlayerPtr pPlayer, uint64_t actorId, uint32_t eventId )
   {
      pPlayer->queuePacket( EventStartPacket( pPlayer->getId(), actorId, eventId, 1, 0, 0 ) );
      pPlayer->queuePacket( EventFinishPacket( pPlayer->getId(), eventId, 1, 0 ) );
      // this isn't ideal as it will also reset any other status that might be active
      pPlayer->queuePacket( PlayerStateFlagsPacket( pPlayer, PlayerStateFlagList{} ) );
   };

   std::string eventIdStr = boost::str( boost::format( "%|04X|" ) % static_cast< uint32_t >( eventHandlerId & 0xFFFF ) );
   pPlayer->sendDebug( "---------------------------------------" );
   pPlayer->sendDebug( "EventHandler ( " + eventIdStr + " )" );

   switch( eventHandlerId )
   {
   
   case ClientIpcType::TalkEventHandler: // Talk event
   {
      uint64_t actorId = pInPacket->getValAt< uint64_t >( 0x20 );
      uint32_t eventId = pInPacket->getValAt< uint32_t >( 0x28 );

      if( !g_scriptMgr.onTalk( pPlayer, actorId, eventId ) )
         abortEventFunc( pPlayer, actorId, eventId );
      break;
   }

   case ClientIpcType::EmoteEventHandler: // Emote event
   {
      uint64_t actorId = pInPacket->getValAt< uint64_t >( 0x20 );
      uint32_t eventId = pInPacket->getValAt< uint32_t >( 0x28 );
      uint16_t emoteId = pInPacket->getValAt< uint16_t >( 0x2C );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEmote( pPlayer, actorId, eventId, emoteId ) )
         abortEventFunc( pPlayer, actorId, eventId );
      break;
   }


   case ClientIpcType::WithinRangeEventHandler:
   {
      uint32_t eventId = pInPacket->getValAt< uint32_t >( 0x24 );
      uint32_t eventParam1 = pInPacket->getValAt< uint32_t >( 0x20 );
      float x = pInPacket->getValAt< float >( 0x28 );
      float y = pInPacket->getValAt< float >( 0x2C );
      float z = pInPacket->getValAt< float >( 0x30 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onWithinRange( pPlayer, eventId, eventParam1, x, y, z ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientIpcType::OutOfRangeEventHandler:
   {
      uint32_t eventId = pInPacket->getValAt< uint32_t >( 0x24 );
      uint32_t eventParam1 = pInPacket->getValAt< uint32_t >( 0x20 );
      float x = pInPacket->getValAt< float >( 0x28 );
      float y = pInPacket->getValAt< float >( 0x2C );
      float z = pInPacket->getValAt< float >( 0x30 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onOutsideRange( pPlayer, eventId, eventParam1, x, y, z ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientIpcType::EnterTeriEventHandler: 
   {
      uint32_t eventId = pInPacket->getValAt< uint32_t >( 0x20 );
      uint16_t eventParam1 = pInPacket->getValAt< uint16_t >( 0x24 );
      uint16_t eventParam2 = pInPacket->getValAt< uint16_t >( 0x26 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEnterTerritory( pPlayer, eventId, eventParam1, eventParam2 ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientIpcType::ReturnEventHandler: 
   case ClientIpcType::TradeReturnEventHandler: 
   {
      uint32_t eventId = pInPacket->getValAt< uint32_t >( 0x20 );
      uint16_t subEvent = pInPacket->getValAt< uint16_t >( 0x24 );
      uint16_t param1 = pInPacket->getValAt< uint16_t >( 0x26 );
      uint16_t param2 = pInPacket->getValAt< uint16_t >( 0x28 );
      uint16_t param3 = pInPacket->getValAt< uint16_t >( 0x2C );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEventHandlerReturn( pPlayer, eventId, subEvent, param1, param2, param3 ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   }

}




