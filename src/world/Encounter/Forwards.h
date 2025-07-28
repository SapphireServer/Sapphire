#pragma once

#include <memory>

namespace Sapphire
{
  class Selector;
  class TimelineActor;
  class Phase;
  class PhaseCondition;
  class Timepoint;

  class Encounter;
  class TimelinePack;

  using PhaseConditionPtr = std::shared_ptr< PhaseCondition >;
  using EncounterPtr = std::shared_ptr< Encounter >;
}