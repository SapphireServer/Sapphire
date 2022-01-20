#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"

namespace Sapphire::World
{

class FadeBNpcTask : public Task
{
public:
  FadeBNpcTask( uint64_t delayTime, Entity::BNpcPtr bnpc );

  void onQueue() override;
  void execute() override;
  std::string toString() override;
private:
  Entity::BNpcPtr m_pBNpc;
};

}
