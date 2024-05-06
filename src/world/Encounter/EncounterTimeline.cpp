#include "EncounterFight.h"
#include "EncounterTimeline.h"

#include "../Actor/BNpc.h"
#include "../Actor/Chara.h"

namespace Sapphire
{
  void EncounterTimeline::ConditionHp::from_json( nlohmann::json& json, PhasePtr pPhase, ConditionId conditionId )
  {
    TimepointCondition::from_json( json, pPhase, conditionId );

    auto params = json.at( "params" ).get< std::vector< uint32_t > >();

    this->actorId = params[ 0 ];

    if( conditionId == ConditionId::HpPctLessThan )
      this->hp.val = params[ 1 ];
    else
      this->hp.min = params[ 1 ], this->hp.max = params[ 2 ];
  }

  bool EncounterTimeline::ConditionHp::canExecute( EncounterFightPtr pFight, uint64_t time )
  {
    auto pBNpc = pFight->getBNpc( actorId );
    if( !pBNpc )
      return false;

    // todo: check time elapsed

    switch( m_conditionId )
    {
      case ConditionId::HpPctLessThan:
        return pBNpc->getHpPercent() < hp.val;
      case ConditionId::HpPctBetween:
      {
        auto hpPct = pBNpc->getHpPercent();
        return hpPct >= hp.min && hpPct <= hp.max;
      }
    }
    return false;
  };

  void EncounterTimeline::ConditionDirectorVar::from_json( nlohmann::json& json, PhasePtr pPhase, ConditionId conditionId )
  {
    TimepointCondition::from_json( json, pPhase, conditionId );

    auto params = json.at( "params" ).get< std::vector< uint32_t > >();

    this->directorVar = params[ 0 ];
    this->value = params[ 1 ];
  }

  bool EncounterTimeline::ConditionDirectorVar::canExecute( EncounterFightPtr pFight, uint64_t time )
  {
    auto pInstance = pFight->getInstance();

    // todo: use something other than InstanceContentPtr
    if( !pInstance )
      return false;

    switch( m_conditionId )
    {
      case ConditionId::DirectorVarEquals:
        return pInstance->getDirectorVar( directorVar ) == value;
      case ConditionId::DirectorVarGreaterThan:
        return pInstance->getDirectorVar( directorVar ) > value;
    }
    return false;
  }

  void EncounterTimeline::Timepoint::execute( EncounterFightPtr pFight, uint64_t time )
  {
    switch( m_type )
    {
      case TimepointDataType::Idle:
      {
        auto pIdleData = std::dynamic_pointer_cast< TimepointDataIdle, TimepointData >( m_pData );
        auto pBNpc = pFight->getBNpc( pIdleData->m_actorId );

        if( pBNpc )
        {
          // todo: idle
        }
      }
      break;
      case TimepointDataType::CastAction:
      {
        auto pActionData = std::dynamic_pointer_cast< TimepointDataAction, TimepointData >( m_pData );

        // todo: filter the correct target
        // todo: tie to mechanic script?
      }
      break;
      case TimepointDataType::MoveTo:
      {
        auto pMoveToData = std::dynamic_pointer_cast< TimepointDataMoveTo, TimepointData >( m_pData );
        auto pBNpc = pFight->getBNpc( pMoveToData->m_actorId );

        // todo: path
        if( pBNpc )
        {
          pBNpc->setPos( pMoveToData->m_x, pMoveToData->m_y, pMoveToData->m_z );
          pBNpc->setRot( pMoveToData->m_rot );
          pBNpc->sendPositionUpdate();
        }
      }
      break;
      case TimepointDataType::BattleTalk:
      {
        // auto pBattleTalkData = std::dynamic_pointer_cast< TimepointDataBattleTalk, TimepointData >();
      }
      break;
      case TimepointDataType::SetDirectorSeq:
      case TimepointDataType::SetDirectorVar:
      case TimepointDataType::SetDirectorFlag:
      {
        auto pDirectorData = std::dynamic_pointer_cast< TimepointDataDirector, TimepointData >( m_pData );
        auto pInstance = pFight->getInstance();

        // todo: this should never not be set?
        // todo: probably should use ContentDirector 
        if( pInstance )
        {
          switch( pDirectorData->m_directorOp )
          {
            case DirectorOpId::SetDirectorVar:
              pInstance->setDirectorVar( pDirectorData->m_data.index, pDirectorData->m_data.value.val );
              break;
            case DirectorOpId::SetDirectorVarLR:
              pInstance->setDirectorVar( pDirectorData->m_data.index, pDirectorData->m_data.value.left, pDirectorData->m_data.value.right );
              break;
            case DirectorOpId::SetDirectorFlag:
              pInstance->setDirectorFlags( pDirectorData->m_data.flags );
              break;
            case DirectorOpId::SetDirectorSeq:
              pInstance->setDirectorSequence( pDirectorData->m_data.seq );
              break;
            case DirectorOpId::ClearDirectorFlag:
              break;
            default:
              // probably throw an error here
              break;
          }
        }
      }
      break;
    }
  }

  EncounterTimeline::EncounterTimelineInfo EncounterTimeline::buildEncounterTimeline( uint32_t encounterId, bool reload )
  {
    static std::map< uint32_t, EncounterTimelineInfo > cache = {};
    const static std::map< std::string, TimepointDataType > timepointTypeMap =
    {
      { "idle",               TimepointDataType::Idle },
      { "castAction",         TimepointDataType::CastAction },
      { "moveTo",             TimepointDataType::MoveTo },
      { "logMessage",         TimepointDataType::LogMessage },
      { "setDirectorVar",     TimepointDataType::SetDirectorVar },
      { "setDirectorSeq",     TimepointDataType::SetDirectorSeq },
      { "setDirectorFlags",   TimepointDataType::SetDirectorFlag },
      { "addStatusEffect",    TimepointDataType::AddStatusEffect },
      { "removeStatusEffect", TimepointDataType::RemoveStatusEffect }
    };

    const static std::map< std::string, TimepointCallbackType > callbackTypeMap =
    {
      { "onActionInit",       TimepointCallbackType::OnActionInit },
      { "onActionStart",      TimepointCallbackType::OnActionStart },
      { "onActionInterrupt",  TimepointCallbackType::OnActionInterrupt },
      { "onActionExecute",    TimepointCallbackType::OnActionExecute },
    };

    const static std::map< std::string, ConditionId > conditionIdMap =
    {
      { "hpPctLessThan",          ConditionId::HpPctLessThan },
      { "hpPctBetween",           ConditionId::HpPctBetween },
      { "directorVarEquals",      ConditionId::DirectorVarEquals },
      { "directorVarGreaterThan", ConditionId::DirectorVarGreaterThan },
      { "encounterTimeElapsed",   ConditionId::EncounterTimeElapsed },
      { "phaseTimeElapsed",       ConditionId::PhaseTimeElapsed }
    };

    EncounterTimelineInfo info;
    if( cache.find( encounterId ) != cache.end() && !reload )
      return cache.at( encounterId );
    /*
    class RngCondition : TimepointCondition
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

    std::map< std::string, PhasePtr > phaseNameMap;


    for( const auto& phaseJ : json.at( "phases" ).items() )
    {
      auto phaseV = phaseJ.value();
      const auto id = phaseV.at( "id" ).get< uint32_t >();
      const auto& phaseName = phaseV.at( "name" ).get< std::string >();
      const auto& timepoints = phaseV.at( "timepoints" );

      PhasePtr pPhase = std::make_shared< Phase >();

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

      PhasePtr pPhase;
      ConditionId conditionId;

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
      TimepointConditionPtr pCondition;
      switch( conditionId )
      {
        case ConditionId::HpPctLessThan:
        case ConditionId::HpPctBetween:
        {
          auto pHpCondition = std::make_shared< ConditionHp >();
          pHpCondition->from_json( pcV, pPhase, conditionId );
        }
        break;
        case ConditionId::DirectorVarEquals:
        case ConditionId::DirectorVarGreaterThan:
        {
          auto pDirectorCondition = std::make_shared< ConditionDirectorVar >();
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