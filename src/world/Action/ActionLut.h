#ifndef SAPPHIRE_ACTIONLUT_H
#define SAPPHIRE_ACTIONLUT_H

#include <unordered_map>
#include <Common.h>

using namespace Sapphire::Common;

namespace Sapphire::World::Action
{
  struct ActionEntry
  {
  public:
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
  private:
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
  public:
    ActionEntry() = default;
    ActionEntry( uint16_t dp, uint16_t dcp, uint16_t ddp, uint16_t hp, uint16_t ss, uint32_t ssd, uint16_t ssp, uint16_t ts, uint32_t tsd, uint16_t tsp, uint8_t be, uint8_t br, uint32_t bdu32 );
    uint32_t getRawBonusData() const;
    uint8_t getDamageFallOffPercentage() const; // as the result percentage for 2nd (or more) victims, not the percentage to subtract from 100%
    uint16_t getSelfHealPotency() const;
    uint16_t getMPGainPercentage() const;
    ClassJob getAffectedJob() const;
    uint8_t getJobResourceGain() const;
    uint16_t getJobTimerGain() const;
    uint16_t getCritRateBonus() const;
    uint16_t getDirectHitRateBonus() const;
  };

  struct StatusEffectEntry
  {
  private:
    uint32_t effectType;
    int32_t effectValue1;
    int32_t effectValue2;
    int32_t effectValue3;
    int32_t effectValue4;
  public:
    StatusEffectEntry() = default;
    StatusEffectEntry( uint32_t type, int32_t v1, int32_t v2, int32_t v3, int32_t v4 );
    void init( StatusEffectType type, int32_t v1, int32_t v2, int32_t v3, int32_t v4 );
    StatusEffectType getType() const;
    ActionTypeFilter getActionTypeFilter() const;
    int32_t getMPRestoreTick() const;
    int32_t getDotHotPotency() const;
    int32_t getOutgoingDamageMultiplier() const;
    int32_t getIncomingDamageMultiplier() const;
    int32_t getOutgoingHealMultiplier() const;
    int32_t getIncomingHealMultiplier() const;
    int32_t getPotencyMultiplier() const;
    int32_t getGCDBasedMPRestorePercentage() const;
    int32_t getRemainingCharges() const; // -1 is infinite charges
    void setRemainingCharges( int32_t charges );
    int32_t getRemainingShield() const;
    void setRemainingShield( int32_t shield );
    int32_t getHasteBonus() const;
    int32_t getBlockRateBonus() const;
    int32_t getParryRateBonus() const;
    int32_t getCritRateBonus() const;
    int32_t getDirectHitRateBonus() const;
    StatusEffectTriggerResult getTriggerResult() const;
    int32_t getTriggerValue() const;
    ActionTypeFilter getTriggerDamageType() const;

    bool canApplyToAction( uint32_t actionId, uint8_t actionCategory ) const;
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
