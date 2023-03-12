#include <cstdint>
#include <ForwardsZone.h>
#include "GambitTargetCondition.h"
#include "GambitRule.h"

using namespace Sapphire;
using namespace Sapphire::World;

AI::GambitRule::GambitRule( const GambitTargetConditionPtr targetCondition, Action::ActionPtr action, uint32_t coolDown ) :
  m_targetCondition( targetCondition ),
  m_pAction( std::move( action ) ),
  m_lastExecutionMs( 0 ),
  m_coolDownMs( coolDown ),
  m_isEnabled( true )
{

}

void AI::GambitRule::toggleEnabled()
{
  m_isEnabled = !m_isEnabled;
}

bool AI::GambitRule::isEnabled() const
{
  return m_isEnabled;
}

uint64_t AI::GambitRule::getLastExecutionMs() const
{
  return m_lastExecutionMs;
}

void AI::GambitRule::setLastExecutionMs( uint64_t lastExecution )
{
  m_lastExecutionMs = lastExecution;
}

uint32_t AI::GambitRule::getCoolDown() const
{
  return m_coolDownMs;
}

AI::GambitTargetConditionPtr AI::GambitRule::getGambitTargetCondition()
{
  return m_targetCondition;
}

Action::ActionPtr AI::GambitRule::getActionPtr()
{
  return m_pAction;
}