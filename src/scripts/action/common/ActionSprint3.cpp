#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionSprint3 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSprint3() :
    Sapphire::ScriptAPI::ActionScript( 3 )
  {
  }

  void onFinish( Sapphire::Action::Action& currentAction ) override
  {
    auto sourceChara = currentAction.getSourceChara();

    if( !sourceChara->isPlayer() )
      return;

    sourceChara->getAsPlayer()->addStatusEffectByIdIfNotExist( 50, 20000, *sourceChara, 30 );
  }
};

EXPOSE_SCRIPT( ActionSprint3 );