#pragma once

#include <cstdint>

#include "EventSignal.h"

namespace Sapphire::Entity
{
  class Chara;
}

namespace Sapphire::World::Notifications
{
  // Published after stat recalculation, including when an effect is refreshed.
  struct StatusEffectApplied
  {
    Entity::Chara& target;
    uint32_t effectId;
  };

  // Published after effect cleanup, before the actor erases its status entry.
  struct StatusEffectRemoving
  {
    Entity::Chara& target;
    uint32_t effectId;
  };

  struct StatusEffectEvents
  {
    EventSignal< StatusEffectApplied > applied;
    EventSignal< StatusEffectRemoving > removing;
  };
}
