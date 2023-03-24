#include <cstdint>
#include <ForwardsZone.h>
#include <Service.h>
#include <Manager/ActionMgr.h>
#include <Action/Action.h>
#include "GambitTargetCondition.h"
#include "GambitRule.h"
#include "GambitPack.h"

using namespace Sapphire;
using namespace Sapphire::World;

AI::GambitTimeLinePack::GambitTimeLinePack( int8_t loopCount ) :
  GambitPack( GambitPackType::TimeLine ),
  m_loopCount( loopCount ),
  m_currentIndex( 0 ),
  m_currentLoop( 0 ),
  m_startTimeMs( 0 )
{

}

void AI::GambitTimeLinePack::start()
{
  m_startTimeMs = Common::Util::getTimeMs();
}

void AI::GambitTimeLinePack::addTimeLine( const GambitRulePtr& pRule, uint32_t offsetInSeconds )
{
  auto timeLine = std::make_pair( pRule, offsetInSeconds );
  m_gambits.push_back( timeLine );
}

void AI::GambitTimeLinePack::addTimeLine( const GambitTargetConditionPtr& targetCondition, const Action::ActionPtr& action, uint32_t offsetInSeconds )
{
  auto pRule = make_GambitRule( targetCondition, action, 0 );
  auto timeLine = std::make_pair( pRule, offsetInSeconds );
  m_gambits.push_back( timeLine );
}

uint8_t AI::GambitTimeLinePack::getLoopCount() const
{
  return m_loopCount;
}

uint8_t AI::GambitTimeLinePack::getCurrentIndex() const
{
  return m_currentIndex;
}

void AI::GambitTimeLinePack::update( Entity::BNpc& bnpc, uint64_t tickCount )
{
  if( m_startTimeMs == 0 || m_gambits.empty() )
    return;

  auto& actionMgr = Common::Service< World::Manager::ActionMgr >::ref();

  if( m_gambits.size() <= m_currentIndex )
  {
    if( m_currentLoop < m_loopCount || m_loopCount == -1 )
    {
      m_currentIndex = 0;
      m_currentLoop++;
      m_startTimeMs = Common::Util::getTimeMs();
    }
    else
    {
      m_startTimeMs = 0;
      m_currentLoop = 0;
      return;
    }
  }

  auto currentTimeLine = m_gambits.at( m_currentIndex );
  auto& pRule = currentTimeLine.first;
  auto offset = currentTimeLine.second * 1000;

  if( tickCount - m_startTimeMs >= offset )
  {
    if( pRule->getGambitTargetCondition()->isConditionMet( bnpc ) )
    {
      pRule->setLastExecutionMs( tickCount );
      actionMgr.handleTargetedAction( bnpc, pRule->getActionPtr()->getId(), pRule->getGambitTargetCondition()->getTarget()->getId(), 0 );
    }
    m_currentIndex++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AI::GambitRuleSetPack::GambitRuleSetPack() : GambitPack( GambitPackType::RuleSetList )
{

}

void AI::GambitRuleSetPack::addRule( const GambitRulePtr& pRule )
{
  m_gambits.push_back( pRule );
}

void AI::GambitRuleSetPack::addRule( const GambitTargetConditionPtr& targetCondition, const Action::ActionPtr& action, uint32_t coolDown )
{
  auto pRule = make_GambitRule( targetCondition, action, coolDown );
  m_gambits.push_back( pRule );
}

void AI::GambitRuleSetPack::update( Entity::BNpc& bnpc, uint64_t tickCount )
{
  auto& actionMgr = Common::Service< World::Manager::ActionMgr >::ref();
  for( auto& gambitRule : m_gambits )
  {
    if( !gambitRule->isEnabled() )
      continue;

    if( ( tickCount - gambitRule->getLastExecutionMs() ) > gambitRule->getCoolDown() )
    {
      if( !gambitRule->getGambitTargetCondition()->isConditionMet( bnpc ) )
        continue;

      gambitRule->setLastExecutionMs( tickCount );
      actionMgr.handleTargetedAction( bnpc, gambitRule->getActionPtr()->getId(), gambitRule->getGambitTargetCondition()->getTarget()->getId(), 0 );
      break;
    }
  }
}

AI::GambitTimeLinePackPtr AI::GambitPack::getAsTimeLine()
{
  return std::dynamic_pointer_cast< GambitTimeLinePack, GambitPack >( shared_from_this() );
}

AI::GambitRuleSetPackPtr AI::GambitPack::getAsRuleSet()
{
  return std::dynamic_pointer_cast< GambitRuleSetPack, GambitPack >( shared_from_this() );
}
