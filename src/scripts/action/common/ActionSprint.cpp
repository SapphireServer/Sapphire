#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

#include <Math/CalcStats.h>
#include <Action/CommonAction.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionSprint : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSprint() : Sapphire::ScriptAPI::ActionScript( Sprint )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto sourceChara = action.getSourceChara();

    if( !sourceChara->isPlayer() )
      return;

    uint32_t duration = ( sourceChara->getAsPlayer()->getTp() / 50 ) * 1000; // Todo: Check for parity
    action.getActionResultBuilder()->applyStatusEffectSelf( SprintStatus, duration, 30, true );
    sourceChara->getAsPlayer()->setTp( 0 );
  }
};

EXPOSE_SCRIPT( ActionSprint );