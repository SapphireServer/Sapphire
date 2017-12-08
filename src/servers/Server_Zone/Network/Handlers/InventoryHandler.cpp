#include <Server_Common/Common.h>
#include <Server_Common/Network/CommonNetwork.h>
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Network/PacketContainer.h>

#include <boost/format.hpp>

#include "Network/GameConnection.h"

#include "Session.h"
#include "Zone/Zone.h"
#include "Zone/ZonePosition.h"
#include "ServerZone.h"
#include "Zone/ZoneMgr.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

#include "DebugCommand/DebugCommandHandler.h"
#include "Actor/Player.h"
#include "Inventory/Inventory.h"
#include "Forwards.h"

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::DebugCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;


void Core::Network::GameConnection::inventoryModifyHandler( const Packets::GamePacket& inPacket,
                                                            Entity::Player& player )
{
   uint32_t seq = inPacket.getValAt< uint32_t >( 0x20 );
   uint8_t action = inPacket.getValAt< uint8_t >( 0x24 );
   uint8_t fromSlot = inPacket.getValAt< uint8_t >( 0x30 );
   uint8_t toSlot = inPacket.getValAt< uint8_t >( 0x44 );
   uint16_t fromContainer = inPacket.getValAt< uint16_t >( 0x2C );
   uint16_t toContainer = inPacket.getValAt< uint16_t >( 0x40 );

   ZoneChannelPacket< FFXIVIpcInventoryActionAck > ackPacket( player.getId() );
   ackPacket.data().sequence = seq;
   ackPacket.data().type = 7;
   player.queuePacket( ackPacket );


   g_log.debug( inPacket.toString() );
   g_log.debug( "InventoryAction: " + std::to_string( action ) );

   // TODO: other inventory operations need to be implemented
   switch( action )
   {

      case 0x07: // discard item action
      {
         player.getInventory()->discardItem( fromContainer, fromSlot );
      }
      break;

      case 0x08: // move item action
      {
         player.getInventory()->moveItem( fromContainer, fromSlot, toContainer, toSlot );
      }
      break;

      case 0x09: // swap item action
      {
         player.getInventory()->swapItem( fromContainer, fromSlot, toContainer, toSlot );
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
}

