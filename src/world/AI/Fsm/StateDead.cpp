#include "StateDead.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateDead::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{

}

void AI::Fsm::StateDead::onEnter( Entity::BNpc& bnpc )
{
  bnpc.hateListClear();
  bnpc.changeTarget( Common::INVALID_GAME_OBJECT_ID64 );
  bnpc.setStance( Common::Stance::Passive );
  bnpc.setOwner( nullptr );
}

void AI::Fsm::StateDead::onExit( Entity::BNpc& bnpc )
{

}

