#ifndef SAPPHIRE_EFFECTRESULT_H
#define SAPPHIRE_EFFECTRESULT_H

#include <ForwardsZone.h>
#include <Common.h>

namespace Sapphire::World::Action
{
  /*!
   * @brief A container for the computed result of an effect on a single actor. Used to apply damage/healing dealt
   * at a later point in time.
   */
  class EffectResult
  {
  public:
    explicit EffectResult( Entity::CharaPtr target, uint64_t delayMs );

    void damage( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void restoreMP( uint32_t amount, Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );
    void startCombo( uint16_t actionId );
    void comboSucceed();
    void applyStatusEffect( uint16_t statusId, uint8_t param );

    Entity::CharaPtr getTarget() const;

    uint32_t getValue() const;

    uint64_t getDelay();

    Common::EffectEntry buildEffectEntry() const;

    void execute();

  private:
    uint64_t m_delayMs;

    Entity::CharaPtr m_target;

    Common::ActionHitSeverityType m_severity;
    Common::ActionEffectType m_type;

    uint32_t m_value;
    uint8_t m_param;
    Common::ActionEffectResultFlag m_flag;
  };
}

#endif //SAPPHIRE_EFFECTRESULT_H
