#include <Common.h>
#include <Exd/ExdData.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ConditionPacket.h"

#include "Script/ScriptMgr.h"

#include <Service.h>

#include "Manager/EventMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/TerritoryMgr.h"

#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"

#include "Session.h"
#include <Network/PacketDef/ClientIpcs.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;

void Sapphire::Network::GameConnection::eventHandlerTalk( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcEventHandlerTalk >( inPacket );

  const auto actorId = packet.data().actorId;
  const auto eventId = packet.data().eventId;

  std::string eventName = "onTalk";
  std::string objName = eventMgr.getEventName( eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Chara: {0} -> {1} \neventId: {2} ({3:08X})",
                                        actorId, eventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) ),
                                        eventId, eventId );


  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1}", objName, eventName );
  eventMgr.eventStart( player, actorId, eventId, Event::EventHandler::Talk, 0, 0 );

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( auto instance = pZone->getAsInstanceContent() )
  {
    instance->onTalk( player, eventId, actorId );
  }
  else
  {
    scriptMgr.onTalk( player, actorId, eventId );
  }

  eventMgr.checkEvent( player, eventId );
}

void Sapphire::Network::GameConnection::eventHandlerEmote( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcEventHandlerEmote >( inPacket );

  const auto actorId = packet.data().actorId;
  const auto eventId = packet.data().eventId;
  const auto emoteId = packet.data().emoteId;
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );

  std::string eventName = "onEmote";
  std::string objName = eventMgr.getEventName( eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Chara: {0} -> {1} \neventId: {2} ({3:08X})",
                                        actorId, eventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) ),
                                        eventId, eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1}", objName, eventName );

  eventMgr.eventStart( player, actorId, eventId, Event::EventHandler::Emote, 0, emoteId );

  if( !scriptMgr.onEmote( player, actorId, eventId, static_cast< uint8_t >( emoteId ) ) &&
      eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto questInfo = exdData.getRow< Excel::Quest >( eventId );
    if( questInfo )
      World::Manager::PlayerMgr::sendUrgent( player, "Quest not implemented: {0}",
                                             questInfo->getString( questInfo->data().Text.Name ) );
  }

  eventMgr.checkEvent( player, eventId );
}

void Sapphire::Network::GameConnection::eventHandlerWithinRange( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                 Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcEventHandlerWithinRange >( inPacket );

  const auto eventId = packet.data().eventId;
  const auto param1 = packet.data().param1;
  const auto& pos = packet.data().position;

  std::string eventName = "onWithinRange";
  std::string objName = eventMgr.getEventName( eventId );
  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1} - {2} p1: {3}", objName, eventName, eventId, param1 );

  eventMgr.eventStart( player, player.getId(), eventId, Event::EventHandler::WithinRange, 1, param1 );

  scriptMgr.onWithinRange( player, eventId, param1, pos.x, pos.y, pos.z );

  eventMgr.checkEvent( player, eventId );
}

void Sapphire::Network::GameConnection::eventHandlerOutsideRange( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                  Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcEventHandlerOutsideRange >( inPacket );
  const auto eventId = packet.data().eventId;
  const auto param1 = packet.data().param1;
  const auto& pos = packet.data().position;

  std::string eventName = "onOutsideRange";
  std::string objName = eventMgr.getEventName( eventId );
  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1} - {2} p1: {3}", objName, eventName, eventId, param1 );

  eventMgr.eventStart( player, player.getId(), eventId, Event::EventHandler::OutsideRange, 1, param1 );

  scriptMgr.onOutsideRange( player, eventId, param1, pos.x, pos.y, pos.z );

  eventMgr.checkEvent( player, eventId );
}

void Sapphire::Network::GameConnection::eventHandlerEnterTerritory( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                    Entity::Player& player )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto& teriMgr = Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );

  const auto packet = ZoneChannelPacket< FFXIVIpcEnterTerritoryHandler >( inPacket );

  const auto eventId = packet.data().eventId;
  const auto param1 = packet.data().param1;
  const auto param2 = packet.data().param2;

  std::string eventName = "onEnterTerritory";

  std::string objName = eventMgr.getEventName( eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1} - {2}", objName, eventName, eventId & 0xFFFF );

  if( auto instance = pZone->getAsInstanceContent() )
  {
    eventMgr.eventStart( player, player.getId(), eventId, Event::EventHandler::EnterTerritory, 1,
                         player.getTerritoryTypeId() );
    instance->onEnterTerritory( player, eventId, param1, param2 );
  }
  else if( auto qb = pZone->getAsQuestBattle() )
  {
    eventMgr.eventStart( player, player.getId(), eventId, Event::EventHandler::EnterTerritory, 1,
                         player.getTerritoryTypeId() );
    qb->onEnterTerritory( player, eventId, param1, param2 );
  }
  else
  {
    eventMgr.eventStart( player, player.getId(), eventId, Event::EventHandler::EnterTerritory, 0,
                         player.getTerritoryTypeId() );
    scriptMgr.onEnterTerritory( player, eventId, param1, param2 );
  }

  eventMgr.checkEvent( player, eventId );
}

void Sapphire::Network::GameConnection::returnEventSceneHeader( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventSceneHeader >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene2( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene2 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene4( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene4 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene8( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene8 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene16( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene16 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene32( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene32 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene64( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene64 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene128( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                             Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene128 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::returnEventScene255( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                             Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcReturnEventScene255 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleReturnEventScene( player, data.handlerId, data.sceneId, data.errorCode, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventSceneHeader( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                               Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventSceneHeader >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene2( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene2 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene4( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene4 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene8( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene8 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene16( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene16 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene32( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene32 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene64( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene64 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene128( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene128 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventScene255( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventScene255 >( inPacket );
  const auto& data = packet.data();

  std::vector< uint32_t > results( std::begin( data.results ), std::end( data.results ) );

  eventMgr.handleYieldEventScene( player, data.handlerId, data.sceneId, data.yieldId, data.numOfResults, results );
}

void Sapphire::Network::GameConnection::yieldEventString( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  std::string inString;

  uint16_t type = *( ( uint16_t * ) ( &inPacket.data[ 2 ] ) );
  switch( type )
  {
    case Packets::WorldPackets::Client::ClientZoneIpcType::YieldEventSceneString8:
    {
      const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventSceneString8 >( inPacket );
      inString = std::string( packet.data().result );
      break;
    }
    case Packets::WorldPackets::Client::ClientZoneIpcType::YieldEventSceneString16:
    {
      const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventSceneString16 >( inPacket );
      inString = std::string( packet.data().result );
      break;
    }
    case Packets::WorldPackets::Client::ClientZoneIpcType::YieldEventSceneString32:
    {
      const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventSceneString32 >( inPacket );
      inString = std::string( packet.data().result );
      break;
    }
  }

  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventSceneString8 >( inPacket );
  auto& data = packet.data();
  eventMgr.handleYieldStringEventScene( player, data.handlerId, data.sceneId, data.yieldId, inString );
}

void Sapphire::Network::GameConnection::yieldEventSceneIntAndString( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                     Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  std::string inString;
  const auto packet = ZoneChannelPacket< FFXIVIpcYieldEventSceneIntAndString >( inPacket );
  auto& data = packet.data();
  inString = std::string( data.str );

  eventMgr.handleYieldStringIntEventScene( player, data.handlerId, data.sceneId, data.yieldId, inString, data.integer );
}

void Sapphire::Network::GameConnection::startEventSayHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                              Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcStartSayEventHandler >( inPacket );
  const auto actorId = packet.data().targetId;
  const auto eventId = packet.data().handlerId;
  const auto sayId = packet.data().sayId;

  std::string eventName = "onSay";
  std::string objName = eventMgr.getEventName( eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Chara: {0} -> {1} \neventId: {2} ({3:08X})",
                                        actorId, eventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) ),
                                        eventId, eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1}", objName, eventName );
  eventMgr.eventStart( player, actorId, eventId, Event::EventHandler::Say, 0, 0 );
  scriptMgr.onSay( player, actorId, eventId, sayId );

  eventMgr.checkEvent( player, eventId );
}

void Sapphire::Network::GameConnection::startUiEvent( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                      Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcShopEventHandler >( inPacket );
  const auto eventId = packet.data().eventId;

  std::string eventName = "onOpen";
  std::string objName = eventMgr.getEventName( eventId );

  World::Manager::PlayerMgr::sendDebug( player, "EventId: {0} ({0:08X})", eventId );

  World::Manager::PlayerMgr::sendDebug( player, "Calling: {0}.{1}", objName, eventName );
  eventMgr.eventStart( player, player.getId(), eventId, Event::EventHandler::UI, 0, packet.data().param );

  scriptMgr.onTalk( player, player.getId(), eventId );
}
