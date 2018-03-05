#include <boost/format.hpp>

#include <common/Common.h>
#include <common/Network/CommonNetwork.h>
#include <common/Network/GamePacketNew.h>
#include <common/Logging/Logger.h>
#include <common/Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

#include "Zone/Zone.h"
#include "Zone/ZonePosition.h"

#include "DebugCommand/DebugCommandHandler.h"
#include "Actor/Player.h"
#include "Inventory/Inventory.h"

#include "Session.h"
#include "ServerZone.h"
#include "Forwards.h"
#include "Framework.h"

extern Core::Framework g_framework;

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

   ZoneChannelPacket< FFXIVIpcInventoryActionAck > ackPacket( player.getId() );
   ackPacket.data().sequence = seq;
   ackPacket.data().type = 7;
   player.queuePacket( ackPacket );


   g_framework.getLogger().debug( inPacket.toString() );
   g_framework.getLogger().debug( "InventoryAction: " + std::to_string( action ) );

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

      }
      break;

      case InventoryOperation::Split: // split stack action
      {

      }
      break;

      default:
         break;

   }
}

