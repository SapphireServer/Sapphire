#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Inventory/Item.h>
#include <Action/CommonAction.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionGlamour : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionGlamour() : Sapphire::ScriptAPI::ActionScript( Glamour )
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

EXPOSE_SCRIPT( ActionGlamour );