#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"

namespace Sapphire::World
{

class TestTask : public Task
{
public:
  TestTask( uint64_t delayTime );

  void onQueue() override;
  void execute() override;
  std::string toString() override;
};

}
