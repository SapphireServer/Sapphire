#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"

namespace Sapphire::World
{

class ActionIntegrityTask : public Task
{
public:
  ActionIntegrityTask( uint32_t resultId, Entity::CharaPtr pTarget, uint64_t delayTime );

  void onQueue() override;
  void execute() override;
  std::string toString() override;

private:
  uint32_t m_resultId;
  Entity::CharaPtr m_pTarget;
};

template< typename... Args >
std::shared_ptr< ActionIntegrityTask > makeActionIntegrityTask( Args... args )
{
  return std::make_shared< ActionIntegrityTask >( args... );
}

}
