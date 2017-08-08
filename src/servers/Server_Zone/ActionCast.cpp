#include "ActionCast.h"

#include <Server_Common/Common.h>
#include <Server_Common/Util.h>
#include <Server_Common/UtilMath.h>
#include <Server_Common/ExdData.h>
#include <Server_Common/Logger.h>

#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"
#include "Player.h"

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;

Core::Action::ActionCast::ActionCast()
{
   m_actionType = Common::ActionType::Event;
}

Core::Action::ActionCast::ActionCast( Entity::ActorPtr pActor, Entity::ActorPtr pTarget, uint32_t actionId )
{
   m_startTime = 0;
   m_id = actionId;
   m_actionType = ActionType::Spell;
   m_castTime = g_exdData.m_actionInfoMap[actionId].cast_time; // TODO: Add security checks.
   m_pSource = pActor;
   m_pTarget = pTarget;
   m_bInterrupt = false;
}

Core::Action::ActionCast::~ActionCast()
{

}

void Core::Action::ActionCast::onStart()
{
   if( !m_pSource )
      return;

   m_pSource->getAsPlayer()->sendDebug( "onStart()" );
   m_startTime = Util::getTimeMs();

   GamePacketNew< FFXIVIpcActorCast > castPacket( getId() );

   castPacket.data().action_id = m_id;
   castPacket.data().unknown = 1;
   castPacket.data().cast_time = m_castTime;
   castPacket.data().target_id = m_pTarget->getId();

   m_pSource->sendToInRangeSet( castPacket, true );
   m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

}

void Core::Action::ActionCast::onFinish()
{
   if( !m_pSource )
      return;

   auto pPlayer = m_pSource->getAsPlayer();
   pPlayer->sendDebug( "onFinish()" );

   m_pTarget->onActionHostile( pPlayer->shared_from_this() );

   pPlayer->unsetStateFlag( PlayerStateFlag::Casting );
   pPlayer->sendStateFlags();

   GamePacketNew< FFXIVIpcEffect > effectPacket( pPlayer->getId() );
   effectPacket.data().targetId = m_pTarget->getId();
   effectPacket.data().actionAnimationId = m_id;
   effectPacket.data().unknown_2 = 0;
//   effectPacket.data().unknown_3 = 1;
   effectPacket.data().actionTextId = m_id;
   effectPacket.data().numEffects = 1;
   effectPacket.data().rotation = Math::Util::floatToUInt16Rot( pPlayer->getRotation() );
   effectPacket.data().effectTarget = m_pTarget->getId();
   effectPacket.data().effects[0].param1 = 30;
   effectPacket.data().effects[0].unknown_1 = 3;
   effectPacket.data().effects[0].unknown_2 = 1;
   effectPacket.data().effects[0].unknown_3 = 7;

   pPlayer->sendToInRangeSet( effectPacket, true );
   m_pTarget->takeDamage( 30 );
}

void Core::Action::ActionCast::onInterrupt()
{
   if( !m_pSource )
      return;

   m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
   m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

   auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt,
                                          0x219, 0x04, m_id, 1 );
   m_pSource->sendToInRangeSet( control, true );

}
