#pragma once

#include <memory>

namespace Sapphire
{
  class Selector;
  class TimelineActor;
  class Schedule;
  class ScheduleCondition;
  class Timepoint;

  class Encounter;
  class TimelinePack;

  using ScheduleConditionPtr = std::shared_ptr< ScheduleCondition >;
  using EncounterPtr = std::shared_ptr< Encounter >;
}