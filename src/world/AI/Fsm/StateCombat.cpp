#include "StateCombat.h"
#include "Actor/BNpc.h"
#include "Actor/Player.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Util/UtilMath.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/PlayerMgr.h>
#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateCombat::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  if( !pZone )
  {
    Logger::debug( "Territory not found for BNPC" );
    return;
  }
  auto pNaviProvider = pZone->getNaviProvider();
  bool hasQueuedAction = bnpc.hasAction();

  if( hasQueuedAction )
    return;

  auto pHatedActor = bnpc.hateListGetHighest();
  if( !pHatedActor )
    return;

  if( pNaviProvider && bnpc.pathingActive() )
  {
    auto state = bnpc.getState();
    bool isRunning = state == Entity::BNpcState::Retreat || state == Entity::BNpcState::Combat;
    pNaviProvider->updateAgentParameters( bnpc.getAgentId(), bnpc.getRadius(), isRunning, isRunning ? bnpc.getRunSpeed() : bnpc.getWalkSpeed() );
  }

  auto distanceOrig = Common::Util::distance( bnpc.getPos(), bnpc.getSpawnPos() );

  if( !pHatedActor->isAlive() || bnpc.getTerritoryId() != pHatedActor->getTerritoryId() )
  {
    bnpc.deaggro( pHatedActor );
    pHatedActor = bnpc.hateListGetHighest();
  }

  if( !pHatedActor )
    return;

  auto distance = Common::Util::distance( bnpc.getPos(), pHatedActor->getPos() );

  // All possibilities to automatically lose aggro go here
  // todo: use status flags here instead of bnpc flags?
  if( !bnpc.hasFlag( Entity::NoDeaggro ) )
  {
    if( bnpc.hasFlag( Entity::Immobile ) && distance > 40.0f )
    {
      bnpc.deaggro( pHatedActor );
    }
    else if( distance > 80.0f )
    {
      bnpc.deaggro( pHatedActor );
    }
  }
  if( bnpc.getBoundEncounterId() != pHatedActor->getBoundEncounterId() )
  {
    bnpc.deaggro( pHatedActor );
  }

  auto dtMove = tickCount - m_lastMoveTime;
  auto dtRot = tickCount - m_lastRotTime;
  if( dtRot == tickCount )
    dtRot = 300;

  float targetRadius = pHatedActor->getRadius();
  float stopDistance = targetRadius + bnpc.getNaviTargetReachedDistance() + 3.0f;
  float startDistance = stopDistance + 0.5f;

  bool isPathing = bnpc.getNaviIsPathing();

  // movement
  if( !bnpc.hasFlag( Entity::Immobile ) && !hasQueuedAction )
  {
    if( distance > startDistance )
    {
      if( dtMove >= 1500 )
      {
        if( pNaviProvider )
          pNaviProvider->setMoveTarget( bnpc.getAgentId(), pHatedActor->getPos() );

        bnpc.moveTo( *pHatedActor );
        m_lastMoveTime = tickCount;
      }
    }
    else if( isPathing && distance <= stopDistance )
    {
      if( pNaviProvider )
        pNaviProvider->resetMoveTarget( bnpc.getAgentId() );
      bnpc.setNaviIsPathing( false );
    }
  }

  // ensure navi pos == bnpc pos
  if( bnpc.getAgentId() != -1 )
  {
    auto pos = pNaviProvider->getAgentPos( bnpc.getAgentId() );
    auto myPos = bnpc.getPos();
    if( ( pos.x != myPos.x || pos.y != myPos.y || pos.z != myPos.z ) )
    {
      bnpc.setPos( pos );
    }
  }

  // rotation
  if( !bnpc.hasFlag( Entity::TurningDisabled ) && !hasQueuedAction )
  {
    if( dtRot >= 300 )
    {
      Common::Vector3 lookAtPos = pHatedActor->getPos();

      // If moving and outside combat range, face the movement direction (Navi Agent)
      if( isPathing && distance > stopDistance && bnpc.getAgentId() != -1 )
      {
        auto naviPos = pNaviProvider->getAgentPos( bnpc.getAgentId() );
        float dx = naviPos.x - bnpc.getPos().x;
        float dz = naviPos.z - bnpc.getPos().z;
        // Only use heading if we actually moved enough to have a valid vector
        if( ( dx * dx + dz * dz ) > 0.0001f )
        {
          lookAtPos = naviPos;
        }
      }

      bnpc.face( lookAtPos );
      bnpc.sendPositionUpdate( tickCount );
      m_lastRotTime = tickCount;
    }
  }

  // combat
  if( !hasQueuedAction && distance <= startDistance )
  {
    bnpc.processGambits( tickCount );

    // in combat range. ATTACK!
    if( !bnpc.hasFlag( Entity::BNpcFlag::AutoAttackDisabled ) && bnpc.isFacingTarget( *pHatedActor, 0.99f ) )
    {
      bnpc.autoAttack( pHatedActor );
    }
  }
  m_lastTick = tickCount;
}

void AI::Fsm::StateCombat::onEnter( Entity::BNpc& bnpc )
{
}

void AI::Fsm::StateCombat::onExit( Entity::BNpc& bnpc )
{
  bnpc.hateListClear();
  bnpc.changeTarget( Common::INVALID_GAME_OBJECT_ID64 );
  bnpc.setStance( Common::Stance::Passive );
  bnpc.setOwner( nullptr );
}
