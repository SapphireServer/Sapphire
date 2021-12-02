#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>

#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Manager/FriendListMgr.h"

#include "Network/GameConnection.h"

#include "Actor/Player.h"
#include "WorldServer.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::friendlistRemoveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                 Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcFriendlistRemove >( inPacket );
  const auto& data = packet.data();

  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto& flMgr = Common::Service< Sapphire::World::Manager::FriendListMgr >::ref();

  auto target = server.getPlayer( data.TargetCharacterID );
  if( !target )
    return;

  flMgr.onRemoveFriend( player, *target );

  auto replyPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcFriendlistRemoveResult >( player.getId() );
  auto& replyData = replyPacket->data();

  replyData.RemovedCharacterID = target->getCharacterId();
  replyData.Identity = target->getGender();
  replyData.Result = 0;
  strcpy( replyData.RemovedCharacterName, target->getName().c_str() );

  server.queueForPlayer( player.getCharacterId(), replyPacket );
}

void Sapphire::Network::GameConnection::setFriendlistGroupHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                   Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSetFriendlistGroup >( inPacket );
  const auto& data = packet.data();

  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto& flMgr = Common::Service< Sapphire::World::Manager::FriendListMgr >::ref();

  auto target = server.getPlayer( data.TargetCharacterID );
  if( !target )
    return;

  flMgr.onAssignGroup( player, *target, data.group );
}