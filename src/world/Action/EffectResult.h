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
    explicit EffectResult( Entity::CharaPtr target, uint32_t delayMs );

    void damage( uint32_t amount, Common::ActionHitSeverityType severity );
    void heal( uint32_t amount, Common::ActionHitSeverityType severity );

    Entity::CharaPtr getTarget() const;

    uint32_t getValue() const;

    Common::EffectEntry buildEffectEntry() const;

  private:
    uint64_t m_runAfter;

    Entity::CharaPtr m_target;

    Common::ActionHitSeverityType m_severity;
    Common::ActionEffectType m_type;

    uint32_t m_value;
  };
}

#endif //SAPPHIRE_EFFECTRESULT_H
