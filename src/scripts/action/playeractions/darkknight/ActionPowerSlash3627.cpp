#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionPowerSlash3627 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionPowerSlash3627() :
    Sapphire::ScriptAPI::ActionScript( 3627 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {

  }

};

EXPOSE_SCRIPT( ActionPowerSlash3627 );