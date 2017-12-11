#include "../ScriptObject.h"

class Status50 : public StatusEffectScript
{
public:
   Status50() : StatusEffectScript( "StatusEffect50", 50 )
   {}

   virtual void onTick( Core::Entity::ActorPtr actor )
   {
      if( actor->isPlayer() )
         actor->getAsPlayer()->sendDebug( "tick tock bitch" );
   }
};

EXPORT_STATUSEFFECTSCRIPT( Status50 )