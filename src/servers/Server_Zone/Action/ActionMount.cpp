#include "ActionMount.h"

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

Core::Action::ActionMount::ActionMount()
{
   m_handleActionType = HandleActionType::Event;
}

Core::Action::ActionMount::ActionMount( Entity::ActorPtr pActor, uint16_t mountId )
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

   ZoneChannelPacket< FFXIVIpcActorCast > castPacket( m_pSource->getId() );

   castPacket.data().action_id = m_id;
   castPacket.data().skillType = Common::SkillType::MountSkill;
   castPacket.data().unknown_1 = m_id;
   // This is used for the cast bar above the target bar of the caster.
   castPacket.data().cast_time = static_cast< float >( m_castTime / 1000 );
   castPacket.data().target_id = m_pSource->getAsPlayer()->getId();

   m_pSource->sendToInRangeSet( castPacket, true );
   m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );
   m_pSource->getAsPlayer()->sendStateFlags();

}

void Core::Action::ActionMount::onFinish()
{
   if( !m_pSource )
      return;

   auto pPlayer = m_pSource->getAsPlayer();
   pPlayer->sendDebug( "ActionMount::onFinish()" );

   pPlayer->unsetStateFlag( PlayerStateFlag::Casting );
   pPlayer->sendStateFlags();

   ZoneChannelPacket< FFXIVIpcEffect > effectPacket( pPlayer->getId() );
   effectPacket.data().targetId = pPlayer->getId();
   effectPacket.data().actionAnimationId = m_id;
   // Affects displaying action name next to number in floating text
   effectPacket.data().unknown_62 = 13; 
   effectPacket.data().actionTextId = 4;
   effectPacket.data().numEffects = 1;
   effectPacket.data().rotation = Math::Util::floatToUInt16Rot( pPlayer->getRotation() );
   effectPacket.data().effectTarget = INVALID_GAME_OBJECT_ID;
   effectPacket.data().effects[0].effectType = ActionEffectType::Mount;
   effectPacket.data().effects[0].hitSeverity = ActionHitSeverityType::CritDamage;
   effectPacket.data().effects[0].value = m_id;

   pPlayer->sendToInRangeSet( effectPacket, true );

   pPlayer->mount( m_id );
}

void Core::Action::ActionMount::onInterrupt()
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
