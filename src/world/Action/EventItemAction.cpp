#include "EventItemAction.h"

#include <Actor/Player.h>
#include <Network/PacketWrappers/EffectPacket.h>

#include "Manager/PlayerMgr.h"
#include "Manager/EventMgr.h"

#include "Script/ScriptMgr.h"
#include <Service.h>
#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include <Util/UtilMath.h>
#include <Common.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World;
using namespace Sapphire::World::Action;

EventItemAction::EventItemAction( Sapphire::Entity::CharaPtr source, uint32_t eventItemId,
                                  Data::EventItemPtr eventItemActionData,
                                  uint32_t sequence, uint64_t targetId ) :
  m_eventItemAction( std::move( eventItemActionData ) )
{
  m_id = eventItemId;
  m_eventItem = eventItemId;
  m_pSource = std::move( source );
  m_sequence = sequence;
  m_targetId = targetId;
  m_interruptType = Common::ActionInterruptType::None;
  //m_actionKind = Common::SkillType::EventItem;
}

bool EventItemAction::init()
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto actionInfoPtr = exdData.get< Data::Action >( m_eventItemAction->action );

  m_castTimeMs = static_cast< uint32_t >( m_eventItemAction->castTime * 1000 );
  m_recastTimeMs = static_cast< uint32_t >( actionInfoPtr->recast100ms * 100 );
  m_cooldownGroup = actionInfoPtr->cooldownGroup;
  m_id = m_eventItemAction->action;
  return true;
}

void EventItemAction::execute()
{
  auto player = getSourceChara()->getAsPlayer();
  if( !player )
    return;

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  player->eventStart( m_targetId, m_eventItemAction->quest, Event::EventHandler::ActionResult, 0, 0 );
  scriptMgr.onEventItem( *player, m_eventItem, m_eventItemAction->quest, m_castTimeMs, m_targetId );
  player->checkEvent( m_eventItemAction->quest );
}

void EventItemAction::start()
{
  m_startTime = Common::Util::getTimeMs();
  if( !hasCastTime() )
    execute();
}
