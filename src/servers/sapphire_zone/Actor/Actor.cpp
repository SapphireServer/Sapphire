#include "Actor.h"

#include <Network/PacketContainer.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>

#include "Action/Action.h"
#include "Action/ActionCollision.h"

#include "Zone/Zone.h"

#include "Network/GameConnection.h"

#include "Chara.h"
#include "EventObject.h"
#include "Player.h"

#include "ServerZone.h"
#include "Session.h"

#include "Zone/TerritoryMgr.h"

#include "StatusEffect/StatusEffect.h"

#include "Math/CalcBattle.h"

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network::Packets;
//using namespace Core::Network::Packets::Server;

Core::Entity::Actor::Actor( ObjKind type ) :
   m_objKind( type )
{

}

uint32_t Core::Entity::Actor::getId() const
{
   return m_id;
}

void Core::Entity::Actor::setId( uint32_t id )
{
   m_id = id;
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
   m_pCurrentZone->updateActorPosition( *this );
}

void Core::Entity::Actor::setPos( const Core::Common::FFXIVARR_POSITION3& pos )
{
   m_pos = pos;
   m_pCurrentZone->updateActorPosition( *this );
}

float Core::Entity::Actor::getRot() const
{
   return m_rot;
}

void Core::Entity::Actor::setRot( float rot )
{
   m_rot = rot;
}

bool Core::Entity::Actor::isChara() const
{
   return isPlayer() || isBattleNpc() || isEventNpc() || isRetainer() || isCompanion();
}

bool Core::Entity::Actor::isPlayer() const
{
   return m_objKind == ObjKind::Player;
}

bool Core::Entity::Actor::isEventNpc() const
{
   return m_objKind == ObjKind::EventNpc;
}

bool Core::Entity::Actor::isBattleNpc() const
{
   return m_objKind == ObjKind::BattleNpc;
}

bool Core::Entity::Actor::isRetainer() const
{
   return m_objKind == ObjKind::Retainer;
}

bool Core::Entity::Actor::isCompanion() const
{
   return m_objKind == ObjKind::Companion;
}

bool Core::Entity::Actor::isEventObj() const
{
   return m_objKind == ObjKind::EventObj;
}

bool Core::Entity::Actor::isHousingEventObj() const
{
   return m_objKind == ObjKind::Housing;
}

bool Core::Entity::Actor::isAetheryte() const
{
   return m_objKind == ObjKind::Aetheryte;
}


/*! \return pointer to this instance as ActorPtr */
Core::Entity::CharaPtr Core::Entity::Actor::getAsChara()
{
   if( !isChara() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::Chara, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::PlayerPtr Core::Entity::Actor::getAsPlayer()
{
   if( !isPlayer() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::Player, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Core::Entity::EventObjectPtr Core::Entity::Actor::getAsEventObj()
{
   if( !isEventObj() )
      return nullptr;
   return boost::dynamic_pointer_cast< Entity::EventObject, Entity::Actor >( shared_from_this() );
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

      spawn( pPlayer );

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
   auto pServerZone = g_fw.get< ServerZone >();
   if( bToSelf && isPlayer() )
   {
      auto pPlayer = getAsPlayer();

      auto pSession = pServerZone->getSession( pPlayer->getId() );

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

/*! \return InstanceContentPtr to the current instance, nullptr if not an instance or not set */
Core::InstanceContentPtr Core::Entity::Actor::getCurrentInstance() const
{
   if( m_pCurrentZone )
      return m_pCurrentZone->getAsInstanceContent();

   return nullptr;
}

/*!
Get the current cell of a region the actor is in

\return Cell*
*/
Core::Cell * Core::Entity::Actor::getCellPtr()
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
