#pragma once

#include "ForwardsZone.h"
#include <Common.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace Sapphire::World::Action
{
  class Archer
  {
  public:
    static void onAction( Entity::Player& player, Action& action );
  };
}