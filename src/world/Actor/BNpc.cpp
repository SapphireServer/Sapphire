#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/EffectPacket.h>
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

#include "ServerMgr.h"
#include "Session.h"
#include "Chara.h"
#include "Player.h"
#include "BNpc.h"
#include "BNpcTemplate.h"
#include "Script/ScriptMgr.h"

#include "Common.h"

#include <Manager/TerritoryMgr.h>
#include <Manager/NaviMgr.h>
#include <Manager/TerritoryMgr.h>
#include <Manager/RNGMgr.h>
#include <Manager/ActionMgr.h>
#include <Service.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Entity::BNpc::BNpc() :
  Npc( ObjKind::BattleNpc )
{
}

Sapphire::Entity::BNpc::BNpc( uint32_t id, BNpcTemplatePtr pTemplate, float posX, float posY, float posZ, float rot,
                              uint8_t level, uint32_t maxHp, TerritoryPtr pZone ) :
  Npc( ObjKind::BattleNpc )
{
  m_id = id;
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
  m_rot = rot;
  m_level = level;
  m_invincibilityType = InvincibilityNone;
  m_currentStance = Common::Stance::Passive;
  m_levelId = 0;
  m_flags = 0;

  m_class = ClassJob::Adventurer;

  m_pCurrentTerritory = std::move( pZone );

  m_spawnPos = m_pos;
  m_isMoving = false;

  m_timeOfDeath = 0;
  m_targetId = Common::INVALID_GAME_OBJECT_ID64;

  m_maxHp = maxHp;
  m_maxMp = 200;
  m_hp = maxHp;
  m_mp = 200;

  m_state = BNpcState::Idle;
  m_status = ActorStatus::Idle;

  m_baseStats.max_hp = maxHp;
  m_baseStats.max_mp = 200;

  memcpy( m_customize, pTemplate->getCustomize(), sizeof( m_customize ) );
  memcpy( m_modelEquip, pTemplate->getModelEquip(), sizeof( m_modelEquip ) );

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto bNpcBaseData = exdData.get< Data::BNpcBase >( m_bNpcBaseId );
  assert( bNpcBaseData );

  m_radius = bNpcBaseData->scale;

  auto modelChara = exdData.get< Data::ModelChara >( bNpcBaseData->modelChara );
  if( modelChara )
  {
    auto modelSkeleton = exdData.get< Data::ModelSkeleton >( modelChara->model );
    if( modelSkeleton )
      m_radius *= modelSkeleton->radius;
  }

  m_naviTargetReachedDistance = m_radius;

  calculateStats();
  auto& scriptMgr = Common::Service< Sapphire::Scripting::ScriptMgr >::ref();
  scriptMgr.onBNpcInit( *this );
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
  pTarget->queuePacket( std::make_shared< NpcSpawnPacket >( *this, *pTarget ) );
}

void Sapphire::Entity::BNpc::despawn( PlayerPtr pTarget )
{
  pTarget->freePlayerSpawnId( getId() );
  pTarget->queuePacket( makeActorControlSelf( m_id, DespawnZoneScreenMsg, 0x04, getId(), 0x01 ) );
}

Sapphire::Entity::BNpcState Sapphire::Entity::BNpc::getState() const
{
  return m_state;
}

void Sapphire::Entity::BNpc::setState( BNpcState state )
{
  m_state = state;
}

bool Sapphire::Entity::BNpc::moveTo( const FFXIVARR_POSITION3& pos, float radius )
{

  auto pNaviProvider = m_pCurrentTerritory->getNaviProvider();

  if( !pNaviProvider )
  {
    Logger::error( "No NaviProvider for zone#{0} - {1}",
                   m_pCurrentTerritory->getGuId(),
                   m_pCurrentTerritory->getInternalName() );
    return false;
  }

  auto pos1 = pNaviProvider->getMovePos( *this );
  
  if( Util::distance( pos1, pos ) < getNaviTargetReachedDistance() + radius )
  {
    // Reached destination
    face( pos );
    setPos( pos1 );
    sendPositionUpdate();
    pNaviProvider->updateAgentPosition( *this );
    m_isMoving = false;
    return true;
  }

  m_pCurrentTerritory->updateActorPosition( *this );
  face( pos );
  setPos( pos1 );
  sendPositionUpdate();
  m_isMoving = true;
  return false;
}

bool Sapphire::Entity::BNpc::moveTo( const Entity::Chara& targetChara )
{
  return moveTo( targetChara.getPos(), targetChara.getRadius() );
}

void Sapphire::Entity::BNpc::stopMoving()
{
  auto pNaviProvider = m_pCurrentTerritory->getNaviProvider();
  if( !pNaviProvider || !m_isMoving )
    return;
  sendPositionUpdate();
  pNaviProvider->updateAgentPosition( *this );
  m_isMoving = false;
}

void Sapphire::Entity::BNpc::sendPositionUpdate()
{
  uint8_t unk1 = 0x3a;
  uint8_t animationType = 2;
  uint16_t moveSpeed = MoveSpeed::Walk;

  if( m_state == BNpcState::Combat || m_state == BNpcState::Retreat )
  {
    animationType = 0;
    moveSpeed = MoveSpeed::Run;
  }

  auto movePacket = std::make_shared< MoveActorPacket >( *getAsChara(), unk1, animationType, 0, moveSpeed );
  sendToInRangeSet( movePacket );
}

void Sapphire::Entity::BNpc::hateListClear()
{
  if( m_hateList.empty() )
    return;

  auto hateListCopy = m_hateList;
  for( auto& listEntry : hateListCopy )
  {
    deaggro( listEntry->m_pChara );
  }
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

void Sapphire::Entity::BNpc::hateListAddOrUpdate( Sapphire::Entity::CharaPtr pChara, int32_t hateAmount )
{
  for( auto listEntry : m_hateList )
  {
    if( listEntry->m_pChara->getId() == pChara->getId() )
    {
      listEntry->m_hateAmount += static_cast< uint32_t >( hateAmount );
      return;
    }
  }

  auto hateEntry = std::make_shared< HateListEntry >();
  hateEntry->m_hateAmount = static_cast< uint32_t >( hateAmount );
  hateEntry->m_pChara = pChara;
  m_hateList.insert( hateEntry );
  if( pChara->isPlayer() )
  {
    auto pPlayer = pChara->getAsPlayer();
    pPlayer->onMobAggro( getAsBNpc() );
  }
  auto& scriptMgr = Common::Service< Sapphire::Scripting::ScriptMgr >::ref();
  scriptMgr.onBNpcHateListAdd( *this, *pChara );
}

void Sapphire::Entity::BNpc::hateListRemove( Sapphire::Entity::CharaPtr pChara )
{
  for( auto listEntry : m_hateList )
  {
    if( listEntry->m_pChara->getId() == pChara->getId() )
    {
      m_hateList.erase( listEntry );
      if( pChara->isPlayer() )
      {
        PlayerPtr tmpPlayer = pChara->getAsPlayer();
        tmpPlayer->onMobDeaggro( getAsBNpc() );
      }
      auto& scriptMgr = Common::Service< Sapphire::Scripting::ScriptMgr >::ref();
      scriptMgr.onBNpcHateListRemove( *this, *pChara );
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

  changeTarget( pChara->getId() );
  setStance( Stance::Active );
  m_state = BNpcState::Combat;

  if( m_hateList.empty() )
  {
    sendToInRangeSet( makeActorControl( getId(), ActorControlType::ToggleWeapon, 1, 1, 0 ) );
    sendToInRangeSet( makeActorControl( getId(), ActorControlType::ToggleAggro, 1, 0, 0 ) );
  }

  hateListAddOrUpdate( pChara, 1 );
}

void Sapphire::Entity::BNpc::deaggro( Sapphire::Entity::CharaPtr pChara )
{
  hateListRemove( pChara );

  if( m_hateList.empty() )
  {
    sendToInRangeSet( makeActorControl( getId(), ActorControlType::ToggleWeapon, 0, 1, 1 ) );
    sendToInRangeSet( makeActorControl( getId(), ActorControlType::ToggleAggro, 0, 0, 0 ) );
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
  if( getCurrentAction() && getCurrentAction()->hasCastTime() )
  {
    if( m_pCurrentAction->update() )
      m_pCurrentAction = nullptr;
    return;
  }

  auto& scriptMgr = Common::Service< Sapphire::Scripting::ScriptMgr >::ref();
  if( !scriptMgr.onBNpcUpdate( *this, tickCount ) )
    doDefaultBNpcUpdate( tickCount );
  
  Chara::update( tickCount );
}

void Sapphire::Entity::BNpc::doDefaultBNpcUpdate( uint64_t tickCount )
{
  const uint8_t maxDistanceToOrigin = 40;
  const uint32_t roamTick = 20;

  auto pNaviProvider = m_pCurrentTerritory->getNaviProvider();

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

        m_roamPos = pNaviProvider->findRandomPositionInCircle( m_spawnPos, 5 );
        m_state = BNpcState::Roaming;
        pNaviProvider->updateAgentParameters( *this );
      }

      checkAggro();
    }
    break;

    case BNpcState::Combat:
    {
      pNaviProvider->updateAgentParameters( *this );

      auto distanceOrig = Util::distance( getPos().x, getPos().y, getPos().z,
        m_spawnPos.x, m_spawnPos.y,  m_spawnPos.z );

      auto pHatedActor = hateListGetHighest();

      while( pHatedActor && ( !pHatedActor->isAlive() || getCurrentTerritory()->getGuId() != pHatedActor->getCurrentTerritory()->getGuId() ) )
      {
        hateListRemove( pHatedActor );
        pHatedActor = hateListGetHighest();
      }

      if( !pHatedActor )
      {
        hateListClear();
        changeTarget( INVALID_GAME_OBJECT_ID64 );
        setStance( Stance::Passive );
        setOwner( nullptr );
        m_state = BNpcState::Retreat;
        return;
      }

      auto distance = Util::distance( getPos().x, getPos().y, getPos().z,
        pHatedActor->getPos().x, pHatedActor->getPos().y, pHatedActor->getPos().z );

      if( !hasFlag( NoDeaggro ) && ( distanceOrig > maxDistanceToOrigin ) )
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

      if( distance < ( getRadius() + pHatedActor->getRadius() + 3.f ) )
      {
        stopMoving();

        if( !hasFlag( TurningDisabled ) && face( pHatedActor->getPos() ) )
          sendPositionUpdate();

        // in combat range. ATTACK!
        autoAttack( pHatedActor );
      }
    }
  }
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
  setTargetId( INVALID_GAME_OBJECT_ID64 );
  m_currentStance = Stance::Passive;
  m_state = BNpcState::Dead;
  m_timeOfDeath = Util::getTimeSeconds();
  setOwner( nullptr );

  auto& scriptMgr = Common::Service< Sapphire::Scripting::ScriptMgr >::ref();
  scriptMgr.onBNpcDeath( *this );

  for( auto& pHateEntry : m_hateList )
  {
    // TODO: handle drops 
    auto pPlayer = pHateEntry->m_pChara->getAsPlayer();
    if( pPlayer )
      pPlayer->onMobKill( static_cast< uint16_t >( m_bNpcNameId ) );
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

  if( pClosestChara && pClosestChara->isAlive() && pClosestChara->isPlayer() )
  {
    // will use this range if chara level is lower than bnpc, otherwise diminishing equation applies
    float range = 13.f;

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
  if( ( !m_pOwner && !m_pChara ) || ( m_pOwner && m_pChara && m_pOwner->getId() == m_pChara->getId() ) )
    return;
  m_pOwner = m_pChara;
  if( m_pChara != nullptr )
  {
    auto setOwnerPacket = makeZonePacket< FFXIVIpcActorOwner >( m_pChara->getId() );
    setOwnerPacket->data().type = 0x01;
    setOwnerPacket->data().actorId = m_pChara->getId();
    sendToInRangeSet( setOwnerPacket );
  }
  else
  {
    auto setOwnerPacket = makeZonePacket< FFXIVIpcActorOwner >( getId() );
    setOwnerPacket->data().type = 0x00;
    setOwnerPacket->data().actorId = static_cast< uint32_t >( INVALID_GAME_OBJECT_ID );
    sendToInRangeSet( setOwnerPacket );
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

void Sapphire::Entity::BNpc::unsetFlag( uint32_t flag )
{
  m_flags = m_flags & ( 0xFFFFFFFF - flag );
}

/*!
TODO: this only solves attacks from melee classes.
Will have to be extended for ranged attacks.

\param ActorPtr the autoAttack is performed on
*/
void Sapphire::Entity::BNpc::autoAttack( CharaPtr pTarget )
{
  uint64_t tick = Util::getTimeMs();

  // todo: this needs to use the auto attack delay for the equipped weapon
  if( ( tick - m_lastAttack ) > 2500 )
  {
    pTarget->onActionHostile( getAsChara() );
    m_lastAttack = tick;

    auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
    auto actionData = exdData.get< Data::Action >( 7 );
    assert( actionData );
    auto action = World::Action::make_Action( getAsChara(), 7, 0, actionData );

    action->setTargetId( pTarget->getId() );
    action->setPos( getPos() );
    action->setAutoAttack();

    if( action->init() )
    {
      action->start();
    }
  }
}

void Sapphire::Entity::BNpc::calculateStats()
{
  uint8_t level = getLevel();
  uint8_t job = static_cast< uint8_t >( getClass() );

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto classInfo = exdData.get< Sapphire::Data::ClassJob >( job );
  auto paramGrowthInfo = exdData.get< Sapphire::Data::ParamGrow >( level );

  float base = Math::CalcStats::calculateBaseStat( *this );

  m_baseStats.str = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierStrength ) / 100 ) );
  m_baseStats.dex = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierDexterity ) / 100 ) );
  m_baseStats.vit = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierVitality ) / 100 ) );
  m_baseStats.inte = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierIntelligence ) / 100 ) );
  m_baseStats.mnd = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierMind ) / 100 ) );
  //m_baseStats.pie = static_cast< uint32_t >( base * ( static_cast< float >( classInfo->modifierPiety ) / 100 ) );

  m_baseStats.determination = static_cast< uint32_t >( base );
  m_baseStats.pie = static_cast< uint32_t >( base );
  m_baseStats.skillSpeed = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );
  m_baseStats.spellSpeed = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );
  m_baseStats.haste = 100;
  m_baseStats.accuracy = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );
  m_baseStats.critHitRate = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );
  m_baseStats.attackPotMagic = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );
  m_baseStats.healingPotMagic = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );
  m_baseStats.tenacity = static_cast< uint32_t >( paramGrowthInfo->baseSpeed );

  m_baseStats.attack = m_baseStats.str;
  m_baseStats.attackPotMagic = m_baseStats.inte;
  m_baseStats.healingPotMagic = m_baseStats.mnd;
}

void Sapphire::Entity::BNpc::setCustomVar( uint32_t varId, uint64_t value )
{
  m_customVarMap[ varId ] = value;
}

uint64_t Sapphire::Entity::BNpc::getCustomVar( uint32_t varId )
{
  auto it = m_customVarMap.find( varId );
  if( it != m_customVarMap.end() )
    return it->second;
  return 0;
}
