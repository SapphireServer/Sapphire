#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <utility>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/EffectPacket1.h>
#include <Logging/Logger.h>

#include "Forwards.h"
#include "Action/Action.h"

#include "Territory/Territory.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/NpcSpawnPacket.h"
#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/Util/PacketUtil.h"

#include "Navi/NaviProvider.h"

#include "Math/CalcStats.h"

#include "WorldServer.h"
#include "Session.h"
#include "Chara.h"
#include "BNpc.h"

#include "Common.h"

#include <Manager/TerritoryMgr.h>
#include <Manager/RNGMgr.h>
#include <Manager/PlayerMgr.h>
#include <Manager/TaskMgr.h>
#include <Manager/MgrUtil.h>
#include <Manager/ActionMgr.h>
#include <Script/ScriptMgr.h>
#include <Task/RemoveBNpcTask.h>
#include <Task/FadeBNpcTask.h>
#include <Task/DelayedEmnityTask.h>
#include <Task/ActionIntegrityTask.h>
#include <Service.h>

#include <Action/Action.h>
#include <AI/GambitRule.h>
#include <AI/GambitPack.h>
#include <AI/GambitTargetCondition.h>
#include <AI/Fsm/StateMachine.h>
#include <AI/Fsm/Condition.h>
#include <AI/Fsm/StateIdle.h>
#include <AI/Fsm/StateRoam.h>
#include <AI/Fsm/StateCombat.h>
#include <AI/Fsm/StateRetreat.h>
#include <AI/Fsm/StateDead.h>

using namespace Sapphire;
using namespace Sapphire::World;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

BNpc::BNpc() : Npc( ObjKind::BattleNpc )
{
}

BNpc::BNpc( uint32_t id, std::shared_ptr< Common::BNPCInstanceObject > pInfo, const Territory& zone ) : Npc( ObjKind::BattleNpc )
{
  m_id = id;
  m_pInfo = pInfo;
  m_layoutId = pInfo->instanceId;

  m_aggressionMode = pInfo->ActiveType;

  m_displayFlags = 0;
  m_weaponMain = 0;
  m_weaponSub = 0;
  m_pose = 0;

  m_bNpcNameId = pInfo->NameId;
  m_bNpcBaseId = pInfo->BaseId;

  m_pos.x = pInfo->x;
  m_pos.y = pInfo->y;
  m_pos.z = pInfo->z;
  m_rot = pInfo->rotation;
  m_level = pInfo->Level <= 0 ? 1 : pInfo->Level;
  m_invincibilityType = InvincibilityNone;
  m_currentStance = Common::Stance::Passive;
  m_boundInstanceId = pInfo->BoundInstanceID;
  m_flags = 0;
  m_rank = pInfo->BNPCRankId;



  // Striking Dummy
  if( pInfo->NameId == 541 )
    m_invincibilityType = Common::InvincibilityRefill;

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto bNpcBaseData = exdData.getRow< Excel::BNpcBase >( m_bNpcBaseId );
  if( !bNpcBaseData )
  {
    Logger::debug( "BNpcBase#{0} not found in exd data!", m_bNpcBaseId );
    return;
  }

  m_modelChara = bNpcBaseData->data().Model;
  m_enemyType = bNpcBaseData->data().Battalion;

  if( pInfo->WanderingRange == 0 || pInfo->BoundInstanceID != 0 || m_enemyType == 0 )
    setFlag( Immobile );

  m_class = ClassJob::Gladiator;

  m_territoryTypeId = zone.getTerritoryTypeId();
  m_territoryId = zone.getGuId();

  m_spawnPos = m_pos;

  m_timeOfDeath = 0;
  m_targetId = Common::INVALID_GAME_OBJECT_ID64;

  m_maxHp = 500;
  m_maxMp = 200;
  m_hp = m_maxHp;
  m_mp = 200;

  if( m_level <= BnpcBaseHp.size() )
    m_maxHp = BnpcBaseHp[ m_level - 1 ];

  m_state = BNpcState::Idle;
  m_status = ActorStatus::Idle;

  memset( m_customize, 0, sizeof( m_customize ) );
  memset( m_modelEquip, 0, sizeof( m_modelEquip ) );


  m_radius = bNpcBaseData->data().Scale;
  if( bNpcBaseData->data().Customize != 0 )
  {
    auto bnpcCustom = exdData.getRow< Excel::BNpcCustomize >( bNpcBaseData->data().Customize );
    if( bnpcCustom )
    {
      memcpy( m_customize, reinterpret_cast< char* >( &bnpcCustom->data() ), sizeof( m_customize ) );
    }
  }

  if( bNpcBaseData->data().Equipment != 0 )
  {
    auto bnpcEquip = exdData.getRow< Excel::NpcEquip >( bNpcBaseData->data().Equipment );
    if( bnpcEquip )
    {
      m_weaponMain = bnpcEquip->data().WeaponModel;
      m_weaponSub = bnpcEquip->data().SubWeaponModel;
      memcpy( m_modelEquip, reinterpret_cast< char* >( bnpcEquip->data().Equip ), sizeof( m_modelEquip ) );
    }
  }

  auto modelChara = exdData.getRow< Excel::ModelChara >( bNpcBaseData->data().Model );
  if( modelChara )
  {
    auto modelSkeleton = exdData.getRow< Excel::ModelSkeleton >( modelChara->data().SkeletonId );
    if( modelSkeleton )
    {
      m_radius *= modelSkeleton->data().Radius;
    }
  }

  // todo: is this actually good?
  m_naviTargetReachedDistance = m_radius * 2;

  calculateStats();

  if( m_bnpcType == BNpcType::Friendly )
    m_maxHp *= 5;

}

BNpc::BNpc( uint32_t id, std::shared_ptr< Common::BNPCInstanceObject > pInfo, const Territory& zone, uint32_t hp, Common::BNpcType type ) :
  Npc( ObjKind::BattleNpc )
{
  m_id = id;
  m_pInfo = pInfo;
  m_layoutId = pInfo->instanceId;

  m_aggressionMode = pInfo->ActiveType;

  m_displayFlags = 0;
  m_weaponMain = 0;
  m_weaponSub = 0;
  m_pose = 0;

  m_bNpcNameId = pInfo->NameId;
  m_bNpcBaseId = pInfo->BaseId;

  m_pos.x = pInfo->x;
  m_pos.y = pInfo->y;
  m_pos.z = pInfo->z;
  m_rot = pInfo->rotation;
  m_level = pInfo->Level <= 0 ? 1 : pInfo->Level;
  m_invincibilityType = InvincibilityNone;
  m_currentStance = Common::Stance::Passive;
  m_boundInstanceId = pInfo->BoundInstanceID;
  m_flags = 0;
  m_rank = pInfo->BNPCRankId;

  m_territoryTypeId = zone.getTerritoryTypeId();
  m_territoryId = zone.getGuId();

  if( pInfo->WanderingRange == 0 || pInfo->BoundInstanceID != 0 )
    setFlag( Immobile );

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto bNpcBaseData = exdData.getRow< Excel::BNpcBase >( m_bNpcBaseId );
  if( !bNpcBaseData )
  {
    Logger::debug( "BNpcBase#{0} not found in exd data!", m_bNpcBaseId );
    return;
  }

  m_modelChara = bNpcBaseData->data().Model;
  m_enemyType = bNpcBaseData->data().Battalion;

  m_class = ClassJob::Gladiator;

  m_spawnPos = m_pos;

  m_timeOfDeath = 0;
  m_targetId = Common::INVALID_GAME_OBJECT_ID64;

  m_maxHp = hp;
  m_maxMp = 200;
  m_hp = m_maxHp;
  m_mp = 200;

  m_state = BNpcState::Idle;
  m_status = ActorStatus::Idle;

  m_bnpcType = type;

  memset( m_customize, 0, sizeof( m_customize ) );
  memset( m_modelEquip, 0, sizeof( m_modelEquip ) );


  m_radius = bNpcBaseData->data().Scale;
  if( bNpcBaseData->data().Customize != 0 )
  {
    auto bnpcCustom = exdData.getRow< Excel::BNpcCustomize >( bNpcBaseData->data().Customize );
    if( bnpcCustom )
    {
      memcpy( m_customize, reinterpret_cast< char* >( &bnpcCustom->data() ), sizeof( m_customize ) );
    }
  }

  if( bNpcBaseData->data().Equipment != 0 )
  {
    auto bnpcEquip = exdData.getRow< Excel::NpcEquip >( bNpcBaseData->data().Equipment );
    if( bnpcEquip )
    {
      m_weaponMain = bnpcEquip->data().WeaponModel;
      m_weaponSub = bnpcEquip->data().SubWeaponModel;
      memcpy( m_modelEquip, reinterpret_cast< char* >( bnpcEquip->data().Equip ), sizeof( m_modelEquip ) );
    }
  }

  auto modelChara = exdData.getRow< Excel::ModelChara >( bNpcBaseData->data().Model );
  if( modelChara )
  {
    auto modelSkeleton = exdData.getRow< Excel::ModelSkeleton >( modelChara->data().ModelType );
    if( modelSkeleton )
      m_radius *= modelSkeleton->data().Radius;
  }

  // todo: is this actually good?
  m_naviTargetReachedDistance = m_radius;

  calculateStats();
}

BNpc::~BNpc() = default;

uint8_t BNpc::getAggressionMode() const
{
  return m_aggressionMode;
}

float BNpc::getNaviTargetReachedDistance() const
{
  return m_naviTargetReachedDistance;
}

uint8_t BNpc::getEnemyType() const
{
  return m_enemyType;
}

uint64_t BNpc::getWeaponMain() const
{
  return m_weaponMain;
}

uint64_t BNpc::getWeaponSub() const
{
  return m_weaponSub;
}

uint16_t BNpc::getModelChara() const
{
  return m_modelChara;
}

uint8_t BNpc::getLevel() const
{
  return m_level;
}

uint32_t BNpc::getBNpcBaseId() const
{
  return m_bNpcBaseId;
}

uint32_t BNpc::getBNpcNameId() const
{
  return m_bNpcNameId;
}

void BNpc::spawn( PlayerPtr pTarget )
{
  m_lastRoamTargetReachedTime = Common::Util::getTimeSeconds();

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( pTarget->getCharacterId(), std::make_shared< NpcSpawnPacket >( *this, *pTarget ) );
}

void BNpc::despawn( PlayerPtr pTarget )
{
  pTarget->freePlayerSpawnId( getId() );
  Network::Util::Packet::sendActorControlSelf( *pTarget, getId(), WarpStart, 4, getId(), 1 );
}

BNpcState BNpc::getState() const
{
  return m_state;
}

void BNpc::setState( BNpcState state )
{
  m_state = state;
}

bool BNpc::moveTo( const FFXIVARR_POSITION3& pos )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  auto pNaviProvider = pZone->getNaviProvider();

  if( !pNaviProvider )
  {
    Logger::error( "No NaviProvider for zone#{0} - {1}", pZone->getGuId(), pZone->getInternalName() );
    return false;
  }

  auto pos1 = pNaviProvider->getMovePos( *this );
  auto distance = Common::Util::distance( pos1, pos );

  if( distance < getNaviTargetReachedDistance() )
  {
    // Reached destination
    face( pos );
    setPos( pos1 );
    sendPositionUpdate();
    pNaviProvider->updateAgentPosition( *this );
    return true;
  }

  pZone->updateActorPosition( *this );
  face( pos );
  if( distance > 2.0f )
    face( { ( pos.x - pos1.x ) + pos.x, 1.0f, ( pos.z - pos1.z ) + pos.z } );
  else
    face( pos );
  setPos( pos1 );
  sendPositionUpdate();
  return false;
}

bool BNpc::moveTo( const Chara& targetChara )
{

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  auto pNaviProvider = pZone->getNaviProvider();

  if( !pNaviProvider )
  {
    Logger::error( "No NaviProvider for zone#{0} - {1}", pZone->getGuId(), pZone->getInternalName() );
    return false;
  }

  auto pos1 = pNaviProvider->getMovePos( *this );
  auto distance = Common::Util::distance( pos1, targetChara.getPos() );

  if( distance <= ( getNaviTargetReachedDistance() + targetChara.getRadius() ) )
  {
    // Reached destination
    face( targetChara.getPos() );
    setPos( pos1 );
    sendPositionUpdate();
    pNaviProvider->resetMoveTarget( *this );
    pNaviProvider->updateAgentPosition( *this );
    return true;
  }

  pZone->updateActorPosition( *this );
  if( distance > 2.0f )
    face( { ( pos1.x - getPos().x ) + pos1.x, 1.0f, ( pos1.z - getPos().z ) + pos1.z } );
  else
    face( targetChara.getPos() );
  setPos( pos1 );
  sendPositionUpdate();
  return false;
}

void BNpc::sendPositionUpdate()
{
  uint8_t animationType = 2;

  if( m_state == BNpcState::Combat || m_state == BNpcState::Retreat )
    animationType = 0;

  auto movePacket = std::make_shared< MoveActorPacket >( *getAsChara(), 0x3A, animationType, 0, 0x5A / 4 );
  server().queueForPlayers( getInRangePlayerIds(), movePacket );
}

void BNpc::hateListClear()
{
  for( auto& listEntry : m_hateList )
  {
    if( isInRangeSet( listEntry->m_pChara ) )
      deaggro( listEntry->m_pChara );
  }
  m_hateList.clear();
}

uint32_t BNpc::hateListGetValue( const Sapphire::Entity::CharaPtr& pChara )
{
  for( const auto& listEntry : m_hateList )
  {
    if( listEntry->m_pChara == pChara )
    {
      return listEntry->m_hateAmount;
    }
  }

  return 0;
}

uint32_t BNpc::hateListGetHighestValue()
{
  auto it = m_hateList.begin();
  uint32_t maxHate = 0;
  std::shared_ptr< HateListEntry > entry;
  for( ; it != m_hateList.end(); ++it )
  {
    if( ( *it )->m_hateAmount > maxHate )
    {
      maxHate = ( *it )->m_hateAmount;
      entry = *it;
    }
  }

  if( entry && maxHate != 0 )
    return entry->m_hateAmount;

  return 0;
}


CharaPtr BNpc::hateListGetHighest()
{
  auto it = m_hateList.begin();
  uint32_t maxHate = 0;
  std::shared_ptr< HateListEntry > entry;
  for( ; it != m_hateList.end(); ++it )
  {
    if( ( *it )->m_hateAmount > maxHate )
    {
      maxHate = ( *it )->m_hateAmount;
      entry = *it;
    }
  }

  if( entry && maxHate != 0 )
    return entry->m_pChara;

  return nullptr;
}

void BNpc::hateListAdd( const CharaPtr& pChara, int32_t hateAmount )
{
  auto hateEntry = std::make_shared< HateListEntry >();
  hateEntry->m_hateAmount = static_cast< uint32_t >( hateAmount );
  hateEntry->m_pChara = pChara;

  m_hateList.insert( hateEntry );
  if( pChara->isPlayer() )
  {
    auto pPlayer = pChara->getAsPlayer();
    pPlayer->hateListAdd( *this );
  }
}

void BNpc::hateListAddDelayed( const CharaPtr& pChara, int32_t hateAmount )
{
  auto& taskMgr = Common::Service< World::Manager::TaskMgr >::ref();
  auto delayedEmnityTask = std::make_shared< World::DelayedEmnityTask >( 5000, getAsBNpc(), pChara, hateAmount );
  taskMgr.queueTask( delayedEmnityTask );
}

void BNpc::hateListUpdate( const CharaPtr& pChara, int32_t hateAmount )
{
  bool hasEntry = false;

  for( const auto& listEntry : m_hateList )
  {
    if( listEntry->m_pChara == pChara )
    {
      listEntry->m_hateAmount += static_cast< uint32_t >( hateAmount );
      hasEntry = true;
      break;
    }
  }

  if( !hasEntry )
  {
    auto hateEntry = std::make_shared< HateListEntry >();
    hateEntry->m_hateAmount = static_cast< uint32_t >( hateAmount );
    hateEntry->m_pChara = pChara;
    m_hateList.insert( hateEntry );
  }

  for( const auto& listEntry : m_hateList )
  {
    // update entire hatelist for all players who are on aggro with this bnpc
    if( pChara->isPlayer() )
    {
      auto pPlayer = pChara->getAsPlayer();
      Network::Util::Packet::sendHateList( *pPlayer );
    }
  }
}

void BNpc::hateListRemove( const CharaPtr& pChara )
{
  for( const auto& listEntry : m_hateList )
  {
    if( listEntry->m_pChara == pChara )
    {
      m_hateList.erase( listEntry );

      if( pChara->isPlayer() )
      {
        PlayerPtr tmpPlayer = pChara->getAsPlayer();
        tmpPlayer->onMobDeaggro( *this );
      }
      return;
    }
  }
}

uint32_t BNpc::getTriggerOwnerId() const
{
  return m_triggerOwnerId;
}

void BNpc::setTriggerOwnerId( uint32_t triggerOwnerId )
{
  m_triggerOwnerId = triggerOwnerId;
}

bool BNpc::hateListHasActor( const Sapphire::Entity::CharaPtr& pChara )
{
  return std::any_of( m_hateList.begin(), m_hateList.end(),
                      [ pChara ]( const auto& entry ) { return entry->m_pChara == pChara; } );
}

void BNpc::aggro( const Sapphire::Entity::CharaPtr& pChara )
{
  auto& pRNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
  auto variation = static_cast< uint32_t >( pRNGMgr.getRandGenerator< float >( 500, 1000 ).next() );

  if( m_pGambitPack && m_pGambitPack->getAsTimeLine() )
  {
    m_pGambitPack->getAsTimeLine()->start();
  }

  m_lastAttack = Common::Util::getTimeMs() + variation;

  setStance( Stance::Active );
  m_state = BNpcState::Combat;

  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), SetBattle, 1 );

  changeTarget( pChara->getId() );

  if( pChara->isPlayer() )
  {
    PlayerPtr tmpPlayer = pChara->getAsPlayer();
    tmpPlayer->onMobAggro( *getAsBNpc() );
  }

}

void BNpc::deaggro( const CharaPtr& pChara )
{
  if( !hateListHasActor( pChara ) )
    hateListRemove( pChara );

  if( pChara->isPlayer() )
  {
    PlayerPtr tmpPlayer = pChara->getAsPlayer();
    Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), ToggleWeapon, 0, 1, 1 );
    Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), SetBattle );
    tmpPlayer->onMobDeaggro( *this );

    if( getTriggerOwnerId() == pChara->getId() )
    {
      auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
      auto bnpc = *getAsBNpc();
      scriptMgr.onTriggerOwnerDeaggro( *tmpPlayer, bnpc );
    }
  }
}

void BNpc::onTick()
{
  Chara::onTick();
  if( m_state == BNpcState::Retreat )
  {
    restHp();
  }
}

void BNpc::update( uint64_t tickCount )
{
  Chara::update( tickCount );
  m_fsm->update( *this, tickCount );
}

void BNpc::restHp()
{
  if( m_hp < getMaxHp() )
  {
    auto addHp = static_cast< uint32_t >( getMaxHp() * 0.1f + 1 );

    if( m_hp + addHp < getMaxHp() )
      m_hp += addHp;
    else
      m_hp = getMaxHp();
  }

  Network::Util::Packet::sendHudParam( *this );
}

void BNpc::onActionHostile( CharaPtr pSource )
{
  if( !hateListGetHighest() )
    aggro( pSource );

  hateListUpdate( pSource, 1 );

  if( !m_pOwner )
    setOwner( pSource );
}

void BNpc::onDeath()
{
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& taskMgr = Common::Service< World::Manager::TaskMgr >::ref();

  setTargetId( INVALID_GAME_OBJECT_ID64 );
  m_currentStance = Stance::Passive;
  m_state = BNpcState::Dead;
  m_timeOfDeath = Common::Util::getTimeSeconds();
  setOwner( nullptr );

  taskMgr.queueTask( World::makeFadeBNpcTask( 10000, getAsBNpc() ) );
  taskMgr.queueTask( World::makeRemoveBNpcTask( 12000, getAsBNpc() ) );

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( m_level );

  for( const auto& pHateEntry : m_hateList )
  {
    // TODO: handle drops 
    auto pPlayer = pHateEntry->m_pChara->getAsPlayer();
    if( pPlayer )
    {
      playerMgr.onMobKill( *pPlayer, *this );
      pPlayer->gainExp( paramGrowthInfo->data().BaseExp );
    }
  }

  hateListClear();
}

uint32_t BNpc::getTimeOfDeath() const
{
  return m_timeOfDeath;
}

void BNpc::setTimeOfDeath( uint32_t timeOfDeath )
{
  m_timeOfDeath = timeOfDeath;
}

void BNpc::checkAggro()
{
  // passive mobs should ignore players unless aggro'd
  if( m_aggressionMode == 1 )
    return;

  CharaPtr pClosestChara = getClosestChara();

  if( pClosestChara && pClosestChara->isAlive() && ( getEnemyType() != 0 && pClosestChara->isPlayer() ) )
  {

    // will use this range if chara level is lower than bnpc, otherwise diminishing equation applies
    float range = 14.f;

    if( pClosestChara->getLevel() > m_level )
    {
      auto levelDiff = std::abs( pClosestChara->getLevel() - this->getLevel() );

      if( levelDiff >= 10 )
        range = 0.f;
      else
        range = std::max< float >( 0.f, range - std::pow( 1.53f, static_cast< float >( levelDiff ) * 0.6f ) );
    }

    auto distance = Common::Util::distance( getPos(), pClosestChara->getPos() );

    if( distance < range )
    {
      aggro( pClosestChara );
    }
  }
  else if( pClosestChara && pClosestChara->isAlive() && ( getEnemyType() == 0 && pClosestChara->isBattleNpc() ) )
  {
    if( getBNpcType() == Common::BNpcType::Friendly )
    {
      if( pClosestChara->getAsBNpc()->getBNpcType() == Common::BNpcType::Friendly )
        return;
    }

    if( getEnemyType() == 0 && pClosestChara->getAsBNpc()->getEnemyType() == 0 )
      return;

    // will use this range if chara level is lower than bnpc, otherwise diminishing equation applies
    float range = 14.f;

    if( pClosestChara->getLevel() > m_level )
    {
      auto levelDiff = std::abs( pClosestChara->getLevel() - this->getLevel() );

      if( levelDiff >= 10 )
        range = 0.f;
      else
        range = std::max< float >( 0.f, range - std::pow( 1.53f, static_cast< float >( levelDiff ) * 0.6f ) );
    }

    auto distance = Common::Util::distance( getPos(), pClosestChara->getPos() );

    if( distance < range )
    {
      aggro( pClosestChara );
    }
  }
}

void BNpc::setOwner( const CharaPtr& m_pChara )
{
  m_pOwner = m_pChara;
  auto targetId = static_cast< uint32_t >( INVALID_GAME_OBJECT_ID );
  if( m_pChara != nullptr )
    targetId = m_pChara->getId();

  auto setOwnerPacket = makeZonePacket< FFXIVIpcFirstAttack >( getId() );
  setOwnerPacket->data().Type = 0x01;
  setOwnerPacket->data().Id = targetId;
  server().queueForPlayers( getInRangePlayerIds(), setOwnerPacket );

  if( m_pChara && m_pChara->isPlayer() )
    Network::Util::Packet::sendActorControl( *m_pChara->getAsPlayer(), getId(), SetHateLetter, 1, getId(), 0 );

}

void BNpc::setLevelId( uint32_t levelId )
{
  m_levelId = levelId;
}

uint32_t BNpc::getLevelId() const
{
  return m_levelId;
}

bool BNpc::hasFlag( uint32_t flag ) const
{
  return m_flags & flag;
}

void BNpc::setFlag( uint32_t flag )
{
  m_flags |= flag;
}

void BNpc::clearFlags()
{
  m_flags = 0;
}

void BNpc::autoAttack( CharaPtr pTarget )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );
  auto& actionMgr = Common::Service< World::Manager::ActionMgr >::ref();
  auto& exdData = Common::Service< Data::ExdData >::ref();

  uint64_t tick = Common::Util::getTimeMs();

  // todo: this needs to use the auto attack delay for the equipped weapon
  if( ( tick - m_lastAttack ) > 2500 )
  {
    pTarget->onActionHostile( getAsChara() );
    m_lastAttack = tick;
    srand( static_cast< uint32_t >( tick ) );
    actionMgr.handleTargetedAction( *this, 7, pTarget->getId(), 0 );
  }
}

void BNpc::calculateStats()
{
  auto level = getLevel();
  auto job = static_cast< uint8_t >( getClass() );

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto classInfo = exdData.getRow< Excel::ClassJob >( job );
  auto paramGrowthInfo = exdData.getRow< Excel::ParamGrow >( level );

  float base = Math::CalcStats::calculateBaseStat( *this );

  auto str = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().STR ) / 100 ) );
  auto dex = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().DEX ) / 100 ) );
  auto vit = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().VIT ) / 100 ) );
  auto inte = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().INT_ ) / 100 ) );
  auto mnd = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().MND ) / 100 ) );
  auto pie = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->data().PIE ) / 100 ) );

  setStatValue( BaseParam::Strength, str );
  setStatValue( BaseParam::Dexterity, dex );
  setStatValue( BaseParam::Vitality, vit );
  setStatValue( BaseParam::Intelligence, inte );
  setStatValue( BaseParam::Mind, mnd );
  setStatValue( BaseParam::Piety, pie );

  auto determination = static_cast< uint32_t >( base );
  auto skillSpeed = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );
  auto spellSpeed = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );
  auto accuracy = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );
  auto critHitRate = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );

  setStatValue( BaseParam::Determination, determination );
  setStatValue( BaseParam::SkillSpeed, skillSpeed );
  setStatValue( BaseParam::SpellSpeed, spellSpeed );
  setStatValue( BaseParam::CriticalHit, critHitRate );

  setStatValue( BaseParam::AttackPower, str );
  setStatValue( BaseParam::AttackMagicPotency, inte );
  setStatValue( BaseParam::HealingMagicPotency, mnd );

}

uint32_t BNpc::getRank() const
{
  return m_rank;
}

uint32_t BNpc::getBoundInstanceId() const
{
  return m_boundInstanceId;
}

BNpcType BNpc::getBNpcType() const
{
  return m_bnpcType;
}

uint32_t BNpc::getLayoutId() const
{
  return m_layoutId;
}

void BNpc::init()
{
  m_maxHp = Math::CalcStats::calculateMaxHp( *getAsChara() );
  m_hp = m_maxHp;

  m_lastRoamTargetReachedTime = Common::Util::getTimeSeconds();

  //setup a test gambit
  auto testGambitRule = AI::make_GambitRule( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 88, 0 ), 5000 );
  auto testGambitRule1 = AI::make_GambitRule( AI::make_HPSelfPctLessThanTargetCondition( 50 ), Action::make_Action( getAsChara(), 120, 0 ), 5000 );
/*
  auto gambitPack = AI::make_GambitRuleSetPack();
  gambitPack->addRule( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 88, 0 ), 5000 );
  gambitPack->addRule( AI::make_HPSelfPctLessThanTargetCondition( 50 ), Action::make_Action( getAsChara(), 120, 0 ), 10000 );
  m_pGambitPack = gambitPack;
*/

  auto gambitPack = AI::make_GambitTimeLinePack( -1 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 88, 0 ), 2 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 89, 0 ), 4 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 90, 0 ), 6 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 91, 0 ), 8 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 92, 0 ), 10 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 81, 0 ), 12 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 82, 0 ), 14 );
  m_pGambitPack = gambitPack;

  using namespace AI::Fsm;
  m_fsm = make_StateMachine();
  auto stateIdle = make_StateIdle();
  auto stateCombat = make_StateCombat();
  auto stateDead = make_StateDead();
  if( !hasFlag( Immobile ) )
  {
    auto stateRoam = make_StateRoam();
    stateIdle->addTransition( stateRoam, make_RoamNextTimeReachedCondition() );
    stateRoam->addTransition( stateIdle, make_RoamTargetReachedCondition() );
    stateRoam->addTransition( stateCombat, make_HateListHasEntriesCondition() );
    stateRoam->addTransition( stateDead, make_IsDeadCondition() );
    m_fsm->addState( stateRoam );
  }
  stateIdle->addTransition( stateCombat, make_HateListHasEntriesCondition() );
  stateCombat->addTransition( stateIdle, make_HateListEmptyCondition() );
  stateIdle->addTransition( stateDead, make_IsDeadCondition() );
  stateCombat->addTransition( stateDead, make_IsDeadCondition() );
  m_fsm->addState( stateIdle );
  if( !hasFlag( NoDeaggro ) )
  {
    auto stateRetreat = make_StateRetreat();
    stateCombat->addTransition( stateRetreat, make_SpawnPointDistanceGtMaxDistanceCondition() );
    stateRetreat->addTransition( stateIdle, make_RoamTargetReachedCondition() );
  }
  m_fsm->setCurrentState( stateIdle );
}

void BNpc::processGambits( uint64_t tickCount )
{
  m_tp = 1000;
  m_pGambitPack->update( *this, tickCount );
}

uint32_t BNpc::getLastRoamTargetReachedTime() const
{
  return m_lastRoamTargetReachedTime;
}

void BNpc::setLastRoamTargetReachedTime( uint32_t time )
{
  m_lastRoamTargetReachedTime = time;
}

std::shared_ptr< Common::BNPCInstanceObject > BNpc::getInstanceObjectInfo() const
{
  return m_pInfo;
}

void BNpc::setRoamTargetReached( bool reached )
{
  m_roamTargetReached = reached;
}

bool BNpc::isRoamTargetReached() const
{
  return m_roamTargetReached;
}

void BNpc::setRoamTargetPos( const FFXIVARR_POSITION3& targetPos )
{
  m_roamPos = targetPos;
}

const Common::FFXIVARR_POSITION3& BNpc::getRoamTargetPos() const
{
  return m_roamPos;
}

const Common::FFXIVARR_POSITION3& BNpc::getSpawnPos() const
{
  return m_spawnPos;
}