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

  void onCastFinish( Sapphire::Entity::Player& player, Sapphire::Entity::Chara& targetActor ) override
  {
    player.addStatusEffectByIdIfNotExist( 50, 20000, player, 30 );
  }
};

EXPOSE_SCRIPT( ActionSprint3 );