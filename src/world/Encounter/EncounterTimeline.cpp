#include "EncounterTimeline.h"

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

namespace Sapphire::Encounter
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
    static std::map< std::string, TimelinePack > cache = {};
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
      { "bnpcHasFlags",             ConditionType::BNpcHasFlags }
    };

    TimelinePack pack;
    if( cache.find( name ) != cache.end() && !reload )
      return cache.at( name );

    std::string encounter_name( fmt::format( std::string( "data/EncounterTimelines/%s.json" ), name ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return pack;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< std::string, Phase > > actorNamePhaseMap;

    for( const auto& selectorJ : json.at( "selectors" ).items() )
    {
      auto selectorV = selectorJ.value();
      auto name = selectorV.at( "name" );
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
      for( const auto& phaseJ : json.at( "phases" ).items() )
      {
        auto& phaseV = phaseJ.value();
        const auto id = phaseV.at( "id" ).get< uint32_t >();
        const auto& phaseName = phaseV.at( "name" ).get< std::string >();
        const auto& timepointsJ = phaseV.at( "timepoints" );

        Phase phase;
        for( const auto& timepointJ : timepointsJ.items() )
        {
          auto timepointV = timepointJ.value();
          Timepoint timepoint;
          timepoint.from_json( timepointV, actorNameMap, actor.m_layoutId );

          phase.m_timepoints.push_back( timepoint );
        }

        if( phaseNameMap.find( phaseName ) != phaseNameMap.end() )
          throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - duplicate phase by name: %s" ), phaseName ) );

        phaseNameMap.emplace( std::make_pair( phaseName, phase ) );
      }
      actorNamePhaseMap[ actorName ] = phaseNameMap;
      if( actorNameMap.find( actorName ) != actorNameMap.end() )
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - duplicate actor by name: %s" ), actorName ) );

      actorNameMap.emplace( std::make_pair( actorName, actor ) );
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
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no condition id found by name: %s" ), conditionName ) );

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
          PhaseConditionPtr pCondition;
          switch( condition )
          {
            case ConditionType::HpPctLessThan:
            case ConditionType::HpPctBetween:
            {
              auto pHpCondition = std::make_shared< ConditionHp >();
              pHpCondition->from_json( pcV, phase, condition, actorNameMap );
            }
            break;
            case ConditionType::DirectorVarEquals:
            case ConditionType::DirectorVarGreaterThan:
            case ConditionType::DirectorFlagsEquals:
            case ConditionType::DirectorFlagsGreaterThan:
            case ConditionType::DirectorSeqEquals:
            case ConditionType::DirectorSeqGreaterThan:
            {
              auto pDirectorCondition = std::make_shared< ConditionDirectorVar >();
              pDirectorCondition->from_json( pcV, phase, condition );
            }
            break;
            case ConditionType::EncounterTimeElapsed:
            {
              auto pEncounterCondition = std::make_shared< ConditionEncounterTimeElapsed >();
              pEncounterCondition->from_json( pcV, phase, condition );
            }
            break;
            case ConditionType::CombatState:
            {
              auto pCombatStateCondition = std::make_shared< ConditionCombatState >();
              pCombatStateCondition->from_json( pcV, phase, condition, actorNameMap );
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
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no state found by name: %s" ), phaseRef ) );
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
    m_actors.emplace_back( actor );
  }

  Entity::BNpcPtr TimelinePack::getBNpcByActorRef( const std::string& name, TerritoryPtr pTeri, const std::string& subActorName )
  {
    for( const auto& actor : m_actors )
    {
      if( actor.m_name == name )
      {
        return actor.getBNpcByRef( name, pTeri );
      }
    }
    return nullptr;
  }

  void TimelinePack::setStartTime( uint64_t time )
  {
    m_startTime = time;
  }

  uint64_t TimelinePack::getStartTime() const
  {
    return m_startTime;
  }

  void TimelinePack::update( TerritoryPtr pTeri, uint64_t time )
  {
    for( auto& actor : m_actors )
      actor.update( pTeri, *this, time );
  }
}// namespace Sapphire::Encounter