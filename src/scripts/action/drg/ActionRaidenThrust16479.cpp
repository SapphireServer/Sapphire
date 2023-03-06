#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_RAIDEN_THRUST_READY = 1863;

class ActionRaidenThrust16479 :
  public ScriptAPI::ActionScript
{
public:
  ActionRaidenThrust16479() :
    ScriptAPI::ActionScript( 16479 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_RAIDEN_THRUST_READY );
    if( effectEntry.second )
    {
      auto pPlayer = action.getSourceChara()->getAsPlayer();
      action.getSourceChara()->removeStatusEffect( effectEntry.first );

    }
    else
    {
      action.disableGenericHandler();
      action.interrupt();
    }
  }
};

EXPOSE_SCRIPT( ActionRaidenThrust16479 );