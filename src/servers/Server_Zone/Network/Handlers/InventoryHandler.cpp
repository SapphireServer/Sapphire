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

#include "src/servers/Server_Zone/Network/PacketWrappers/ServerNoticePacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket144.h"

#include "src/servers/Server_Zone/DebugCommand/DebugCommandHandler.h"
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Inventory/Inventory.h"
#include "src/servers/Server_Zone/Forwards.h"

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::ZoneMgr g_zoneMgr;
extern Core::Data::ExdData g_exdData;
extern Core::DebugCommandHandler g_gameCommandMgr;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;


void Core::Network::GameConnection::inventoryModifyHandler( const Packets::GamePacket& inPacket,
                                                            Entity::PlayerPtr pPlayer )
{
   uint32_t seq = inPacket.getValAt< uint32_t >( 0x20 );
   uint8_t action = inPacket.getValAt< uint8_t >( 0x24 );
   uint8_t fromSlot = inPacket.getValAt< uint8_t >( 0x30 );
   uint8_t toSlot = inPacket.getValAt< uint8_t >( 0x44 );
   uint16_t fromContainer = inPacket.getValAt< uint16_t >( 0x2C );
   uint16_t toContainer = inPacket.getValAt< uint16_t >( 0x40 );

   ZoneChannelPacket< FFXIVIpcInventoryActionAck > ackPacket( pPlayer->getId() );
   ackPacket.data().sequence = seq;
   ackPacket.data().type = 7;
   pPlayer->queuePacket( ackPacket );


   g_log.debug( inPacket.toString() );
   g_log.debug( "InventoryAction: " + std::to_string( action ) );

   // TODO: other inventory operations need to be implemented
   switch( action )
   {

      case 0x07: // discard item action
      {
         pPlayer->getInventory()->discardItem( fromContainer, fromSlot );
      }
      break;

      case 0x08: // move item action
      {
         pPlayer->getInventory()->moveItem( fromContainer, fromSlot, toContainer, toSlot );
      }
      break;

      case 0x09: // swap item action
      {
         pPlayer->getInventory()->swapItem( fromContainer, fromSlot, toContainer, toSlot );
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

