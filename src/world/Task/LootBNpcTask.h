#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include "Task.h"

namespace Sapphire::World
{
  class LootBNpcTask : public Task
  {
  public:
    LootBNpcTask( Entity::Player& player, std::string lootTable, uint64_t delayTime );

    void onQueue() override;
    void execute() override;
    std::string toString() override;

  private:
    uint32_t m_playerId;
    std::string m_lootTable;
  };

  template< typename... Args >
  std::shared_ptr< LootBNpcTask > makeLootBNpcTask( Args... args )
  {
    return std::make_shared< LootBNpcTask >( args... );
  }
}
