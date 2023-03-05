#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Inventory/Item.h>

class ActionGlamour2471 : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionGlamour2471() : Sapphire::ScriptAPI::ActionScript( 2471 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto sourceChara = action.getSourceChara();

    if( !sourceChara->isPlayer() )
      return;

    //TODO: Effect
    sourceChara->getAsPlayer()->glamourItemFromGlamouringInfo();
  }
};

EXPOSE_SCRIPT(ActionGlamour2471);