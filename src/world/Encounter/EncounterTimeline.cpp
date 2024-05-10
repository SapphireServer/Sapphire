#include "EncounterFight.h"
#include "EncounterTimeline.h"

#include <Actor/BNpc.h>
#include <Actor/Chara.h>
#include <Actor/EventObject.h>

#include <Util/UtilMath.h>

namespace Sapphire
{
  bool EncounterTimeline::ConditionHp::isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
  {
    auto pBNpc = pInstance->getActiveBNpcByLayoutId( layoutId );
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

  bool EncounterTimeline::ConditionDirectorVar::isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
  {
    // todo: use something other than InstanceContentPtr
    if( !pInstance )
      return false;

    switch( m_conditionId )
    {
      case ConditionId::DirectorVarEquals:
        return pInstance->getDirectorVar( param.index ) == param.value;
      case ConditionId::DirectorVarGreaterThan:
        return pInstance->getDirectorVar( param.index ) > param.value;
      case ConditionId::DirectorFlagsEquals:
        return pInstance->getFlags() == param.flags;
      case ConditionId::DirectorFlagsGreaterThan:
        return pInstance->getFlags() > param.flags;
      case ConditionId::DirectorSeqEquals:
        return pInstance->getSequence() == param.seq;
      case ConditionId::DirectorSeqGreaterThan:
        return pInstance->getSequence() > param.seq;
    }
    return false;
  }

  bool EncounterTimeline::ConditionCombatState::isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
  {
    auto pBattleNpc = pInstance->getActiveBNpcByLayoutId( this->layoutId );

    switch( combatState )
    {
      case CombatStateType::Idle:
        return pBattleNpc->getState() == Entity::BNpcState::Idle;
      case CombatStateType::Combat:
        return pBattleNpc->getState() == Entity::BNpcState::Combat;
      case CombatStateType::Retreat:
        return pBattleNpc->getState() == Entity::BNpcState::Retreat;
      case CombatStateType::Roaming:
        return pBattleNpc->getState() == Entity::BNpcState::Roaming;
      case CombatStateType::JustDied:
        return pBattleNpc->getState() == Entity::BNpcState::JustDied;
      case CombatStateType::Dead:
        return pBattleNpc->getState() == Entity::BNpcState::Dead;
      default:
        break;
    }
    return false;
  }

  bool EncounterTimeline::ConditionEncounterTimeElapsed::isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
  {
    auto elapsed = time - pack.getStartTime();
    // todo: check encounter time
    return elapsed >= this->duration;
  }

  bool EncounterTimeline::ConditionBNpcFlags::isConditionMet( ConditionState& state, InstanceContentPtr pInstance, TimelinePack& pack, uint64_t time ) const
  {
    auto pBNpc = pInstance->getActiveBNpcByLayoutId( this->layoutId );
    return pBNpc && pBNpc->hasFlag( this->flags );
  }

  void EncounterTimeline::Timepoint::update( TimepointState& state, InstanceContentPtr pInstance, uint64_t time ) const
  {
    state.m_lastTick = time;
    switch( m_type )
    {
      case TimepointDataType::Idle:
      {
        auto pIdleData = std::dynamic_pointer_cast< TimepointDataIdle, TimepointData >( getData() );
        auto pBNpc = pInstance->getActiveBNpcByLayoutId( pIdleData->m_layoutId );

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
        auto pBNpc = pInstance->getActiveBNpcByLayoutId( pMoveToData->m_layoutId );

        if( pBNpc )
        {
          auto currPos = pBNpc->getPos();
          Common::FFXIVARR_POSITION3 targetPos = { pMoveToData->m_x, pMoveToData->m_y, pMoveToData->m_z };

          auto distance = Common::Util::distance( currPos, targetPos );
          if( distance > 0.5f )
          {
            if( pMoveToData->m_moveType == MoveType::WalkPath )
              pBNpc->moveTo( targetPos );
            else
              pBNpc->setPos( pMoveToData->m_x, pMoveToData->m_y, pMoveToData->m_z );
          }
          else
          {
            // if we are at the pos, stop waiting
            state.m_finished = true;
          }
          pBNpc->setRot( pMoveToData->m_rot );
        }
      }
      break;
      case TimepointDataType::LogMessage:
      {
        // todo: LogMessage
      }
      break;
      case TimepointDataType::BattleTalk:
      {
        // todo: BattleTalk
        // auto pBattleTalkData = std::dynamic_pointer_cast< TimepointDataBattleTalk, TimepointData >();
      }
      break;
      case TimepointDataType::SetDirectorSeq:
      case TimepointDataType::SetDirectorVar:
      case TimepointDataType::SetDirectorVarLR:
      case TimepointDataType::SetDirectorFlag:
      {
        auto pDirectorData = std::dynamic_pointer_cast< TimepointDataDirector, TimepointData >( getData() );
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
            case DirectorOpId::ClearDirector:
            {
              for( auto playerId : pInstance->getSpawnedPlayerIds() )
              {
                // todo: get all players, clear director vars/flags to default(?)
              }
            }
            break;
            default:
              // probably throw an error here
              break;
          }
        }
      }
      break;
      case TimepointDataType::AddStatusEffect:
      {
        // todo:
      }
      break;
      case TimepointDataType::RemoveStatusEffect:
      {

      }
      break;
      case TimepointDataType::SetBNpcFlags:
      {
        auto pBNpcFlagData = std::dynamic_pointer_cast< TimepointDataBNpcFlags, TimepointData >( getData() );
        auto pBNpc = pInstance->getActiveBNpcByLayoutId( pBNpcFlagData->m_layoutId );

        if( pBNpc )
        {
          pBNpc->clearFlags();
          pBNpc->setFlag( pBNpcFlagData->m_flags );
        }
      }
      break;
      case TimepointDataType::SetEObjState:
      {
        auto pEObjData = std::dynamic_pointer_cast< TimepointDataEObjState, TimepointData >( getData() );
        auto pEObj = pInstance->getEObjById( pEObjData->m_eobjId );

        if( pEObj )
        {
          pEObj->setState( pEObjData->m_state );
        }
      }
      break;
      case TimepointDataType::SetBgm:
      {
        auto pBgmData = std::dynamic_pointer_cast< TimepointDataBGM, TimepointData >( getData() );
        pInstance->setCurrentBGM( pBgmData->m_bgmId );
      }
      break;
    }
    state.m_finished = state.m_finished || state.m_startTime + m_duration <= time;
  }

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

  void EncounterTimeline::Timepoint::execute( InstanceContentPtr pInstance, uint64_t time )
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

  void EncounterTimeline::Timepoint::execute( TimepointState& state, InstanceContentPtr pInstance, uint64_t time ) const
  {
    state.m_startTime = time;
    update( state, pInstance, time );
  }

  //
  // parsing stuff below
  //

  void EncounterTimeline::ConditionHp::from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId,
    const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, conditionId );

    auto paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose hp we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionHp::from_json unable to find actor by name: %s" ), actorRef ) );

    switch( conditionId )
    {
      case ConditionId::HpPctLessThan:
        this->hp.val = paramData.at( "hp" ).get< uint32_t >();
        break;
      case ConditionId::HpPctBetween:
        this->hp.min = paramData.at( "hpMin" ).get< uint32_t >(),
        this->hp.max = paramData.at( "hpMax" ).get< uint32_t >();
        break;
      default:
        break;
    }
  }

  void EncounterTimeline::ConditionDirectorVar::from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId )
  {
    PhaseCondition::from_json( json, phase, conditionId );

    auto paramData = json.at( "paramData" );

    switch( conditionId )
    {
      case ConditionId::DirectorVarEquals:
      case ConditionId::DirectorVarGreaterThan:
      {
        param.index = paramData.at( "index" ).get< uint32_t >();
        param.value = paramData.at( "value" ).get< uint32_t >();
      }
      break;
      case ConditionId::DirectorFlagsEquals:
      case ConditionId::DirectorFlagsGreaterThan:
      {
        param.flags = paramData.at( "flags" ).get< uint32_t >();
      }
      break;
      case ConditionId::DirectorSeqEquals:
      case ConditionId::DirectorSeqGreaterThan:
      {
        param.seq = paramData.at( "seq" ).get< uint32_t >();
      }
      break;
      default:
        break;
    }
  }

  void EncounterTimeline::ConditionCombatState::from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId,
    const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, conditionId );

    auto paramData = json.at( "paramData" );
    auto actorRef = paramData.at( "sourceActor" ).get< std::string >();

    // resolve the actor whose name we are checking
    if( auto it = actors.find( actorRef ); it != actors.end() )
      this->layoutId = it->second.m_layoutId;
    else
      throw std::runtime_error( fmt::format( std::string( "EncounterTimeline::ConditionCombatState::from_json unable to find actor by name: %s" ), actorRef ) );

    this->combatState = paramData.at( "combatState" ).get< CombatStateType >();
  }

  void EncounterTimeline::ConditionEncounterTimeElapsed::from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId )
  {
    PhaseCondition::from_json( json, phase, conditionId );

    auto paramData = json.at( "paramData" );
    auto duration = paramData.at( "duration" ).get< uint64_t >();

    this->duration = duration;
  }

  void EncounterTimeline::ConditionBNpcFlags::from_json( nlohmann::json& json, Phase& phase, ConditionId conditionId,
                                                           const std::unordered_map< std::string, TimelineActor >& actors )
  {
    PhaseCondition::from_json( json, phase, conditionId );
    // todo: BNpcHasFlags
  }

  void EncounterTimeline::Timepoint::from_json( const nlohmann::json& json, const std::unordered_map< std::string, TimelineActor>& actors, uint32_t selfLayoutId )
  {
    const static std::unordered_map< std::string, TimepointDataType > timepointTypeMap =
    {
      { "idle",               TimepointDataType::Idle },
      { "castAction",         TimepointDataType::CastAction },
      { "moveTo",             TimepointDataType::MoveTo },
      { "logMessage",         TimepointDataType::LogMessage },
      { "battleTalk",         TimepointDataType::BattleTalk  },
      { "setDirectorVar",     TimepointDataType::SetDirectorVar },
      { "setDirectorSeq",     TimepointDataType::SetDirectorSeq },
      { "setDirectorFlags",   TimepointDataType::SetDirectorFlag },
      { "addStatusEffect",    TimepointDataType::AddStatusEffect },
      { "removeStatusEffect", TimepointDataType::RemoveStatusEffect },
      { "setBNpcFlags",       TimepointDataType::SetBNpcFlags },
      { "setEObjState",       TimepointDataType::SetEObjState }
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
      case TimepointDataType::Idle:
      {
        auto duration = json.at( "duration" ).get< uint32_t >();
        m_pData = std::make_shared< TimepointDataIdle >( selfLayoutId, duration );
      }
      break;
      case TimepointDataType::CastAction:
      {
        // todo: CastAction
        // todo: parse and build callback funcs
        auto dataJ = json.at( "data" );

      }
      break;
      case TimepointDataType::MoveTo:
      {
        auto dataJ = json.at( "data" );
        auto posJ = dataJ.at( "pos" );
        auto x = posJ.at( "x" ).get< float >();
        auto y = posJ.at( "y" ).get< float >();
        auto z = posJ.at( "z" ).get< float >();
        auto rot = dataJ.at( "rot" ).get< float >();
        auto pathReq = dataJ.at( "pathRequested" ).get< bool >() ? MoveType::WalkPath : MoveType::Teleport;
        
        m_pData = std::make_shared< TimepointDataMoveTo >( selfLayoutId, pathReq, x, y, z, rot );
      }
      break;
      case TimepointDataType::LogMessage:
      {
        auto dataJ = json.at( "data" );
        auto messageId = dataJ.at( "messageId" ).get< uint32_t >();
        auto params = dataJ.at( "params" ).get< std::vector< uint32_t > >();

        m_pData = std::make_shared< TimepointDataLogMessage >( messageId, params );
      }
      break;
      case TimepointDataType::BattleTalk:
      {
        auto dataJ = json.at( "data" );

        // todo: BattleTalk
      }
      break;

      //
      // Directors
      //
      case TimepointDataType::SetDirectorVar:
      {
        auto dataJ = json.at( "data" );
        auto index = dataJ.at( "index" ).get< uint32_t >();
        auto val = dataJ.at( "value" ).get< uint32_t >();

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType );
        pDirectorData->m_directorOp = DirectorOpId::SetDirectorVar;
        pDirectorData->m_data.index = index;
        pDirectorData->m_data.value.val = val;

        m_pData = pDirectorData;
      }
      break;
      case TimepointDataType::SetDirectorVarLR:
      {
        auto dataJ = json.at( "data" );
        auto index = dataJ.at( "index" ).get< uint32_t >();
        auto left = dataJ.at( "left" ).get< uint32_t >();
        auto right = dataJ.at( "right" ).get< uint32_t >();

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType );
        pDirectorData->m_directorOp = DirectorOpId::SetDirectorVarLR;
        pDirectorData->m_data.index = index;
        pDirectorData->m_data.value.left = left;
        pDirectorData->m_data.value.right = right;

        m_pData = pDirectorData;
      }
      break;
      case TimepointDataType::SetDirectorSeq:
      {
        auto dataJ = json.at( "data" );
        auto seq = dataJ.at( "seq" ).get< uint32_t >();

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType );
        pDirectorData->m_directorOp = DirectorOpId::SetDirectorSeq;
        pDirectorData->m_data.seq = seq;

        m_pData = pDirectorData;
      }
      break;
      case TimepointDataType::SetDirectorFlag:
      {
        auto dataJ = json.at( "data" );
        auto flags = dataJ.at( "flags" ).get< uint32_t >();

        auto pDirectorData = std::make_shared< TimepointDataDirector >( tpType );
        pDirectorData->m_directorOp = DirectorOpId::SetDirectorFlag;
        pDirectorData->m_data.flags = flags;

        m_pData = pDirectorData;
      }
      break;

      //
      // Status Effects
      //
      case TimepointDataType::AddStatusEffect:
      case TimepointDataType::RemoveStatusEffect:
      {
        // todo: add/remove status effects
      }
      break;


      case TimepointDataType::SetBNpcFlags:
      {
        auto dataJ = json.at( "data" );

        // todo: SetBNpcFlags
      }
      break;

      case TimepointDataType::SetEObjState:
      {
        auto dataJ = json.at( "data" );

        // todo: SetEObjState
      }
      default:
        break;
    }
  }

  EncounterTimeline::TimelinePack EncounterTimeline::buildEncounterTimeline( uint32_t encounterId, bool reload )
  {
    static std::map< uint32_t, TimelinePack > cache = {};
    const static std::unordered_map< std::string, ConditionId > conditionIdMap =
    {
      { "hpPctLessThan",            ConditionId::HpPctLessThan },
      { "hpPctBetween",             ConditionId::HpPctBetween },

      { "directorVarEquals",        ConditionId::DirectorVarEquals },
      { "directorVarGreaterThan",   ConditionId::DirectorVarGreaterThan },

      { "directorSeqEquals",        ConditionId::DirectorSeqEquals },
      { "directorSeqGreaterThan",   ConditionId::DirectorSeqGreaterThan },

      { "directorFlagsEquals",      ConditionId::DirectorFlagsEquals },
      { "directorFlagsGreaterThan", ConditionId::DirectorFlagsGreaterThan },

      { "encounterTimeElapsed",     ConditionId::EncounterTimeElapsed },

      { "combatState",              ConditionId::CombatState },
      { "bnpcHasFlags",             ConditionId::BNpcHasFlags }
    };

    TimelinePack pack;
    if( cache.find( encounterId ) != cache.end() && !reload )
      return cache.at( encounterId );

    std::string encounter_name( fmt::format( std::string( "data/EncounterTimelines/EncounterTimeline%u.json" ), encounterId ) );

    std::fstream f( encounter_name );

    if( !f.is_open() )
      return pack;

    auto json = nlohmann::json::parse( f );

    std::unordered_map< std::string, TimelineActor > actorNameMap;
    std::unordered_map< std::string, std::map< std::string, Phase > > actorNamePhaseMap;

    // first run through cache actor info
    for( const auto& actorJ : json.at( "actors" ).items() )
    {
      TimelineActor actor;
      auto actorV = actorJ.value();
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
        auto phaseV = phaseJ.value();
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
    for( const auto& pcJ : json.at( "phaseConditions" ).items() )
    {
      auto pcV = pcJ.value();
      auto conditionName = pcV.at( "condition" ).get< std::string >();
      auto description = pcV.at( "description" ).get< std::string >();
      auto loop = pcV.at( "loop" ).get< bool >();
      auto phaseRef = pcV.at( "targetPhase" ).get< std::string >();
      auto actorRef = pcV.at( "targetActor" ).get< std::string >();

      ConditionId conditionId;

      // make sure condition exists
      if( auto it = conditionIdMap.find( conditionName ); it != conditionIdMap.end() )
        conditionId = it->second;
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
          switch( conditionId )
          {
            case ConditionId::HpPctLessThan:
            case ConditionId::HpPctBetween:
            {
              auto pHpCondition = std::make_shared< ConditionHp >();
              pHpCondition->from_json( pcV, phase, conditionId, actorNameMap );
            }
            break;
            case ConditionId::DirectorVarEquals:
            case ConditionId::DirectorVarGreaterThan:
            case ConditionId::DirectorFlagsEquals:
            case ConditionId::DirectorFlagsGreaterThan:
            case ConditionId::DirectorSeqEquals:
            case ConditionId::DirectorSeqGreaterThan:
            {
              auto pDirectorCondition = std::make_shared< ConditionDirectorVar >();
              pDirectorCondition->from_json( pcV, phase, conditionId );
            }
            break;
            case ConditionId::EncounterTimeElapsed:
            {
              auto pEncounterCondition = std::make_shared< ConditionEncounterTimeElapsed >();
              pEncounterCondition->from_json( pcV, phase, conditionId );
            }
            break;
            case ConditionId::CombatState:
            {
              auto pCombatStateCondition = std::make_shared< ConditionCombatState >();
              pCombatStateCondition->from_json( pcV, phase, conditionId, actorNameMap );
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
    if( reload )
      cache[ encounterId ] = pack;
    else
      cache.emplace( std::make_pair( encounterId, pack ) );
    return pack;
  }
}// namespace Sapphire