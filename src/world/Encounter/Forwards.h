#pragma once

#include <memory>

namespace Sapphire::Encounter
{
  class Selector;
  class TimelineActor;
  class Phase;
  class PhaseCondition;
  class Timepoint;

  class TimelinePack;

  using PhaseConditionPtr = std::shared_ptr< PhaseCondition >;
}