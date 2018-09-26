#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Exd/ExdDataGenerated.h>
#include <utility>
#include <Network/CommonActorControl.h>


#include "Forwards.h"
#include "Action/Action.h"

#include "Zone/Zone.h"

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/UpdateHpMpTpPacket.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "StatusEffect/StatusEffect.h"
#include "Action/ActionCollision.h"
#include "ServerZone.h"
#include "Session.h"
#include "Math/CalcBattle.h"
#include "Chara.h"
#include "Player.h"
#include "Zone/TerritoryMgr.h"
#include "Framework.h"
#include "Common.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;

Core::Entity::Chara::Chara( ObjKind type ) :
  Actor( type ),
  m_pose( 0 ),
  m_targetId( INVALID_GAME_OBJECT_ID )
{
  // initialize the free slot queue
  for( uint8_t i = 0; i < MAX_STATUS_EFFECTS; i++ )
  {
    m_statusEffectFreeSlotQueue.push( i );
  }
}

Core::Entity::Chara::~Chara()
{
}

/*! \return the actors name */
std::string Core::Entity::Chara::getName() const
{
  return std::string( m_name );
}


/*! \return current stance of the actors */
Core::Common::Stance Core::Entity::Chara::getStance() const
{
  return m_currentStance;
}

/*! \return actor stats */
Core::Entity::Chara::ActorStats Core::Entity::Chara::getStats() const
{
  return m_baseStats;
}

/*! \return current HP */
uint32_t Core::Entity::Chara::getHp() const
{
  return m_hp;
}

/*! \return current MP */
uint32_t Core::Entity::Chara::getMp() const
{
  return m_mp;
}

/*! \return current TP */
uint16_t Core::Entity::Chara::getTp() const
{
  return m_tp;
}

/*! \return current GP */
uint16_t Core::Entity::Chara::getGp() const
{
  return m_gp;
}

/*! \return current invincibility type */
InvincibilityType Core::Entity::Chara::getInvincibilityType() const
{
  return m_invincibilityType;
}

/*! \return current class or job */
Core::Common::ClassJob Core::Entity::Chara::getClass() const
{
  return m_class;
}

/*! \return current class or job as int32_t ( this feels pointless ) */
uint8_t Core::Entity::Chara::getClassAsInt() const
{
  return static_cast< uint8_t >( m_class );
}

/*! \param ClassJob to set */
void Core::Entity::Chara::setClass( Common::ClassJob classJob )
{
  m_class = classJob;
}

/*! \param Id of the target to set */
void Core::Entity::Chara::setTargetId( uint64_t targetId )
{
  m_targetId = targetId;
}

/*! \return Id of the current target */
uint64_t Core::Entity::Chara::getTargetId() const
{
  return m_targetId;
}

/*! \return True if the actor is alive */
bool Core::Entity::Chara::isAlive() const
{
  return ( m_hp > 0 );
}

/*! \return max hp for the actor */
uint32_t Core::Entity::Chara::getMaxHp() const
{
  return m_baseStats.max_hp;
}

/*! \return max mp for the actor */
uint32_t Core::Entity::Chara::getMaxMp() const
{
  return m_baseStats.max_mp;
}

/*! \return reset hp to current max hp */
void Core::Entity::Chara::resetHp()
{
  m_hp = getMaxHp();
  sendStatusUpdate( true );
}

/*! \return reset mp to current max mp */
void Core::Entity::Chara::resetMp()
{
  m_mp = getMaxMp();
  sendStatusUpdate( true );
}

/*! \param hp amount to set ( caps to maxHp ) */
void Core::Entity::Chara::setHp( uint32_t hp )
{
  m_hp = hp < getMaxHp() ? hp : getMaxHp();
  sendStatusUpdate( true );
}

/*! \param mp amount to set ( caps to maxMp ) */
void Core::Entity::Chara::setMp( uint32_t mp )
{
  m_mp = mp < getMaxMp() ? mp : getMaxMp();
  sendStatusUpdate( true );
}

/*! \param gp amount to set*/
void Core::Entity::Chara::setGp( uint32_t gp )
{
  m_gp = gp;
  sendStatusUpdate( true );
}

/*! \param type invincibility type to set */
void Core::Entity::Chara::setInvincibilityType( Common::InvincibilityType type )
{
  m_invincibilityType = type;
}

/*! \return current status of the actor */
Core::Common::ActorStatus Core::Entity::Chara::getStatus() const
{
  return m_status;
}

/*! \param status to set */
void Core::Entity::Chara::setStatus( ActorStatus status )
{
  m_status = status;
}

/*!
Performs necessary steps to mark an actor dead.
Sets hp/mp/tp, sets status, plays animation and fires onDeath event
*/
void Core::Entity::Chara::die()
{
  m_status = ActorStatus::Dead;
  m_hp = 0;
  m_mp = 0;
  m_tp = 0;

  // fire onDeath event
  onDeath();

  // if the actor is a player, the update needs to be send to himself too
  bool selfNeedsUpdate = isPlayer();

  FFXIVPacketBasePtr packet = makeActorControl142( m_id, SetStatus, static_cast< uint8_t >( ActorStatus::Dead ) );
  sendToInRangeSet( packet, selfNeedsUpdate );

  // TODO: not all actor show the death animation when they die, some quest npcs might just despawn
  //       although that might be handled by setting the HP to 1 and doing some script magic

  FFXIVPacketBasePtr packet1 = makeActorControl142( m_id, DeathAnimation, 0, 0, 0, 0x20 );
  sendToInRangeSet( packet1, selfNeedsUpdate );

}

/*!
Calculates and sets the rotation to look towards a specified
position

\param Position to look towards
*/
bool Core::Entity::Chara::face( const Common::FFXIVARR_POSITION3& p )
{
  float oldRot = getRot();
  float rot = Math::Util::calcAngFrom( getPos().x, getPos().z, p.x, p.z );
  float newRot = PI - rot + ( PI / 2 );

  m_pCell = nullptr;

  setRot( newRot );

  return oldRot != newRot ? true : false;
}

/*!
Set and propagate the actor stance to in range players
( not the actor himself )

\param stance to set
*/
void Core::Entity::Chara::setStance( Stance stance )
{
  m_currentStance = stance;

  FFXIVPacketBasePtr packet = makeActorControl142( m_id, ToggleWeapon, stance, 0 );
  sendToInRangeSet( packet );
}

/*!
Check if an action is queued for execution, if so update it
and if fully performed, clean up again.

\return true if a queued action has been updated
*/
bool Core::Entity::Chara::checkAction()
{

  if( m_pCurrentAction == nullptr )
    return false;

  if( m_pCurrentAction->update() )
    m_pCurrentAction.reset();

  return true;

}

/*!
Change the current target and propagate to in range players

\param target actor id
*/
void Core::Entity::Chara::changeTarget( uint64_t targetId )
{
  setTargetId( targetId );
  FFXIVPacketBasePtr packet = makeActorControl144( m_id, SetTarget, 0, 0, 0, 0, targetId );
  sendToInRangeSet( packet );
}

/*!
Dummy function \return 0
*/
uint8_t Core::Entity::Chara::getLevel() const
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
void Core::Entity::Chara::takeDamage( uint32_t damage )
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
    }
  }
  else
    m_hp -= damage;

  sendStatusUpdate( false );
}

/*!
Let an actor get healed and perform necessary steps
according to resulting hp, propagates new hp value to players
in range

\param amount of hp to be healed
*/
void Core::Entity::Chara::heal( uint32_t amount )
{
  if( ( m_hp + amount ) > getMaxHp() )
  {
    m_hp = getMaxHp();
  }
  else
    m_hp += amount;

  sendStatusUpdate( false );
}

/*!
Send an HpMpTp update to players in range ( and potentially to self )
TODO: poor naming, should be changed. Status is not HP. Also should be virtual
so players can have their own version and we can abolish the param.

\param true if the update should also be sent to the actor ( player ) himself
*/
void Core::Entity::Chara::sendStatusUpdate( bool toSelf )
{
  FFXIVPacketBasePtr packet = boost::make_shared< UpdateHpMpTpPacket >( *this );
  sendToInRangeSet( packet );
}

/*! \return ActionPtr of the currently registered action, or nullptr */
Core::Action::ActionPtr Core::Entity::Chara::getCurrentAction() const
{
  return m_pCurrentAction;
}

/*! \param ActionPtr of the action to be registered */
void Core::Entity::Chara::setCurrentAction( Core::Action::ActionPtr pAction )
{
  m_pCurrentAction = pAction;
}

/*!
Autoattack prototype implementation
TODO: move the check if the autoAttack can be performed to the callee
also rename autoAttack to autoAttack as that is more elaborate
On top of that, this only solves attacks from melee classes.
Will have to be extended for ranged attacks.

\param ActorPtr the autoAttack is performed on
*/
void Core::Entity::Chara::autoAttack( CharaPtr pTarget )
{

  uint64_t tick = Util::getTimeMs();

  if( ( tick - m_lastAttack ) > 2500 )
  {
    pTarget->onActionHostile( *this );
    m_lastAttack = tick;
    srand( static_cast< uint32_t >( tick ) );

    uint16_t damage = static_cast< uint16_t >( 10 + rand() % 12 );
    uint32_t variation = static_cast< uint32_t >( 0 + rand() % 4 );

    auto effectPacket = boost::make_shared< Server::EffectPacket >( getId(), pTarget->getId(), 0x336 );
    effectPacket->setRotation( Math::Util::floatToUInt16Rot( getRot() ) );

    Server::EffectEntry effectEntry{};
    effectEntry.value = damage;
    effectEntry.effectType = ActionEffectType::Damage;
    effectEntry.hitSeverity = static_cast< ActionHitSeverityType >( variation );

    effectPacket->addEffect( effectEntry );

    sendToInRangeSet( effectPacket );

    if( isPlayer() )
      getAsPlayer()->queuePacket( effectPacket );

    pTarget->takeDamage( damage );
  }
}

/*!
ChaiScript Skill Handler.

\param GamePacketPtr to send
\param bool should be send to self?
*/
void Core::Entity::Chara::handleScriptSkill( uint32_t type, uint16_t actionId, uint64_t param1,
                                             uint64_t param2, Entity::Chara& target )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  if( isPlayer() )
  {
    getAsPlayer()->sendDebug( std::to_string( target.getId() ) );
    getAsPlayer()->sendDebug( "Handle script skill type: " + std::to_string( type ) );
  }

  auto actionInfoPtr = pExdData->get< Core::Data::Action >( actionId );

  // Todo: Effect packet generator. 90% of this is basically setting params and it's basically unreadable.
  // Prepare packet. This is seemingly common for all packets in the action handler.

  auto effectPacket = boost::make_shared< Server::EffectPacket >( getId(), target.getId(), actionId );
  effectPacket->setRotation( Math::Util::floatToUInt16Rot( getRot() ) );

  // Todo: for each actor, calculate how much damage the calculated value should deal to them - 2-step damage calc. we only have 1-step
  switch( type )
  {

    case ActionEffectType::Damage:
    {
      Server::EffectEntry effectEntry{};
      effectEntry.value = static_cast< uint16_t >( param1 );
      effectEntry.effectType = ActionEffectType::Damage;
      effectEntry.hitSeverity = ActionHitSeverityType::NormalDamage;

      effectPacket->addEffect( effectEntry );

      if( ( actionInfoPtr->castType == 1 && actionInfoPtr->effectRange != 0 ) ||
	  ( actionInfoPtr->castType != 1 ) )
      {
        // If action on this specific target is valid...
        if( isPlayer() && !ActionCollision::isActorApplicable( target, TargetFilter::Enemies ) )
          break;

        sendToInRangeSet( effectPacket, true );

        if( target.isAlive() )
          target.onActionHostile( *this );

        target.takeDamage( static_cast< uint32_t >( param1 ) );

      }
      else
      {

        auto actorsCollided = ActionCollision::getActorsHitFromAction( target.getPos(), getInRangeActors( true ),
                                                                       actionInfoPtr, TargetFilter::Enemies );

        for( const auto& pHitActor : actorsCollided )
        {
          effectPacket->setTargetActor( pHitActor->getId() );

          // todo: send to range of what? ourselves? when mob script hits this is going to be lacking
          sendToInRangeSet( effectPacket, true );


          if( pHitActor->getAsChara()->isAlive() )
            pHitActor->getAsChara()->onActionHostile( *this );

          pHitActor->getAsChara()->takeDamage( static_cast< uint32_t >( param1 ) );

          // Debug
          if( isPlayer() )
          {
            if( pHitActor->isPlayer() )
              getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) +
                                        " (" + pHitActor->getAsChara()->getName() + ")" );
            else
              getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) );
          }
        }
      }

      break;
    }

    case ActionEffectType::Heal:
    {
      uint32_t calculatedHeal = Math::CalcBattle::calculateHealValue( getAsPlayer(),
                                                                      static_cast< uint32_t >( param1 ) );

      Server::EffectEntry effectEntry{};
      effectEntry.value = calculatedHeal;
      effectEntry.effectType = ActionEffectType::Heal;
      effectEntry.hitSeverity = ActionHitSeverityType::NormalHeal;

      effectPacket->addEffect( effectEntry );

      if( ( actionInfoPtr->castType == 1 && actionInfoPtr->effectRange != 0 ) || actionInfoPtr->castType != 1 )
      {
        if( isPlayer() && !ActionCollision::isActorApplicable( target, TargetFilter::Allies ) )
          break;

        sendToInRangeSet( effectPacket, true );
        target.heal( calculatedHeal );
      }
      else
      {
        // todo: get proper packets: the following was just kind of thrown together from what we know.
        // atm buggy (packets look "delayed" from client)

        auto actorsCollided = ActionCollision::getActorsHitFromAction( target.getPos(), getInRangeActors( true ),
                                                                       actionInfoPtr, TargetFilter::Allies );

        for( auto pHitActor : actorsCollided )
        {
          effectPacket->setTargetActor( pHitActor->getId() );

          sendToInRangeSet( effectPacket, true );
          pHitActor->getAsChara()->heal( calculatedHeal );

          // Debug
          if( isPlayer() )
          {
            if( pHitActor->isPlayer() )
              getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) +
                                        " (" + pHitActor->getAsChara()->getName() + ")" );
            else
              getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) );
          }
        }
      }
      break;
    }

    default:
      break;
  }
}

/*! \param StatusEffectPtr to be applied to the actor */
void Core::Entity::Chara::addStatusEffect( StatusEffect::StatusEffectPtr pEffect )
{
  int8_t nextSlot = getStatusEffectFreeSlot();
  // if there is no slot left, do not add the effect
  if( nextSlot == -1 )
    return;

  pEffect->applyStatus();
  m_statusEffectMap[ nextSlot ] = pEffect;

  auto statusEffectAdd = makeZonePacket< FFXIVIpcAddStatusEffect >( getId() );

  statusEffectAdd->data().actor_id = pEffect->getTargetActorId();
  statusEffectAdd->data().actor_id1 = pEffect->getSrcActorId();
  statusEffectAdd->data().current_hp = getHp();
  statusEffectAdd->data().current_mp = getMp();
  statusEffectAdd->data().current_tp = getTp();
  statusEffectAdd->data().duration = static_cast< float >( pEffect->getDuration() ) / 1000;
  statusEffectAdd->data().effect_id = pEffect->getId();
  statusEffectAdd->data().effect_index = nextSlot;
  statusEffectAdd->data().max_hp = getMaxHp();
  statusEffectAdd->data().max_mp = getMaxMp();
  statusEffectAdd->data().max_something = 1;
  //statusEffectAdd->data().unknown2 = 28;
  statusEffectAdd->data().param = pEffect->getParam();

  sendToInRangeSet( statusEffectAdd, isPlayer() );
}

/*! \param StatusEffectPtr to be applied to the actor */
void Core::Entity::Chara::addStatusEffectById( uint32_t id, int32_t duration, Entity::Chara& source, uint16_t param )
{
  auto effect = StatusEffect::make_StatusEffect( id, source.getAsChara(), getAsChara(), duration, 3000 );
  effect->setParam( param );
  addStatusEffect( effect );
}

/*! \param StatusEffectPtr to be applied to the actor */
void Core::Entity::Chara::addStatusEffectByIdIfNotExist( uint32_t id, int32_t duration, Entity::Chara& source,
                                                         uint16_t param )
{
  if( hasStatusEffect( id ) )
    return;

  auto effect = StatusEffect::make_StatusEffect( id, source.getAsChara(), getAsChara(), duration, 3000 );
  effect->setParam( param );
  addStatusEffect( effect );

}

int8_t Core::Entity::Chara::getStatusEffectFreeSlot()
{
  int8_t freeEffectSlot = -1;

  if( m_statusEffectFreeSlotQueue.empty() )
    return freeEffectSlot;

  freeEffectSlot = m_statusEffectFreeSlotQueue.front();
  m_statusEffectFreeSlotQueue.pop();

  return freeEffectSlot;
}

void Core::Entity::Chara::statusEffectFreeSlot( uint8_t slotId )
{
  m_statusEffectFreeSlotQueue.push( slotId );
}

void Core::Entity::Chara::removeSingleStatusEffectById( uint32_t id )
{
  for( auto effectIt : m_statusEffectMap )
  {
    if( effectIt.second->getId() == id )
    {
      removeStatusEffect( effectIt.first );
      break;
    }
  }
}

void Core::Entity::Chara::removeStatusEffect( uint8_t effectSlotId )
{
  auto pEffectIt = m_statusEffectMap.find( effectSlotId );
  if( pEffectIt == m_statusEffectMap.end() )
    return;

  statusEffectFreeSlot( effectSlotId );

  auto pEffect = pEffectIt->second;
  pEffect->removeStatus();

  sendToInRangeSet( makeActorControl142( getId(), StatusEffectLose, pEffect->getId() ), isPlayer() );

  m_statusEffectMap.erase( effectSlotId );

  sendStatusEffectUpdate();
}

std::map< uint8_t, Core::StatusEffect::StatusEffectPtr > Core::Entity::Chara::getStatusEffectMap() const
{
  return m_statusEffectMap;
}

const uint8_t* Core::Entity::Chara::getLookArray() const
{
  return m_customize;
}

const uint32_t* Core::Entity::Chara::getModelArray() const
{
  return m_modelEquip;
}

uint8_t Core::Entity::Chara::getPose() const
{
  return m_pose;
}

void Core::Entity::Chara::setPose( uint8_t pose )
{
  m_pose = pose;
}

void Core::Entity::Chara::sendStatusEffectUpdate()
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
  for( auto effectIt : m_statusEffectMap )
  {
    float timeLeft = static_cast< float >( effectIt.second->getDuration() -
                                           ( currentTimeMs - effectIt.second->getStartTimeMs() ) ) / 1000;
    statusEffectList->data().effect[ slot ].duration = timeLeft;
    statusEffectList->data().effect[ slot ].effect_id = effectIt.second->getId();
    statusEffectList->data().effect[ slot ].sourceActorId = effectIt.second->getSrcActorId();
    slot++;
  }

  sendToInRangeSet( statusEffectList, isPlayer() );

}

void Core::Entity::Chara::updateStatusEffects()
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

    if( ( currentTimeMs - startTime ) > duration )
    {
      // remove status effect
      removeStatusEffect( effectIndex );
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
    sendToInRangeSet( makeActorControl142( getId(), HPFloatingText, 0,
                                           static_cast< uint8_t >( ActionEffectType::Damage ), thisTickDmg ) );
  }

  if( thisTickHeal != 0 )
  {
    heal( thisTickDmg );
    sendToInRangeSet( makeActorControl142( getId(), HPFloatingText, 0,
                                           static_cast< uint8_t >( ActionEffectType::Heal ), thisTickHeal ) );
  }
}

bool Core::Entity::Chara::hasStatusEffect( uint32_t id )
{
  if( m_statusEffectMap.find( id ) != m_statusEffectMap.end() )
    return true;
  return false;
}

