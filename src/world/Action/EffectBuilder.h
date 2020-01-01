#ifndef SAPPHIRE_EFFECTBUILDER_H
#define SAPPHIRE_EFFECTBUILDER_H

#include <ForwardsZone.h>
#include <Common.h>

namespace Sapphire::World::Action
{
  class EffectBuilder
  {
  public:
    EffectBuilder( Entity::CharaPtr source, uint32_t actionId, uint16_t sequence );


    void healTarget( Entity::CharaPtr& target, uint32_t amount,
                     Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalHeal );

    void selfHeal( Entity::CharaPtr& target, Entity::CharaPtr& source, uint32_t amount,
                     Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalHeal );

    void damageTarget( Entity::CharaPtr& target, uint32_t amount,
                       Common::ActionHitSeverityType severity = Common::ActionHitSeverityType::NormalDamage );

    void startCombo( Entity::CharaPtr& target, uint16_t actionId );

    void comboVisualEffect( Entity::CharaPtr& target );

    void buildAndSendPackets();


  private:
    std::shared_ptr< std::vector< EffectResultPtr > > getResultList( Entity::CharaPtr& chara );

    uint64_t getResultDelayMs();

  private:
    uint32_t m_actionId;
    uint16_t m_sequence;

    Entity::CharaPtr m_sourceChara;
    std::unordered_map< uint32_t, std::shared_ptr< std::vector< EffectResultPtr > > > m_resolvedEffects;
  };

}

#endif //SAPPHIRE_EFFECTBUILDER_H
