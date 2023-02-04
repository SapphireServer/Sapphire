#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>

namespace Sapphire::World
{

  class Task
  {
  public:
    Task( uint64_t delayTime );

    uint64_t getQueueTimeMs() const;
    uint64_t getDelayTimeMs() const;

    virtual void onQueue() = 0;
    virtual void execute() = 0;
    virtual std::string toString() = 0;

  protected:
    uint64_t m_delayTimeMs;
    uint64_t m_timeQueuedMs;
  };

}
