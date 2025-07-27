#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTheWanderersMinuet : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTheWanderersMinuet() : Sapphire::ScriptAPI::ActionScript( TheWanderersMinuet )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( pSource->hasStatusEffect( TheWanderersMinuetStatus ) )
      pSource->removeSingleStatusEffectById( TheWanderersMinuetStatus );
    else
      pActionBuilder->applyStatusEffectSelf( TheWanderersMinuetStatus, 0, 0, { StatusModifier{ Common::ParamModifier::DamageDealtPercent, 30 } }, 5, false );
  }
};

EXPOSE_SCRIPT( ActionTheWanderersMinuet );