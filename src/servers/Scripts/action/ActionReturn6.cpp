#include <Script/NativeScriptApi.h>
#include "../ScriptObject.h"
#include <Actor/Player.h>

class ActionReturn6 :
  public ActionScript
{
public:
  ActionReturn6() :
    ActionScript( 6 )
  {
  }

  void onCastFinish( Core::Entity::Player& player, Core::Entity::Chara& targetActor ) override
  {
    player.returnToHomepoint();
  }
};