#ifndef SAPPHIRE_SCRIPTOBJECT_H
#define SAPPHIRE_SCRIPTOBJECT_H

#include <Forwards.h>
#include <Script/NativeScriptApi.h>

#include <Event/EventDefs.h>

#define BIND_SCENE( x ) std::bind( x, this, std::placeholders::_1 )


#endif //SAPPHIRE_SCRIPTOBJECT_H
