#include "../ScriptObject.h"

class ActionSprint3 : public ActionScript
{
public:
   ActionSprint3() : ActionScript( "ActionSprint3", 3 )
   {}

   void onCastFinish( Core::Entity::Player& player, Core::Entity::Actor& targetActor ) override
   {
      player.addStatusEffectByIdIfNotExist( 50, 20000, player, 30 );
   }
};

EXPORT_SCRIPTOBJECT( ActionSprint3 )