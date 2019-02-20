#ifndef SAPPHIRE_SCRIPTOBJECT_H
#define SAPPHIRE_SCRIPTOBJECT_H

#include <ForwardsZone.h>
#include <Script/NativeScriptApi.h>

#include <Event/EventDefs.h>

#define EXPOSE_SCRIPT( className ) Sapphire::ScriptAPI::ScriptObject* makeScript##className() { return new className; }

#endif //SAPPHIRE_SCRIPTOBJECT_H
