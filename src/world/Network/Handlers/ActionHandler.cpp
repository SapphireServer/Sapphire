#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Logging/Logger.h>
#include <Util/Util.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/MoveActorPacket.h"

#include "Network/PacketWrappers/PlayerStateFlagsPacket.h"

#include "Manager/DebugCommandMgr.h"
#include "Manager/ActionMgr.h"

#include "Action/Action.h"
#include "Action/ActionCast.h"
#include "Script/ScriptMgr.h"

#include "Session.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

void Sapphire::Network::GameConnection::actionHandler( FrameworkPtr pFw,
                                                       const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                       Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcSkillHandler >( inPacket );

  const auto type = packet.data().type;
  const auto action = packet.data().actionId;
  const auto sequence = packet.data().sequence;
  const auto targetId = packet.data().targetId;

  player.sendDebug( "Skill type: {0}, sequence: {1}, actionId: {2}, targetId: {3}", type, sequence, action, targetId );

  auto actionMgr = pFw->get< World::Manager::ActionMgr >();
  actionMgr->handleTargetedPlayerAction( player, type, action, targetId );
}

void Sapphire::Network::GameConnection::aoeActionHandler( FrameworkPtr pFw,
                                                          const Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                          Entity::Player& player )
{
  const auto packet = ZoneChannelPacket< Client::FFXIVIpcAoESkillHandler >( inPacket );

  const auto type = packet.data().type;
  const auto action = packet.data().actionId;
  const auto sequence = packet.data().sequence;
  const auto pos = packet.data().pos;

  auto actionMgr = pFw->get< World::Manager::ActionMgr >();
  actionMgr->handleAoEPlayerAction( player, type, action, pos );

  player.sendDebug( "Skill type: {0}, sequence: {1}, actionId: {2}\nx:{3}, y:{4}, z:{5}",
                    type, sequence, action, pos.x, pos.y, pos.z );
}
