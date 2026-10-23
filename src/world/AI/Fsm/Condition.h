#pragma once

#include <cstdint>

#include <Util/Util.h>
#include <Util/UtilMath.h>

#include "ForwardsZone.h"

#include <Actor/GameObject.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>

//#include <AI/Controller/Controller.h>

namespace Sapphire::World::AI::Fsm
{
  class Condition
  {
  public:
    Condition() = default;
    virtual ~Condition() = default;

    virtual bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const = 0;
    virtual bool update( Sapphire::Entity::GameObjectPtr& pEntity, float time )
    {
      if( isConditionMet( pEntity ) )
        return true;
      return false;
    };
  };

  class RoamNextTimeReachedCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class RoamTargetReachedCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class HateListEmptyCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class HateListHasEntriesCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class SpawnPointDistanceGtMaxDistanceCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class IsDeadCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class PathDestinationReachedCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };

  class FollowTargetInvalidCondition : public Condition
  {
  public:
    bool isConditionMet( Sapphire::Entity::GameObjectPtr& pEntity ) const override;
  };
}