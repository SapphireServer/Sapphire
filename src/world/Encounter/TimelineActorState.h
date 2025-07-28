#pragma once

#include <cstdint>
#include <vector>

namespace Sapphire
{
struct TimepointState
{
  uint64_t m_startTime{ 0 };
  uint64_t m_lastTick{ 0 };
  bool m_finished{ false };
};

struct ConditionState
{
  uint64_t m_startTime{ 0 };
  bool m_loop{ false };
  bool m_completed{ false };
  bool m_enabled{ false };

  struct ScheduleInfo
  {
    uint64_t m_startTime{ 0 };
    uint64_t m_lastTimepointTime{ 0 };
    uint32_t m_lastTimepointIndex{ 0 };

    std::vector< TimepointState > m_timepointStates;
  } m_scheduleInfo;
};
}; // namespace Sapphire::Encounter