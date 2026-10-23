#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "State.h"

#include <Vector3.h>

namespace Sapphire::World::AI::Fsm
{
  class StateFollowPath : public State
  {
  public:
    StateFollowPath( const std::function< void( Common::Vector3 ) >& onPointReachCb = {},
                    const std::function< void() >& onDestReachCb = {} )
    {
      m_onPointReachCb = onPointReachCb;
      m_onDestReachCb = onDestReachCb;
    }
    virtual ~StateFollowPath() = default;

    void onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount ) override;
    void onEnter( Entity::GameObjectPtr& pEntity ) override;
    void onExit( Entity::GameObjectPtr& pEntity ) override;

    void setOnPointReachedCb( const std::function< void( Common::Vector3 ) >& onPointReachCb );
    void setOnDestReachedCb( const std::function< void() >& onDestReachedCb );

  private:
    std::function< void( Common::Vector3 ) > m_onPointReachCb;
    std::function< void() > m_onDestReachCb;

    uint32_t m_initialPathType{ 0 };
  };
}