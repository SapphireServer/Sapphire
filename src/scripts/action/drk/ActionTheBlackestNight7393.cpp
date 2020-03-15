#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_THE_BLACKEST_NIGHT = 1178;

class ActionTheBlackestNight7393 :
  public ScriptAPI::ActionScript
{
public:
  ActionTheBlackestNight7393() :
    ScriptAPI::ActionScript( 7393 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pTarget = action.getHitChara();
    World::Action::StatusEffectEntry effectEntry;
    effectEntry.effectType = static_cast< uint32_t >( Common::StatusEffectType::Shield );
    effectEntry.effectValue1 = static_cast< int32_t >( ( 1.0 * pTarget->getMaxHp() ) * 0.25 );
    auto pNewEffect = Sapphire::StatusEffect::make_StatusEffect( STATUS_ID_THE_BLACKEST_NIGHT, action.getSourceChara(), pTarget, 7000, 3000 );
    pNewEffect->replaceEffectEntry( effectEntry );
    action.getEffectbuilder()->applyStatusEffect( pTarget, action.getSourceChara(), pNewEffect );
  }

  void onStart( Sapphire::World::Action::Action& action ) override
  {
    action.disableGenericHandler();
  }
};

EXPOSE_SCRIPT( ActionTheBlackestNight7393 );