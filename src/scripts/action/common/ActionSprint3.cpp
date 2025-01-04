#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionSprint3 : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSprint3() : Sapphire::ScriptAPI::ActionScript( 3 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto sourceChara = action.getSourceChara();

    if( !sourceChara->isPlayer() )
      return;

    uint32_t duration = ( sourceChara->getAsPlayer()->getTp() / 50 ) * 1000;
    action.getActionResultBuilder()->applyStatusEffectSelf( 50, duration, 30, false );
    sourceChara->getAsPlayer()->setTp( 0 );
  }
};

EXPOSE_SCRIPT( ActionSprint3 );