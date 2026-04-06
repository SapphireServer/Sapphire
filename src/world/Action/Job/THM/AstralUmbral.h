#pragma once

#include <ForwardsZone.h>
#include <cstdint>

namespace Sapphire::World::Action
{
  class ActionResultBuilder;

  class THM
  {
  public:
    static constexpr float AstralUmbralCastTimeReduction = 0.5f;
    static Sapphire::StatusEffect::StatusEffectPtr getAstralFire( Entity::CharaPtr& pSource);
    static Sapphire::StatusEffect::StatusEffectPtr getUmbralIce( Entity::CharaPtr& pSource);
    
    static void applyAstralFire( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder );
    static void applyUmbralIce( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder );

    static void setAstralFire( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder, uint8_t tier );
    static void setUmbralIce( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder, uint8_t tier );

  };
}
