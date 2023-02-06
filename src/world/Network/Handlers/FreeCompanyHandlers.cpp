#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>

#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Network/GameConnection.h"

#include "Session.h"
#include "Actor/Player.h"
#include "FreeCompany/FreeCompany.h"
#include "Manager/FreeCompanyMgr.h"
#include <WorldServer.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;

void Sapphire::Network::GameConnection::getFcInviteListHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& fcMgr = Common::Service< FreeCompanyMgr >::ref();
  fcMgr.sendFcInviteList( player );
}

void Sapphire::Network::GameConnection::getFcStatus( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& fcMgr = Common::Service< FreeCompanyMgr >::ref();
  fcMgr.sendFcStatus( player );
}

void Sapphire::Network::GameConnection::getFcProfile( const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcGetFcProfile >( inPacket );

  auto& server = Common::Service< World::WorldServer >::ref();

  auto resultPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcGetFcProfileResult >( player.getId() );
  resultPacket->data().TargetCharacterID = packet.data().TargetCharacterID;
  resultPacket->data().TargetEntityID = packet.data().TargetEntityID;

  // haha test code
  resultPacket->data().FreeCompanyID = 1;
  resultPacket->data().CrestID = 0x0001000100010001;
  resultPacket->data().LandID = Common::INVALID_GAME_OBJECT_ID64;
  resultPacket->data().OnlineMemberCount = 69;
  resultPacket->data().TotalMemberCount = 420;
  resultPacket->data().JoinRequestCount = 69;
  resultPacket->data().FcRank = 1;
  resultPacket->data().FcStatus = 1;
  resultPacket->data().FcRole = 1;
  resultPacket->data().FcActivity = 1;
  resultPacket->data().GrandCompanyID = 1;
  resultPacket->data().CreateDate = 1587305592;
  resultPacket->data().Reputation = 500;
  resultPacket->data().FcActiveTimeFlag = 0xFF;
  resultPacket->data().FcJoinRequestFlag = 0xFF;
  strcpy( resultPacket->data().MasterCharacterName, "Biggus Dickus" );
  strcpy( resultPacket->data().FcTag, "Wang" );
  strcpy( resultPacket->data().FreeCompanyName, "Test FC" );
  strcpy( resultPacket->data().CompanyMotto, "nobody here but us chickens" );


  server.queueForPlayer( player.getCharacterId(), resultPacket );

}