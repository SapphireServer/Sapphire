#include <Script/NativeScriptApi.h>

#include "ActionSprint3.cpp"

const ScriptObject* ptrs[] =
{
   static_cast< ScriptObject* >( new ActionSprint3 ),

   nullptr
};

extern "C" EXPORT const ScriptObject** getScripts()
{
   return ptrs;
}
