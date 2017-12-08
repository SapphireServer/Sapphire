#include <Server_Common/Common.h>
#include <Server_Common/Network/CommonNetwork.h>
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Network/PacketContainer.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>

#include <boost/format.hpp>

#include "Network/GameConnection.h"
#include "Session.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "Script/ScriptManager.h"
#include "Actor/Player.h"
#include "Forwards.h"
#include "Event/EventHelper.h"

extern Core::Scripting::ScriptManager g_scriptMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::eventHandler( const Packets::GamePacket& inPacket,
                                                  Entity::Player& player )
{
   uint16_t eventHandlerId = inPacket.getValAt< uint16_t >( 0x12 );

   // we need to abort the event in case it has not been scripted so the player wont be locked up
   auto abortEventFunc = []( Core::Entity::Player& player, uint64_t actorId, uint32_t eventId )
   {
      player.queuePacket( EventStartPacket( player.getId(), actorId, eventId, 1, 0, 0 ) );
      player.queuePacket( EventFinishPacket( player.getId(), eventId, 1, 0 ) );
      // this isn't ideal as it will also reset any other status that might be active
      player.queuePacket( PlayerStateFlagsPacket( player, PlayerStateFlagList{} ) );
   };

   std::string eventIdStr = boost::str( boost::format( "%|04X|" ) % static_cast< uint32_t >( eventHandlerId & 0xFFFF ) );
   player.sendDebug( "---------------------------------------" );
   player.sendDebug( "EventHandler ( " + eventIdStr + " )" );

   switch( eventHandlerId )
   {
   
   case ClientZoneIpcType::TalkEventHandler: // Talk event
   {
      uint64_t actorId = inPacket.getValAt< uint64_t >( 0x20 );
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x28 );

      if( !g_scriptMgr.onTalk( player, actorId, eventId ) )
         abortEventFunc( player, actorId, eventId );
      break;
   }

   case ClientZoneIpcType::EmoteEventHandler: // Emote event
   {
      uint64_t actorId = inPacket.getValAt< uint64_t >( 0x20 );
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x28 );
      uint16_t emoteId = inPacket.getValAt< uint16_t >( 0x2C );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEmote( player, actorId, eventId, static_cast< uint8_t >( emoteId ) ) )
         abortEventFunc( player, actorId, eventId );
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

      if( !g_scriptMgr.onWithinRange( player, eventId, eventParam1, x, y, z ) )
         abortEventFunc( player, 0, eventId );
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

      if( !g_scriptMgr.onOutsideRange( player, eventId, eventParam1, x, y, z ) )
         abortEventFunc( player, 0, eventId );
      break;
   }

   case ClientZoneIpcType::EnterTeriEventHandler:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x20 );
      uint16_t eventParam1 = inPacket.getValAt< uint16_t >( 0x24 );
      uint16_t eventParam2 = inPacket.getValAt< uint16_t >( 0x26 );

      std::string eventName = Event::getEventName( eventId );

      if( !g_scriptMgr.onEnterTerritory( player, eventId, eventParam1, eventParam2 ) )
         abortEventFunc( player, 0, eventId );
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

      if( !g_scriptMgr.onEventHandlerReturn( player, eventId, subEvent, param1, param2, param3 ) )
         abortEventFunc( player, 0, eventId );
      break;
   }

   case ClientZoneIpcType::LinkshellEventHandler:
   case ClientZoneIpcType::LinkshellEventHandler1:
   {
      uint32_t eventId = inPacket.getValAt< uint32_t >( 0x20 );
      uint16_t subEvent = inPacket.getValAt< uint16_t >( 0x24 );
      std::string lsName = inPacket.getStringAt( 0x27 );

      ZoneChannelPacket< FFXIVIpcEventLinkshell > linkshellEvent( player.getId() );
      linkshellEvent.data().eventId = eventId;
      linkshellEvent.data().scene = static_cast< uint8_t >( subEvent );
      linkshellEvent.data().param3 = 1;
      linkshellEvent.data().unknown1 = 0x15a;
      player.queuePacket( linkshellEvent );

//      abortEventFunc( pPlayer, 0, eventId );
      break;
   }

   }

}




