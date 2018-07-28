#include "Action.h"

#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Script/ScriptMgr.h>

#include <Actor/Chara.h>
#include <Actor/Player.h>

#include <Exd/ExdDataGenerated.h>

#include <Network/CommonNetwork.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Network::Packets;

Core::Action::Action::Action( Entity::CharaPtr caster, Entity::CharaPtr target, uint32_t actionId ) :
   m_pSource( caster ),
   m_pTarget( target ),
   m_id( actionId ),
   m_castTime( 0 )
{
   auto pExdData = g_fw.get< Core::Data::ExdDataGenerated >();
   if( !pExdData )
      return;

   auto action = pExdData->get< Core::Data::Action >( actionId );

   m_cooldown = static_cast< uint16_t >( action->recast100ms * 10 );
}

uint32_t Core::Action::Action::getId() const
{
   return m_id;
}

Core::Common::HandleActionType Core::Action::Action::getHandleActionType() const
{
   return m_handleActionType;
}

Core::Entity::CharaPtr Core::Action::Action::getTargetChara() const
{
   return m_pTarget;
}

bool Core::Action::Action::isInterrupted() const
{
   return m_bInterrupt;
}

void Core::Action::Action::setInterrupted()
{
   m_bInterrupt = true;
}

uint64_t Core::Action::Action::getStartTime() const
{
   return m_startTime;
}

void Core::Action::Action::setStartTime( uint64_t startTime )
{
   m_startTime = startTime;
}

uint32_t Core::Action::Action::getCastTime() const
{
   return m_castTime;
}

void Core::Action::Action::setCastTime( uint32_t castTime )
{
   m_castTime = castTime;
}

Core::Entity::CharaPtr Core::Action::Action::getActionSource() const
{
   return m_pSource;
}

uint16_t Core::Action::Action::getCooldown() const
{
   return m_cooldown;
}

void Core::Action::Action::setCooldown( uint16_t cooldown )
{
   m_cooldown = cooldown;
}

void Core::Action::Action::startAction()
{
   m_startTime = Util::getTimeMs();

   onStart();

   // instantly fire the onFinish event when there's no cast time
   if( m_castTime == 0 )
      onFinish();
}

bool Core::Action::Action::update()
{
   // action has not been started yet
   if( m_startTime == 0 )
      return false;

   if( m_bInterrupt )
   {
      onInterrupt();

      return true;
   }

   uint64_t currTime = Util::getTimeMs();

   if( std::difftime( currTime, m_startTime ) > m_castTime )
   {
      onFinish();

      return true;
   }

   return false;
}

void Core::Action::Action::onFinish()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   if( !pScriptMgr )
      return;

   // todo: handling aoes? we need to send effects relevant to hit entities

   pScriptMgr->onCastFinish( *m_pSource, *m_pTarget, *this );
}

void Core::Action::Action::onInterrupt()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   if( !pScriptMgr )
      return;

   auto sourcePlayer = m_pSource->getAsPlayer();
   if( sourcePlayer )
   {
      // set cooldown on client
      sourcePlayer->queuePacket( boost::make_shared< Server::ActorControlPacket143 >(
         getId(), Network::ActorControl::SetActionCooldown, 1, m_id, 0 ) );
   }

   pScriptMgr->onCastInterrupt( *m_pSource, *this );
}

void Core::Action::Action::onStart()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   if( pScriptMgr )
      return;

   auto sourcePlayer = m_pSource->getAsPlayer();
   if( sourcePlayer )
   {
      // set cooldown on client
      sourcePlayer->queuePacket( boost::make_shared< Server::ActorControlPacket143 >(
         getId(), Network::ActorControl::SetActionCooldown, 1, m_id, m_cooldown ) );
   }

   pScriptMgr->onCastStart( *m_pSource, *m_pTarget, *this );
}
