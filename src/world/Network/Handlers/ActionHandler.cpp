#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/GamePacketNew.h>
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

  auto exdData = m_pFw->get< Data::ExdDataGenerated >();
  assert( exdData );

  auto action = exdData->get< Data::Action >( actionId );

  // ignore invalid actions
  if( !action )
    return;

  auto actionMgr = pFw->get< World::Manager::ActionMgr >();
  actionMgr->handleTargetedPlayerAction( player, type, actionId, action, targetId );

  player.sendDebug( "Skill type: {0}, sequence: {1}, actionId: {2}, targetId: {3}", type, sequence, actionId, targetId );
}

void Sapphire::Network::GameConnection::aoeActionHandler( FrameworkPtr pFw,
                                                          const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcAoESkillHandler >( inPacket );

  const auto type = packet.data().type;
  const auto actionId = packet.data().actionId;
  const auto sequence = packet.data().sequence;
  const auto pos = packet.data().pos;

  auto exdData = m_pFw->get< Data::ExdDataGenerated >();
  assert( exdData );

  auto action = exdData->get< Data::Action >( actionId );

  // ignore invalid actions
  if( !action )
    return;

  auto actionMgr = pFw->get< World::Manager::ActionMgr >();
  actionMgr->handleAoEPlayerAction( player, type, actionId, action, pos );

  player.sendDebug( "Skill type: {0}, sequence: {1}, actionId: {2}, x:{3}, y:{4}, z:{5}",
                    type, sequence, actionId, pos.x, pos.y, pos.z );
}
