#include <cstdint>
#include <ForwardsZone.h>
#include <Actor/BNpc.h>
#include "Fsm.h"
#include "FsmState.h"

#pragma once

using namespace Sapphire;
using namespace Sapphire::World;

AI::FsmStatePtr AI::Fsm::addState( FsmStatePtr state )
{
  m_states.push_back( state );
  return state;
}

void AI::Fsm::setCurrentState( FsmStatePtr state )
{
  m_pCurrentState = state;
}

void AI::Fsm::update( Entity::BNpc& bnpc, float deltaTime )
{
  if( !m_pCurrentState )
    return;

  FsmTransitionPtr transition = m_pCurrentState->getTriggeredTransition( bnpc );

  if( transition )
  {
    m_pCurrentState->onExit( bnpc );
    m_pCurrentState = transition->getTargetState();
    m_pCurrentState->onEnter( bnpc );
  }

  m_pCurrentState->onUpdate( bnpc, deltaTime );
}
