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

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

EventObject::EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId, uint32_t instanceId, uint8_t initialState,
                          FFXIVARR_POSITION3 pos, float rotation, const std::string& givenName, uint8_t permissionInv ) :
  GameObject( ObjKind::EventObj ),
  m_sharedGroupId( gimmickId ),
  m_instanceId( instanceId ),
  m_state( initialState ),
  m_objectId( objectId ),
  m_name( givenName ),
  m_housingLink( 0 ),
  m_permissionInvisibility( permissionInv ),
  m_ownerId( INVALID_GAME_OBJECT_ID )
{
  m_id = actorId;
  m_pos.x = pos.x;
  m_pos.y = pos.y;
  m_pos.z = pos.z;
  m_rot = rotation;
}

uint32_t EventObject::getSharedGroupId() const
{
  return m_sharedGroupId;
}

uint32_t EventObject::getObjectId() const
{
  return m_objectId;
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

void EventObject::setSharedGroupId( uint32_t sharedGroupId )
{
  m_sharedGroupId = sharedGroupId;
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
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), PlaySharedGroupTimeline, flag, animationFlag );
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

  Logger::debug( "Spawning EObj: id#{0} name={1}", getId(), getName() );

  auto eobjStatePacket = makeZonePacket< FFXIVIpcCreateObject >( getId(), pTarget->getId() );
  eobjStatePacket->data().Index = spawnIndex;
  eobjStatePacket->data().Kind = getObjKind();
  eobjStatePacket->data().Flag = getState();
  eobjStatePacket->data().BaseId = getObjectId();
  eobjStatePacket->data().LayoutId = getInstanceId();
  eobjStatePacket->data().BindLayoutId = getSharedGroupId();
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
  Logger::debug( "despawn eobj#{0}", getId() );

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

uint8_t EventObject::getPermissionInvisibility() const
{
  return m_permissionInvisibility;
}

void EventObject::setPermissionInvisibility( uint8_t permissionInvisibility )
{
  Network::Util::Packet::sendActorControl( getInRangePlayerIds(), getId(), DirectorEObjMod, permissionInvisibility );
}

uint32_t Sapphire::Entity::EventObject::getOwnerId() const
{
  return m_ownerId;
}
