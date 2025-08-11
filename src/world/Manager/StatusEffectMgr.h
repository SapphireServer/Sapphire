#pragma once

#include "ForwardsZone.h"
#include <Common.h>
#include "Action/ActionLut.h"

namespace Sapphire::World::Manager
{
  class StatusEffectMgr
  {
  public:
    StatusEffectMgr() = default;
    ~StatusEffectMgr() = default;

    void damage( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, uint32_t amount );
    void heal( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, uint32_t amount );
    void restoreMP( Entity::CharaPtr pTarget, uint32_t amount );
    void applyStatusEffect( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, uint32_t id, int32_t duration, uint8_t param,
                            const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool shouldOverride );
    void applyStatusEffectSelf( Entity::CharaPtr pSource, uint32_t id, int32_t duration, uint8_t param, 
                                const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool shouldOverride );
    void replaceStatusEffect( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id, 
                              int32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag );
    void replaceStatusEffectSelf( Entity::CharaPtr pSource, Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id, 
                                  int32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag );

  private:
    void applyStatusEffect( Entity::CharaPtr pTarget, Sapphire::StatusEffect::StatusEffectPtr& pStatus, bool shouldOverride );
    void replaceStatusEffect( Entity::CharaPtr pTarget, Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, Sapphire::StatusEffect::StatusEffectPtr& pNewStatus );
    void splitAggroApplication( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, float aggro );
  };
}