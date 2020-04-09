#ifndef SAPPHIRE_EFFECTRESULT_H
#define SAPPHIRE_EFFECTRESULT_H

#include <ForwardsZone.h>
#include <Common.h>

#include "StatusEffect/StatusEffect.h"

namespace Sapphire::World::Action
{
  /*!
   * @brief A container for the computed result of an effect on a single actor. Used to apply damage/healing dealt
   * at a later point in time.
   */
  class EffectResult
  {
  public:
    explicit EffectResult( Entity::CharaPtr target, Entity::CharaPtr source, uint64_t delayMs );
    explicit EffectResult( Entity::CharaPtr target, uint64_t delayMs );

    void dodge( Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void damage( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void blockedDamage( uint32_t amount, uint16_t rate, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void parriedDamage( uint32_t amount, uint16_t rate, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void restoreMP( uint32_t amount, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void startCombo( uint16_t actionId );
    void comboSucceed();
    void applyStatusEffect( uint16_t statusId, uint32_t duration, uint16_t param );
    void applyStatusEffect( StatusEffect::StatusEffectPtr pStatusEffect );
    void statusNoEffect( uint16_t statusId );
    void mount( uint16_t mountId );
    void provoke( );

    Entity::CharaPtr getSource() const;
    Entity::CharaPtr getTarget() const;

    uint32_t getValue() const;

    uint64_t getDelay();

    Common::EffectEntry buildEffectEntry() const;

    void execute();

  private:
    uint64_t m_delayMs;

    Entity::CharaPtr m_source;
    Entity::CharaPtr m_target;

    Common::ActionEffectType m_type;

    uint8_t m_param0;
    uint8_t m_param1;
    uint16_t m_param2;

    uint32_t m_value;
    uint32_t m_statusDuration;
    Common::ActionEffectResultFlag m_flag;

    StatusEffect::StatusEffectPtr m_pPreBuiltStatusEffect;
  };
}

#endif //SAPPHIRE_EFFECTRESULT_H
