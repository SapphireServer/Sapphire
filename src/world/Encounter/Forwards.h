#pragma once

#include <memory>

namespace Sapphire::Encounter
{
  class Selector;
  class TimelineActor;
  class Schedule;
  class ScheduleCondition;
  class Timepoint;

  class TimelinePack;

  using ScheduleConditionPtr = std::shared_ptr< ScheduleCondition >;
}