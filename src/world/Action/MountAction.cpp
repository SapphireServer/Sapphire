#include "MountAction.h"

#include <Exd/ExdDataGenerated.h>

#include "Actor/Player.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Action;

MountAction::MountAction( Sapphire::Entity::CharaPtr source, uint16_t mountId, uint16_t sequence, Data::ActionPtr actionData ) :
  Action::Action( source, 4, sequence, actionData ),
  m_mountId( mountId )
{
}

bool MountAction::preCheck()
{
  // todo: check if mount is unlocked
  return m_pSource->isPlayer();
}

void MountAction::start()
{
  assert( m_pSource );

  m_startTime = Common::Util::getTimeMs();

  auto player = m_pSource->getAsPlayer();

  auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( getId() );
  auto& data = castPacket->data();

  data.action_id = static_cast< uint16_t >( m_id );
  data.skillType = Common::SkillType::MountSkill;
  data.unknown_1 = m_mountId;
  data.cast_time = m_castTimeMs / 1000.f;
  data.target_id = static_cast< uint32_t >( m_targetId );
  data.unknown_2 = 0xE0000000;

  auto pos = m_pSource->getPos();
  data.posX = Common::Util::floatToUInt16( pos.x );
  data.posY = Common::Util::floatToUInt16( pos.y );
  data.posZ = Common::Util::floatToUInt16( pos.z );
  data.rotation = Common::Util::floatToUInt16Rot( m_pSource->getRot() );

  m_pSource->sendToInRangeSet( castPacket, true );

  player->setStateFlag( Common::PlayerStateFlag::Casting );

  auto actionStartPkt = makeActorControlSelf( m_pSource->getId(), ActorControlType::ActionStart, 1, getId(), m_recastTimeMs / 10 );
  player->queuePacket( actionStartPkt );
}

void MountAction::execute()
{
  assert( m_pSource );

  m_pSource->getAsPlayer()->unsetStateFlag( Common::PlayerStateFlag::Casting );
  m_effectBuilder->mount( m_pSource, m_mountId );
  m_effectBuilder->buildAndSendPackets();
}