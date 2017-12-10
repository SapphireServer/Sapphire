#include "../ScriptObject.h"

class ActionScript3 : public ActionScript
{
public:
    ActionScript3() : ActionScript( "ActionScript3", 3 )
    {}

    virtual void onCastFinish( Core::Entity::Player player, Core::Entity::ActorPtr targetActor )
    {
       player.addStatusEffectByIdIfNotExist( 50, 20000, player, 30 );
    }
};

EXPORT_ACTIONSCRIPT( ActionScript3 )