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

  auto pHatedActor = bnpc.hateListGetHighest();
  if( !pHatedActor )
    return;

  pNaviProvider->updateAgentParameters( bnpc );

  auto distanceOrig = Common::Util::distance( bnpc.getPos(), bnpc.getSpawnPos() );

  if( !pHatedActor->isAlive() || bnpc.getTerritoryId() != pHatedActor->getTerritoryId() )
  {
    bnpc.hateListRemove( pHatedActor );
    pHatedActor = bnpc.hateListGetHighest();
  }

  if( !pHatedActor )
    return;

  auto distance = Common::Util::distance( bnpc.getPos(), pHatedActor->getPos() );

  if( !bnpc.hasFlag( Entity::NoDeaggro ) )
  {

  }

  if( !bnpc.hasFlag( Entity::Immobile ) && distance > ( bnpc.getNaviTargetReachedDistance() + pHatedActor->getRadius() ) )
  {
    if( pNaviProvider )
      pNaviProvider->setMoveTarget( bnpc, pHatedActor->getPos() );

    bnpc.moveTo( *pHatedActor );
  }

  if (bnpc.hasFlag(Entity::Immobile) && distance > 30.0f )
  {
    bnpc.deaggro( pHatedActor );
  }

  if( pNaviProvider->syncPosToChara( bnpc ) )
    bnpc.sendPositionUpdate();

  if( distance < ( bnpc.getNaviTargetReachedDistance() + pHatedActor->getRadius() ) )
  {
    if( !bnpc.hasFlag( Entity::TurningDisabled ) && bnpc.face( pHatedActor->getPos() ) )
      bnpc.sendPositionUpdate();

    if( !bnpc.checkAction() )
      bnpc.processGambits( tickCount );

    // in combat range. ATTACK!
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

