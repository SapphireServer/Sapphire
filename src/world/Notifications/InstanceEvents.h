#pragma once

#include "EventSignal.h"
#include "Territory/InstanceContentState.h"

namespace Sapphire
{
  class InstanceContent;
}

namespace Sapphire::Entity
{
  class Chara;
}

namespace Sapphire::World::Notifications
{
  struct InstanceActorDied
  {
    InstanceContent& instance;
    Entity::Chara& actor;
  };

  struct InstanceStateChanged
  {
    InstanceContent& instance;
    InstanceContentState previousState;
    InstanceContentState state;
  };

  struct InstanceEvents
  {
    EventSignal< InstanceActorDied > actorDied;
    EventSignal< InstanceStateChanged > stateChanged;
  };
}
