#include "StateRoam.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateRoam::onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( pEntity->getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    if( bnpc.hasFlag( Entity::NoRoam ) || bnpc.hasFlag( Entity::Immobile ) || !bnpc.pathingActive() )
    {
      bnpc.setRoamTargetReached( true );
      return;
    }

    if( pNaviProvider )
      pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getRoamTargetPos() );

    if( bnpc.moveTo( bnpc.getRoamTargetPos() ) )
    {
      bnpc.setRoamTargetReached( true );
      bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );

      if( bnpc.getEnemyType() == Common::Friendly )
        bnpc.setRot( bnpc.getSpawnRot() );
    }
  }
}

void AI::Fsm::StateRoam::onEnter( Entity::GameObjectPtr& pEntity )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( pEntity->getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    if( !pNaviProvider || bnpc.hasFlag( Entity::NoRoam ) || bnpc.hasFlag( Entity::Immobile ) )
    {
      bnpc.setRoamTargetReached( true );
      return;
    }

    if( bnpc.getEnemyType() == Common::Friendly )
    {
      bnpc.setRoamTargetPos( bnpc.getSpawnPos() );
    }
    else
    {
      auto pos = pNaviProvider->findRandomPositionInCircle( bnpc.getSpawnPos(), bnpc.getInstanceObjectInfo()->WanderingRange );
      bnpc.setRoamTargetPos( pos );
    }
  }
}

void AI::Fsm::StateRoam::onExit( Entity::GameObjectPtr& pEntity )
{
  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    bnpc.setRoamTargetReached( false );
  }
}

