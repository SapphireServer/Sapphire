#include <cstdint>
#include <vector>
#include <queue>

#include "ForwardsZone.h"

#include "State.h"

#include "Actor/GameObject.h"
#include "Actor/BNpc.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class StateMachine
  {
  public:
    explicit StateMachine( Entity::GameObject& owner ) :
      m_owner( owner )
    {
    }
    ~StateMachine() = default;

    StatePtr addState( StatePtr state );

    StatePtr getCurrentState();
    void setCurrentState( StatePtr state );
    void reset();

    virtual void update( uint64_t tickCount );

    template< typename T, typename = std::enable_if_t< std::is_base_of< State, T >::value > >
    bool isCurrentState()
    {
      return m_pCurrentState && dynamic_cast< T* >( m_pCurrentState.get() );
    }

    template< typename T, typename = std::enable_if_t< std::is_base_of< State, T >::value > >
    bool isPrevState()
    {
      return m_pPrevState && dynamic_cast< T* >( m_pPrevState.get() );
    }



    const StatePtr getPrevState() const
    {
      return m_pPrevState;
    }

  protected:
    std::deque< StatePtr > m_stateStack;
    Entity::GameObject& m_owner;
    std::vector< StatePtr > m_states;
    StatePtr m_pPrevState;
    StatePtr m_pCurrentState;
  };
}
