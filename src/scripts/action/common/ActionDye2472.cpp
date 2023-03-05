#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Inventory/Item.h>

class ActionDye2472 : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionDye2472() : Sapphire::ScriptAPI::ActionScript( 2472 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto sourceChara = action.getSourceChara();

    if( !sourceChara->isPlayer() )
      return;

    //TODO: Effect
    sourceChara->getAsPlayer()->dyeItemFromDyeingInfo();
  }
};

EXPOSE_SCRIPT(ActionDye2472);