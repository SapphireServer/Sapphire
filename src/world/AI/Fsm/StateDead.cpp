#include "StateDead.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateDead::onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount )
{

}

void AI::Fsm::StateDead::onEnter( Entity::GameObjectPtr& pEntity )
{
  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    bnpc.hateListClear();
    bnpc.changeTarget( Common::INVALID_GAME_OBJECT_ID64 );
    bnpc.setStance( Common::Stance::Passive );
    bnpc.setOwner( nullptr );
  }
}

void AI::Fsm::StateDead::onExit( Entity::GameObjectPtr& pEntity )
{

}

