#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Network/CommonNetwork.h>
#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>

#include <boost/format.hpp>

#include "src/servers/Server_Zone/Network/GameConnection.h"

#include "src/servers/Server_Zone/Session.h"
#include "src/servers/Server_Zone/Zone/Zone.h"
#include "src/servers/Server_Zone/Zone/ZonePosition.h"
#include "src/servers/Server_Zone/ServerZone.h"
#include "src/servers/Server_Zone/Zone/ZoneMgr.h"

#include "src/servers/Server_Zone/Network/PacketWrappers/InitUIPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/PingPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/MoveActorPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ChatPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ServerNoticePacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket144.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/EventStartPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/EventFinishPacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "src/servers/Server_Zone/DebugCommand/DebugCommandHandler.h"
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Inventory/Inventory.h"
#include "src/servers/Server_Zone/Forwards.h"
#include "src/servers/Server_Zone/Event/EventHelper.h"
#include "src/servers/Server_Zone/Action/Action.h"
#include "src/servers/Server_Zone/Action/ActionTeleport.h"

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::DebugCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::actionHandler( const Packets::GamePacket& inPacket,
                                                   Entity::PlayerPtr pPlayer )
{
    uint16_t commandId = inPacket.getValAt< uint16_t >( 0x20 );
    uint64_t param1 = inPacket.getValAt< uint64_t >( 0x24 );
    uint32_t param11 = inPacket.getValAt< uint32_t >( 0x24 );
    uint32_t param12 = inPacket.getValAt< uint32_t >( 0x28 );
    uint32_t param2 = inPacket.getValAt< uint32_t >( 0x2C );
    uint64_t param3 = inPacket.getValAt< uint64_t >( 0x38 );

    g_log.debug( "[" + std::to_string( m_pSession->getId() ) + "] Incoming action: " +
                 boost::str( boost::format( "%|04X|" ) % ( uint32_t ) ( commandId & 0xFFFF ) ) +
                 "\nparam1: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param1 & 0xFFFFFFFFFFFFFFF ) ) +
                 "\nparam2: " + boost::str( boost::format( "%|08X|" ) % ( uint32_t ) ( param2 & 0xFFFFFFFF ) ) +
                 "\nparam3: " + boost::str( boost::format( "%|016X|" ) % ( uint64_t ) ( param3 & 0xFFFFFFFFFFFFFFF ) )
    );


    //g_log.Log(LoggingSeverity::debug, "[" + std::to_string(m_pSession->getId()) + "] " + pInPacket->toString());

    switch( commandId )
    {
        case 0x01:  // Toggle sheathe
        {
            if ( param11 == 1 )
                pPlayer->setStance( Entity::Actor::Stance::Active );
            else
            {
                pPlayer->setStance( Entity::Actor::Stance::Passive );
                pPlayer->setAutoattack( false );
            }

            pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), 0, param11, 1 ) );

            break;
        }
        case 0x02:  // Toggle auto-attack
        {
            if ( param11 == 1 )
            {
                pPlayer->setAutoattack( true );
                pPlayer->setStance( Entity::Actor::Stance::Active );
            }
            else
                pPlayer->setAutoattack( false );

            pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), 1, param11, 1 ) );

            break;
        }
        case 0x03: // Change target
        {

            uint64_t targetId = inPacket.getValAt< uint64_t >( 0x24 );
            pPlayer->changeTarget( targetId );
            break;
        }
        case 0x65:
        {
           pPlayer->dismount();
           break;
        }
        case 0x68: // Remove status (clicking it off)
        {
           // todo: check if status can be removed by client from exd
           pPlayer->removeSingleStatusEffectById( static_cast< uint32_t >( param1 ) );
           break;
        }
        case 0x69: // Cancel cast
        {
           if( pPlayer->getCurrentAction() )
               pPlayer->getCurrentAction()->setInterrupted();
           break;
        }
        case 0x12E: // Set player title
        {
           pPlayer->setTitle( static_cast< uint16_t >( param1 ) );
           break;
        }
        case 0x12F: // Get title list
        {
           ZoneChannelPacket< FFXIVIpcPlayerTitleList > titleListPacket( pPlayer->getId() );
           memcpy( titleListPacket.data().titleList, pPlayer->getTitleList(), sizeof( titleListPacket.data().titleList ) );

           pPlayer->queuePacket( titleListPacket );
           break;
        }
        case 0x133: // Update howtos seen
        {
            uint32_t howToId = static_cast< uint32_t >( param1 );
            pPlayer->updateHowtosSeen( howToId );
            break;
        }
        case 0x1F4: // emote
        {
            uint64_t targetId = pPlayer->getTargetId();
            uint32_t emoteId = inPacket.getValAt< uint32_t >( 0x24 );

            pPlayer->sendToInRangeSet( ActorControlPacket144( pPlayer->getId(), Emote, emoteId, 0, 0, 0, targetId ) );
            break;
        }
        case 0xC8: // return dead
        {
           switch ( static_cast < ResurrectType >( param1 ) )
           {
              case ResurrectType::RaiseSpell:
                 // todo: handle raise case (set position to raiser, apply weakness status, set hp/mp/tp as well as packet)
                 pPlayer->returnToHomepoint();
                 break;
              case ResurrectType::Return:
                 pPlayer->returnToHomepoint();
                 break;
              default:
                 break;
           }
            
        }
        case 0xC9: // Finish zoning
        {
            switch( pPlayer->getZoningType() )
            {
                case ZoneingType::None:
                    pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01 ), true );
                    break;
                case ZoneingType::Teleport:
                    pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0, 0, 110 ), true );
                    break;
                case ZoneingType::Return:
                case ZoneingType::ReturnDead:
                {
                    if( pPlayer->getStatus() == Entity::Actor::ActorStatus::Dead )
                    {
                        pPlayer->resetHp();
                        pPlayer->resetMp();
                        pPlayer->setStatus( Entity::Actor::ActorStatus::Idle );

                        pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0x01, 0, 111 ), true );
                        pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), SetStatus, static_cast< uint8_t >( Entity::Actor::ActorStatus::Idle ) ), true );
                    }
                    else
                        pPlayer->sendToInRangeSet( ActorControlPacket143( pPlayer->getId(), ZoneIn, 0x01, 0x00, 0, 111 ), true );
                }
                    break;
                case ZoneingType::FadeIn:
                    break;
            }

            pPlayer->setZoningType( Common::ZoneingType::None );

            pPlayer->unsetStateFlag( PlayerStateFlag::BetweenAreas );
            pPlayer->unsetStateFlag( PlayerStateFlag::BetweenAreas1 );
            pPlayer->sendStateFlags();
            break;
        }

        case 0xCA: // Teleport
        {
            // TODO: only register this action if enough gil is in possession
            auto targetAetheryte = g_exdData.getAetheryteInfo( param11 );

            if( targetAetheryte )
            {
                auto fromAetheryte = g_exdData.getAetheryteInfo( g_exdData.m_zoneInfoMap[pPlayer->getZoneId()].aetheryte_index );

                // calculate cost - does not apply for favorite points or homepoints neither checks for aether tickets
                auto cost = static_cast< uint16_t > ( ( sqrt( pow( fromAetheryte->map_coord_x - targetAetheryte->map_coord_x, 2 ) +
                                    pow( fromAetheryte->map_coord_y - targetAetheryte->map_coord_y, 2 ) ) / 2 ) + 100 );

                // cap at 999 gil
                cost = cost > uint16_t{999} ? uint16_t{999} : cost;

                bool insufficientGil = pPlayer->getCurrency( Inventory::CurrencyType::Gil ) < cost;
                // todo: figure out what param1 really does
                pPlayer->queuePacket( ActorControlPacket143( pPlayer->getId(), TeleportStart, insufficientGil ? 2 : 0, param11 ) );

                if( !insufficientGil )
                {
                    Action::ActionTeleportPtr pActionTeleport( new Action::ActionTeleport( pPlayer, param11, cost ) );
                    pPlayer->setCurrentAction( pActionTeleport );
                }
            }
            break;
        }
        case 0x1B5: // Dye item
        {
           break;
        }
        default:
        {
           g_log.debug( "[" + std::to_string( m_pSession->getId() ) + "] Unhandled action: " +
              boost::str( boost::format( "%|04X|" ) % (uint32_t) ( commandId & 0xFFFF ) ) );
           break;
        }
    }
}
