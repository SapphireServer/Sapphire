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

   virtual void onApply( Entity::ActorPtr actor )
   {
      if( actor->isPlayer() )
         actor->getAsPlayer()->sendDebug( "status50 applied" );
   }

   virtual void onExpire( Entity::ActorPtr actor )
   {
      if( actor->isPlayer() )
         actor->getAsPlayer()->sendDebug( "status50 timed out" );
   }

};

EXPORT_STATUSEFFECTSCRIPT( Status50 )