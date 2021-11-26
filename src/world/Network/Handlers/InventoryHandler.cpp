#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"

#include "Territory/Territory.h"
#include "Actor/Player.h"

#include "Session.h"
#include "WorldServer.h"
#include <Service.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;

void Sapphire::Network::GameConnection::itemOperation( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  const auto packet = ZoneChannelPacket< FFXIVIpcClientInventoryItemOperation >( inPacket );

  const auto operationType = packet.data().OperationType;
  const auto splitCount = packet.data().SrcStack;

  const auto fromSlot = packet.data().SrcContainerIndex;
  const auto fromContainer = packet.data().SrcStorageId;
  const auto toSlot = packet.data().DstContainerIndex;
  const auto toContainer = packet.data().DstStorageId;

  const auto contextId = packet.data().ContextId;

  auto ackPacket = makeZonePacket< FFXIVIpcItemOperationBatch >( player.getId() );
  ackPacket->data().contextId = contextId;
  ackPacket->data().operationType = operationType;
  server.queueForPlayer( player.getCharacterId(), ackPacket );

  Logger::debug( "OperationType: {0}", operationType );

  // TODO: other inventory operations need to be implemented
  switch( operationType )
  {

    case Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_DELETEITEM: // discard item action
    {
      player.discardItem( fromContainer, fromSlot );
    }
      break;

    case Common::ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_MOVEITEM: // move item action
    {
      player.moveItem( fromContainer, fromSlot, toContainer, toSlot );
    }
      break;

    case ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_SWAPITEM: // swap item action
    {
      player.swapItem( fromContainer, fromSlot, toContainer, toSlot );
    }
      break;

    case ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_MERGEITEM: // merge stack action
    {
      player.mergeItem( fromContainer, fromSlot, toContainer, toSlot );
    }
      break;

    case ITEM_OPERATION_TYPE::ITEM_OPERATION_TYPE_SPLITITEM: // split stack action
    {
      player.splitItem( fromContainer, fromSlot, toContainer, toSlot, splitCount );
    }
      break;

    default:
      break;

  }
}

