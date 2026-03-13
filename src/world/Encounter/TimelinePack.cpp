#include "TimelinePack.h"

#include "TimelinePack.h"
#include "Encounter.h"

#include "Timepoint.h"
#include "TimelineActorState.h"
#include "TimelineActor.h"
#include "ScheduleCondition.h"
#include "Selector.h"

#include <Action/Action.h>

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Actor/EventObject.h>
#include <Actor/Player.h>

#include <Event/Director.h>

#include <Manager/ActionMgr.h>
#include <Manager/PlayerMgr.h>

#include <Random/RNGMgr.h>

#include <Service.h>

#include <Territory/QuestBattle.h>
#include <Territory/InstanceContent.h>
#include <Util/UtilMath.h>
#include <Util/Util.h>

#include <filesystem>

namespace Sapphire
{
  //
  // parsing stuff below
  //

  std::shared_ptr< TimelinePack > TimelinePack::createTimelinePack( const std::string& name )
  {
    const static std::unordered_map< std::string, ConditionType > conditionMap =
    {
      { "hpPctLessThan",            ConditionType::HpPctLessThan },
      { "hpPctBetween",             ConditionType::HpPctBetween },

      { "varEquals",                ConditionType::VarEquals },
      { "directorVarGreaterThan",   ConditionType::DirectorVarGreaterThan },

      { "directorSeqEquals",        ConditionType::DirectorSeqEquals },
      { "directorSeqGreaterThan",   ConditionType::DirectorSeqGreaterThan },

      { "directorFlagsEquals",      ConditionType::DirectorFlagsEquals },
      { "directorFlagsGreaterThan", ConditionType::DirectorFlagsGreaterThan },

      { "encounterTimeElapsed",     ConditionType::EncounterTimeElapsed },

      { "combatState",              ConditionType::CombatState },
      { "bnpcHasFlags",             ConditionType::BNpcHasFlags },

      { "getAction",                ConditionType::GetAction },
      { "scheduleActive",           ConditionType::ScheduleActive },
      { "interruptedAction",        ConditionType::InterruptedAction },
    };

    auto pack = std::make_shared< TimelinePack >();
    std::string encounter_name( fmt::format( std::string( "data/encounterTimelines/{}.json" ), name ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return nullptr;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< std::string, Schedule > > actorNameScheduleMap;

    for( const auto& selectorJ : json.at( "selectors" ).items() )
    {
      auto& selectorV = selectorJ.value();
      auto name = selectorV.at( "name" ).get< std::string >();
      Selector selector;
      selector.from_json( selectorV );

      pack->addSelector( name, selector );
    }

    // first run through cache actor info
    for( const auto& actorJ : json.at( "actors" ).items() )
    {
      TimelineActor actor;
      auto& actorV = actorJ.value();
      actor.m_hp = actorV.at( "hp" ).get< uint32_t >();
      actor.m_layoutId = actorV.at( "layoutId" ).get< uint32_t >();
      actor.m_name = actorV.at( "name" ).get< std::string >();

      auto& subActorsJ = actorV.at( "subactors" );

      if( !subActorsJ.is_null() )
        for( const auto& subActorV : subActorsJ.items() )
          actor.addPlaceholderSubactor( subActorV.value().get< std::string >() );

      actorNameMap.emplace( std::make_pair( actor.m_name, actor ) );
    }

    // build timeline info per actor
    for( const auto& actorJ : json.at( "actors" ).items() )
    {
      // < actorName, < phasename, phase > >
      std::map< std::string, Schedule > scheduleNameMap;

      auto& actorV = actorJ.value();
      std::string actorName = actorV.at( "name" );

      TimelineActor& actor = actorNameMap[ actorName ];
      // todo: are phases linked by actor, or global in the json
      for( const auto& scheduleJ : actorV.at( "schedules" ).items() )
      {
        auto& scheduleV = scheduleJ.value();
        const auto id = scheduleV.at( "id" ).get< uint32_t >();
        const auto& scheduleName = scheduleV.at( "name" ).get< std::string >();
        const auto& timepointsJ = scheduleV.at( "timepoints" );
        const auto& description = scheduleV.at( "description" ).get< std::string >();

        Schedule phase;
        phase.m_name = scheduleName;
        phase.m_description = description;
        for( const auto& timepointJ : timepointsJ.items() )
        {
          auto& timepointV = timepointJ.value();
          Timepoint timepoint;
          timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

          phase.m_timepoints.push_back( timepoint );
        }

        if( scheduleNameMap.find( scheduleName ) != scheduleNameMap.end() )
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::createTimelinePack - duplicate phase by name: {}" ), scheduleName ) );

        scheduleNameMap.emplace( std::make_pair( scheduleName, phase ) );
      }
      actorNameScheduleMap[ actorName ] = scheduleNameMap;
    }

    // build the condition list
    for( const auto& pcJ : json.at( "conditions" ).items() )
    {
      auto& pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string >();
      auto scheduleRef = pcV.at( "targetSchedule" ).get< std::string >();
      auto actorRef = pcV.at( "targetActor" ).get< std::string >();

      ConditionType condition;

      // make sure condition exists
      if( auto it = conditionMap.find( conditionName ); it != conditionMap.end() )
        condition = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::createTimelinePack - no condition id found by name: {}" ), conditionName ) );

      // make sure the actor we're referencing exists
      if( auto actorIt = actorNameMap.find( actorRef ); actorIt != actorNameMap.end() )
      {
        auto& scheduleNameMap = actorNameScheduleMap[ actorRef ];

        TimelineActor& actor = actorIt->second;

        // make sure phase we're referencing exists
        if( auto scheduleIt = scheduleNameMap.find( scheduleRef ); scheduleIt != scheduleNameMap.end() )
        {
          Schedule& schedule = scheduleIt->second;

          // build the condition
          ScheduleConditionPtr pCondition = nullptr;
          switch( condition )
          {
            case ConditionType::HpPctLessThan:
            case ConditionType::HpPctBetween:
            {
              pCondition = std::make_shared< ConditionHp >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            case ConditionType::DirectorVarEquals:
            case ConditionType::DirectorVarGreaterThan:
            case ConditionType::DirectorFlagsEquals:
            case ConditionType::DirectorFlagsGreaterThan:
            case ConditionType::DirectorSeqEquals:
            case ConditionType::DirectorSeqGreaterThan:
            {
              pCondition = std::make_shared< ConditionDirectorVar >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );

            }
            break;
            case ConditionType::EncounterTimeElapsed:
            {
              pCondition = std::make_shared< ConditionEncounterTimeElapsed >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            case ConditionType::CombatState:
            {
              pCondition = std::make_shared< ConditionCombatState >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            case ConditionType::GetAction:
            {
              pCondition = std::make_shared< ConditionGetAction >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            case ConditionType::ScheduleActive:
            {
              pCondition = std::make_shared< ConditionScheduleActive >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            case ConditionType::InterruptedAction:
            {
              pCondition = std::make_shared< ConditionInterruptedAction >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            case ConditionType::VarEquals:
            {
              pCondition = std::make_shared< ConditionVarEquals >();
              pCondition->from_json( pcV, schedule, condition, actorNameMap );
            }
            break;
            default:
              break;
          }
          actor.addPhaseCondition( pCondition );
        }
      }
      else
      {
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::createTimelinePack - no state found by name: {}" ), scheduleRef ) );
      }
    }

    for( const auto& actor : actorNameMap )
      pack->addTimelineActor( actor.second );

    pack->setName( name );
    return pack;
  }

  void TimelinePack::setName( const std::string& name )
  {
    m_name = name;
  }

  void TimelinePack::addSelector( const std::string& name, const Selector& selector )
  {
    m_selectors.emplace( std::make_pair( name, selector ) );
  }

  void TimelinePack::createSnapshot( const std::string& selectorName, Entity::Chara& src, const std::vector< uint32_t >& exclude )
  {
    if( auto it = m_selectors.find( selectorName ); it != m_selectors.end() )
      it->second.createSnapshot( src, exclude );
  }

  const World::AI::Snapshot::Results& TimelinePack::getSnapshotResults( const std::string& selectorName )
  {
    static World::AI::Snapshot::Results empty;
    if( auto it = m_selectors.find( selectorName ); it != m_selectors.end() )
      return it->second.getResults();
    return empty;
  }

  const World::AI::Snapshot::TargetIds& TimelinePack::getSnapshotTargetIds( const std::string& selectorName )
  {
    static World::AI::Snapshot::TargetIds empty;
    if( auto it = m_selectors.find( selectorName ); it != m_selectors.end() )
      return it->second.getTargetIds();
    return empty;
  }

  void TimelinePack::addTimelineActor( const TimelineActor& actor )
  {
    m_timelineActors.emplace_back( actor );
  }

  Entity::BNpcPtr TimelinePack::getBNpcByRef( const std::string& name, EncounterPtr pEncounter )
  {
    for( const auto& actor : m_timelineActors )
    {
      auto pBNpc = actor.getBNpcByRef( name, pEncounter->getTeriPtr() );
      if( pBNpc )
        return pBNpc;
    }
    return nullptr;
  }

  void TimelinePack::reset( EncounterPtr pEncounter )
  {
    for( auto& actor : m_timelineActors )
    {
      actor.resetAllSubActors( pEncounter->getTeriPtr() );
      actor.resetAllConditionStates();
    }
    m_startTime = 0;
    m_vars.clear();
  }

  void TimelinePack::setStartTime( uint64_t time )
  {
    m_startTime = time;
  }

  uint64_t TimelinePack::getStartTime() const
  {
    return m_startTime;
  }

  void TimelinePack::update( uint64_t time )
  {
    auto now = Common::Util::getTimeMs(); 
    for( auto& actor : m_timelineActors )
      actor.update( m_pEncounter, *this, now );
  }

  bool TimelinePack::isScheduleActive( const std::string& actorName, const std::string& scheduleName )
  {
    for( const auto& actor : m_timelineActors )
      if( actor.getName() == actorName )
        return actor.isScheduleActive( scheduleName );
    return false;
  }

  void TimelinePack::resetConditionState( uint32_t id, bool toDefault )
  {
    for( auto& actor : m_timelineActors )
    {
      if( actor.resetConditionState( id, toDefault ) )
        return;
    }
  }

  void TimelinePack::setConditionStateEnabled( uint32_t id, bool enabled )
  {
    for( auto& actor : m_timelineActors )
    {
      if( actor.setConditionStateEnabled( id, enabled ) )
        return;
    }
  }

  bool TimelinePack::valid()
  {
    return !m_timelineActors.empty();
  }

  void TimelinePack::setEncounter( std::shared_ptr< Encounter > pEncounter )
  {
    m_pEncounter = pEncounter;
  }

  uint32_t TimelinePack::getVar( uint32_t index ) const
  {
    auto it = m_vars.find( index );
    if( it != m_vars.end() )
      return it->second;
    return 0;
  }

  void TimelinePack::setVar( uint32_t index, uint32_t val )
  {
    m_vars[ index ] = val;
  }
}// namespace Sapphire::Encounter