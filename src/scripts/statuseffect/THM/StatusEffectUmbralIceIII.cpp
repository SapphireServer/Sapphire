#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <StatusEffect/StatusEffect.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectUmbralIceIII : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  static constexpr int32_t RefreshBonus = 2900;
  static constexpr int32_t FireDamageModifier = -30;
  static constexpr int32_t FireSpellMpCostMultiplier = -75;

  StatusEffectUmbralIceIII() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::UmbralIceIIIStatus )
  {
  }

  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    auto pStatus = actor.getStatusEffectById( ActionStatus::UmbralIceIIIStatus );
    if( !pStatus )
      return;

    pStatus->setModifier( Common::ParamModifier::MpRestRegenPercent, RefreshBonus );
    pStatus->setModifier( Common::ParamModifier::ElementalFireDamagePercent, FireDamageModifier);
    pStatus->setModifier( Common::ParamModifier::ElementalFireMpCostPercent, FireSpellMpCostMultiplier);    
  }
    
};

EXPOSE_SCRIPT( StatusEffectUmbralIceIII );