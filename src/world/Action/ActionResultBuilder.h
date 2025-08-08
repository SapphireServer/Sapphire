#pragma once

#include <ForwardsZone.h>
#include <Common.h>
#include "ActionLut.h"

namespace Sapphire::World::Action
{
  class ActionResultBuilder
  {
  public:
    ActionResultBuilder( Entity::CharaPtr source, uint32_t actionId, float aggroModifier, uint32_t resultId, uint16_t requestId );

    void heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount,
               Common::CalcResultType hitType = Common::CalcResultType::TypeRecoverMp,
               Common::ActionResultFlag flag = Common::ActionResultFlag::None );

    void restoreMP( Entity::CharaPtr& effectTarget, Entity::CharaPtr& restoringTarget, uint32_t amount,
                    Common::ActionResultFlag flag = Common::ActionResultFlag::None );

    void damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount,
                 Common::CalcResultType hitType = Common::CalcResultType::TypeDamageHp,
                 Common::ActionResultFlag flag = Common::ActionResultFlag::None );

    void startCombo( Entity::CharaPtr& target, uint16_t actionId );

    void comboSucceed( Entity::CharaPtr& target );

    void applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param, bool shouldOverride = false );
    void applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param,
                            const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag = 0, bool statusToSource = false, bool shouldOverride = false );
    void applyStatusEffectSelf( uint16_t statusId, uint32_t duration, uint8_t param, bool shouldOverride = false );
    void applyStatusEffectSelf( uint16_t statusId, uint32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers,
                                uint32_t flag = 0, bool shouldOverride = false );
    void replaceStatusEffect( Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param,
                              const std::vector< StatusModifier >& modifiers, uint32_t flag = 0, bool statusToSource = false );
    void replaceStatusEffectSelf( Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint16_t statusId, uint32_t duration, uint8_t param,
                                  const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag = 0 );
    void mount( Entity::CharaPtr& target, uint16_t mountId );

    void sendActionResults( const std::vector< Entity::CharaPtr >& targetList );

  private:
    void addResultToActor( Entity::CharaPtr& chara, ActionResultPtr result );

    Network::Packets::FFXIVPacketBasePtr createActionResultPacket( const std::vector< Entity::CharaPtr >& targetList );

  private:
    uint32_t m_actionId;
    float m_aggroModifier;
    uint16_t m_requestId;
    uint32_t m_resultId;

    bool m_applyHealAggro = true;
    bool m_applyStatusAggro = true;
    Entity::CharaPtr m_sourceChara;
    std::unordered_map< Entity::CharaPtr, std::vector< ActionResultPtr > > m_actorResultsMap;
  };

}