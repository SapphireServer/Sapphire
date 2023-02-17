#include "EventObject.h"

#include "Territory/InstanceContent.h"
#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"

#include <Logging/Logger.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/CommonActorControl.h>
#include <Util/UtilMath.h>

#include <Service.h>

#include <utility>
#include "WorldServer.h"
#include "Session.h"
#include "Network/GameConnection.h"


using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Entity::EventObject::EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId, uint32_t instanceId,
                                            uint8_t initialState, Common::FFXIVARR_POSITION3 pos,
                                            float rotation, const std::string& givenName, uint8_t permissionInv ) :
  Sapphire::Entity::GameObject( ObjKind::EventObj ),
  m_gimmickId( gimmickId ),
  m_instanceId( instanceId ),
  m_state( initialState ),
  m_objectId( objectId ),
  m_name( givenName ),
  m_housingLink( 0 ),
  m_permissionInvisibility( permissionInv ),
  m_ownerId( Common::INVALID_GAME_OBJECT_ID )
{
  m_id = actorId;
  m_pos.x = pos.x;
  m_pos.y = pos.y;
  m_pos.z = pos.z;
  m_rot = rotation;
}

uint32_t Sapphire::Entity::EventObject::getGimmickId() const
{
  return m_gimmickId;
}

uint32_t Sapphire::Entity::EventObject::getObjectId() const
{
  return m_objectId;
}

float Sapphire::Entity::EventObject::getScale() const
{
  return m_scale;
}

void Sapphire::Entity::EventObject::setScale( float scale )
{
  m_scale = scale;
}

Sapphire::Entity::EventObject::OnTalkEventHandler Sapphire::Entity::EventObject::getOnTalkHandler() const
{
  return m_onTalkEventHandler;
}

void Sapphire::Entity::EventObject::setOnTalkHandler( Sapphire::Entity::EventObject::OnTalkEventHandler handler )
{
  m_onTalkEventHandler = std::move( handler );
}

void Sapphire::Entity::EventObject::setGimmickId( uint32_t gimmickId )
{
  m_gimmickId = gimmickId;
}

uint8_t Sapphire::Entity::EventObject::getState() const
{
  return m_state;
}

void Sapphire::Entity::EventObject::setState( uint8_t state )
{
  m_state = state;
}

void Sapphire::Entity::EventObject::setAnimationFlag( uint32_t flag, uint32_t animationFlag )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  for( const auto& player : m_inRangePlayers )
  {
    auto pSession = server.getSession( player->getCharacterId() );
    pSession->getZoneConnection()->queueOutPacket( makeActorControl( getId(), EObjAnimation, flag, animationFlag ) );
  }
}

void Sapphire::Entity::EventObject::setHousingLink( uint32_t housingLink )
{
  m_housingLink = housingLink;
}

uint32_t Sapphire::Entity::EventObject::getHousingLink() const
{
  return m_housingLink;
}

void Sapphire::Entity::EventObject::setParentInstance( Sapphire::TerritoryPtr instance )
{
  m_parentInstance = std::move( instance );
}

Sapphire::TerritoryPtr Sapphire::Entity::EventObject::getParentInstance() const
{
  return m_parentInstance;
}

void Sapphire::Entity::EventObject::spawn( Sapphire::Entity::PlayerPtr pTarget )
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
  eobjStatePacket->data().BindLayoutId = getGimmickId();
  eobjStatePacket->data().OwnerId = getOwnerId();
  eobjStatePacket->data().Pos = getPos();
  eobjStatePacket->data().Scale = getScale();
  eobjStatePacket->data().EntityId = getId();
  eobjStatePacket->data().Dir = Util::floatToUInt16Rot( getRot() );
  eobjStatePacket->data().OwnerId = getOwnerId();
  eobjStatePacket->data().PermissionInvisibility = getPermissionInvisibility();
  eobjStatePacket->data().Args = 0xE0;
  eobjStatePacket->data().Args2 = 0; // initial animation state
  eobjStatePacket->data().Args3 = getHousingLink();

  server.queueForPlayer( pTarget->getCharacterId(), eobjStatePacket );
}


void Sapphire::Entity::EventObject::despawn( Sapphire::Entity::PlayerPtr pTarget )
{
  Logger::debug( "despawn eobj#{0}", getId() );

  pTarget->freeObjSpawnIndexForActorId( getId() );
}

const std::string& Sapphire::Entity::EventObject::getName() const
{
  return m_name;
}

uint32_t Sapphire::Entity::EventObject::getInstanceId() const
{
  return m_instanceId;
}

uint8_t Sapphire::Entity::EventObject::getPermissionInvisibility() const
{
  return m_permissionInvisibility;
}

void Sapphire::Entity::EventObject::setPermissionInvisibility( uint8_t permissionInvisibility )
{
  m_permissionInvisibility = permissionInvisibility;
  auto& server = Common::Service< World::WorldServer >::ref();
  auto inRangePlayerIds = getInRangePlayerIds();
  server.queueForPlayers( inRangePlayerIds, makeActorControl( getId(), DirectorEObjMod, permissionInvisibility ) );
}

uint32_t Sapphire::Entity::EventObject::getOwnerId() const
{
  return m_ownerId;
}
