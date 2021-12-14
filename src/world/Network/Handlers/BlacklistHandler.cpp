#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>

#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Manager/BlacklistMgr.h"

#include "Network/GameConnection.h"

#include "Actor/Player.h"
#include "WorldServer.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::getBlacklistHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto& blMgr = Common::Service< Sapphire::World::Manager::BlacklistMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcGetBlacklist >( inPacket );
  auto& data = packet.data();

  // TODO: remove this paging test!!
  /*
  for( size_t i = 0; i < 200; ++i )
  {
    player.getBlacklistID()[i] = player.getCharacterId();
  }
  */

  blMgr.onGetBlacklistPage( player, data.RequestKey, data.NextIndex );
}

void Sapphire::Network::GameConnection::blacklistAddHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto& blMgr = Common::Service< Sapphire::World::Manager::BlacklistMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcBlacklistAdd >( inPacket );
  auto& data = packet.data();

  auto resultPacket = makeZonePacket< Server::FFXIVIpcBlacklistAddResult >( player.getId() );

  std::string targetName( data.TargetCharacterName );

  auto target = server.getPlayer( targetName );

  if( !target || !blMgr.onAddCharacter( player, *target ) )
  {
    resultPacket->data().Result = 0x7; // TODO: find the correct value for each invalid arg
  }
  else
  {
    Server::BlacklistCharacter blChar;
    blChar.CharacterID = target->getCharacterId();
    strcpy( blChar.CharacterName, target->getName().c_str() );

    resultPacket->data().AddedCharacter = blChar;
    resultPacket->data().Identity = target->getGender();
    resultPacket->data().Result = 0;
  }

  queueOutPacket( resultPacket );
}

void Sapphire::Network::GameConnection::blacklistRemoveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto& blMgr = Common::Service< Sapphire::World::Manager::BlacklistMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcBlacklistRemove >( inPacket );
  auto& data = packet.data();

  auto resultPacket = makeZonePacket< Server::FFXIVIpcBlacklistRemoveResult >( player.getId() );

  std::string targetName( data.TargetCharacterName );

  auto target = server.getPlayer( targetName );

  if( !target || !blMgr.onRemoveCharacter( player, *target ) )
  {
    resultPacket->data().Result = 0x7; // TODO: find the correct value for each invalid arg
  }
  else
  {
    Server::BlacklistCharacter blChar;
    blChar.CharacterID = target->getCharacterId();
    strcpy( blChar.CharacterName, target->getName().c_str() );

    resultPacket->data().RemovedCharacter = blChar;
    resultPacket->data().Identity = target->getGender();
    resultPacket->data().Result = 0;
  }

  queueOutPacket( resultPacket );
}