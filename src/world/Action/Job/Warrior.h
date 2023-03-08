#pragma once

#include <Common.h>
#include "ForwardsZone.h"
#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

namespace Sapphire::World::Action
{
  class Warrior
  {
    public:
      static void onAction( Entity::Player& player, Action& action );

    private:
      static void handleWrath( Entity::Player& player, Action& action );
  };
}