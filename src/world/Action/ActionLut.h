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
    uint16_t selfStatus;
    uint32_t selfStatusDuration;
    uint16_t selfStatusParam;
    uint16_t targetStatus;
    uint32_t targetStatusDuration;
    uint16_t targetStatusParam;
    uint8_t bonusEffect;
    uint8_t bonusRequirement;
    union
    {
      uint32_t bonusDataUInt32;
      struct
      {
        uint16_t bonusDataUInt16L;
        uint16_t bonusDataUInt16H;
      };
      struct
      {
        uint8_t bonusDataByte1;
        uint8_t bonusDataByte2;
        uint8_t bonusDataByte3;
        uint8_t bonusDataByte4;
      };
    };
  };

  struct StatusEffectEntry
  {
    uint32_t effectType;
    int32_t effectValue1;
    int32_t effectValue2;
    int32_t effectValue3;
    int32_t effectValue4;
  };

  class ActionLut
  {
  public:
    using Lut = std::unordered_map< uint16_t, ActionEntry >;
    using StatusEffectTable = std::unordered_map< uint16_t, StatusEffectEntry >;

    static bool validEntryExists( uint16_t actionId );
    static const ActionEntry& getEntry( uint16_t actionId );

    static bool validStatusEffectExists( uint16_t statusId );
    static const StatusEffectEntry& getStatusEffectEntry( uint16_t statusId );

    static Lut m_actionLut;
    static StatusEffectTable m_statusEffectTable;
  };
}

#endif //SAPPHIRE_ACTIONLUT_H
