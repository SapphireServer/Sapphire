#include <string.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Logging/Logger.h>
#include <Network/CommonActorControl.h>

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "Actor/Player.h"

#include "EventItemAction.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::Action::EventItemAction::EventItemAction()
{
  m_handleActionType = HandleActionType::Event;
}

Sapphire::Action::EventItemAction::EventItemAction( Entity::CharaPtr pActor, uint32_t eventId, uint16_t action,
                                                ActionCallback finishRef, ActionCallback interruptRef,
                                                uint64_t additional )
{
  m_additional = additional;
  m_handleActionType = HandleActionType::Event;
  m_eventId = eventId;
  m_id = action;
  // TODO: read the cast time from the action itself
  m_castTime = 3000;
  m_onActionFinishClb = finishRef;
  m_onActionInterruptClb = interruptRef;
  m_pSource = pActor;
  m_bInterrupt = false;
}

Sapphire::Action::EventItemAction::~EventItemAction() = default;

void Sapphire::Action::EventItemAction::onStart()
{
  if( !m_pSource )
    return;

  m_startTime = Util::getTimeMs();

  auto castPacket = makeZonePacket< FFXIVIpcActorCast >( m_pSource->getId() );
  castPacket->data().action_id = 1;
  castPacket->data().unknown = 3;
  castPacket->data().unknown_1 = m_id;
  castPacket->data().cast_time = 3.0f;
  castPacket->data().target_id = m_pSource->getId();

  m_pSource->sendToInRangeSet( castPacket, true );
  m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );

}

void Sapphire::Action::EventItemAction::onFinish()
{
  if( !m_pSource )
    return;

  try
  {
    auto effectPacket = std::make_shared< Server::EffectPacket >( m_pSource->getId(), m_additional, m_id );
    effectPacket->setAnimationId( 1 );
    effectPacket->setRotation( Util::floatToUInt16Rot( m_pSource->getRot() ) );

    m_pSource->getAsPlayer()->unsetStateFlag( Common::PlayerStateFlag::Casting );
    m_pSource->sendToInRangeSet( effectPacket, true );

    if( m_onActionFinishClb )
      m_onActionFinishClb( *m_pSource->getAsPlayer(), m_eventId, m_additional );
  }
  catch( std::exception& e )
  {
    Logger::error( e.what() );
  }

}

void Sapphire::Action::EventItemAction::onInterrupt()
{
  if( !m_pSource )
    return;

  try
  {

    auto control = makeActorControl142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 0x04, m_id );
    if( m_pSource->isPlayer() )
    {
      m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );
      m_pSource->sendToInRangeSet( control, true );
    }
    else
      m_pSource->sendToInRangeSet( control );

    if( m_onActionInterruptClb )
      m_onActionInterruptClb( *m_pSource->getAsPlayer(), m_eventId, m_additional );

  }
  catch( std::exception& e )
  {
    Logger::error( e.what() );
  }

}
