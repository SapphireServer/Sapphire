#include "StateCombat.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>

#include <Manager/TerritoryMgr.h>
#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateCombat::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();
  bool hasQueuedAction = bnpc.checkAction();

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
    bnpc.hateListRemove( pHatedActor );
    pHatedActor = bnpc.hateListGetHighest();
  }

  if( !pHatedActor )
    return;

  auto distance = Common::Util::distance( bnpc.getPos(), pHatedActor->getPos() );

  // All possibilities to automatically lose aggro go here
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

  if( bnpc.pathingActive() && !hasQueuedAction &&
      !bnpc.hasFlag( Entity::Immobile ) &&
      distance > ( bnpc.getNaviTargetReachedDistance() + pHatedActor->getRadius() ) )
  {

    if( pNaviProvider )
      pNaviProvider->setMoveTarget( bnpc.getAgentId(), pHatedActor->getPos() );

    bnpc.moveTo( *pHatedActor );
  }

  if( bnpc.getAgentId() != -1 )
  {
    auto pos = pNaviProvider->getAgentPos( bnpc.getAgentId() );
    if( pos.x != bnpc.getPos().x || pos.y != bnpc.getPos().y || pos.z != bnpc.getPos().z )
      bnpc.setPos( pos );
  }

  if( !hasQueuedAction && distance < ( bnpc.getNaviTargetReachedDistance() + pHatedActor->getRadius() ) )
  {
    // todo: dont turn if facing
    if( !bnpc.hasFlag( Entity::TurningDisabled ) )
      bnpc.face( pHatedActor->getPos() );

    bnpc.processGambits( tickCount );

    // in combat range. ATTACK!
    if( !bnpc.hasFlag( Entity::BNpcFlag::AutoAttackDisabled ) )
      bnpc.autoAttack( pHatedActor );
  }

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

