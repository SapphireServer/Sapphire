#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>


#include "Forwards.h"

#include "Territory/Territory.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "StatusEffect/StatusEffect.h"
#include "Action/Action.h"
#include "ServerMgr.h"
#include "Session.h"
#include "Math/CalcStats.h"
#include "Chara.h"
#include "Player.h"
#include "Manager/TerritoryMgr.h"
#include "Framework.h"
#include "Common.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Entity::Chara::Chara( ObjKind type, FrameworkPtr pFw ) :
  Actor( type ),
  m_pose( 0 ),
  m_targetId( INVALID_GAME_OBJECT_ID64 ),
  m_pFw( std::move( std::move( pFw ) ) ),
  m_directorId( 0 ),
  m_radius( 1.f )
{

  m_lastTickTime = 0;
  m_lastUpdate = 0;

  m_bonusStats.fill( 0 );

  // initialize the free slot queue
  for( uint8_t i = 0; i < MAX_STATUS_EFFECTS; i++ )
  {
    m_statusEffectFreeSlotQueue.push( i );
  }
}

Sapphire::Entity::Chara::~Chara()
= default;

/*! \return the actors name */
std::string Sapphire::Entity::Chara::getName() const
{
  return std::string( m_name );
}


/*! \return current stance of the actors */
Sapphire::Common::Stance Sapphire::Entity::Chara::getStance() const
{
  return m_currentStance;
}

/*! \return actor stats */
Sapphire::Entity::Chara::ActorStats Sapphire::Entity::Chara::getStats() const
{
  return m_baseStats;
}

/*! \return current HP */
uint32_t Sapphire::Entity::Chara::getHp() const
{
  return m_hp;
}

uint32_t Sapphire::Entity::Chara::getHpPercent() const
{
  return ( m_hp * 100 ) / m_maxHp;
}

/*! \return current MP */
uint32_t Sapphire::Entity::Chara::getMp() const
{
  return m_mp;
}

/*! \return current TP */
uint16_t Sapphire::Entity::Chara::getTp() const
{
  return m_tp;
}

/*! \return current GP */
uint16_t Sapphire::Entity::Chara::getGp() const
{
  return m_gp;
}

/*! \return current invincibility type */
InvincibilityType Sapphire::Entity::Chara::getInvincibilityType() const
{
  return m_invincibilityType;
}

/*! \return current class or job */
Sapphire::Common::ClassJob Sapphire::Entity::Chara::getClass() const
{
  return m_class;
}

/*! \param ClassJob to set */
void Sapphire::Entity::Chara::setClass( Common::ClassJob classJob )
{
  m_class = classJob;
}

Sapphire::Common::Role Sapphire::Entity::Chara::getRole() const
{
  switch( getClass() )
  {
    case ClassJob::Gladiator:
    case ClassJob::Marauder:
    case ClassJob::Paladin:
    case ClassJob::Warrior:
    case ClassJob::Darkknight:
    case ClassJob::Gunbreaker:
      return Role::Tank;

    case ClassJob::Pugilist:
    case ClassJob::Lancer:
    case ClassJob::Monk:
    case ClassJob::Dragoon:
    case ClassJob::Rogue:
    case ClassJob::Ninja:
    case ClassJob::Samurai:
      return Role::Melee;

    case ClassJob::Archer:
    case ClassJob::Bard:
    case ClassJob::Machinist:
    case ClassJob::Dancer:
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
    case ClassJob::Redmage:
    case ClassJob::Bluemage:
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
void Sapphire::Entity::Chara::setTargetId( uint64_t targetId )
{
  m_targetId = targetId;
}

/*! \return Id of the current target */
uint64_t Sapphire::Entity::Chara::getTargetId() const
{
  return m_targetId;
}

/*! \return True if the actor is alive */
bool Sapphire::Entity::Chara::isAlive() const
{
  return ( m_hp > 0 );
}

/*! \return max hp for the actor */
uint32_t Sapphire::Entity::Chara::getMaxHp() const
{
  return m_baseStats.max_hp;
}

/*! \return max mp for the actor */
uint32_t Sapphire::Entity::Chara::getMaxMp() const
{
  return m_baseStats.max_mp;
}

/*! \return reset hp to current max hp */
void Sapphire::Entity::Chara::resetHp()
{
  m_hp = getMaxHp();
  sendStatusUpdate();
}

/*! \return reset mp to current max mp */
void Sapphire::Entity::Chara::resetMp()
{
  m_mp = getMaxMp();
  sendStatusUpdate();
}

/*! \param hp amount to set ( caps to maxHp ) */
void Sapphire::Entity::Chara::setHp( uint32_t hp )
{
  m_hp = hp < getMaxHp() ? hp : getMaxHp();
  sendStatusUpdate();
}

/*! \param mp amount to set ( caps to maxMp ) */
void Sapphire::Entity::Chara::setMp( uint32_t mp )
{
  m_mp = mp < getMaxMp() ? mp : getMaxMp();
  sendStatusUpdate();
}

/*! \param gp amount to set*/
void Sapphire::Entity::Chara::setGp( uint32_t gp )
{
  m_gp = static_cast< uint16_t >( gp );
  sendStatusUpdate();
}

/*! \param tp amount to set*/
void Sapphire::Entity::Chara::setTp( uint32_t tp )
{
  m_tp = static_cast< uint16_t >( tp );
  sendStatusUpdate();
}

/*! \param type invincibility type to set */
void Sapphire::Entity::Chara::setInvincibilityType( Common::InvincibilityType type )
{
  m_invincibilityType = type;
}

/*! \return current status of the actor */
Sapphire::Common::ActorStatus Sapphire::Entity::Chara::getStatus() const
{
  return m_status;
}

/*! \param status to set */
void Sapphire::Entity::Chara::setStatus( ActorStatus status )
{
  m_status = status;
}

/*!
Performs necessary steps to mark an actor dead.
Sets hp/mp/tp, sets status, plays animation and fires onDeath event
*/
void Sapphire::Entity::Chara::die()
{
  m_status = ActorStatus::Dead;
  m_hp = 0;
  m_mp = 0;
  m_tp = 0;

  // fire onDeath event
  onDeath();

  // if the actor is a player, the update needs to be send to himself too
  bool selfNeedsUpdate = isPlayer();

  FFXIVPacketBasePtr packet = makeActorControl( m_id, SetStatus, static_cast< uint8_t >( ActorStatus::Dead ) );
  sendToInRangeSet( packet, selfNeedsUpdate );

  // TODO: not all actor show the death animation when they die, some quest npcs might just despawn
  //       although that might be handled by setting the HP to 1 and doing some script magic

  FFXIVPacketBasePtr packet1 = makeActorControl( m_id, DeathAnimation, 0, 0, 0, 0x20 );
  sendToInRangeSet( packet1, selfNeedsUpdate );

}

/*!
Calculates and sets the rotation to look towards a specified
position

\param Position to look towards
*/
bool Sapphire::Entity::Chara::face( const Common::FFXIVARR_POSITION3& p )
{
  float oldRot = getRot();
  float rot = Util::calcAngFrom( getPos().x, getPos().z, p.x, p.z );
  float newRot = PI - rot + ( PI / 2 );

  setRot( newRot );

  return ( fabs( oldRot - newRot ) <= std::numeric_limits< float >::epsilon() * fmax( fabs( oldRot ), fabs( newRot ) ) );
}

/*!
Set and propagate the actor stance to in range players
( not the actor himself )

\param stance to set
*/
void Sapphire::Entity::Chara::setStance( Stance stance )
{
  m_currentStance = stance;

  FFXIVPacketBasePtr packet = makeActorControl( m_id, ToggleWeapon, stance, 0 );
  sendToInRangeSet( packet );
}

/*!
Check if an action is queued for execution, if so update it
and if fully performed, clean up again.

\return true if a queued action has been updated
*/
bool Sapphire::Entity::Chara::checkAction()
{

  if( m_pCurrentAction == nullptr )
    return false;

  if( m_pCurrentAction->update() )
    m_pCurrentAction.reset();

  return true;

}

void Sapphire::Entity::Chara::update( uint64_t tickCount )
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
void Sapphire::Entity::Chara::changeTarget( uint64_t targetId )
{
  setTargetId( targetId );
  FFXIVPacketBasePtr packet = makeActorControlTarget( m_id, SetTarget, 0, 0, 0, 0, targetId );
  sendToInRangeSet( packet );
}

/*!
Dummy function \return 0
*/
uint8_t Sapphire::Entity::Chara::getLevel() const
{
  return 0;
}

/*!
Let an actor take damage and perform necessary steps
according to resulting hp, propagates new hp value to players
in range

\param amount of damage to be taken
*/
void Sapphire::Entity::Chara::takeDamage( uint32_t damage )
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

  sendStatusUpdate();
}

/*!
Let an actor get healed and perform necessary steps
according to resulting hp, propagates new hp value to players
in range

\param amount of hp to be healed
*/
void Sapphire::Entity::Chara::heal( uint32_t amount )
{
  if( ( m_hp + amount ) > getMaxHp() )
  {
    m_hp = getMaxHp();
  }
  else
    m_hp += amount;

  sendStatusUpdate();
}

void Sapphire::Entity::Chara::restoreMP( uint32_t amount )
{
  if( ( m_mp + amount ) > getMaxMp() )
  {
    m_mp = getMaxMp();
  }
  else
    m_mp += amount;

  sendStatusUpdate();
}

/*!
Send an HpMpTp update to players in range ( and potentially to self )
TODO: poor naming, should be changed. Status is not HP. Also should be virtual
so players can have their own version and we can abolish the param.

\param true if the update should also be sent to the actor ( player ) himself
*/
void Sapphire::Entity::Chara::sendStatusUpdate()
{
  FFXIVPacketBasePtr packet = std::make_shared< UpdateHpMpTpPacket >( *this );
  sendToInRangeSet( packet );
}

/*! \return ActionPtr of the currently registered action, or nullptr */
Sapphire::World::Action::ActionPtr Sapphire::Entity::Chara::getCurrentAction() const
{
  return m_pCurrentAction;
}

/*! \param ActionPtr of the action to be registered */
void Sapphire::Entity::Chara::setCurrentAction( Sapphire::World::Action::ActionPtr pAction )
{
  m_pCurrentAction = std::move( pAction );
}

uint32_t Sapphire::Entity::Chara::getBonusStat( Common::BaseParam bonus ) const
{
  return m_bonusStats[ static_cast< uint8_t >( bonus ) ];
}

void Sapphire::Entity::Chara::autoAttack( CharaPtr pTarget )
{
  // moved to BNpc
}

/*! \param StatusEffectPtr to be applied to the actor */
void Sapphire::Entity::Chara::addStatusEffect( StatusEffect::StatusEffectPtr pEffect )
{
  int8_t nextSlot = getStatusEffectFreeSlot();
  // if there is no slot left, do not add the effect
  if( nextSlot == -1 )
    return;

  pEffect->applyStatus();
  m_statusEffectMap[ nextSlot ] = pEffect;

  auto statusEffectAdd = makeZonePacket< FFXIVIpcEffectResult >( getId() );

  statusEffectAdd->data().actor_id = pEffect->getTargetActorId();
  statusEffectAdd->data().current_hp = getHp();
  statusEffectAdd->data().current_mp = static_cast< uint16_t >( getMp() );
  statusEffectAdd->data().current_tp = getTp();
  statusEffectAdd->data().max_hp = getMaxHp();
  statusEffectAdd->data().max_mp = static_cast< uint16_t >( getMaxMp() );
  statusEffectAdd->data().classId = static_cast< uint8_t >( getClass() );
  statusEffectAdd->data().entryCount = 1; // todo: add multiple status but send only one result

  auto& status = statusEffectAdd->data().statusEntries[0];

  status.sourceActorId = pEffect->getSrcActorId();
  status.duration = static_cast< float >( pEffect->getDuration() ) / 1000;
  status.id = static_cast< uint16_t >( pEffect->getId() );
  status.index = static_cast< uint8_t >( nextSlot );
  status.param = pEffect->getParam();

  float totalShieldValue = 0;
  for( auto effectIt : m_statusEffectMap )
  {
    auto statusEffect = effectIt.second;
    if( static_cast< Common::StatusEffectType >( statusEffect->getEffectEntry().effectType ) == Common::StatusEffectType::Shield )
    {
      totalShieldValue += statusEffect->getEffectEntry().effectValue1;
    }
  }

  if( totalShieldValue > 0 )
  {
    totalShieldValue /= getMaxHp();
    totalShieldValue *= 100;
    statusEffectAdd->data().shieldPercentage = totalShieldValue >= 255 ? 255 : static_cast< uint8_t >( totalShieldValue );
  }

  sendToInRangeSet( statusEffectAdd, true );
  sendStatusEffectUpdate(); // although client buff displays correctly without this but retail sends it so we do it as well
}

void Sapphire::Entity::Chara::addStatusEffectById( uint32_t id, int32_t duration, Entity::Chara& source, uint16_t param )
{
  auto oldEffect = getStatusEffectById( id );
  if( oldEffect.second )
    removeStatusEffect( oldEffect.first, false, false );

  auto effect = StatusEffect::make_StatusEffect( id, source.getAsChara(), getAsChara(), duration, 3000, m_pFw );
  effect->setParam( param );
  addStatusEffect( effect );
}

void Sapphire::Entity::Chara::addStatusEffectByIdIfNotExist( uint32_t id, int32_t duration, Entity::Chara& source,
                                                             uint16_t param )
{
  if( getStatusEffectById( id ).second )
    return;

  auto effect = StatusEffect::make_StatusEffect( id, source.getAsChara(), getAsChara(), duration, 3000, m_pFw );
  effect->setParam( param );
  addStatusEffect( effect );
}

int8_t Sapphire::Entity::Chara::getStatusEffectFreeSlot()
{
  int8_t freeEffectSlot = -1;

  if( m_statusEffectFreeSlotQueue.empty() )
    return freeEffectSlot;

  freeEffectSlot = static_cast< int8_t >( m_statusEffectFreeSlotQueue.front() );
  m_statusEffectFreeSlotQueue.pop();

  return freeEffectSlot;
}

void Sapphire::Entity::Chara::statusEffectFreeSlot( uint8_t slotId )
{
  m_statusEffectFreeSlotQueue.push( slotId );
}

void Sapphire::Entity::Chara::removeSingleStatusEffectById( uint32_t id, bool sendActorControl, bool sendStatusList )
{
  for( auto effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == id )
    {
      removeStatusEffect( effectIt.first, sendActorControl, sendStatusList );
      break;
    }
  }
}

void Sapphire::Entity::Chara::removeStatusEffect( uint8_t effectSlotId, bool sendActorControl, bool sendStatusList )
{
  auto pEffectIt = m_statusEffectMap.find( effectSlotId );
  if( pEffectIt == m_statusEffectMap.end() )
    return;

  statusEffectFreeSlot( effectSlotId );

  auto pEffect = pEffectIt->second;
  pEffect->removeStatus();

  if( sendActorControl )
    sendToInRangeSet( makeActorControl( getId(), StatusEffectLose, pEffect->getId() ), isPlayer() );

  m_statusEffectMap.erase( effectSlotId );

  if( sendStatusList )
    sendStatusEffectUpdate();
}

std::map< uint8_t, Sapphire::StatusEffect::StatusEffectPtr > Sapphire::Entity::Chara::getStatusEffectMap() const
{
  return m_statusEffectMap;
}

const uint8_t* Sapphire::Entity::Chara::getLookArray() const
{
  return m_customize;
}

const uint32_t* Sapphire::Entity::Chara::getModelArray() const
{
  return m_modelEquip;
}

uint8_t Sapphire::Entity::Chara::getPose() const
{
  return m_pose;
}

void Sapphire::Entity::Chara::setPose( uint8_t pose )
{
  m_pose = pose;
}

void Sapphire::Entity::Chara::sendStatusEffectUpdate()
{
  uint64_t currentTimeMs = Util::getTimeMs();

  auto statusEffectList = makeZonePacket< FFXIVIpcStatusEffectList >( getId() );
  statusEffectList->data().classId = static_cast< uint8_t >( getClass() );
  statusEffectList->data().level = getLevel();
  statusEffectList->data().level1 = getLevel();
  statusEffectList->data().current_hp = getHp();
  statusEffectList->data().current_mp = getMp();
  statusEffectList->data().currentTp = getTp();
  statusEffectList->data().max_hp = getMaxHp();
  statusEffectList->data().max_mp = getMaxMp();
  uint8_t slot = 0;
  float totalShieldValue = 0;
  for( auto effectIt : m_statusEffectMap )
  {
    auto statusEffect = effectIt.second;
    if( static_cast< Common::StatusEffectType >( statusEffect->getEffectEntry().effectType ) == Common::StatusEffectType::Shield )
    {
      totalShieldValue += statusEffect->getEffectEntry().effectValue1;
    }

    float timeLeft = static_cast< float >( statusEffect->getDuration() -
                                           ( currentTimeMs - statusEffect->getStartTimeMs() ) ) / 1000;
    statusEffectList->data().effect[ slot ].duration = timeLeft;
    statusEffectList->data().effect[ slot ].effect_id = statusEffect->getId();
    statusEffectList->data().effect[ slot ].sourceActorId = statusEffect->getSrcActorId();
    slot++;
  }

  if( totalShieldValue > 0 )
  {
    totalShieldValue /= getMaxHp();
    totalShieldValue *= 100;
    statusEffectList->data().shieldPercentage = totalShieldValue >= 255 ? 255 : static_cast< uint8_t >( totalShieldValue );
  }

  sendToInRangeSet( statusEffectList, true );
}

void Sapphire::Entity::Chara::sendEffectResultToUpdateShieldValue()
{
  auto pPacket = makeZonePacket< FFXIVIpcEffectResult >( getId() );

  pPacket->data().actor_id = getId();
  pPacket->data().current_hp = getHp();
  pPacket->data().current_mp = static_cast< uint16_t >( getMp() );
  pPacket->data().current_tp = getTp();
  pPacket->data().max_hp = getMaxHp();
  pPacket->data().max_mp = static_cast< uint16_t >( getMaxMp() );
  pPacket->data().classId = static_cast< uint8_t >( getClass() );

  float totalShieldValue = 0;
  for( auto effectIt : m_statusEffectMap )
  {
    auto statusEffect = effectIt.second;
    if( static_cast< Common::StatusEffectType >( statusEffect->getEffectEntry().effectType ) == Common::StatusEffectType::Shield )
    {
      totalShieldValue += statusEffect->getEffectEntry().effectValue1;
    }
  }

  if( totalShieldValue > 0 )
  {
    totalShieldValue /= getMaxHp();
    totalShieldValue *= 100;
    pPacket->data().shieldPercentage = totalShieldValue >= 255 ? 255 : static_cast< uint8_t >( totalShieldValue );
  }

  sendToInRangeSet( pPacket, true );
}

void Sapphire::Entity::Chara::updateStatusEffects()
{
  uint64_t currentTimeMs = Util::getTimeMs();

  uint32_t thisTickDmg = 0;
  uint32_t thisTickHeal = 0;

  for( auto effectIt : m_statusEffectMap )
  {
    uint8_t effectIndex = effectIt.first;
    auto effect = effectIt.second;

    uint64_t lastTick = effect->getLastTickMs();
    uint64_t startTime = effect->getStartTimeMs();
    uint32_t duration = effect->getDuration();
    uint32_t tickRate = effect->getTickRate();

    if( duration > 0 && ( currentTimeMs - startTime ) > duration )
    {
      // remove status effect
      removeStatusEffect( effectIndex, true, true );
      // break because removing invalidates iterators
      break;
    }

    if( ( currentTimeMs - lastTick ) > tickRate )
    {
      effect->setLastTick( currentTimeMs );
      effect->onTick();

      auto thisEffect = effect->getTickEffect();

      switch( thisEffect.first )
      {

        case 1:
        {
          thisTickDmg += thisEffect.second;
          break;
        }

        case 2:
        {
          thisTickHeal += thisEffect.second;
          break;
        }

      }
    }

  }

  if( thisTickDmg != 0 )
  {
    takeDamage( thisTickDmg );
    sendToInRangeSet( makeActorControl( getId(), HPFloatingText, 0,
                                        static_cast< uint8_t >( ActionEffectType::Damage ), thisTickDmg ), true );
  }

  if( thisTickHeal != 0 )
  {
    heal( thisTickHeal );
    sendToInRangeSet( makeActorControl( getId(), HPFloatingText, 0,
                                        static_cast< uint8_t >( ActionEffectType::Heal ), thisTickHeal ), true );
  }
}

std::pair< uint8_t, Sapphire::StatusEffect::StatusEffectPtr > Sapphire::Entity::Chara::getStatusEffectById( uint32_t id )
{
  for( auto effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == id )
    {
      return std::make_pair( effectIt.first, effectIt.second );
    }
  }
  return std::make_pair( 0, nullptr );
}

int64_t Sapphire::Entity::Chara::getLastUpdateTime() const
{
  return m_lastUpdate;
}

void Sapphire::Entity::Chara::setLastComboActionId( uint32_t actionId )
{
  m_lastComboActionId = actionId;
  m_lastComboActionTime = Util::getTimeMs();
}

uint32_t Sapphire::Entity::Chara::getLastComboActionId() const
{
  // initially check for the time passed first, if it's more than the threshold just return 0 for the combo
  // we can hide the implementation detail this way and it just works:tm: for anything that uses it

  if( std::difftime( Util::getTimeMs(), m_lastComboActionTime ) > Common::MAX_COMBO_LENGTH )
  {
    return 0;
  }

  return m_lastComboActionId;
}

uint32_t Sapphire::Entity::Chara::getDirectorId() const
{
  return m_directorId;
}

void Sapphire::Entity::Chara::setDirectorId( uint32_t directorId )
{
  m_directorId = directorId;
}

uint32_t Sapphire::Entity::Chara::getAgentId() const
{
  return m_agentId;
}

void Sapphire::Entity::Chara::setAgentId( uint32_t agentId )
{
  m_agentId = agentId;
}


float Sapphire::Entity::Chara::getRadius() const
{
  return m_radius;
}

Sapphire::Common::BaseParam Sapphire::Entity::Chara::getPrimaryStat() const
{
  auto exdData = m_pFw->get< Data::ExdDataGenerated >();
  assert( exdData );

  auto classJob = exdData->get< Data::ClassJob >( static_cast< uint16_t >( getClass() ) );
  assert( classJob );

  return static_cast< Sapphire::Common::BaseParam >( classJob->primaryStat );
}

uint32_t Sapphire::Entity::Chara::getStatValue( Sapphire::Common::BaseParam baseParam ) const
{
  uint32_t value = 0;

  switch( baseParam )
  {
    case Common::BaseParam::Strength:
    {
      value = m_baseStats.str;
      break;
    }

    case Common::BaseParam::Dexterity:
    {
      value = m_baseStats.dex;
      break;
    }

    case Common::BaseParam::Vitality:
    {
      value = m_baseStats.vit;
      break;
    }

    case Common::BaseParam::Intelligence:
    {
      value = m_baseStats.inte;
      break;
    }

    case Common::BaseParam::Mind:
    {
      value = m_baseStats.mnd;
      break;
    }

    case Common::BaseParam::Piety:
    {
      value = m_baseStats.pie;
      break;
    }

    case Common::BaseParam::Determination:
    {
      value = m_baseStats.determination;
      break;
    }

    case Common::BaseParam::HP:
    {
      value = m_baseStats.max_hp;
      break;
    }

    case Common::BaseParam::MP:
    {
      value = m_baseStats.max_mp;
      break;
    }

    case Common::BaseParam::AttackPower:
    {
      auto primaryStat = getPrimaryStat();

      // everything else uses str for atk power except for brd/rogue/etc who use dex
      if( primaryStat == Common::BaseParam::Dexterity )
      {
        return getStatValue( primaryStat );
      }

      return getStatValue( Common::BaseParam::Strength );
    }

    case Common::BaseParam::AttackMagicPotency:
    {
      value = m_baseStats.attackPotMagic;
      break;
    }

    case Common::BaseParam::HealingMagicPotency:
    {
      value = m_baseStats.healingPotMagic;
      break;
    }

    case Common::BaseParam::SkillSpeed:
    {
      value = m_baseStats.skillSpeed;
      break;
    }

    case Common::BaseParam::SpellSpeed:
    {
      value = m_baseStats.spellSpeed;
      break;
    }

    case Common::BaseParam::CriticalHit:
    {
      value = m_baseStats.critHitRate;
      break;
    }

    case Common::BaseParam::Defense:
    {
      value = m_baseStats.defense;
      break;
    }

    case Common::BaseParam::MagicDefense:
    {
      value = m_baseStats.magicDefense;
      break;
    }

    case Common::BaseParam::Tenacity:
    {
      value = m_baseStats.tenacity;
      break;
    }

    // todo: not sure if this is right?
    case Common::BaseParam::DirectHitRate:
    {
      value = m_baseStats.accuracy;
      break;
    }

    default:
      break;
  }

  return value + getBonusStat( baseParam );
}
