#include <Logging/Logger.h>
#include <Service.h>

#include "TaskMgr.h"
#include "Task/Task.h"

using namespace Sapphire::World::Manager;
using namespace Sapphire::World;

void TaskMgr::update( uint64_t tickCount )
{

  for( auto it = m_taskList.begin(); it != m_taskList.end(); )
  {
    auto pTask = *it;
    // is the task ready for execution?
    if( ( tickCount - pTask->getQueueTimeMs() ) >= pTask->getDelayTimeMs() )
    {
      Logger::info( "[TaskMgr] " + pTask->toString() );
      pTask->execute();
      it = m_taskList.erase( it );
    }
    else
      ++it;
  }

  m_lastTick = tickCount;

}

void TaskMgr::queueTask( const TaskPtr& pTask )
{
  pTask->onQueue();
  m_taskList.push_back( pTask );
}
