#include "../ScriptObject.h"

class StatusSprint : public StatusEffectScript
{
public:
   StatusSprint() : StatusEffectScript( "StatusSprint", 50 )
   {}

   virtual void onTick( Entity::Actor& actor ) override
   {
      if( actor.isPlayer() )
         actor.getAsPlayer()->sendDebug( "tick tock bitch" );
   }

   virtual void onApply( Entity::Actor& actor ) override
   {
      if( actor.isPlayer() )
         actor.getAsPlayer()->sendDebug( "status50 applied" );
   }

   virtual void onExpire( Entity::Actor& actor ) override
   {
      if( actor.isPlayer() )
         actor.getAsPlayer()->sendDebug( "status50 timed out" );
   }

};

EXPORT_SCRIPTOBJECT( StatusSprint )