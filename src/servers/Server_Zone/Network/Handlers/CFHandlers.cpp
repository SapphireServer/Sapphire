#include <Server_Common/Common.h>
#include <Server_Common/Network/CommonNetwork.h>
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Session.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"
#include "Actor/Player.h"

#include "Forwards.h"

extern Core::Logger g_log;

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
   auto contentId1 = inPacket.getValAt< uint16_t >( 46 );
   auto contentId2 = inPacket.getValAt< uint16_t >( 48 );
   auto contentId3 = inPacket.getValAt< uint16_t >( 50 );
   auto contentId4 = inPacket.getValAt< uint16_t >( 52 );
   auto contentId5 = inPacket.getValAt< uint16_t >( 54 );

   player.sendDebug("Duty register request");
   player.sendDebug("ContentId1" + std::to_string(contentId1));
   player.sendDebug("ContentId2" + std::to_string(contentId2));
   player.sendDebug("ContentId3" + std::to_string(contentId3));
   player.sendDebug("ContentId4" + std::to_string(contentId4));
   player.sendDebug("ContentId5" + std::to_string(contentId5));

   // let's cancel it because otherwise you can't register it again
   ZoneChannelPacket< FFXIVIpcCFNotify > cfCancelPacket( player.getId() );
   cfCancelPacket.data().state1 = 3;
   cfCancelPacket.data().state2 = 1; // Your registration is withdrawn.
   queueOutPacket( cfCancelPacket );
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
