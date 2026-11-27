#include "BNpcSubActorController.h"

#include <Actor/BNpc.h>
#include <Common.h>
#include <Vector3.h>

#include <AI/Fsm/StateFollowPath.h>

#include <Logging/Logger.h>

namespace Sapphire::World::AI::Controller
{
  BNpcSubActorController::BNpcSubActorController( Entity::BNpc& bnpc ) :
    Controller( bnpc )
  {
    
  }

  void BNpcSubActorController::initialize()
  {
    
  }

  bool BNpcSubActorController::tryAggro( uint32_t targetId )
  {
    return false;
  }

  void BNpcSubActorController::aggro( uint32_t targetId, uint32_t hateAmount )
  {

  }

  void BNpcSubActorController::autoAttack( uint32_t targetId )
  {

  }

  void BNpcSubActorController::rangedAutoAttack( uint32_t targetId )
  {

  }

  void BNpcSubActorController::deaggro()
  {

  }

  void BNpcSubActorController::clearEnmityList()
  {

  }

  void BNpcSubActorController::pathTo( const Common::Vector3& pos, float targetReachedDist, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    Controller::pathTo( pos, targetReachedDist, flags, onReachPoint, onReachDestination );
  }

  void BNpcSubActorController::followPath( const std::vector< Common::Vector3 >& path, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    Controller::followPath( path, flags, onReachPoint, onReachDestination );
  }

  void BNpcSubActorController::followTarget( uint32_t targetId, bool followDuringCombat )
  {
    Controller::followTarget( targetId, followDuringCombat );
  }

  void BNpcSubActorController::update( uint64_t tick )
  {
    Controller::update( tick );
  }
}