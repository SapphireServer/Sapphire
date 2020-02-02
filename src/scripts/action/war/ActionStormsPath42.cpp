#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionStormsPath42 :
  public ScriptAPI::ActionScript
{
public:
  ActionStormsPath42() :
    ScriptAPI::ActionScript( 42 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    assert( pPlayer );
    uint8_t ib = pPlayer->gaugeWarGetIb();
    ib = std::min( 100, ib + 20 );
    pPlayer->gaugeWarSetIb( ib );
  }
};

EXPOSE_SCRIPT( ActionStormsPath42 );