#pragma once

#include <memory>
#include <vector>
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{
  class BlacklistMgr
  {
  public:
    BlacklistMgr() = default;

    bool onAddCharacter( Entity::Player& source, Entity::Player& target );
    bool onRemoveCharacter( Entity::Player& source, Entity::Player& target );

    bool onGetBlacklistPage( Entity::Player& source, uint8_t key, uint8_t nextIdx );

    bool isBlacklisted( Entity::Player& source, Entity::Player& target );

   private:
    ptrdiff_t getEntryIndex( Entity::Player& source, uint64_t characterId );
  };
}
