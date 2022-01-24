#include "DelayedEmnityTask.h"

#include <Actor/BNpc.h>
#include <Logging/Logger.h>

using namespace Sapphire::World;


Sapphire::World::DelayedEmnityTask::DelayedEmnityTask( uint64_t delayTime, Entity::BNpcPtr bnpc, Entity::CharaPtr chara, int32_t hateAmount ) :
  Task(delayTime),
  m_pBNpc(std::move(bnpc)),
  m_pChara(std::move(chara)),
  m_hateAmount( std::move(hateAmount) )
{
}


void DelayedEmnityTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void DelayedEmnityTask::execute()
{
  m_pBNpc->hateListAdd( m_pChara, m_hateAmount );
}

std::string DelayedEmnityTask::toString()
{
  return fmt::format( "DelayedEmnityTask: BNpc#{}, Chara Name: {}, Hate Amount: {}, ElapsedTimeMs: {}", m_pBNpc->getId(), m_pChara->getName(), m_hateAmount, getDelayTimeMs() );
}
