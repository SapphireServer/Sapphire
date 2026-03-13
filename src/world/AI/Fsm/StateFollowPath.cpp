#include "StateFollowPath.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateFollowPath::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( bnpc.hasFlag( Entity::NoRoam ) || bnpc.hasFlag( Entity::Immobile ) || !bnpc.pathingActive() )
  {
    bnpc.setRoamTargetReached( true );
    return;
  }

  if( pNaviProvider )
    pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getRoamTargetPos() );

  auto path = bnpc.getActiveServerPath();
  if( !path )
    onEnter( bnpc );


  if( bnpc.moveTo( bnpc.getRoamTargetPos() ) )
  {
    uint8_t currPoint = bnpc.getActiveServerPathPointIndex();
    auto pathSize = bnpc.getActiveServerPath()->points.size();

    if( currPoint < pathSize && !bnpc.isReversePath() )
    {
      // go to next point
      bnpc.setActiveServerPathPointIndex( currPoint + 1 );

      // Check if we've reached the last point, if so reverse the path
      if( currPoint + 1 >= pathSize )
      {
        // eached end, reverse
        bnpc.setReversePath( true );
        bnpc.setActiveServerPathPointIndex( pathSize - 1 );
      }
    }
    else if( currPoint > 0 && bnpc.isReversePath() )
    {
      // to previous point
      bnpc.setActiveServerPathPointIndex( currPoint - 1 );

      // Check if we've reached the first point, if so reverse the path
      if( currPoint - 1 <= 0 )
      {
        // reached start, reverse
        bnpc.setReversePath( false );
        bnpc.setActiveServerPathPointIndex( 0 );
      }
    }

    if( bnpc.getActiveServerPathPointIndex() >= bnpc.getActiveServerPath()->points.size() )
      return;

    auto path = bnpc.getActiveServerPath();
    if( !path )
      return;

    // set target
    bnpc.setRoamTargetPos( {
      path->position.x + path->points[ bnpc.getActiveServerPathPointIndex() ].Translation.x,
      path->position.y + path->points[ bnpc.getActiveServerPathPointIndex() ].Translation.y,
      path->position.z + path->points[ bnpc.getActiveServerPathPointIndex() ].Translation.z
    } );

  }

}

void AI::Fsm::StateFollowPath::onEnter( Entity::BNpc& bnpc )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( bnpc.getInstanceObjectInfo()->ServerPathId == 0 )
    return;

  auto serverPath = pZone->getServerPath( bnpc.getInstanceObjectInfo()->ServerPathId );
  if( !serverPath )
  {
    Logger::error( "Failed to get server path {} for instance object {} in zone {}", bnpc.getInstanceObjectInfo()->ServerPathId, bnpc.getId(), pZone->getInternalName() );
    return;
  }


  bnpc.setActiveServerPath( serverPath );
  bnpc.setActiveServerPathPointIndex( 0 );

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
    if( serverPath->points.empty() )
      return;

    bnpc.setRoamTargetPos( {
      serverPath->position.x + serverPath->points[ 0 ].Translation.x,
      serverPath->position.y + serverPath->points[ 0 ].Translation.y,
      serverPath->position.z + serverPath->points[ 0 ].Translation.z
    } );
  }
}

void AI::Fsm::StateFollowPath::onExit( Entity::BNpc& bnpc )
{
  bnpc.setRoamTargetReached( false );
}
