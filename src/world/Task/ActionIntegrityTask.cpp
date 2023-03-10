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

ActionIntegrityTask::ActionIntegrityTask( uint32_t resultId, Entity::CharaPtr pTarget, Action::ActionResultList& results, uint64_t delayTime ) : Task( delayTime )
{
  Logger::debug( "Constructor called {} {} {}", resultId, pTarget->getId(), results.size() );
  m_resultId = resultId;
  m_pTarget = std::move( pTarget );
  m_results = results;
}

void ActionIntegrityTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void ActionIntegrityTask::execute()
{
  if( !m_pTarget )
    return;

  auto& server = Common::Service< WorldServer >::ref();

  auto inRangePlayers = m_pTarget->getInRangePlayerIds( true );

  if( inRangePlayers.empty() )
    return;

  for( auto& actionResult : m_results )
  {
    if( actionResult && actionResult->getTarget() && actionResult->getTarget()->isAlive() )
      actionResult->execute();
  }

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

  server.queueForPlayers( inRangePlayers, integrityPacket );

}

std::string ActionIntegrityTask::toString()
{
  return fmt::format( "ActionIntegrityTask: ResultId#{}, TargetId#{}, ElapsedTimeMs: {}", m_resultId, m_pTarget ? m_pTarget->getId() : 0, getDelayTimeMs() );
}


