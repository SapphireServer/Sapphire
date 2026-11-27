#include "BNpcHomingController.h"

#include <Actor/BNpc.h>
#include <Common.h>
#include <Vector3.h>

#include <AI/Fsm/StateFollowPath.h>

namespace Sapphire::World::AI::Controller
{
  BNpcHomingController::BNpcHomingController( Entity::BNpc& bnpc ) :
    Controller( bnpc )
  {

  }

  void BNpcHomingController::initialize()
  {
    
  }

  bool BNpcHomingController::tryAggro( uint32_t targetId )
  {
    return false;
  }

  void BNpcHomingController::aggro( uint32_t targetId, uint32_t hateAmount )
  {

  }

  void BNpcHomingController::autoAttack( uint32_t targetId )
  {

  }

  void BNpcHomingController::rangedAutoAttack( uint32_t targetId )
  {

  }

  void BNpcHomingController::deaggro()
  {

  }

  void BNpcHomingController::clearEnmityList()
  {

  }

  void BNpcHomingController::pathTo( const Common::Vector3& pos, float targetReachedDist, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    Controller::pathTo( pos, targetReachedDist, flags, onReachPoint, onReachDestination );
  }

  void BNpcHomingController::followPath( const std::vector< Common::Vector3 >& path, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    Controller::followPath( path, flags, onReachPoint, onReachDestination );
  }

  void BNpcHomingController::followTarget( uint32_t targetId, bool followDuringCombat )
  {
    Controller::followTarget( targetId, followDuringCombat );
  }

  void BNpcHomingController::setHomingTargetId( uint32_t targetId, const std::function< void() >& onReachDestination )
  {
    m_path.reset();
    m_path.m_type = PathType::TargetId;
    m_path.m_active = true;
    m_path.m_targetId = targetId;
    m_path.m_targetReachedDist = 0.5f;

    auto pCurrState = m_stateMachine.getCurrentState();
    auto pFollowPathState = Fsm::make_StateFollowPath( nullptr, onReachDestination );

    m_stateMachine.setCurrentState( pFollowPathState );
  }

  void BNpcHomingController::setHomingTargetPos( Common::Vector3& pos, const std::function< void() >& onReachDest )
  {
    m_path.reset();
    m_path.m_type = PathType::FixedPos;
    m_path.m_active = true;
    m_path.m_targetPos = pos;
    m_path.m_targetReachedDist = 0.5f;

    auto pCurrState = m_stateMachine.getCurrentState();
    auto pFollowPathState = Fsm::make_StateFollowPath( nullptr, onReachDest );

    m_stateMachine.setCurrentState( pFollowPathState );
  }

  void BNpcHomingController::update( uint64_t tick )
  {
    m_stateMachine.update( tick );
    m_lastTick = tick;
  }
}