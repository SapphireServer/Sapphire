#include "ItemManipulationAction.h"

#include <Exd/ExdData.h>

#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/BNpc.h"

#include <Logging/Logger.h>

#include <Service.h>
#include "WorldServer.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

ItemManipulationAction::ItemManipulationAction( Entity::CharaPtr source, uint32_t actionId, uint16_t requestId,
                                                std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData, uint32_t delayTime ) :
  m_delayTimeMs( delayTime )
{
  m_id = actionId;
  m_pSource = std::move( source );
  m_actionData = std::move( actionData );
  m_requestId = requestId;
}

void ItemManipulationAction::start()
{
  assert( m_pSource );
  m_startTime = Common::Util::getTimeMs();

  onStart();

  execute();
}

void ItemManipulationAction::execute()
{
  assert( m_pSource );

  m_actionResultBuilder->sendActionResults( m_hitActors );
}

void ItemManipulationAction::onFinish()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  // send execute event to action script
  scriptMgr.onExecute( *this );
}

bool ItemManipulationAction::update()
{
  // action has not been started yet
  if( m_startTime == 0 )
    return false;

  uint64_t tickCount = Common::Util::getTimeMs();
  uint32_t delayTime = m_delayTimeMs;

  if( std::difftime( static_cast< time_t >( tickCount ), static_cast< time_t >( m_startTime ) ) > delayTime )
  {
    onFinish();
    return true;
  }

  return false;
}