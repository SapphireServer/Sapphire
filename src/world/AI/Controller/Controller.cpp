#include "Controller.h"

#include "../GambitPack.h"
#include "../Fsm/StateMachine.h"

#include <Actor/GameObject.h>
#include <Actor/Chara.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>

#include <AI/Fsm/StateCombat.h>
#include <AI/Fsm/StateDead.h>
#include <AI/Fsm/StateFollowPath.h>

#include <Navi/NaviProvider.h>

#include <Service.h>
#include <Manager/TerritoryMgr.h>
#include <Territory/Territory.h>

#include <Logging/Logger.h>
#include <Util/UtilMath.h>

namespace Sapphire::World::AI::Controller
{

  void Controller::initialize()
  {
    m_stateMachine.reset();
    m_path.reset();
    stopFollowingTarget();
  }

  void Controller::onDetach()
  {
    m_path.reset();
    stopFollowingTarget();
    m_stateMachine.reset();
  }

  bool Controller::tryAggro( uint32_t targetId )
  {
    return false;
  }

  void Controller::aggro( uint32_t targetId, uint32_t hateAmount )
  {
  }

  void Controller::autoAttack( uint32_t targetId )
  {
  }

  void Controller::rangedAutoAttack( uint32_t targetId )
  {
  }

  void Controller::deaggro()
  {
  }

  void Controller::clearEnmityList()
  {
  }

  void Controller::pathTo( const Common::Vector3& pos, float targetReachedDist, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pTeri = teriMgr.getTerritoryByGuId( m_owner.getTerritoryId() );

    if( !pTeri )
    {
      // todo:
      return;
    }

    auto pNavi = pTeri->getNaviProvider();
    if( !( flags & PathFlags::IgnoreNavmesh ) && !pNavi )
    {
      // todo:
      return;
    }

    m_path.reset();

    m_path.m_type = PathType::FixedPos;
    m_path.m_targetPos = pos;
    m_path.m_flags = flags;
    m_path.m_targetReachedDist = targetReachedDist;
    m_path.m_active = true;

    if( !( flags & PathFlags::IgnoreNavmesh ) )
    {
      //Logger::debug( "Pre-adjustment TargetPos: {} {} {}", m_path.m_targetPos.x, m_path.m_targetPos.y, m_path.m_targetPos.z );
      m_path.m_targetPos = pNavi->findNearestPosition( pos.x, pos.y, pos.z );
      //Logger::debug( "TargetPos: {} {} {}", m_path.m_targetPos.x, m_path.m_targetPos.y, m_path.m_targetPos.z );
    }

    auto pCurrState = m_stateMachine.getCurrentState();
    auto pPathState = std::make_shared< Fsm::StateFollowPath >( onReachPoint, onReachDestination );

    // transition back to current state on reaching destination
    auto pTransition = std::make_shared< Fsm::Transition >( pCurrState, std::make_shared< Fsm::PathDestinationReachedCondition >() );
    pPathState->addTransition( pTransition );

    if( flags & PathFlags::Interruptible )
    {
      pPathState->addTransition( std::make_shared< Fsm::Transition >( pCurrState, std::make_shared< Fsm::HateListHasEntriesCondition >() ) );
    }
    m_stateMachine.setCurrentState( pPathState );
  }

  void Controller::followPath( const std::vector< Common::Vector3 >& path, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    if( path.empty() )
      return;

    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pTeri = teriMgr.getTerritoryByGuId( m_owner.getTerritoryId() );

    if( !pTeri )
    {
      // todo:
      return;
    }

    auto pNavi = pTeri->getNaviProvider();
    if( !( flags & PathFlags::IgnoreNavmesh ) && !pNavi )
    {
      // todo:
      return;
    }

    m_path.reset();

    m_path.m_type = PathType::PointList;
    m_path.m_targetPos = path[ path.size() - 1 ];
    m_path.m_flags = flags;
    m_path.m_points = path;
    m_path.m_active = true;

    //Logger::debug( "BNpc {} X:{} Y:{} Z:{}", m_owner.getId(), m_owner.getPos().x, m_owner.getPos().y, m_owner.getPos().z );

    float radius = m_owner.isBattleNpc() ? m_owner.getAsBNpc()->getRadius() : 1.f;

    if( !( flags & PathFlags::IgnoreNavmesh ) )
    {
      for( auto& pos : m_path.m_points )
      {

        //Logger::debug( "Pre-adjustment pos: X:{} Y:{} Z:{}", pos.x, pos.y, pos.z );
        auto pos2 = pNavi->findNearestPosition( pos.x, pos.y, pos.z );
        auto calculatedPath = pNavi->findFollowPath( m_owner.getPos(), pos, radius );
        if( !calculatedPath.empty() )
        {
          const auto& pathEnd = calculatedPath.back();
          //Logger::debug( "FindFollowPath {} {} {}", pathEnd.x, pathEnd.y, pathEnd.z );
        }
        //Logger::debug( "Post-adjustment pos: X:{} Y:{} Z:{}", pos2.x, pos2.y, pos2.z );
        pos = pos2;
      }
      m_path.m_targetPos = m_path.m_points[ m_path.m_points.size() - 1 ];

      //Logger::info( "TargetPos: {} {} {}", m_path.m_targetPos.x, m_path.m_targetPos.y, m_path.m_targetPos.z );
    }

    auto pCurrState = m_stateMachine.getCurrentState();
    auto pPathState = std::make_shared< Fsm::StateFollowPath >( onReachPoint, onReachDestination );

    // transition back to current state on reaching destination
    auto pTransition = std::make_shared< Fsm::Transition >( pCurrState, std::make_shared< Fsm::PathDestinationReachedCondition >() );
    pPathState->addTransition( pTransition );

    if( flags & PathFlags::Interruptible )
    {
      pPathState->addTransition( std::make_shared< Fsm::Transition >( pCurrState, std::make_shared< Fsm::HateListHasEntriesCondition >() ) );
    }

    m_stateMachine.setCurrentState( pPathState );
  }

  void Controller::followTarget( uint32_t targetId, bool followDuringCombat )
  {
    m_owner.setFollowTargetId( targetId );
    m_followTargetActive = targetId != Common::INVALID_GAME_OBJECT_ID;
    m_followTargetDuringCombat = followDuringCombat;
  }

  void Controller::stopFollowingTarget()
  {
    m_owner.resetFollowTargetId();
    m_followTargetActive = false;
    m_followTargetDuringCombat = false;
  }

  void Controller::updateFollowTarget( uint64_t )
  {
    if( !m_followTargetActive )
      return;

    if( !m_followTargetDuringCombat && m_stateMachine.isCurrentState< Fsm::StateCombat >() )
      return;

    auto pBNpc = m_owner.getAsBNpc();
    if( !pBNpc || !pBNpc->isAlive() )
    {
      stopFollowingTarget();
      return;
    }

    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pTeri = teriMgr.getTerritoryByGuId( m_owner.getTerritoryId() );
    if( !pTeri )
    {
      stopFollowingTarget();
      return;
    }

    auto pTarget = pTeri->getEntityById( m_owner.getFollowTargetId() );
    if( !pTarget )
    {
      stopFollowingTarget();
      return;
    }

    auto pNavi = pTeri->getNaviProvider();
    if( !pNavi || pBNpc->getAgentId() == -1 )
      return;

    // const auto targetPos = Common::Util::getOffsettedPosition( pTarget->getPos(), pTarget->getRot(), 0.f, 0.f, -1.f );
    const auto& targetPos = pTarget->getPos();
    pBNpc->setPathingActive( true );
    pBNpc->setRoamTargetPos( targetPos );

    if( pBNpc->moveTo( targetPos ) )
    {
      pBNpc->setNaviIsPathing( false );
      pBNpc->setRoamTargetReached( true );
      pBNpc->face( pTarget->getPos() );
      return;
    }

    pBNpc->setRoamTargetReached( false );
    pNavi->setMoveTarget( pBNpc->getAgentId(), targetPos );
    pBNpc->face( pTarget->getPos() );
  }

  void Controller::processGambits( uint64_t tick )
  {
  }

  Controller::Path& Controller::getPath()
  {
    return m_path;
  }

  void Controller::setPath( const Controller::Path& path )
  {
    m_path = path;
  }

  GambitPackPtr Controller::getGambitPack() const
  {
    return m_pGambitPack;
  }

  void Controller::setGambitPack( GambitPackPtr& pGambitPack )
  {
    m_pGambitPack = pGambitPack;
  }

  Fsm::StatePtr Controller::getCurrentState()
  {
    return m_stateMachine.getCurrentState();
  }

  void Controller::update( uint64_t tick )
  {
    auto elapsed = Common::Util::getTimeMs() - m_lastTick;

    m_stateMachine.update( tick );
    updateFollowTarget( tick );
    m_lastTick = Common::Util::getTimeMs();
  }


}// namespace Sapphire::World::AI
