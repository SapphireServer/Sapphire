#include <Script/NativeScriptApi.h>
#include "../ScriptObject.h"
#include <Actor/Player.h>

class ActionReturn6 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionReturn6() :
    Sapphire::ScriptAPI::ActionScript( 6 )
  {
  }

  void onCastFinish( Sapphire::Entity::Player& player, Sapphire::Entity::Chara& targetActor ) override
  {
    player.returnToHomepoint();
  }
};

EXPOSE_SCRIPT( ActionReturn6 );