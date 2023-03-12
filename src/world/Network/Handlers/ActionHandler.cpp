#include <Common.h>
#include <Exd/ExdData.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>

#include <Actor/Player.h>
#include <Service.h>

#include "Network/GameConnection.h"

#include "Manager/ActionMgr.h"
#include "Manager/PlayerMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Client;

void Sapphire::Network::GameConnection::actionRequest( const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< FFXIVIpcActionRequest >( inPacket );

  const auto type = packet.data().ActionKind;
  const auto actionId = packet.data().ActionKey;
  const auto requestId = packet.data().RequestId;
  const auto targetId = packet.data().Target;
  const auto itemSourceSlot = packet.data().Arg & 0x0000FFFF;
  const auto itemSourceContainer = packet.data().Arg & 0xFFFF0000;

  PlayerMgr::sendDebug( player, "Skill type: {0}, requestId: {1}, actionId: {2}, targetId: {3}", type, requestId, actionId, targetId );

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& actionMgr = Common::Service< World::Manager::ActionMgr >::ref();

  switch( type )
  {
    default:
    {
      PlayerMgr::sendDebug( player, "Skill type {0} not supported. Defaulting to normal action", type );
    }
    case Common::ActionKind::ACTION_KIND_NORMAL:
    {
      auto action = exdData.getRow< Excel::Action >( actionId );

      // ignore invalid actions
      if( !action )
        return;

      auto category = static_cast< Common::ActionCategory >( action->data().Category );

      if( category  == Common::ActionCategory::ItemManipulation )
        actionMgr.handleItemManipulationAction( player, actionId, requestId );
      else
        actionMgr.handleTargetedAction( player, actionId, targetId, requestId );
      break;
    }

    case Common::ActionKind::ACTION_KIND_ITEM:
    {
      auto item = exdData.getRow< Excel::Item >( actionId );
      if( !item )
        return;

      if( item->data().Action == 0 )
        return;

      auto itemAction = exdData.getRow< Excel::ItemAction >( item->data().Action );
      if( !itemAction )
        return;

      actionMgr.handleItemAction( player, actionId, itemAction, itemSourceSlot, itemSourceContainer );

      break;
    }

    case Common::ActionKind::ACTION_KIND_EVENT_ITEM:
    {
      auto action = exdData.getRow< Excel::EventItem >( actionId );
      assert( action );
      actionMgr.handleEventItemAction( player, actionId, action, requestId, targetId );
      break;
    }

    case Common::ActionKind::ACTION_KIND_MOUNT:
    {
      auto action = exdData.getRow< Excel::Action >( 4 );
      assert( action );
      actionMgr.handleMountAction( player, static_cast< uint16_t >( actionId ), action, targetId, requestId );
      break;
    }
  }



}

void Sapphire::Network::GameConnection::selectGroundActionRequest( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< FFXIVIpcSelectGroundActionRequest >( inPacket );

  const auto type = packet.data().ActionKind;
  const auto actionId = packet.data().ActionKey;
  const auto requestId = packet.data().RequestId;
  const auto pos = packet.data().Pos;

  // todo: find out if there are any other action types which actually use this handler
  if( type != Common::ActionKind::ACTION_KIND_NORMAL )
  {
    PlayerMgr::sendDebug( player, "Skill type {0} not supported by aoe action handler!", type );
    return;
  }

  PlayerMgr::sendDebug( player, "Skill type: {0}, requestId: {1}, actionId: {2}, x:{3}, y:{4}, z:{5}",
                        type, requestId, actionId, pos.x, pos.y, pos.z );

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto action = exdData.getRow< Excel::Action >( actionId );

  // ignore invalid actions
  if( !action )
    return;

  auto& actionMgr = Common::Service< World::Manager::ActionMgr >::ref();
  actionMgr.handlePlacedAction( player, actionId, pos, requestId );
}
