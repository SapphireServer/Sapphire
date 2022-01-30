#include "MoveTerritoryTask.h"

#include <Logging/Logger.h>
#include <Actor/Player.h>
#include <WorldServer.h>
#include <Service.h>

#include <Manager/TerritoryMgr.h>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;

MoveTerritoryTask::MoveTerritoryTask( Entity::Player& player, Common::WarpType warpType,
                                      uint32_t targetTerritoryId, Common::FFXIVARR_POSITION3 targetPos, float targetRot, uint64_t delayTime ) : Task( delayTime )
{
  m_playerId = player.getId();
  m_warpInfo = { targetTerritoryId, warpType, targetPos, targetRot };
}

void MoveTerritoryTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void MoveTerritoryTask::execute()
{
  auto& server = Common::Service< WorldServer >::ref();
  auto pPlayer = server.getPlayer( m_playerId );
  if( !pPlayer )
    return;

  pPlayer->setPos( m_warpInfo.m_targetPos, false );
  pPlayer->setRot( m_warpInfo.m_targetRot );

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  pPlayer->setOnEnterEventDone( false );

  TerritoryPtr pZone;
  if( m_warpInfo.m_targetTerritoryId != 0 )
    pZone = teriMgr.getTerritoryByGuId( m_warpInfo.m_targetTerritoryId );

  if( !teriMgr.movePlayer( pZone, *pPlayer ) )
  {
    // todo: this will require proper handling, for now just return the player to their previous area
    pPlayer->setPos( pPlayer->getPrevPos(), false );

    auto pZone1 = teriMgr.getZoneByTerritoryTypeId( pPlayer->getPrevTerritoryTypeId() );
    if( !teriMgr.movePlayer( pZone1, *pPlayer ) )
      return;
  }
}

std::string MoveTerritoryTask::toString()
{
  return fmt::format( "MoveTerritoryTask: Player#{}, TerritoryId#{}, ElapsedTimeMs: {}", m_playerId, m_warpInfo.m_targetTerritoryId, getDelayTimeMs() );
}


