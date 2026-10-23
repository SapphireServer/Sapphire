#include "StateFollowPath.h"
#include "Actor/GameObject.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

#include <AI/Controller/Controller.h>
#include <AI/Controller/BNpcOverworldController.h>

using namespace Sapphire::World;

void AI::Fsm::StateFollowPath::onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( pEntity->getTerritoryId() );
  if( !pZone )
    return;

  auto pNaviProvider = pZone->getNaviProvider();

  if( auto pController = pEntity->getController() )
  {
    // todo: support pathing for non bnpc?
    auto pBNpc = pEntity->getAsBNpc();

    if( !pBNpc )
      return;

    auto& path = pController->getPath();
    if( !path.m_active )
      return;

    // we don't wanna account for radius in this path request but leave some leeway in case pos is slightly off
    if( path.m_flags & AI::Controller::Controller::PathFlags::PathToExactPos )
      path.m_targetReachedDist = 0.5f;

    const auto now = Common::Util::getTimeMs();
    const auto elapsed = now - m_lastTick;
    const bool ignoreNavmesh = path.m_flags & AI::Controller::Controller::PathFlags::IgnoreNavmesh;

    // Navi target updates do not need to be requested every actor tick. Direct
    // paths do, because the controller itself advances the actor position.
    if( !ignoreNavmesh && elapsed < 250 )
      return;

    if( pBNpc->hasFlag( Entity::NoRoam ) || pBNpc->hasFlag( Entity::Immobile ) || !pBNpc->pathingActive() )
    {
      pBNpc->setRoamTargetReached( true );
      return;
    }

    if( !ignoreNavmesh && ( !pNaviProvider || pBNpc->getAgentId() == -1 ) )
      return;

    const auto moveDirectly = [ & ]( const Common::Vector3& destination )
    {
      const auto currentPos = pBNpc->getPos();
      const auto delta = destination - currentPos;
      const auto distance = delta.length();
      const auto step = pBNpc->getCurrentSpeed() * static_cast< float >( elapsed ) / 1000.f;

      pBNpc->face( destination );
      if( distance <= pBNpc->getNaviTargetReachedDistance() || step >= distance )
      {
        pBNpc->setPos( destination );
        return true;
      }

      if( step > 0.f )
        pBNpc->setPos( currentPos + delta.normalize() * step );
      return false;
    };

    Common::Vector3 targetPos = pBNpc->getPos();

    // path to target
    if( path.m_type == AI::Controller::Controller::PathType::TargetId )
    {
      auto pEntity = pZone->getEntityById( path.m_targetId );
      if( pEntity )
      {
        targetPos = pEntity->getPos();
        path.m_targetPos = targetPos;
      }
    }

    if( path.m_type == AI::Controller::Controller::PathType::FixedPos )
      targetPos = path.m_targetPos;

    bool reachedTarget = false;
    if( path.m_type == AI::Controller::Controller::PathType::TargetId || path.m_type == AI::Controller::Controller::PathType::FixedPos )
    {
      auto distance = Common::Util::distance( pBNpc->getPos(), targetPos );
      auto distXZ = Common::Util::distance2D( pBNpc->getPos().x, pBNpc->getPos().z, targetPos.x, targetPos.z );
      auto distY = std::fabs( pBNpc->getPos().y - targetPos.y );

      reachedTarget = ignoreNavmesh ? moveDirectly( targetPos ) : pBNpc->moveTo( targetPos, path.m_targetReachedDist );

      /*
      Logger::debug( "FollowPath (FixedPos): BNpc {} NaviTargetDist {} Radius {} Distance {} dXZ {} dY {} Pos {} {} {} TargetPos {} {} {}",
                    pBNpc->getId(), pBNpc->getNaviTargetReachedDistance(), pBNpc->getRadius(),
                    distance, distXZ, distY,
                    pBNpc->getPos().x, pBNpc->getPos().y, pBNpc->getPos().z,
                    targetPos.x, targetPos.y, targetPos.z );
      */
      if( reachedTarget )
      {
        path.m_active = false;
        if( m_onDestReachCb )
          m_onDestReachCb();
      }
    }
    // follow predefined path
    else if( path.m_type == AI::Controller::Controller::PathType::PointList || path.m_type == AI::Controller::Controller::PathType::ServerPath )
    {
      const auto pathSize = path.m_points.size();
      if( pathSize == 0 || path.m_currPointIndex >= pathSize )
      {
        if( !path.m_flags & Controller::Controller::PathFlags::CanReversePath )
          path.m_active = false;

        path.m_currPointIndex = static_cast< uint32_t >( pathSize );
        return;
      }

      const auto currPoint = path.m_currPointIndex;

      //Logger::debug( "FollowPath: Pre-adjustment targetPos {} {} {}", targetPos.x, targetPos.y, targetPos.z );
      targetPos = path.m_points[ currPoint ];

      //Logger::debug( "FollowPath: Post-adjustment targetPos {} {} {}", targetPos.x, targetPos.y, targetPos.z );
      reachedTarget = ignoreNavmesh ? moveDirectly( targetPos ) : pBNpc->moveTo( targetPos, path.m_targetReachedDist );
      if( reachedTarget )
      {
        //Logger::debug( "FollowPath: Arrived at pos {} {} {}", targetPos.x, targetPos.y, targetPos.z );
        //Logger::debug( "FollowPath: currPoint {} pathSize {}", currPoint, pathSize );

        if( m_onPointReachCb && path.m_prevPointIndex != currPoint )
          m_onPointReachCb( path.m_points[ currPoint ] );
        path.m_prevPointIndex = currPoint;

        if( !path.m_isReversePath )
        {
          if( currPoint + 1 < pathSize )
            path.m_currPointIndex = currPoint + 1;
          else if( path.m_flags & AI::Controller::Controller::PathFlags::CanReversePath && pathSize > 1 )
          {
            path.m_isReversePath = true;
            path.m_currPointIndex = static_cast< uint32_t >( pathSize - 2 );
            //Logger::debug( "FollowPath: Reversing path" );
          }
          else
          {
            path.m_currPointIndex = static_cast< uint32_t >( pathSize );
            path.m_active = false;
            if( m_onDestReachCb )
              m_onDestReachCb();
            //Logger::debug( "FollowPath: Reached destination" );
            m_lastTick = now;
            return;
          }
        }
        else if( currPoint > 0 )
          path.m_currPointIndex = currPoint - 1;
        else
        {
          path.m_isReversePath = false;
          path.m_currPointIndex = pathSize > 1 ? 1 : 0;
        }

        targetPos = path.m_points[ path.m_currPointIndex ];
        pBNpc->face( targetPos );
      }
    }

    if( !ignoreNavmesh && !reachedTarget )
      pNaviProvider->setMoveTarget( pBNpc->getAgentId(), targetPos );

    pBNpc->setRoamTargetPos( targetPos );
    m_lastTick = now;
  }

  /*
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

    auto path = bnpc.getActiveServerPath();
    if( !path )
      onEnter( pEntity );


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
          // reached end, reverse
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
      bnpc.setRoamTargetPos( { path->position.x + path->points[ bnpc.getActiveServerPathPointIndex() ].Translation.x,
                               path->position.y + path->points[ bnpc.getActiveServerPathPointIndex() ].Translation.y,
                               path->position.z + path->points[ bnpc.getActiveServerPathPointIndex() ].Translation.z } );
    }
  }
  //*/
}

void AI::Fsm::StateFollowPath::onEnter( Entity::GameObjectPtr& pEntity )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( pEntity->getTerritoryId() );
  if( !pZone )
    return;

  auto pNaviProvider = pZone->getNaviProvider();

  auto pController = pEntity->getController();
  if( !pController )
    return;

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    auto& path = pController->getPath();

    if( path.m_targetReachedDist == std::numeric_limits< float >::max() )
      path.m_targetReachedDist = bnpc.getNaviTargetReachedDistance();

    bnpc.setNaviIsPathing( true );
    bnpc.setPathingActive( true );
    bnpc.setRoamTargetPos( path.m_targetPos );

    const bool ignoreNavmesh = path.m_flags & Controller::Controller::PathFlags::IgnoreNavmesh;
    if( ( !ignoreNavmesh && !pNaviProvider ) || bnpc.hasFlag( Entity::NoRoam ) || bnpc.hasFlag( Entity::Immobile ) )
    {
      bnpc.setRoamTargetReached( true );
      return;
    }

    // disable agent-agent collision, restore in onExit
    if( path.m_flags & Controller::Controller::PathFlags::IgnoreActorCollision && pNaviProvider )
    {
      pNaviProvider->updateAgentParameters( pBNpc->getAgentId(), pBNpc->getRadius(), false, pBNpc->getCurrentSpeed(), true );
    }

    path.m_restoreDefaultPathOnExit = ( path.m_flags & Controller::Controller::PathFlags::RestoreDefaultPathOnExit );

    if( bnpc.getEnemyType() == Common::Friendly )
    {
      /*
      path.reset();

      path.m_type = AI::Controller::PathType::FixedPos;
      path.m_targetPos = bnpc.getSpawnPos();
      path.m_active = true;

      bnpc.setRoamTargetPos( bnpc.getSpawnPos() );
      */
    }

    // todo: restore server path if transitioning from combat?
    if( path.m_type == AI::Controller::Controller::PathType::ServerPath )
    {
      if( auto serverPath = pZone->getServerPath( path.m_serverPathId ) )
      {
        auto serverPathId = path.m_serverPathId;

        // restore server path
        if( serverPath->points.empty() )
          return;

        path.m_active = true;
        path.m_targetPos = { serverPath->position.x + serverPath->points[ 0 ].Translation.x,
                             serverPath->position.y + serverPath->points[ 0 ].Translation.y,
                             serverPath->position.z + serverPath->points[ 0 ].Translation.z };

        path.m_points.clear();
        for( const auto& p : serverPath->points )
          path.m_points.push_back( { serverPath->position.x + p.Translation.x,
                                     serverPath->position.y + p.Translation.y,
                                     serverPath->position.z + p.Translation.z } );

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

        if( closestPointIndex < path.m_points.size() )
          path.m_targetPos = path.m_points[ path.m_currPointIndex ];

        bnpc.setRoamTargetPos( path.m_targetPos );
      }
    }
  }
}

void AI::Fsm::StateFollowPath::onExit( Entity::GameObjectPtr& pEntity )
{
  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    pBNpc->setRoamTargetReached( false );
    pBNpc->setNaviIsPathing( false );

    if( auto pController = pBNpc->getController() )
    {
      auto& path = pController->getPath();

      auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
      auto pZone = teriMgr.getTerritoryByGuId( pBNpc->getTerritoryId() );
      if( !pZone )
        return;

      auto pNaviProvider = pZone->getNaviProvider();

      // allow agent-agent collision again if it was unset for this request
      if( pNaviProvider )
        pNaviProvider->updateAgentParameters( pBNpc->getAgentId(), pBNpc->getRadius(), false, pBNpc->getCurrentSpeed(), false );

      // restore default server path if specified
      if( path.m_restoreDefaultPathOnExit )
      {
        path.reset();

        path.m_active = true;
        path.m_type = path.m_defaultType;
        path.m_serverPathId = path.m_defaultServerPathId;
        path.m_flags = path.m_defaultFlags;
      }
    }
  }
}

void AI::Fsm::StateFollowPath::setOnPointReachedCb( const std::function< void( Common::Vector3 ) >& onPointReachCb )
{
  m_onPointReachCb = onPointReachCb;
}

void AI::Fsm::StateFollowPath::setOnDestReachedCb( const std::function< void() >& onDestReachCb )
{
  m_onDestReachCb = onDestReachCb;
}
