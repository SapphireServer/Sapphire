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

  void onFinish( Sapphire::Action::Action& currentAction ) override
  {
    if( !currentAction.getSourceChara()->isPlayer() )
      return;

    currentAction.getSourceChara()->getAsPlayer()->returnToHomepoint();
  }
};

EXPOSE_SCRIPT( ActionReturn6 );