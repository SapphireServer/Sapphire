#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <Service.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Manager/TerritoryMgr.h"
#include "Manager/PlayerMgr.h"
#include "Territory/InstanceContent.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ConditionPacket.h"

#include "ContentFinder/ContentFinder.h"

#include "Session.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::cfRequestPenalties( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto dutyInfoPacket = makeZonePacket< Server::FFXIVIpcResponsePenalties >( player.getId() );
  auto penaltyMinutes = player.getCFPenaltyMinutes();
  if( penaltyMinutes > 255 )
  {
    // cap it since it's uint8_t in packets
    penaltyMinutes = 255;
  }
  dutyInfoPacket->data().penalties[ 0 ] = static_cast< uint8_t >( penaltyMinutes ); //TODO: What is the second array for?
  queueOutPacket( dutyInfoPacket );
}

void Sapphire::Network::GameConnection::requestBonus( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto inNeedsPacket = makeZonePacket< Server::FFXIVIpcContentBonus >( player.getId() );
  queueOutPacket( inNeedsPacket );
}

void Sapphire::Network::GameConnection::findContent( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto& contentFinder = Common::Service< World::ContentFinder >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcFindContent >( inPacket );

  PlayerMgr::sendDebug( player, "Duty register request for terriId#{0}", packet.data().territoryType );

  auto contentId = teriMgr.getInstanceContentId( packet.data().territoryType );

  if( contentId == 0 )
    return;

  contentFinder.registerContentRequest( player, contentId, packet.data().flags );

}

void Sapphire::Network::GameConnection::find5Contents( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& contentFinder = Common::Service< World::ContentFinder >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcFind5Contents >( inPacket );

  std::set< uint16_t > selectedContent;

  for( auto territoryType : packet.data().territoryTypes )
    if( territoryType != 0 )
      selectedContent.insert( territoryType );

  auto contentListIds = exdData.getIdList< Excel::InstanceContent >();

  std::vector< uint32_t > idList;
  for( auto id : contentListIds )
  {
    auto instanceContent = exdData.getRow< Excel::InstanceContent >( id );
    if( selectedContent.count( instanceContent->data().TerritoryType ) )
    {
      idList.push_back( id );
    }
  }

  if( !idList.empty() )
    contentFinder.registerContentsRequest( player, idList );

}

void Sapphire::Network::GameConnection::findContentAsRandom( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  auto& contentFinder = Common::Service< World::ContentFinder >::ref();
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcFindContentAsRandom >( inPacket );
  contentFinder.registerRandomContentRequest( player, packet.data().randomContentType );
}

void Sapphire::Network::GameConnection::cfDutyAccepted( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  PlayerMgr::sendDebug( player, "TODO: Duty accept" );
}

void Sapphire::Network::GameConnection::cancelFindContent( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcCancelFindContent >( inPacket );

  PlayerMgr::sendDebug( player, "CancelFindContent: reason: {}", packet.data().cause );
  auto& contentFinder = Common::Service< World::ContentFinder >::ref();
  contentFinder.withdraw( player );

}

void Sapphire::Network::GameConnection::acceptContent( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcAcceptContent >( inPacket );

  PlayerMgr::sendDebug( player, "acceptContent: accept: {}, terriId: {}, terryType: {}",
                        packet.data().accept, packet.data().territoryId, packet.data().territoryType );
  auto& contentFinder = Common::Service< World::ContentFinder >::ref();

  if( packet.data().accept )
    contentFinder.accept( player ); 
  else
    contentFinder.withdraw( player );
}
