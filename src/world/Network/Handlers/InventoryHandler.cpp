#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"

#include "Territory/Territory.h"
#include "Territory/ZonePosition.h"

#include "Manager/DebugCommandMgr.h"
#include "Actor/Player.h"

#include "Session.h"
#include "ServerMgr.h"

#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

void Sapphire::Network::GameConnection::inventoryModifyHandler( FrameworkPtr pFw,
                                                                const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                                Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcInventoryModifyHandler >( inPacket );

  const auto action = packet.data().action;
  const auto splitCount = packet.data().splitCount;

  const auto fromSlot = packet.data().fromSlot;
  const auto fromContainer = packet.data().fromContainer;
  const auto toSlot = packet.data().toSlot;
  const auto toContainer = packet.data().toContainer;

  auto ackPacket = makeZonePacket< Server::FFXIVIpcInventoryActionAck >( player.getId() );
  ackPacket->data().sequence = packet.data().seq;
  ackPacket->data().type = 7;
  player.queuePacket( ackPacket );

  Logger::debug( "InventoryAction: {0}", action );

  // TODO: other inventory operations need to be implemented
  switch( action )
  {

    case InventoryOperation::Discard: // discard item action
    {
      player.discardItem( fromContainer, fromSlot );
    }
      break;

    case InventoryOperation::Move: // move item action
    {
      player.moveItem( fromContainer, fromSlot, toContainer, toSlot );
    }
      break;

    case InventoryOperation::Swap: // swap item action
    {
      player.swapItem( fromContainer, fromSlot, toContainer, toSlot );
    }
      break;

    case InventoryOperation::Merge: // merge stack action
    {
      player.mergeItem( fromContainer, fromSlot, toContainer, toSlot );
    }
      break;

    case InventoryOperation::Split: // split stack action
    {
      player.splitItem( fromContainer, fromSlot, toContainer, toSlot, splitCount );
    }
      break;

    default:
      break;

  }
}

