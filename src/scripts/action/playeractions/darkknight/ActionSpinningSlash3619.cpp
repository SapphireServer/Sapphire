#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionSpinningSlash3619 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSpinningSlash3619() :
    Sapphire::ScriptAPI::ActionScript( 3619 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {

  }

};

EXPOSE_SCRIPT( ActionSpinningSlash3619 );