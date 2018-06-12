#include "EventObject.h"

#include "Zone/InstanceContent.h"
#include "Actor/Player.h"

#include <Logging/Logger.h>
#include <Network/GamePacket.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Util/UtilMath.h>

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

#include "Framework.h"
extern Core::Framework g_fw;

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

void Core::Entity::EventObject::setAnimationFlag( uint32_t flag, uint32_t animationFlag ) {
   for( const auto& player : m_inRangePlayers )
   {
      ZoneChannelPacket< FFXIVIpcActorControl142 > eobjUpdatePacket( getId(), player->getId() );
      eobjUpdatePacket.data().category = Common::ActorControlType::EObjAnimation;
      eobjUpdatePacket.data().param1 = flag;
      eobjUpdatePacket.data().param2 = animationFlag;

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

   auto pLog = g_fw.get< Logger >();

   pLog->debug( "Spawning EObj: id:" + std::to_string( getId() ) + " name:" + getName() );
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
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "despawn eobj: " + std::to_string( getId() ) );

   pTarget->freeObjSpawnIndexForActorId( getId( ) );
}

const std::string& Core::Entity::EventObject::getName() const
{
   return m_name;
}
