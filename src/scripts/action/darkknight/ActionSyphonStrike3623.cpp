#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionSyphonStrike3623 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSyphonStrike3623() :
    Sapphire::ScriptAPI::ActionScript( 3623 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {

  }

};

EXPOSE_SCRIPT( ActionSyphonStrike3623 );