#include <cstdint>
#include <ForwardsZone.h>
#include <Actor/BNpc.h>
#include "FsmTransition.h"

#pragma once

namespace Sapphire::World::AI
{
  class FsmState
  {
  public:
    virtual ~FsmState() = default;

    virtual void onUpdate( Entity::BNpc& bnpc, float deltaTime ) = 0;
    virtual void onEnter( Entity::BNpc& bnpc ) { }
    virtual void onExit( Entity::BNpc& bnpc ) { }

    void addTransition( FsmTransitionPtr transition )
    {
      m_transitions.push_back( transition );
    }

    FsmTransitionPtr getTriggeredTransition( Entity::BNpc& bnpc )
    {
      for( auto transition : m_transitions )
      {
        if( transition->hasTriggered( bnpc ) )
          return transition;
      }
      return nullptr;
    }

  private:
    std::vector< FsmTransitionPtr > m_transitions;
  };
}