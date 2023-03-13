#include "ActionIntegrityTask.h"

#include <Logging/Logger.h>
#include <Actor/Player.h>
#include <Actor/Chara.h>
#include <WorldServer.h>
#include <Service.h>
#include <Network/PacketWrappers/WarpPacket.h>
#include <StatusEffect/StatusEffect.h>

#include <utility>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

ActionIntegrityTask::ActionIntegrityTask( uint32_t resultId, Entity::CharaPtr pTarget, Action::ActionResultList& results, uint64_t delayTime ) : Task( delayTime )
{
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

  auto integrityPacket = makeZonePacket< FFXIVIpcActionIntegrity >( 0 );
  auto& data = integrityPacket->data();
  integrityPacket->setSourceActor( m_pTarget->getId() );

  for( int i = 0; i < 4; ++i )
    data.Status[ i ].Source = Common::INVALID_GAME_OBJECT_ID;

  int statusIdx = 0;
  for( auto& actionResult : m_results )
  {
    if( actionResult && actionResult->getTarget() )
      actionResult->execute();

    if( ( actionResult->getCalcResultParam().Type == Common::CALC_RESULT_TYPE_SET_STATUS ) ||
        ( actionResult->getCalcResultParam().Type == Common::CALC_RESULT_TYPE_SET_STATUS_ME ) )
    {
      auto& status = data.Status[ statusIdx++ ];
      auto pEffect = actionResult->getStatusEffect();
      status.Source = pEffect->getSrcActorId();
      status.Time = static_cast< float >( pEffect->getDuration() ) / 1000;
      status.Id = static_cast< uint16_t >( pEffect->getId() );
      status.Slot = static_cast< uint8_t >( pEffect->getSlot() );
      status.SystemParam = static_cast< int16_t >( pEffect->getParam() );
    }
  }

  data.Hp = m_pTarget->getHp();
  data.HpMax = m_pTarget->getMaxHp();
  data.Mp = m_pTarget->getMp();
  data.MpMax = m_pTarget->getMaxMp();
  data.Tp = m_pTarget->getTp();
  data.ResultId = m_resultId;
  data.Target = m_pTarget->getId();
  data.StatusCount = statusIdx;
  data.ClassJob = static_cast< uint8_t >( m_pTarget->getClass() );
  data.unknown_E0 = 0xE0;

  server.queueForPlayers( inRangePlayers, integrityPacket );

}

std::string ActionIntegrityTask::toString()
{
  return fmt::format( "ActionIntegrityTask: ResultId#{}, TargetId#{}, ElapsedTimeMs: {}", m_resultId, m_pTarget ? m_pTarget->getId() : 0, getDelayTimeMs() );
}


