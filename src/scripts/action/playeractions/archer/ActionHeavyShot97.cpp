#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionHeavyShot97 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionHeavyShot97() :
    Sapphire::ScriptAPI::ActionScript( 97 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {
    if( auto player = action.getSourceChara()->getAsPlayer() )
      player->sendDebug( "Imagine you just hit an enemy for 150 potency. Incredible, right?" );
  }

};

EXPOSE_SCRIPT( ActionHeavyShot97 );