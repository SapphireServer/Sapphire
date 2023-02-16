#include "ActionIntegrityTask.h"

#include <Logging/Logger.h>
#include <Actor/Player.h>
#include <Actor/Chara.h>
#include <WorldServer.h>
#include <Service.h>
#include <Network/PacketWrappers/WarpPacket.h>

#include <utility>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

ActionIntegrityTask::ActionIntegrityTask( uint32_t resultId, Entity::CharaPtr pTarget, uint64_t delayTime ) : Task( delayTime )
{
  m_resultId = resultId;
  m_pTarget = std::move( pTarget );
}

void ActionIntegrityTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void ActionIntegrityTask::execute()
{
  auto& server = Common::Service< WorldServer >::ref();

  auto inRangePlayers = m_pTarget->getInRangePlayerIds( true );

  if( inRangePlayers.empty() )
    return;

  auto integrityPacket = makeZonePacket< FFXIVIpcActionIntegrity >( 0 );
  auto& data = integrityPacket->data();
  integrityPacket->setSourceActor( m_pTarget->getId() );
  data.Hp = m_pTarget->getHp();
  data.HpMax = m_pTarget->getMaxHp();
  data.Mp = m_pTarget->getMp();
  data.MpMax = m_pTarget->getMaxMp();
  data.Tp = m_pTarget->getTp();
  data.ResultId = m_resultId;
  data.Target = m_pTarget->getId();


  for( auto& charId : inRangePlayers )
  {
    auto pPlayer = server.getPlayer( charId );
    Logger::debug( "Sending to {}", charId );
    integrityPacket->setTargetActor( pPlayer->getId() );

    server.queueForPlayer( charId, integrityPacket );
  }

}

std::string ActionIntegrityTask::toString()
{
  return fmt::format( "ActionIntegrityTask: ResultId#{}, TargetId#{}, ElapsedTimeMs: {}", m_resultId, m_pTarget->getId(), getDelayTimeMs() );
}


