#include "StateResumePath.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateResumePath::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
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

  if( bnpc.moveTo( bnpc.getRoamTargetPos() ) )
  {
    bnpc.setRoamTargetReached( true );
    bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
  }
}

void AI::Fsm::StateResumePath::onEnter( Entity::BNpc& bnpc )
{
  bnpc.setRoamTargetReached( false );

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityIgnoreDamage );

  // Get the active server path
  auto path = bnpc.getActiveServerPath();
  if( !path || path->points.empty() )
  {
    Logger::error( "No active server path found for resuming path" );
    // Fallback to spawn position if no path is available
    if( pNaviProvider )
      pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getSpawnPos() );
    return;
  }

  uint8_t currentIndex = bnpc.getActiveServerPathPointIndex();
  auto currentPos = bnpc.getPos();

  // Find the closest point with index >= currentIndex
  uint8_t closestPointIndex = currentIndex;
  float closestDistance = std::numeric_limits< float >::max();

  for( uint8_t i = currentIndex; i < path->points.size(); ++i )
  {
    auto pointPos = Common::FFXIVARR_POSITION3{
      path->position.x + path->points[ i ].Translation.x,
      path->position.y + path->points[ i ].Translation.y,
      path->position.z + path->points[ i ].Translation.z
    };

    float distance = std::sqrt(
      std::pow( currentPos.x - pointPos.x, 2 ) +
      std::pow( currentPos.y - pointPos.y, 2 ) +
      std::pow( currentPos.z - pointPos.z, 2 )
    );

    if( distance < closestDistance )
    {
      closestDistance = distance;
      closestPointIndex = i;
    }
  }

  // Set the closest point as the target
  bnpc.setActiveServerPathPointIndex( closestPointIndex );
  bnpc.setRoamTargetPos( {
    path->position.x + path->points[ closestPointIndex ].Translation.x,
    path->position.y + path->points[ closestPointIndex ].Translation.y,
    path->position.z + path->points[ closestPointIndex ].Translation.z
  } );

  Logger::debug( "Resuming path at point index {}", closestPointIndex );

  if( pNaviProvider )
    pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getRoamTargetPos() );
}

void AI::Fsm::StateResumePath::onExit( Entity::BNpc& bnpc )
{
  bnpc.setOwner( nullptr );
  bnpc.setRoamTargetReached( false );
  bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityNone );
}
