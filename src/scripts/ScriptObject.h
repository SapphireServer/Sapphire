#ifndef SAPPHIRE_SCRIPTOBJECT_H
#define SAPPHIRE_SCRIPTOBJECT_H

#include <ForwardsZone.h>
#include <Script/NativeScriptApi.h>

#include <Event/EventDefs.h>

#define EXPOSE_SCRIPT( x ) Sapphire::ScriptAPI::ScriptObject* makeScript##x() { return new x; }

#endif //SAPPHIRE_SCRIPTOBJECT_H
