#include <cstdint>
#include "ForwardsZone.h"
#include "Actor/BNpc.h"
#include <Util/Util.h>
#include <Util/UtilMath.h>

#pragma once

namespace Sapphire::World::AI::Fsm
{
  class Condition
  {
  public:
    Condition() = default;
    virtual ~Condition() = default;

    virtual bool isConditionMet( Sapphire::Entity::BNpc& src ) const = 0;
    virtual bool update( Sapphire::Entity::BNpc& src, float time )
    {
      if( isConditionMet( src ) )
        return true;
      return false;
    };
  };

  class RoamNextTimeReachedCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::BNpc& src ) const override
    {
      if( ( Common::Util::getTimeSeconds() - src.getLastRoamTargetReachedTime() ) > 20 )
        return true;
      return false;
    }
  };

  class RoamTargetReachedCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::BNpc& src ) const override
    {
      if( src.isRoamTargetReached() )
        return true;
      return false;
    }
  };

  class HateListEmptyCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::BNpc& src ) const override
    {
      if( src.hateListGetHighest() )
        return false;
      return true;
    }
  };

  class HateListHasEntriesCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::BNpc& src ) const override
    {
      if( src.hateListGetHighest() )
        return true;
      return false;
    }
  };

  class SpawnPointDistanceGtMaxDistanceCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::BNpc& src ) const override
    {
      auto distanceOrig = Common::Util::distance( src.getPos(), src.getSpawnPos() );
      if( distanceOrig > 40 )
        return true;

      return false;
    }
  };

  class IsDeadCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::BNpc& src ) const override
    {
      if( !src.isAlive() )
        return true;

      return false;
    }
  };

}