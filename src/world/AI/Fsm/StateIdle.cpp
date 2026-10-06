#include "StateIdle.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"

using namespace Sapphire::World;

void AI::Fsm::StateIdle::onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount )
{
  // bool hasQueuedAction = bnpc.hasAction();
}

void AI::Fsm::StateIdle::onEnter( Entity::GameObjectPtr& pEntity )
{
  if( auto pBNpc = pEntity->getAsBNpc() )
    pBNpc->setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
}

void AI::Fsm::StateIdle::onExit( Entity::GameObjectPtr& pEntity )
{
}

