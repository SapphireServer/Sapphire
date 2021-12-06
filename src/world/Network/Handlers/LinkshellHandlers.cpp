#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>

#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Network/GameConnection.h"

#include "Session.h"
#include "Actor/Player.h"
#include "Manager/LinkshellMgr.h"
#include <WorldServer.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::linkshellListHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();
  lsMgr.sendLinkshellList( player );
}

void Sapphire::Network::GameConnection::linkshellJoinHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsJoinPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellJoin >( inPacket );
  auto& server = Common::Service< World::WorldServer >::ref();
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();

  auto charName = std::string( lsJoinPacket.data().MemberCharacterName );
  auto invitedPlayer = server.getSession( charName );

  if( !invitedPlayer )
  {
    Logger::error( std::string( __FUNCTION__ ) + " requested player \"{}\" not found!", charName );
    return;
  }

  lsMgr.invitePlayer( player, *invitedPlayer->getPlayer(), lsJoinPacket.data().LinkshellID );
}


void Sapphire::Network::GameConnection::linkshellLeaveHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsLeavePacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellLeave >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();

  lsMgr.leaveLinkshell( lsLeavePacket.data().LinkshellID, player.getCharacterId() );
}

void Sapphire::Network::GameConnection::linkshellJoinOfficialHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsLeavePacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellJoinOfficial >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();

  lsMgr.joinLinkshell( lsLeavePacket.data().LinkshellID, player.getCharacterId() );
}