#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionMount4 : public ActionScript
{
public:
   ActionMount4() : ActionScript( 4 )
   {}

   void onCastFinish( Entity::Chara& caster, Entity::Chara& target, Action::Action& action ) override
   {
      if( auto player = caster.getAsPlayer() )
         player->mount( action.getParam() );
   }
};