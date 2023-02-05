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

  auto fc = fcMgr.getPlayerFreeCompany( player );
  if( !fc )
    return;

  auto inviteListPacket = makeZonePacket< FFXIVIpcGetFcInviteListResult >( player.getId() );
  inviteListPacket->data().GrandCompanyID = fc->getGrandCompany();
  inviteListPacket->data().FreeCompanyID = fc->getId();
  std::strcpy( inviteListPacket->data().FcTag, fc->getTag().c_str() );
  std::strcpy( inviteListPacket->data().FreeCompanyName, fc->getName().c_str() );
  inviteListPacket->data().MasterCharacter.GrandCompanyID = player.getGc();
  inviteListPacket->data().MasterCharacter.CharacterID = player.getCharacterId();
  strcpy( inviteListPacket->data().MasterCharacter.CharacterName, player.getName().c_str() );
  inviteListPacket->data().MasterCharacter.SelectRegion = player.getSearchSelectRegion();
  inviteListPacket->data().MasterCharacter.OnlineStatus = player.getOnlineStatusMask();
  inviteListPacket->data().MasterCharacter.GrandCompanyRank[ 0 ] = player.getGcRankArray()[ 0 ];
  inviteListPacket->data().MasterCharacter.GrandCompanyRank[ 1 ] = player.getGcRankArray()[ 1 ];
  inviteListPacket->data().MasterCharacter.GrandCompanyRank[ 2 ] = player.getGcRankArray()[ 2 ];

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), inviteListPacket );

}
