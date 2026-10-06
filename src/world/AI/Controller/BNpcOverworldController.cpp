#include "BNpcOverworldController.h"

#include <Territory/Territory.h>
#include <Manager/TerritoryMgr.h>

#include <AI/Fsm/State.h>
#include <AI/Fsm/StateCombat.h>
#include <AI/Fsm/StateFollowPath.h>
#include <AI/Fsm/StateResumePath.h>
#include <AI/Fsm/StateRetreat.h>
#include <AI/Fsm/StateIdle.h>
#include <AI/Fsm/StateRoam.h>
#include <AI/Fsm/StateDead.h>

#include <AI/GambitPack.h>

#include <Actor/BNpc.h>

#include <Logging/Logger.h>

namespace Sapphire::World::AI::Controller
{
  BNpcOverworldController::BNpcOverworldController( Entity::BNpc& bnpc ) :
    Controller( bnpc )
  {
  }

  void BNpcOverworldController::initialize()
  {
    Controller::initialize();

    using namespace AI::Fsm;

    auto pBNpc = m_owner.getAsBNpc();
    auto pBNpcInfo = pBNpc->getInstanceObjectInfo();
    auto& bnpc = *pBNpc;

    auto stateIdle = make_StateIdle();
    auto stateCombat = make_StateCombat();
    auto stateDead = make_StateDead();

    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
    auto pZone = teriMgr.getTerritoryByGuId( pBNpc->getTerritoryId() );
    if( pBNpcInfo->ServerPathId != 0 && pZone && pZone->getServerPath( pBNpcInfo->ServerPathId ) )
    {
      auto statePath = make_StateFollowPath();
      auto stateResumePath = make_StateResumePath();
      statePath->addTransition( stateCombat, make_HateListHasEntriesCondition() );
      statePath->addTransition( stateDead, make_IsDeadCondition() );

      stateCombat->addTransition( stateDead, make_IsDeadCondition() );
      stateCombat->addTransition( stateResumePath, make_HateListEmptyCondition() );
      stateResumePath->addTransition( statePath, make_RoamTargetReachedCondition() );

      m_stateMachine.addState( statePath );

      m_stateMachine.setCurrentState( statePath );

      auto pServerPath = pZone->getServerPath( pBNpcInfo->ServerPathId );
      if( pServerPath )
      {
        std::vector< Common::Vector3 > points;
        for( const auto& p : pServerPath->points )
          points.push_back( { pServerPath->position.x + p.Translation.x,
                              pServerPath->position.y + p.Translation.y,
                              pServerPath->position.z + p.Translation.z } );

        m_path.reset();

        m_path.m_type = PathType::ServerPath;
        m_path.m_flags = PathFlags::CanReversePath;
        m_path.m_active = true;
        m_path.m_points = points;
        m_path.m_serverPathId = pBNpcInfo->ServerPathId;

        m_path.m_defaultServerPathId = m_path.m_serverPathId;
        m_path.m_defaultType = m_path.m_type;
        m_path.m_defaultFlags = m_path.m_flags;
      }

      Logger::info( "Setting server path {} for BNpc {} Teri {} Pos {} {} {}", pBNpcInfo->ServerPathId, bnpc.getId(), bnpc.getTerritoryId(), bnpc.getPos().x, bnpc.getPos().y, bnpc.getPos().z );
    }
    else
    {
      if( !pBNpc->hasFlag( Entity::BNpcFlag::Immobile ) && !pBNpc->hasFlag( Entity::BNpcFlag::NoRoam ) )
      {
        auto stateRoam = make_StateRoam();
        stateIdle->addTransition( stateRoam, make_RoamNextTimeReachedCondition() );
        stateRoam->addTransition( stateIdle, make_RoamTargetReachedCondition() );
        stateRoam->addTransition( stateCombat, make_HateListHasEntriesCondition() );
        stateRoam->addTransition( stateDead, make_IsDeadCondition() );

        m_stateMachine.addState( stateRoam );
      }
      stateIdle->addTransition( stateCombat, make_HateListHasEntriesCondition() );
      //stateCombat->addTransition( stateIdle, make_HateListEmptyCondition() );
      stateIdle->addTransition( stateDead, make_IsDeadCondition() );
      stateCombat->addTransition( stateDead, make_IsDeadCondition() );

      m_stateMachine.addState( stateIdle );

      if( !pBNpc->hasFlag( Entity::BNpcFlag::NoDeaggro ) )
      {
        auto stateRetreat = make_StateRetreat();
        stateCombat->addTransition( stateRetreat, make_SpawnPointDistanceGtMaxDistanceCondition() );
        stateCombat->addTransition( stateRetreat, make_HateListEmptyCondition() );
        stateRetreat->addTransition( stateIdle, make_RoamTargetReachedCondition() );
      }
      m_stateMachine.setCurrentState( stateIdle );
    }
  }

  void BNpcOverworldController::update( uint64_t tick )
  {
    // todo: handle gambits here instead of BNpc::processGambits called by StateCombat?
    /*
    if( m_pGambitPack )
      m_pGambitPack->update( *m_owner.getAsBNpc(), tick );
    */
    m_owner.getAsBNpc()->checkAggro();
    Controller::update( tick );
  }

  bool BNpcOverworldController::tryAggro( uint32_t targetId )
  {
    // todo:
    return false;
  }

  void BNpcOverworldController::aggro( uint32_t targetId, uint32_t hateAmount )
  {
    // todo:
  }

  void BNpcOverworldController::autoAttack( uint32_t targetId )
  {
    // todo:
  }

  void BNpcOverworldController::rangedAutoAttack( uint32_t targetId )
  {
    // todo:
  }

  void BNpcOverworldController::deaggro()
  {
    // todo:
  }

  void BNpcOverworldController::clearEnmityList()
  {
    // todo:
  }

  void BNpcOverworldController::pathTo( const Common::Vector3& pos, float targetReachedDist, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    // todo:
    Controller::pathTo( pos, targetReachedDist, flags, onReachPoint, onReachDestination );
  }

  void BNpcOverworldController::followPath( const std::vector< Common::Vector3 >& path, PathFlags flags, const std::function< void( Common::Vector3 ) >& onReachPoint, const std::function< void() >& onReachDestination )
  {
    // todo:
    Controller::followPath( path, flags, onReachPoint, onReachDestination );
  }

  void BNpcOverworldController::followTarget( uint32_t targetId, bool followDuringCombat )
  {
    Controller::followTarget( targetId, followDuringCombat );
  }

}
