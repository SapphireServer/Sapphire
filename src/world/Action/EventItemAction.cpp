#include "EventItemAction.h"
#include <Network/CommonActorControl.h>

#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include <Actor/Player.h>

#include "Manager/EventMgr.h"
#include "Manager/PlayerMgr.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Script/ScriptMgr.h"
#include <Service.h>

#include <Common.h>


using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::World::Action;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;

EventItemAction::EventItemAction( Sapphire::Entity::CharaPtr source, uint32_t eventItemId,
                                  std::shared_ptr< Excel::ExcelStruct< Excel::EventItem > > eventItemActionData,
                                  uint32_t sequence, uint64_t targetId ) : m_eventItemAction( std::move( eventItemActionData ) )
{
  m_id = eventItemId;
  m_eventItem = eventItemId;
  m_pSource = std::move( source );
  m_sequence = sequence;
  m_targetId = targetId;
  m_interruptType = Common::ActionInterruptType::None;
  m_actionKind = Common::SkillType::EventItem;
}

bool EventItemAction::init()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto actionInfoPtr = exdData.getRow< Excel::Action >( m_eventItemAction->data().Action );

  m_castTimeMs = static_cast< uint32_t >( m_eventItemAction->data().CastTime * 1000 );
  m_recastTimeMs = static_cast< uint32_t >( actionInfoPtr->data().RecastTime * 100 );
  m_cooldownGroup = actionInfoPtr->data().RecastGroup;
  m_id = m_eventItemAction->data().Action;
  return true;
}

void EventItemAction::execute()
{
  Sapphire::Entity::PlayerPtr pPlayer = m_pSource->getAsPlayer();
  if( !pPlayer )
    return;

  Manager::PlayerMgr::sendDebug( *pPlayer, "EventItemAction type {0} execute called.", m_eventItemAction->data().Action );
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  eventMgr.eventStart( *pPlayer, m_targetId, m_eventItemAction->data().EventHandler, Event::EventHandler::ActionResult, 0, 0 );
  scriptMgr.onEventItem( *pPlayer, m_eventItem, m_eventItemAction->data().EventHandler, m_targetId );
  eventMgr.checkEvent( *pPlayer, m_eventItemAction->data().EventHandler );
}

void EventItemAction::onStart()
{
  m_startTime = Common::Util::getTimeMs();
}