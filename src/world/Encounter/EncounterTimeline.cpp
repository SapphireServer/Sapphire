#include "EncounterFight.h"
#include "EncounterTimeline.h"

#include "../Actor/BNpc.h"
#include "../Actor/Chara.h"

namespace Sapphire
{
  void EncounterTimeline::ConditionHp::from_json( nlohmann::json& json, Phase phase, ConditionId conditionId )
  {
    TimepointCondition::from_json( json, phase, conditionId );

    auto params = json.at( "params" ).get< std::vector< uint32_t > >();

    this->actorId = params[ 0 ];

    if( conditionId == ConditionId::HpPctLessThan )
      this->hp.val = params[ 1 ];
    else
      this->hp.min = params[ 1 ], this->hp.max = params[ 2 ];
  }
  
  void EncounterTimeline::ConditionDirectorVar::from_json( nlohmann::json& json, Phase phase, ConditionId conditionId )
  {
    TimepointCondition::from_json( json, phase, conditionId );

    auto params = json.at( "params" ).get< std::vector< uint32_t > >();

    switch( conditionId )
    {
      case ConditionId::DirectorVarEquals:
      case ConditionId::DirectorVarGreaterThan:
      {
        param.var = params[ 0 ];
        param.value = params[ 1 ];
      }
      break;
      case ConditionId::DirectorFlagsEquals:
      case ConditionId::DirectorFlagsGreaterThan:
      {
        param.flag = params[ 0 ];
      }
      break;
      case ConditionId::DirectorSeqEquals:
      case ConditionId::DirectorSeqGreaterThan:
      {
        param.seq = params[ 0 ];
      }
      break;
      default:
        break;
    }
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

  bool EncounterTimeline::ConditionDirectorVar::canExecute( EncounterFightPtr pFight, uint64_t time )
  {
    auto pInstance = pFight->getInstance();

    // todo: use something other than InstanceContentPtr
    if( !pInstance )
      return false;

    switch( m_conditionId )
    {
      case ConditionId::DirectorVarEquals:
        return pInstance->getDirectorVar( param.var ) == param.value;
      case ConditionId::DirectorVarGreaterThan:
        return pInstance->getDirectorVar( param.var ) > param.value;
      case ConditionId::DirectorFlagsEquals:
        return pInstance->getFlags() == param.flag;
      case ConditionId::DirectorFlagsGreaterThan:
        return pInstance->getFlags() > param.flag;
      case ConditionId::DirectorSeqEquals:
        return pInstance->getSequence() == param.seq;
      case ConditionId::DirectorSeqGreaterThan:
        return pInstance->getSequence() > param.seq;
    }
    return false;
  }

  void EncounterTimeline::Timepoint::execute( EncounterFightPtr pFight, uint64_t time )
  {
    switch( m_type )
    {
      case TimepointDataType::Idle:
      {
        auto pIdleData = std::dynamic_pointer_cast< TimepointDataIdle, TimepointData >( getData() );
        auto pBNpc = pFight->getBNpc( pIdleData->m_actorId );

        if( pBNpc )
        {
          // todo: idle
        }
      }
      break;
      case TimepointDataType::CastAction:
      {
        auto pActionData = std::dynamic_pointer_cast< TimepointDataAction, TimepointData >( getData() );

        // todo: filter the correct target
        // todo: tie to mechanic script?
      }
      break;
      case TimepointDataType::MoveTo:
      {
        auto pMoveToData = std::dynamic_pointer_cast< TimepointDataMoveTo, TimepointData >( getData() );
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
        auto pDirectorData = std::dynamic_pointer_cast< TimepointDataDirector, TimepointData >( getData() );
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

  void EncounterTimeline::Timepoint::from_json( const nlohmann::json& json )
  {
    const static std::unordered_map< std::string, TimepointDataType > timepointTypeMap =
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

    const static std::unordered_map< std::string, TimepointOverrideFlags > overrideFlagMap =
    {
      {}
    };

    const static std::unordered_map< std::string, TargetSelectFilterId > targetFilterMap =
    {
      { "self",       TargetSelectFilterId::Self },
      { "tank",       TargetSelectFilterId::Tank },
      { "healer",     TargetSelectFilterId::Healer },
      { "dps",        TargetSelectFilterId::Dps },
      { "dpsMelee",   TargetSelectFilterId::DpsMelee },
      { "dpsRanged",  TargetSelectFilterId::DpsRanged },
      { "furthest",   TargetSelectFilterId::Furthest },
      { "aggro1",     TargetSelectFilterId::Aggro1 },
      { "aggro2",     TargetSelectFilterId::Aggro2 }
    };

    const static std::unordered_map< std::string, TimepointCallbackType > callbackTypeMap =
    {
      { "onActionInit",       TimepointCallbackType::OnActionInit },
      { "onActionStart",      TimepointCallbackType::OnActionStart },
      { "onActionInterrupt",  TimepointCallbackType::OnActionInterrupt },
      { "onActionExecute",    TimepointCallbackType::OnActionExecute },
    };

    TimepointDataType tpType{ 0 };

    auto typeStr = json.at( "type" ).get< std::string >();
    if( auto it = timepointTypeMap.find( typeStr ); it != timepointTypeMap.end() )
      tpType = it->second;
    else
      throw std::runtime_error( fmt::format( "Timepoint::from_json unable to find timepoint by type: %s", typeStr ) );

    m_duration = json.at( "duration" ).get< uint64_t >();
    //m_overrideFlags = json.at( "overrideFlags" ).get< TimepointOverrideFlags >();
    m_description = json.at( "description" ).get< std::string >();

    switch( tpType )
    {
      case TimepointDataType::MoveTo:
      {
        auto dataJ = json.at( "data" );
        auto posJ = dataJ.at( "pos" );
        auto x = posJ.at( "x" ).get< float >();
        auto y = posJ.at( "y" ).get< float >();
        auto z = posJ.at( "z" ).get< float >();
        auto rot = dataJ.at( "rot" ).get< float >();
        auto pathReq = dataJ.at( "pathRequested" ).get< bool >() ? MoveType::WalkPath : MoveType::Teleport;
        auto actorId = dataJ.at( "actorId" ).get< uint32_t >();

        m_pData = std::make_shared< TimepointDataMoveTo >( actorId, pathReq, x, y, z, rot );
      }
      break;
      default:
        break;
    }
  }
  EncounterTimeline::EncounterTimelineInfo EncounterTimeline::buildEncounterTimeline( uint32_t encounterId, bool reload )
  {
    static std::map< uint32_t, EncounterTimelineInfo > cache = {};
    const static std::unordered_map< std::string, ConditionId > conditionIdMap =
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

    std::map< std::string, Phase > phaseNameMap;


    for( const auto& phaseJ : json.at( "phases" ).items() )
    {
      auto phaseV = phaseJ.value();
      const auto id = phaseV.at( "id" ).get< uint32_t >();
      const auto& phaseName = phaseV.at( "name" ).get< std::string >();
      const auto& timepointsJ = phaseV.at( "timepoints" );

      Phase phase;
      for( const auto& timepointJ : timepointsJ.items() )
      {
        auto timepointV = timepointJ.value();
        Timepoint timepoint;
        timepoint.from_json( timepointV );

        phase.m_timepoints.push( timepoint );
      }

      if( phaseNameMap.find( phaseName ) != phaseNameMap.end() )
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - duplicate phase by name: %s" ), phaseName ) );

      phaseNameMap.emplace( std::make_pair( phaseName, phase ) );
    }
    for( const auto& pcJ : json.at( "phaseConditions" ).items() )
    {
      auto pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string>();
      auto description = pcV.at( "description" ).get< std::string >();
      auto loop = pcV.at( "loop" ).get< bool >();
      auto phaseRef = pcV.at( "phase" ).get< std::string >();

      ConditionId conditionId;
      
      // make sure condition exists
      if( auto it = conditionIdMap.find( conditionName ); it != conditionIdMap.end() )
        conditionId = it->second;
      else
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no condition id found by name: %s" ), conditionName ) );

      // make sure phase we're referencing exists
      if( auto phaseIt = phaseNameMap.find( phaseRef ); phaseIt != phaseNameMap.end() )
      {
        Phase& phase = phaseIt->second;

        // build the condition
        TimepointConditionPtr pCondition;
        switch( conditionId )
        {
          case ConditionId::HpPctLessThan:
          case ConditionId::HpPctBetween:
          {
            auto pHpCondition = std::make_shared< ConditionHp >();
            pHpCondition->from_json( pcV, phase, conditionId );
          }
          break;
          case ConditionId::DirectorVarEquals:
          case ConditionId::DirectorVarGreaterThan:
          {
            auto pDirectorCondition = std::make_shared< ConditionDirectorVar >();
            pDirectorCondition->from_json( pcV, phase, conditionId );
          }
          break;
          default:
            break;
        }
        info.push( pCondition );
      }
      else
      {
        throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::buildEncounterTimeline - no state found by name: %s" ), phaseRef ) );
      }
    }
    if( reload )
      cache[ encounterId ] = info;
    else
      cache.emplace( std::make_pair( encounterId, info ) );
    return info;
  }
}// namespace Sapphire