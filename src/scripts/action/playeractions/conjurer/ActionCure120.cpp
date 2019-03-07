#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionCure120 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionCure120() :
    Sapphire::ScriptAPI::ActionScript( 120 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {

  }

};

EXPOSE_SCRIPT( ActionCure120 );