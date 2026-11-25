#pragma once

#include <cstdint>

#include "EventSignal.h"

namespace Sapphire::Common
{
  enum class ClassJob : uint8_t;
  enum WarpType : uint8_t;
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

  // Published after warp setup, before FINISH_LOADING updates the player's loading state.
  struct PlayerWarpFinished
  {
    Entity::Player& player;
    Common::WarpType warpType;
  };

  struct NpcKillCredited
  {
    Entity::Player& player;
    Entity::BNpc& npc;
  };

  // Published after class/job setup, including when the same job is reapplied.
  struct PlayerClassJobUpdated
  {
    Entity::Player& player;
    Common::ClassJob previousClassJob;
    Common::ClassJob classJob;
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

  // Published after each completion flag write, including writes of the existing value.
  struct QuestCompletionUpdated
  {
    Entity::Player& player;
    uint32_t questId;
    bool completed;
  };

  struct PlayerAddedToBlacklist
  {
    Entity::Player& source;
    Entity::Player& target;
  };

  struct ActiveQuestChanged
  {
    enum class Kind
    {
      Added,
      Updated,
      Removed
    };

    Entity::Player& player;
    uint16_t questId;
    uint8_t slot;
    Kind kind;
  };

  struct PlayerEvents
  {
    EventSignal< PlayerDied > died;
    EventSignal< NpcKillCredited > npcKillCredited;
    EventSignal< PlayerClassJobUpdated > classJobUpdated;
    EventSignal< PlayerJobLevelChanged > jobLevelChanged;
    EventSignal< PlayerTerritoryChanged > territoryChanged;
    EventSignal< PlayerWarpFinished > warpFinished;
    EventSignal< QuestCompleted > questCompleted;
    EventSignal< QuestCompletionUpdated > questCompletionUpdated;
    EventSignal< ActiveQuestChanged > activeQuestChanged;
    EventSignal< PlayerAddedToBlacklist > addedToBlacklist;
  };
}
