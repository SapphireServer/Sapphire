#include "RemoveBNpcTask.h"

#include <Logging/Logger.h>
#include <Actor/BNpc.h>
#include <Manager/TerritoryMgr.h>
#include <Service.h>

#include <Territory/Territory.h>
#include <utility>

using namespace Sapphire::World;

RemoveBNpcTask::RemoveBNpcTask( uint64_t delayTime, Entity::BNpcPtr bnpc ) :
  Task( delayTime ),
  m_pBNpc( std::move( bnpc ) )
{
}

void RemoveBNpcTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void RemoveBNpcTask::execute()
{
  Logger::info( toString() );

  auto teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto pZone = teriMgr.getTerritoryByGuId( m_pBNpc->getTerritoryId() );

  if( !pZone )
    return;

  pZone->removeActor( m_pBNpc );
}

std::string RemoveBNpcTask::toString()
{
  return fmt::format( "RemoveBNpcTask: BNpc#{}, TerritoryId#{}, ElapsedTimeMs: {}", m_pBNpc->getId(), m_pBNpc->getTerritoryId(), getDelayTimeMs() );
}


