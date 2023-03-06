#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionSonicThrust7397 :
  public ScriptAPI::ActionScript
{
public:
  ActionSonicThrust7397() :
    ScriptAPI::ActionScript( 7397 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();

    if( pPlayer->getLastComboActionId() == 86 )
    {
      if( pPlayer->gaugeDrgGetDragonState( Common::DrgState::BloodOfTheDragon ) )
      {
        uint16_t dragonTimer = pPlayer->gaugeDrgGetDragonTimer();
        dragonTimer = std::min( 30000, dragonTimer + 10000 );
        pPlayer->gaugeDrgSetDragonTimer( dragonTimer, true );
      }
    }
  }
};

EXPOSE_SCRIPT( ActionSonicThrust7397 );