#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionStormsEye45 :
  public ScriptAPI::ActionScript
{
public:
  ActionStormsEye45() :
    ScriptAPI::ActionScript( 45 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    assert( pPlayer );
    uint8_t ib = pPlayer->gaugeWarGetIb();
    ib = std::min( 100, ib + 10 );
    pPlayer->gaugeWarSetIb( ib );
    pPlayer->sendActorGuage();
  }
};

EXPOSE_SCRIPT( ActionStormsEye45 );