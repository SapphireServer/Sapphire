#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Sapphire::World::Action
{
  enum ActionSkill
  {
    SkullSunder = 35,
    Maim = 37,
    StormsPath = 42,
    StormsEye = 45,
    ButchersBlock = 47
  };

  enum ActionStatus
  {
    Defiance = 91,
    Unchained = 92,
    Wrath = 93,
    WrathII = 94,
    WrathIII = 95,
    WrathIV = 96,
    Infuriated = 97,
    InnerBeast = 411,
    Deliverance = 729
  };
}