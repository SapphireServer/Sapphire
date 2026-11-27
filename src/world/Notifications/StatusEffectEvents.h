#pragma once

#include <cstdint>

#include "EventSignal.h"

namespace Sapphire::Entity
{
  class Chara;
}

namespace Sapphire::StatusEffect
{
  class StatusEffect;
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

  // Published for each effect in the target's status snapshot before damage.
  struct StatusEffectTargetHit
  {
    Entity::Chara& target;
    StatusEffect::StatusEffect& effect;
  };

  struct StatusEffectEvents
  {
    EventSignal< StatusEffectApplied > applied;
    EventSignal< StatusEffectRemoving > removing;
    EventSignal< StatusEffectTargetHit > targetHit;
  };
}
