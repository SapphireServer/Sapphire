#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>

class ActionReturn6 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionReturn6() :
    Sapphire::ScriptAPI::ActionScript( 6 )
  {
  }

  void onCastFinish( Sapphire::Entity::Chara& sourceActor, Sapphire::Action::Action& currentAction ) override
  {
    if( !sourceActor.isPlayer() )
      return;

    sourceActor.getAsPlayer()->returnToHomepoint();
  }
};