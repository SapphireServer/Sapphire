#include "AreaObject.h"

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

AreaObject::AreaObject( uint32_t actorId, uint32_t actionId, uint32_t actionPotency, uint32_t vfxId,
    float scale, uint32_t ownerId, const Common::FFXIVARR_POSITION3& pos ) :
  GameObject( ObjKind::Area ),
  m_actionId( actionId ),
  m_actionPotency( actionPotency ),
  m_vfxId( vfxId ),
  m_scale( scale ),
  m_ownerId( ownerId )
{
  m_id = actorId;
  m_pos.x = pos.x;
  m_pos.y = pos.y;
  m_pos.z = pos.z;
}

void AreaObject::spawn( PlayerPtr pTarget )
{
  auto spawnIndex = pTarget->getNextObjSpawnIndexForActorId( getId() );
  if( !pTarget->isObjSpawnIndexValid( spawnIndex ) )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();

  auto areaSpawnPacket = makeZonePacket< FFXIVIpcCreateObject >( getId(), pTarget->getId() );
  areaSpawnPacket->data().Index = spawnIndex;
  areaSpawnPacket->data().Kind = getObjKind();
  areaSpawnPacket->data().BaseId = m_vfxId;
  areaSpawnPacket->data().OwnerId = getOwnerId();
  areaSpawnPacket->data().Pos = getPos();
  areaSpawnPacket->data().EntityId = getId();
  areaSpawnPacket->data().Dir = Util::floatToUInt16Rot( getRot() );
  // these numbers are from a retail packet cap, unsure what each does
  areaSpawnPacket->data().SharedGroupTimelineState = 28384;
  areaSpawnPacket->data().Args = 227;
  areaSpawnPacket->data().Args2 = 2133301740;
  areaSpawnPacket->data().Args3 = 1743564264;
  areaSpawnPacket->data().Scale = m_scale;
  server.queueForPlayer( pTarget->getCharacterId(), areaSpawnPacket );
}

void AreaObject::despawn( PlayerPtr pTarget )
{
  pTarget->freeObjSpawnIndexForActorId( getId() );
}

uint32_t AreaObject::getOwnerId() const
{
  return m_ownerId;
}

void AreaObject::setOwnerId( uint32_t ownerId )
{
  m_ownerId = ownerId;
}

uint32_t Sapphire::Entity::AreaObject::getActionId() const
{
  return m_actionId;
}

uint32_t Sapphire::Entity::AreaObject::getActionPotency() const
{
  return m_actionPotency;
}
