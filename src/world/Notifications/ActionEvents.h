#pragma once

#include <cstdint>

#include "EventSignal.h"

namespace Sapphire::Common
{
  enum class ActionInterruptType : uint8_t;
}

namespace Sapphire::World::Action
{
  class Action;
}

namespace Sapphire::World::Notifications
{
  // Published after result construction and before sending action results.
  struct ActionEffectsBuilt
  {
    Action::Action& action;
  };

  // Published after casting cleanup and any cast-interrupt packet is queued.
  struct ActionInterrupted
  {
    Action::Action& action;
    Common::ActionInterruptType reason;
  };

  struct ActionEvents
  {
    EventSignal< ActionEffectsBuilt > effectsBuilt;
    EventSignal< ActionInterrupted > interrupted;
  };
}
