#include "EventObject.h"

#include "Zone/InstanceContent.h"
#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

#include <Logging/Logger.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/CommonActorControl.h>
#include <Util/UtilMath.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

#include "Framework.h"

extern Sapphire::Framework g_fw;

Sapphire::Entity::EventObject::EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId,
                                        uint8_t initialState, Common::FFXIVARR_POSITION3 pos,
                                        float rotation, const std::string& givenName ) :
  Sapphire::Entity::Actor( ObjKind::EventObj ),
  m_gimmickId( gimmickId ),
  m_state( initialState ),
  m_objectId( objectId ),
  m_name( givenName )
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
  m_onTalkEventHandler = handler;
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

  for( const auto& player : m_inRangePlayers )
  {
    player->queuePacket( makeActorControl142( getId(), DirectorEObjMod, state ) );
  }
}

void Sapphire::Entity::EventObject::setAnimationFlag( uint32_t flag, uint32_t animationFlag )
{
  for( const auto& player : m_inRangePlayers )
  {
    player->queuePacket( makeActorControl142( getId(), EObjAnimation, flag, animationFlag ) );
  }
}

void Sapphire::Entity::EventObject::setParentInstance( Sapphire::InstanceContentPtr instance )
{
  m_parentInstance = instance;
}

Sapphire::InstanceContentPtr Sapphire::Entity::EventObject::getParentInstance() const
{
  return m_parentInstance;
}

void Sapphire::Entity::EventObject::spawn( Sapphire::Entity::PlayerPtr pTarget )
{
  auto spawnIndex = pTarget->getNextObjSpawnIndexForActorId( getId() );
  if( !pTarget->isObjSpawnIndexValid( spawnIndex ) )
    return;

  auto pLog = g_fw.get< Logger >();

  pLog->debug( "Spawning EObj: id:" + std::to_string( getId() ) + " name:" + getName() );

  auto eobjStatePacket = makeZonePacket< FFXIVIpcObjectSpawn >( getId(), pTarget->getId() );
  eobjStatePacket->data().spawnIndex = spawnIndex;
  eobjStatePacket->data().objKind = getObjKind();
  eobjStatePacket->data().state = getState();
  eobjStatePacket->data().objId = getObjectId();
  eobjStatePacket->data().gimmickId = getGimmickId();
  eobjStatePacket->data().position = getPos();
  eobjStatePacket->data().scale = getScale();
  eobjStatePacket->data().actorId = getId();
  eobjStatePacket->data().rotation = Math::Util::floatToUInt16Rot( getRot() );
  pTarget->queuePacket( eobjStatePacket );
}


void Sapphire::Entity::EventObject::despawn( Sapphire::Entity::PlayerPtr pTarget )
{
  auto pLog = g_fw.get< Logger >();
  pLog->debug( "despawn eobj: " + std::to_string( getId() ) );

  pTarget->freeObjSpawnIndexForActorId( getId() );
}

const std::string& Sapphire::Entity::EventObject::getName() const
{
  return m_name;
}
