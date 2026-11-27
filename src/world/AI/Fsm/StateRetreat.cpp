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
  auto elapsedHeal = tickCount - m_lastHeal;

  if( auto pBNpc = pEntity->getAsBNpc() )
  {
    auto& bnpc = *pBNpc;

    // we call moveTo on tick to sync the position from navmesh agent
    if( bnpc.moveTo( bnpc.getSpawnPos() ) )
    {
      bnpc.setRoamTargetReached( true );
      bnpc.setLastRoamTargetReachedTime( Common::Util::getTimeSeconds() );
    }
    else
    {
      if( auto pController = bnpc.getController() )
      {
        auto& path = pController->getPath();
        path.m_flags = static_cast< Controller::Controller::PathFlags >( Controller::Controller::IgnoreObstacles |
                       Controller::Controller::IgnoreActorCollision );
      }
    }

    if( elapsedHeal >= 2500 && bnpc.getHpPercent() < 100 )
    {
      bnpc.heal( bnpc.getMaxHp() / 10.f );
      m_lastHeal = tickCount;
    }
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

    bnpc.setState( Entity::BNpcState::Retreat );

    if( pNaviProvider )
    {
      auto& path = bnpc.getController()->getPath();
      path.m_type = Controller::Controller::PathType::FixedPos;
      path.m_targetPos = bnpc.getSpawnPos();
      path.m_flags = static_cast< Controller::Controller::PathFlags >( Controller::Controller::PathFlags::IgnoreActorCollision | Controller::Controller::PathFlags::IgnoreObstacles );
      path.m_targetReachedDist = 0.5f;

      pNaviProvider->setMoveTarget( bnpc.getAgentId(), path.m_targetPos );

      bnpc.moveTo( path.m_targetPos );
    }
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

    bnpc.setState( Entity::BNpcState::Idle );

    auto& path = bnpc.getController()->getPath();
    path.reset();

    if( bnpc.getHpPercent() < 100 )
      bnpc.heal( bnpc.getMaxHp() );
  }
}

