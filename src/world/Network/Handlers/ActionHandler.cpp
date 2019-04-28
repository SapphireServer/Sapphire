#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Logging/Logger.h>

#include <Actor/Player.h>

#include "Network/GameConnection.h"
#include "Framework.h"

#include "Manager/ActionMgr.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;

void Sapphire::Network::GameConnection::actionHandler( FrameworkPtr pFw,
                                                       const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSkillHandler >( inPacket );

  const auto type = packet.data().type;
  const auto actionId = packet.data().actionId;
  const auto sequence = packet.data().sequence;
  const auto targetId = packet.data().targetId;
  const auto itemSourceSlot = packet.data().itemSourceSlot;
  const auto itemSourceContainer = packet.data().itemSourceContainer;

  player.sendDebug( "Skill type: {0}, sequence: {1}, actionId: {2}, targetId: {3}", type, sequence, actionId, targetId );

  auto exdData = m_pFw->get< Data::ExdDataGenerated >();
  assert( exdData );

  auto actionMgr = pFw->get< World::Manager::ActionMgr >();

  switch( type )
  {
    default:
    {
      player.sendDebug( "Skill type {0} not supported. Defaulting to normal action", type );
    }
    case Common::SkillType::Normal:
    {
      auto action = exdData->get< Data::Action >( actionId );

      // ignore invalid actions
      if( !action )
        return;

      actionMgr->handleTargetedPlayerAction( player, actionId, action, targetId );
      break;
    }

    case Common::SkillType::ItemAction:
    {
      auto item = exdData->get< Data::Item >( actionId );
      if( !item )
        return;

      if( item->itemAction == 0 )
        return;

      auto itemAction = exdData->get< Data::ItemAction >( item->itemAction );
      if( !itemAction )
        return;

      actionMgr->handleItemAction( player, actionId, itemAction, itemSourceSlot, itemSourceContainer );

      break;
    }

    case Common::SkillType::MountSkill:
    {

      break;
    }
  }



}

void Sapphire::Network::GameConnection::placedActionHandler( FrameworkPtr pFw,
                                                             const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                             Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcAoESkillHandler >( inPacket );

  const auto type = packet.data().type;
  const auto actionId = packet.data().actionId;
  const auto sequence = packet.data().sequence;
  const auto pos = packet.data().pos;

  // todo: find out if there are any other action types which actually use this handler
  if( type != Common::SkillType::Normal )
  {
    player.sendDebug( "Skill type {0} not supported by aoe action handler!", type );
    return;
  }

  player.sendDebug( "Skill type: {0}, sequence: {1}, actionId: {2}, x:{3}, y:{4}, z:{5}",
                    type, sequence, actionId, pos.x, pos.y, pos.z );

  auto exdData = m_pFw->get< Data::ExdDataGenerated >();
  assert( exdData );

  auto action = exdData->get< Data::Action >( actionId );

  // ignore invalid actions
  if( !action )
    return;

  auto actionMgr = pFw->get< World::Manager::ActionMgr >();
  actionMgr->handlePlacedPlayerAction( player, actionId, action, pos );
}
