#include <Script/NativeScriptApi.h>
#include "../ScriptObject.h"
#include <Actor/Player.h>

class ActionReturn6 : public ActionScript
{
public:
   ActionReturn6() : ActionScript( 6 )
   {}

   void onCastFinish( Entity::Chara& caster, Entity::Chara& targetActor ) override
   {
      if( auto player = caster.getAsPlayer() )
         player->returnToHomepoint();
   }
};