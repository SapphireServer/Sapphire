#include "EventObject.h"

#include "Zone/InstanceContent.h"
#include "Actor/Player.h"

#include <common/Logging/Logger.h>
#include <common/Network/GamePacket.h>
#include <common/Network/GamePacketNew.h>
#include <common/Network/CommonNetwork.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/PacketContainer.h>

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Logger g_log;


Core::Entity::EventObject::EventObject( uint32_t objectId, uint32_t mapLinkId,
                                        uint8_t initialState, Common::FFXIVARR_POSITION3 pos ) :
   Core::Entity::Actor( ObjKind::EventObj ),
   m_mapLinkId( mapLinkId ),
   m_state( initialState ),
   m_objectId( objectId )
{
   m_id = objectId;
   m_pos.x = pos.x;
   m_pos.y = pos.y;
   m_pos.z = pos.z;
}

uint32_t Core::Entity::EventObject::getMapLinkId() const
{
   return m_mapLinkId;
}

uint32_t Core::Entity::EventObject::getObjectId() const
{
   return m_objectId;
}

void Core::Entity::EventObject::setMapLinkId( uint32_t mapLinkId )
{
   m_mapLinkId = mapLinkId;
}

uint8_t Core::Entity::EventObject::getState() const
{
   return m_state;
}

void Core::Entity::EventObject::setState( uint8_t state )
{
   m_state = state;

   //m_parentInstance->updateEObj( InstanceObjectPtr( this ) );
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
   g_log.debug( "spawn eobj: " + std::to_string( getId() ) );
   ZoneChannelPacket< FFXIVIpcObjectSpawn > eobjStatePacket( getId(), pTarget->getId() );
   eobjStatePacket.data().count = pTarget->getNextObjCount();
   eobjStatePacket.data().objKind = getObjKind();
   eobjStatePacket.data().state = getState();
   eobjStatePacket.data().objId = getId();
   eobjStatePacket.data().hierachyId = getMapLinkId();
   eobjStatePacket.data().position = getPos();
   pTarget->queuePacket( eobjStatePacket );
}


void Core::Entity::EventObject::despawn( Core::Entity::PlayerPtr pTarget )
{
   g_log.debug( "despawn eobj: " + std::to_string( getId() ) );
}