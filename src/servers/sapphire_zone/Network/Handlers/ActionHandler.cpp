#include <boost/format.hpp>

#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Network/GameConnection.h"

#include "Actor/Player.h"

#include "Action/ActionMgr.h"
#include "Script/ScriptMgr.h"

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Network::Packets;

void Core::Network::GameConnection::actionHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                   Entity::Player& player )
{
   const auto packet = ZoneChannelPacket< Client::FFXIVIpcSkillHandler >( inPacket );

   const auto type = packet.data().type;
   const auto action = packet.data().actionId;
   const auto useCount = packet.data().useCount;
   const auto targetId = packet.data().targetId;

   player.sendDebug( "Skill type:" + std::to_string( type ) );

   auto pExdData = g_fw.get< Data::ExdDataGenerated >();

   std::string actionIdStr = boost::str( boost::format( "%|04X|" ) % action );
   player.sendDebug( "---------------------------------------" );
   player.sendDebug( "ActionHandler ( " + actionIdStr + " | " +
                     pExdData->get< Core::Data::Action >( action )->name +
                     " | " + std::to_string( targetId ) + " )" );

   auto pActionMgr = g_fw.get< Action::ActionMgr >();
   if( pActionMgr )
      pActionMgr->actionRouter( player, type, action, useCount, targetId );
}
