#include <Common.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Logging/Logger.h>
#include <Network/CommonActorControl.h>

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "Actor/Player.h"
#include "Script/ScriptMgr.h"

#include "ActionMount.h"
#include "Framework.h"

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;
using namespace Core::Network::ActorControl;

extern Core::Framework g_framework;

Core::Action::ActionMount::ActionMount()
{
  m_handleActionType = HandleActionType::Event;
}

Core::Action::ActionMount::ActionMount( Entity::CharaPtr pActor, uint16_t mountId )
{
  m_startTime = 0;
  m_id = mountId;
  m_handleActionType = HandleActionType::Spell;
  m_castTime = 1000;
  m_pSource = pActor;
  m_bInterrupt = false;
}

Core::Action::ActionMount::~ActionMount()
{

}

void Core::Action::ActionMount::onStart()
{
  if( !m_pSource )
    return;

  m_pSource->getAsPlayer()->sendDebug( "ActionMount::onStart()" );
  m_startTime = Util::getTimeMs();

  auto castPacket = makeZonePacket< FFXIVIpcActorCast >( getId() );
  castPacket->data().action_id = m_id;
  castPacket->data().skillType = Common::SkillType::MountSkill;
  castPacket->data().unknown_1 = m_id;
  // This is used for the cast bar above the target bar of the caster.
  castPacket->data().cast_time = static_cast< float >( m_castTime / 1000 );
  castPacket->data().target_id = m_pSource->getAsPlayer()->getId();

  m_pSource->sendToInRangeSet( castPacket, true );
  m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );

}

void Core::Action::ActionMount::onFinish()
{
  if( !m_pSource )
    return;

  auto pPlayer = m_pSource->getAsPlayer();
  pPlayer->sendDebug( "ActionMount::onFinish()" );

  pPlayer->unsetStateFlag( PlayerStateFlag::Casting );

  auto effectPacket = boost::make_shared< Server::EffectPacket >( getId(), pPlayer->getId(), 4 );
  effectPacket->setRotation( Math::Util::floatToUInt16Rot( pPlayer->getRot() ) );

  Server::EffectEntry effectEntry{};
  effectEntry.effectType = ActionEffectType::Mount;
  effectEntry.hitSeverity = ActionHitSeverityType::CritDamage;
  effectEntry.value = m_id;

  effectPacket->addEffect( effectEntry );

  pPlayer->sendToInRangeSet( effectPacket, true );

  pPlayer->mount( m_id );
}

void Core::Action::ActionMount::onInterrupt()
{
  if( !m_pSource )
    return;

  //m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
  m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );

  auto control = makeActorControl142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

  // Note: When cast interrupt from taking too much damage, set the last value to 1. This enables the cast interrupt effect. Example:
  // auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

  m_pSource->sendToInRangeSet( control, true );

}
