#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <StatusEffect/StatusEffect.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectUmbralIce : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  static constexpr int32_t RefreshBonus = 650;
  static constexpr int32_t FireDamageModifier = -10;
  static constexpr int32_t FireSpellMpCostMultiplier = -50;

  StatusEffectUmbralIce() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::UmbralIceStatus )
  {
  }

  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    auto pStatus = actor.getStatusEffectById( ActionStatus::UmbralIceStatus );
    if( !pStatus )
      return;

    pStatus->setModifier( Common::ParamModifier::MpRestRegenPercent, RefreshBonus );
    pStatus->setModifier( Common::ParamModifier::ElementalFireDamagePercent, FireDamageModifier);
    pStatus->setModifier( Common::ParamModifier::ElementalFireMpCostPercent, FireSpellMpCostMultiplier);
  }
    
};

EXPOSE_SCRIPT( StatusEffectUmbralIce );