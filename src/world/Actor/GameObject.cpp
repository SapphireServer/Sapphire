#include "GameObject.h"

#include <Network/PacketContainer.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <utility>
#include <Service.h>

#include "Territory/Territory.h"

#include "Network/GameConnection.h"

#include "Chara.h"
#include "EventObject.h"
#include "Player.h"
#include "BNpc.h"

#include "WorldServer.h"
#include "Session.h"

#include "Manager/TerritoryMgr.h"

#include "StatusEffect/StatusEffect.h"

#include "Math/CalcBattle.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
//using namespace Sapphire::Network::Packets::Server;

Sapphire::Entity::GameObject::GameObject( ObjKind type ) :
  m_objKind( type )
{

}

uint32_t Sapphire::Entity::GameObject::getId() const
{
  return m_id;
}

void Sapphire::Entity::GameObject::setId( uint32_t id )
{
  m_id = id;
}

Sapphire::Common::ObjKind Sapphire::Entity::GameObject::getObjKind() const
{
  return m_objKind;
}

Sapphire::Common::FFXIVARR_POSITION3& Sapphire::Entity::GameObject::getPos()
{
  return m_pos;
}

const Sapphire::Common::FFXIVARR_POSITION3& Sapphire::Entity::GameObject::getPos() const
{
  return m_pos;
}

void Sapphire::Entity::GameObject::setPos( float x, float y, float z, bool broadcastUpdate )
{
  m_pos.x = x;
  m_pos.y = y;
  m_pos.z = z;

  if( broadcastUpdate )
    m_pCurrentTerritory->updateActorPosition( *this );
}

void Sapphire::Entity::GameObject::setPos( const Sapphire::Common::FFXIVARR_POSITION3& pos, bool broadcastUpdate )
{
  m_pos = pos;

  if( broadcastUpdate )
    m_pCurrentTerritory->updateActorPosition( *this );
}

float Sapphire::Entity::GameObject::getRot() const
{
  return m_rot;
}

void Sapphire::Entity::GameObject::setRot( float rot )
{
  m_rot = rot;
}

bool Sapphire::Entity::GameObject::isChara() const
{
  return isPlayer() || isBattleNpc() || isEventNpc() || isRetainer() || isCompanion();
}

bool Sapphire::Entity::GameObject::isPlayer() const
{
  return m_objKind == ObjKind::Player;
}

bool Sapphire::Entity::GameObject::isEventNpc() const
{
  return m_objKind == ObjKind::EventNpc;
}

bool Sapphire::Entity::GameObject::isBattleNpc() const
{
  return m_objKind == ObjKind::BattleNpc;
}

bool Sapphire::Entity::GameObject::isRetainer() const
{
  return m_objKind == ObjKind::Retainer;
}

bool Sapphire::Entity::GameObject::isCompanion() const
{
  return m_objKind == ObjKind::Companion;
}

bool Sapphire::Entity::GameObject::isEventObj() const
{
  return m_objKind == ObjKind::EventObj;
}

bool Sapphire::Entity::GameObject::isHousingEventObj() const
{
  return m_objKind == ObjKind::Housing;
}

bool Sapphire::Entity::GameObject::isAetheryte() const
{
  return m_objKind == ObjKind::Aetheryte;
}


/*! \return pointer to this instance as GameObjectPtr */
Sapphire::Entity::CharaPtr Sapphire::Entity::GameObject::getAsChara()
{
  if( !isChara() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::Chara, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
Sapphire::Entity::PlayerPtr Sapphire::Entity::GameObject::getAsPlayer()
{
  if( !isPlayer() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::Player, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as EventObjPtr */
Sapphire::Entity::EventObjectPtr Sapphire::Entity::GameObject::getAsEventObj()
{
  if( !isEventObj() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::EventObject, Entity::GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as BNpcPtr */
Sapphire::Entity::BNpcPtr Sapphire::Entity::GameObject::getAsBNpc()
{
  if( !isBattleNpc() )
    return nullptr;
  return std::dynamic_pointer_cast< Entity::BNpc, Entity::GameObject >( shared_from_this() );
}

/*!
Add a given actor to the fitting in range set according to type
but also to the global actor map

\param GameObjectPtr to add
*/
void Sapphire::Entity::GameObject::addInRangeActor( GameObjectPtr pActor )
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

\param GameObjectPtr to remove
*/
void Sapphire::Entity::GameObject::removeInRangeActor( GameObject& actor )
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
bool Sapphire::Entity::GameObject::hasInRangeActor() const
{
  return ( !m_inRangeActor.empty() );
}

void Sapphire::Entity::GameObject::removeFromInRange()
{
  if( !hasInRangeActor() )
    return;

  Entity::GameObjectPtr pCurAct;

  for( auto& pCurAct : m_inRangeActor )
  {
    pCurAct->removeInRangeActor( *this );
  }

}

/*!
check if a given actor is in the actors in range set

\param GameObjectPtr to be checked for
\return true if the actor was found
*/
bool Sapphire::Entity::GameObject::isInRangeSet( GameObjectPtr pActor ) const
{
  return !( m_inRangeActor.find( pActor ) == m_inRangeActor.end() );
}


/*! \return GameObjectPtr of the closest actor in range, if none, nullptr */
Sapphire::Entity::CharaPtr Sapphire::Entity::GameObject::getClosestChara()
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
void Sapphire::Entity::GameObject::clearInRangeSet()
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
void Sapphire::Entity::GameObject::sendToInRangeSet( Network::Packets::FFXIVPacketBasePtr pPacket, bool bToSelf )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  if( bToSelf && isPlayer() )
  {
    server.queueForPlayer( getAsPlayer()->getCharacterId(), pPacket );
  }

  if( m_inRangePlayers.empty() )
    return;

  pPacket->setSourceActor( m_id );

  for( const auto& pCurAct : m_inRangePlayers )
  {
    assert( pCurAct );
    // it might be that the player DC'd in which case the session would be invalid
    // TODO: copy packet to a new unique_ptr then move ownership
    server.queueForPlayer( pCurAct->getCharacterId(), pPacket );
  }
}

/*! \return list of actors currently in range */
std::set< Sapphire::Entity::GameObjectPtr > Sapphire::Entity::GameObject::getInRangeActors( bool includeSelf )
{
  auto tempInRange = m_inRangeActor;

  if( includeSelf )
    tempInRange.insert( shared_from_this() );

  return tempInRange;
}

/*! \return TerritoryPtr to the current zone, nullptr if not set */
Sapphire::TerritoryPtr Sapphire::Entity::GameObject::getCurrentTerritory() const
{
  return m_pCurrentTerritory;
}

/*! \param TerritoryPtr to the zone to be set as current */
void Sapphire::Entity::GameObject::setCurrentZone( TerritoryPtr currZone )
{
  m_pCurrentTerritory = currZone;
}

/*! \return InstanceContentPtr to the current instance, nullptr if not an instance or not set */
Sapphire::InstanceContentPtr Sapphire::Entity::GameObject::getCurrentInstance() const
{
  if( m_pCurrentTerritory )
    return m_pCurrentTerritory->getAsInstanceContent();

  return nullptr;
}

/*! \return QuestBattlePtr to the current instance, nullptr if not an instance or not set */
Sapphire::QuestBattlePtr Sapphire::Entity::GameObject::getCurrentQuestBattle() const
{
  if( m_pCurrentTerritory )
    return m_pCurrentTerritory->getAsQuestBattle();

  return nullptr;
}

/*!
Get the current cellId of a region the actor is in

\return CellId
*/
Sapphire::Common::CellId Sapphire::Entity::GameObject::getCellId() const
{
  return m_cellId;
}

/*!
Set the current cellId the actor is in

\param CellId for the cell to be set
*/
void Sapphire::Entity::GameObject::setCellId( Common::CellId cellId )
{
  m_cellId = cellId;
}
