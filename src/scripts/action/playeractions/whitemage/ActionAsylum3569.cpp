#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionAsylum3569 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionAsylum3569() :
    Sapphire::ScriptAPI::ActionScript( 3569 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {

  }

};

EXPOSE_SCRIPT( ActionAsylum3569 );