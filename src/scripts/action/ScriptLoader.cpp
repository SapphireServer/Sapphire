#include <Script/NativeScriptApi.h>

#include "ActionReturn6.cpp"
#include "ActionSprint3.cpp"

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ActionReturn6 ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ActionSprint3 ),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
