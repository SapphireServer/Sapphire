#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionHardSlash3617 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionHardSlash3617() :
    Sapphire::ScriptAPI::ActionScript( 3617 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {

  }

};

EXPOSE_SCRIPT( ActionHardSlash3617 );