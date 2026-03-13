#include <Logging/Logger.h>
#include <Service.h>

#include "TaskMgr.h"
#include "Task/Task.h"

using namespace Sapphire::World::Manager;
using namespace Sapphire::World;

void TaskMgr::update( uint64_t tickCount )
{
  std::vector< TaskPtr > tmpTaskList;
  for( const auto& pTask : m_taskList )
  {
    // is the task ready for execution?
    if( ( tickCount - pTask->getQueueTimeMs() ) >= pTask->getDelayTimeMs() )
    {
      //Logger::debug( "[TaskMgr] " + pTask->toString() );
      pTask->execute();
    }
    else
      tmpTaskList.push_back( pTask );
  }

  m_taskList = tmpTaskList;
  m_lastTick = tickCount;

  while( !m_deferredTasks.empty() )
  {
    auto pTask = m_deferredTasks.front();
    m_deferredTasks.pop();
    m_taskList.push_back( pTask );
  }
}

void TaskMgr::queueTask( const TaskPtr& pTask )
{
  pTask->onQueue();
  m_deferredTasks.push( pTask );
}
