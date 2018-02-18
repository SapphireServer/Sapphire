#include "GameObject.h"

#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>

#include "Player.h"
#include "Actor.h"
#include "BattleNpc.h"
#include "EventNpc.h"

Core::Entity::GameObject::GameObject( ObjKind type ) :
   m_objKind( type )
{

}

uint32_t Core::Entity::GameObject::getId() const
{
   return m_id;
}

Core::Entity::GameObject::ObjKind Core::Entity::GameObject::getObjKind() const
{
   return m_objKind;
}

Core::Common::FFXIVARR_POSITION3& Core::Entity::GameObject::getPos()
{
   return m_pos;
}

void Core::Entity::GameObject::setPos( float x, float y, float z )
{
   m_pos.x = x;
   m_pos.y = y;
   m_pos.z = z;
}

void Core::Entity::GameObject::setPos( const Core::Common::FFXIVARR_POSITION3& pos )
{
   m_pos = pos;
}

float Core::Entity::GameObject::getRot() const
{
   return m_rot;
}

void Core::Entity::GameObject::setRot( float rot )
{
   m_rot = rot;
}

bool Core::Entity::GameObject::isPlayer() const
{
   return m_objKind == ObjKind::Player;
}

bool Core::Entity::GameObject::isBattleNpc() const
{
   return m_objKind == ObjKind::BattleNpc;
}

bool Core::Entity::GameObject::isEventNpc() const
{
   return m_objKind == ObjKind::EventNpc;
}

/*!
Add a given actor to the fitting in range set according to type
but also to the global actor map

\param ActorPtr to add
*/
void Core::Entity::GameObject::addInRangeGameObject( GameObjectPtr pGameObject )
{

   // if this is null, something went wrong
   assert( pGameObject );

   // add actor to in range set
   m_inRangeGameObjects.insert( { pGameObject } );

   if( pGameObject->isPlayer() )
   {
      auto pPlayer = pGameObject->getAsPlayer();

      // if actor is a player, add it to the in range player set
      m_inRangePlayers.insert( pGameObject->getAsPlayer() );
   }
}

/*!
Remove a given actor from the matching in range set according to type
but also to the global actor map

\param ActorPtr to remove
*/
void Core::Entity::GameObject::removeInRangeGameObject( GameObject& gameObject )
{
   // call virtual event
   onRemoveInRangeGameObject( gameObject );

   // remove actor from in range actor set
   m_inRangeGameObjects.erase( gameObject.shared_from_this() );

   // if actor is a player, despawn ourself for him
   // TODO: move to virtual onRemove?
   if( isPlayer() )
      gameObject.despawn( getAsPlayer() );

   if( gameObject.isPlayer() )
      m_inRangePlayers.erase( gameObject.getAsPlayer() );
}

/*! \return true if there is at least one actor in the in range set */
bool Core::Entity::GameObject::hasInRangeGameObject() const
{
   return ( m_inRangeGameObjects.size() > 0 );
}

void Core::Entity::GameObject::removeFromInRange()
{
   if( !hasInRangeGameObject() )
      return;

   for( auto& pCurAct : m_inRangeGameObjects )
   {
      pCurAct->removeInRangeGameObject( *this );
   }

}

/*! Clear the whole in range set, this does no cleanup */
void Core::Entity::GameObject::clearInRangeSet()
{
   m_inRangeGameObjects.clear();
   m_inRangePlayers.clear();
}

/*! \return list of actors currently in range */
std::set< Core::Entity::GameObjectPtr > Core::Entity::GameObject::getInRangeGameObjects( bool includeSelf )
{
   auto tempInRange = m_inRangeGameObjects;

   if( includeSelf )
      tempInRange.insert( { shared_from_this() } );

   return tempInRange;
}

/*!
check if a given actor is in the actors in range set

\param ActorPtr to be checked for
\return true if the actor was found
*/
bool Core::Entity::GameObject::isInRangeSet( GameObjectPtr pGameObject ) const
{
   return !( m_inRangeGameObjects.find( pGameObject ) == m_inRangeGameObjects.end() );
}

/*! \return ActorPtr of the closest actor in range, if none, nullptr */
Core::Entity::GameObjectPtr Core::Entity::GameObject::getClosestGameObject()
{
   if( m_inRangeGameObjects.empty() )
      // no actors in range, don't bother
      return nullptr;

   GameObjectPtr tmpActor = nullptr;

   // arbitrary high number
   float minDistance = 10000;

   for( const auto& pCurAct : m_inRangeGameObjects )
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

/*! \return pointer to this instance as ActorPtr */
Core::Entity::ActorPtr Core::Entity::GameObject::getAsActor()
{
   return boost::dynamic_pointer_cast< Entity::Actor, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::PlayerPtr Core::Entity::GameObject::getAsPlayer()
{
   if( !isPlayer() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::Player, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as BattleNpcPtr */
Core::Entity::BattleNpcPtr Core::Entity::GameObject::getAsBattleNpc()
{
   if( !isBattleNpc() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::BattleNpc, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as EventNpcPtr */
Core::Entity::EventNpcPtr Core::Entity::GameObject::getAsEventNpc()
{
   if( !isEventNpc() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::EventNpc, Entity::GameObject >( shared_from_this() );
}
