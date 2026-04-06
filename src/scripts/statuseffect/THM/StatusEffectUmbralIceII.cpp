#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <StatusEffect/StatusEffect.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectUmbralIceII : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectUmbralIceII() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::UmbralIceIIStatus )
  {
  }

  static constexpr int32_t RefreshBonus = 1400;
  static constexpr int32_t FireDamageModifier = -20;
  static constexpr int32_t FireSpellMpCostMultiplier = -75;

  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    auto pStatus = actor.getStatusEffectById( ActionStatus::UmbralIceIIStatus );
    if( !pStatus )
      return;

    pStatus->setModifier( Common::ParamModifier::MpRestRegenPercent, RefreshBonus );
    pStatus->setModifier( Common::ParamModifier::ElementalFireDamagePercent, FireDamageModifier );
    pStatus->setModifier( Common::ParamModifier::ElementalFireMpCostPercent, FireSpellMpCostMultiplier );
  }
    
};

EXPOSE_SCRIPT( StatusEffectUmbralIceII );