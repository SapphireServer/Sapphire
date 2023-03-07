#pragma once

#include <ForwardsZone.h>
#include <Common.h>

namespace Sapphire::World::Action
{
  class EffectBuilder
  {
  public:
    EffectBuilder( Entity::CharaPtr source, uint32_t actionId, uint16_t requestId );

    void heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount,
               Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalHeal,
               Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );

    void restoreMP( Entity::CharaPtr& effectTarget, Entity::CharaPtr& restoringTarget, uint32_t amount,
                    Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );

    void damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount,
                 Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalDamage,
                 Common::ActionEffectResultFlag flag = Common::ActionEffectResultFlag::None );

    void startCombo( Entity::CharaPtr& target, uint16_t actionId );

    void comboSucceed( Entity::CharaPtr& target );

    void applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint8_t param, bool forSelf = false );

    void mount( Entity::CharaPtr& target, uint16_t mountId );

    void buildAndSendPackets( const std::vector< Entity::CharaPtr >& targetList );

  private:
    void addResultToActor( Entity::CharaPtr& chara, EffectResultPtr result );

    uint64_t getResultDelayMs();

    Network::Packets::FFXIVPacketBasePtr buildNextEffectPacket( const std::vector< Entity::CharaPtr >& targetList );

  private:
    uint32_t m_actionId;
    uint16_t m_requestId;

    Entity::CharaPtr m_sourceChara;
    std::unordered_map< uint32_t, std::vector< EffectResultPtr > > m_actorEffectsMap;
  };

}