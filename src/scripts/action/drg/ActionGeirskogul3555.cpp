#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::StatusEffect;

class ActionGeirskogul3555 :
  public ScriptAPI::ActionScript
{
public:
  ActionGeirskogul3555() :
    ScriptAPI::ActionScript( 3555 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    if( pPlayer->gaugeDrgGetDragonState( Common::DrgState::BloodOfTheDragon ) )
    {
      if( pPlayer->gaugeDrgGetEyes() == 2 )
      {
        pPlayer->gaugeDrgSetDragonState( Common::DrgState::LifeOfTheDragon );
        pPlayer->gaugeDrgSetDragonTimer( 30000, true );
        pPlayer->setVisualEffect( 34, true );
        pPlayer->gaugeDrgSetEyes( 0 );
      }
    }
    else
    {
      action.disableGenericHandler();
      action.interrupt();
    }
  }
};

EXPOSE_SCRIPT( ActionGeirskogul3555 );