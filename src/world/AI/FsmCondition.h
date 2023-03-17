#include <cstdint>
#include <ForwardsZone.h>
#include <Actor/BNpc.h>

#pragma once

namespace Sapphire::World::AI
{
  class FsmCondition
  {
  public:
    FsmCondition() = default;
    virtual ~FsmCondition() = default;

    virtual bool isConditionMet( Sapphire::Entity::BNpc& src ) const = 0;
    virtual bool update( Sapphire::Entity::BNpc& src, float time )
    {
      if( isConditionMet( src ) )
        return true;
      return false;
    };
  };
}