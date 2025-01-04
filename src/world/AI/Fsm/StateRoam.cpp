#include "StateRoam.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateRoam::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( bnpc.hasFlag( Entity::NoRoam ) )
  {
    bnpc.setRoamTargetReached( true );
    return;
  }

  if( pNaviProvider )
    pNaviProvider->setMoveTarget( bnpc, bnpc.getRoamTargetPos() );

  if( bnpc.moveTo( bnpc.getRoamTargetPos() ) )
  {
    bnpc.setRoamTargetReached( true );
    bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
  }

}

void AI::Fsm::StateRoam::onEnter( Entity::BNpc& bnpc )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( !pNaviProvider )
  {
    bnpc.setRoamTargetReached( true );
    return;
  }

  auto pos = pNaviProvider->findRandomPositionInCircle( bnpc.getSpawnPos(), bnpc.getInstanceObjectInfo()->WanderingRange );
  bnpc.setRoamTargetPos( pos );
}

void AI::Fsm::StateRoam::onExit( Entity::BNpc& bnpc )
{
  bnpc.setRoamTargetReached( false );
}

