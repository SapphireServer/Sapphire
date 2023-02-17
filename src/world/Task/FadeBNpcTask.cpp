#include "FadeBNpcTask.h"

#include <Logging/Logger.h>
#include <Actor/BNpc.h>
#include <Manager/TerritoryMgr.h>
#include <Manager/MgrUtil.h>
#include "WorldServer.h"
#include <Service.h>

#include <Territory/Territory.h>
#include <utility>

#include <Network/CommonActorControl.h>
#include <Network/PacketWrappers/ActorControlPacket.h>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

FadeBNpcTask::FadeBNpcTask( uint64_t delayTime, Entity::BNpcPtr bnpc ) :
  Task( delayTime ),
  m_pBNpc( std::move( bnpc ) )
{
}

void FadeBNpcTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void FadeBNpcTask::execute()
{
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( m_pBNpc->getTerritoryId() );

  if( !pZone )
    return;

  auto inRangePlayerIds = m_pBNpc->getInRangePlayerIds();
  server().queueForPlayers( inRangePlayerIds, makeActorControl( m_pBNpc->getId(), ActorControlType::DeadFadeOut, 0, 0, 0 ) );
}

std::string FadeBNpcTask::toString()
{
  return fmt::format( "FadeBNpcTask: BNpc#{}, TerritoryId#{}, ElapsedTimeMs: {}", m_pBNpc->getId(), m_pBNpc->getTerritoryId(), getDelayTimeMs() );
}


