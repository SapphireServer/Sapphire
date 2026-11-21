#pragma once

#include <cstdint>
#include <vector>
#include <map>

namespace Sapphire::World::Encounter
{
  struct TimepointState
  {
    uint64_t m_startTime{ 0 };
    uint64_t m_lastTick{ 0 };
    bool m_finished{ false };

    void shiftTimes( uint64_t deltaMs )
    {
      if( m_startTime )
        m_startTime += deltaMs;

      if( m_lastTick )
        m_lastTick += deltaMs;
    }
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

      void shiftTimes( uint64_t deltaMs )
      {
        if( m_startTime )
          m_startTime += deltaMs;

        if( m_pauseTime )
          m_pauseTime += deltaMs;

        if( m_lastTimepointTime )
          m_lastTimepointTime += deltaMs;

        for( auto& tp : m_timepointStates )
          tp.shiftTimes( deltaMs );
      }
    };

    std::map< uint32_t, bool > m_triggerStates;
    std::map< uint32_t, ScheduleInfo > m_scheduleInfo;

    void shiftTimes( uint64_t delta )
    {
      if( m_startTime )
        m_startTime += delta;

      for( auto& [ id, info ] : m_scheduleInfo )
        info.shiftTimes( delta );
    }
  };

  struct TimelineActorState
  {
    uint32_t m_phaseId{ 1 };
    PhaseState m_phaseState;

    void shiftTimes( uint64_t deltaMs )
    {
      m_phaseState.shiftTimes( deltaMs );
    }
  };
};// namespace Sapphire