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
#include "Manager/PlayerMgr.h"
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

void Sapphire::Network::GameConnection::linkshellKickHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsKickPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellKick >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();

  auto playerPtr = playerMgr.getPlayer( lsKickPacket.data().LeaveCharacterID );

  if( !playerPtr )
  {
    Logger::error( std::string( __FUNCTION__ ) + " requested player \"{}\" not found!", lsKickPacket.data().LeaveCharacterName );
    return;
  }

  lsMgr.kickPlayer( player, *playerPtr, lsKickPacket.data().LinkshellID );

}

void Sapphire::Network::GameConnection::linkshellAddLeaderHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsAddLeaderPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellAddLeader >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();

  auto playerPtr = playerMgr.getPlayer( lsAddLeaderPacket.data().MemberCharacterID );

  if( !playerPtr )
  {
    Logger::error( std::string( __FUNCTION__ ) + " requested player \"{}\" not found!", lsAddLeaderPacket.data().MemberCharacterName );
    return;
  }

  lsMgr.addLeader( player, *playerPtr, lsAddLeaderPacket.data().LinkshellID );

}

void Sapphire::Network::GameConnection::linkshellRemoveLeaderHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsRemoveLeaderPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellRemoveLeader >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();

  auto playerPtr = playerMgr.getPlayer( lsRemoveLeaderPacket.data().MemberCharacterID );

  if( !playerPtr )
  {
    Logger::error( std::string( __FUNCTION__ ) + " requested player \"{}\" not found!", lsRemoveLeaderPacket.data().MemberCharacterName );
    return;
  }

  lsMgr.removeLeader( player, *playerPtr, lsRemoveLeaderPacket.data().LinkshellID );

}

void Sapphire::Network::GameConnection::linkshellDeclineLeaderHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsDeclineLeaderPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellDeclineLeader >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();

  lsMgr.declineLeader( player, lsDeclineLeaderPacket.data().LinkshellID );

}

void Sapphire::Network::GameConnection::linkshellJoinHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsJoinPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellJoin >( inPacket );
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();

  auto charName = std::string( lsJoinPacket.data().MemberCharacterName );
  auto invitedPlayer = playerMgr.getPlayer( charName );

  if( !invitedPlayer )
  {
    Logger::error( std::string( __FUNCTION__ ) + " requested player \"{}\" not found!", charName );
    return;
  }

  lsMgr.invitePlayer( player, *invitedPlayer, lsJoinPacket.data().LinkshellID );
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

void Sapphire::Network::GameConnection::linkshellChangeMasterHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto lsChMasterPacket = ZoneChannelPacket< Client::FFXIVIpcLinkshellChangeMaster >( inPacket );
  auto& lsMgr = Common::Service< LinkshellMgr >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();

  auto charName = std::string( lsChMasterPacket.data().NextMasterCharacterName );
  auto nextMaster = playerMgr.getPlayer( charName );

  if( !nextMaster )
  {
    Logger::error( std::string( __FUNCTION__ ) + " requested player \"{}\" not found!", charName );
    return;
  }

  lsMgr.changeMaster( player, *nextMaster, lsChMasterPacket.data().LinkshellID );
}