#include "ActionCast.h"

#include <Server_Common/Common.h>
#include <Server_Common/Util/Util.h>
#include <Server_Common/Util/UtilMath.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Logging/Logger.h>

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include "Actor/Player.h"
#include "Script/ScriptManager.h"

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;
extern Core::Scripting::ScriptManager g_scriptMgr;

Core::Action::ActionCast::ActionCast()
{
   m_handleActionType = Common::HandleActionType::Event;
}

Core::Action::ActionCast::ActionCast( Entity::ActorPtr pActor, Entity::ActorPtr pTarget, uint16_t actionId )
{
   m_startTime = 0;
   m_id = actionId;
   m_handleActionType = HandleActionType::Spell;
   m_castTime = g_exdData.getActionInfo( actionId )->cast_time; // TODO: Add security checks.
   m_pSource = pActor;
   m_pTarget = pTarget;
   m_bInterrupt = false;
}

Core::Action::ActionCast::~ActionCast() = default;

void Core::Action::ActionCast::onStart()
{
   if( !m_pSource )
      return;

   m_pSource->getAsPlayer()->sendDebug( "onStart()" );
   m_startTime = Util::getTimeMs();

   ZoneChannelPacket< FFXIVIpcActorCast > castPacket( m_pSource->getId() );

   castPacket.data().action_id = m_id;
   castPacket.data().skillType = Common::SkillType::Normal;
   castPacket.data().unknown_1 = m_id;
   // This is used for the cast bar above the target bar of the caster.
   castPacket.data().cast_time = static_cast< float >( m_castTime / 1000 );
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

   pPlayer->unsetStateFlag( PlayerStateFlag::Casting );
   pPlayer->sendStateFlags();

   /*auto control = ActorControlPacket143( m_pTarget->getId(), ActorControlType::Unk7,
                                           0x219, m_id, m_id, m_id, m_id );
   m_pSource->sendToInRangeSet( control, true );*/

   g_scriptMgr.onCastFinish( *pPlayer, m_pTarget, m_id );
}

void Core::Action::ActionCast::onInterrupt()
{
   if( !m_pSource )
      return;

   m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
   m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

   auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt,
                                         0x219, 1, m_id, 0 );

   // Note: When cast interrupt from taking too much damage, set the last value to 1. This enables the cast interrupt effect. Example:
   // auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

   m_pSource->sendToInRangeSet( control, true );

}
