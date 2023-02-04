#pragma once

#include <cstdint>
#include <string>
#include "Task.h"

namespace Sapphire::World
{

  class DelayedEmnityTask : public Task
  {
  public:
    DelayedEmnityTask( uint64_t delayTime, Entity::BNpcPtr bnpc, Entity::CharaPtr chara, int32_t hateAmount );

    void onQueue() override;
    void execute() override;
    std::string toString() override;

  private:
    Entity::BNpcPtr m_pBNpc;
    Entity::CharaPtr m_pChara;
    int32_t m_hateAmount;
  };

}
