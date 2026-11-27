#pragma once

#include <cstdint>

#include "EventSignal.h"
#include "Territory/InstanceContentState.h"

namespace Sapphire
{
  class InstanceContent;
  class QuestBattle;
}

namespace Sapphire::Entity
{
  class Chara;
  class Player;
}

namespace Sapphire::World::Notifications
{
  struct InstanceActorDied
  {
    InstanceContent& instance;
    Entity::Chara& actor;
  };

  struct InstanceCustomVarUpdated
  {
    InstanceContent& instance;
    uint32_t index;
    uint64_t value;
  };

  struct InstanceDirectorFlagsUpdated
  {
    InstanceContent& instance;
    uint8_t flags;
  };

  struct InstanceDirectorSequenceUpdated
  {
    InstanceContent& instance;
    uint8_t sequence;
  };

  // Reports the requested index and value after setVar queues its director packets.
  struct InstanceDirectorVarUpdated
  {
    InstanceContent& instance;
    uint8_t index;
    uint8_t value;
  };

  // Published after director cleanup. The player may be reinserted during a wipe.
  struct InstancePlayerRemoved
  {
    InstanceContent& instance;
    Entity::Player& player;
  };

  // Published after the encounter resets and return warps are queued.
  struct InstanceReset
  {
    InstanceContent& instance;
  };

  struct InstanceStateChanged
  {
    InstanceContent& instance;
    InstanceContentState previousState;
    InstanceContentState state;
  };

  // Published after the final victory scene and before the return warp.
  struct QuestBattleCompleted
  {
    QuestBattle& battle;
    Entity::Player& player;
  };

  struct InstanceEvents
  {
    EventSignal< InstanceActorDied > actorDied;
    EventSignal< InstanceCustomVarUpdated > customVarUpdated;
    EventSignal< InstanceDirectorFlagsUpdated > directorFlagsUpdated;
    EventSignal< InstanceDirectorSequenceUpdated > directorSequenceUpdated;
    EventSignal< InstanceDirectorVarUpdated > directorVarUpdated;
    EventSignal< InstancePlayerRemoved > playerRemoved;
    EventSignal< InstanceReset > reset;
    EventSignal< InstanceStateChanged > stateChanged;
    EventSignal< QuestBattleCompleted > questBattleCompleted;
  };
}
