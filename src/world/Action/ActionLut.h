#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>
#include "Common.h"

namespace Sapphire::World::Action
{
  struct StatusModifier
  {
    Common::ParamModifier modifier;
    int32_t value;
  };

  struct StatusEntry
  {
    uint16_t id;
    uint32_t duration;
    uint32_t maxDuration;
    uint8_t statusRefreshPolicy;
    uint32_t flag;
    std::vector< StatusModifier > modifiers;
  };

  struct StatusEffect
  {
    std::vector< StatusEntry > caster;
    std::vector< StatusEntry > target;
  };

  struct ActionEntry
  {
    uint16_t potency;
    uint16_t comboPotency;
    uint16_t flankPotency;
    uint16_t frontPotency;
    uint16_t rearPotency;
    uint16_t curePotency;
    uint16_t restoreMPPercentage;
    std::vector< uint32_t > nextCombo;
    Common::TargetFilter targetFilter;
    StatusEffect statuses;
  };

  class ActionLut
  {
  public:
    using Lut = std::unordered_map< uint16_t, ActionEntry >;

    static bool validEntryExists( uint16_t actionId );
    static const ActionEntry& getEntry( uint16_t actionId );

    static Lut m_actionLut;
  };

  Sapphire::Common::StatusRefreshPolicy getStatusRefreshPolicy( uint8_t statusRefreshPolicy, bool sameSource );
}
