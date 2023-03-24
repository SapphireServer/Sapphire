#include <cstdint>
#include <ForwardsZone.h>
#include "GambitTargetCondition.h"
#include "GambitRule.h"

#pragma once

namespace Sapphire::World::AI
{
  enum class GambitPackType : uint8_t
  {
    None,
    RuleSetList,
    TimeLine
  };

  class GambitPack : public std::enable_shared_from_this< GambitPack >
  {
  public:
    GambitPack( GambitPackType type ) : m_type( type ) { };
    virtual ~GambitPack() = default;
    GambitPackType getType() const { return m_type; }
    virtual void update( Entity::BNpc& bnpc, uint64_t tickCount ) = 0;
    GambitTimeLinePackPtr getAsTimeLine();
    GambitRuleSetPackPtr getAsRuleSet();
  private:
    GambitPackType m_type;
  };

  class GambitTimeLinePack : public GambitPack
  {
  public:
    GambitTimeLinePack( int8_t loopCount );
    void update( Entity::BNpc& bnpc, uint64_t tickCount );
    void addTimeLine( const GambitRulePtr& pRule, uint32_t offsetInSeconds );
    void addTimeLine( const GambitTargetConditionPtr& targetCondition, const Action::ActionPtr& action, uint32_t offsetInSeconds );
    uint8_t getLoopCount() const;
    uint8_t getCurrentIndex() const;
    void start();

  private:
    std::vector< std::pair< GambitRulePtr, uint32_t > > m_gambits;

    uint64_t m_startTimeMs;
    uint8_t m_currentIndex;
    int8_t m_loopCount;
    uint8_t m_currentLoop;
  };

  class GambitRuleSetPack : public GambitPack
  {
  public:
    GambitRuleSetPack();
    void addRule( const GambitRulePtr& pRule );
    void addRule( const GambitTargetConditionPtr& targetCondition, const Action::ActionPtr& action, uint32_t coolDown );
    void update( Entity::BNpc& bnpc, uint64_t tickCount );
  private:
    std::vector< GambitRulePtr > m_gambits;
  };
}