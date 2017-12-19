#include "ActionTeleport.h"

#include <Server_Common/Util/Util.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Logging/Logger.h>

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Actor/Player.h"

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;

Core::Action::ActionTeleport::ActionTeleport()
{
   m_handleActionType = HandleActionType::Event;
}

Core::Action::ActionTeleport::ActionTeleport( Entity::ActorPtr pActor, uint16_t targetZone, uint16_t cost )
{
   m_startTime = 0;
   m_id = 5;
   m_handleActionType = HandleActionType::Teleport;
   m_castTime = g_exdData.getActionInfo(5)->cast_time; // TODO: Add security checks.
   m_pSource = pActor;
   m_bInterrupt = false;
   m_targetAetheryte = targetZone;
   m_cost = cost;
}

Core::Action::ActionTeleport::~ActionTeleport()
{

}

void Core::Action::ActionTeleport::onStart()
{
   if( !m_pSource )
      return;

   m_startTime = Util::getTimeMs();

   ZoneChannelPacket< FFXIVIpcActorCast > castPacket( m_pSource->getId() );

   castPacket.data().action_id = 5;
   castPacket.data().unknown = 1;
   castPacket.data().cast_time = 5.0f;
   castPacket.data().target_id = m_pSource->getId();

   m_pSource->sendToInRangeSet( castPacket, true );
   m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

}

void Core::Action::ActionTeleport::onFinish()
{
   if( !m_pSource )
      return;

   auto pPlayer = m_pSource->getAsPlayer();

   // check we can finish teleporting
   if( pPlayer->getCurrency( Inventory::CurrencyType::Gil ) < m_cost )
   {
      onInterrupt();
      return;
   }

   pPlayer->removeCurrency( Inventory::CurrencyType::Gil, m_cost );
 
   pPlayer->unsetStateFlag( PlayerStateFlag::Casting );
   pPlayer->sendStateFlags();

   // TODO: not sure if this ever gets sent
   //auto control = Network::Packets::Server::ActorControlPacket142( m_pSource->getId(), Common::ActorControlType::TeleportDone );
   //m_pSource->sendToInRangeSet( control, false );

   pPlayer->setZoningType( ZoneingType::Teleport );

   ZoneChannelPacket< FFXIVIpcEffect > effectPacket( pPlayer->getId() );
   effectPacket.data().targetId = pPlayer->getId();
   effectPacket.data().actionAnimationId = 5;
   //effectPacket.data().unknown_3 = 1;
   effectPacket.data().actionTextId = 5;
   effectPacket.data().unknown_5 = 1;
   effectPacket.data().numEffects = 1;
   effectPacket.data().rotation = static_cast< uint16_t >( 0x8000 * ( ( pPlayer->getRotation() + 3.1415926 ) ) / 3.1415926 );
   effectPacket.data().effectTarget = pPlayer->getId();
   pPlayer->sendToInRangeSet( effectPacket, true );

   pPlayer->teleport( m_targetAetheryte );


}

void Core::Action::ActionTeleport::onInterrupt()
{
   if( !m_pSource )
      return;

   m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

   auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt,
                                         0x219, 0x04, m_id, 0 );
   m_pSource->sendToInRangeSet( control, true );

}
