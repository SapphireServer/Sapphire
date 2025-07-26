#pragma once

#include <Common.h>
#include "ForwardsZone.h"
#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

namespace Sapphire::World::Action
{
  class Bard
  {
    public:
      static void onAction( Entity::Player& player, Action& action );
  };
}