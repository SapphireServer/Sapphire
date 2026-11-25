#pragma once

#include <cstdint>

#include "EventSignal.h"

namespace Sapphire::Common
{
  enum class ClassJob : uint8_t;
}

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

  struct PlayerJobLevelChanged
  {
    Entity::Player& player;
    Common::ClassJob classJob;
    uint8_t previousLevel;
    uint8_t level;
  };

  // Reports recorded quest completion after the reward attempt has finished.
  struct QuestCompleted
  {
    Entity::Player& player;
    uint16_t questId;
  };

  struct PlayerAddedToBlacklist
  {
    Entity::Player& source;
    Entity::Player& target;
  };

  struct PlayerEvents
  {
    EventSignal< PlayerDied > died;
    EventSignal< NpcKillCredited > npcKillCredited;
    EventSignal< PlayerJobLevelChanged > jobLevelChanged;
    EventSignal< PlayerTerritoryChanged > territoryChanged;
    EventSignal< QuestCompleted > questCompleted;
    EventSignal< PlayerAddedToBlacklist > addedToBlacklist;
  };
}
