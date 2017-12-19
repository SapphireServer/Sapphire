#include "EventItemAction.h"

#include <Server_Common/Util/Util.h>
#include <Server_Common/Util/UtilMath.h>
#include <Server_Common/Logging/Logger.h>

#include <string.h>

#include "Actor/Player.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

extern Core::Logger g_log;

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::Action::EventItemAction::EventItemAction()
{
   m_handleActionType = HandleActionType::Event;
}

Core::Action::EventItemAction::EventItemAction( Entity::ActorPtr pActor, uint32_t eventId, uint16_t action,
                                                ActionCallback finishRef, ActionCallback interruptRef, uint64_t additional )
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

Core::Action::EventItemAction::~EventItemAction() = default;

void Core::Action::EventItemAction::onStart()
{
   if( !m_pSource )
      return;

   m_startTime = Util::getTimeMs();

   GamePacketNew< FFXIVIpcActorCast, ServerZoneIpcType > castPacket( m_pSource->getId() );

   castPacket.data().action_id = 1;
   castPacket.data().unknown = 3;
   castPacket.data().unknown_1 = m_id;
   castPacket.data().cast_time = 3.0f;
   castPacket.data().target_id = m_pSource->getId();

   m_pSource->sendToInRangeSet( castPacket, true );
   m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

}

void Core::Action::EventItemAction::onFinish()
{
   if( !m_pSource )
      return;

   try
   {
      GamePacketNew< FFXIVIpcEffect, ServerZoneIpcType > effectPacket( m_pSource->getId() );
      effectPacket.data().targetId = static_cast< uint32_t >( m_additional );
      effectPacket.data().actionAnimationId = 1;
//      effectPacket.data().unknown_3 = 3;
      effectPacket.data().actionTextId = m_id;
      effectPacket.data().unknown_5 = 2;
      effectPacket.data().numEffects = 1;
      effectPacket.data().rotation = Math::Util::floatToUInt16Rot( m_pSource->getRotation() );
      effectPacket.data().effectTarget = static_cast< uint32_t >( m_additional );

      m_pSource->getAsPlayer()->unsetStateFlag( Common::PlayerStateFlag::Casting );
      m_pSource->getAsPlayer()->sendStateFlags();
      m_pSource->sendToInRangeSet( effectPacket, true );

      if( m_onActionFinishClb )
         m_onActionFinishClb( *m_pSource->getAsPlayer(), m_eventId, m_additional );
   }
   catch( std::exception& e )
   {
      g_log.error( e.what() );
   }

}

void Core::Action::EventItemAction::onInterrupt()
{
   if( !m_pSource )
      return;

   try
   {

      auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt,
                                            0x219, 0x04, m_id );
      if( m_pSource->isPlayer() )
      {
         m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );
         m_pSource->getAsPlayer()->sendStateFlags();
         m_pSource->sendToInRangeSet( control, true );
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
