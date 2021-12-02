#pragma once

#include <memory>
#include <vector>
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{
  class FriendListMgr
  {
  public:
    FriendListMgr() = default;

    bool onInviteCreate( Entity::Player& source, Entity::Player& target );

    bool onInviteAccept( Entity::Player& source, Entity::Player& target );
    bool onInviteDecline( Entity::Player& source, Entity::Player& target );

    bool onRemoveFriend( Entity::Player& source, Entity::Player& target );
    bool onAssignGroup( Entity::Player& source, Entity::Player& target, uint8_t group );

  private:
    ptrdiff_t getEntryIndex( Entity::Player& source, uint64_t characterId );
  };
}
