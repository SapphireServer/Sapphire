#include "TestTask.h"

#include <Logging/Logger.h>

using namespace Sapphire::World;

TestTask::TestTask( uint64_t delayTime ) : Task( delayTime )
{
}

void TestTask::onQueue()
{
  Logger::debug( "Queueing a TestTask!" );
}

void TestTask::execute()
{
  Logger::debug( "Executing a TestTask after {}ms", getDelayTimeMs() );
}

std::string TestTask::toString()
{
  return "TestTask";
}


