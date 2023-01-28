#include <Service.h>

#include "TaskMgr.h"
#include "WarpMgr.h"
#include "TerritoryMgr.h"

#include <WorldServer.h>
#include <Logging/Logger.h>

#include "Task/MoveTerritoryTask.h"
#include "Task/WarpTask.h"
#include <Network/CommonActorControl.h>
#include "Territory/Territory.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Actor/Player.h"

using namespace Sapphire::World::Manager;
using namespace Sapphire::World;
using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void WarpMgr::requestMoveTerritory( Entity::Player& player, Common::WarpType warpType,
                                    uint32_t targetTerritoryId, Common::FFXIVARR_POSITION3 targetPos, float targetRot )
{
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  auto& server = Common::Service< WorldServer >::ref();

  auto pTeri = teriMgr.getTerritoryByGuId( targetTerritoryId );
  if( !pTeri )
  {
    Logger::error( "Unable to find target territory instance {}", targetTerritoryId );
    return;
  }

  m_entityIdToWarpInfoMap[ player.getId() ] = { targetTerritoryId, warpType, targetPos, targetRot };

  player.updatePrevTerritory();

  player.sendToInRangeSet( makeActorControl( player.getId(), WarpStart, warpType, 1, pTeri->getTerritoryTypeId() ), true );
  player.sendToInRangeSet( makeActorControl( player.getId(), ActorDespawnEffect, warpType ) );
  player.setStateFlag( PlayerStateFlag::BetweenAreas );

  auto moveTerritoryPacket = makeZonePacket< FFXIVIpcMoveTerritory >( player.getId() );
  moveTerritoryPacket->data().index = -1;
  moveTerritoryPacket->data().territoryType = pTeri->getTerritoryTypeId();
  moveTerritoryPacket->data().zoneId = player.getTerritoryTypeId();
  moveTerritoryPacket->data().worldId = server.getWorldId();
  moveTerritoryPacket->data().worldId1 = server.getWorldId();
  moveTerritoryPacket->data().landId = -1;
  moveTerritoryPacket->data().landSetId = -1;
  moveTerritoryPacket->data().landTerritoryId = -1;
  strcpy( moveTerritoryPacket->data().worldName, "Sapphire" );
  server.queueForPlayer( player.getCharacterId(), moveTerritoryPacket );

  // create warp task
  auto& taskMgr = Common::Service< TaskMgr >::ref();
  taskMgr.queueTask( makeMoveTerritoryTask( player, warpType, targetTerritoryId, targetPos, targetRot, 2000 ) );
}

void WarpMgr::finishWarp( Entity::Player& player )
{
  WarpType warpType = WarpType::WARP_TYPE_NORMAL;
  auto it = m_entityIdToWarpInfoMap.find( player.getId() );
  if( it != m_entityIdToWarpInfoMap.end() )
    warpType = it->second.m_warpType;

  switch( warpType )
  {
    case WarpType::WARP_TYPE_REISE:
    case WarpType::WARP_TYPE_HOME_POINT:
    {
      if( player.getStatus() == Common::ActorStatus::Dead )
      {
        player.resetHp();
        player.resetMp();
        player.setStatus( Common::ActorStatus::Idle );
      }
    }
  }

  auto zoneInPacket = makeActorControlSelf( player.getId(), Appear, warpType, 0, 0, 0 );
  auto SetStatusPacket = makeActorControl( player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );

  player.setZoningType( Common::ZoneingType::None );

  if( !player.getGmInvis() )
    player.sendToInRangeSet( zoneInPacket );

  player.sendToInRangeSet( SetStatusPacket, true );

  auto& server = Common::Service< WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), zoneInPacket );

  player.unsetStateFlag( PlayerStateFlag::BetweenAreas );

}

void WarpMgr::requestWarp( Entity::Player& player, Common::WarpType warpType, Common::FFXIVARR_POSITION3 targetPos, float targetRot )
{
  m_entityIdToWarpInfoMap[ player.getId() ] = { 0, warpType, targetPos, targetRot };

  player.sendToInRangeSet( makeActorControl( player.getId(), WarpStart, warpType, 1, 0, player.getTerritoryTypeId(), 1 ), true );
  player.sendToInRangeSet( makeActorControl( player.getId(), ActorDespawnEffect, warpType ) );

  auto& taskMgr = Common::Service< TaskMgr >::ref();
  taskMgr.queueTask( makeWarpTask( player, warpType, targetPos, targetRot, 1000 ) );
}
