#include <scripts/native/ScriptObject.h>

class StatusEffect50 : StatusEffectScript
{
public:
    StatusEffect50() : StatusEffectScript( "StatusEffect50", 50 )
    {}

    virtual void onTick( Core::Entity::ActorPtr actor )
    {

    }
};

EXPORT_STATUSEFFECTSCRIPT( StatusEffect50 )