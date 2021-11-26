#include "EventObject.h"

#include "Territory/InstanceContent.h"
#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"

#include <Logging/Logger.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/CommonActorControl.h>
#include <Util/UtilMath.h>

#include <Service.h>
#include "WorldServer.h"
#include "Session.h"
#include "Network/GameConnection.h"


using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Entity::EventObject::EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId,
                                            uint8_t initialState, Common::FFXIVARR_POSITION3 pos,
                                            float rotation, const std::string& givenName ) :
  Sapphire::Entity::GameObject( ObjKind::EventObj ),
  m_gimmickId( gimmickId ),
  m_state( initialState ),
  m_objectId( objectId ),
  m_name( givenName ),
  m_housingLink( 0 )
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

  sendToInRangeSet( makeActorControl( getId(), DirectorEObjMod, state ) );
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
  m_parentInstance = instance;
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
  eobjStatePacket->data().BindLayoutId = getGimmickId();
  eobjStatePacket->data().Pos = getPos();
  eobjStatePacket->data().Scale = getScale();
  eobjStatePacket->data().EntityId = getId();
  eobjStatePacket->data().Dir = Util::floatToUInt16Rot( getRot() );

  eobjStatePacket->data().Args3 = getHousingLink();

  auto pSession = server.getSession( pTarget->getCharacterId() );
  pSession->getZoneConnection()->queueOutPacket( eobjStatePacket );
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
