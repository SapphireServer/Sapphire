#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionSwiftsong : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSwiftsong() : Sapphire::ScriptAPI::ActionScript( Swiftsong )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( pSource->hasStatusEffect( SwiftsongAura ) )
      pSource->removeSingleStatusEffectById( SwiftsongAura );
    else
      pActionBuilder->applyStatusEffectSelf( SwiftsongAura, 0, 20, {}, 5, false );
  }
};

EXPOSE_SCRIPT( ActionSwiftsong );