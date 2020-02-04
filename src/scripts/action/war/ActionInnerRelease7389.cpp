#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_INNER_RELEASE = 1177;

class ActionInnerRelease7389 :
  public ScriptAPI::ActionScript
{
public:
  ActionInnerRelease7389() :
    ScriptAPI::ActionScript( 7389 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    assert( pSource );

    World::Action::StatusEffectEntry effectEntry;
    effectEntry.effectType = static_cast< uint32_t >( Common::StatusEffectType::CritDHRateBonus );
    effectEntry.effectValue1 = static_cast< int32_t >( Common::ActionTypeFilter::Physical );
    effectEntry.effectValue2 = 100;
    effectEntry.effectValue3 = 100;
    auto pNewEffect = action.createStatusEffect( STATUS_ID_INNER_RELEASE, action.getSourceChara(), pSource, 10000, 3000 );
    pNewEffect->replaceEffectEntry( effectEntry );
    pNewEffect->setParam( 65436 );
    action.getEffectbuilder()->applyStatusEffect( pSource, action.getSourceChara(), pNewEffect, 0 );
  }
};

EXPOSE_SCRIPT( ActionInnerRelease7389 );