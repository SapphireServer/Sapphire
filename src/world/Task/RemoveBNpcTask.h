#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"

namespace Sapphire::World
{

class RemoveBNpcTask : public Task
{
public:
  RemoveBNpcTask( uint64_t delayTime, Entity::BNpcPtr bnpc );

  void onQueue() override;
  void execute() override;
  std::string toString() override;
private:
  Entity::BNpcPtr m_pBNpc;
};

template< typename... Args >
std::shared_ptr< RemoveBNpcTask > makeRemoveBNpcTask( Args... args )
{
  return std::make_shared< RemoveBNpcTask >( args... );
}

}
