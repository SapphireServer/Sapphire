#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/InstanceContent.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "Framework.h"
#include "Session.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;


void Sapphire::Network::GameConnection::cfDutyInfoRequest( FrameworkPtr pFw,
                                                           const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                           Entity::Player& player )
{
  auto dutyInfoPacket = makeZonePacket< FFXIVIpcCFDutyInfo >( player.getId() );
  auto penaltyMinutes = player.getCFPenaltyMinutes();
  if( penaltyMinutes > 255 )
  {
    // cap it since it's uint8_t in packets
    penaltyMinutes = 255;
  }
  dutyInfoPacket->data().penaltyTime = penaltyMinutes;
  queueOutPacket( dutyInfoPacket );

  auto inNeedsPacket = makeZonePacket< FFXIVIpcCFPlayerInNeed >( player.getId() );
  queueOutPacket( inNeedsPacket );

}

void Sapphire::Network::GameConnection::cfRegisterDuty( FrameworkPtr pFw,
                                                        const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                        Entity::Player& player )
{
  Packets::FFXIVARR_PACKET_RAW copy = inPacket;
  auto pTeriMgr = pFw->get< TerritoryMgr >();
  auto pExdData = pFw->get< Data::ExdDataGenerated >();

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
  auto index = std::rand() % selectedContent.size();
  auto contentId = selectedContent.at( index );

  player.sendDebug( "Duty register request for contentid#{0}", contentId );

  // let's cancel it because otherwise you can't register it again
  auto cfCancelPacket = makeZonePacket< FFXIVIpcCFNotify >( player.getId() );
  cfCancelPacket->data().state1 = 3;
  cfCancelPacket->data().state2 = 1; // Your registration is withdrawn.
  queueOutPacket( cfCancelPacket );

  auto cfCondition = pExdData->get< Sapphire::Data::ContentFinderCondition >( contentId );
  if( !cfCondition )
    return;

  auto instance = pTeriMgr->createInstanceContent( cfCondition->content );
  if( !instance )
    return;

  auto pInstance = instance->getAsInstanceContent();
  pInstance->bindPlayer( player.getId() );

  player.sendDebug( "Created instance with id#", instance->getGuId() );

  player.setInstance( instance );
}

void Sapphire::Network::GameConnection::cfRegisterRoulette( FrameworkPtr pFw,
                                                            const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                            Entity::Player& player )
{
  auto cfCancelPacket = makeZonePacket< FFXIVIpcCFNotify >( player.getId() );
  cfCancelPacket->data().state1 = 3;
  cfCancelPacket->data().state2 = 1; // Your registration is withdrawn.
  queueOutPacket( cfCancelPacket );

  player.sendDebug( "Roulette register" );
}

void Sapphire::Network::GameConnection::cfDutyAccepted( FrameworkPtr pFw,
                                                        const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                        Entity::Player& player )
{
  player.sendDebug( "TODO: Duty accept" );
}
