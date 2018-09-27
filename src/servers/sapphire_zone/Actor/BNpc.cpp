#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/EffectPacket.h>

#include "Forwards.h"
#include "Action/Action.h"

#include "Zone/Zone.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/NpcSpawnPacket.h"

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

Core::Entity::BNpc::BNpc( BNpcTemplatePtr pTemplate, float posX, float posY, float posZ, uint8_t level ) : Npc( ObjKind::BattleNpc )
{
  m_modelChara = pTemplate->getModelChara();
  m_displayFlags = pTemplate->getDisplayFlags();
  m_pose = pTemplate->getPose();
  m_aggressionMode = pTemplate->getAggressionMode();
  m_weaponMain = pTemplate->getWeaponMain();
  m_weaponSub = pTemplate->getWeaponSub();
  m_bNpcNameId = pTemplate->getBNpcNameId();
  m_bNpcBaseId = pTemplate->getBNpcBaseId();
  m_enemyType = pTemplate->getEnemyType();
  m_pos.x = posX;
  m_pos.y = posY;
  m_pos.z = posZ;
  m_level = level;

  m_maxHp = 200;
  m_maxMp = 200;
  m_hp = 200;
  m_mp = 200;

  m_baseStats.max_hp = 200;
  m_baseStats.max_mp = 200;

  memcpy( m_customize, pTemplate->getCustomize(), sizeof( m_customize ) );
  memcpy( m_modelEquip, pTemplate->getModelEquip(), sizeof( m_modelEquip ) );

}

Core::Entity::BNpc::~BNpc()
{
}

uint8_t Core::Entity::BNpc::getAggressionMode() const
{
  return m_aggressionMode;
}

uint8_t Core::Entity::BNpc::getEnemyType() const
{
  return m_enemyType;
}

uint64_t Core::Entity::BNpc::getWeaponMain() const
{
  return m_weaponMain;
}

uint64_t Core::Entity::BNpc::getWeaponSub() const
{
  return m_weaponSub;
}

uint16_t Core::Entity::BNpc::getModelChara() const
{
  return m_modelChara;
}

uint8_t Core::Entity::BNpc::getLevel() const
{
  return m_level;
}

uint32_t Core::Entity::BNpc::getBNpcBaseId() const
{
  return m_bNpcBaseId;
}

uint32_t Core::Entity::BNpc::getBNpcNameId() const
{
  return m_bNpcNameId;
}

void Core::Entity::BNpc::spawn( PlayerPtr pTarget )
{
  pTarget->queuePacket( boost::make_shared< NpcSpawnPacket >( *getAsBNpc(), *pTarget ) );
}
