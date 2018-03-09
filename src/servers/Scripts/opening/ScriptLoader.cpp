#include <Script/NativeScriptApi.h>

#include "OpeningLimsa.cpp"
#include "OpeningGridania.cpp"
#include "OpeningUldah.cpp"

const ScriptObject* ptrs[] =
{
   static_cast< ScriptObject* >( new OpeningLimsa ),
   static_cast< ScriptObject* >( new OpeningGridania ),
   static_cast< ScriptObject* >( new OpeningUldah ),

   nullptr
};

extern "C" EXPORT const ScriptObject** getScripts()
{
   return ptrs;
}
