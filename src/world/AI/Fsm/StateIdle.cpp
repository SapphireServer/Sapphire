#include "StateIdle.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"

using namespace Sapphire::World;

void AI::Fsm::StateIdle::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{
  bool hasQueuedAction = bnpc.checkAction();
}

void AI::Fsm::StateIdle::onEnter( Entity::BNpc& bnpc )
{
  bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
}

void AI::Fsm::StateIdle::onExit( Entity::BNpc& bnpc )
{
}

