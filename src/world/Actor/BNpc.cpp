#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>
#include <utility>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/EffectPacket.h>
#include <Network/PacketWrappers/EffectPacket1.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Logging/Logger.h>

#include "Forwards.h"
#include "Action/Action.h"

#include "Territory/Territory.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/NpcSpawnPacket.h"
#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Navi/NaviProvider.h"

#include "Math/CalcBattle.h"
#include "Math/CalcStats.h"

#include "StatusEffect/StatusEffect.h"

#include "WorldServer.h"
#include "Session.h"
#include "Chara.h"
#include "Player.h"
#include "BNpc.h"

#include "Common.h"

#include <Manager/TerritoryMgr.h>
#include <Manager/NaviMgr.h>
#include <Manager/TerritoryMgr.h>
#include <Manager/RNGMgr.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Entity::BNpc::BNpc() :
  Npc( ObjKind::BattleNpc )
{
}

Sapphire::Entity::BNpc::BNpc( uint32_t id, std::shared_ptr< Common::BNPCInstanceObject > pInfo, TerritoryPtr pZone ) :
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

  if( pInfo->WanderingRange == 0 || pInfo->BoundInstanceID != 0 )
    setFlag( Immobile );

  // Striking Dummy
  if( pInfo->NameId == 541 )
    m_invincibilityType = Common::InvincibilityRefill;

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto bNpcBaseData = exdData.getRow< Component::Excel::BNpcBase >( m_bNpcBaseId );
  if( !bNpcBaseData )
  {
    Logger::debug( "BNpcBase#{0} not found in exd data!", m_bNpcBaseId );
    return;
  }

  m_modelChara = bNpcBaseData->data().Model;
  m_enemyType = bNpcBaseData->data().Battalion;

  m_class = ClassJob::Gladiator;

  m_territoryTypeId = pZone->getTerritoryTypeId();
  m_territoryId = pZone->getGuId();

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

  max_hp = m_maxHp;
  max_mp = 200;

  memset( m_customize, 0, sizeof( m_customize ) );
  memset( m_modelEquip, 0, sizeof( m_modelEquip ) );


  m_radius = bNpcBaseData->data().Scale;
  if( bNpcBaseData->data().Customize != 0 )
  {
    auto bnpcCustom = exdData.getRow< Component::Excel::BNpcCustomize >( bNpcBaseData->data().Customize );
    if( bnpcCustom )
    {
      memcpy( m_customize, reinterpret_cast< char* >( &bnpcCustom->data() ), sizeof( m_customize ) );
    }
  }

  if( bNpcBaseData->data().Equipment != 0 )
  {
    auto bnpcEquip = exdData.getRow< Component::Excel::NpcEquip >( bNpcBaseData->data().Equipment );
    if( bnpcEquip )
    {
      m_weaponMain = bnpcEquip->data().WeaponModel;
      m_weaponSub = bnpcEquip->data().SubWeaponModel;
      memcpy( m_modelEquip, reinterpret_cast< char* >( bnpcEquip->data().Equip ), sizeof( m_modelEquip ) );
    }
  }

  auto modelChara = exdData.getRow< Component::Excel::ModelChara >( bNpcBaseData->data().Model );
  if( modelChara )
  {
    auto modelSkeleton = exdData.getRow< Component::Excel::ModelSkeleton >( modelChara->data().SkeletonId );
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

  max_hp = m_maxHp;

}

Sapphire::Entity::BNpc::BNpc( uint32_t id, std::shared_ptr< Common::BNPCInstanceObject > pInfo, TerritoryPtr pZone, uint32_t hp, Common::BNpcType type ) :
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

  m_territoryTypeId = pZone->getTerritoryTypeId();
  m_territoryId = pZone->getGuId();

  if( pInfo->WanderingRange == 0 || pInfo->BoundInstanceID != 0 )
    setFlag( Immobile );

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto bNpcBaseData = exdData.getRow< Component::Excel::BNpcBase >( m_bNpcBaseId );
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

  max_hp = hp;
  max_mp = 200;

  m_bnpcType = type;

  memset( m_customize, 0, sizeof( m_customize ) );
  memset( m_modelEquip, 0, sizeof( m_modelEquip ) );


  m_radius = bNpcBaseData->data().Scale;
  if( bNpcBaseData->data().Customize != 0 )
  {
    auto bnpcCustom = exdData.getRow< Component::Excel::BNpcCustomize >( bNpcBaseData->data().Customize );
    if( bnpcCustom )
    {
      memcpy( m_customize, reinterpret_cast< char* >( &bnpcCustom->data() ), sizeof( m_customize ) );
    }
  }

  if( bNpcBaseData->data().Equipment != 0 )
  {
    auto bnpcEquip = exdData.getRow< Component::Excel::NpcEquip >( bNpcBaseData->data().Equipment );
    if( bnpcEquip )
    {
      m_weaponMain = bnpcEquip->data().WeaponModel;
      m_weaponSub = bnpcEquip->data().SubWeaponModel;
      memcpy( m_modelEquip, reinterpret_cast< char* >( bnpcEquip->data().Equip ), sizeof( m_modelEquip ) );
    }
  }

  auto modelChara = exdData.getRow< Component::Excel::ModelChara >( bNpcBaseData->data().Model );
  if( modelChara )
  {
    auto modelSkeleton = exdData.getRow< Component::Excel::ModelSkeleton >( modelChara->data().ModelType );
    if( modelSkeleton )
      m_radius *= modelSkeleton->data().Radius;
  }

  // todo: is this actually good?
  m_naviTargetReachedDistance = m_radius;

  calculateStats();
}

Sapphire::Entity::BNpc::~BNpc() = default;

uint8_t Sapphire::Entity::BNpc::getAggressionMode() const
{
  return m_aggressionMode;
}

float Sapphire::Entity::BNpc::getNaviTargetReachedDistance() const
{
  return m_naviTargetReachedDistance;
}

uint8_t Sapphire::Entity::BNpc::getEnemyType() const
{
  return m_enemyType;
}

uint64_t Sapphire::Entity::BNpc::getWeaponMain() const
{
  return m_weaponMain;
}

uint64_t Sapphire::Entity::BNpc::getWeaponSub() const
{
  return m_weaponSub;
}

uint16_t Sapphire::Entity::BNpc::getModelChara() const
{
  return m_modelChara;
}

uint8_t Sapphire::Entity::BNpc::getLevel() const
{
  return m_level;
}

uint32_t Sapphire::Entity::BNpc::getBNpcBaseId() const
{
  return m_bNpcBaseId;
}

uint32_t Sapphire::Entity::BNpc::getBNpcNameId() const
{
  return m_bNpcNameId;
}

void Sapphire::Entity::BNpc::spawn( PlayerPtr pTarget )
{
  m_lastRoamTargetReached = Util::getTimeSeconds();

  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( pTarget->getCharacterId(), std::make_shared< NpcSpawnPacket >( *this, *pTarget ) );
}

void Sapphire::Entity::BNpc::despawn( PlayerPtr pTarget )
{
  pTarget->freePlayerSpawnId( getId() );

  auto& server = Common::Service< World::WorldServer >::ref();

  server.queueForPlayer( pTarget->getCharacterId(), makeActorControlSelf( m_id, WarpStart, 0x04, getId(), 0x01 ) );
}

Sapphire::Entity::BNpcState Sapphire::Entity::BNpc::getState() const
{
  return m_state;
}

void Sapphire::Entity::BNpc::setState( BNpcState state )
{
  m_state = state;
}

bool Sapphire::Entity::BNpc::moveTo( const FFXIVARR_POSITION3& pos )
{
  auto teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  auto pNaviProvider = pZone->getNaviProvider();

  if( !pNaviProvider )
  {
    Logger::error( "No NaviProvider for zone#{0} - {1}", pZone->getGuId(), pZone->getInternalName() );
    return false;
  }

  auto pos1 = pNaviProvider->getMovePos( *this );
  auto distance = Util::distance( pos1, pos );

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

bool Sapphire::Entity::BNpc::moveTo( const Entity::Chara& targetChara )
{

  auto teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  auto pNaviProvider = pZone->getNaviProvider();

  if( !pNaviProvider )
  {
    Logger::error( "No NaviProvider for zone#{0} - {1}", pZone->getGuId(), pZone->getInternalName() );
    return false;
  }

  auto pos1 = pNaviProvider->getMovePos( *this );
  auto distance = Util::distance( pos1, targetChara.getPos() );

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

void Sapphire::Entity::BNpc::sendPositionUpdate()
{
  uint8_t unk1 = 0x3a;
  uint8_t animationType = 2;

  if( m_state == BNpcState::Combat || m_state == BNpcState::Retreat )
    animationType = 0;

  auto movePacket = std::make_shared< MoveActorPacket >( *getAsChara(), 0x3A, animationType, 0, 0x5A / 4 );
  sendToInRangeSet( movePacket );
}

void Sapphire::Entity::BNpc::hateListClear()
{
  auto it = m_hateList.begin();
  for( auto& listEntry : m_hateList )
  {
    if( isInRangeSet( listEntry->m_pChara ) )
      deaggro( listEntry->m_pChara );
  }
  m_hateList.clear();
}

Sapphire::Entity::CharaPtr Sapphire::Entity::BNpc::hateListGetHighest()
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

void Sapphire::Entity::BNpc::hateListAdd( Sapphire::Entity::CharaPtr pChara, int32_t hateAmount )
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

void Sapphire::Entity::BNpc::hateListUpdate( Sapphire::Entity::CharaPtr pChara, int32_t hateAmount )
{
  for( auto listEntry : m_hateList )
  {
    if( listEntry->m_pChara == pChara )
    {
      listEntry->m_hateAmount += static_cast< uint32_t >( hateAmount );
      return;
    }
  }

  auto hateEntry = std::make_shared< HateListEntry >();
  hateEntry->m_hateAmount = static_cast< uint32_t >( hateAmount );
  hateEntry->m_pChara = pChara;
  m_hateList.insert( hateEntry );
}

void Sapphire::Entity::BNpc::hateListRemove( Sapphire::Entity::CharaPtr pChara )
{
  for( auto listEntry : m_hateList )
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

bool Sapphire::Entity::BNpc::hateListHasActor( Sapphire::Entity::CharaPtr pChara )
{
  for( auto& listEntry : m_hateList )
  {
    if( listEntry->m_pChara == pChara )
      return true;
  }
  return false;
}

void Sapphire::Entity::BNpc::aggro( Sapphire::Entity::CharaPtr pChara )
{
  auto& pRNGMgr = Common::Service< World::Manager::RNGMgr >::ref();
  auto variation = static_cast< uint32_t >( pRNGMgr.getRandGenerator< float >( 500, 1000 ).next() );

  m_lastAttack = Util::getTimeMs() + variation;
  hateListUpdate( pChara, 1 );

  setStance( Stance::Active );
  m_state = BNpcState::Combat;

  sendToInRangeSet( makeActorControl( getId(), ActorControlType::SetBattle, 1, 0, 0 ) );

  changeTarget( pChara->getId() );

  if( pChara->isPlayer() )
  {
    PlayerPtr tmpPlayer = pChara->getAsPlayer();
    tmpPlayer->onMobAggro( *getAsBNpc() );
  }

}

void Sapphire::Entity::BNpc::deaggro( Sapphire::Entity::CharaPtr pChara )
{
  if( !hateListHasActor( pChara ) )
    hateListRemove( pChara );

  if( pChara->isPlayer() )
  {
    PlayerPtr tmpPlayer = pChara->getAsPlayer();
    sendToInRangeSet( makeActorControl( getId(), ActorControlType::ToggleWeapon, 0, 1, 1 ) );
    sendToInRangeSet( makeActorControl( getId(), ActorControlType::SetBattle, 0, 0, 0 ) );
    tmpPlayer->onMobDeaggro( *this );
  }
}

void Sapphire::Entity::BNpc::onTick()
{
  Chara::onTick();
  if( m_state == BNpcState::Retreat )
  {
    regainHp();
  }
}

void Sapphire::Entity::BNpc::update( uint64_t tickCount )
{
  auto teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  const uint8_t maxDistanceToOrigin = 40;
  const uint32_t roamTick = 20;

  auto pNaviProvider = pZone->getNaviProvider();

  if( !pNaviProvider )
    return;

  switch( m_state )
  {
    case BNpcState::Dead:
    case BNpcState::JustDied:
      return;

    case BNpcState::Retreat:
    {
      setInvincibilityType( InvincibilityType::InvincibilityIgnoreDamage );

      if( pNaviProvider )
        pNaviProvider->setMoveTarget( *this, m_spawnPos );

      if( moveTo( m_spawnPos ) )
      {
        setInvincibilityType( InvincibilityType::InvincibilityNone );

        // retail doesn't seem to roam straight after retreating
        // todo: perhaps requires more investigation?
        m_lastRoamTargetReached = Util::getTimeSeconds();

        // resetHp
        setHp( getMaxHp() );

        m_state = BNpcState::Idle;
        setOwner( nullptr );
      }
    }
    break;

    case BNpcState::Roaming:
    {

      if( pNaviProvider )
        pNaviProvider->setMoveTarget( *this, m_roamPos );

      if( moveTo( m_roamPos ) )
      {
        m_lastRoamTargetReached = Util::getTimeSeconds();
        m_state = BNpcState::Idle;
      }

      checkAggro();
    }
    break;

    case BNpcState::Idle:
    {
      auto pHatedActor = hateListGetHighest();
      if( pHatedActor )
        aggro( pHatedActor );

      if( pNaviProvider->syncPosToChara( *this ) )
        sendPositionUpdate();

      if( !hasFlag( Immobile ) && ( Util::getTimeSeconds() - m_lastRoamTargetReached > roamTick ) )
      {

        if( !pNaviProvider )
        {
          m_lastRoamTargetReached = Util::getTimeSeconds();
          break;
        }
        if( m_pInfo->WanderingRange != 0 && getEnemyType() != 0 )
        {
          m_roamPos = pNaviProvider->findRandomPositionInCircle( m_spawnPos, m_pInfo->WanderingRange );
        }
        else
        {
          m_roamPos = m_spawnPos;
        }
        m_state = BNpcState::Roaming;
      }

      checkAggro();
    }

    case BNpcState::Combat:
    {
      auto pHatedActor = hateListGetHighest();
      if( !pHatedActor )
        return;

      pNaviProvider->updateAgentParameters( *this );

      auto distanceOrig = Util::distance( getPos().x, getPos().y, getPos().z, m_spawnPos.x, m_spawnPos.y,  m_spawnPos.z );

      if( pHatedActor && !pHatedActor->isAlive() )
      {
        hateListRemove( pHatedActor );
        pHatedActor = hateListGetHighest();
      }

      if( pHatedActor )
      {
        auto distance = Util::distance( getPos().x, getPos().y, getPos().z,
                                        pHatedActor->getPos().x, pHatedActor->getPos().y, pHatedActor->getPos().z );

        if( !hasFlag( NoDeaggro ) && ( ( distanceOrig > maxDistanceToOrigin ) || distance > 30.0f ) )
        {
          hateListClear();
          changeTarget( INVALID_GAME_OBJECT_ID64 );
          setStance( Stance::Passive );
          setOwner( nullptr );
          m_state = BNpcState::Retreat;
          break;
        }

        if( distance > ( getNaviTargetReachedDistance() + pHatedActor->getRadius() ) )
        {
          if( hasFlag( Immobile ) )
            break;

          if( pNaviProvider )
            pNaviProvider->setMoveTarget( *this, pHatedActor->getPos() );

          moveTo( *pHatedActor );
        }

        if( pNaviProvider->syncPosToChara( *this ) )
          sendPositionUpdate();

        if( distance < ( getNaviTargetReachedDistance() + pHatedActor->getRadius() ) )
        {
          if( !hasFlag( TurningDisabled ) && face( pHatedActor->getPos() ) )
            sendPositionUpdate();

          // in combat range. ATTACK!
          autoAttack( pHatedActor );
        }
      }
      else
      {
        changeTarget( INVALID_GAME_OBJECT_ID64 );
        setStance( Stance::Passive );
        //setOwner( nullptr );
        m_state = BNpcState::Retreat;
        pNaviProvider->updateAgentParameters( *this );
      }
    }
  }


  Chara::update( tickCount );
}

void Sapphire::Entity::BNpc::regainHp()
{
  if( this->m_hp < this->getMaxHp() )
  {
    auto addHp = static_cast< uint32_t >( this->getMaxHp() * 0.1f + 1 );

    if( this->m_hp + addHp < this->getMaxHp() )
      this->m_hp += addHp;
    else
      this->m_hp = this->getMaxHp();
  }

  this->sendStatusUpdate();
}

void Sapphire::Entity::BNpc::onActionHostile( Sapphire::Entity::CharaPtr pSource )
{
  if( !hateListGetHighest() )
    aggro( pSource );

  if( !m_pOwner )
    setOwner( pSource );
}

void Sapphire::Entity::BNpc::onDeath()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  setTargetId( INVALID_GAME_OBJECT_ID64 );
  m_currentStance = Stance::Passive;
  m_state = BNpcState::Dead;
  m_timeOfDeath = Util::getTimeSeconds();
  setOwner( nullptr );

  for( auto& pHateEntry : m_hateList )
  {
    // TODO: handle drops 
    auto pPlayer = pHateEntry->m_pChara->getAsPlayer();
    if( pPlayer )
    {
      auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
      playerMgr.onMobKill( *pPlayer, static_cast< uint16_t >( m_bNpcNameId ), getLayoutId() );
    }
  }
  hateListClear();
}

uint32_t Sapphire::Entity::BNpc::getTimeOfDeath() const
{
  return m_timeOfDeath;
}

void Sapphire::Entity::BNpc::setTimeOfDeath( uint32_t timeOfDeath )
{
  m_timeOfDeath = timeOfDeath;
}

void Sapphire::Entity::BNpc::checkAggro()
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
        range = std::max< float >( 0.f, range - std::pow( 1.53f, levelDiff * 0.6f ) );
    }

    auto distance = Util::distance( getPos().x, getPos().y, getPos().z,
                                    pClosestChara->getPos().x,
                                    pClosestChara->getPos().y,
                                    pClosestChara->getPos().z );

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

    // will use this range if chara level is lower than bnpc, otherwise diminishing equation applies
    float range = 14.f;

    if( pClosestChara->getLevel() > m_level )
    {
      auto levelDiff = std::abs( pClosestChara->getLevel() - this->getLevel() );

      if( levelDiff >= 10 )
        range = 0.f;
      else
        range = std::max< float >( 0.f, range - std::pow( 1.53f, levelDiff * 0.6f ) );
    }

    auto distance = Util::distance( getPos().x, getPos().y, getPos().z,
                                    pClosestChara->getPos().x,
                                    pClosestChara->getPos().y,
                                    pClosestChara->getPos().z );

    if( distance < range )
    {
      aggro( pClosestChara );
    }
  }
}

void Sapphire::Entity::BNpc::setOwner( Sapphire::Entity::CharaPtr m_pChara )
{
  m_pOwner = m_pChara;
  if( m_pChara != nullptr )
  {
    auto setOwnerPacket = makeZonePacket< FFXIVIpcFirstAttack >( m_pChara->getId() );
    setOwnerPacket->data().Type = 0x01;
    setOwnerPacket->data().Id = m_pChara->getId();
    sendToInRangeSet( setOwnerPacket );
  }
  else
  {
    auto setOwnerPacket = makeZonePacket< FFXIVIpcFirstAttack >( getId() );
    setOwnerPacket->data().Type = 0x01;
    setOwnerPacket->data().Id = static_cast< uint32_t >( INVALID_GAME_OBJECT_ID );
    sendToInRangeSet( setOwnerPacket );
  }

  if( m_pChara != nullptr && m_pChara->isPlayer() )
  {
    auto letter = makeActorControl( getId(), ActorControlType::SetHateLetter, 1, getId(), 0 );
    auto& server = Common::Service< World::WorldServer >::ref();
    server.queueForPlayer( m_pChara->getAsPlayer()->getCharacterId(), letter );
  }

}

void Sapphire::Entity::BNpc::setLevelId( uint32_t levelId )
{
  m_levelId = levelId;
}

uint32_t Sapphire::Entity::BNpc::getLevelId() const
{
  return m_levelId;
}

bool Sapphire::Entity::BNpc::hasFlag( uint32_t flag ) const
{
  return m_flags & flag;
}

void Sapphire::Entity::BNpc::setFlag( uint32_t flag )
{
  m_flags |= flag;
}

void Sapphire::Entity::BNpc::autoAttack( CharaPtr pTarget )
{
  auto teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  uint64_t tick = Util::getTimeMs();

  // todo: this needs to use the auto attack delay for the equipped weapon
  if( ( tick - m_lastAttack ) > 2500 )
  {
    pTarget->onActionHostile( getAsChara() );
    m_lastAttack = tick;
    srand( static_cast< uint32_t >( tick ) );

    auto damage = Math::CalcStats::calcAutoAttackDamage( *this );
    //damage.first = 1;

    auto effectPacket = std::make_shared< EffectPacket1 >( getId(), pTarget->getId(), 7 );
    effectPacket->setRotation( Util::floatToUInt16Rot( getRot() ) );
    Common::CalcResultParam effectEntry{};
    effectEntry.Value = static_cast< int16_t >( damage.first );
    effectEntry.Type = ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
    effectEntry.Flag = 128;
    effectEntry.Arg0 = 3;
    effectEntry.Arg1 = 7;
    //effectEntry.Arg2 = 0x71;
    effectPacket->setSequence( pZone->getNextEffectSequence() );
    effectPacket->addTargetEffect( effectEntry );

    sendToInRangeSet( effectPacket );

    pTarget->takeDamage( static_cast< uint16_t >( damage.first ) );

  }
}

void Sapphire::Entity::BNpc::calculateStats()
{
  uint8_t level = getLevel();
  uint8_t job = static_cast< uint8_t >( getClass() );

  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto classInfo = exdData.getRow< Component::Excel::ClassJob >( job );
  auto paramGrowthInfo = exdData.getRow< Component::Excel::ParamGrow >( level );

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
//  m_baseStats.attackPotMagic = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );
//  m_baseStats.healingPotMagic = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );
//  auto tenacity = static_cast< uint32_t >( paramGrowthInfo->data().ParamBase );

  setStatValue( BaseParam::Determination, determination );
  setStatValue( BaseParam::SkillSpeed, skillSpeed );
  setStatValue( BaseParam::SpellSpeed, spellSpeed );
  setStatValue( BaseParam::CriticalHit, critHitRate );

  setStatValue( BaseParam::AttackPower, str );
  setStatValue( BaseParam::AttackMagicPotency, inte );
  setStatValue( BaseParam::HealingMagicPotency, mnd );

}

uint32_t Sapphire::Entity::BNpc::getRank() const
{
  return m_rank;
}

uint32_t Sapphire::Entity::BNpc::getBoundInstanceId() const
{
  return m_boundInstanceId;
}

BNpcType Sapphire::Entity::BNpc::getBNpcType() const
{
  return m_bnpcType;
}

uint32_t Sapphire::Entity::BNpc::getLayoutId() const
{
  return m_layoutId;
}

void Sapphire::Entity::BNpc::init()
{
  m_maxHp = Sapphire::Math::CalcStats::calculateMaxHp( *getAsChara() );
  m_hp = m_maxHp;
  max_hp = m_maxHp;
}
