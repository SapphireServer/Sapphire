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

    bool onAddCharacter( Entity::Player& source, const std::string& targetName );
    bool onRemoveCharacter( Entity::Player& source, const std::string& targetName );

    bool onGetBlacklistPage( Entity::Player& source, uint8_t key, uint8_t nextIdx );

    bool isBlacklisted( Entity::Player& source, const Entity::Player& target ) const;

   private:
    ptrdiff_t getEntryIndex( Entity::Player& source, uint64_t characterId ) const;

    void sendAddResultPacket( Entity::Player& source, const Entity::PlayerPtr pTarget, uint32_t result );
    void sendRemoveResultPacket( Entity::Player& source, const Entity::PlayerPtr pTarget, uint32_t result );
  };
}
