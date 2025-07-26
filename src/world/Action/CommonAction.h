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
    ButchersBlock = 47,
    HeavyShot = 97,
    StraightShot = 98,
    VenomousBite = 100,
    Shadowbind = 108,
    Bloodletter = 110
  };

  enum ActionStatus
  {
    Bind = 13,
    Defiance = 91,
    Unchained = 92,
    Wrath = 93,
    WrathII = 94,
    WrathIII = 95,
    WrathIV = 96,
    Infuriated = 97,
    StraightShotReady = 122,
    VenomousBiteStatus = 124,
    StraightShotBuff = 130,
    InnerBeast = 411,
    Deliverance = 729
  };
}