#include <Service.h>

#include "TaskMgr.h"
#include "WarpMgr.h"
#include "TerritoryMgr.h"

#include <WorldServer.h>
#include <Logging/Logger.h>
#include <Exd/ExdData.h>

#include "Task/MoveTerritoryTask.h"
#include "Task/WarpTask.h"

#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include <Network/PacketWrappers/ActorControlPacket.h>

#include <Manager/PlayerMgr.h>

#include "Territory/Territory.h"
#include "Actor/Player.h"
#include <Territory/InstanceObjectCache.h>

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
  
  // create warp task
  auto& taskMgr = Common::Service< TaskMgr >::ref();
  taskMgr.queueTask( makeMoveTerritoryTask( player, warpType, targetTerritoryId, targetPos, targetRot, 1000 ) );
}

void WarpMgr::requestWarp( Entity::Player& player, Common::WarpType warpType, Common::FFXIVARR_POSITION3 targetPos, float targetRot )
{
  m_entityIdToWarpInfoMap[ player.getId() ] = { 0, warpType, targetPos, targetRot };

  player.sendToInRangeSet( makeActorControlSelf( player.getId(), WarpStart, warpType, warpType, 0, player.getTerritoryTypeId(), 1 ), true );
  player.sendToInRangeSet( makeActorControl( player.getId(), ActorDespawnEffect, warpType, player.getTerritoryTypeId() ) );

  auto& taskMgr = Common::Service< TaskMgr >::ref();
  taskMgr.queueTask( makeWarpTask( player, warpType, targetPos, targetRot, 1000 ) );
}

void WarpMgr::finishWarp( Entity::Player& player )
{
  auto& playerMgr = Common::Service< PlayerMgr >::ref();

  WarpType warpType = WarpType::WARP_TYPE_NORMAL;
  auto it = m_entityIdToWarpInfoMap.find( player.getId() );
  if( it != m_entityIdToWarpInfoMap.end() )
    warpType = it->second.m_warpType;

  bool raiseAnim = player.getStatus() == Common::ActorStatus::Dead ? 1 : 0;

  switch( warpType )
  {
    case WarpType::WARP_TYPE_REISE:
    case WarpType::WARP_TYPE_HOME_POINT:
    case WarpType::WARP_TYPE_EXIT_RANGE:
    {
      if( player.getStatus() == Common::ActorStatus::Dead )
      {
        player.resetHp();
        player.resetMp();
        player.setStatus( Common::ActorStatus::Idle );
      }
    }
  }

  auto warpFinishAnim = warpType - 1;

  auto zoneInPacket = makeActorControlSelf( player.getId(), Appear, warpFinishAnim, raiseAnim, 0, 0 );
  auto setStatusPacket = makeActorControl( player.getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );
  player.setZoningType( Common::ZoningType::None );

  if( !player.getGmInvis() )
    player.sendToInRangeSet( zoneInPacket );

  auto& server = Common::Service< WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), zoneInPacket );

  player.sendToInRangeSet( setStatusPacket, true );

  playerMgr.onUnsetStateFlag( player, PlayerStateFlag::BetweenAreas );
}

void WarpMgr::requestPlayerTeleport( Entity::Player& player, uint16_t aetheryteId, uint8_t teleportType )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& teriMgr = Common::Service< TerritoryMgr >::ref();

  auto aetherData = exdData.getRow< Excel::Aetheryte >( aetheryteId );

  if( !aetherData )
    return;

  const auto& data = aetherData->data();

  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto pop = instanceObjectCache.getPopRangeInfo( data.PopRange[ 0 ] );

  Common::FFXIVARR_POSITION3 pos{ 0.f, 0.f, 0.f };

  float rot = 0.f;

  if( pop )
  {
    PlayerMgr::sendDebug( player, "Teleport: popRange {0} found!", data.PopRange[ 0 ] );
    pos = pop->m_pos;
    rot = pop->m_rotation;
  }
  else
  {
    PlayerMgr::sendDebug( player, "Teleport: popRange {0} not found in {1}!", data.PopRange[ 0 ], data.TerritoryType );
  }

  auto townPlace = exdData.getRow< Excel::PlaceName >( data.TelepoName );
  auto aetherytePlace = exdData.getRow< Excel::PlaceName >( data.TransferName );

  PlayerMgr::sendDebug( player, "Teleport: {0} - {1} ({2})",
                           townPlace->getString( townPlace->data().Text.SGL ),
                           aetherytePlace->getString( aetherytePlace->data().Text.SGL ),
                           data.TerritoryType );

  // if it is a teleport in the same zone, we want to do warp instead of moveTerri
  bool sameTerritory = player.getTerritoryTypeId() == data.TerritoryType;

  WarpType warpType = WarpType::WARP_TYPE_NORMAL;
  // TODO: should teleport type be a separate enum?
  if( teleportType == 1 || teleportType == 2 ) // teleport
  {
    warpType = WarpType::WARP_TYPE_TELEPO;
    player.setZoningType( Common::ZoningType::Teleport );
  }
  else if( teleportType == 3 ) // return
  {
    warpType = WarpType::WARP_TYPE_EXIT_RANGE;
    player.setZoningType( Common::ZoningType::Return );
  }
  else if( teleportType == 4 ) // return dead
  {
    warpType = WarpType::WARP_TYPE_EXIT_RANGE;
    player.setZoningType( Common::ZoningType::ReturnDead );
  }

  if( sameTerritory )
    requestWarp( player, warpType, pos, rot );
  else
  {
    auto pTeri = teriMgr.getZoneByTerritoryTypeId( data.TerritoryType );
    if( !pTeri )
      return;

    requestMoveTerritory( player, warpType, pTeri->getGuId(), pos, rot );
  }
}