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
#include "Logging/Logger.h"
#include "Manager/PlayerMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::pcPartyLeaveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                             Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  partyMgr.onLeave( player );
}

void Sapphire::Network::GameConnection::pcPartyDisbandHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                               Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  partyMgr.onDisband( player );
}

void Sapphire::Network::GameConnection::pcPartyKickHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPcPartyKick >( inPacket );
  const auto& data = packet.data();

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto kickedName = std::string( data.LeaveCharacterName );
  auto pKickedPlayer = playerMgr.getPlayer( kickedName );
  if( !pKickedPlayer )
  {
    Logger::error( "Target player for kicking not found (\"{t}\")", kickedName );
    return;
  }


  partyMgr.onKick( *pKickedPlayer, player );
}

void Sapphire::Network::GameConnection::pcPartyChangeLeaderHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                    Entity::Player& player )
{
  if( player.getPartyId() == 0 )
    return;

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcPcPartyChangeLeader >( inPacket );
  const auto& data = packet.data();

  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  auto leaderName = std::string( data.NextLeaderCharacterName );
  auto pNewLeader = playerMgr.getPlayer( leaderName );

  if( !pNewLeader )
  {
    Logger::error( "Target player for new leader not found (\"{t}\")", leaderName );
    return;
  }

  partyMgr.onChangeLeader( *pNewLeader, player );
}
