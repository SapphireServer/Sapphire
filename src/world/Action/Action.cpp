#include "Action.h"

#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include "Framework.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;


Sapphire::Action::Action::Action() = default;
Sapphire::Action::Action::~Action() = default;

Sapphire::Action::Action::Action( Entity::CharaPtr caster, Entity::CharaPtr target,
                                  uint16_t actionId, FrameworkPtr fw ) :

                                  m_pSource( std::move( caster ) ),
                                  m_pTarget( std::move( target ) ),
                                  m_pFw( std::move( fw ) ),
                                  m_id( actionId ),
                                  m_startTime( 0 )
{
  auto exdData = m_pFw->get< Data::ExdDataGenerated >();
  assert( exdData );

  auto actionData = exdData->get< Data::Action >( actionId );
  // todo: clients can crash the server here, ideally we do this check outside of the action anyway
  assert( actionData );

  m_castTime = actionData->cast100ms * 100;
}

uint16_t Sapphire::Action::Action::getId() const
{
  return m_id;
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getTargetChara() const
{
  return m_pTarget;
}

bool Sapphire::Action::Action::isInterrupted() const
{
  return m_bInterrupt;
}

void Sapphire::Action::Action::setInterrupted()
{
  m_bInterrupt = true;
}

void Sapphire::Action::Action::start()
{
  m_startTime = Util::getTimeMs();

  onStart();
}

uint32_t Sapphire::Action::Action::getCastTime() const
{
  return m_castTime;
}

void Sapphire::Action::Action::setCastTime( uint32_t castTime )
{
  m_castTime = castTime;
}

bool Sapphire::Action::Action::isCastedAction() const
{
  return m_castTime > 0;
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getActionSource() const
{
  return m_pSource;
}

bool Sapphire::Action::Action::update()
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

  if( ( currTime - m_startTime ) > m_castTime )
  {
    onFinish();
    return true;
  }
  return false;
}

void Sapphire::Action::Action::onStart()
{
  assert( m_pSource );

  if( isCastedAction() )
  {
    m_pSource->getAsPlayer()->sendDebug( "onStart()" );
    m_startTime = Util::getTimeMs();

    auto castPacket = makeZonePacket< FFXIVIpcActorCast >( getId() );

    castPacket->data().action_id = m_id;
    castPacket->data().skillType = Common::SkillType::Normal;
    castPacket->data().unknown_1 = m_id;
    // This is used for the cast bar above the target bar of the caster.
    castPacket->data().cast_time = static_cast< float >( m_castTime / 1000.f );
    castPacket->data().target_id = m_pTarget->getId();

    m_pSource->sendToInRangeSet( castPacket, true );
    m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );
  }
}

void Sapphire::Action::Action::onInterrupt()
{
  assert( m_pSource );

  if( isCastedAction() )
  {
    //m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
    m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );

    auto control = makeActorControl142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

    // Note: When cast interrupt from taking too much damage, set the last value to 1. This enables the cast interrupt effect. Example:
    // auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

    m_pSource->sendToInRangeSet( control, true );
  }
}

void Sapphire::Action::Action::onFinish()
{
  assert( m_pSource );

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  auto pPlayer = m_pSource->getAsPlayer();
  pPlayer->sendDebug( "onFinish()" );

  if( isCastedAction() )
  {
    pPlayer->unsetStateFlag( PlayerStateFlag::Casting );

    /*auto control = ActorControlPacket143( m_pTarget->getId(), ActorControlType::Unk7,
                                            0x219, m_id, m_id, m_id, m_id );
    m_pSource->sendToInRangeSet( control, true );*/

    pScriptMgr->onCastFinish( *pPlayer, m_pTarget, m_id );
  }
}
