#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>

#include <Network/PacketContainer.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Manager/BlacklistMgr.h"

#include "Network/GameConnection.h"

#include "Actor/Player.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::getBlacklistHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& blMgr = Common::Service< Sapphire::World::Manager::BlacklistMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcGetBlacklist >( inPacket );
  auto& data = packet.data();

  blMgr.onGetBlacklistPage( player, data.RequestKey, data.NextIndex );
}

void Sapphire::Network::GameConnection::blacklistAddHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& blMgr = Common::Service< Sapphire::World::Manager::BlacklistMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcBlacklistAdd >( inPacket );
  auto& data = packet.data();

  std::string targetName( data.TargetCharacterName );

  blMgr.onAddCharacter( player, targetName );
}

void Sapphire::Network::GameConnection::blacklistRemoveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& blMgr = Common::Service< Sapphire::World::Manager::BlacklistMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcBlacklistRemove >( inPacket );
  auto& data = packet.data();

  std::string targetName( data.TargetCharacterName );

  blMgr.onRemoveCharacter( player, targetName );
}