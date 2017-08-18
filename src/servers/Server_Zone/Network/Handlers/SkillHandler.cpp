#include <Server_Common/Common.h>
#include <Server_Common/CommonNetwork.h>
#include <Server_Common/ExdData.h>
#include <Server_Common/GamePacketNew.h>
#include <Server_Common/PacketContainer.h>
#include <Server_Common/Logger.h>

#include <boost/format.hpp>

#include "src/servers/Server_Zone/Network/GameConnection.h"

#include "src/servers/Server_Zone/Session.h"

#include "src/servers/Server_Zone/Network/PacketWrappers/ServerNoticePacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket144.h"

#include "src/servers/Server_Zone/Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "src/servers/Server_Zone/DebugCommand/DebugCommandHandler.h"

#include "src/servers/Server_Zone/Actor/Player.h"

#include "src/servers/Server_Zone/Forwards.h"

#include "src/servers/Server_Zone/Action/Action.h"
#include "src/servers/Server_Zone/Action/ActionTeleport.h"
#include "src/servers/Server_Zone/Action/ActionCast.h"
#include "src/servers/Server_Zone/Script/ScriptManager.h"


extern Core::Scripting::ScriptManager g_scriptMgr;
extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

void Core::Network::GameConnection::skillHandler( const Packets::GamePacket& inPacket,
                                                  Entity::PlayerPtr pPlayer )
{

    uint32_t action = inPacket.getValAt< uint32_t >( 0x24 );
    uint32_t useCount = inPacket.getValAt< uint32_t >( 0x28 );

    uint64_t targetId = inPacket.getValAt< uint64_t >( 0x30 );

    if( action < 1000000 ) // normal action
    {
        std::string actionIdStr = boost::str( boost::format( "%|04X|" ) % action );
        pPlayer->sendDebug( "---------------------------------------" );
        pPlayer->sendDebug( "ActionHandler ( " + actionIdStr + " | " +
                            g_exdData.m_actionInfoMap[action].name +
                            " | " + std::to_string( targetId ) + " )" );

        pPlayer->queuePacket( ActorControlPacket142( pPlayer->getId(), ActorControlType::ActionStart, 0x01, action ) );

        if( action == 5 )
        {
            auto currentAction = pPlayer->getCurrentAction();

            // we should always have an action here, if not there is a bug
            assert( currentAction );
            currentAction->onStart();
        }
        else
        {
            Core::Entity::ActorPtr targetActor = pPlayer;
            if( targetId != pPlayer->getId() )
            {
                targetActor = pPlayer->lookupTargetById( targetId );
            }

            if( !pPlayer->actionHasCastTime( action ) )
            {
                g_scriptMgr.onCastFinish( pPlayer, targetActor, action );
            }
            else
            {
                Action::ActionCastPtr pActionCast( new Action::ActionCast( pPlayer, targetActor, action ) );
                pPlayer->setCurrentAction( pActionCast );
                pPlayer->sendDebug( "setCurrentAction()" );
                pPlayer->getCurrentAction()->onStart();
            }
        }
    }
    else if( action < 2000000 ) // craft action
    {

    }
    else if( action < 3000000 ) // item action
    {
        auto info = g_exdData.getEventItemInfo( action );
        if( info )
        {
            g_log.debug( info->name );
            g_scriptMgr.onEventItem( pPlayer, action, info->eventId, info->castTime, targetId );
        }
    }
    else if( action > 3000000 ) // unknown
    {

    }

}