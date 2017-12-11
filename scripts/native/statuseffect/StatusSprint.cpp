#include "../ScriptObject.h"

class StatusSprint : public StatusEffectScript
{
public:
   StatusSprint() : StatusEffectScript( "StatusSprint", 50 )
   {}
};

EXPORT_STATUSEFFECTSCRIPT( StatusSprint )