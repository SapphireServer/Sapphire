#include <ScriptObject.h>
#include <Actor/Player.h>

class ActionSprint3 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionSprint3() :
    Sapphire::ScriptAPI::ActionScript( 3 )
  {
  }

  void onCastFinish( Sapphire::Entity::Chara& sourceActor, Sapphire::Action::Action& currentAction ) override
  {
    if( !sourceActor.isPlayer() )
      return;

    sourceActor.getAsPlayer()->addStatusEffectByIdIfNotExist( 50, 20000, sourceActor, 30 );
  }
};