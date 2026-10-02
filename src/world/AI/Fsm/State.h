#include <cstdint>

#include <Util/Util.h>

#include "ForwardsZone.h"

#include "Actor/BNpc.h"
#include "Actor/GameObject.h"
#include "Transition.h"


#pragma once

namespace Sapphire::World::AI::Fsm
{
  class State
  {
  public:
    State() :
      m_lastTick( Common::Util::getTimeMs() )
    {

    }
    virtual ~State() = default;

    virtual void onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount ) { }
    virtual void onEnter( Entity::GameObjectPtr& pEntity ) { }
    virtual void onExit( Entity::GameObjectPtr& pEntity ) { }

    bool hasInitialised() const
    {
      return m_initialised;
    }

    void setInitialised( bool initialised )
    {
      m_initialised = initialised;
    }

    void addTransition( TransitionPtr transition )
    {
      m_transitions.push_back( transition );
    }

    void addTransition( StatePtr targetState, ConditionPtr condition )
    {
      m_transitions.push_back( make_Transition( targetState, condition ) );
    }

    template< typename T, typename = std::enable_if_t< std::is_base_of< State, T >::value > >
    bool hasTransitionToState()
    {
      auto ret = false;
      for( const auto& transition : m_transitions )
      {
        ret = transition && transition->getTargetState() && dynamic_cast< T* >( transition->getTargetState().get() );

        if( ret )
          break;
      }

      return ret;
    }

    template< typename T, typename = std::enable_if_t< std::is_base_of< State, T >::value > >
    bool is()
    {
      return dynamic_cast< T* >( this );
    }

    TransitionPtr getTriggeredTransition( Entity::GameObjectPtr& pObject )
    {
      for( auto& transition : m_transitions )
      {
        if( transition->hasTriggered( pObject ) )
          return transition;
      }
      return nullptr;
    }

    const std::vector< TransitionPtr >& getTransitions() const
    {
      return m_transitions;
    }

  protected:
    bool m_initialised{ false };
    uint64_t m_lastTick{ 0 };
    std::vector< TransitionPtr > m_transitions;
  };
}