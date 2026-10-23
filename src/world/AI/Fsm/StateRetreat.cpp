#include "StateRetreat.h"
#include "Actor/BNpc.h"
#include "Logging/Logger.h"
#include <Service.h>
#include <Manager/TerritoryMgr.h>

#include <Territory/Territory.h>
#include <Navi/NaviProvider.h>

using namespace Sapphire::World;

void AI::Fsm::StateRetreat::onUpdate( Entity::GameObjectPtr& pEntity, uint64_t tickCount )
{
  auto elapsed = tickCount - m_lastTick;

  if( elapsed < 2500 )
    return;

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    if( bnpc.moveTo( bnpc.getSpawnPos() ) )
    {
      bnpc.setRoamTargetReached( true );
      bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
    }
    if( bnpc.getHpPercent() < 100 )
      bnpc.heal( bnpc.getMaxHp() / 10.f );
  }
  m_lastTick = tickCount;
}

void AI::Fsm::StateRetreat::onEnter( Entity::GameObjectPtr& pEntity )
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( pEntity->getTerritoryId() );
  auto pNaviProvider = pZone->getNaviProvider();

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    bnpc.setRoamTargetReached( false );
    bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityIgnoreDamage );

    if( pNaviProvider )
      pNaviProvider->setMoveTarget( bnpc.getAgentId(), bnpc.getSpawnPos() );
  }
}

void AI::Fsm::StateRetreat::onExit( Entity::GameObjectPtr& pEntity )
{
  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    bnpc.setOwner( nullptr );
    bnpc.setRoamTargetReached( false );
    bnpc.setInvincibilityType( Common::InvincibilityType::InvincibilityNone );
    bnpc.setRot( bnpc.getSpawnRot() );
    if( bnpc.getHpPercent() < 100 )
      bnpc.heal( bnpc.getMaxHp() );
  }
}

