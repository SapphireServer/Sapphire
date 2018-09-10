#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>
#include <sapphire_zone/Network/PacketWrappers/EffectPacket.h>

#include "Forwards.h"
#include "Action/Action.h"

#include "Zone/Zone.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"

#include "StatusEffect/StatusEffect.h"
#include "Action/ActionCollision.h"
#include "ServerZone.h"
#include "Session.h"
#include "Math/CalcBattle.h"
#include "Chara.h"
#include "Player.h"
#include "BNpc.h"
#include "BNpcTemplate.h"
#include "Zone/TerritoryMgr.h"
#include "Framework.h"
#include "Common.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;

Core::Entity::BNpc::BNpc() : Npc( ObjKind::BattleNpc )
{
}

Core::Entity::BNpc::BNpc( BNpcTemplatePtr pTemplate ) : Npc( ObjKind::BattleNpc )
{
  m_modelChara = pTemplate->getModelChara();
  m_displayFlags = pTemplate->getDisplayFlags();
  m_pose = pTemplate->getPose();
  m_aggressionMode = pTemplate->getAggressionMode();
  m_weaponMain = pTemplate->getWeaponMain();
  m_weaponSub = pTemplate->getWeaponSub();
  m_bNpcNameId = pTemplate->getBNpcNameId();
  m_bNpcBaseId = pTemplate->getBNpcBaseId();

  memcpy( m_customize, pTemplate->getCustomize(), sizeof( m_customize ) );
  memcpy( m_modelEquip, pTemplate->getModelEquip(), sizeof( m_modelEquip ) );

}

Core::Entity::BNpc::~BNpc()
{
}

void Core::Entity::BNpc::spawn( PlayerPtr pTarget )
{

}