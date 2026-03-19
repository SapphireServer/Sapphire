#include "TimelinePack.h"

#include "Encounter.h"

#include "Timepoint.h"
#include "TimelineActorState.h"
#include "TimelineActor.h"
#include "Trigger.h"
#include "TriggerCondition.h"
#include "Phase.h"
#include "Schedule.h"
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
      { "phaseActive",              ConditionType::PhaseActive },
      { "interruptedAction",        ConditionType::InterruptedAction },
    };

    const static std::unordered_map< std::string, TriggerAction::Type > triggerActionMap =
    {
      { "transitionPhase", TriggerAction::Type::TransitionPhase },
      { "fireTimepoint",   TriggerAction::Type::FireTimepoint }
    };

    auto pack = std::make_shared< TimelinePack >();
    std::string encounter_name( fmt::format( std::string( "data/encounterTimelines/{}.json" ), name ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return nullptr;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< uint32_t, PhasePtr > > actorNamePhaseMap;

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
      actor.m_initialPhaseId = actorV.at( "initialPhaseId" ).get< uint32_t >();

      auto& subActorsJ = actorV.at( "subactors" );

      if( !subActorsJ.is_null() )
        for( const auto& subActorV : subActorsJ.items() )
          actor.addPlaceholderSubactor( subActorV.value().get< std::string >() );

      actorNameMap.emplace( std::make_pair( actor.m_name, actor ) );

      // cache phases so we can refer to them from other actors, we'll populate these later
      for( const auto& phaseJ : actorV.at( "phases" ).items() )
      {
        PhasePtr pPhase = std::make_shared< Phase >();
        pPhase->from_json( phaseJ.value() );

        actorNamePhaseMap[ actor.getName() ].emplace( pPhase->getId(), pPhase );
      }
    }

    // build timeline info per actor
    for( const auto& actorJ : json.at( "actors" ).items() )
    {
      auto& actorV = actorJ.value();
      std::string actorName = actorV.at( "name" );

      TimelineActor& actor = actorNameMap[ actorName ];

      auto& phaseV = actorV.at( "phases" );

      for( const auto& phaseJ : phaseV.items() )
      {
        std::map< std::string, Schedule > scheduleNameMap;

        auto phaseId = phaseJ.value().at( "id" ).get< uint32_t >();

        // get the cached phase
        PhasePtr pPhase = actorNamePhaseMap[ actorName ][ phaseId ];

        // onEnter
        {
          auto& onEnterJ = phaseJ.value().at( "onEnter" );
          for( const auto& tpJ : onEnterJ.items() )
          {
            Timepoint timepoint;
            timepoint.from_json( tpJ.value(), actorNameMap, actor.m_layoutId );

            pPhase->addTimepointOnEnter( timepoint );
          }
        }

        // onExit
        {
          auto& onExitJ = phaseJ.value().at( "onExit" );

          for( const auto& tpJ : onExitJ.items() )
          {
            Timepoint timepoint;
            timepoint.from_json( tpJ.value(), actorNameMap, actor.m_layoutId );

            pPhase->addTimepointOnExit( timepoint );
          }
        }

        // Schedules
        for( const auto& scheduleJ : phaseJ.value().at( "schedules" ).items() )
        {
          auto& scheduleV = scheduleJ.value();
          const auto id = scheduleV.at( "id" ).get< uint32_t >();
          const auto& scheduleName = scheduleV.at( "name" ).get< std::string >();
          const auto& timepointsJ = scheduleV.at( "timepoints" );
          const auto& description = scheduleV.at( "description" ).get< std::string >();

          Schedule sched;
          sched.from_json( scheduleV );

          for( const auto& timepointJ : timepointsJ.items() )
          {
            auto& timepointV = timepointJ.value();
            Timepoint timepoint;
            timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

            sched.addTimepoint( timepoint );
          }

          if( scheduleNameMap.find( scheduleName ) != scheduleNameMap.end() )
            throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::createTimelinePack - duplicate scheduke by name: {}" ), scheduleName ) );

          scheduleNameMap.emplace( std::make_pair( scheduleName, sched ) );

          // add to phase
          pPhase->addSchedule( sched.m_id, sched );
        }

        // Triggers
        for( const auto& triggerJ : phaseJ.value().at( "triggers" ).items() )
        {
          Trigger trigger;
          trigger.setId( triggerJ.value().at( "id" ).get< uint32_t >() );

          // Action
          {
            const auto& actionJ = triggerJ.value().at( "action" );
            const auto actionType = triggerActionMap.at( actionJ.at( "type" ).get< std::string >() );
            TriggerActionPtr pAction = std::make_shared< TriggerAction >();
            pAction->m_type = actionType;
            if( pAction->m_type == TriggerAction::Type::TransitionPhase )
            {
              auto phaseId = actionJ.at( "phaseId" ).get< uint32_t >();

              pAction->m_phaseId = phaseId;
            }
            else if( pAction->m_type == TriggerAction::Type::FireTimepoint )
            {
              if( !actionJ.at( "timepoint" ).is_null() )
              {
                auto& timepointV = actionJ.at( "timepoint" );
                Timepoint timepoint;
                timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

                pAction->m_timepoint = timepoint;
              }
            }
            // add the action to the trigger
            trigger.setAction( pAction );
          }

          // Condition
          {
            auto& conditionJ = triggerJ.value();

            ConditionType condition;

            auto conditionName = conditionJ.at( "condition" ).get< std::string >();

            // make sure condition exists
            if( auto it = conditionMap.find( conditionName ); it != conditionMap.end() )
              condition = it->second;
            else
              throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::createTimelinePack - no condition id found by name: {}" ), conditionName ) );

            // build the condition
            TriggerConditionPtr pCondition = nullptr;
            switch( condition )
            {
              case ConditionType::HpPctLessThan:
              case ConditionType::HpPctBetween:
              {
                pCondition = std::make_shared< ConditionHp >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
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
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              case ConditionType::EncounterTimeElapsed:
              {
                pCondition = std::make_shared< ConditionEncounterTimeElapsed >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              case ConditionType::CombatState:
              {
                pCondition = std::make_shared< ConditionCombatState >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              case ConditionType::GetAction:
              {
                pCondition = std::make_shared< ConditionGetAction >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              case ConditionType::PhaseActive:
              {
                pCondition = std::make_shared< ConditionPhaseActive >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              case ConditionType::InterruptedAction:
              {
                pCondition = std::make_shared< ConditionInterruptedAction >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              case ConditionType::VarEquals:
              {
                pCondition = std::make_shared< ConditionVarEquals >();
                pCondition->from_json( conditionJ, condition, actorNameMap );
              }
              break;
              default:
                break;
            }

            // add the condition to the trigger
            trigger.setCondition( pCondition );
          }

          // add the trigger to the phase
          pPhase->addTrigger( trigger );
        }
        // add the phase to the actor
        actor.addPhase( pPhase );
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
      // todo: reset all phases
    }
    m_startTime = 0;
    m_vars.clear();
  }

  void TimelinePack::spawnAllSubActors( EncounterPtr pEncounter )
  {
    for( auto& actor : m_timelineActors )
      actor.spawnAllSubActors( pEncounter->getTeriPtr() );
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

  bool TimelinePack::isPhaseActive( const std::string& actorName, uint32_t phaseId )
  {
    for( const auto& actor : m_timelineActors )
      if( actor.getName() == actorName )
        return actor.isPhaseActive( phaseId );
    return false;
  }

  void TimelinePack::setTriggerEnabled( const std::string& actorRef, uint32_t phaseId, uint32_t triggerId, bool enabled )
  {
    for( auto& actor : m_timelineActors )
    {
      if( actor.getName() == actorRef )
      {
        actor.setTriggerEnabled( phaseId, triggerId, enabled );
        return;
      }
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