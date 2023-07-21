#pragma once

#include <ForwardsZone.h>
#include <Common.h>
#include "ActionLut.h"

namespace Sapphire::World::Action
{
  class ActionResultBuilder
  {
  public:
    ActionResultBuilder( Entity::CharaPtr source, uint32_t actionId, uint32_t resultId, uint16_t requestId );

    void heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount,
               Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalHeal,
               Common::ActionResultFlag flag = Common::ActionResultFlag::None );

    void restoreMP( Entity::CharaPtr& effectTarget, Entity::CharaPtr& restoringTarget, uint32_t amount,
                    Common::ActionResultFlag flag = Common::ActionResultFlag::None );

    void damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount,
                 Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalDamage,
                 Common::ActionResultFlag flag = Common::ActionResultFlag::None );

    void startCombo( Entity::CharaPtr& target, uint16_t actionId );

    void comboSucceed( Entity::CharaPtr& target );

    void applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param, bool shouldOverride = false );
    void applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param,
                            std::vector< World::Action::StatusModifier > modifiers, uint32_t flag = 0, bool canApplyMultipleTimes = false, bool shouldOverride = false );
    void applyStatusEffectSelf( uint16_t statusId, uint32_t duration, uint8_t param, bool shouldOverride = false );
    void applyStatusEffectSelf( uint16_t statusId, uint32_t duration, uint8_t param, std::vector< World::Action::StatusModifier > modifiers,
                                uint32_t flag = 0, bool shouldOverride = false );

    void mount( Entity::CharaPtr& target, uint16_t mountId );

    void sendActionResults( const std::vector< Entity::CharaPtr >& targetList );

  private:
    void addResultToActor( Entity::CharaPtr& chara, ActionResultPtr result );

    Network::Packets::FFXIVPacketBasePtr createActionResultPacket( const std::vector< Entity::CharaPtr >& targetList );

  private:
    uint32_t m_actionId;
    uint16_t m_requestId;
    uint32_t m_resultId;

    Entity::CharaPtr m_sourceChara;
    std::unordered_map< Entity::CharaPtr, std::vector< ActionResultPtr > > m_actorResultsMap;
  };

}