#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>

#include <Network/PacketContainer.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Manager/PartyMgr.h"

#include "Network/GameConnection.h"

#include "Session.h"
#include "Actor/Player.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::partyLeaveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                             Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  partyMgr.onLeave( player );

}

void Sapphire::Network::GameConnection::partyDisbandHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                               Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  partyMgr.onDisband( player );

}

void Sapphire::Network::GameConnection::partyKickHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPartyKickHandler >( inPacket );
  const auto& data = packet.data();

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  partyMgr.onKick( std::string( data.name ), player );

}

void Sapphire::Network::GameConnection::partyChangeLeaderHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                    Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPartyChangeLeaderHandler >( inPacket );
  const auto& data = packet.data();

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  partyMgr.onChangeLeader( std::string( data.name ), player );

}
