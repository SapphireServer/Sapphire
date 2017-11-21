#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Network/CommonNetwork.h>
#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>
#include <src/servers/Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>

#include <boost/format.hpp>

#include "src/servers/Server_Zone/Network/GameConnection.h"
#include "src/servers/Server_Zone/Session.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ServerNoticePacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket144.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/EventStartPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/EventFinishPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "src/servers/Server_Zone/Script/ScriptManager.h"
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Forwards.h"
#include "src/servers/Server_Zone/Event/EventHelper.h"

extern Core::Scripting::ScriptManager g_scriptMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::eventHandler( const Packets::GamePacket& inPacket,
                                                  Entity::PlayerPtr pPlayer )
{
   uint16_t eventHandlerId = inPacket.getValAt< uint16_t >( 0x12 );

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
   
   case ClientZoneIpcType::TalkEventHandler: // Talk event
   {
      uint64_t actorId = inPacket.getValAt< uint64_t >( 0x20 );
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x28 );

      if( !g_scriptMgr.onTalk( pPlayer, actorId, eventId ) )
         abortEventFunc( pPlayer, actorId, eventId );
      break;
   }

   case ClientZoneIpcType::EmoteEventHandler: // Emote event
   {
      uint64_t actorId = inPacket.getValAt< uint64_t >( 0x20 );
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x28 );
      uint16_t emoteId = inPacket.getValAt< uint16_t >( 0x2C );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEmote( pPlayer, actorId, eventId, static_cast< uint8_t >( emoteId ) ) )
         abortEventFunc( pPlayer, actorId, eventId );
      break;
   }


   case ClientZoneIpcType::WithinRangeEventHandler:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x24 );
      uint32_t eventParam1 = inPacket.getValAt< uint32_t >( 0x20 );
      float x = inPacket.getValAt< float >( 0x28 );
      float y = inPacket.getValAt< float >( 0x2C );
      float z = inPacket.getValAt< float >( 0x30 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onWithinRange( pPlayer, eventId, eventParam1, x, y, z ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientZoneIpcType::OutOfRangeEventHandler:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x24 );
      uint32_t eventParam1 = inPacket.getValAt< uint32_t >( 0x20 );
      float x = inPacket.getValAt< float >( 0x28 );
      float y = inPacket.getValAt< float >( 0x2C );
      float z = inPacket.getValAt< float >( 0x30 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onOutsideRange( pPlayer, eventId, eventParam1, x, y, z ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientZoneIpcType::EnterTeriEventHandler:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x20 );
      uint16_t eventParam1 = inPacket.getValAt< uint16_t >( 0x24 );
      uint16_t eventParam2 = inPacket.getValAt< uint16_t >( 0x26 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEnterTerritory( pPlayer, eventId, eventParam1, eventParam2 ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientZoneIpcType::ReturnEventHandler:
   case ClientZoneIpcType::TradeReturnEventHandler:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x20 );
      uint16_t subEvent = inPacket.getValAt< uint16_t >( 0x24 );
      uint16_t param1 = inPacket.getValAt< uint16_t >( 0x26 );
      uint16_t param2 = inPacket.getValAt< uint16_t >( 0x28 );
      uint16_t param3 = inPacket.getValAt< uint16_t >( 0x2C );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEventHandlerReturn( pPlayer, eventId, subEvent, param1, param2, param3 ) )
         abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   case ClientZoneIpcType::LinkshellEventHandler:
   case ClientZoneIpcType::LinkshellEventHandler1:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x20 );
      uint16_t subEvent = inPacket.getValAt< uint16_t >( 0x24 );
      std::string lsName = inPacket.getStringAt( 0x27 );



      ZoneChannelPacket< FFXIVIpcEventLinkshell > linkshellEvent( pPlayer->getId() );
      linkshellEvent.data().eventId = eventId;
      linkshellEvent.data().scene = static_cast< uint8_t >(subEvent);
      linkshellEvent.data().param3 = 1;
      linkshellEvent.data().unknown1 = 0x15a;
      pPlayer->queuePacket( linkshellEvent );

//      abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   }

}




