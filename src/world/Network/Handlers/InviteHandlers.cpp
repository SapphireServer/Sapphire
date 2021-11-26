#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/CommonActorControl.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Database/DatabaseDef.h>

#include <datReader/DatCategories/bg/LgbTypes.h>

#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Service.h>

#include "Network/GameConnection.h"
#include "Session.h"

#include "Territory/Territory.h"
#include "Territory/Land.h"

#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/InviteUpdatePacket.h"

#include "Manager/PartyMgr.h"
#include "Manager/PlayerMgr.h"

#include "Action/Action.h"

#include "WorldServer.h"
#include "Forwards.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::inviteHandler( const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcInvite >( inPacket );

  PlayerMgr::sendDebug( player, "Auth Type#{0}", packet.data().AuthType );
  PlayerMgr::sendDebug( player, "Target Name: {0}", packet.data().TargetName );

  std::string name( packet.data().TargetName );

  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto pSession = server.getSession( name );

  if( !pSession )
    return;

  switch( packet.data().AuthType )
  {
    case InviteType::PCPARTY:
    {
      auto inviteResultPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.AuthType = packet.data().AuthType;
      strcpy( data.TargetName, packet.data().TargetName );
      server.queueForPlayer( player.getCharacterId(), inviteResultPacket );

      auto invitePacket = std::make_shared< InviteUpdatePacket >( player, Common::Util::getTimeSeconds() + 30,
                                                                  packet.data().AuthType, 1,
                                                                  InviteUpdateType::NEW_INVITE );
      pSession->getZoneConnection()->queueOutPacket( invitePacket );

      break;
    }

    case InviteType::FRIENDLIST:
    {
      auto inviteResultPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcInviteResult >( player.getId() );
      auto& data = inviteResultPacket->data();
      data.AuthType = packet.data().AuthType;
      strcpy( data.TargetName, packet.data().TargetName );
      server.queueForPlayer( player.getCharacterId(), inviteResultPacket );

      auto invitePacket = std::make_shared< InviteUpdatePacket >( player, Common::Util::getTimeSeconds() + 30,
                                                                  packet.data().AuthType, 1,
                                                                  InviteUpdateType::NEW_INVITE );
      pSession->getZoneConnection()->queueOutPacket( invitePacket );

      break;
    }
    case Common::InviteType::AUTOPARTY:
      break;
    case Common::InviteType::FCCREATE:
      break;
    case Common::InviteType::FREECOMPANY:
      break;
    case Common::InviteType::FCJOINREQUEST:
      break;
    case Common::InviteType::PARTYCANCEL:
      break;
  }
}

void Sapphire::Network::GameConnection::inviteReplyHandler( const FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcInviteReply >( inPacket );
  const auto& data = packet.data();

  auto& server = Common::Service< Sapphire::World::WorldServer >::ref();
  auto pSession = server.getSession( data.InviteCharacterID );

  auto& partyMgr = Common::Service< Sapphire::World::Manager::PartyMgr >::ref();

  if( !pSession )
    return;

  switch( data.AuthType )
  {
    case Common::InviteType::PCPARTY:
    {
      auto inviteReplyPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcInviteReplyResult >( player.getId() );
      auto& inviteReplyData = inviteReplyPacket->data();

      inviteReplyData.Answer = data.Answer;
      uint8_t result;
      if( data.Answer == InviteReplyType::ACCEPT )
      {
        partyMgr.onJoin( player.getId(), pSession->getPlayer()->getId() );
        result = InviteUpdateType::ACCEPT_INVITE;
      }
      else
      {
        result = InviteUpdateType::REJECT_INVITE;
      }

      auto inviteUpPacket = std::make_shared< InviteUpdatePacket >( player, Common::Util::getTimeSeconds() + 30,
                                                                    data.AuthType, 1, result );
      pSession->getZoneConnection()->queueOutPacket( inviteUpPacket );

      inviteReplyData.AuthType = data.AuthType;
      strcpy( inviteReplyData.InviteCharacterName, pSession->getPlayer()->getName().c_str() );
      server.queueForPlayer( player.getCharacterId(), inviteReplyPacket );

      break;
    }
    case Common::InviteType::FRIENDLIST:
      break;
    case Common::InviteType::AUTOPARTY:
      break;
    case Common::InviteType::FCCREATE:
      break;
    case Common::InviteType::FREECOMPANY:
      break;
    case Common::InviteType::FCJOINREQUEST:
      break;
    case Common::InviteType::PARTYCANCEL:
      break;
  }
}
