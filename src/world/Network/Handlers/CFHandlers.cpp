#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/InstanceContent.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "Network/PacketDef/Zone/ClientZoneDef.h"

#include "Session.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::cfDutyInfoRequest( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto dutyInfoPacket = makeZonePacket< FFXIVIpcCFDutyInfo >( player.getId() );
  auto penaltyMinutes = player.getCFPenaltyMinutes();
  if( penaltyMinutes > 255 )
  {
    // cap it since it's uint8_t in packets
    penaltyMinutes = 255;
  }
  dutyInfoPacket->data().penaltyTime = static_cast< uint8_t >( penaltyMinutes );
  queueOutPacket( dutyInfoPacket );

  auto inNeedsPacket = makeZonePacket< FFXIVIpcCFPlayerInNeed >( player.getId() );
  queueOutPacket( inNeedsPacket );

}

void Sapphire::Network::GameConnection::cfRegisterDuty( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                        Entity::Player& player )
{
  Packets::FFXIVARR_PACKET_RAW copy = inPacket;
  std::vector< uint16_t > selectedContent;

  for( uint32_t offset = 0x2A; offset <= 0x32; offset += 0x2 )
  {
    auto id = *reinterpret_cast< uint16_t* >( &copy.data[ offset ] );
    if( id == 0 )
      break;

    player.sendDebug( "got contentFinderConditionId#{0}", id );

    selectedContent.push_back( id );
  }

  // todo: rand bias problem, will do for now tho
  auto index = static_cast< uint32_t >( std::rand() ) % selectedContent.size();
  auto contentFinderConditionId = selectedContent.at( index );

  player.sendDebug( "Duty register request for contentFinderConditionId#{0}", contentFinderConditionId );
  player.m_cfNotifiedContent = contentFinderConditionId;
  auto notify = makeZonePacket< FFXIVIpcCFNotify >( player.getId() );
  notify->data().state1 = 3;
  notify->data().unknown_one = 1;
  notify->data().contents[ 0 ] = contentFinderConditionId;
  player.queuePacket( notify );
}

void Sapphire::Network::GameConnection::cfRegisterRoulette( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto packet = makeZonePacket< FFXIVIpcCFCancel >( player.getId() );
  packet->data().cancelReason = 890;
  queueOutPacket( packet );

  player.sendDebug( "Roulette register not implemented." );
}

void Sapphire::Network::GameConnection::cfDutyAccepted( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                        Entity::Player& player )
{
  const auto packetIn = ZoneChannelPacket< Client::FFXIVIpcCFCommenceHandler >( inPacket );
  if( packetIn.data().param == 0 )
  {
    // accept
    if( player.m_cfNotifiedContent > 0 )
    {
      auto& teriMgr = Common::Service< TerritoryMgr >::ref();

      auto instance = teriMgr.createInstanceContent( player.m_cfNotifiedContent );
      if( !instance )
        return;

      player.m_cfNotifiedContent = 0;
      auto pInstance = instance->getAsInstanceContent();
      pInstance->bindPlayer( player.getId() );

      player.sendDebug( "Created instance with id#{}", instance->getGuId() );

      player.prepareZoning( pInstance->getTerritoryTypeId(), true, 1, 0, 0, 1, 9 );

      player.setInstance( instance );
    }
  }
  else
  {
    // cancel
    player.m_cfNotifiedContent = 0;
    auto packet = makeZonePacket< FFXIVIpcCFCancel >( player.getId() );
    packet->data().cancelReason = 890;
    queueOutPacket( packet );
  }
}
/*
void Sapphire::Network::GameConnection::cfCancel( const Packets::FFXIVARR_PACKET_RAW& inPacket,
  Entity::Player& player )
{
  auto packet = makeZonePacket< FFXIVIpcCFCancel >( player.getId() );
  packet->data().cancelReason = 890;
  queueOutPacket( packet );
}
*/