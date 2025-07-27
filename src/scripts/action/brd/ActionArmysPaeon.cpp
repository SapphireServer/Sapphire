#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Chara.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionArmysPaeon : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionArmysPaeon() : Sapphire::ScriptAPI::ActionScript( ArmysPaeon )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder )
      return;

    if( pSource->getMp() == 0 )
      return;

    if( pSource->hasStatusEffect( ArmysPaeonAura ) )
      pSource->removeSingleStatusEffectById( ArmysPaeonAura );
    else
      pActionBuilder->applyStatusEffectSelf( ArmysPaeonAura, 0, 0, {}, 5, false );
  }
};

EXPOSE_SCRIPT( ActionArmysPaeon );