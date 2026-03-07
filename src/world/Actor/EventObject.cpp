#include "EventObject.h"

#include "Territory/InstanceContent.h"
#include "Actor/Player.h"

#include <Logging/Logger.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/CommonActorControl.h>
#include <Network/Util/PacketUtil.h>
#include <Util/UtilMath.h>

#include <Service.h>

#include <utility>
#include "WorldServer.h"
#include "Session.h"
#include "Manager/MgrUtil.h"
#include "Manager/TerritoryMgr.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

EventObject::EventObject( uint32_t actorId, uint32_t baseId, uint32_t boundInstanceId, uint32_t instanceId,
                          uint8_t initialState,
                          Vector3 pos, float rotation, const std::string& givenName,
                          uint8_t permissionInv ) :
  GameObject( ObjKind::EventObj ),
  m_boundInstanceId( boundInstanceId ),
  m_instanceId( instanceId ),
  m_state( initialState ),
  m_baseId( baseId ),
  m_name( givenName ),
  m_housingLink( 0 ),
  m_ownerId( INVALID_GAME_OBJECT_ID )
{
  m_id = actorId;
  m_pos.x = pos.x;
  m_pos.y = pos.y;
  m_pos.z = pos.z;
  m_rot = rotation;
  m_permissionInvisibility = permissionInv;
}

void EventObject::setEventObjectType( EventObjectType type )
{
  m_eobjType = type;
}

uint32_t EventObject::getBoundInstanceId() const
{
  return m_boundInstanceId;
}

uint32_t EventObject::getBaseId() const
{
  return m_baseId;
}

float EventObject::getScale() const
{
  return m_scale;
}

void EventObject::setScale( float scale )
{
  m_scale = scale;
}

EventObject::OnTalkEventHandler EventObject::getOnTalkHandler() const
{
  return m_onTalkEventHandler;
}

void EventObject::setOnTalkHandler( EventObject::OnTalkEventHandler handler )
{
  m_onTalkEventHandler = std::move( handler );
}

void EventObject::setBoundInstanceId( uint32_t boundInstanceId )
{
  m_boundInstanceId = boundInstanceId;
}

uint8_t EventObject::getState() const
{
  return m_state;
}

void EventObject::setState( uint8_t state )
{
  m_state = state;
}

void EventObject::playSharedGroupTimeline( uint32_t flag, uint32_t animationFlag )
{
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), PlaySharedGroupTimeline, flag,
                                           animationFlag );
}

void EventObject::setHousingLink( uint32_t housingLink )
{
  m_housingLink = housingLink;
}

uint32_t EventObject::getHousingLink() const
{
  return m_housingLink;
}

void EventObject::setParentInstance( Sapphire::TerritoryPtr instance )
{
  m_parentInstance = std::move( instance );
}

TerritoryPtr EventObject::getParentInstance() const
{
  return m_parentInstance;
}

void EventObject::spawn( PlayerPtr pTarget )
{
  auto spawnIndex = pTarget->getNextObjSpawnIndexForActorId( getId() );
  if( !pTarget->isObjSpawnIndexValid( spawnIndex ) )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();
  auto eobjStatePacket = makeZonePacket< FFXIVIpcCreateObject >( getId(), pTarget->getId() );
  eobjStatePacket->data().Index = spawnIndex;
  eobjStatePacket->data().Kind = getObjKind();
  eobjStatePacket->data().Flag = getState();
  eobjStatePacket->data().BaseId = getBaseId();
  eobjStatePacket->data().LayoutId = getInstanceId();
  eobjStatePacket->data().BindLayoutId = getBoundInstanceId();
  eobjStatePacket->data().OwnerId = getOwnerId();
  eobjStatePacket->data().Pos = getPos();
  eobjStatePacket->data().Scale = getScale();
  eobjStatePacket->data().EntityId = getId();
  eobjStatePacket->data().Dir = getRotUInt16();
  eobjStatePacket->data().OwnerId = getOwnerId();
  eobjStatePacket->data().PermissionInvisibility = getPermissionInvisibility();
  eobjStatePacket->data().Args = 0xE0;
  eobjStatePacket->data().Args2 = 0; // initial animation state
  eobjStatePacket->data().Args3 = getHousingLink();

  server.queueForPlayer( pTarget->getCharacterId(), eobjStatePacket );
}


void EventObject::despawn( PlayerPtr pTarget )
{
  pTarget->freeObjSpawnIndexForActorId( getId() );
}

const std::string& EventObject::getName() const
{
  return m_name;
}

uint32_t EventObject::getInstanceId() const
{
  return m_instanceId;
}

void EventObject::setPermissionInvisibility( uint8_t permissionInvisibility )
{
  m_permissionInvisibility = permissionInvisibility;
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), DirectorEObjMod, permissionInvisibility );
}

uint32_t EventObject::getOwnerId() const
{
  return m_ownerId;
}

void EventObject::setCollisionEnabled( bool enabled )
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  
  if( auto pTeri = teriMgr.getTerritoryByGuId( getTerritoryId() ) )
  {
    if( auto pNavi = pTeri->getNaviProvider() )
    {
      for( auto& collision : m_collision )
      {
        switch( collision.m_type )
        {
          case EventObjectCollisionType::Box:
          {
            // todo: figure this out
            auto& box = collision.m_shape.box;
            Common::Vector3 pos = collision.m_pos;// Common::Util::getOffsettedPosition( collision.m_pos, collision.m_rot, 0.f, 0.f, box.width / 2.f );
            float rot = collision.m_rot;
            // rot = rot + ( PI / 2.0f );

            pNavi->toggleBox( collision.m_obstacleRef, pos, { box.width, box.height, box.depth }, rot, enabled );
          }
          break;
          case EventObjectCollisionType::Sphere:
          {
            // todo: actually make this a sphere
            auto& sphere = collision.m_shape.sphere;
            pNavi->toggleObstacle( collision.m_obstacleRef, collision.m_pos, sphere.radius, sphere.radius, enabled );
          }
          break;
          case EventObjectCollisionType::Cylinder:
          {
            auto& cylinder = collision.m_shape.cylinder;
            pNavi->toggleObstacle( collision.m_obstacleRef, collision.m_pos, cylinder.radius, cylinder.height, enabled );
          }
          break;
          default:
            break;
        }
      }
    }
  }
}

void EventObject::addCollisionBox( Common::Vector3 pos, float rot, float width, float height, float depth )
{
  EventObjectCollision collision;
  collision.m_type = EventObjectCollisionType::Box;
  collision.m_pos = pos;
  collision.m_rot = rot;
  collision.m_shape.box.width = width;
  collision.m_shape.box.height = height;
  collision.m_shape.box.depth = depth;

  m_collision.push_back( collision );
}

void EventObject::addCollisionCylinder( Common::Vector3 pos, float radius, float height )
{
  EventObjectCollision collision;
  collision.m_type = EventObjectCollisionType::Cylinder;
  collision.m_pos = pos;
  collision.m_shape.cylinder.radius = radius;
  collision.m_shape.cylinder.height = height;

  m_collision.push_back( collision );
}

void EventObject::addCollisionSphere( Common::Vector3 pos, float radius )
{
  EventObjectCollision collision;
  collision.m_type = EventObjectCollisionType::Sphere;
  collision.m_pos = pos;
  collision.m_shape.sphere.radius = radius;

  m_collision.push_back( collision );
}

const std::vector< EventObjectCollision >& EventObject::getCollisionData() const
{
  return m_collision;
}