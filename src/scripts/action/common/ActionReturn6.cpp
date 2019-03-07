#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionReturn6 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionReturn6() :
    Sapphire::ScriptAPI::ActionScript( 6 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {
    if( !action.getSourceChara()->isPlayer() )
      return;

    action.getSourceChara()->getAsPlayer()->returnToHomepoint();
  }
};

EXPOSE_SCRIPT( ActionReturn6 );