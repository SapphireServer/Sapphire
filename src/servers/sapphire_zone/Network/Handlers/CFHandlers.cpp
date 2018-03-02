#include <common/Common.h>
#include <common/Network/CommonNetwork.h>
#include <common/Network/GamePacketNew.h>
#include <common/Logging/Logger.h>
#include <common/Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Session.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "Actor/Player.h"

#include "Forwards.h"
#include <common/Exd/ExdDataGenerated.h>
#include "Zone/TerritoryMgr.h"
#include "Zone/Zone.h"

extern Core::Logger g_log;
extern Core::Data::ExdDataGenerated g_exdDataGen;
extern Core::TerritoryMgr g_territoryMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;


void Core::Network::GameConnection::cfDutyInfoRequest( const Packets::GamePacket& inPacket,
                                                       Entity::Player& player )
{
   ZoneChannelPacket< FFXIVIpcCFDutyInfo > dutyInfoPacket( player.getId() );

   auto penaltyMinutes = player.getCFPenaltyMinutes();
   if (penaltyMinutes > 255)
   {
      // cap it since it's uint8_t in packets
      penaltyMinutes = 255;
   }
   dutyInfoPacket.data().penaltyTime = penaltyMinutes;

   queueOutPacket( dutyInfoPacket );

   ZoneChannelPacket< FFXIVIpcCFPlayerInNeed > inNeedsPacket( player.getId() );
   queueOutPacket( inNeedsPacket );

}

void Core::Network::GameConnection::cfRegisterDuty( const Packets::GamePacket& inPacket,
                                                    Entity::Player& player)
{
   // TODO use for loop for this
   auto contentId1 = inPacket.getValAt< uint16_t >( 0x2E );
   auto contentId2 = inPacket.getValAt< uint16_t >( 0x30 );
   auto contentId3 = inPacket.getValAt< uint16_t >( 0x32 );
   auto contentId4 = inPacket.getValAt< uint16_t >( 0x34 );
   auto contentId5 = inPacket.getValAt< uint16_t >( 0x36 );

   player.sendDebug("Duty register request");
   player.sendDebug("ContentId1: " + std::to_string(contentId1));
   player.sendDebug("ContentId2: " + std::to_string(contentId2));
   player.sendDebug("ContentId3: " + std::to_string(contentId3));
   player.sendDebug("ContentId4: " + std::to_string(contentId4));
   player.sendDebug("ContentId5: " + std::to_string(contentId5));

   // let's cancel it because otherwise you can't register it again
   ZoneChannelPacket< FFXIVIpcCFNotify > cfCancelPacket( player.getId() );
   cfCancelPacket.data().state1 = 3;
   cfCancelPacket.data().state2 = 1; // Your registration is withdrawn.
   queueOutPacket( cfCancelPacket );

   auto cfCondition = g_exdDataGen.get< Core::Data::ContentFinderCondition >( contentId1 );
   if( !cfCondition )
      return;

   auto instance = g_territoryMgr.createInstanceContent( cfCondition->instanceContent );
   if( !instance )
      return;

   player.sendDebug( "Created instance with id: " + std::to_string( instance->getGuId() ) );

   player.setInstance( instance );
}

void Core::Network::GameConnection::cfRegisterRoulette( const Packets::GamePacket& inPacket,
                                                        Entity::Player& player)
{
   player.sendDebug("Roulette register");
}

void Core::Network::GameConnection::cfDutyAccepted( const Packets::GamePacket& inPacket,
                                                    Entity::Player& player)
{
   player.sendDebug("TODO: Duty accept");
}
