#include <ScriptObject.h>
#include <Actor/Player.h>

class ActionSprint3 : public ActionScript
{
public:
   ActionSprint3() : ActionScript( 3 )
   {}

   void onCastFinish( Entity::Chara& caster, Entity::Chara& targetActor ) override
   {
      caster.addStatusEffectByIdIfNotExist( 50, 20000, caster, 30 );
   }
};