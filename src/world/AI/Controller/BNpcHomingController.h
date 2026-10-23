#pragma once

#include "Controller.h"

namespace Sapphire::World::AI::Controller
{
  class BNpcHomingController : public Controller
  {
  public:
    explicit BNpcHomingController( Entity::BNpc& bnpc );

    void initialize() override;

    bool tryAggro( uint32_t targetId ) override;
    void aggro( uint32_t targetId, uint32_t hateAmount = 1 ) override;
    void autoAttack( uint32_t targetId ) override;
    void rangedAutoAttack( uint32_t targetId ) override;
    void deaggro() override;
    void clearEnmityList() override;
    void pathTo( const Common::Vector3& pos, float targetReachedDist, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint = {}, const std::function< void() >& onReachDestination = {} ) override;
    void followPath( const std::vector< Common::Vector3 >& path, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint = {}, const std::function< void() >& onReachDestination = {} ) override;
    void followTarget( uint32_t targetId, bool followDuringCombat = false ) override;

    void setHomingTargetId( uint32_t targetId, const std::function< void() >& onReachDestination = {} );
    void setHomingTargetPos( Common::Vector3& pos, const std::function< void() >& onReachDestination = {} );

    void update( uint64_t tick ) override;
  };
}