#include "GameObject.h"

#include <Network/PacketContainer.h>

#include <Util/UtilMath.h>
#include <utility>
#include <Service.h>

#include "Territory/Territory.h"

#include "Network/GameConnection.h"

#include "Chara.h"
#include "EventObject.h"
#include "Player.h"
#include "BNpc.h"
#include "AreaObject.h"

#include "WorldServer.h"
#include "Session.h"

#include "Manager/TerritoryMgr.h"

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::Network::Packets;
//using namespace Sapphire::Network::Packets::Server;

GameObject::GameObject( ObjKind type ) :
  m_objKind( type )
{

}

uint32_t GameObject::getId() const
{
  return m_id;
}

void GameObject::setId( uint32_t id )
{
  m_id = id;
}

ObjKind GameObject::getObjKind() const
{
  return m_objKind;
}

FFXIVARR_POSITION3& GameObject::getPos()
{
  return m_pos;
}

const FFXIVARR_POSITION3& GameObject::getPos() const
{
  return m_pos;
}

void GameObject::setPos( float x, float y, float z, bool broadcastUpdate )
{
  m_pos.x = x;
  m_pos.y = y;
  m_pos.z = z;

  if( broadcastUpdate )
  {
    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );
    pZone->updateActorPosition( *this );
  }

}

void GameObject::setPos( const FFXIVARR_POSITION3& pos, bool broadcastUpdate )
{
  m_pos = pos;

  if( broadcastUpdate )
  {
    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pZone = teriMgr.getTerritoryByGuId( getTerritoryId() );
    pZone->updateActorPosition( *this );
  }
}

float GameObject::getRot() const
{
  return m_rot;
}

void GameObject::setRot( float rot )
{
  m_rot = rot;
}

bool GameObject::isChara() const
{
  return isPlayer() || isBattleNpc() || isEventNpc() || isRetainer() || isCompanion();
}

bool GameObject::isPlayer() const
{
  return m_objKind == ObjKind::Player;
}

bool GameObject::isEventNpc() const
{
  return m_objKind == ObjKind::EventNpc;
}

bool GameObject::isBattleNpc() const
{
  return m_objKind == ObjKind::BattleNpc;
}

bool GameObject::isRetainer() const
{
  return m_objKind == ObjKind::Retainer;
}

bool GameObject::isCompanion() const
{
  return m_objKind == ObjKind::Companion;
}

bool GameObject::isEventObj() const
{
  return m_objKind == ObjKind::EventObj;
}

bool GameObject::isHousingEventObj() const
{
  return m_objKind == ObjKind::Housing;
}

bool GameObject::isAetheryte() const
{
  return m_objKind == ObjKind::Aetheryte;
}

bool GameObject::isArea() const
{
  return m_objKind == ObjKind::Area;
}


/*! \return pointer to this instance as GameObjectPtr */
CharaPtr GameObject::getAsChara()
{
  if( !isChara() )
    return nullptr;
  return std::dynamic_pointer_cast< Chara, GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as PlayerPtr */
PlayerPtr GameObject::getAsPlayer()
{
  if( !isPlayer() )
    return nullptr;
  return std::dynamic_pointer_cast< Player, GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as EventObjPtr */
EventObjectPtr GameObject::getAsEventObj()
{
  if( !isEventObj() )
    return nullptr;
  return std::dynamic_pointer_cast< EventObject, GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as BNpcPtr */
BNpcPtr GameObject::getAsBNpc()
{
  if( !isBattleNpc() )
    return nullptr;
  return std::dynamic_pointer_cast< BNpc, GameObject >( shared_from_this() );
}

/*! \return pointer to this instance as AreaPtr */
AreaObjectPtr GameObject::getAsArea()
{
  if( !isArea() )
    return nullptr;
  return std::dynamic_pointer_cast< AreaObject, GameObject >( shared_from_this() );
}

/*!
Add a given actor to the fitting in range set according to type
but also to the global actor map

\param GameObjectPtr to add
*/
void GameObject::addInRangeActor( GameObjectPtr pActor )
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
void GameObject::removeInRangeActor( GameObject& actor )
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
bool GameObject::hasInRangeActor() const
{
  return ( !m_inRangeActor.empty() );
}

void GameObject::removeFromInRange()
{
  if( !hasInRangeActor() )
    return;

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
bool GameObject::isInRangeSet( GameObjectPtr pActor ) const
{
  return !( m_inRangeActor.find( pActor ) == m_inRangeActor.end() );
}


/*! \return GameObjectPtr of the closest actor in range, if none, nullptr */
CharaPtr GameObject::getClosestChara()
{
  if( m_inRangeActor.empty() )
    // no actors in range, don't bother
    return nullptr;

  CharaPtr tmpActor = nullptr;

  // arbitrary high number
  float minDistance = 10000;

  for( const auto& pCurAct : m_inRangeActor )
  {
    float distance = Util::distance( getPos().x, getPos().y, getPos().z, pCurAct->getPos().x, pCurAct->getPos().y, pCurAct->getPos().z );

    if( distance < minDistance )
    {
      minDistance = distance;
      tmpActor = pCurAct->getAsChara();
    }
  }

  return tmpActor;
}

/*! Clear the whole in range set, this does no cleanup */
void GameObject::clearInRangeSet()
{
  m_inRangeActor.clear();
  m_inRangePlayers.clear();
  m_inRangeBNpc.clear();
}

/*! \return list of actors currently in range */
std::set< GameObjectPtr > GameObject::getInRangeActors( bool includeSelf )
{
  auto tempInRange = m_inRangeActor;

  if( includeSelf )
    tempInRange.insert( shared_from_this() );

  return tempInRange;
}

std::set< uint64_t > GameObject::getInRangePlayerIds( bool includeSelf )
{
  std::set< uint64_t > playerIds;
  for( auto& player : m_inRangePlayers )
    playerIds.insert( player->getCharacterId() );

  if( isPlayer() && includeSelf )
    playerIds.insert( getAsPlayer()->getCharacterId() );

  return playerIds;
}

uint32_t GameObject::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

void GameObject::setTerritoryTypeId( uint32_t territoryTypeId )
{
  m_territoryTypeId = territoryTypeId;
}

uint32_t GameObject::getTerritoryId() const
{
  return m_territoryId;
}

void GameObject::setTerritoryId( uint32_t territoryId )
{
  m_territoryId = territoryId;
}

/*!
Get the current cellId of a region the actor is in

\return CellId
*/
CellId GameObject::getCellId() const
{
  return m_cellId;
}

/*!
Set the current cellId the actor is in

\param CellId for the cell to be set
*/
void GameObject::setCellId( CellId cellId )
{
  m_cellId = cellId;
}
