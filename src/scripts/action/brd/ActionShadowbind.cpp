#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionShadowbind : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionShadowbind() : Sapphire::ScriptAPI::ActionScript( Shadowbind )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    pTarget->onActionHostile( pSource );

    pActionBuilder->applyStatusEffect( pTarget, Bind, 10000, 0, { }, 290, false, true );
  }
};

EXPOSE_SCRIPT( ActionShadowbind );