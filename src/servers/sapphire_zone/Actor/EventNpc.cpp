#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <cmath>

#include <common/Logging/Logger.h>
#include <common/Exd/ExdData.h>
#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>

#include "Player.h"
#include "EventNpc.h"

#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;

uint32_t Core::Entity::EventNpc::m_nextID = 1249241694;

Core::Entity::EventNpc::EventNpc()
{
   m_id = 0;
   m_objKind = ObjKind::EventNpc;
   m_status = ActorStatus::Idle;
}

Core::Entity::EventNpc::~EventNpc()
{

}

Core::Entity::EventNpc::EventNpc( uint32_t enpcId, const Common::FFXIVARR_POSITION3& spawnPos, float rotation ) : Actor()
{
   EventNpc::m_nextID++;
   m_id = EventNpc::m_nextID;

   m_pos = spawnPos;
   m_posOrigin = spawnPos;

   m_objKind = ObjKind::EventNpc;

   m_targetId = static_cast< uint64_t >( INVALID_GAME_OBJECT_ID );

   m_maxHp = 150;
   m_maxMp = 100;

   m_baseStats.max_hp = m_maxHp;
   m_baseStats.max_mp = m_maxMp;

   m_hp = m_maxHp;
   m_mp = m_maxMp;

   m_currentStance = Stance::Passive;

   m_eNpcId = enpcId;

   m_status = ActorStatus::Idle;

   m_invincibilityType = InvincibilityType::InvincibilityNone;
   m_rot = rotation;

}

// spawn this player for pTarget
// TODO: Retail additionally sends Look+Models for EventNpcs even though it is not needed, add when the new exd reader is implemented(also counts for BNPCs)
void Core::Entity::EventNpc::spawn( PlayerPtr pTarget )
{
   ZoneChannelPacket< FFXIVIpcNpcSpawn > spawnPacket( getId(), pTarget->getId() );


   spawnPacket.data().pos.x = m_pos.x;
   spawnPacket.data().pos.y = m_pos.y;
   spawnPacket.data().pos.z = m_pos.z;

   spawnPacket.data().targetId = pTarget->getId();
   spawnPacket.data().hPCurr = 1;
   spawnPacket.data().hPMax = 1;

   spawnPacket.data().bNPCBase = m_eNpcId;
   spawnPacket.data().bNPCName = m_eNpcId;
   spawnPacket.data().spawnIndex = pTarget->getSpawnIdForActorId( getId() );

   spawnPacket.data().rotation = Math::Util::floatToUInt16Rot( getRotation() );

   spawnPacket.data().type = static_cast< uint8_t >( m_objKind );

   pTarget->queuePacket( spawnPacket );
}

// despawn
void Core::Entity::EventNpc::despawn( ActorPtr pTarget )
{

   auto pPlayer = pTarget->getAsPlayer();

   pPlayer->freePlayerSpawnId( getId() );

   ActorControlPacket143 controlPacket( m_id, DespawnZoneScreenMsg, 0x04, getId(), 0x01 );
   pPlayer->queuePacket( controlPacket );

}

uint8_t Core::Entity::EventNpc::getLevel() const
{
   return m_level;
}

void Core::Entity::EventNpc::resetPos()
{
   m_pos = m_posOrigin;
}

uint32_t Core::Entity::EventNpc::getEnpcId() const
{
   return m_eNpcId;
}