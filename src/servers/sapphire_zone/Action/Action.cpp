#include "Action.h"

#include <Util/Util.h>
#include <Script/ScriptMgr.h>

#include "Framework.h"

extern Core::Framework g_fw;


Core::Action::Action::Action( Entity::CharaPtr caster, Entity::CharaPtr target, uint32_t actionId ) :
   m_pSource( caster ),
   m_pTarget( target ),
   m_id( actionId ),
   m_castTime( 0 )
{
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

void Core::Action::Action::start()
{
   m_startTime = Util::getTimeMs();

   onStart();
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
   if( pScriptMgr )
   {
      pScriptMgr->onCastFinish( *m_pSource, *m_pTarget, *this );
   }
}

void Core::Action::Action::onInterrupt()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   if( pScriptMgr )
   {
      pScriptMgr->onCastInterrupt( *m_pSource, *this );
   }
}

void Core::Action::Action::onStart()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   if( pScriptMgr )
   {
      pScriptMgr->onCastStart( *m_pSource, *m_pTarget, *this );
   }
}
