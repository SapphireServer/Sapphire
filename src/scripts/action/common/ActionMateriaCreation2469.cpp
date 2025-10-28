#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Inventory/Item.h>

#include <cstdlib>

class ActionMateriaCreation2469 : public Sapphire::ScriptAPI::ActionScript
{

public:
  ActionMateriaCreation2469() : Sapphire::ScriptAPI::ActionScript( 2469 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto sourceChara = action.getSourceChara();

    if( !sourceChara->isPlayer() )
      return;
    
    sourceChara->getAsPlayer()->materiaItemFromMateriaInfo();
  }
};

EXPOSE_SCRIPT( ActionMateriaCreation2469 );