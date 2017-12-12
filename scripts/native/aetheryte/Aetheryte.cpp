#include "../ScriptObject.h"

class Aetheryte : public QuestScript
{
public:
   Aetheryte() : QuestScript( "Aetheryte", 0x50000 )
   {}


};

EXPORT_SCRIPTOBJECT( Aetheryte )