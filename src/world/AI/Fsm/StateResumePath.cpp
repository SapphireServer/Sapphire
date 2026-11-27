#include "StateResumePath.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

#include <AI/Controller/Controller.h>
#include <AI/Controller/BNpcOverworldController.h>

using namespace Sapphire::World;

void AI::Fsm::StateResumePath::onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount )
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
    }
  }
}

void AI::Fsm::StateResumePath::onEnter( Entity::GameObjectPtr& pEntity )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( pEntity->getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;


    bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityIgnoreDamage );
    bnpc.setRoamTargetReached( false );

    auto pController = pBNpc->getController();
    auto& path = pController->getPath();

    auto currentPos = pBNpc->getPos();

    uint8_t closestPointIndex = path.m_currPointIndex;
    float closestDistance = std::numeric_limits< float >::max();

    for( auto i = closestPointIndex; i < path.m_points.size(); ++i )
    {
      const auto& pointPos = path.m_points[ i ];
      float distance = std::sqrt(
              std::pow( currentPos.x - pointPos.x, 2 ) +
              std::pow( currentPos.y - pointPos.y, 2 ) +
              std::pow( currentPos.z - pointPos.z, 2 ) );

      if( distance < closestDistance )
      {
        closestDistance = distance;
        closestPointIndex = i;
      }
    }

    path.m_currPointIndex = closestPointIndex;

    if( path.m_points.size() > path.m_currPointIndex )
      bnpc.setRoamTargetPos( path.m_points[ path.m_currPointIndex ] );

    /*
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
      auto pointPos = Common::Vector3{
              path->position.x + path->points[ i ].Translation.x,
              path->position.y + path->points[ i ].Translation.y,
              path->position.z + path->points[ i ].Translation.z };

      float distance = std::sqrt(
              std::pow( currentPos.x - pointPos.x, 2 ) +
              std::pow( currentPos.y - pointPos.y, 2 ) +
              std::pow( currentPos.z - pointPos.z, 2 ) );

      if( distance < closestDistance )
      {
        closestDistance = distance;
        closestPointIndex = i;
      }
    }

    // Set the closest point as the target
    bnpc.setActiveServerPathPointIndex( closestPointIndex );
    bnpc.setRoamTargetPos( { path->position.x + path->points[ closestPointIndex ].Translation.x,
                             path->position.y + path->points[ closestPointIndex ].Translation.y,
                             path->position.z + path->points[ closestPointIndex ].Translation.z } );

    Logger::debug( "Resuming path at point index {}", closestPointIndex );

    */
    if( pNaviProvider )
      pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getRoamTargetPos() );
  }
}

void AI::Fsm::StateResumePath::onExit( Entity::GameObjectPtr& pEntity )
{
  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    bnpc.setOwner( nullptr );
    bnpc.setRoamTargetReached( false );
    bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityNone );
  }
}
