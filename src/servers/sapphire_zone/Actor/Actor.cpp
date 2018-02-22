#include "Actor.h"

#include <common/Network/PacketContainer.h>
#include <common/Network/GamePacket.h>
#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>

#include "Chara.h"
#include "Network/GameConnection.h"
#include "Player.h"
#include "ServerZone.h"
#include "Session.h"

extern Core::ServerZone g_serverZone;

Core::Entity::Actor::Actor( ObjKind type ) :
   m_objKind( type )
{

}

uint32_t Core::Entity::Actor::getId() const
{
   return m_id;
}

Core::Entity::Actor::ObjKind Core::Entity::Actor::getObjKind() const
{
   return m_objKind;
}

Core::Common::FFXIVARR_POSITION3& Core::Entity::Actor::getPos()
{
   return m_pos;
}

void Core::Entity::Actor::setPos( float x, float y, float z )
{
   m_pos.x = x;
   m_pos.y = y;
   m_pos.z = z;
}

void Core::Entity::Actor::setPos( const Core::Common::FFXIVARR_POSITION3& pos )
{
   m_pos = pos;
}

float Core::Entity::Actor::getRot() const
{
   return m_rot;
}

void Core::Entity::Actor::setRot( float rot )
{
   m_rot = rot;
}

bool Core::Entity::Actor::isPlayer() const
{
   return m_objKind == ObjKind::Player;
}

/*! \return pointer to this instance as ActorPtr */
Core::Entity::CharaPtr Core::Entity::Actor::getAsChara()
{
   return boost::dynamic_pointer_cast< Entity::Chara, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::PlayerPtr Core::Entity::Actor::getAsPlayer()
{
   if( !isPlayer() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::Player, Entity::Actor >( shared_from_this() );
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
   m_inRangeActor.insert( pActor );

   if( pActor->isPlayer() )
   {
      auto pPlayer = pActor->getAsPlayer();

      pPlayer->spawn( getAsPlayer() );

      // if actor is a player, add it to the in range player set
      m_inRangePlayers.insert( pPlayer );
   }
}

/*!
Remove a given actor from the matching in range set according to type
but also to the global actor map

\param ActorPtr to remove
*/
void Core::Entity::Actor::removeInRangeActor( Actor& actor )
{
   // call virtual event
   onRemoveInRangeActor( actor );

   // remove actor from in range actor set
   m_inRangeActor.erase( actor.shared_from_this() );

   // if actor is a player, despawn ourself for him
   // TODO: move to virtual onRemove?
   if( isPlayer() )
      actor.despawn( getAsPlayer() );

   if( actor.isPlayer() )
      m_inRangePlayers.erase( actor.getAsPlayer() );
}

/*! \return true if there is at least one actor in the in range set */
bool Core::Entity::Actor::hasInRangeActor() const
{
   return ( m_inRangeActor.size() > 0 );
}

void Core::Entity::Actor::removeFromInRange()
{
   if( !hasInRangeActor() )
      return;

   Entity::ActorPtr pCurAct;

   for( auto& pCurAct : m_inRangeActor )
   {
      pCurAct->removeInRangeActor( *this );
   }

}

/*!
check if a given actor is in the actors in range set

\param ActorPtr to be checked for
\return true if the actor was found
*/
bool Core::Entity::Actor::isInRangeSet( ActorPtr pActor ) const
{
   return !( m_inRangeActor.find( pActor ) == m_inRangeActor.end() );
}

/*! \return ActorPtr of the closest actor in range, if none, nullptr */
Core::Entity::ActorPtr Core::Entity::Actor::getClosestActor()
{
   if( m_inRangeActor.empty() )
      // no actors in range, don't bother
      return nullptr;

   ActorPtr tmpActor = nullptr;

   // arbitrary high number
   float minDistance = 10000;

   for( const auto& pCurAct : m_inRangeActor )
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


/*! Clear the whole in range set, this does no cleanup */
void Core::Entity::Actor::clearInRangeSet()
{
   m_inRangeActor.clear();
   m_inRangePlayers.clear();
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

   for( const auto &pCurAct : m_inRangePlayers )
   {
      assert( pCurAct );
      pPacket->setValAt< uint32_t >( 0x04, m_id );
      pPacket->setValAt< uint32_t >( 0x08, pCurAct->getId() );
      // it might be that the player DC'd in which case the session would be invalid
      pCurAct->queuePacket( pPacket );
   }
}

/*! \return list of actors currently in range */
std::set< Core::Entity::ActorPtr > Core::Entity::Actor::getInRangeActors( bool includeSelf )
{
   auto tempInRange = m_inRangeActor;

   if( includeSelf )
      tempInRange.insert( shared_from_this() );

   return tempInRange;
}