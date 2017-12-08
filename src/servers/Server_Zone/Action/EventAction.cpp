#include <Server_Common/Util/Util.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>

#include "EventAction.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Server_Zone/Actor/Player.h"
#include "Server_Zone/Event/Event.h"

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Action::EventAction::EventAction()
{
   m_handleActionType = HandleActionType::Event;
}

Core::Action::EventAction::EventAction( Entity::ActorPtr pActor, uint32_t eventId, uint16_t action,
                                        ActionCallback finishRef, ActionCallback interruptRef, uint64_t additional )
{
   m_additional = additional;
   m_handleActionType = HandleActionType::Event;
   m_eventId = eventId;
   m_id = action;
   m_castTime = g_exdData.m_EventActionInfoMap[action].castTime; // TODO: Add security checks.
   m_onActionFinishClb = finishRef;
   m_onActionInterruptClb = interruptRef;
   m_pSource = pActor;
   m_bInterrupt = false;
}

Core::Action::EventAction::~EventAction()
{

}

void Core::Action::EventAction::onStart()
{
   if( !m_pSource )
      return;

   m_startTime = Util::getTimeMs();

   auto control = ActorControlPacket142( m_pSource->getId(), Common::ActorControlType::CastStart,
                                         1, m_id, 0x4000004E );

   if( m_pSource->isPlayer() )
   {
      m_pSource->sendToInRangeSet( control, true );
      m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::SomeFlag );
      m_pSource->getAsPlayer()->sendStateFlags();
   }
   else
      m_pSource->sendToInRangeSet( control );
}

void Core::Action::EventAction::onFinish()
{
   if( !m_pSource )
      return;

   try
   {
      auto pEvent = m_pSource->getAsPlayer()->getEvent( m_eventId );

      pEvent->setPlayedScene( false );

      if( m_onActionFinishClb )
         m_onActionFinishClb( *m_pSource->getAsPlayer(), m_eventId, m_additional );

      auto control = ActorControlPacket142( m_pSource->getId(), Common::ActorControlType::CastStart, 0, m_id );
      
      if( !pEvent->hasPlayedScene() )
         m_pSource->getAsPlayer()->eventFinish( m_eventId, 1 );
      else
         pEvent->setPlayedScene( false );

      if( m_pSource->isPlayer() )
      {
         m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::SomeFlag );
         m_pSource->getAsPlayer()->sendStateFlags();
         m_pSource->sendToInRangeSet( control, true );
      }
      else
         m_pSource->sendToInRangeSet( control );
   }
   catch( std::exception& e )
   {
      g_log.error( e.what() );
   }

}

void Core::Action::EventAction::onInterrupt()
{
   if( !m_pSource )
      return;

   try
   {

      auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt,
                                            0x219, 0x04, m_id );

      if( m_pSource->isPlayer() )
      {
         auto control1 = ActorControlPacket143( m_pSource->getId(), ActorControlType::FreeEventPos, m_eventId );

         m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::NoCombat );
         m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
         m_pSource->getAsPlayer()->sendStateFlags();
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
      g_log.error( e.what() );
   }

}
