#include <boost/format.hpp>

#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <sapphire_zone/Event/EventHandler.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "Script/ScriptMgr.h"

#include "Event/EventHelper.h"

#include "Zone/InstanceContent.h"

#include "Session.h"

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::eventHandlerTalk( const Packets::GamePacket& inPacket, Entity::Player& player )
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto actorId = inPacket.getValAt< uint64_t >( 0x20 );
   auto eventId = inPacket.getValAt< uint32_t >( 0x28 );
   auto eventType = static_cast< uint16_t >( eventId >> 16 );

   std::string eventName = "onTalk";
   std::string objName = Event::getEventName( eventId );

   player.sendDebug( "Chara: " +
                     std::to_string( actorId ) + " -> " +
                     std::to_string( Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) ) ) +
                     " \neventId: " +
                     std::to_string( eventId ) +
                     " (0x" + boost::str( boost::format( "%|08X|" )
                                          % static_cast< uint64_t >( eventId & 0xFFFFFFF ) ) + ")" );


   player.sendDebug( "Calling: " + objName + "." + eventName );
   player.eventStart( actorId, eventId, Event::EventHandler::Talk, 0, 0 );


   if( auto instance = player.getCurrentInstance() )
   {
      instance->onTalk( player, eventId, actorId );
   }
   else if( !pScriptMgr->onTalk( player, actorId, eventId ) &&
            eventType == Event::EventHandler::EventHandlerType::Quest )
   {
      auto questInfo = pExdData->get< Core::Data::Quest >( eventId );
      if( questInfo )
         player.sendUrgent( "Quest not implemented: " + questInfo->name + " (" + questInfo->id + ")" );
   }

   player.checkEvent( eventId );

}

void Core::Network::GameConnection::eventHandlerEmote( const Packets::GamePacket& inPacket, Entity::Player& player )
{

   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto actorId = inPacket.getValAt< uint64_t >( 0x20 );
   auto eventId = inPacket.getValAt< uint32_t >( 0x28 );
   auto emoteId = inPacket.getValAt< uint16_t >( 0x2C );
   auto eventType = static_cast< uint16_t >( eventId >> 16 );

   std::string eventName = "onEmote";
   std::string objName = Event::getEventName( eventId );

   player.sendDebug( "Chara: " +
                     std::to_string( actorId ) + " -> " +
                     std::to_string( Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) ) ) +
                     " \neventId: " +
                     std::to_string( eventId ) +
                     " (0x" + boost::str( boost::format( "%|08X|" )
                                          % static_cast< uint64_t >( eventId & 0xFFFFFFF ) ) + ")" );

   player.sendDebug( "Calling: " + objName + "." + eventName );

   player.eventStart( actorId, eventId, Event::EventHandler::Emote, 0, emoteId );

   if( !pScriptMgr->onEmote( player, actorId, eventId, static_cast< uint8_t >( emoteId ) )  &&
       eventType == Event::EventHandler::EventHandlerType::Quest )
   {
      auto questInfo = pExdData->get< Core::Data::Quest >( eventId );
      if( questInfo )
         player.sendUrgent( "Quest not implemented: " + questInfo->name );
   }

   player.checkEvent( eventId );
}

void Core::Network::GameConnection::eventHandlerWithinRange( const Packets::GamePacket& inPacket,
                                                             Entity::Player& player )
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   auto eventId = inPacket.getValAt< uint32_t >( 0x24 );
   auto param1 = inPacket.getValAt< uint32_t >( 0x20 );
   auto x = inPacket.getValAt< float >( 0x28 );
   auto y = inPacket.getValAt< float >( 0x2C );
   auto z = inPacket.getValAt< float >( 0x30 );

   std::string eventName = "onWithinRange";
   std::string objName = Event::getEventName( eventId );
   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) +
                     " p1: " + std::to_string( param1 ) );

   player.eventStart( player.getId(), eventId, Event::EventHandler::WithinRange, 1, param1 );

   pScriptMgr->onWithinRange( player, eventId, param1, x, y, z );

   player.checkEvent( eventId );
}

void Core::Network::GameConnection::eventHandlerOutsideRange( const Packets::GamePacket& inPacket,
                                                              Entity::Player& player )
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   auto eventId = inPacket.getValAt< uint32_t >( 0x24 );
   auto param1 = inPacket.getValAt< uint32_t >( 0x20 );
   auto x = inPacket.getValAt< float >( 0x28 );
   auto y = inPacket.getValAt< float >( 0x2C );
   auto z = inPacket.getValAt< float >( 0x30 );

   std::string eventName = "onOutsideRange";
   std::string objName = Event::getEventName( eventId );
   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) +
                     " p1: " + std::to_string( param1 ) );

   player.eventStart( player.getId(), eventId, Event::EventHandler::WithinRange, 1, param1 );

   pScriptMgr->onOutsideRange( player, eventId, param1, x, y, z );

   player.checkEvent( eventId );
}

void Core::Network::GameConnection::eventHandlerEnterTerritory( const Packets::GamePacket &inPacket,
                                                                Entity::Player &player )
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   auto eventId = inPacket.getValAt< uint32_t >( 0x20 );
   auto param1 = inPacket.getValAt< uint16_t >( 0x24 );
   auto param2 = inPacket.getValAt< uint16_t >( 0x26 );

   std::string eventName = "onEnterTerritory";

   std::string objName = Event::getEventName( eventId );

   player.sendDebug( "Calling: " + objName + "." + eventName + " - " + std::to_string( eventId ) );

   if( auto instance = player.getCurrentInstance() )
   {
      player.eventStart( player.getId(), eventId, Event::EventHandler::EnterTerritory, 1, player.getZoneId() );
      instance->onEnterTerritory( player, eventId, param1, param2 );
   }
   else
   {
      player.eventStart( player.getId(), eventId, Event::EventHandler::EnterTerritory, 0, player.getZoneId() );
      pScriptMgr->onEnterTerritory( player, eventId, param1, param2 );
   }

   player.checkEvent( eventId );
}

void Core::Network::GameConnection::eventHandlerReturn( const Packets::GamePacket &inPacket,
                                                        Entity::Player &player )
{
   auto eventId = inPacket.getValAt< uint32_t >( 0x20 );
   auto scene = inPacket.getValAt< uint16_t >( 0x24 );
   auto param1 = inPacket.getValAt< uint16_t >( 0x26 );
   auto param2 = inPacket.getValAt< uint16_t >( 0x28 );
   auto param3 = inPacket.getValAt< uint16_t >( 0x2C );

   std::string eventName = Event::getEventName( eventId );

   player.sendDebug( "eventId: " +
                     std::to_string( eventId ) +
                     " ( 0x" + boost::str( boost::format( "%|08X|" ) % ( uint64_t ) ( eventId & 0xFFFFFFF ) ) + " ) " +
                     " scene: " + std::to_string( scene ) +
                     " p1: " + std::to_string( param1 ) +
                     " p2: " + std::to_string( param2 ) +
                     " p3: " + std::to_string( param3 ) );

   auto pEvent = player.getEvent( eventId );
   if( pEvent )
   {
      pEvent->setPlayedScene( false );
      // try to retrieve a stored callback
      auto eventCallback = pEvent->getEventReturnCallback();
      // if there is one, proceed to call it
      if( eventCallback )
      {
         Event::SceneResult result;
         result.eventId = eventId;
         result.param1 = param1;
         result.param2 = param2;
         result.param3 = param3;
         eventCallback( player, result );
      }
      // we might have a scene chain callback instead so check for that too
      else if( auto chainCallback = pEvent->getSceneChainCallback() )
         chainCallback( player );

   }

   player.checkEvent( eventId );

}

void Core::Network::GameConnection::eventHandlerLinkshell( const Packets::GamePacket &inPacket,
                                                           Entity::Player &player )
{
   auto eventId = inPacket.getValAt< uint32_t >( 0x20 );
   auto scene = inPacket.getValAt< uint16_t >( 0x24 );
   auto lsName = inPacket.getStringAt( 0x27 );

   ZoneChannelPacket< FFXIVIpcEventLinkshell > linkshellEvent( player.getId() );
   linkshellEvent.data().eventId = eventId;
   linkshellEvent.data().scene = static_cast< uint8_t >( scene );
   linkshellEvent.data().param3 = 1;
   linkshellEvent.data().unknown1 = 0x15a;
   player.queuePacket( linkshellEvent );

}


