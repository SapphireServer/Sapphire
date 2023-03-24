#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "Transition.h"

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class State
  {
  public:
    virtual ~State() = default;

    virtual void onUpdate( Entity::BNpc& bnpc, uint64_t tickCount ) = 0;
    virtual void onEnter( Entity::BNpc& bnpc ) { }
    virtual void onExit( Entity::BNpc& bnpc ) { }

    void addTransition( TransitionPtr transition )
    {
      m_transitions.push_back( transition );
    }

    void addTransition( StatePtr targetState, ConditionPtr condition )
    {
      m_transitions.push_back( make_Transition( targetState, condition ) );
    }


    TransitionPtr getTriggeredTransition( Entity::BNpc& bnpc )
    {
      for( auto transition : m_transitions )
      {
        if( transition->hasTriggered( bnpc ) )
          return transition;
      }
      return nullptr;
    }

  private:
    std::vector< TransitionPtr > m_transitions;
  };
}