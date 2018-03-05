#include "EventObject.h"

#include "Zone/InstanceContent.h"
#include "Actor/Player.h"

#include <common/Logging/Logger.h>
#include <common/Network/GamePacket.h>
#include <common/Network/GamePacketNew.h>
#include <common/Network/CommonNetwork.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/PacketContainer.h>
#include <common/Util/UtilMath.h>

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Logger g_log;


Core::Entity::EventObject::EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId,
                                        uint8_t initialState, Common::FFXIVARR_POSITION3 pos,
                                        float rotation, const std::string& givenName ) :
   Core::Entity::Actor( ObjKind::EventObj ),
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

uint32_t Core::Entity::EventObject::getGimmickId() const
{
   return m_gimmickId;
}

uint32_t Core::Entity::EventObject::getObjectId() const
{
   return m_objectId;
}

float Core::Entity::EventObject::getScale() const
{
   return m_scale;
}

void Core::Entity::EventObject::setScale( float scale )
{
   m_scale = scale;
}

Core::Entity::EventObject::OnTalkEventHandler Core::Entity::EventObject::getOnTalkHandler() const
{
   return m_onTalkEventHandler;
}

void Core::Entity::EventObject::setOnTalkHandler( Core::Entity::EventObject::OnTalkEventHandler handler )
{
   m_onTalkEventHandler = handler;
}

void Core::Entity::EventObject::setGimmickId( uint32_t gimmickId )
{
   m_gimmickId = gimmickId;
}

uint8_t Core::Entity::EventObject::getState() const
{
   return m_state;
}

void Core::Entity::EventObject::setState( uint8_t state )
{
   m_state = state;

   for( const auto& player : m_inRangePlayers )
   {
      ZoneChannelPacket< FFXIVIpcActorControl142 > eobjUpdatePacket( getId(), player->getId() );
      eobjUpdatePacket.data().category = Common::ActorControlType::DirectorEObjMod;
      eobjUpdatePacket.data().param1 = state;

      player->queuePacket( eobjUpdatePacket );
   }
}

void Core::Entity::EventObject::setParentInstance( Core::InstanceContentPtr instance )
{
   m_parentInstance = instance;
}

Core::InstanceContentPtr Core::Entity::EventObject::getParentInstance() const
{
   return m_parentInstance;
}

void Core::Entity::EventObject::spawn( Core::Entity::PlayerPtr pTarget )
{
   auto spawnIndex = pTarget->getNextObjSpawnIndexForActorId( getId( ) );
   if( !pTarget->isObjSpawnIndexValid( spawnIndex ) )
      return;

   g_log.debug( "Spawning EObj: id:" + std::to_string( getId() ) + " name:" + getName() );
   ZoneChannelPacket< FFXIVIpcObjectSpawn > eobjStatePacket( getId(), pTarget->getId() );
   eobjStatePacket.data().spawnIndex = spawnIndex;
   eobjStatePacket.data().objKind = getObjKind();
   eobjStatePacket.data().state = getState();
   eobjStatePacket.data().objId = getObjectId();
   eobjStatePacket.data().gimmickId = getGimmickId();
   eobjStatePacket.data().position = getPos();
   eobjStatePacket.data().scale = getScale();
   eobjStatePacket.data().actorId = getId();
   eobjStatePacket.data().rotation = Math::Util::floatToUInt16Rot( getRot() );
   pTarget->queuePacket( eobjStatePacket );
}


void Core::Entity::EventObject::despawn( Core::Entity::PlayerPtr pTarget )
{
   g_log.debug( "despawn eobj: " + std::to_string( getId() ) );

   pTarget->freeObjSpawnIndexForActorId( getId( ) );
}

const std::string& Core::Entity::EventObject::getName() const
{
   return m_name;
}
