#pragma once

#include <cstdint>

#include "EventSignal.h"

namespace Sapphire::Entity
{
  class BNpc;
  class Player;
}

namespace Sapphire::World::Notifications
{
  struct PlayerDied
  {
    Entity::Player& player;
  };

  // Published after zone-in setup. The client may still be loading.
  struct PlayerTerritoryChanged
  {
    Entity::Player& player;
    uint32_t previousTerritoryId;
    uint32_t territoryId;
  };

  struct NpcKillCredited
  {
    Entity::Player& player;
    Entity::BNpc& npc;
  };

  struct PlayerEvents
  {
    EventSignal< PlayerDied > died;
    EventSignal< NpcKillCredited > npcKillCredited;
    EventSignal< PlayerTerritoryChanged > territoryChanged;
  };
}
