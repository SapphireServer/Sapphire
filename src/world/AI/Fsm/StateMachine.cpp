#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include "StateMachine.h"
#include "State.h"

using namespace Sapphire;
using namespace Sapphire::World;

AI::Fsm::StatePtr AI::Fsm::StateMachine::addState( Fsm::StatePtr state )
{
  m_states.push_back( state );
  return state;
}

void AI::Fsm::StateMachine::setCurrentState( Fsm::StatePtr state )
{
  m_pCurrentState = state;
}

void AI::Fsm::StateMachine::update( Entity::BNpc& bnpc, uint64_t tickCount )
{
  if( !m_pCurrentState )
    return;

  TransitionPtr transition = m_pCurrentState->getTriggeredTransition( bnpc );

  if( transition )
  {
    m_pCurrentState->onExit( bnpc );
    m_pCurrentState = transition->getTargetState();
    m_pCurrentState->onEnter( bnpc );
  }

  m_pCurrentState->onUpdate( bnpc, tickCount );
}
