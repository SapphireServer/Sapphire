#include <Util/Util.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonActorControl.h>
#include <Service.h>

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "Actor/Player.h"

#include "EventAction.h"

using namespace Sapphire;
using namespace Sapphire::World;
using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Action::EventAction::EventAction( Entity::CharaPtr pActor, uint32_t eventId, uint16_t action,
                                  ActionCallback finishRef, ActionCallback interruptRef, uint64_t additional )
{
  m_additional = additional;
  m_eventId = eventId;
  m_id = action;
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  m_castTimeMs = exdData.get< Sapphire::Data::EventAction >( action )->castTime * 1000; // TODO: Add security checks.
  m_onActionFinishClb = std::move( finishRef );
  m_onActionInterruptClb = std::move( interruptRef );
  m_pSource = std::move( pActor );
  m_interruptType = Common::ActionInterruptType::None;
}

Action::EventAction::~EventAction() = default;

void Action::EventAction::start()
{
  if( !m_pSource )
    return;

  m_startTime = Common::Util::getTimeMs();

  auto control = makeActorControl( m_pSource->getId(), ActorControlType::CastStart, 1, m_id, 0x4000004E );

  if( m_pSource->isPlayer() )
  {
    m_pSource->sendToInRangeSet( control, true );
    if( m_pSource->getAsPlayer()->hasStateFlag( PlayerStateFlag::InNpcEvent ) )
      m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::InNpcEvent );
  }
  else
    m_pSource->sendToInRangeSet( control );
}

void Action::EventAction::execute()
{
  if( !m_pSource )
    return;

  try
  {
    auto pEvent = m_pSource->getAsPlayer()->getEvent( m_eventId );

    pEvent->setPlayedScene( false );

    if( m_onActionFinishClb )
      m_onActionFinishClb( *m_pSource->getAsPlayer(), m_eventId, m_additional );

    auto control = makeActorControl( m_pSource->getId(), ActorControlType::CastStart, 0, m_id );

    if( !pEvent->hasPlayedScene() )
      m_pSource->getAsPlayer()->eventFinish( m_eventId, 1 );
    else
      pEvent->setPlayedScene( false );

    if( m_pSource->isPlayer() )
    {
      //m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied2 );
      m_pSource->sendToInRangeSet( control, true );
    }
    else
      m_pSource->sendToInRangeSet( control );
  }
  catch( std::exception& e )
  {
    Logger::error( e.what() );
  }

}

void Action::EventAction::interrupt( Common::ActionInterruptType type )
{
  if( !m_pSource )
    return;

  m_interruptType = type;

  try
  {

    auto control = makeActorControl( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 0x04, m_id );

    if( m_pSource->isPlayer() )
    {
      auto control1 = makeActorControlSelf( m_pSource->getId(), ActorControlType::FreeEventPos, m_eventId );

      //m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::NoCombat );
      //m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
      m_pSource->sendToInRangeSet( control );
      m_pSource->sendToInRangeSet( control1 );

      m_pSource->getAsPlayer()->queuePacket( control1 );
      m_pSource->getAsPlayer()->queuePacket( control );
      m_pSource->getAsPlayer()->eventFinish( m_eventId, 1 );

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
