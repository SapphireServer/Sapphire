#ifndef SAPPHIRE_ACTIONLUT_H
#define SAPPHIRE_ACTIONLUT_H

#include <unordered_map>

namespace Sapphire::World::Action
{
  struct ActionEntry
  {
    uint16_t damagePotency;
    uint16_t damageComboPotency;
    uint16_t damageDirectionalPotency;
    uint16_t healPotency;
    uint16_t selfHealPotency;
    uint16_t selfStatus;
    uint16_t selfStatusDuration;
    uint16_t selfStatusParam;
    uint16_t targetStatus;
    uint16_t targetStatusDuration;
    uint16_t targetStatusParam;
    uint16_t gainMPPercentage;
    uint16_t gainJobResource;
  };

  class ActionLut
  {
  public:
    using Lut = std::unordered_map< uint16_t, ActionEntry >;

    static bool validEntryExists( uint16_t actionId );
    static const ActionEntry& getEntry( uint16_t actionId );

    static Lut m_actionLut;
  };
}

#endif //SAPPHIRE_ACTIONLUT_H
