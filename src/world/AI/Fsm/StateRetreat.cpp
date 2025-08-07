#include "StateRetreat.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateRetreat::onUpdate( Entity::BNpc& bnpc, uint64_t tickCount )
{
  if( bnpc.moveTo( bnpc.getSpawnPos() ) )
  {
    bnpc.setRoamTargetReached( true );
    bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
  }
}

void AI::Fsm::StateRetreat::onEnter( Entity::BNpc& bnpc )
{
  bnpc.setRoamTargetReached( false );

  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( bnpc.getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityIgnoreDamage );

  if( pNaviProvider )
    pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getSpawnPos() );
}

void AI::Fsm::StateRetreat::onExit( Entity::BNpc& bnpc )
{
  bnpc.setOwner( nullptr );
  bnpc.setRoamTargetReached( false );
  bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityNone );
}

