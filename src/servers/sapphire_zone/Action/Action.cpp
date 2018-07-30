#include "Action.h"

#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Script/ScriptMgr.h>

#include <Actor/Chara.h>
#include <Actor/Player.h>

#include <Exd/ExdDataGenerated.h>

#include <Network/CommonNetwork.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/ActorControlPacket142.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>
#include <sapphire_zone/Network/PacketWrappers/EffectPacket.h>

#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;
using namespace Core::Network;
using namespace Core::Network::Packets;
using namespace Core::Network::ActorControl;

Core::Action::Action::Action( Entity::CharaPtr caster, Entity::CharaPtr target, uint32_t actionId ) :
   m_pSource( caster ),
   m_pTarget( target ),
   m_id( actionId ),
   m_bInterrupt( false )
{
   auto pExdData = g_fw.get< Core::Data::ExdDataGenerated >();
   if( !pExdData )
      return;

   auto action = pExdData->get< Core::Data::Action >( actionId );

   m_cooldown = static_cast< uint16_t >( action->recast100ms * 10 );
   m_castTime = static_cast< uint32_t >( action->cast100ms ) * 100;
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

bool Core::Action::Action::hasCastTime() const
{
   return m_castTime != 0;
}

uint64_t Core::Action::Action::getParam() const
{
   return m_param;
}

void Core::Action::Action::setParam( uint64_t param )
{
   m_param = param;
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

void Core::Action::Action::setSkillType( uint8_t skillType )
{
   m_skillType = static_cast< Common::SkillType >( skillType );
}

Core::Common::SkillType Core::Action::Action::getSkillType() const
{
   return m_skillType;
}

void Core::Action::Action::startAction()
{
   m_startTime = Util::getTimeMs();

   onStart();

   // instantly fire the onFinish event when there's no cast time
   if( !hasCastTime() )
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

   if( hasCastTime() )
   {
      if( auto player = m_pSource->getAsPlayer() )
         player->unsetStateFlag( PlayerStateFlag::Casting );
   }

   // todo: handling aoes? we need to send effects relevant to hit entities
   // todo: combo actions?

   auto effectPacket = boost::make_shared< Server::EffectPacket >( m_pSource->getId(), m_pTarget->getId(), getId() );
   effectPacket->setRotation( Math::Util::floatToUInt16Rot( m_pSource->getRot() ) );

   m_pSource->sendToInRangeSet( effectPacket, true );

   if( auto player = m_pSource->getAsPlayer() )
      player->sendDebug( "Action::onFinish()" );

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
         m_pSource->getId(), ActorControl::SetActionCooldown, 1, m_id, 0 ) );

      if( hasCastTime() )
      {
         sourcePlayer->unsetStateFlag( PlayerStateFlag::Casting );

         auto interruptPacket = boost::make_shared< Server::ActorControlPacket142 >(
            m_pSource->getId(), ActorControl::CastInterrupt, 0x219, 1, m_id, 0 );

         sourcePlayer->queuePacket( interruptPacket );
      }

      sourcePlayer->sendDebug( "Action::onInterrupt()" );
   }

   pScriptMgr->onCastInterrupt( *m_pSource, *this );
}

void Core::Action::Action::onStart()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
   if( !pScriptMgr )
      return;

   if( hasCastTime() )
   {
      auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( m_pSource->getId() );

      castPacket->data().action_id = static_cast< uint16_t >( m_id );
      castPacket->data().skillType = m_skillType;
      castPacket->data().unknown_1 = m_id;
      // This is used for the cast bar above the target bar of the caster.
      castPacket->data().cast_time = static_cast< float >( m_castTime / 1000 );
      castPacket->data().target_id = m_pTarget->getId();

      m_pSource->sendToInRangeSet( castPacket, true );
   }

   auto sourcePlayer = m_pSource->getAsPlayer();
   if( sourcePlayer )
   {
      // set cooldown on client
      // todo: maintain a list of cooldowns for each player and check before casting
      sourcePlayer->queuePacket( boost::make_shared< Server::ActorControlPacket143 >(
         sourcePlayer->getId(), ActorControl::SetActionCooldown, 1, m_id, m_cooldown ) );

      if( hasCastTime() )
         sourcePlayer->setStateFlag( PlayerStateFlag::Casting );

      sourcePlayer->sendDebug( "Action::onStart()" );
   }

   pScriptMgr->onCastStart( *m_pSource, *m_pTarget, *this );
}
