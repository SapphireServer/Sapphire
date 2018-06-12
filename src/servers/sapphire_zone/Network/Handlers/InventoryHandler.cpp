#include <boost/format.hpp>

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacketNew.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

#include "Zone/Zone.h"
#include "Zone/ZonePosition.h"

#include "DebugCommand/DebugCommandHandler.h"
#include "Actor/Player.h"

#include "Session.h"
#include "ServerZone.h"

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

enum InventoryOperation
{
   Discard = 0x07,
   Move = 0x08,
   Swap = 0x09,
   Merge = 0x0C,
   Split = 0x0A
};

void Core::Network::GameConnection::inventoryModifyHandler( const Packets::GamePacket& inPacket,
                                                            Entity::Player& player )
{
   uint32_t seq = inPacket.getValAt< uint32_t >( 0x20 );
   uint8_t action = inPacket.getValAt< uint8_t >( 0x24 );
   uint8_t fromSlot = inPacket.getValAt< uint8_t >( 0x30 );
   uint8_t toSlot = inPacket.getValAt< uint8_t >( 0x44 );
   uint16_t fromContainer = inPacket.getValAt< uint16_t >( 0x2C );
   uint16_t toContainer = inPacket.getValAt< uint16_t >( 0x40 );
   // todo: check packet handler in game and see if this is sent as a u16 or u32
   uint16_t splitCount = inPacket.getValAt< uint16_t >( 0x48 );

   ZoneChannelPacket< FFXIVIpcInventoryActionAck > ackPacket( player.getId() );
   ackPacket.data().sequence = seq;
   ackPacket.data().type = 7;
   player.queuePacket( ackPacket );
  
   auto pLog = g_fw.get< Logger >();


   pLog->debug( inPacket.toString() );
   pLog->debug( "InventoryAction: " + std::to_string( action ) );

   // TODO: other inventory operations need to be implemented
   switch( action )
   {

      case InventoryOperation::Discard: // discard item action
      {
         player.getInventory()->discardItem( fromContainer, fromSlot );
      }
      break;

      case InventoryOperation::Move: // move item action
      {
         player.getInventory()->moveItem( fromContainer, fromSlot, toContainer, toSlot );
      }
      break;

      case InventoryOperation::Swap: // swap item action
      {
         player.getInventory()->swapItem( fromContainer, fromSlot, toContainer, toSlot );
      }
      break;

      case InventoryOperation::Merge: // merge stack action
      {
         player.getInventory()->mergeItem( fromContainer, fromSlot, toContainer, toSlot );
      }
      break;

      case InventoryOperation::Split: // split stack action
      {
         player.getInventory()->splitItem( fromContainer, fromSlot, toContainer, toSlot, splitCount );
      }
      break;

      default:
         break;

   }
}

