#include "Schedule.h"

#include "Encounter/Encounter.h"

#include "TimelineActor.h"
#include "TimelineActorState.h"
#include "TimelinePack.h"
#include "Timepoint.h"

#include <unordered_map>

namespace Sapphire
{
  void Schedule::from_json( const nlohmann::json& json )
  {
    static std::unordered_map< std::string, Schedule::LoopType > loopTypeMap =
    {
      { "none",         Schedule::LoopType::None },
      { "infinite",     Schedule::LoopType::Infinite },
      { "finite",       Schedule::LoopType::Finite },
    };

    m_id = json.at( "id" ).get< uint32_t >();
    m_name = json.at( "name" ).get< std::string >();
    m_description = json.at( "description" ).get< std::string >();
    m_loopType = loopTypeMap.at( json.at( "loopType" ).get< std::string >() );
    m_loopCount = json.at( "loopCount" ).get< uint32_t >();
  }

  void Schedule::addTimepoint( const Timepoint& timepoint )
  {
    m_timepoints.push_back( timepoint );
  }

  void Schedule::execute( TimelineActor& self, TimelinePack& pack, PhaseState& state, EncounterPtr pEncounter, uint64_t time ) const
  {
    // loop
    if( completed( state ) )
    {
      if( m_loopType == Schedule::LoopType::Infinite )
      {
        resetForLoop( state );
      }
      else if( m_loopType == Schedule::LoopType::Finite )
      {
        auto& scheduleInfo = state.m_scheduleInfo[ m_id ];
        if( scheduleInfo.m_loopCount < m_loopCount )
        {
          resetForLoop( state );
          scheduleInfo.m_loopCount++;
        }
      }
      else
      {
        return;
      }
    }

    if( pack.getStartTime() == 0 )
    {
      pack.setStartTime( time );
      pack.spawnAllSubActors( pEncounter );
    }

    if( state.m_startTime == 0 )
      state.m_startTime = time;

    auto& scheduleInfo = state.m_scheduleInfo[ m_id ];

    if( scheduleInfo.m_startTime == 0 )
      scheduleInfo.m_startTime = time;

    if( scheduleInfo.m_lastTimepointTime == 0 )
      scheduleInfo.m_lastTimepointTime = time;

    for( auto i = scheduleInfo.m_lastTimepointIndex; i < m_timepoints.size(); )
    {
      auto elapsed = time - scheduleInfo.m_startTime;
      const auto& timepoint = m_timepoints[ i ];

      if( elapsed >= timepoint.m_offset )
      {
        // todo: stall the timeline while auto attack is queued
        if( timepoint.execute( self, pack, pEncounter, time ) )
        {
          scheduleInfo.m_lastTimepointTime = time;
          scheduleInfo.m_lastTimepointIndex = ++i;
          continue;
        }
        else
        {
          scheduleInfo.m_pauseTime = time;
        }
      }
      break;
    }
  }

  void Schedule::resetForLoop( PhaseState& state ) const
  {
    auto& scheduleInfo = state.m_scheduleInfo[ m_id ];

    scheduleInfo.m_startTime = 0;
    scheduleInfo.m_pauseTime = 0;
    scheduleInfo.m_lastTimepointIndex = 0;
    scheduleInfo.m_lastTimepointTime = 0;
  }

  void Schedule::reset( PhaseState& state ) const
  {
    auto& scheduleInfo = state.m_scheduleInfo[ m_id ];

    scheduleInfo.m_startTime = 0;
    scheduleInfo.m_pauseTime = 0;
    scheduleInfo.m_lastTimepointIndex = 0;
    scheduleInfo.m_lastTimepointTime = 0;
    scheduleInfo.m_loopCount = 0;
  }

  bool Schedule::completed( PhaseState& state ) const
  {
    auto& scheduleInfo = state.m_scheduleInfo[ m_id ];
    return scheduleInfo.m_lastTimepointIndex == m_timepoints.size();
  }
}// namespace Sapphire