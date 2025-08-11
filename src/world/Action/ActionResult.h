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
    explicit ActionResult( Entity::CharaPtr source, Entity::CharaPtr target );

    void damage( uint32_t amount, Common::CalcResultType hitType, uint8_t hitEffect, Common::ActionResultFlag flag = Common::ActionResultFlag::None, float aggroModifier = 1.0f );
    void heal( uint32_t amount, Common::CalcResultType hitType, uint8_t hitEffect, Common::ActionResultFlag flag = Common::ActionResultFlag::None, float aggroModifier = 1.0f );
    void restoreMP( uint32_t amount, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void startCombo( uint16_t actionId );
    void comboSucceed();
    void applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param, bool applyAggro, bool shouldOverride );
    void applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param,
                            const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool statusToSource, bool applyAggro, bool shouldOverride );
    void applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, bool applyAggro, bool shouldOverride );
    void applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers,
                                uint32_t flag, bool applyAggro, bool shouldOverride );
    void replaceStatusEffect( Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param,
                              const std::vector< StatusModifier >& modifiers, uint32_t flag, bool statusToSource, bool applyAggro );
    void replaceStatusEffectSelf( Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id, int32_t duration, uint8_t param,
                                  const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool applyAggro );
    void mount( uint16_t mountId );

    Entity::CharaPtr getTarget() const;

    const Common::CalcResultParam& getCalcResultParam() const;
    const Sapphire::StatusEffect::StatusEffectPtr getStatusEffect() const;

    void execute();

  private:
    Entity::CharaPtr m_source;
    Entity::CharaPtr m_target;

    Common::CalcResultParam m_result;
    float m_aggroModifier;
    bool m_applyStatusAggro { false };
    bool m_bShouldOverride { false };

    Sapphire::StatusEffect::StatusEffectPtr m_pStatus;
    Sapphire::StatusEffect::StatusEffectPtr m_pOldStatus;

    void splitAggroApplication( float aggro );
  };

  using ActionResultList = std::vector< ActionResultPtr >;
}