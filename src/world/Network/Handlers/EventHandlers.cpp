#include <Common.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/EventStartPacket.h"
#include "Network/PacketWrappers/EventFinishPacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "Script/ScriptMgr.h"

#include <Util/Util.h>
#include <Service.h>

#include "Event/EventHandler.h"
#include "Manager/EventMgr.h"

#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"

#include "Session.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

void Sapphire::Network::GameConnection::eventHandlerTalk( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcEventHandlerTalk >( inPacket );

  const auto actorId = packet.data().actorId;
  const auto eventId = packet.data().eventId;

  auto eventType = static_cast< Event::EventHandler::EventHandlerType >( eventId >> 16 );

  std::string eventName = "onTalk";
  std::string objName = eventMgr.getEventName( eventId );

  player.sendDebug( "Chara: {0} -> {1} \neventId: {2} ({3:08X})",
                    actorId, eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) ),
                    eventId, eventId );


  player.sendDebug( "Calling: {0}.{1}", objName, eventName );
  player.eventStart( actorId, eventId, Event::EventHandler::Talk, 0, 0 );

  if( auto instance = player.getCurrentInstance() )
  {
    instance->onTalk( player, eventId, actorId );
  }
  else if( !scriptMgr.onTalk( player, actorId, eventId ) &&
           eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto questInfo = exdData.get< Sapphire::Data::Quest >( eventId );
    if( questInfo )
      player.sendUrgent( "Quest not implemented: {0} ({1})", questInfo->name, questInfo->id );
  }

  player.checkEvent( eventId );

}

void Sapphire::Network::GameConnection::eventHandlerEmote( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcEventHandlerEmote >( inPacket );

  const auto actorId = packet.data().actorId;
  const auto eventId = packet.data().eventId;
  const auto emoteId = packet.data().emoteId;
  const auto eventType = static_cast< Event::EventHandler::EventHandlerType >( eventId >> 16 );

  std::string eventName = "onEmote";
  std::string objName = eventMgr.getEventName( eventId );

  player.sendDebug( "Chara: {0} -> {1} \neventId: {2} ({3:08X})",
                    actorId, eventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) ),
                    eventId, eventId );

  player.sendDebug( "Calling: {0}.{1}", objName, eventName );

  player.eventStart( actorId, eventId, Event::EventHandler::Emote, 0, emoteId );

  if( !scriptMgr.onEmote( player, actorId, eventId, static_cast< uint8_t >( emoteId ) ) &&
      eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto questInfo = exdData.get< Sapphire::Data::Quest >( eventId );
    if( questInfo )
      player.sendUrgent( "Quest not implemented: {0}", questInfo->name );
  }

  player.checkEvent( eventId );
}

void Sapphire::Network::GameConnection::eventHandlerWithinRange( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                 Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcEventHandlerWithinRange >( inPacket );

  const auto eventId = packet.data().eventId;
  const auto param1 = packet.data().param1;
  const auto& pos = packet.data().position;

  std::string eventName = "onWithinRange";
  std::string objName = eventMgr.getEventName( eventId );
  player.sendDebug( "Calling: {0}.{1} - {2} p1: {3}", objName, eventName, eventId, param1 );

  player.eventStart( player.getId(), eventId, Event::EventHandler::WithinRange, 1, param1 );

  scriptMgr.onWithinRange( player, eventId, param1, pos.x, pos.y, pos.z );

  player.checkEvent( eventId );
}

void Sapphire::Network::GameConnection::eventHandlerOutsideRange( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                  Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcEventHandlerOutsideRange >( inPacket );
  const auto eventId = packet.data().eventId;
  const auto param1 = packet.data().param1;
  const auto& pos = packet.data().position;

  std::string eventName = "onOutsideRange";
  std::string objName = eventMgr.getEventName( eventId );
  player.sendDebug( "Calling: {0}.{1} - {2} p1: {3}", objName, eventName, eventId, param1 );

  player.eventStart( player.getId(), eventId, Event::EventHandler::WithinRange, 1, param1 );

  scriptMgr.onOutsideRange( player, eventId, param1, pos.x, pos.y, pos.z );

  player.checkEvent( eventId );
}

void Sapphire::Network::GameConnection::eventHandlerEnterTerritory( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                    Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcEnterTerritoryHandler >( inPacket );

  const auto eventId = packet.data().eventId;
  const auto param1 = packet.data().param1;
  const auto param2 = packet.data().param2;

  std::string eventName = "onEnterTerritory";

  std::string objName = eventMgr.getEventName( eventId );

  player.sendDebug( "Calling: {0}.{1} - {2}", objName, eventName, eventId & 0xFFFF );

  if( auto instance = player.getCurrentInstance() )
  {
    player.eventStart( player.getId(), eventId, Event::EventHandler::EnterTerritory, 1, player.getZoneId() );
    instance->onEnterTerritory( player, eventId, param1, param2 );
  }
  else if( auto instance = player.getCurrentQuestBattle() )
  {
    player.eventStart( player.getId(), eventId, Event::EventHandler::EnterTerritory, 1, player.getZoneId() );
    instance->onEnterTerritory( player, eventId, param1, param2 );
  }
  else
  {
    player.eventStart( player.getId(), eventId, Event::EventHandler::EnterTerritory, 0, player.getZoneId() );
    scriptMgr.onEnterTerritory( player, eventId, param1, param2 );
  }

  player.checkEvent( eventId );
}

void Sapphire::Network::GameConnection::eventHandlerReturn( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcEventHandlerReturn >( inPacket );
  const auto eventId = packet.data().eventId;
  const auto scene = packet.data().scene;
  const auto param1 = packet.data().param1;
  const auto param2 = packet.data().param2;
  const auto param3 = packet.data().param3;
  const auto param4 = packet.data().param4;

  std::string eventName = eventMgr.getEventName( eventId );

  player.sendDebug( "eventId: {0} ({0:08X}) scene: {1}, p1: {2}, p2: {3}, p3: {4}, p4: {5}",
                    eventId, scene, param1, param2, param3, param4 );

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
      result.actorId = pEvent->getActorId();
      result.eventId = eventId;
      result.param1 = param1;
      result.param2 = param2;
      result.param3 = param3;
      result.param4 = param4;
      eventCallback( player, result );
    }
      // we might have a scene chain callback instead so check for that too
    else if( auto chainCallback = pEvent->getSceneChainCallback() )
      chainCallback( player );

  }

  player.checkEvent( eventId );

}

void Sapphire::Network::GameConnection::eventHandlerLinkshell( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                               Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcLinkshellEventHandler >( inPacket );

  auto linkshellEvent = makeZonePacket< Server::FFXIVIpcEventLinkshell >( player.getId() );
  linkshellEvent->data().eventId = packet.data().eventId;
  linkshellEvent->data().scene = static_cast< uint8_t >( packet.data().scene );
  linkshellEvent->data().param3 = 1;
  linkshellEvent->data().unknown1 = 0x15a;
  player.queuePacket( linkshellEvent );

}

void Sapphire::Network::GameConnection::eventHandlerShop( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcShopEventHandler >( inPacket );


  const auto eventId = packet.data().eventId;

  auto eventType = static_cast< uint16_t >( eventId >> 16 );

  std::string eventName = "onOpen";
  std::string objName = eventMgr.getEventName( eventId );

  player.sendDebug( "EventId: {0} ({0:08X})", eventId );

  player.sendDebug( "Calling: {0}.{1}", objName, eventName );
  player.eventStart( player.getId(), eventId, Event::EventHandler::UI, 0, packet.data().param );

  scriptMgr.onTalk( player, player.getId(), eventId );
}



