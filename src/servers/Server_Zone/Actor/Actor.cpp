#include <src/servers/Server_Common/Util/Util.h>
#include <src/servers/Server_Common/Util/UtilMath.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Network/GamePacket.h>

#include "src/servers/Server_Zone/Forwards.h"
#include "src/servers/Server_Zone/Action/Action.h"

#include "src/servers/Server_Zone/Zone/Zone.h"

#include "src/servers/Server_Zone/Network/GameConnection.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket144.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/UpdateHpMpTpPacket.h"

#include "src/servers/Server_Zone/StatusEffect/StatusEffectContainer.h"
#include "src/servers/Server_Zone/StatusEffect/StatusEffect.h"
#include "src/servers/Server_Zone/Action/ActionCollision.h"
#include "src/servers/Server_Zone/ServerZone.h"
#include "src/servers/Server_Zone/Session.h"
#include "src/servers/Server_Zone/Math/CalcBattle.h"
#include "Actor.h"
#include "Player.h"

extern Core::ServerZone g_serverZone;
extern Core::Data::ExdData g_exdData;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Entity::Actor::Actor()
{
}

Core::Entity::Actor::~Actor()
{
}

/*! \return the id of the actor */
uint32_t Core::Entity::Actor::getId() const
{
   return m_id;
}

/*! \return the actors position object */
Core::Common::FFXIVARR_POSITION3& Core::Entity::Actor::getPos()
{
   return m_pos;
}
/*! \return the actors name */
std::string Core::Entity::Actor::getName() const
{
   return std::string( m_name );
}

/*! \return true if the actor is of type player */
bool Core::Entity::Actor::isPlayer() const
{
   return m_type == ActorType::Player;
}

/*! \return true if the actor is of type mob */
bool Core::Entity::Actor::isMob() const
{
   return m_type == ActorType::BattleNpc;
}

/*! \return list of actors currently in range */
std::set< Core::Entity::ActorPtr > Core::Entity::Actor::getInRangeActors( bool includeSelf )
{
    auto tempInRange = m_inRangeActors;

    if( includeSelf )
        tempInRange.insert( shared_from_this() );

    return tempInRange;
}

/*! \return current stance of the actors */
Core::Entity::Actor::Stance Core::Entity::Actor::getStance() const
{
   return m_currentStance;
}

/*! \return actor stats */
Core::Entity::Actor::ActorStats Core::Entity::Actor::getStats() const
{
   return m_baseStats;
}

/*! \return current HP */
uint32_t Core::Entity::Actor::getHp() const
{
   return m_hp;
}

/*! \return current MP */
uint32_t Core::Entity::Actor::getMp() const
{
   return m_mp;
}

/*! \return current TP */
uint16_t Core::Entity::Actor::getTp() const
{
   return m_tp;
}

/*! \return current GP */
uint16_t Core::Entity::Actor::getGp() const
{
   return m_gp;
}

/*! \return current invincibility type */
InvincibilityType Core::Entity::Actor::getInvincibilityType() const
{
   return m_invincibilityType;
}

/*! \return current class or job */
Core::Common::ClassJob Core::Entity::Actor::getClass() const
{
   return m_class;
}

/*! \return current class or job as int32_t ( this feels pointless ) */
uint8_t Core::Entity::Actor::getClassAsInt() const
{
   return static_cast< uint8_t >( m_class );
}

/*! \param ClassJob to set */
void Core::Entity::Actor::setClass( Common::ClassJob classJob )
{
   m_class = classJob;
}

/*! \param Id of the target to set */
void Core::Entity::Actor::setTargetId( uint64_t targetId )
{
   m_targetId = targetId;
}

/*! \return Id of the current target */
uint64_t Core::Entity::Actor::getTargetId() const
{
   return m_targetId;
}

/*! \return True if the actor is alive */
bool Core::Entity::Actor::isAlive() const
{
   return ( m_hp > 0 );
}

/*! \return max hp for the actor */
uint32_t Core::Entity::Actor::getMaxHp() const
{
   return m_baseStats.max_hp;
}

/*! \return max mp for the actor */
uint32_t Core::Entity::Actor::getMaxMp() const
{
   return m_baseStats.max_mp;
}

/*! \return reset hp to current max hp */
void Core::Entity::Actor::resetHp()
{
   m_hp = getMaxHp();
   sendStatusUpdate( true );
}

/*! \return reset mp to current max mp */
void Core::Entity::Actor::resetMp()
{
   m_mp = getMaxMp();
   sendStatusUpdate( true );
}

/*! \param hp amount to set ( caps to maxHp ) */
void Core::Entity::Actor::setHp( uint32_t hp )
{
   m_hp = hp < getMaxHp() ? hp : getMaxHp();
   sendStatusUpdate( true );
}

/*! \param mp amount to set ( caps to maxMp ) */
void Core::Entity::Actor::setMp( uint32_t mp )
{
   m_mp = mp < getMaxMp() ? mp : getMaxMp();
   sendStatusUpdate( true );
}

/*! \param gp amount to set*/
void Core::Entity::Actor::setGp( uint32_t gp )
{
   m_gp = gp;
   sendStatusUpdate( true );
}

/*! \param type invincibility type to set */
void Core::Entity::Actor::setInvincibilityType( Common::InvincibilityType type )
{
   m_invincibilityType = type;
}


/*! \return current status of the actor */
Core::Entity::Actor::ActorStatus Core::Entity::Actor::getStatus() const
{
   return m_status;
}

/*! \param status to set */
void Core::Entity::Actor::setStatus( ActorStatus status )
{
   m_status = status;
}

/*!
Performs necessary steps to mark an actor dead.
Sets hp/mp/tp, sets status, plays animation and fires onDeath event
*/
void Core::Entity::Actor::die()
{
   m_status = ActorStatus::Dead;
   m_hp = 0;
   m_mp = 0;
   m_tp = 0;

   // fire onDeath event
   onDeath();

   // if the actor is a player, the update needs to be send to himself too
   bool selfNeedsUpdate = isPlayer();

   sendToInRangeSet( ActorControlPacket142( m_id, SetStatus, static_cast< uint8_t >( ActorStatus::Dead ) ), selfNeedsUpdate );

   // TODO: not all actor show the death animation when they die, some quest npcs might just despawn
   //       although that might be handled by setting the HP to 1 and doing some script magic
   sendToInRangeSet( ActorControlPacket142( m_id, DeathAnimation, 0, 0, 0, 0x20 ), selfNeedsUpdate );

}

/*!
Calculates and sets the rotation to look towards a specified
position

\param Position to look towards
*/
bool Core::Entity::Actor::face( const Common::FFXIVARR_POSITION3& p )
{
   float oldRot = getRotation();
   float rot = Math::Util::calcAngFrom( getPos().x, getPos().z, p.x, p.z );
   float newRot = PI - rot + ( PI / 2 );

   m_pCell = nullptr;

   setRotation( newRot );

   return oldRot != newRot ? true : false;
}

/*!
Sets the actors position and notifies the zone to propagate the change

\param Position to set
*/
void Core::Entity::Actor::setPosition( const Common::FFXIVARR_POSITION3& pos )
{
   m_pos = pos;
   m_pCurrentZone->changeActorPosition( shared_from_this() );
}

void Core::Entity::Actor::setPosition( float x, float y, float z )
{
   m_pos.x = x;
   m_pos.y = y;
   m_pos.z = z;
   m_pCurrentZone->changeActorPosition( shared_from_this() );
}

/*!
Set and propagate the actor stance to in range players
( not the actor himself )

\param stance to set
*/
void Core::Entity::Actor::setStance( Stance stance )
{
   m_currentStance = stance;

   sendToInRangeSet( ActorControlPacket142( m_id, ToggleAggro, stance, 1 ) );
}

/*!
Check if an action is queued for execution, if so update it
and if fully performed, clean up again.

\return true if a queued action has been updated
*/
bool Core::Entity::Actor::checkAction()
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
void Core::Entity::Actor::changeTarget( uint64_t targetId )
{
   setTargetId( targetId );

   sendToInRangeSet( ActorControlPacket144( m_id, SetTarget,
                                            0, 0, 0, 0, targetId ) );
}

/*!
Dummy function \return 0
*/
uint8_t Core::Entity::Actor::getLevel() const
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
void Core::Entity::Actor::takeDamage( uint32_t damage )
{
   if( damage >= m_hp )
   {
      switch( m_invincibilityType ) { 
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
void Core::Entity::Actor::heal( uint32_t amount )
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
void Core::Entity::Actor::sendStatusUpdate( bool toSelf )
{
   UpdateHpMpTpPacket updateHpPacket( shared_from_this() );
   sendToInRangeSet( updateHpPacket );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::PlayerPtr Core::Entity::Actor::getAsPlayer()
{
   return boost::dynamic_pointer_cast< Entity::Player, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as BattleNpcPtr */
Core::Entity::BattleNpcPtr Core::Entity::Actor::getAsBattleNpc()
{
   return boost::reinterpret_pointer_cast< Entity::BattleNpc, Entity::Actor >( shared_from_this() );
}

/*! \return ActionPtr of the currently registered action, or nullptr */
Core::Action::ActionPtr Core::Entity::Actor::getCurrentAction() const
{
   return m_pCurrentAction;
}

/*! \param ActionPtr of the action to be registered */
void Core::Entity::Actor::setCurrentAction( Core::Action::ActionPtr pAction )
{
   m_pCurrentAction = pAction;
}

/*!
check if a given actor is in the actors in range set

\param ActorPtr to be checked for
\return true if the actor was found
*/
bool Core::Entity::Actor::isInRangeSet( ActorPtr pActor ) const
{
   return !( m_inRangeActors.find( pActor ) == m_inRangeActors.end() );
}

/*! \return ActorPtr of the closest actor in range, if none, nullptr */
Core::Entity::ActorPtr Core::Entity::Actor::getClosestActor()
{
   if( m_inRangeActors.empty() )
      // no actors in range, don't bother
      return nullptr;

   ActorPtr tmpActor = nullptr;

   // arbitrary high number
   float minDistance = 10000;

   for( auto pCurAct : m_inRangeActors )
   {
      float distance = Math::Util::distance( getPos().x,
                                             getPos().y,
                                             getPos().z,
                                             pCurAct->getPos().x,
                                             pCurAct->getPos().y,
                                             pCurAct->getPos().z );

      if( distance < minDistance )
      {
         minDistance = distance;
         tmpActor = pCurAct;
      }
   }

   return tmpActor;
}

/*!
Send a packet to all players in range, potentially to self if set and is player

\param GamePacketPtr to send
\param bool should be send to self?
*/
void Core::Entity::Actor::sendToInRangeSet( Network::Packets::GamePacketPtr pPacket, bool bToSelf )
{

   if( bToSelf && isPlayer() )
   {
      auto pPlayer = getAsPlayer();

      auto pSession = g_serverZone.getSession( pPlayer->getId() );

      // it might be that the player DC'd in which case the session would be invalid
      if( pSession )
         pSession->getZoneConnection()->queueOutPacket( pPacket );
   }

   if( m_inRangePlayers.empty() )
      return;

   for( auto pCurAct : m_inRangePlayers )
   {
      assert( pCurAct );
      pPacket->setValAt<uint32_t>( 0x04, m_id );
      pPacket->setValAt<uint32_t>( 0x08, pCurAct->m_id );
      // it might be that the player DC'd in which case the session would be invalid
      pCurAct->queuePacket( pPacket );
   }
}

/*!
Add a given actor to the fitting in range set according to type
but also to the global actor map

\param ActorPtr to add
*/
void Core::Entity::Actor::addInRangeActor( ActorPtr pActor )
{

   // if this is null, something went wrong
   assert( pActor );

   // add actor to in range set
   m_inRangeActors.insert( pActor );

   if( pActor->isPlayer() )
   {
      auto pPlayer = pActor->getAsPlayer();

      // if actor is a player, add it to the in range player set
      m_inRangePlayers.insert( pPlayer );
   }

   m_inRangeActorMap[pActor->getId()] = pActor;
}

/*!
Remove a given actor from the fitting in range set according to type
but also to the global actor map

\param ActorPtr to remove
*/
void Core::Entity::Actor::removeInRangeActor( ActorPtr pActor )
{
   // if this is null, something went wrong
   assert( pActor );

   // call virtual event
   onRemoveInRangeActor( pActor );

   // remove actor from in range actor set
   m_inRangeActors.erase( pActor );

   // if actor is a player, despawn ourself for him
   // TODO: move to virtual onRemove?
   if( isPlayer() )
      pActor->despawn( shared_from_this() );

   if( pActor->isPlayer() )
   {
      auto pPlayer = pActor->getAsPlayer();
      m_inRangePlayers.erase( pPlayer );
   }

   m_inRangeActorMap.erase( pActor->getId() );
}

/*! \return true if there is at least one actor in the in range set */
bool Core::Entity::Actor::hasInRangeActor() const
{
   return ( m_inRangeActors.size() > 0 );
}

/*! Clear the whole in range set, this does no cleanup */
void Core::Entity::Actor::clearInRangeSet()
{
   m_inRangeActors.clear();
   m_inRangePlayers.clear();
   m_inRangeActorMap.clear();
}

/*! \return ZonePtr to the current zone, nullptr if not set */
Core::ZonePtr Core::Entity::Actor::getCurrentZone() const
{
   return m_pCurrentZone;
}

/*! \param ZonePtr to the zone to be set as current */
void Core::Entity::Actor::setCurrentZone( ZonePtr currZone )
{
   m_pCurrentZone = currZone;
}

/*!
Get the current cell of a region the actor is in

\return Cell*
*/
Core::Cell * Core::Entity::Actor::getCell() const
{
   return m_pCell;
}

/*!
Set the current cell the actor is in

\param Cell* for the cell to be set
*/
void Core::Entity::Actor::setCell( Cell * pCell )
{
   m_pCell = pCell;
}

/*!
Autoattack prototype implementation
TODO: move the check if the autoAttack can be performed to the callee
also rename autoAttack to autoAttack as that is more elaborate
On top of that, this only solves attacks from melee classes.
Will have to be extended for ranged attacks.

\param ActorPtr the autoAttack is performed on
*/
void Core::Entity::Actor::autoAttack( ActorPtr pTarget )
{

   uint64_t tick = Util::getTimeMs();

   if( ( tick - m_lastAttack ) > 2500 )
   {
      pTarget->onActionHostile( shared_from_this() );
      m_lastAttack = tick;
      srand( static_cast< uint32_t >( tick ) );

      uint32_t damage = 10 + rand() % 12;
      uint32_t variation = 0 + rand() % 4;

      ZoneChannelPacket< FFXIVIpcEffect > effectPacket( getId() );
      effectPacket.data().targetId = pTarget->getId();
      effectPacket.data().actionAnimationId = 0x366;
      effectPacket.data().unknown_2 = variation;
//      effectPacket.data().unknown_3 = 1;
      effectPacket.data().actionTextId = 0x366;
      effectPacket.data().numEffects = 1;
      effectPacket.data().rotation = Math::Util::floatToUInt16Rot( getRotation() );
      effectPacket.data().effectTarget = pTarget->getId();
      effectPacket.data().effects[0].value = damage;
      effectPacket.data().effects[0].effectType = ActionEffectType::Damage;
      effectPacket.data().effects[0].hitSeverity = static_cast< ActionHitSeverityType >( variation );
      effectPacket.data().effects[0].unknown_3 = 7;

      sendToInRangeSet( effectPacket );

      if( this->isPlayer() )
         this->getAsPlayer()->queuePacket( effectPacket );

      pTarget->takeDamage( damage );
   }
}

/*!
ChaiScript Skill Handler.

\param GamePacketPtr to send
\param bool should be send to self?
*/
void Core::Entity::Actor::handleScriptSkill( uint32_t type, uint32_t actionId, uint64_t param1, uint64_t param2, Entity::Actor& pTarget )
{

   if ( isPlayer() )
   {
      getAsPlayer()->sendDebug( std::to_string( pTarget.getId() ) );
      getAsPlayer()->sendDebug( "Handle script skill type: " + std::to_string( type ) );
   }

   auto actionInfoPtr = g_exdData.getActionInfo( actionId );

   // Todo: Effect packet generator. 90% of this is basically setting params and it's basically unreadable.
   // Prepare packet. This is seemingly common for all packets in the action handler.

   ZoneChannelPacket< FFXIVIpcEffect > effectPacket( getId() );
   effectPacket.data().targetId = pTarget.getId();
   effectPacket.data().actionAnimationId = actionId;
   effectPacket.data().unknown_62 = 1; // Affects displaying action name next to number in floating text
   effectPacket.data().unknown_2 = 1;  // This seems to have an effect on the "double-cast finish" animation
   effectPacket.data().actionTextId = actionId;
   effectPacket.data().numEffects = 1;
   effectPacket.data().rotation = Math::Util::floatToUInt16Rot( getRotation() );
   effectPacket.data().effectTarget = pTarget.getId();

   // Todo: for each actor, calculate how much damage the calculated value should deal to them - 2-step damage calc. we only have 1-step
   switch ( type )
   {

   case ActionEffectType::Damage:
   {
      effectPacket.data().effects[0].value = static_cast< uint16_t >( param1 );
      effectPacket.data().effects[0].effectType = ActionEffectType::Damage;
      effectPacket.data().effects[0].hitSeverity = ActionHitSeverityType::NormalDamage;
      effectPacket.data().effects[0].unknown_3 = 7;

      if ( !actionInfoPtr->is_aoe )
      {
         // If action on this specific target is valid...
         if ( isPlayer() && !ActionCollision::isActorApplicable( pTarget.shared_from_this(), TargetFilter::Enemies ) )
            break;

         sendToInRangeSet( effectPacket, true );

         pTarget.takeDamage( static_cast< uint32_t >( param1 ) );

         if ( pTarget.isAlive() )
            pTarget.onActionHostile( shared_from_this() );
         
      }
      else
      {

         std::set< ActorPtr > actorsCollided = ActionCollision::getActorsHitFromAction( pTarget.getPos(), getInRangeActors( true ), actionInfoPtr, TargetFilter::Enemies );

         for ( auto pHitActor : actorsCollided )
         {
            effectPacket.data().targetId = pHitActor->getId();
            effectPacket.data().effectTarget = pHitActor->getId();

            sendToInRangeSet( effectPacket, true ); // todo: send to range of what? ourselves? when mob script hits this is going to be lacking

            pHitActor->takeDamage( static_cast< uint32_t >( param1 ) );

            if( pHitActor->isAlive() )
               pHitActor->onActionHostile( shared_from_this() );

            // Debug
            if ( isPlayer() ) 
            {
               if ( pHitActor->isPlayer() ) {
                  getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) + " (" + pHitActor->getName() + ")" );
               }
               else
                  getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) );
            }  
         }
      }

      break;
   }

   case ActionEffectType::Heal:
   {
      uint32_t calculatedHeal = Math::CalcBattle::calculateHealValue( getAsPlayer(), static_cast< uint32_t >( param1 ) );

      effectPacket.data().effects[0].value = calculatedHeal;
      effectPacket.data().effects[0].effectType = ActionEffectType::Heal;
      effectPacket.data().effects[0].hitSeverity = ActionHitSeverityType::NormalHeal;

      if ( !actionInfoPtr->is_aoe )
      {
         if ( isPlayer() && !ActionCollision::isActorApplicable( pTarget.shared_from_this(), TargetFilter::Allies ) )
            break;

         sendToInRangeSet( effectPacket, true );
         pTarget.heal( calculatedHeal );
      }
      else
      {
         // todo: get proper packets: the following was just kind of thrown together from what we know. atm buggy (packets look "delayed" from client)

         std::set< ActorPtr > actorsCollided = ActionCollision::getActorsHitFromAction( pTarget.getPos(), getInRangeActors( true ), actionInfoPtr, TargetFilter::Allies );

         for ( auto pHitActor : actorsCollided )
         {
            effectPacket.data().targetId = pTarget.getId();
            effectPacket.data().effectTarget = pHitActor->getId();

            sendToInRangeSet( effectPacket, true );
            pHitActor->heal( calculatedHeal );

            // Debug
            if ( isPlayer() )
            {
               if ( pHitActor->isPlayer() ) {
                  getAsPlayer()->sendDebug( "AoE hit actor " + std::to_string( pHitActor->getId() ) + " (" + pHitActor->getName() + ")" );
               }
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
void Core::Entity::Actor::addStatusEffect( StatusEffect::StatusEffectPtr pEffect )
{
   m_pStatusEffectContainer->addStatusEffect( pEffect );
}

/*! \param StatusEffectPtr to be applied to the actor */
void Core::Entity::Actor::addStatusEffectById( uint32_t id, int32_t duration, Entity::Actor& pSource, uint16_t param )
{
   StatusEffect::StatusEffectPtr effect( new StatusEffect::StatusEffect( id, pSource.shared_from_this(),
                                                                         shared_from_this(), duration, 3000 ) );
   effect->setParam( param );
   addStatusEffect( effect );
}

/*! \param StatusEffectPtr to be applied to the actor */
void Core::Entity::Actor::addStatusEffectByIdIfNotExist( uint32_t id, int32_t duration, Entity::Actor& pSource, uint16_t param )
{
   if( !m_pStatusEffectContainer->hasStatusEffect( id ) )
   {
      StatusEffect::StatusEffectPtr effect( new StatusEffect::StatusEffect( id, pSource.shared_from_this(),
                                                                            shared_from_this(), duration, 3000 ) );
      effect->setParam( param );
      addStatusEffect( effect );
   }
}

/*! \param Status that should be removed, based on its ID. */
void Core::Entity::Actor::removeSingleStatusEffectFromId( uint32_t id )
{
   m_pStatusEffectContainer->removeSingleStatusEffectFromId( id );
}

Core::StatusEffect::StatusEffectContainerPtr Core::Entity::Actor::getStatusEffectContainer() const
{
   return m_pStatusEffectContainer;
}