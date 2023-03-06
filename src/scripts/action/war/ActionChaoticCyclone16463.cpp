#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

const uint16_t STATUS_ID_NASCENT_CHAOS = 1897;

class ActionChaoticCyclone16463 :
  public ScriptAPI::ActionScript
{
public:
  ActionChaoticCyclone16463() :
    ScriptAPI::ActionScript( 16463 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto effectEntry = action.getSourceChara()->getStatusEffectById( STATUS_ID_NASCENT_CHAOS );
    if( effectEntry.second )
    {
      action.getSourceChara()->removeStatusEffect( effectEntry.first );
    }
    else
    {
      action.disableGenericHandler();
      action.interrupt();
    }
  }
};

EXPOSE_SCRIPT( ActionChaoticCyclone16463 );