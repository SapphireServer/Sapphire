#include "EncounterTimeline.h"
#include "Encounter.h"

#include "Timepoint.h"
#include "TimelineActorState.h"
#include "TimelineActor.h"
#include "PhaseCondition.h"
#include "Selector.h"

#include <Action/Action.h>

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Actor/EventObject.h>
#include <Actor/Player.h>

#include <Event/Director.h>

#include <Manager/ActionMgr.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

#include <Territory/QuestBattle.h>
#include <Territory/InstanceContent.h>
#include <Util/UtilMath.h>
#include <Util/Util.h>

#include <filesystem>

namespace Sapphire
{

  /*
  class RngCondition : TimepointCondition
  {
    EncounterTimepointcondition m_type;
    std::vector< uint32_t > m_params
    
    RngCondition( EncounterTimepointcondition condition std::vector< uint32_t params ) : m_type( condition ), m_params( params ){}
    bool isConditionMet( uint32_t shit )
    {
      switch( m_type )
      {
        case EncounterTimepointcondition::RngMinMax:
          return RNGMgr::generate( params[0], params[1] ) == params[2];
      }
      return false;
    }
  }
  enum class ActionCallbackType : uint32_t
  {
    OnActionInit,
    OnActionStart,
    OnActionInterrupt,
    OnActionExecute
  };

  using CallbackFunc = std::function< void < CharaPtr, Action > >;

  std::unordered_map< ActionCallbackType, CallbackFunc > m_actionCallbacks;
  void Chara::registerActionCallback( ActionCallbackType type, CallbackFunc callback )
  {
    m_actionCallbacks[ type ].push_back( callback );
  }

  // call this when changing EncounterPack
  void Chara::clearActionCallbacks()
  {
    for( auto& callback : m_actionCallbacks )
      callback.second.clear()
  }

  void Chara::onActionInterrupt()
  {
    auto action = getCurrentAction();
    for( auto& callback : m_actionCallbacks[ ActionCallbackType::OnActionInterrupt ] )
      callback( this, action );
  }

  void EncounterTimeline::Timepoint::execute( TerritoryPtr pTeri, uint64_t time )
  {
    switch( m_type )
    {
      case TimepointDataType::CastAction:
      {
        auto pActionData = std::dynamic_pointer_cast< TimepointDataAction, TimepointData >( getData() );

        // todo: filter the correct target
        // todo: tie to mechanic script?
      }
    }
  }
  */

  //
  // parsing stuff below
  //

  TimelinePack EncounterTimeline::getEncounterPack( const std::string& name, bool reload )
  {
    static std::unordered_map< std::string, TimelinePack > cache = {};
    const static std::unordered_map< std::string, ConditionType > conditionMap =
    {
      { "hpPctLessThan",            ConditionType::HpPctLessThan },
      { "hpPctBetween",             ConditionType::HpPctBetween },

      { "directorVarEquals",        ConditionType::DirectorVarEquals },
      { "directorVarGreaterThan",   ConditionType::DirectorVarGreaterThan },

      { "directorSeqEquals",        ConditionType::DirectorSeqEquals },
      { "directorSeqGreaterThan",   ConditionType::DirectorSeqGreaterThan },

      { "directorFlagsEquals",      ConditionType::DirectorFlagsEquals },
      { "directorFlagsGreaterThan", ConditionType::DirectorFlagsGreaterThan },

      { "encounterTimeElapsed",     ConditionType::EncounterTimeElapsed },

      { "combatState",              ConditionType::CombatState },
      { "bnpcHasFlags",             ConditionType::BNpcHasFlags },

      { "getAction",                ConditionType::GetAction },
      { "phaseActive",              ConditionType::PhaseActive }
    };

    TimelinePack pack;
    if( cache.find( name ) != cache.end() && !reload )
      return cache.at( name );

    std::string encounter_name( fmt::format( std::string( "data/EncounterTimelines/{}.json" ), name ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return pack;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< std::string, Phase > > actorNamePhaseMap;

    for( const auto& selectorJ : json.at( "selectors" ).items() )
    {
      auto& selectorV = selectorJ.value();
      auto name = selectorV.at( "name" ).get< std::string >();
      Selector selector;
      selector.from_json( selectorV );

      pack.addSelector( name, selector );
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
      std::map< std::string, Phase > phaseNameMap;

      auto actorV = actorJ.value();
      std::string actorName = actorV.at( "name" );

      TimelineActor& actor = actorNameMap[ actorName ];
      // todo: are phases linked by actor, or global in the json
      for( const auto& phaseJ : actorV.at( "phases" ).items() )
      {
        auto& phaseV = phaseJ.value();
        const auto id = phaseV.at( "id" ).get< uint32_t >();
        const auto& phaseName = phaseV.at( "name" ).get< std::string >();
        const auto& timepointsJ = phaseV.at( "timepoints" );
        const auto& description = phaseV.at( "description" ).get< std::string >();

        Phase phase;
        phase.m_name = phaseName;
        phase.m_description = description;
        for( const auto& timepointJ : timepointsJ.items() )
        {
          auto timepointV = timepointJ.value();
          Timepoint timepoint;
          timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

          phase.m_timepoints.push_back( timepoint );
        }

        if( phaseNameMap.find( phaseName ) != phaseNameMap.end() )
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::getEncounterPack - duplicate phase by name: {}" ), phaseName ) );

        phaseNameMap.emplace( std::make_pair( phaseName, phase ) );
      }
      actorNamePhaseMap[ actorName ] = phaseNameMap;
    }

    // build the condition list
    for( const auto& pcJ : json.at( "conditions" ).items() )
    {
      auto& pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string >();
      auto phaseRef = pcV.at( "targetPhase" ).get< std::string >();
      auto actorRef = pcV.at( "targetActor" ).get< std::string >();
      
      ConditionType condition;

      // make sure condition exists
      if( auto it = conditionMap.find( conditionName ); it != conditionMap.end() )
        condition = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::getEncounterPack - no condition id found by name: {}" ), conditionName ) );

      // make sure the actor we're referencing exists
      if( auto actorIt = actorNameMap.find( actorRef ); actorIt != actorNameMap.end() )
      {
        auto& phaseNameMap = actorNamePhaseMap[ actorRef ];

        TimelineActor& actor = actorIt->second;

        // make sure phase we're referencing exists
        if( auto phaseIt = phaseNameMap.find( phaseRef ); phaseIt != phaseNameMap.end() )
        {
          Phase& phase = phaseIt->second;

          // build the condition
          PhaseConditionPtr pCondition = nullptr;
          switch( condition )
          {
            case ConditionType::HpPctLessThan:
            case ConditionType::HpPctBetween:
            {
              pCondition = std::make_shared< ConditionHp >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
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
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            case ConditionType::EncounterTimeElapsed:
            {
              pCondition = std::make_shared< ConditionEncounterTimeElapsed >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            case ConditionType::CombatState:
            {
              pCondition = std::make_shared< ConditionCombatState >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            case ConditionType::GetAction:
            {
              pCondition = std::make_shared< ConditionGetAction >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            case ConditionType::PhaseActive:
            {
              pCondition = std::make_shared< ConditionPhaseActive >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
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
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::getEncounterPack - no state found by name: {}" ), phaseRef ) );
      }
    }

    for( const auto& actor : actorNameMap )
      pack.addTimelineActor( actor.second );

    pack.setName( name );

    // todo: reload will probably kill the server when CastAction.callbacks are added
    if( reload )
      cache[ name ] = pack;
    else
      cache.emplace( std::make_pair( name, pack ) );
    return pack;
  }

  std::shared_ptr< TimelinePack > EncounterTimeline::createTimelinePack( const std::string& name )
  {
    const static std::unordered_map< std::string, ConditionType > conditionMap =
    {
      { "hpPctLessThan",            ConditionType::HpPctLessThan },
      { "hpPctBetween",             ConditionType::HpPctBetween },

      { "directorVarEquals",        ConditionType::DirectorVarEquals },
      { "directorVarGreaterThan",   ConditionType::DirectorVarGreaterThan },

      { "directorSeqEquals",        ConditionType::DirectorSeqEquals },
      { "directorSeqGreaterThan",   ConditionType::DirectorSeqGreaterThan },

      { "directorFlagsEquals",      ConditionType::DirectorFlagsEquals },
      { "directorFlagsGreaterThan", ConditionType::DirectorFlagsGreaterThan },

      { "encounterTimeElapsed",     ConditionType::EncounterTimeElapsed },

      { "combatState",              ConditionType::CombatState },
      { "bnpcHasFlags",             ConditionType::BNpcHasFlags },

      { "getAction",                ConditionType::GetAction },
      { "phaseActive",              ConditionType::PhaseActive }
    };

    auto pack = std::make_shared< TimelinePack >();
    std::string encounter_name( fmt::format( std::string( "data/EncounterTimelines/{}.json" ), name ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return nullptr;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< std::string, Phase > > actorNamePhaseMap;

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
      std::map< std::string, Phase > phaseNameMap;

      auto actorV = actorJ.value();
      std::string actorName = actorV.at( "name" );

      TimelineActor& actor = actorNameMap[ actorName ];
      // todo: are phases linked by actor, or global in the json
      for( const auto& phaseJ : actorV.at( "phases" ).items() )
      {
        auto& phaseV = phaseJ.value();
        const auto id = phaseV.at( "id" ).get< uint32_t >();
        const auto& phaseName = phaseV.at( "name" ).get< std::string >();
        const auto& timepointsJ = phaseV.at( "timepoints" );
        const auto& description = phaseV.at( "description" ).get< std::string >();

        Phase phase;
        phase.m_name = phaseName;
        phase.m_description = description;
        for( const auto& timepointJ : timepointsJ.items() )
        {
          auto timepointV = timepointJ.value();
          Timepoint timepoint;
          timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

          phase.m_timepoints.push_back( timepoint );
        }

        if( phaseNameMap.find( phaseName ) != phaseNameMap.end() )
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::getEncounterPack - duplicate phase by name: {}" ), phaseName ) );

        phaseNameMap.emplace( std::make_pair( phaseName, phase ) );
      }
      actorNamePhaseMap[ actorName ] = phaseNameMap;
    }

    // build the condition list
    for( const auto& pcJ : json.at( "conditions" ).items() )
    {
      auto& pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string >();
      auto phaseRef = pcV.at( "targetPhase" ).get< std::string >();
      auto actorRef = pcV.at( "targetActor" ).get< std::string >();

      ConditionType condition;

      // make sure condition exists
      if( auto it = conditionMap.find( conditionName ); it != conditionMap.end() )
        condition = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::getEncounterPack - no condition id found by name: {}" ), conditionName ) );

      // make sure the actor we're referencing exists
      if( auto actorIt = actorNameMap.find( actorRef ); actorIt != actorNameMap.end() )
      {
        auto& phaseNameMap = actorNamePhaseMap[ actorRef ];

        TimelineActor& actor = actorIt->second;

        // make sure phase we're referencing exists
        if( auto phaseIt = phaseNameMap.find( phaseRef ); phaseIt != phaseNameMap.end() )
        {
          Phase& phase = phaseIt->second;

          // build the condition
          PhaseConditionPtr pCondition = nullptr;
          switch( condition )
          {
            case ConditionType::HpPctLessThan:
            case ConditionType::HpPctBetween:
            {
              pCondition = std::make_shared< ConditionHp >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
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
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
              break;
            case ConditionType::EncounterTimeElapsed:
            {
              pCondition = std::make_shared< ConditionEncounterTimeElapsed >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
              break;
            case ConditionType::CombatState:
            {
              pCondition = std::make_shared< ConditionCombatState >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
              break;
            case ConditionType::GetAction:
            {
              pCondition = std::make_shared< ConditionGetAction >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
            }
              break;
            case ConditionType::PhaseActive:
            {
              pCondition = std::make_shared< ConditionPhaseActive >();
              pCondition->from_json( pcV, phase, condition, actorNameMap );
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
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::getEncounterPack - no state found by name: {}" ), phaseRef ) );
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

  void TimelinePack::createSnapshot( const std::string& selectorName, Entity::CharaPtr pSrc, const std::vector< uint32_t >& exclude )
  {
    if( auto it = m_selectors.find( selectorName ); it != m_selectors.end() )
      it->second.createSnapshot( pSrc, exclude );
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

  bool TimelinePack::isPhaseActive( const std::string& actorName, const std::string& phaseName )
  {
    for( const auto& actor : m_timelineActors )
      if( actor.getName() == actorName )
        return actor.isPhaseActive( phaseName );
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
}// namespace Sapphire::Encounter