#include <ScriptObject.h>
#include <Actor/Player.h>

class ActionSprint3 : public ActionScript
{
public:
   ActionSprint3() : ActionScript( 3 )
   {}

   void onCastFinish( Core::Entity::Player& player, Core::Entity::Chara& targetActor ) override
   {
      player.addStatusEffectByIdIfNotExist( 50, 20000, player, 30 );
   }
};