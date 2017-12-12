#include "../ScriptObject.h"

class ActionSprint : public ActionScript
{
public:
   ActionSprint() : ActionScript( "ActionSprint", 3 )
   {}

   virtual void onCastFinish( Core::Entity::Player& player, Core::Entity::Actor& targetActor )
   {
      player.addStatusEffectByIdIfNotExist( 50, 20000, player, 30 );
   }
};

EXPORT_SCRIPTOBJECT( ActionSprint )