#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionIkishoten16482 :
  public ScriptAPI::ActionScript
{
public:
  ActionIkishoten16482() :
    ScriptAPI::ActionScript( 16482 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    assert( pPlayer );
    pPlayer->gaugeSamSetKenki( std::min( 100, pPlayer->gaugeSamGetKenki() + 50 ) );
  }
};

EXPOSE_SCRIPT( ActionIkishoten16482 );