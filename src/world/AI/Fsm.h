#include <cstdint>
#include <ForwardsZone.h>
#include <Actor/BNpc.h>

#pragma once

namespace Sapphire::World::AI
{
  class Fsm
  {
  public:
    Fsm() = default;
    ~Fsm() = default;

    FsmStatePtr addState( FsmStatePtr state );
    void setCurrentState( FsmStatePtr state );
    virtual void update( Entity::BNpc& bnpc, float deltaTime );

  protected:
    std::vector< FsmStatePtr > m_states;
    FsmStatePtr m_pCurrentState;
  };
}