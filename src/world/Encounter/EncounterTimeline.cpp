#include "EncounterFight.h"
#include "EncounterTimeline.h"

#include "../Actor/BNpc.h"
#include "../Actor/Chara.h"

namespace Sapphire
{
  void EncounterTimeline::EncounterConditionHp::from_json( nlohmann::json& json, EncounterPhasePtr pPhase, EncounterConditionId conditionId )
  {
    EncounterTimepointCondition::from_json( json, pPhase, conditionId );

    auto params = json.at( "params" ).get< std::vector< uint32_t > >();

    this->actorId = params[ 0 ];

    if( conditionId == EncounterConditionId::HpPctLessThan )
      this->hp.val = params[ 1 ];
    else
      this->hp.min = params[ 1 ], this->hp.max = params[ 2 ];
  }

  bool EncounterTimeline::EncounterConditionHp::canExecute( EncounterFightPtr pFight, uint64_t time )
  {
    auto pBNpc = pFight->getBNpc( actorId );
    if( !pBNpc )
      return false;

    // todo: check time elapsed

    switch( m_conditionId )
    {
      case EncounterConditionId::HpPctLessThan:
        return pBNpc->getHpPercent() < hp.val;
      case EncounterConditionId::HpPctBetween:
      {
        auto hpPct = pBNpc->getHpPercent();
        return hpPct >= hp.min && hpPct <= hp.max;
      }
    }
    return false;
  };

  void EncounterTimeline::EncounterConditionDirectorVar::from_json( nlohmann::json& json, EncounterPhasePtr pPhase, EncounterConditionId conditionId )
  {
    EncounterTimepointCondition::from_json( json, pPhase, conditionId );

    auto params = json.at( "params" ).get< std::vector< uint32_t > >();

    this->directorVar = params[ 0 ];
    this->value = params[ 1 ];
  }

  bool EncounterTimeline::EncounterConditionDirectorVar::canExecute( EncounterFightPtr pFight, uint64_t time )
  {
    switch( m_conditionId )
    {
      case EncounterConditionId::DirectorVarEquals:
        return false; // pFight->getDirectorVar( directorVar ) == value;
      case EncounterConditionId::DirectorVarGreaterThan:
        return false; // pFight->getDirectorVar( directorVar ) > value;
    }
    return false;
  }

  EncounterTimeline::EncounterTimelineInfo EncounterTimeline::buildEncounterTimeline( uint32_t encounterId, bool reload )
  {
    static std::map< uint32_t, EncounterTimelineInfo > cache = {};
    const static std::map< std::string, EncounterTimepointDataType > timepointTypeMap =
    {
      { "idle",               EncounterTimepointDataType::Idle },
      { "castAction",         EncounterTimepointDataType::CastAction },
      { "moveTo",             EncounterTimepointDataType::MoveTo },
      { "logMessage",         EncounterTimepointDataType::LogMessage },
      { "setDirectorVar",     EncounterTimepointDataType::SetDirectorVar },
      { "addStatusEffect",    EncounterTimepointDataType::AddStatusEffect },
      { "removeStatusEffect", EncounterTimepointDataType::RemoveStatusEffect }
    };

    const static std::map< std::string, EncounterTimepointCallbackType > callbackTypeMap =
    {
      { "onActionInit",       EncounterTimepointCallbackType::OnActionInit },
      { "onActionStart",      EncounterTimepointCallbackType::OnActionStart },
      { "onActionInterrupt",  EncounterTimepointCallbackType::OnActionInterrupt },
      { "onActionExecute",    EncounterTimepointCallbackType::OnActionExecute },
    };

    const static std::map< std::string, EncounterConditionId > conditionIdMap =
    {
      { "hpPctLessThan",          EncounterConditionId::HpPctLessThan },
      { "hpPctBetween",           EncounterConditionId::HpPctBetween },
      { "directorVarEquals",      EncounterConditionId::DirectorVarEquals },
      { "directorVarGreaterThan", EncounterConditionId::DirectorVarGreaterThan },
    };

    EncounterTimelineInfo info;
    if( cache.find( encounterId ) != cache.end() && !reload )
      return cache.at( encounterId );
    /*
      array of states e.g.
      [
        pushStates:
        [
          {
            condition: "HpPctBetween", params:[ 20, 25 ], state: "phase1", loop: true
          },
          {
            condition: "RNGMinMax", params:[ 0, 10, 5 ], state: "phase1", loop: true
          }
        ],
        states:
        [
          {
            name: "idle",
            type: "idle",
            duration: 5000,
            overrideFlags: ["INVULNERABLE"],
            data: {}
          }
          {
            name: "phase1",
            type: "action",
            data: {
              actionId: 150,
              onFinish: {
                type: "addStatusEffect",
                data: {
                  selectFilter: "self",
                  statusEffectId: 70,
                  duration: 30000
                }
              }
            }
          }
        ]
      ]
          /*
  *
    class HpPercentCondition : EncounterTimepointCondition
    {
      EncounterTimepointConditionId m_type;
      std::vector< uint32_t > m_params
      
      HpPercentCondition( EncounterTimepointConditionId conditionId std::vector< uint32_t params ) : m_type( conditionId ), m_params( params ){}
      bool isConditionMet( uint32_t bossHpPct )
      {
        switch( m_type )
        {
          case EncounterTimepointConditionId::HpLessThanPct:
            return bossHpPct < m_params[0];
          case EncounterTimepointConditionId::HpBetweenPct:
            return bossHpPct >= m_params[0] && bossHpPct <= m_params[1];
        }
        return false;
      }
    }
    class RngCondition : EncounterTimepointCondition
    {
      EncounterTimepointConditionId m_type;
      std::vector< uint32_t > m_params
      
      RngCondition( EncounterTimepointConditionId conditionId std::vector< uint32_t params ) : m_type( conditionId ), m_params( params ){}
      bool isConditionMet( uint32_t shit )
      {
        switch( m_type )
        {
          case EncounterTimepointConditionId::RngMinMax:
            return RNGMgr::generate( params[0], params[1] ) == params[2];
        }
        return false;
      }
    }
    // Main encounter script
    EncounterFight::update()
    {
      auto pStateCondition = m_stateConditions.pop();
      
      switch( pStateCondition->getType() )
      {
        case EncounterTimepointConditionId::HpBetweenPct:
          if (((HpPercentCondition*)pStateCondition)->isConditionMet( bossHpPct ) )
            pStateCondition->execute( someDutyInstanceInfoHere );
          else if( !pStateCondition->hasExecuted() || pStateCondition->canLoop() )
            m_stateConditions.push( pStateCondition );
      }
    }

  */

    std::string encounter_name( fmt::format( std::string( "data/EncounterTimelines/EncounterTimeline%u.json" ), encounterId ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return {};

    auto json = nlohmann::json::parse( f );

    std::map< std::string, EncounterPhasePtr > phaseNameMap;


    for( const auto& phaseJ : json.at( "phases" ).items() )
    {
      auto phaseV = phaseJ.value();
      const auto id = phaseV.at( "id" ).get< uint32_t >();
      const auto& phaseName = phaseV.at( "name" ).get< std::string >();
      const auto& timepoints = phaseV.at( "timepoints" );

      EncounterPhasePtr pPhase = std::make_shared< EncounterPhase >();

      for( const auto& timepoint : timepoints.items() )
      {
       

        
      }

      if( phaseNameMap.find( phaseName ) != phaseNameMap.end() )
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - duplicate phase by name: %s" ), phaseName ) );

      phaseNameMap.emplace( std::make_pair( phaseName, pPhase ) );
    }
    for( const auto& pcJ : json.at( "phaseConditions" ).items() )
    {
      auto pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string>();
      auto description = pcV.at( "description" ).get< std::string >();
      auto loop = pcV.at( "loop" ).get< bool >();
      auto phaseRef = pcV.at( "phase" ).get< std::string >();

      EncounterPhasePtr pPhase;
      EncounterConditionId conditionId;

      // make sure condition exists
      if( auto it = conditionIdMap.find( conditionName ); it != conditionIdMap.end() )
        conditionId = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no condition id found by name: %s" ), conditionName ) );

      // make sure phase we're referencing exists
      if( auto it = phaseNameMap.find( phaseRef ); it != phaseNameMap.end() )
        pPhase = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no state found by name: %s" ), phaseRef ) );

      // build the condition
      EncounterTimepointConditionPtr pCondition;
      switch( conditionId )
      {
        case EncounterConditionId::HpPctLessThan:
        case EncounterConditionId::HpPctBetween:
        {
          auto pHpCondition = std::make_shared< EncounterConditionHp >();
          pHpCondition->from_json( pcV, pPhase, conditionId );
        }
        break;
        case EncounterConditionId::DirectorVarEquals:
        case EncounterConditionId::DirectorVarGreaterThan:
        {
          auto pDirectorCondition = std::make_shared< EncounterConditionDirectorVar >();
          pDirectorCondition->from_json( pcV, pPhase, conditionId );
        }
        break;
        default:
          break;
      }
      info.push( pCondition );
    }
    if( reload )
      cache[ encounterId ] = info;
    else
      cache.emplace( std::make_pair( encounterId, info ) );
    return info;
  }
}// namespace Sapphire