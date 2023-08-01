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

//#include "Manager/FriendListMgr.h"
#include "Manager/PartyMgr.h"
#include "Manager/PlayerMgr.h"
//#include "Manager/FreeCompanyMgr.h"

#include "Action/Action.h"

#include "ServerMgr.h"
#include "Forwards.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::Packets::Client;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::socialInviteHandler( const FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSocialInviteHandler >( inPacket );

  player.sendDebug( "Auth Type#{0}", packet.data().socialType );
  player.sendDebug( "Target Name: {0}", packet.data().name );

  std::string name( packet.data().name );

  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& server = Common::Service< Sapphire::World::ServerMgr >::ref();
  auto pTargetPlayer = server.getSession( name )->getPlayer();

  if( !pTargetPlayer )
    return;

  switch( packet.data().socialType )
  {
    case 1:
    {
      auto inviteResultPacket = makeZonePacket< Server::FFXIVIpcSocialInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.contentId = pTargetPlayer->getContentId();
      data.p1 = packet.data().p1;
      data.p2 = packet.data().p2;
      data.socialType = packet.data().socialType;
      strcpy( data.name, packet.data().name );
      player.queuePacket( inviteResultPacket );

      auto inviteUpdatePacket = makeZonePacket< Server::FFXIVIpcSocialInviteUpdate >( pTargetPlayer->getId() );
      inviteUpdatePacket->data().contentId = player.getContentId();
      inviteUpdatePacket->data().expireTime = Common::Util::getTimeSeconds() + 30;
      inviteUpdatePacket->data().p1 = packet.data().p1;
      inviteUpdatePacket->data().p2 = packet.data().p2;
      inviteUpdatePacket->data().socialType = packet.data().socialType;
      inviteUpdatePacket->data().type = 1;
      inviteUpdatePacket->data().gender = player.getGender();
      strcpy( inviteUpdatePacket->data().name, player.getName().c_str() );
      pTargetPlayer->queuePacket( inviteUpdatePacket );

      break;
    }
  }
}

void Sapphire::Network::GameConnection::socialReplyHandler( const FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSocialReplyHandler >( inPacket );
  const auto& data = packet.data();

  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& server = Common::Service< Sapphire::World::ServerMgr >::ref();
  auto pPlayer = server.getSession( data.contentId )->getPlayer();

  if( !pPlayer )
    return;

  auto inviteReplyPacket = makeZonePacket< Server::FFXIVIpcSocialInviteResponse >( player.getId() );
  auto& inviteReplyData = inviteReplyPacket->data();
  inviteReplyData.response = data.response;

  switch( data.socialType )
  {
    case 1:
    {
      auto& partyMgr = Common::Service< PartyMgr >::ref();

      if( data.response == InviteReplyType::ACCEPT )
      {
        partyMgr.onJoin( player, *pPlayer );
      }

      auto inviteUpPacket = makeZonePacket< Server::FFXIVIpcSocialInviteUpdate >( pPlayer->getId() );
      inviteUpPacket->data().contentId = player.getContentId();
      inviteUpPacket->data().expireTime = Common::Util::getTimeSeconds() + 30;
      inviteUpPacket->data().p1 = packet.data().p1;
      inviteUpPacket->data().p2 = packet.data().p2;
      inviteUpPacket->data().socialType = packet.data().socialType;
      inviteUpPacket->data().type = data.response == InviteReplyType::ACCEPT ? InviteUpdateType::ACCEPT_INVITE : InviteUpdateType::REJECT_INVITE;
      strcpy( inviteUpPacket->data().name, player.getName().c_str() );
      pPlayer->queuePacket( inviteUpPacket );

      inviteReplyData.contentId == pPlayer->getContentId();
      inviteReplyData.socialType = data.socialType;
      inviteReplyData.gender = pPlayer->getGender();
      strcpy( inviteReplyData.name, pPlayer->getName().c_str() );
      player.queuePacket( inviteReplyPacket );

      break;
    }
  }
}
