#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionBloodfest16164 :
  public ScriptAPI::ActionScript
{
public:
  ActionBloodfest16164() :
    ScriptAPI::ActionScript( 16164 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto chara = action.getHitChara();
    if( chara )
    {
      auto source = action.getSourceChara();
      auto player = source->getAsPlayer();
      assert( player );
      chara->onActionHostile( source );
      player->gaugeGnbSetAmmo( 2 );
    }
  }
};

EXPOSE_SCRIPT( ActionBloodfest16164 );