#include <cstdint>
#include <ForwardsZone.h>
#include <Actor/BNpc.h>

#pragma once

namespace Sapphire::World::AI
{
  enum GambitTargetType : uint8_t
  {
    Self,
    Player,
    PlayerAndAlly,
    Ally,
    BNpc
  };

  class GambitTargetCondition
  {
  public:
    GambitTargetCondition() = default;
    virtual ~GambitTargetCondition() = default;

    virtual bool isConditionMet( Sapphire::Entity::BNpc& src ) { return false; };
    Sapphire::Entity::CharaPtr getTarget() const { return m_pTarget; };
  protected:
    Sapphire::Entity::CharaPtr m_pTarget;
  };

  class TopHateTargetCondition : public GambitTargetCondition
  {
  public:
    TopHateTargetCondition() = default;

    bool isConditionMet( Sapphire::Entity::BNpc& src ) override
    {
      auto foundChara = src.hateListGetHighest();
      if( foundChara )
      {
        m_pTarget = foundChara;
        return true;
      }
      return false;
    };
  };

  class HPSelfPctLessThanTargetCondition : public GambitTargetCondition
  {
  public:
    HPSelfPctLessThanTargetCondition( uint8_t pct ) : m_HpPct( pct ) {};

    bool isConditionMet( Sapphire::Entity::BNpc& src ) override
    {
      if( src.getHpPercent() < m_HpPct )
      {
        m_pTarget = src.getAsBNpc();
        return true;
      }
      return false;
    };
  private:
    uint8_t m_HpPct;
  };

}