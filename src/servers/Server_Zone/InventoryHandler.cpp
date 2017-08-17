#include <Server_Common/Common.h>
#include <Server_Common/CommonNetwork.h>
#include <Server_Common/Database.h>
#include <Server_Common/GamePacketNew.h>
#include <Server_Common/Logger.h>
#include <Server_Common/ExdData.h>
#include <Server_Common/PacketContainer.h>

#include <boost/format.hpp>


#include "GameConnection.h"

#include "Session.h"
#include "Zone.h"
#include "ZonePosition.h"
#include "ServerZone.h"
#include "ZoneMgr.h"

#include "InitUIPacket.h"
#include "PingPacket.h"
#include "MoveActorPacket.h"
#include "ChatPacket.h"
#include "ServerNoticePacket.h"
#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"
#include "ActorControlPacket144.h"
#include "EventStartPacket.h"
#include "EventFinishPacket.h"
#include "PlayerStateFlagsPacket.h"


#include "GameCommandHandler.h"

#include "Player.h"
#include "Inventory.h"

#include "Forwards.h"

#include "EventHelper.h"

#include "Action.h"
#include "ActionTeleport.h"

extern Core::Logger g_log;
extern Core::Db::Database g_database;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::GameCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;


void Core::Network::GameConnection::inventoryModifyHandler( Core::Network::Packets::GamePacketPtr pInPacket,
                                                            Core::Entity::PlayerPtr pPlayer )
{
    uint32_t seq = pInPacket->getValAt< uint32_t >( 0x20 );
    uint8_t action = pInPacket->getValAt< uint8_t >( 0x24 );
    uint8_t fromSlot = pInPacket->getValAt< uint8_t >( 0x30 );
    uint8_t toSlot = pInPacket->getValAt< uint8_t >( 0x44 );
    uint16_t fromContainer = pInPacket->getValAt< uint16_t >( 0x2C );
    uint16_t toContainer = pInPacket->getValAt< uint16_t >( 0x40 );

    GamePacketNew< FFXIVIpcInventoryActionAck > ackPacket( pPlayer->getId() );
    ackPacket.data().sequence = seq;
    ackPacket.data().type = 7;
    pPlayer->queuePacket( ackPacket );


    g_log.debug( pInPacket->toString() );
    g_log.debug( "InventoryAction: " + std::to_string( action ) );

    // TODO: other inventory operations need to be implemented
    switch( action )
    {

        case 0x07: // discard item action
        {
            pPlayer->getInvetory()->discardItem( fromContainer, fromSlot );
        }
            break;

        case 0x08: // move item action
        {
            pPlayer->getInvetory()->moveItem( fromContainer, fromSlot, toContainer, toSlot );
        }
            break;

        case 0x09: // swap item action
        {
            pPlayer->getInvetory()->swapItem( fromContainer, fromSlot, toContainer, toSlot );
        }
            break;

        case 0x0C: // merge stack action
        {

        }
            break;

        case 0x0A: // split stack action
        {

        }
            break;

        default:

            break;
    }

    pPlayer->setSyncFlag( PlayerSyncFlags::Status );

}

