#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_GALVANIZE = 297;
const uint16_t STATUS_ID_CATALYZE = 1918;

class ActionAdloquium185 :
  public ScriptAPI::ActionScript
{
public:
  ActionAdloquium185() :
    ScriptAPI::ActionScript( 185 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pTarget = action.getHitChara();
    if( pTarget )
    {
      // still pull out the lut entry to get potency values etc.
      auto lutEntry = action.getActionEntry();

      // do healing part
      auto heal = action.calcHealing( lutEntry.healPotency );
      heal.first = Math::CalcStats::applyHealingReceiveMultiplier( *pTarget, heal.first );
      action.getEffectbuilder()->heal( pTarget, pTarget, heal.first, heal.second );

      float shieldValue = heal.first * 1.25f;
      // apply new galvanize when not existing or larger than existing one
      auto oldEffect = pTarget->getStatusEffectById( STATUS_ID_GALVANIZE );
      if( !oldEffect.second || oldEffect.second->getEffectEntry().effectValue1 <= shieldValue )
      {
        World::Action::StatusEffectEntry effectEntry;
        effectEntry.effectType = static_cast< uint32_t >( Common::StatusEffectType::Shield );
        effectEntry.effectValue1 = static_cast< int32_t >( shieldValue );
        auto pNewEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_GALVANIZE, action.getSourceChara(), pTarget, 30000, 3000 );
        pNewEffect->replaceEffectEntry( effectEntry );
        action.getEffectbuilder()->applyStatusEffect( pTarget, action.getSourceChara(), pNewEffect );
      }
      else
        action.getEffectbuilder()->statusNoEffect( pTarget, STATUS_ID_GALVANIZE );

      if( heal.second == Common::ActionHitSeverityType::CritHeal )
      {
        // apply catalyze when crit, same rule as galvanize
        oldEffect = pTarget->getStatusEffectById( STATUS_ID_CATALYZE );
        if( !oldEffect.second || oldEffect.second->getEffectEntry().effectValue1 <= shieldValue )
        {
          World::Action::StatusEffectEntry effectEntry;
          effectEntry.effectType = static_cast< uint32_t >( Common::StatusEffectType::Shield );
          effectEntry.effectValue1 = static_cast< int32_t >( shieldValue ); // same shield value
          auto pNewEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_CATALYZE, action.getSourceChara(), pTarget, 30000, 3000 );
          pNewEffect->replaceEffectEntry( effectEntry );
          action.getEffectbuilder()->applyStatusEffect( pTarget, action.getSourceChara(), pNewEffect );
        }
        else
          action.getEffectbuilder()->statusNoEffect( pTarget, STATUS_ID_CATALYZE );
      }
    }
  }

  void onStart( Sapphire::World::Action::Action& action ) override
  {
    /*
      don't run generic action handler for this action.
      for simpler actions like cure 1 we only want to apply the freecure proc in script,
      and let the generic handler do the heal so we don't have to copy heal code into scripts,
      unless in cases like adlo, the healing result matters so we have to.
    */
    action.disableGenericHandler();
  }
};

EXPOSE_SCRIPT( ActionAdloquium185 );