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
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  std::vector< uint16_t > selectedContent;

  for( uint32_t offset = 0x1E; offset <= 0x26; offset += 0x2 )
  {
    auto id = *reinterpret_cast< uint16_t* >( &copy.data[ offset ] );
    if( id == 0 )
      break;

    player.sendDebug( "got contentId#{0}", id );

    selectedContent.push_back( id );
  }

  // todo: rand bias problem, will do for now tho
  auto index = static_cast< uint32_t >( std::rand() ) % selectedContent.size();
  auto contentId = selectedContent.at( index );

  player.sendDebug( "Duty register request for contentid#{0}", contentId );

  // let's cancel it because otherwise you can't register it again
  /*
  auto cfCancelPacket = makeZonePacket< FFXIVIpcCFNotify >( player.getId() );
  cfCancelPacket->data().state1 = 3;
  cfCancelPacket->data().state2 = 1; // Your registration is withdrawn.
  queueOutPacket( cfCancelPacket );
  */
  auto packet = makeZonePacket< FFXIVIpcCFCancel >( player.getId() );
  packet->data().cancelReason = 890;
  queueOutPacket( packet );

  auto cfCondition = exdData.get< Sapphire::Data::ContentFinderCondition >( contentId );
  if( !cfCondition )
    return;

  auto instance = teriMgr.createInstanceContent( cfCondition->content );
  if( !instance )
    return;

  auto pInstance = instance->getAsInstanceContent();
  pInstance->bindPlayer( player.getId() );

  player.sendDebug( "Created instance with id#", instance->getGuId() );

  player.setInstance( instance );
}

void Sapphire::Network::GameConnection::cfRegisterRoulette( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  /*
  auto cfCancelPacket = makeZonePacket< FFXIVIpcCFNotify >( player.getId() );
  cfCancelPacket->data().state1 = 3;
  cfCancelPacket->data().state2 = 1; // Your registration is withdrawn.
  queueOutPacket( cfCancelPacket );
  */
  auto packet = makeZonePacket< FFXIVIpcCFCancel >( player.getId() );
  packet->data().cancelReason = 890;
  queueOutPacket( packet );

  player.sendDebug( "Roulette register" );
}

void Sapphire::Network::GameConnection::cfDutyAccepted( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                        Entity::Player& player )
{
  player.sendDebug( "TODO: Duty accept" );
}

void Sapphire::Network::GameConnection::cfCancel( const Packets::FFXIVARR_PACKET_RAW& inPacket,
  Entity::Player& player )
{
  auto packet = makeZonePacket< FFXIVIpcCFCancel >( player.getId() );
  packet->data().cancelReason = 890;
  queueOutPacket( packet );
}