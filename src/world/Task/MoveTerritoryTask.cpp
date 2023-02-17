#include "MoveTerritoryTask.h"

#include <Logging/Logger.h>
#include <Actor/Player.h>
#include <WorldServer.h>
#include <Service.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/PlayerMgr.h>
#include <Network/PacketContainer.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/PacketWrappers/ActorControlPacket.h>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Common;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

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

  auto inRangePlayerIds = pPlayer->getInRangePlayerIds();

  auto warpStart = makeActorControlSelf( pPlayer->getId(), WarpStart, m_warpInfo.m_warpType, 1, 0, m_warpInfo.m_targetTerritoryId, 1 );
  server.queueForPlayers( inRangePlayerIds, warpStart );
  server.queueForPlayer( pPlayer->getCharacterId(), warpStart );
  server.queueForPlayers( inRangePlayerIds, makeActorControl( pPlayer->getId(), ActorDespawnEffect, m_warpInfo.m_warpType, m_warpInfo.m_targetTerritoryId ) );

  Common::Service< PlayerMgr >::ref().onSetStateFlag( *pPlayer, Common::PlayerStateFlag::BetweenAreas );

  auto moveTerritoryPacket = makeZonePacket< WorldPackets::Server::FFXIVIpcMoveTerritory >( pPlayer->getId() );
  moveTerritoryPacket->data().index = -1;
  moveTerritoryPacket->data().territoryType = m_warpInfo.m_targetTerritoryId;
  moveTerritoryPacket->data().zoneId = pPlayer->getTerritoryTypeId();
  moveTerritoryPacket->data().worldId = server.getWorldId();
  moveTerritoryPacket->data().worldId1 = server.getWorldId();
  moveTerritoryPacket->data().landId = -1;
  moveTerritoryPacket->data().landSetId = -1;
  moveTerritoryPacket->data().landTerritoryId = -1;
  strcpy( moveTerritoryPacket->data().worldName, "Sapphire" );
  server.queueForPlayer( pPlayer->getCharacterId(), moveTerritoryPacket );

  pPlayer->setPos( m_warpInfo.m_targetPos, false );
  pPlayer->setRot( m_warpInfo.m_targetRot );

  auto& teriMgr = Common::Service< TerritoryMgr >::ref();
  pPlayer->setOnEnterEventDone( false );

  TerritoryPtr pZone;
  if( m_warpInfo.m_targetTerritoryId != 0 )
    pZone = teriMgr.getTerritoryByGuId( m_warpInfo.m_targetTerritoryId );

  if( !pZone )
  {
    Logger::error( "Territory typeId#{} not found!", m_warpInfo.m_targetTerritoryId );
    return;
  }

  if( !teriMgr.movePlayer( *pZone, *pPlayer ) )
  {
    // todo: this will require proper handling, for now just return the player to their previous area
    pPlayer->setPos( pPlayer->getPrevPos(), false );

    auto pZone1 = teriMgr.getZoneByTerritoryTypeId( pPlayer->getPrevTerritoryTypeId() );
    if( !teriMgr.movePlayer( *pZone1, *pPlayer ) )
      return;
  }
}

std::string MoveTerritoryTask::toString()
{
  return fmt::format( "MoveTerritoryTask: Player#{}, TerritoryId#{}, ElapsedTimeMs: {}", m_playerId, m_warpInfo.m_targetTerritoryId, getDelayTimeMs() );
}


