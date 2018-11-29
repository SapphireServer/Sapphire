#include <Util/Util.h>
#include <Exd/ExdDataGenerated.h>
#include <Logging/Logger.h>
#include <Network/CommonActorControl.h>
#include <Util/UtilMath.h>

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/EffectPacket.h"

#include "Actor/Player.h"

#include "ActionTeleport.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

extern Sapphire::Framework g_fw;

Sapphire::Action::ActionTeleport::ActionTeleport()
{
  m_handleActionType = HandleActionType::Event;
}

Sapphire::Action::ActionTeleport::ActionTeleport( Entity::CharaPtr pActor, uint16_t targetZone, uint16_t cost )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  m_startTime = 0;
  m_id = 5;
  m_handleActionType = HandleActionType::Teleport;
  m_castTime = pExdData->get< Sapphire::Data::Action >( 5 )->cast100ms * 100; // TODO: Add security checks.
  m_pSource = pActor;
  m_bInterrupt = false;
  m_targetAetheryte = targetZone;
  m_cost = cost;
}

Sapphire::Action::ActionTeleport::~ActionTeleport()
{

}

void Sapphire::Action::ActionTeleport::onStart()
{
  if( !m_pSource )
    return;

  m_startTime = Util::getTimeMs();

  auto castPacket = makeZonePacket< FFXIVIpcActorCast >( getId() );
  castPacket->data().action_id = 5;
  castPacket->data().unknown = 1;
  castPacket->data().cast_time = 5.0f;
  castPacket->data().target_id = m_pSource->getId();

  m_pSource->sendToInRangeSet( castPacket, true );
  m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );

}

void Sapphire::Action::ActionTeleport::onFinish()
{
  if( !m_pSource )
    return;

  auto pPlayer = m_pSource->getAsPlayer();

  // check we can finish teleporting
  if( pPlayer->getCurrency( Common::CurrencyType::Gil ) < m_cost )
  {
    onInterrupt();
    return;
  }

  pPlayer->removeCurrency( Common::CurrencyType::Gil, m_cost );

  pPlayer->unsetStateFlag( PlayerStateFlag::Casting );

  // TODO: not sure if this ever gets sent
  //auto control = makeActorControl142( m_pSource->getId(), Common::ActorControlType::TeleportDone );
  //m_pSource->sendToInRangeSet( control, false );

  pPlayer->setZoningType( ZoneingType::Teleport );

  auto effectPacket = std::make_shared< Server::EffectPacket >( getId(), pPlayer->getId(), 5 );
  effectPacket->setRotation( Math::Util::floatToUInt16Rot( pPlayer->getRot() ) );


  pPlayer->sendToInRangeSet( effectPacket, true );
  pPlayer->teleport( m_targetAetheryte );
}

void Sapphire::Action::ActionTeleport::onInterrupt()
{
  if( !m_pSource )
    return;

  m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );

  auto control = makeActorControl142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 0x04, m_id, 0 );
  m_pSource->sendToInRangeSet( control, true );

}
