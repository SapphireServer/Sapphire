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

    void damage( uint32_t amount, Common::ActionHitSeverityType severity );
    void heal( uint32_t amount, Common::ActionHitSeverityType severity );

    Entity::CharaPtr getTarget() const;

    uint32_t getValue() const;

    uint64_t getDelay();

    void setParam( uint8_t param );

    Common::EffectEntry buildEffectEntry() const;

    void execute();

  private:
    uint64_t m_delayMs;

    Entity::CharaPtr m_target;

    Common::ActionHitSeverityType m_severity;
    Common::ActionEffectType m_type;

    uint32_t m_value;
    uint8_t m_param;
  };
}

#endif //SAPPHIRE_EFFECTRESULT_H
