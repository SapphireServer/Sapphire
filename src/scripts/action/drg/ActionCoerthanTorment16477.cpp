#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionCoerthanTorment16477 :
  public ScriptAPI::ActionScript
{
public:
  ActionCoerthanTorment16477() :
    ScriptAPI::ActionScript( 16477 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();

    if( pPlayer->getLastComboActionId() == 7397 )
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

EXPOSE_SCRIPT( ActionCoerthanTorment16477 );