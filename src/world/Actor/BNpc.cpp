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
#include <Random/RNGMgr.h>
#include <Manager/InventoryMgr.h>
#include <Manager/LootTableMgr.h>
#include <Manager/PlayerMgr.h>
#include <Manager/TaskMgr.h>
#include <Manager/MgrUtil.h>
#include <Manager/ActionMgr.h>
#include <Script/ScriptMgr.h>
#include <Task/RemoveBNpcTask.h>
#include <Task/FadeBNpcTask.h>
#include <Task/DelayedEmnityTask.h>
#include <Task/ActionIntegrityTask.h>
#include <Task/LootBNpcTask.h>
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
#include <AI/Fsm/StateFollowPath.h>
#include <AI/Fsm/StateResumePath.h>
#include <AI/TargetHelper.h>

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

BNpc::BNpc( uint32_t id, std::shared_ptr< Common::BNpcCacheEntry > pInfo, const Territory& zone ) : Npc(
  ObjKind::BattleNpc )
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
  m_lastPos = m_pos;
  m_rot = pInfo->rotation;
  m_level = pInfo->Level <= 0 ? 1 : pInfo->Level;
  m_invincibilityType = InvincibilityNone;
  m_currentStance = Common::Stance::Passive;
  m_boundInstanceId = pInfo->BoundInstanceID;
  m_flags = 0;
  m_rank = pInfo->BNPCRankId;

  m_senseData = pInfo->baseData;

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

  if( pInfo->WanderingRange == 0 || pInfo->BoundInstanceID != 0 )
    setFlag( NoRoam | Immobile );

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

  m_bnpcType = BNpcType::Enemy;

  memset( m_customize, 0, sizeof( m_customize ) );
  memset( m_modelEquip, 0, sizeof( m_modelEquip ) );


  m_radius = bNpcBaseData->data().Scale;
  m_baseScale = bNpcBaseData->data().Scale;
  if( bNpcBaseData->data().Customize != 0 )
  {
    auto bnpcCustom = exdData.getRow< Excel::BNpcCustomize >( bNpcBaseData->data().Customize );
    if( bnpcCustom )
    {
      memcpy( m_customize, reinterpret_cast< char * >( &bnpcCustom->data() ), sizeof( m_customize ) );
    }
  }

  if( bNpcBaseData->data().Equipment != 0 )
  {
    auto bnpcEquip = exdData.getRow< Excel::NpcEquip >( bNpcBaseData->data().Equipment );
    if( bnpcEquip )
    {
      m_weaponMain = bnpcEquip->data().WeaponModel;
      m_weaponSub = bnpcEquip->data().SubWeaponModel;
      memcpy( m_modelEquip, reinterpret_cast< char * >( bnpcEquip->data().Equip ), sizeof( m_modelEquip ) );
    }
  }

  auto modelChara = exdData.getRow< Excel::ModelChara >( bNpcBaseData->data().Model );
  if( modelChara )
  {
    auto modelSkeleton = exdData.getRow< Excel::ModelSkeleton >( modelChara->data().SkeletonId );
    if( modelSkeleton )
    {
      m_radius = modelSkeleton->data().Radius * m_baseScale;
      m_walkSpeed = modelSkeleton->data().WalkSpeed;
      m_runSpeed = modelSkeleton->data().RunSpeed;

      //m_autoAttackAnimation = modelSkeleton->data().AutoAttackType;

    }
  }

  // todo: is this actually good?
  m_naviTargetReachedDistance = m_radius;

  calculateStats();

  //if( m_bnpcType == BNpcType::Friendly )
  //  m_maxHp *= 5;
}

BNpc::BNpc( uint32_t id, std::shared_ptr< Common::BNpcCacheEntry > pInfo, const Territory& zone, uint32_t hp,
            Common::BNpcType type ) :
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
  m_lastPos = m_pos;
  m_rot = pInfo->rotation;
  m_level = pInfo->Level <= 0 ? 1 : pInfo->Level;
  m_invincibilityType = InvincibilityNone;
  m_currentStance = Common::Stance::Passive;
  m_boundInstanceId = pInfo->BoundInstanceID;
  m_flags = 0;
  m_rank = pInfo->BNPCRankId;

  m_senseData = pInfo->baseData;

  m_territoryTypeId = zone.getTerritoryTypeId();
  m_territoryId = zone.getGuId();

  if( pInfo->WanderingRange == 0 || pInfo->BoundInstanceID != 0 )
    setFlag( Immobile | NoRoam );

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
      memcpy( m_customize, reinterpret_cast< char * >( &bnpcCustom->data() ), sizeof( m_customize ) );
    }
  }

  if( bNpcBaseData->data().Equipment != 0 )
  {
    auto bnpcEquip = exdData.getRow< Excel::NpcEquip >( bNpcBaseData->data().Equipment );
    if( bnpcEquip )
    {
      m_weaponMain = bnpcEquip->data().WeaponModel;
      m_weaponSub = bnpcEquip->data().SubWeaponModel;
      memcpy( m_modelEquip, reinterpret_cast< char * >( bnpcEquip->data().Equip ), sizeof( m_modelEquip ) );
    }
  }

  auto modelChara = exdData.getRow< Excel::ModelChara >( bNpcBaseData->data().Model );
  if( modelChara )
  {
    auto modelSkeleton = exdData.getRow< Excel::ModelSkeleton >( modelChara->data().SkeletonId );
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

const BNpcBaseData& BNpc::getSenseData() const
{
  return m_senseData;
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

  auto pos1 = pNaviProvider->getAgentPos( getAgentId() );
  auto distance = Common::Util::distance( pos1, pos );

  if( distance < getNaviTargetReachedDistance() )
  {
    // Reached destination
    face( pos );
    setPos( pos1 );
    auto state = getState();
    bool isRunning = state == Entity::BNpcState::Retreat || state == Entity::BNpcState::Combat;
    auto newAgentId = pNaviProvider->updateAgentPosition( getAgentId(), pos1, getRadius(), isRunning ? getRunSpeed() : getWalkSpeed() );
    setAgentId( newAgentId );
    return true;
  }

  pZone->updateActorPosition( *this );
  face( pos );
  if( distance > 2.0f )
    face( { ( pos.x - pos1.x ) + pos.x, 1.0f, ( pos.z - pos1.z ) + pos.z } );
  else
    face( pos );
  setPos( pos1 );
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

  auto pos1 = pNaviProvider->getAgentPos( getAgentId() );
  auto distance = Common::Util::distance( pos1, targetChara.getPos() );

  if( distance <= ( getNaviTargetReachedDistance() + targetChara.getRadius() ) )
  {
    // Reached destination
    face( targetChara.getPos() );
    setPos( pos1 );
    pNaviProvider->resetMoveTarget( getAgentId() );
    auto state = getState();
    bool isRunning = state == Entity::BNpcState::Retreat || state == Entity::BNpcState::Combat;
    auto newAgentId = pNaviProvider->updateAgentPosition( getAgentId(), pos1, getRadius(), isRunning ? getRunSpeed() : getWalkSpeed() );
    setAgentId( newAgentId );
    return true;
  }

  pZone->updateActorPosition( *this );
  if( distance > 2.0f )
    face( { ( pos1.x - getPos().x ) + pos1.x, 1.0f, ( pos1.z - getPos().z ) + pos1.z } );
  else
    face( targetChara.getPos() );
  setPos( pos1 );
  return false;
}

float mapSpeedToRange(float speed, float minSpeed = 0.0f, float maxSpeed = 18.0f) {
  // Clamp the speed to valid range
  speed = std::max(minSpeed, std::min(maxSpeed, speed));

  // Map from [minSpeed, maxSpeed] to [-π, π]
  float normalized = (speed - minSpeed) / (maxSpeed - minSpeed); // [0, 1]
  return (normalized * 2.0f - 1.0f) * 3.1415927f; // [-π, π]
}


void BNpc::sendPositionUpdate()
{
  uint8_t animationType = 2;

  if( m_state == BNpcState::Combat || m_state == BNpcState::Retreat )
    animationType = 0;

  if( m_lastPos.x != m_pos.x || m_lastPos.y != m_pos.y || m_lastPos.z != m_lastPos.z || m_lastRot != m_rot )
  {
    int speedI = 0x5a/4;
    float s = (((static_cast< float >( speedI ) * 2.4639943) * 0.01f ) - 3.1415927f);

    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

    auto pNaviProvider = pZone->getNaviProvider();
    // not 100% certain of this range, but with limited samples i tested, it looked somewhat correct
    float s1 = mapSpeedToRange( pNaviProvider->getAgentSpeed( getAgentId() ), 0, 25.5f );
    //Logger::debug( "speed: {} {} {}", s, s1, static_cast<uint8_t>((s1 + 3.1415927f) / (2.4639943f * 0.01f)));
;

    auto movePacket = std::make_shared< MoveActorPacket >( *getAsChara(), 0x3A, animationType, 0, static_cast<uint8_t>((s1 + 3.1415927f) / (2.4639943f * 0.01f)) );
    server().queueForPlayers( getInRangePlayerIds(), movePacket );
  }
  m_lastPos = m_pos;
  m_lastRot = m_rot;
}

const std::set< std::shared_ptr< HateListEntry > >& BNpc::getHateList() const
{
  return m_hateList;
}

void BNpc::hateListClear()
{
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), ToggleWeapon, 0, 1, 1 );
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), SetBattle );

  for( auto& listEntry : m_hateList )
  {
    if( isInRangeSet( listEntry->m_pChara ) )
    {
      if( listEntry->m_pChara->isPlayer() )
        notifyPlayerDeaggro( listEntry->m_pChara );
    }
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
  if( hateAmount > 0 )
  {
    auto hateEntry = std::make_shared< HateListEntry >();
    hateEntry->m_hateAmount = hateAmount;
    hateEntry->m_pChara = pChara;

    m_hateList.insert( hateEntry );
    if( pChara->isPlayer() )
    {
      auto pPlayer = pChara->getAsPlayer();
      pPlayer->hateListAdd( *this );
      World::Manager::PlayerMgr::sendDebug( *pChara->getAsPlayer(), "New Aggro: {}, Aggro gained: {}", hateAmount,
                                            hateAmount );
    }
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
      auto currentHate = listEntry->m_hateAmount;
      if( hateAmount >= 0 || currentHate > abs( hateAmount ) )
        listEntry->m_hateAmount += hateAmount;
      else
        listEntry->m_hateAmount = 0;
      hasEntry = true;

      if( auto player = pChara->getAsPlayer() )
      {
        player->hateListLetterUpdate( *this );
        World::Manager::PlayerMgr::sendDebug( *player, "New Aggro: {}, Aggro gained: {}", listEntry->m_hateAmount,
                                              hateAmount );
      }
      break;
    }
  }

  if( !hasEntry )
  {
    hateListAdd( pChara, hateAmount );
  }

  hateListUpdatePlayers();
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

std::vector< CharaPtr > BNpc::getHateList()
{
  std::vector< CharaPtr > hateList = {};

  for( auto& entry : m_hateList )
  {
    hateList.push_back( entry->m_pChara );
  }

  return hateList;
}

void BNpc::hateListUpdatePlayers()
{
  for( const auto& listEntry : m_hateList )
  {
    // update entire hatelist for all players who are on aggro with this bnpc
    if( listEntry->m_pChara->isPlayer() )
    {
      auto pPlayer = listEntry->m_pChara->getAsPlayer();
      Network::Util::Packet::sendHateList( *pPlayer );
    }
  }
}

void BNpc::aggro( const Sapphire::Entity::CharaPtr& pChara )
{
  auto& pRNGMgr = Common::Service< Common::Random::RNGMgr >::ref();
  auto variation = static_cast< uint32_t >( pRNGMgr.getRandGenerator< float >( 500, 1000 ).next() );


  if( !hateListHasActor( pChara ) )
  {
    hateListAdd( pChara, 1000 );
    if( getTargetId() == pChara->getId() )
    {
      updateAggroTarget();
      hateListUpdatePlayers();
    }
    if( m_pOwner == pChara )
    {
      setOwner( hateListGetHighest() );
    }
  }

  if( m_pGambitPack && m_pGambitPack->getAsTimeLine() )
  {
    m_pGambitPack->getAsTimeLine()->start();
  }

  m_lastAttack = Common::Util::getTimeMs() + variation;

  setStance( Stance::Active );
  m_state = BNpcState::Combat;

  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), SetBattle, 1 );

  changeTarget( pChara->getId() );
}

void BNpc::deaggro( const CharaPtr& pChara )
{
  if( hateListHasActor( pChara ) )
  {
    hateListRemove( pChara );
    if( getTargetId() == pChara->getId() )
    {
      updateAggroTarget();
      hateListUpdatePlayers();
    }
    if( m_pOwner == pChara )
    {
      setOwner( hateListGetHighest() );
    }
  }

  if( pChara->isPlayer() )
    notifyPlayerDeaggro( pChara );
}

void BNpc::notifyPlayerDeaggro( const CharaPtr& pChara )
{
  if( m_hateList.empty() )
  {
    Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), ToggleWeapon, 0, 1, 1 );
    Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), SetBattle );
  }

  PlayerPtr tmpPlayer = pChara->getAsPlayer();
  tmpPlayer->onMobDeaggro( *this );

  if( getTriggerOwnerId() == pChara->getId() )
  {
    auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
    auto bnpc = *getAsBNpc();
    scriptMgr.onTriggerOwnerDeaggro( *tmpPlayer, bnpc );
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

  checkAggro();
  // removed check for now, replaced by position check to last position
  //if( m_dirtyFlag & DirtyFlag::Position )
  sendPositionUpdate();

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

void BNpc::onActionHostile( CharaPtr pSource, int32_t aggro )
{
  hateListUpdate( pSource, aggro );

  if( getCanSwapTarget() ) // todo: only call on global server tick
    updateAggroTarget();

  if( !m_pOwner )
    setOwner( pSource );
}

void BNpc::onDeath()
{
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& taskMgr = Common::Service< World::Manager::TaskMgr >::ref();
  auto& lootTableMgr = Common::Service< World::Manager::LootTableMgr >::ref();
  auto& inventoryMgr = Common::Service< World::Manager::InventoryMgr >::ref();

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
    auto pPlayer = pHateEntry->m_pChara->getAsPlayer();
    if( pPlayer )
    {
      // todo: get this outta here!
      taskMgr.queueTask( makeLootBNpcTask( *pPlayer, "testTable", 2000 ) );

      playerMgr.onMobKill( *pPlayer, *this );
      playerMgr.onGainExp( *pPlayer, paramGrowthInfo->data().BaseExp );
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

  if( !getHateList().empty() )
  {
    return;
  }

  auto calculateAdjustedRange = []( float baseRange, int targetLevel, int sourceLevel ) -> float
  {
    auto levelDiff = std::abs( targetLevel - sourceLevel );

    if( levelDiff >= 10 )
      return 0.0f;
    else
      return std::max< float >( 0.0f, baseRange - std::pow( 1.53f, static_cast< float >( levelDiff ) * 0.6f ) );
  };


  bool hasAggro = false;
  auto pCharaSelf = getAsChara();
  static auto pBattalionFilter = std::make_shared< World::AI::OwnBattalionFilter >();

  for( uint32_t i = 0; i < 2; ++i )
  {
    float senseRange = m_senseData.SenseRange[ i ];

    switch( m_senseData.Sense[ i ] )
    {
      case SenseType::HEARING:
      {
        auto actors = getInRangeActors();
        for( const auto& actor : actors )
        {
          if( !actor->isChara() )
            continue;

          auto pCharaTarget = actor->getAsChara();

          // if this chara is in our battalion, dont aggro
          if( pBattalionFilter->isApplicable( pCharaSelf, pCharaTarget ) )
            continue;

          if( auto pBNpc = pCharaTarget->getAsBNpc() )
            if( pBNpc->hateListGetHighest() == nullptr &&
                pBNpc->getAggressionMode() == 1 )
              continue;


          if( auto pPlayer = actor->getAsPlayer() )
            if( !pPlayer->isRunning() || !pPlayer->isAlive() )
              continue;

          // diminish sense range if required.
          senseRange = calculateAdjustedRange( senseRange, pCharaTarget->getLevel(), getLevel() );
          float distance = Common::Util::distance( getPos(), actor->getPos() );
          if( distance < senseRange )
          {
            aggro( actor->getAsChara() );
            hasAggro = true;
            break;
          }
        }
        break;
      }

      case SenseType::VISION:
      {
        auto actors = getInRangeActors();
        for( const auto& actor : actors )
        {
          if( !actor->isChara() )
            continue;

          auto pCharaTarget = actor->getAsChara();

          // if this chara is in our battalion, dont aggro
          if( pBattalionFilter->isApplicable( pCharaSelf, pCharaTarget ) )
            continue;


          if( auto pBNpc = pCharaTarget->getAsBNpc() )
            if( pBNpc->hateListGetHighest() == nullptr &&
                pBNpc->getAggressionMode() == 1 )
              continue;

          if( !pCharaTarget->isAlive() )
            continue;

          // Check if player is within sense range first (distance check)
          float distance = Common::Util::distance( getPos(), actor->getPos() );

          // Diminish sense range if required
          float adjustedSenseRange = calculateAdjustedRange( senseRange, pCharaTarget->getLevel(), getLevel() );

          if( distance > adjustedSenseRange )
            continue; // Too far away

          // Vision cone check
          // Calculate vector from BNPC to player
          const auto& bnpcPos = getPos();
          const auto& playerPos = actor->getPos();

          float deltaX = playerPos.x - bnpcPos.x;
          float deltaZ = playerPos.z - bnpcPos.z;

          // Calculate angle from BNPC to player
          float angleToPlayer = atan2( deltaX, deltaZ );

          // Get BNPC's facing direction (rotation)
          float bnpcRotation = getRot();

          // Calculate the difference between BNPC rotation and angle to player
          float angleDiff = angleToPlayer - bnpcRotation;

          // Normalize angle difference to [-PI, PI]
          while( angleDiff > PI ) angleDiff -= 2.0f * PI;
          while( angleDiff < -PI ) angleDiff += 2.0f * PI;

          // Check if player is within the 75-degree vision cone (37.5 degrees on each side)
          float halfConeAngle = ( 75.0f * PI / 180.0f ) / 2.0f;

          if( abs( angleDiff ) <= halfConeAngle )
          {
            // Player is within vision cone, check for line of sight if needed
            // TODO: Add line of sight check using navmesh/collision mesh raycast if required

            aggro( actor->getAsChara() );
            hasAggro = true;
            break;
          }
        }
        break;
      }


      case SenseType::PRESENCE:
      {
        auto actors = getInRangeActors();
        for( const auto& actor : actors )
        {
          if( !actor->isChara() )
            continue;

          auto pCharaTarget = actor->getAsChara();

          // if this chara is in our battalion, dont aggro
          if( pBattalionFilter->isApplicable( pCharaSelf, pCharaTarget ) )
            continue;

          if( auto pBNpc = pCharaTarget->getAsBNpc() )
            if( pBNpc->hateListGetHighest() == nullptr &&
                pBNpc->getAggressionMode() == 1 )
              continue;

          if( !pCharaTarget->isAlive() )
            continue;

          float distance = Common::Util::distance( getPos(), actor->getPos() );
          if( distance < senseRange )
          {
            aggro( actor->getAsChara() );
            hasAggro = true;
            break;
          }
        }

        break;
      }

      default:
        break;
    }
    if( hasAggro )
      break;
  }
/*
  //legacy code
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
  }*/
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


void BNpc::resetFlags( uint32_t flags )
{
  uint32_t oldFlags = m_flags;
  m_flags = 0;
  m_flags |= flags;

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );


  if( pZone && getAgentId() != -1 && ( oldFlags & Entity::Immobile ) != Entity::Immobile &&
      ( m_flags & Entity::Immobile ) == Entity::Immobile )
  {
    Logger::debug( "{} {} Pathing deactivated", m_id, getAgentId() );
    auto pNaviProvider = pZone->getNaviProvider();
    pNaviProvider->removeAgent( getAgentId() );
    setPathingActive( false );
  }
  else if( pZone && ( oldFlags & Entity::Immobile ) == Entity::Immobile &&
           ( m_flags & Entity::Immobile ) != Entity::Immobile )
  {
    Logger::debug( "{} Pathing activated", m_id );
    auto pNaviProvider = pZone->getNaviProvider();
    if( getAgentId() != -1 )
      pNaviProvider->removeAgent( getAgentId() );
    auto agentId = pNaviProvider->addAgent( getPos(), getRadius() );
    setAgentId( agentId );
    setPathingActive( true );
  }
}


void BNpc::setFlag( uint32_t flag )
{
  uint32_t oldFlags = m_flags;
  m_flags = 0;
  m_flags |= flag;

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );


  if( pZone && getAgentId() != -1 && ( oldFlags & Entity::Immobile ) != Entity::Immobile &&
      ( m_flags & Entity::Immobile ) == Entity::Immobile )
  {
    Logger::debug( "{} {} Pathing deactivated", m_id, getAgentId() );
    auto pNaviProvider = pZone->getNaviProvider();
    pNaviProvider->removeAgent( getAgentId() );
    setPathingActive( false );
  }
  else if( pZone && ( oldFlags & Entity::Immobile ) == Entity::Immobile &&
           ( m_flags & Entity::Immobile ) != Entity::Immobile )
  {
    Logger::debug( "{} Pathing activated", m_id );
    auto pNaviProvider = pZone->getNaviProvider();
    if( getAgentId() != -1 )
      pNaviProvider->removeAgent( getAgentId() );
    auto agentId = pNaviProvider->addAgent( getPos(), getRadius() );
    setAgentId( agentId );
    setPathingActive( true );
  }
}

void BNpc::removeFlag( uint32_t flag )
{
  m_flags &= ~flag;
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

void BNpc::updateAggroTarget()
{
  auto highestAggro = hateListGetHighest();
  if( highestAggro && getTargetId() != highestAggro->getId() )
  {
    aggro( highestAggro );
  }
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

  /*
  //setup a test gambit
  auto testGambitRule = AI::make_GambitRule( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 88, 0 ), 5000 );
  auto testGambitRule1 = AI::make_GambitRule( AI::make_HPSelfPctLessThanTargetCondition( 50 ), Action::make_Action( getAsChara(), 120, 0 ), 5000 );

  auto gambitPack = AI::make_GambitRuleSetPack();
  gambitPack->addRule( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 88, 0 ), 5000 );
  gambitPack->addRule( AI::make_HPSelfPctLessThanTargetCondition( 50 ), Action::make_Action( getAsChara(), 120, 0 ), 10000 );
  m_pGambitPack = gambitPack;


  auto gambitPack = AI::make_GambitTimeLinePack( -1 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 88, 0 ), 2 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 89, 0 ), 4 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 90, 0 ), 6 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 91, 0 ), 8 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 92, 0 ), 10 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 81, 0 ), 12 );
  gambitPack->addTimeLine( AI::make_TopHateTargetCondition(), Action::make_Action( getAsChara(), 82, 0 ), 14 );
  m_pGambitPack = gambitPack;
  */
  initFsm();
}

void BNpc::initFsm()
{
  using namespace AI::Fsm;
  m_fsm = make_StateMachine();
  auto stateIdle = make_StateIdle();
  auto stateCombat = make_StateCombat();
  auto stateDead = make_StateDead();

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  if( m_pInfo->ServerPathId != 0 && pZone && pZone->getServerPath( m_pInfo->ServerPathId ) )
  {
    auto statePath = make_StateFollowPath();
    auto stateResumePath = make_StateResumePath();
    statePath->addTransition( stateCombat, make_HateListHasEntriesCondition() );
    statePath->addTransition( stateDead, make_IsDeadCondition() );

    stateCombat->addTransition( stateDead, make_IsDeadCondition() );
    stateCombat->addTransition( stateResumePath, make_HateListEmptyCondition() );
    stateResumePath->addTransition( statePath, make_RoamTargetReachedCondition() );

    m_fsm->addState( statePath );

    m_fsm->setCurrentState( statePath );
  }
  else
  {
    if( !hasFlag( Immobile ) && !hasFlag( NoRoam ) )
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
}

void BNpc::processGambits( uint64_t tickCount )
{
  m_tp = 1000;
  if( m_pGambitPack )
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

std::shared_ptr< Common::BNPCData > BNpc::getInstanceObjectInfo() const
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

bool BNpc::getCanSwapTarget()
{
  return m_canSwapTarget;
}

void BNpc::setCanSwapTarget( bool value )
{
  m_canSwapTarget = value;

  if( m_canSwapTarget ) // todo: only call on global server tick
  {
    updateAggroTarget();
  }
}

void BNpc::setPos( float x, float y, float z, bool broadcastUpdate )
{
  Chara::setPos( x, y, z, broadcastUpdate );
}

void BNpc::setPos( const FFXIVARR_POSITION3& pos, bool broadcastUpdate )
{
  setPos( pos.x, pos.y, pos.z, broadcastUpdate );
}
