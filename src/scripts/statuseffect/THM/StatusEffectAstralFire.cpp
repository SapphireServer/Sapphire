#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <StatusEffect/StatusEffect.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectAstralFire : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  static constexpr int32_t FireDamageModifier = 40;
  static constexpr int32_t IceDamageModifier = -10;
  static constexpr int32_t FireSpellMpCostMultiplier = 100;
  static constexpr int32_t IceSpellMpCostMultiplier = -50;
  static constexpr int32_t RegenSuppression = 1;

  StatusEffectAstralFire() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::AstralFireStatus )
  {
  }  

  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    auto pStatus = actor.getStatusEffectById( ActionStatus::AstralFireStatus );
    if( !pStatus )
      return;

    pStatus->setModifier( Common::ParamModifier::MpRestRegenSuppressed, RegenSuppression );
    pStatus->setModifier( Common::ParamModifier::ElementalFireDamagePercent, FireDamageModifier);
    pStatus->setModifier( Common::ParamModifier::ElementalIceDamagePercent, IceDamageModifier);
    pStatus->setModifier( Common::ParamModifier::ElementalFireMpCostPercent, FireSpellMpCostMultiplier);
    pStatus->setModifier( Common::ParamModifier::ElementalIceMpCostPercent, IceSpellMpCostMultiplier);
  }
};

EXPOSE_SCRIPT( StatusEffectAstralFire );