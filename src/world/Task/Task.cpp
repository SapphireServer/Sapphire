#include <cstdint>
#include <Util/Util.h>
#include "Task.h"

Sapphire::World::Task::Task( uint64_t delayTime ) :
  m_delayTimeMs( delayTime ),
  m_timeQueuedMs( Common::Util::getTimeMs() )
{

}

uint64_t Sapphire::World::Task::getQueueTimeMs() const
{
  return m_timeQueuedMs;
}

uint64_t Sapphire::World::Task::getDelayTimeMs() const
{
  return m_delayTimeMs;
}
