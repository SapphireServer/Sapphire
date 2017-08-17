#include <Server_Common/Common.h>
#include <Server_Common/CommonNetwork.h>

#include <Server_Common/GamePacketNew.h>
#include <Server_Common/Logger.h>

#include <Server_Common/PacketContainer.h>

#include "GameConnection.h"

#include "Session.h"

#include "ServerNoticePacket.h"
#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"
#include "ActorControlPacket144.h"

#include "PlayerStateFlagsPacket.h"


#include "Player.h"

#include "Forwards.h"



extern Core::Logger g_log;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;


void Core::Network::GameConnection::cfDutyInfoRequest( const Packets::GamePacket& inPacket,
                                                       Entity::PlayerPtr pPlayer )
{
    GamePacketNew< FFXIVIpcCFDutyInfo > dutyInfoPacket( pPlayer->getId() );
    queueOutPacket( dutyInfoPacket );

    GamePacketNew< FFXIVIpcCFPlayerInNeed > inNeedsPacket( pPlayer->getId() );
    queueOutPacket( inNeedsPacket );

}

void Core::Network::GameConnection::cfRegisterDuty( const Packets::GamePacket& inPacket,
                                                    Entity::PlayerPtr pPlayer)
{
    // TODO use for loop for this
    auto contentId1 = inPacket.getValAt< uint16_t >( 46 );
    auto contentId2 = inPacket.getValAt< uint16_t >( 48 );
    auto contentId3 = inPacket.getValAt< uint16_t >( 50 );
    auto contentId4 = inPacket.getValAt< uint16_t >( 52 );
    auto contentId5 = inPacket.getValAt< uint16_t >( 54 );

    pPlayer->sendDebug("Duty register request");
    pPlayer->sendDebug("ContentId1" + std::to_string(contentId1));
    pPlayer->sendDebug("ContentId2" + std::to_string(contentId2));
    pPlayer->sendDebug("ContentId3" + std::to_string(contentId3));
    pPlayer->sendDebug("ContentId4" + std::to_string(contentId4));
    pPlayer->sendDebug("ContentId5" + std::to_string(contentId5));

    // let's cancel it because otherwise you can't register it again
    GamePacketNew< FFXIVIpcCFNotify > cfCancelPacket( pPlayer->getId() );
    cfCancelPacket.data().state1 = 3;
    cfCancelPacket.data().state2 = 1; // Your registration is withdrawn.
    queueOutPacket( cfCancelPacket );
}

void Core::Network::GameConnection::cfRegisterRoulette( const Packets::GamePacket& inPacket,
                                                        Entity::PlayerPtr pPlayer)
{
    pPlayer->sendDebug("Roulette register");
}

void Core::Network::GameConnection::cfDutyAccepted( const Packets::GamePacket& inPacket,
                                                    Entity::PlayerPtr pPlayer)
{
    pPlayer->sendDebug("TODO: Duty accept");
}
