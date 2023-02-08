#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>

#include <datReader/DatCategories/bg/LgbTypes.h>

#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Service.h>

#include "Network/GameConnection.h"
#include "Session.h"

#include "Territory/Territory.h"

#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/InviteUpdatePacket.h"

#include "Manager/FriendListMgr.h"
#include "Manager/PartyMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/FreeCompanyMgr.h"

#include "Action/Action.h"

#include "WorldServer.h"
#include "Forwards.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::inviteHandler( const FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcInvite >( inPacket );

  PlayerMgr::sendDebug( player, "Auth Type#{0}", packet.data().AuthType );
  PlayerMgr::sendDebug( player, "Target Name: {0}", packet.data().TargetName );

  std::string name( packet.data().TargetName );

  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto pTargetPlayer = server.getPlayer( name );

  if( !pTargetPlayer )
    return;

  switch( packet.data().AuthType )
  {
    case HierarchyType::PCPARTY:
    {
      auto inviteResultPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.AuthType = packet.data().AuthType;
      strcpy( data.TargetName, packet.data().TargetName );
      server.queueForPlayer( player.getCharacterId(), inviteResultPacket );

      auto invitePacket = makeInviteUpdatePacket( player, Common::Util::getTimeSeconds() + 30, packet.data().AuthType, 1, InviteUpdateType::NEW_INVITE );
      server.queueForPlayer( pTargetPlayer->getCharacterId(), invitePacket );

      break;
    }

    case HierarchyType::FRIENDLIST:
    {
      auto inviteResultPacket = makeZonePacket< FFXIVIpcInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.AuthType = packet.data().AuthType;
      strcpy( data.TargetName, packet.data().TargetName );
      server.queueForPlayer( player.getCharacterId(), inviteResultPacket );

      auto invitePacket = makeInviteUpdatePacket( player, 0, packet.data().AuthType, 1, InviteUpdateType::NEW_INVITE );
      server.queueForPlayer( pTargetPlayer->getCharacterId(), invitePacket );
      auto& flMgr = Common::Service< FriendListMgr >::ref();

      // add support to adding offline players
      auto target = server.getPlayer( data.TargetName );
      if( !target )
        return;

      flMgr.onInviteCreate( player, *target );

      break;
    }
    case HierarchyType::AUTOPARTY:
      break;
    case HierarchyType::FCCREATE:
    {
      auto inviteResultPacket = makeZonePacket< FFXIVIpcInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.AuthType = packet.data().AuthType;
      strcpy( data.TargetName, packet.data().TargetName );
      server.queueForPlayer( player.getCharacterId(), inviteResultPacket );

      auto invitePacket = makeInviteUpdatePacket( player, Common::Util::getTimeSeconds() + 300, packet.data().AuthType, 1, InviteUpdateType::NEW_INVITE );
      server.queueForPlayer( pTargetPlayer->getCharacterId(), invitePacket );
      break;
    }
    case HierarchyType::FREECOMPANY:
    {
      auto inviteResultPacket = makeZonePacket< FFXIVIpcInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.AuthType = packet.data().AuthType;
      strcpy( data.TargetName, packet.data().TargetName );
      server.queueForPlayer( player.getCharacterId(), inviteResultPacket );

      auto invitePacket = makeInviteUpdatePacket( player, Common::Util::getTimeSeconds() + 300, packet.data().AuthType, 1, InviteUpdateType::NEW_INVITE );
      server.queueForPlayer( pTargetPlayer->getCharacterId(), invitePacket );
      break;
    }
    case HierarchyType::FCJOINREQUEST:
      break;
    case HierarchyType::PARTYCANCEL:
      break;
  }
}

void Sapphire::Network::GameConnection::inviteReplyHandler( const FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcInviteReply >( inPacket );
  const auto& data = packet.data();

  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto pPlayer = server.getPlayer( data.InviteCharacterID );

  if( !pPlayer )
    return;

  auto inviteReplyPacket = makeZonePacket< FFXIVIpcInviteReplyResult >( player.getId() );
  auto& inviteReplyData = inviteReplyPacket->data();
  inviteReplyData.Answer = data.Answer;

  switch( data.AuthType )
  {
    case HierarchyType::PCPARTY:
    {
      auto& partyMgr = Common::Service< PartyMgr >::ref();

      uint8_t result = InviteUpdateType::REJECT_INVITE;
      if( data.Answer == InviteReplyType::ACCEPT )
      {
        partyMgr.onJoin( player.getId(), pPlayer->getId() );
        result = InviteUpdateType::ACCEPT_INVITE;
      }

      auto inviteUpPacket = makeInviteUpdatePacket( player, Common::Util::getTimeSeconds() + 30, data.AuthType, 1, result );
      server.queueForPlayer( pPlayer->getCharacterId(), inviteUpPacket );

      inviteReplyData.AuthType = data.AuthType;
      strcpy( inviteReplyData.InviteCharacterName, pPlayer->getName().c_str() );
      server.queueForPlayer( player.getCharacterId(), inviteReplyPacket );

      break;
    }
    case HierarchyType::FRIENDLIST:
    {
      auto& flMgr = Common::Service< FriendListMgr >::ref();

      uint8_t result;
      if( data.Answer == InviteReplyType::ACCEPT )
      {
        flMgr.onInviteAccept( player, *pPlayer );
        result = InviteUpdateType::ACCEPT_INVITE;
      }
      else
      {
        flMgr.onInviteDecline( player, *pPlayer );
        result = InviteUpdateType::REJECT_INVITE;
      }

      auto inviteUpPacket = makeInviteUpdatePacket( player, 0, data.AuthType, 1, result );
      server.queueForPlayer( pPlayer->getCharacterId(), inviteUpPacket );

      inviteReplyData.AuthType = data.AuthType;
      strcpy( inviteReplyData.InviteCharacterName, pPlayer->getName().c_str() );
      server.queueForPlayer( player.getCharacterId(), inviteReplyPacket );

      break;
    }
    case HierarchyType::AUTOPARTY:
      break;
    case HierarchyType::FCCREATE:
    {

      auto& fcMgr = Common::Service< FreeCompanyMgr >::ref();
      uint8_t result;
      if( data.Answer == InviteReplyType::ACCEPT )
      {
        fcMgr.onSignPetition( player, *pPlayer );
        result = InviteUpdateType::ACCEPT_INVITE;
      }
      else
      {
        result = InviteUpdateType::REJECT_INVITE;
      }
      auto inviteUpPacket = makeInviteUpdatePacket( player, Common::Util::getTimeSeconds() + 300, data.AuthType, 1, result );
      server.queueForPlayer( pPlayer->getCharacterId(), inviteUpPacket );

      inviteReplyData.AuthType = data.AuthType;
      strcpy( inviteReplyData.InviteCharacterName, pPlayer->getName().c_str() );
      server.queueForPlayer( player.getCharacterId(), inviteReplyPacket );
      break;
    }
    case HierarchyType::FREECOMPANY:
      break;
    case HierarchyType::FCJOINREQUEST:
      break;
    case HierarchyType::PARTYCANCEL:
      break;
  }
}
