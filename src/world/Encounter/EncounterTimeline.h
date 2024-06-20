#pragma once

#include <fstream>
#include <memory>

#include <optional>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include <AI/TargetHelper.h>
#include <Territory/Territory.h>
#include <Common.h>
#include <Forwards.h>

#include "Selector.h"
#include "Forwards.h"

namespace Sapphire::Encounter
{
  enum class TimelinePackType : uint32_t
  {
    Solo,
    EncounterFight
  };

  // todo: actually handle solo stuff properly (or tie to zone director/content director at least)
  class TimelinePack
  {
    TimelinePackType m_type{ TimelinePackType::EncounterFight };
    std::vector< TimelineActor > m_actors;
    std::string m_name;

    std::unordered_map< std::string, Selector > m_selectors;

    uint64_t m_startTime{ 0 };

  public:
    TimelinePack() {}
    TimelinePack( const TimelinePack& rhs ) :
      m_type( rhs.m_type ),
      m_name( rhs.m_name ),
      m_actors( rhs.m_actors ),
      m_startTime( 0 )
    {
    }

    TimelinePack( TimelinePackType type ) : m_type( type ) {}

    void setName( const std::string& name );

    void addSelector( const std::string& name, const Selector& selector );

    void createSnapshot( const std::string& selectorName, Entity::CharaPtr pSrc,
                         const std::vector< uint32_t >& exclude );

    const World::AI::Snapshot::Results& getSnapshotResults( const std::string& selectorName );

    const World::AI::Snapshot::TargetIds& getSnapshotTargetIds( const std::string& selectorName );

    void addTimelineActor( const TimelineActor& actor );

    Entity::BNpcPtr getBNpcByActorRef( const std::string& name, TerritoryPtr pTeri, const std::string& subActorName = {} );

    void setStartTime( uint64_t time );

    uint64_t getStartTime() const;

    void update( TerritoryPtr pTeri, uint64_t time );
  };

  class EncounterTimeline
  {
  public:

    TimelinePack getEncounterPack( const std::string& name, bool reload = false );
  };
}// namespace Sapphire