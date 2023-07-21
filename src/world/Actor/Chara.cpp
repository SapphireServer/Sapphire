#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdData.h>
#include <utility>
#include <Network/CommonActorControl.h>
#include <Service.h>

#include "Forwards.h"

#include "Territory/Territory.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/EffectPacket1.h"
#include "Network/PacketWrappers/HudParamPacket.h"
#include "Network/Util/PacketUtil.h"

#include "Action/Action.h"
#include "WorldServer.h"
#include "Session.h"
#include "Math/CalcStats.h"
#include "Chara.h"
#include "Player.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/MgrUtil.h"
#include "Manager/PlayerMgr.h"
#include "Common.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::World;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

Chara::Chara( ObjKind type ) :
  GameObject( type ),
  m_pose( 0 ),
  m_targetId( INVALID_GAME_OBJECT_ID64 ),
  m_directorId( 0 ),
  m_radius( 1.f )
{

  m_lastTickTime = 0;
  m_lastUpdate = 0;
  m_lastAttack = Common::Util::getTimeMs();

  m_bonusStats.fill( 0 );

  // initialize the free slot queue
  for( uint8_t i = 0; i < MAX_STATUS_EFFECTS; i++ )
  {
    m_statusEffectFreeSlotQueue.push( i );
  }
}

Chara::~Chara() = default;

/*! \return the actors name */
std::string Chara::getName() const
{
  return { m_name };
}


/*! \return current stance of the actors */
Stance Chara::getStance() const
{
  return m_currentStance;
}

/*! \return actor stats */
const Chara::ActorStatsArray& Chara::getStats() const
{
  return m_baseStats;
}

/*! \return current HP */
uint32_t Chara::getHp() const
{
  return m_hp;
}

uint32_t Chara::getHpPercent() const
{
  return ( m_hp * 100 ) / m_maxHp;
}

/*! \return current MP */
uint32_t Chara::getMp() const
{
  return m_mp;
}

/*! \return current TP */
uint16_t Chara::getTp() const
{
  return m_tp;
}

/*! \return current GP */
uint16_t Chara::getGp() const
{
  return m_gp;
}

/*! \return current invincibility type */
InvincibilityType Chara::getInvincibilityType() const
{
  return m_invincibilityType;
}

/*! \return current class or job */
ClassJob Chara::getClass() const
{
  return m_class;
}

/*! \param ClassJob to set */
void Chara::setClass( ClassJob classJob )
{
  m_class = classJob;
}

Role Chara::getRole() const
{
  switch( getClass() )
  {
    case ClassJob::Gladiator:
    case ClassJob::Marauder:
    case ClassJob::Paladin:
    case ClassJob::Warrior:
    case ClassJob::Darkknight:
      return Role::Tank;

    case ClassJob::Pugilist:
    case ClassJob::Lancer:
    case ClassJob::Monk:
    case ClassJob::Dragoon:
    case ClassJob::Rogue:
    case ClassJob::Ninja:
      return Role::Melee;

    case ClassJob::Archer:
    case ClassJob::Bard:
    case ClassJob::Machinist:
      return Role::RangedPhysical;

    case ClassJob::Conjurer:
    case ClassJob::Whitemage:
    case ClassJob::Scholar:
    case ClassJob::Astrologian:
      return Role::Healer;

    case ClassJob::Thaumaturge:
    case ClassJob::Blackmage:
    case ClassJob::Arcanist:
    case ClassJob::Summoner:
      return Role::RangedMagical;

    case ClassJob::Carpenter:
    case ClassJob::Blacksmith:
    case ClassJob::Armorer:
    case ClassJob::Goldsmith:
    case ClassJob::Leatherworker:
    case ClassJob::Weaver:
    case ClassJob::Alchemist:
    case ClassJob::Culinarian:
      return Role::Crafter;

    case ClassJob::Miner:
    case ClassJob::Botanist:
    case ClassJob::Fisher:
      return Role::Gatherer;

    default:
      return Role::None;
  }
}

/*! \param Id of the target to set */
void Chara::setTargetId( uint64_t targetId )
{
  m_targetId = targetId;
}

/*! \return Id of the current target */
uint64_t Chara::getTargetId() const
{
  return m_targetId;
}

/*! \return True if the actor is alive */
bool Chara::isAlive() const
{
  return ( m_hp > 0 );
}

/*! \return max hp for the actor */
uint32_t Chara::getMaxHp() const
{
  return m_maxHp;
}

/*! \return max mp for the actor */
uint32_t Chara::getMaxMp() const
{
  return m_maxMp;
}

/*! \return reset hp to current max hp */
void Chara::resetHp()
{
  m_hp = getMaxHp();
}

/*! \return reset mp to current max mp */
void Chara::resetMp()
{
  m_mp = getMaxMp();
}

/*! \param hp amount to set ( caps to maxHp ) */
void Chara::setHp( uint32_t hp )
{
  m_hp = hp < getMaxHp() ? hp : getMaxHp();
}

/*! \param mp amount to set ( caps to maxMp ) */
void Chara::setMp( uint32_t mp )
{
  m_mp = mp < getMaxMp() ? mp : getMaxMp();
}

/*! \param gp amount to set*/
void Chara::setGp( uint32_t gp )
{
  m_gp = static_cast< uint16_t >( gp );
}

/*! \param tp amount to set*/
void Chara::setTp( uint32_t tp )
{
  m_tp = static_cast< uint16_t >( tp );
}

/*! \param type invincibility type to set */
void Sapphire::Entity::Chara::setInvincibilityType( Common::InvincibilityType type )
{
  m_invincibilityType = type;
}

/*! \return current status of the actor */
ActorStatus Chara::getStatus() const
{
  return m_status;
}

/*! \param status to set */
void Chara::setStatus( ActorStatus status )
{
  m_status = status;
}

/*!
Performs necessary steps to mark an actor dead.
Sets hp/mp/tp, sets status, plays animation and fires onDeath event
*/
void Chara::die()
{
  m_status = ActorStatus::Dead;
  m_hp = 0;
  m_mp = 0;
  m_tp = 0;

  // fire onDeath event
  onDeath();

  // if the actor is a player, the update needs to be send to himself too
  bool selfNeedsUpdate = isPlayer();
  Network::Util::Packet::sendActorControl( getInRangePlayerIds( selfNeedsUpdate ), getId(), SetStatus, static_cast< uint8_t >( ActorStatus::Dead ) );
  Network::Util::Packet::sendActorControl( getInRangePlayerIds( selfNeedsUpdate ), getId(), DeathAnimation );
}

uint64_t Chara::getLastAttack() const
{
  return m_lastAttack;
}

void Chara::setLastAttack( uint64_t tickCount )
{
  m_lastAttack = tickCount;
}

/*!
Calculates and sets the rotation to look towards a specified
position

\param Position to look towards
*/
bool Chara::face( const FFXIVARR_POSITION3& p )
{
  float oldRot = getRot();
  float rot = Common::Util::calcAngFrom( getPos().x, getPos().z, p.x, p.z );
  float newRot = PI - rot + ( PI / 2 );

  setRot( newRot );

  return ( fabs( oldRot - newRot ) <= std::numeric_limits< float >::epsilon() * fmax( fabs( oldRot ), fabs( newRot ) ) );
}

/*!
Set and propagate the actor stance to in range players
( not the actor himself )

\param stance to set
*/
void Chara::setStance( Stance stance )
{
  m_currentStance = stance;
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), ToggleWeapon, stance, 1 );
}

/*!
Check if an action is queued for execution, if so update it
and if fully performed, clean up again.

\return true if a queued action has been updated
*/
bool Chara::checkAction()
{

  if( m_pCurrentAction == nullptr )
    return false;

  if( m_pCurrentAction->update() )
    m_pCurrentAction.reset();

  return true;

}

void Chara::update( uint64_t tickCount )
{
  updateStatusEffects();

  if( std::difftime( static_cast< time_t >( tickCount ), m_lastTickTime ) > 3000 )
  {
    onTick();

    m_lastTickTime = static_cast< time_t >( tickCount );
  }

  m_lastUpdate = static_cast< time_t >( tickCount );
}

/*!
Change the current target and propagate to in range players

\param target actor id
*/
void Chara::changeTarget( uint64_t targetId )
{
  setTargetId( targetId );
  Network::Util::Packet::sendActorControlTarget( getInRangePlayerIds(), getId(), SetTarget, 0, 0, 0, 0, targetId );
}

/*!
Dummy function \return 0
*/
uint8_t Chara::getLevel() const
{
  return 0;
}

/*!
Let an actor take damage and perform necessary steps
according to resulting hp, propagates new hp value to players
in range
TODO: eventually this needs to distinguish between physical and
magical dmg and take status effects into account

\param amount of damage to be taken
*/
void Chara::takeDamage( uint32_t damage )
{
  if( damage >= m_hp )
  {
    switch( m_invincibilityType )
    {
      case InvincibilityNone:
        setHp( 0 );
        die();
        break;
      case InvincibilityRefill:
        resetHp();
        break;
      case InvincibilityStayAlive:
        setHp( 0 );
        break;
      case InvincibilityIgnoreDamage:
        break;
    }
  }
  else
    m_hp -= damage;
}

/*!
Let an actor get healed and perform necessary steps
according to resulting hp, propagates new hp value to players
in range

\param amount of hp to be healed
*/
void Chara::heal( uint32_t amount )
{
  if( ( m_hp + amount ) > getMaxHp() )
  {
    m_hp = getMaxHp();
  }
  else
    m_hp += amount;
}

void Chara::restoreMP( uint32_t amount )
{
  if( ( m_mp + amount ) > getMaxMp() )
  {
    m_mp = getMaxMp();
  }
  else
    m_mp += amount;
}

/*! \return ActionPtr of the currently registered action, or nullptr */
Action::ActionPtr Chara::getCurrentAction() const
{
  return m_pCurrentAction;
}

/*! \param ActionPtr of the action to be registered */
void Chara::setCurrentAction( Action::ActionPtr pAction )
{
  m_pCurrentAction = std::move( pAction );
}

/*!
Autoattack prototype implementation
TODO: move the check if the autoAttack can be performed to the callee
also rename autoAttack to autoAttack as that is more elaborate
On top of that, this only solves attacks from melee classes.
Will have to be extended for ranged attacks.

\param GameObjectPtr the autoAttack is performed on
*/
void Chara::autoAttack( CharaPtr pTarget )
{
  uint64_t tick = Common::Util::getTimeMs();

  // todo: this needs to use the auto attack delay for the equipped weapon
  if( ( tick - m_lastAttack ) > 2500 )
  {
    pTarget->onActionHostile( getAsChara() );
    m_lastAttack = tick;
    srand( static_cast< uint32_t >( tick ) );

    auto damage = static_cast< uint16_t >( 10 + rand() % 12 );

    auto effectPacket = std::make_shared< EffectPacket1 >( getId(), pTarget->getId(), 7 );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( getRot() ) );

    Common::CalcResultParam effectEntry{};
    effectEntry.Value = static_cast< int16_t >( damage );
    effectEntry.Type = ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
    effectEntry.Arg0 = static_cast< uint8_t >( ActionHitSeverityType::NormalDamage );
    effectEntry.Arg2 = 0x71;
    effectPacket->addTargetEffect( effectEntry );

    server().queueForPlayers( getInRangePlayerIds(), effectPacket );

    pTarget->takeDamage( damage );
  }
}

/*! \param StatusEffectPtr to be applied to the actor */
void Chara::addStatusEffect( StatusEffect::StatusEffectPtr pEffect )
{
  auto& teriMgr = Common::Service< Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );

  int8_t nextSlot = getStatusEffectSlotWithIdAndSource( pEffect->getId(), pEffect->getSrcActorId() );
  if( nextSlot == -1 && !pEffect->getCanApplyMultipleTimes() )
  {
    nextSlot = getStatusEffectSlotWithId( pEffect->getId());
  }
  if( nextSlot == -1)
  {
    nextSlot = getStatusEffectFreeSlot();
  }

  // if there is no slot left, do not add the effect
  if( nextSlot == -1 )
    return;

  pEffect->setSlot( nextSlot );
  m_statusEffectMap[ nextSlot ] = pEffect;
  pEffect->applyStatus();
}

/*! \param StatusEffectPtr to be applied to the actor */
void Chara::addStatusEffectById( StatusEffect::StatusEffectPtr pStatus )
{
  addStatusEffect( pStatus );
}

/*! \param StatusEffectPtr to be applied to the actor */
void Chara::addStatusEffectByIdIfNotExist( StatusEffect::StatusEffectPtr pStatus )
{
  if( hasStatusEffect( pStatus->getId() ) )
    return;

  addStatusEffect( pStatus );
}

int8_t Chara::getStatusEffectSlotWithIdAndSource( uint8_t statusId, uint32_t sourceId )
{
  for( const auto& effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == statusId && effectIt.second->getSrcActorId() == sourceId )
    {
      return effectIt.first;
    }
  }

  return -1;
}

int8_t Chara::getStatusEffectSlotWithId( uint8_t statusId )
{
  for( const auto& effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == statusId )
    {
      return effectIt.first;
    }
  }

  return -1;
}

int8_t Chara::getStatusEffectFreeSlot()
{
  int8_t freeEffectSlot = -1;

  if( m_statusEffectFreeSlotQueue.empty() )
    return freeEffectSlot;

  freeEffectSlot = static_cast< int8_t >( m_statusEffectFreeSlotQueue.front() );
  m_statusEffectFreeSlotQueue.pop();

  return freeEffectSlot;
}

void Chara::statusEffectFreeSlot( uint8_t slotId )
{
  m_statusEffectFreeSlotQueue.push( slotId );
}

void Chara::replaceSingleStatusEffectById( uint32_t id )
{
  for( const auto& effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == id )
    {
      removeStatusEffect( effectIt.first, false );
      break;
    }
  }
}

void Chara::removeSingleStatusEffectById( uint32_t id )
{
  for( const auto& effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == id )
    {
      removeStatusEffect( effectIt.first );
      break;
    }
  }
}

void Chara::removeStatusEffectByFlag( Common::StatusEffectFlag flag )
{
  for( auto effectIt = m_statusEffectMap.begin(); effectIt != m_statusEffectMap.end(); )
  {
    if( effectIt->second->getFlag() & static_cast< uint32_t >( flag ) )
      effectIt = removeStatusEffect( effectIt->first );
    else
      ++effectIt;
  }
}

std::map< uint8_t, Sapphire::StatusEffect::StatusEffectPtr >::iterator Chara::removeStatusEffect( uint8_t effectSlotId, bool sendOrder )
{
  auto pEffectIt = m_statusEffectMap.find( effectSlotId );
  if( pEffectIt == m_statusEffectMap.end() )
    return pEffectIt;

  statusEffectFreeSlot( effectSlotId );

  auto pEffect = pEffectIt->second;
  pEffect->removeStatus();

  if( sendOrder )
    Network::Util::Packet::sendActorControl( getInRangePlayerIds( isPlayer() ), getId(), StatusEffectLose, pEffect->getId() );

  auto it = m_statusEffectMap.erase( pEffectIt );
  Network::Util::Packet::sendHudParam( *this );
  return it;
}

std::map< uint8_t, StatusEffect::StatusEffectPtr > Chara::getStatusEffectMap() const
{
  return m_statusEffectMap;
}

Sapphire::StatusEffect::StatusEffectPtr Chara::getStatusEffectById( uint32_t id ) const
{
  for( const auto& effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == id )
      return effectIt.second;
  }

  return nullptr;
}

const uint8_t* Chara::getLookArray() const
{
  return m_customize;
}

const uint32_t* Chara::getModelArray() const
{
  return m_modelEquip;
}

uint8_t Chara::getPose() const
{
  return m_pose;
}

void Chara::setPose( uint8_t pose )
{
  m_pose = pose;
}

void Chara::sendStatusEffectUpdate()
{
  uint64_t currentTimeMs = Common::Util::getTimeMs();

  auto statusEffectList = makeZonePacket< FFXIVIpcStatus >( getId() );
  uint8_t slot = 0;
  for( const auto& effectIt : m_statusEffectMap )
  {
    float timeLeft = static_cast< float >( effectIt.second->getDuration() -
                                           ( currentTimeMs - effectIt.second->getStartTimeMs() ) ) / 1000;
    statusEffectList->data().effect[ slot ].Time = timeLeft;
    statusEffectList->data().effect[ slot ].Id = effectIt.second->getId();
    statusEffectList->data().effect[ slot ].Source = effectIt.second->getSrcActorId();
    slot++;
  }

  server().queueForPlayers( getInRangePlayerIds( isPlayer() ), statusEffectList );
}

void Chara::updateStatusEffects()
{
  uint64_t currentTimeMs = Common::Util::getTimeMs();

  for( auto effectIt = m_statusEffectMap.begin(); effectIt != m_statusEffectMap.end(); )
  {
    uint8_t effectIndex = effectIt->first;
    auto effect = effectIt->second;

    uint64_t lastTick = effect->getLastTickMs();
    uint64_t startTime = effect->getStartTimeMs();
    uint32_t duration = effect->getDuration();
    uint32_t tickRate = effect->getTickRate();

    if( duration > 0 && ( currentTimeMs - startTime ) > duration )
      effectIt = removeStatusEffect( effectIndex );
    else
      ++effectIt;

    if( ( currentTimeMs - lastTick ) > tickRate )
    {
      effect->setLastTick( currentTimeMs );
      effect->onTick();
    }
  }
}

bool Chara::hasStatusEffect( uint32_t id )
{
  for( const auto& [ key, val ] : m_statusEffectMap )
  {
    if( val->getId() == id )
      return true;
  }

  return false;
}

int64_t Chara::getLastUpdateTime() const
{
  return m_lastUpdate;
}

void Chara::setLastComboActionId( uint32_t actionId )
{
  m_lastComboActionId = actionId;
  m_lastComboActionTime = Common::Util::getTimeMs();
}

uint32_t Chara::getLastComboActionId() const
{
  // initially check for the time passed first, if it's more than the threshold just return 0 for the combo
  // we can hide the implementation detail this way and it just works:tm: for anything that uses it

  if( std::difftime( static_cast< time_t >( Common::Util::getTimeMs() ),
                     static_cast< time_t >( m_lastComboActionTime ) ) > Common::MAX_COMBO_LENGTH )
  {
    return 0;
  }

  return m_lastComboActionId;
}

uint32_t Chara::getDirectorId() const
{
  return m_directorId;
}

void Chara::setDirectorId( uint32_t directorId )
{
  m_directorId = directorId;
}

uint32_t Chara::getAgentId() const
{
  return m_agentId;
}

void Chara::setAgentId( uint32_t agentId )
{
  m_agentId = agentId;
}

float Chara::getRadius() const
{
  return m_radius;
}

Common::BaseParam Chara::getPrimaryStat() const
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto classJob = exdData.getRow< Excel::ClassJob >( static_cast< uint16_t >( getClass() ) );
  assert( classJob );

  return static_cast< Common::BaseParam >( classJob->data().Role );
}

uint32_t Chara::getStatValue( Common::BaseParam baseParam ) const
{
  auto index = static_cast< uint32_t >( baseParam );
  assert( index < m_baseStats.size() );

  return m_baseStats[ index ] + m_bonusStats[ index ];
}

float Chara::getStatValueFloat( Common::BaseParam baseParam ) const
{
  auto index = static_cast< uint32_t >( baseParam );
  assert( index < m_baseStats.size() );

  return static_cast< float >( m_baseStats[ index ] + m_bonusStats[ index ] );
}

uint32_t Chara::getBonusStat( Common::BaseParam baseParam ) const
{
  auto index = static_cast< uint32_t >( baseParam );
  assert( index < m_bonusStats.size() );

  return m_bonusStats[ index ];
}

void Chara::setStatValue( Common::BaseParam baseParam, uint32_t value )
{
  auto index = static_cast< uint32_t >( baseParam );
  assert( index < m_baseStats.size() );

  m_baseStats[ index ] = value;
}

float Chara::getModifier( Common::ParamModifier paramModifier ) const
{
  auto result = paramModifier >= Common::ParamModifier::StrengthPercent ? 1.0f : 0;

  for( const auto& [ key, status ] : m_statusEffectMap )
  {
    for( const auto& [ mod, val ] : status->getModifiers() )
    {
      if( mod != paramModifier )
        continue;

      if( paramModifier >= Common::ParamModifier::StrengthPercent )
        result *= 1.0f + ( val / 100.0f );
      else
        result += val;
    }
  }

  return result;
}

void Chara::onTick()
{
  uint32_t thisTickDmg = 0;
  uint32_t thisTickHeal = 0;

  for( const auto& effectIt : m_statusEffectMap )
  {
    auto thisEffect = effectIt.second->getTickEffect();
    switch( thisEffect.first )
    {
      case Common::ParamModifier::TickDamage:
      {
        thisTickDmg += thisEffect.second;
        break;
      }

      case Common::ParamModifier::TickHeal:
      {
        thisTickHeal += thisEffect.second;
        break;
      }
    }
  }

  // TODO: don't really like how this is handled
  // TODO: calculate actual damage from potency
  if( thisTickDmg != 0 )
  {
    takeDamage( thisTickDmg );
    Network::Util::Packet::sendActorControl( getInRangePlayerIds( isPlayer() ), getId(), HPFloatingText, 0,
                                             ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP, thisTickDmg );

    Network::Util::Packet::sendHudParam( *this );
  }

  if( thisTickHeal != 0 )
  {
    heal( thisTickHeal );
    Network::Util::Packet::sendActorControl( getInRangePlayerIds( isPlayer() ), getId(), HPFloatingText, 0,
                                             ActionEffectType::CALC_RESULT_TYPE_RECOVER_HP, thisTickHeal );

    Network::Util::Packet::sendHudParam( *this );
  }
}