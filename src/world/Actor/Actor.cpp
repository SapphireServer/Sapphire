#include "Actor.h"

#include <Network/PacketContainer.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <utility>

#include "Territory/Zone.h"

#include "Network/GameConnection.h"

#include "Chara.h"
#include "EventObject.h"
#include "Player.h"
#include "BNpc.h"

#include "ServerMgr.h"
#include "Session.h"

#include "Manager/TerritoryMgr.h"

#include "StatusEffect/StatusEffect.h"

#include "Math/CalcBattle.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
//using namespace Sapphire::Network::Packets::Server;

Sapphire::Entity::Actor::Actor( ObjKind type ) :
  m_objKind( type )
{

}

uint32_t Sapphire::Entity::Actor::getId() const
{
  return m_id;
}

void Sapphire::Entity::Actor::setId( uint32_t id )
{
  m_id = id;
}

Sapphire::Common::ObjKind Sapphire::Entity::Actor::getObjKind() const
{
  return m_objKind;
}

Sapphire::Common::FFXIVARR_POSITION3& Sapphire::Entity::Actor::getPos()
{
  return m_pos;
}

void Sapphire::Entity::Actor::setPos( float x, float y, float z, bool broadcastUpdate )
{
  m_pos.x = x;
  m_pos.y = y;
  m_pos.z = z;

  if( broadcastUpdate )
    m_pCurrentZone->updateActorPosition( *this );
}

void Sapphire::Entity::Actor::setPos( const Sapphire::Common::FFXIVARR_POSITION3& pos, bool broadcastUpdate )
{
  m_pos = pos;

  if( broadcastUpdate )
    m_pCurrentZone->updateActorPosition( *this );
}

float Sapphire::Entity::Actor::getRot() const
{
  return m_rot;
}

void Sapphire::Entity::Actor::setRot( float rot )
{
  m_rot = rot;
}

bool Sapphire::Entity::Actor::isChara() const
{
  return isPlayer() || isBattleNpc() || isEventNpc() || isRetainer() || isCompanion();
}

bool Sapphire::Entity::Actor::isPlayer() const
{
  return m_objKind == ObjKind::Player;
}

bool Sapphire::Entity::Actor::isEventNpc() const
{
  return m_objKind == ObjKind::EventNpc;
}

bool Sapphire::Entity::Actor::isBattleNpc() const
{
  return m_objKind == ObjKind::BattleNpc;
}

bool Sapphire::Entity::Actor::isRetainer() const
{
  return m_objKind == ObjKind::Retainer;
}

bool Sapphire::Entity::Actor::isCompanion() const
{
  return m_objKind == ObjKind::Companion;
}

bool Sapphire::Entity::Actor::isEventObj() const
{
  return m_objKind == ObjKind::EventObj;
}

bool Sapphire::Entity::Actor::isHousingEventObj() const
{
  return m_objKind == ObjKind::Housing;
}

bool Sapphire::Entity::Actor::isAetheryte() const
{
  return m_objKind == ObjKind::Aetheryte;
}


/*! \return pointer to this instance as ActorPtr */
Sapphire::Entity::CharaPtr Sapphire::Entity::Actor::getAsChara()
{
  if( !isChara() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::Chara, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Sapphire::Entity::PlayerPtr Sapphire::Entity::Actor::getAsPlayer()
{
  if( !isPlayer() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::Player, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as EventObjPtr */
Sapphire::Entity::EventObjectPtr Sapphire::Entity::Actor::getAsEventObj()
{
  if( !isEventObj() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::EventObject, Entity::Actor >( shared_from_this() );
}

/*! \return pointer to this instance as BNpcPtr */
Sapphire::Entity::BNpcPtr Sapphire::Entity::Actor::getAsBNpc()
{
  if( !isBattleNpc() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::BNpc, Entity::Actor >( shared_from_this() );
}

/*!
Add a given actor to the fitting in range set according to type
but also to the global actor map

\param ActorPtr to add
*/
void Sapphire::Entity::Actor::addInRangeActor( ActorPtr pActor )
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
  else if( pActor->isBattleNpc() )
  {
    auto pBNpc = pActor->getAsBNpc();

    // if actor is a player, add it to the in range player set
    m_inRangeBNpc.insert( pBNpc );
  }
}

/*!
Remove a given actor from the matching in range set according to type
but also to the global actor map

\param ActorPtr to remove
*/
void Sapphire::Entity::Actor::removeInRangeActor( Actor& actor )
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

  if( actor.isBattleNpc() )
    m_inRangeBNpc.erase( actor.getAsBNpc() );
}

/*! \return true if there is at least one actor in the in range set */
bool Sapphire::Entity::Actor::hasInRangeActor() const
{
  return ( m_inRangeActor.size() > 0 );
}

void Sapphire::Entity::Actor::removeFromInRange()
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
bool Sapphire::Entity::Actor::isInRangeSet( ActorPtr pActor ) const
{
  return !( m_inRangeActor.find( pActor ) == m_inRangeActor.end() );
}


/*! \return ActorPtr of the closest actor in range, if none, nullptr */
Sapphire::Entity::CharaPtr Sapphire::Entity::Actor::getClosestChara()
{
  if( m_inRangeActor.empty() )
    // no actors in range, don't bother
    return nullptr;

  CharaPtr tmpActor = nullptr;

  // arbitrary high number
  float minDistance = 10000;

  for( const auto& pCurAct : m_inRangeActor )
  {
    float distance = Util::distance( getPos().x, getPos().y, getPos().z,
                                     pCurAct->getPos().x, pCurAct->getPos().y, pCurAct->getPos().z );

    if( distance < minDistance )
    {
      minDistance = distance;
      tmpActor = pCurAct->getAsChara();
    }
  }

  return tmpActor;
}

/*! Clear the whole in range set, this does no cleanup */
void Sapphire::Entity::Actor::clearInRangeSet()
{
  m_inRangeActor.clear();
  m_inRangePlayers.clear();
  m_inRangeBNpc.clear();
}

/*!
Send a packet to all players in range, potentially to self if set and is player

\param GamePacketPtr to send
\param bool should be send to self?
*/
void Sapphire::Entity::Actor::sendToInRangeSet( Network::Packets::FFXIVPacketBasePtr pPacket, bool bToSelf )
{
  if( bToSelf && isPlayer() )
  {
    auto pPlayer = getAsPlayer();
    pPlayer->queuePacket( pPacket );
  }

  if( m_inRangePlayers.empty() )
    return;

  pPacket->setSourceActor( m_id );

  for( const auto& pCurAct : m_inRangePlayers )
  {
    assert( pCurAct );
    // it might be that the player DC'd in which case the session would be invalid
    // TODO: copy packet to a new unique_ptr then move ownership
    pCurAct->queuePacket( pPacket );
  }
}

/*! \return list of actors currently in range */
std::set< Sapphire::Entity::ActorPtr > Sapphire::Entity::Actor::getInRangeActors( bool includeSelf )
{
  auto tempInRange = m_inRangeActor;

  if( includeSelf )
    tempInRange.insert( shared_from_this() );

  return tempInRange;
}

/*! \return ZonePtr to the current zone, nullptr if not set */
Sapphire::ZonePtr Sapphire::Entity::Actor::getCurrentZone() const
{
  return m_pCurrentZone;
}

/*! \param ZonePtr to the zone to be set as current */
void Sapphire::Entity::Actor::setCurrentZone( ZonePtr currZone )
{
  m_pCurrentZone = currZone;
}

/*! \return InstanceContentPtr to the current instance, nullptr if not an instance or not set */
Sapphire::InstanceContentPtr Sapphire::Entity::Actor::getCurrentInstance() const
{
  if( m_pCurrentZone )
    return m_pCurrentZone->getAsInstanceContent();

  return nullptr;
}

/*!
Get the current cell of a region the actor is in

\return Cell*
*/
Sapphire::Cell* Sapphire::Entity::Actor::getCellPtr()
{
  return m_pCell;
}

/*!
Set the current cell the actor is in

\param Cell* for the cell to be set
*/
void Sapphire::Entity::Actor::setCell( Cell* pCell )
{
  m_pCell = pCell;
}
