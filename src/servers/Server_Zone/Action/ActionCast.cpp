#include "ActionCast.h"

#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Util/Util.h>
#include <src/servers/Server_Common/Util/UtilMath.h>
#include <src/servers/Server_Common/Exd/ExdData.h>
#include <src/servers/Server_Common/Logging/Logger.h>

#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Script/ScriptManager.h"

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

Core::Action::ActionCast::ActionCast( Entity::ActorPtr pActor, Entity::ActorPtr pTarget, uint32_t actionId )
{
   m_startTime = 0;
   m_id = actionId;
   m_handleActionType = HandleActionType::Spell;
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

   GamePacketNew< FFXIVIpcActorCast, ServerZoneIpcType > castPacket( getId() );

   castPacket.data().action_id = m_id;
   castPacket.data().unknown = 1;
   castPacket.data().cast_time = m_castTime / 1000; // This is used for the cast bar above the target bar of the caster.
   castPacket.data().target_id = m_pTarget->getId();

   m_pSource->sendToInRangeSet( castPacket, false );
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

   g_scriptMgr.onCastFinish( pPlayer, m_pTarget, m_id );
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
