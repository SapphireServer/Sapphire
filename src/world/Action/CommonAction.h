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
    HawksEye = 99,
    VenomousBite = 100,
    RagingStrikes = 101,
    FlamingArrow = 102,
    MiserysEnd = 103,
    QuellingStrikes = 104,
    Swiftsong = 105,
    QuickNock = 106,
    Narrage = 107,
    Shadowbind = 108,
    BluntArrow = 109,
    Bloodletter = 110,
    WideVolley = 111,
    RepellingShot = 112,
    Windbite = 113,
    MagesBallad = 114,
    FoeRequiem = 115,
    ArmysPaeon = 116,
    RainOfDeath = 117,
    BattleVoice = 118
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
    HawksEyeStatus = 123,
    VenomousBiteStatus = 124,
    RagingStrikesStatus = 125,
    BarrageStatus = 128,
    WindbiteStatus = 129,
    StraightShotStatus = 130,
    DownpourOfDeath = 131,
    SwiftsongAura = 133,
    SwiftsongStatus = 134,
    MagesBalladAura = 135,
    MagesBalladStatus = 136,
    ArmysPaeonAura = 137,
    ArmysPaeonStatus = 138,
    FoeRequiemAura = 139,
    FoeRequiemStatus = 140,
    BattleVoiceStatus = 141,
    FlamingArrowStatus = 249,
    InnerBeast = 411,
    Deliverance = 729
  };
}