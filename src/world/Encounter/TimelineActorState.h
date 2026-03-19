#pragma once

#include <cstdint>
#include <vector>
#include <map>

namespace Sapphire
{
  struct TimepointState
  {
    uint64_t m_startTime{ 0 };
    uint64_t m_lastTick{ 0 };
    bool m_finished{ false };
  };

  struct PhaseState
  {
    uint64_t m_startTime{ 0 };

    struct ScheduleInfo
    {
      uint64_t m_startTime{ 0 };
      uint64_t m_pauseTime{ 0 };
      uint64_t m_lastTimepointTime{ 0 };
      uint32_t m_lastTimepointIndex{ 0 };

      uint32_t m_loopCount{ 0 };

      std::vector< TimepointState > m_timepointStates;
    };

    std::map< uint32_t, bool > m_triggerStates;
    std::map< uint32_t, ScheduleInfo > m_scheduleInfo;
  };

  struct TimelineActorState
  {
    uint32_t m_phaseId{ 1 };
    PhaseState m_phaseState;
  };
};// namespace Sapphire