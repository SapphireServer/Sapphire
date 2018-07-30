#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionReturn6 : public ActionScript
{
public:
   ActionReturn6() : ActionScript( 6 )
   {}

   void onCastFinish( Entity::Chara& caster, Entity::Chara& target, Action::Action& action ) override
   {
      if( auto player = caster.getAsPlayer() )
         player->returnToHomepoint();
   }
};