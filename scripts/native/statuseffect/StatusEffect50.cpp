#include "../ScriptObject.h"

class StatusEffect50 : StatusEffectScript
{
public:
   StatusEffect50() : StatusEffectScript( "StatusEffect50", 50 )
   {}

   virtual void onTick( Core::Entity::ActorPtr actor )
   {

   }
};

//extern "C" __declspec( dllexport ) __cdecl StatusEffectScript* getStatusEffectScript() { return static_cast< StatusEffectScript* >( new StatusEffect50 ); }

//EXPORT_STATUSEFFECTSCRIPT( StatusEffect50 )