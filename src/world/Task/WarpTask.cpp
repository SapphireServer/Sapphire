#include "WarpTask.h"

#include <Logging/Logger.h>
#include <Actor/Player.h>
#include <WorldServer.h>
#include <Service.h>
#include <Network/PacketWrappers/WarpPacket.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/PlayerMgr.h>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

WarpTask::WarpTask( Entity::Player& player, Common::WarpType warpType,
                    Common::FFXIVARR_POSITION3 targetPos, float targetRot, uint64_t delayTime ) : Task( delayTime )
{
  m_playerId = player.getId();
  m_warpInfo = { 0, warpType, targetPos, targetRot };
}

void WarpTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void WarpTask::execute()
{
  auto& server = Common::Service< WorldServer >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto pPlayer = playerMgr.getPlayer( m_playerId );
  if( !pPlayer )
    return;

  auto inRangePlayerIds = pPlayer->getInRangePlayerIds();
  auto warpPacket = makeWarp( pPlayer->getId(), m_warpInfo.m_warpType, m_warpInfo.m_targetPos, m_warpInfo.m_targetRot );
  server.queueForPlayers( inRangePlayerIds, warpPacket );
  server.queueForPlayer( pPlayer->getCharacterId(), warpPacket );

  pPlayer->setPos( m_warpInfo.m_targetPos, false );
}

std::string WarpTask::toString()
{
  return fmt::format( "WarpTask: Player#{}, TerritoryId#{}, ElapsedTimeMs: {}", m_playerId, m_warpInfo.m_targetTerritoryId, getDelayTimeMs() );
}


