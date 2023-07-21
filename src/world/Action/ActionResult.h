#pragma once

#include <ForwardsZone.h>
#include <Common.h>
#include "ActionLut.h"

namespace Sapphire::World::Action
{
  /*!
   * @brief A container for the computed result of an effect on a single actor. Used to apply damage/healing dealt
   * at a later point in time.
   */
  class ActionResult
  {
  public:
    explicit ActionResult( Entity::CharaPtr target, uint64_t delayMs );

    void damage( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void restoreMP( uint32_t amount, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void startCombo( uint16_t actionId );
    void comboSucceed();
    void applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param, bool shouldOverride );
    void applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param,
                            std::vector< World::Action::StatusModifier > modifiers, uint32_t flag, bool canApplyMultipleTimes, bool shouldOverride );
    void applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, bool shouldOverride );
    void applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, std::vector< World::Action::StatusModifier > modifiers,
                                uint32_t flag, bool shouldOverride );
    void mount( uint16_t mountId );

    Entity::CharaPtr getTarget() const;

    uint64_t getDelay();

    const Common::CalcResultParam& getCalcResultParam() const;
    const Sapphire::StatusEffect::StatusEffectPtr getStatusEffect() const;

    void execute();

  private:
    uint64_t m_delayMs;

    Entity::CharaPtr m_target;

    Common::CalcResultParam m_result;

    bool m_bOverrideStatus { false };
    Sapphire::StatusEffect::StatusEffectPtr m_pStatus;

  };

  using ActionResultList = std::vector< ActionResultPtr >;
}