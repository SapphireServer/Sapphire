#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>


using namespace Sapphire;

class ActionBloodOfTheDragon3553 :
  public ScriptAPI::ActionScript
{
public:
  ActionBloodOfTheDragon3553() :
    ScriptAPI::ActionScript( 3553 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    pPlayer->gaugeDrgSetDragonTimer( 30000, true );
    pPlayer->gaugeDrgSetDragonState( Common::DrgState::BloodOfTheDragon );
  }
};

EXPOSE_SCRIPT( ActionBloodOfTheDragon3553 );