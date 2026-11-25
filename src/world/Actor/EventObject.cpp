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
#include <Network/PacketWrappers/MoveActorPacket.h>

#include <Territory/InstanceObjectCache.h>

#include <datReader/DatCategories/InstanceObjectParser.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

// todo: i don't trust the overloads enough
template< typename TVec >
vec3 toVec3( const TVec& value )
{
  return { value.x, value.y, value.z };
}

vec3 applyRotation( vec3 value, const vec3& rotation )
{
  value = value * matrix4::rotateX( rotation.x );
  value = value * matrix4::rotateY( rotation.y );
  value = value * matrix4::rotateZ( rotation.z );
  return value;
}

vec3 applyTransform( vec3 value, const vec3& scale, const vec3& rotation, const vec3& translation )
{
  value.x *= scale.x;
  value.y *= scale.y;
  value.z *= scale.z;

  value = applyRotation( value, rotation );

  value.x += translation.x;
  value.y += translation.y;
  value.z += translation.z;

  return value;
}

vec3 scaleExtents( const vec3& extents, const vec3& scale )
{
  return { std::fabs( extents.x * scale.x ), std::fabs( extents.y * scale.y ), std::fabs( extents.z * scale.z ) };
}

float wrapAngle( float angle )
{
  return std::atan2( std::sin( angle ), std::cos( angle ) );
}

float toGameYaw( float yaw )
{
  return wrapAngle( -yaw );
}

float directionFromForward( const vec3& forward )
{
  return wrapAngle( std::atan2( -forward.x, forward.z ) );
}

float composeCollisionRotation( const vec3& parentRotation, const vec3& localRotation )
{
  auto forward = applyRotation( vec3{ 0.0f, 0.0f, 1.0f }, localRotation );
  forward = applyRotation( forward, parentRotation );
  return directionFromForward( forward );
}

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

  if( m_collisionEnabled )
  {
    setCollisionEnabled( true );
  }
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
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), SetSharedGroupTimelineState, state, getId() );
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
  eobjStatePacket->data().Args2 = getAnimation(); // initial animation state
  eobjStatePacket->data().Args3 = getHousingLink();

  server.queueForPlayer( pTarget->getCharacterId(), eobjStatePacket );
}


void EventObject::despawn( PlayerPtr pTarget )
{
  pTarget->freeObjSpawnIndexForActorId( getId() );
  pTarget->freePlayerSpawnId( getId() );
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

  m_collisionEnabled = enabled;

  auto& instanceObjCache = Common::Service< InstanceObjectCache >::ref();
  auto pBoundGroup = instanceObjCache.getSharedGroup( getTerritoryTypeId(), m_boundInstanceId );

  auto parentScale = vec3( m_scale, m_scale, m_scale );
  auto parentRotation = vec3( 0, m_rot, 0 );
  auto parentTranslation = toVec3( m_pos );

  if( !pBoundGroup )
  {
    auto pos = getPos();
    Logger::warn( "EventObject::setCollisionEnabled: EObj InstanceID {} BoundInstanceID {} Pos {} {} {} unable to find bound group. Has this collision been manually added?", m_instanceId, m_boundInstanceId, pos.x, pos.y, pos.z );
  }
  else
  {
    // todo: make this a flag
    // parentScale = pBoundGroup->header.Transformation.Scale;
    // parentRotation = pBoundGroup->header.Transformation.Rotation;
    // parentTranslation = pBoundGroup->header.Transformation.Translation;
  }

  if( auto pTeri = teriMgr.getTerritoryByGuId( getTerritoryId() ) )
  {
    if( auto pNavi = pTeri->getNaviProvider() )
    {
      for( auto& collision : m_collision )
      {
        auto pos = applyTransform(
                toVec3( collision.m_pos ),
                parentScale,
                parentRotation,
                parentTranslation );

        auto rot = composeCollisionRotation( parentRotation, toVec3( collision.m_rot ) );

        if( !collision.m_useParentTransformation )
        {
          pos = { collision.m_pos.x, collision.m_pos.y, collision.m_pos.z };
          rot = collision.m_rot.y;
        }

        switch( collision.m_type )
        {
          case EventObjectCollisionType::Box:
          {
            const auto box = scaleExtents( vec3( collision.m_shape.box.width, collision.m_shape.box.height, collision.m_shape.box.depth ), parentScale );

            pNavi->toggleBox( collision.m_obstacleRef, { pos.x, pos.y, pos.z }, { box.x, box.y, box.z }, rot, enabled );
          }
          break;
          case EventObjectCollisionType::Sphere:
          {
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
  Logger::warn( "EventObject::addCollisionBox: EObj InstanceID {} using old collision box data. May not function correctly. Re-export instance/quest battle script using event_object_parser.", m_instanceId );

  EventObjectCollision collision;
  collision.m_type = EventObjectCollisionType::Box;
  collision.m_pos = pos;
  collision.m_rot = Common::Vector3( 0.f, rot, 0.f );
  collision.m_shape.box.width = width;
  collision.m_shape.box.height = height;
  collision.m_shape.box.depth = depth;
  collision.m_useParentTransformation = false;

  m_collision.push_back( collision );
}

void EventObject::addCollisionBox( Common::Vector3 pos, Common::Vector3 rot, float width, float height, float depth )
{
  EventObjectCollision collision;
  collision.m_type = EventObjectCollisionType::Box;
  collision.m_pos = pos;
  collision.m_rot = rot;
  collision.m_shape.box.width = width;
  collision.m_shape.box.height = height;
  collision.m_shape.box.depth = depth;
  collision.m_useParentTransformation = true;

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

void EventObject::setAnimation( uint32_t animation )
{
  m_animation = animation;
  // todo: first parameter doesn't seem to affect anything?
  playSharedGroupTimeline( 0, animation );
}

uint32_t EventObject::getAnimation() const
{
  return m_animation;
}

bool EventObject::isCollisionEnabled() const
{
  return m_collisionEnabled;
}

void EventObject::setPos( float x, float y, float z, bool broadcastUpdate, bool sendPacketToSelf )
{
  GameObject::setPos( x, y, z, broadcastUpdate, sendPacketToSelf );

  uint8_t dirS1 = Common::Util::floatToUInt8Rot( getRot() );

  auto movePacket = std::make_shared< MoveActorPacket >( *this, 0x3A, 0, 0, dirS1 );
  server().queueForPlayers( getInRangePlayerIds(), movePacket );

  // update collision boxes if moved
  if( m_collisionEnabled )
  {
    setCollisionEnabled( true );
  }
}

void EventObject::setPos( const Common::Vector3& pos, bool broadcastUpdate, bool sendPacketToSelf )
{
  setPos( pos.x, pos.y, pos.z, broadcastUpdate, sendPacketToSelf );
}
