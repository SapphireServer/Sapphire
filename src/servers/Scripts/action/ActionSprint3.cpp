#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionSprint3 : public ActionScript
{
public:
   ActionSprint3() : ActionScript( 3 )
   {}

   void onCastFinish( Entity::Chara& caster, Entity::Chara& target, Action::Action& action ) override
   {
      caster.addStatusEffectByIdIfNotExist( 50, 20000, caster, 30 );
   }
};