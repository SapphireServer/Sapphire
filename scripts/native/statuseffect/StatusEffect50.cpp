#include "../ScriptObject.h"

class StatusEffect50 : public StatusEffectScript
{
public:
   StatusEffect50() : StatusEffectScript( "StatusEffect50", 50 )
   {}

//   virtual void onTick( Core::Entity::ActorPtr actor )
//   {
//      if( actor->isPlayer() )
//         actor->getAsPlayer()->sendDebug( "tick tock bitch" );
//   }
};

EXPORT_STATUSEFFECTSCRIPT( StatusEffect50 )