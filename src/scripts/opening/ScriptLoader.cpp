#include <Script/NativeScriptApi.h>

#include "OpeningGridania.cpp"
#include "OpeningLimsa.cpp"
#include "OpeningUldah.cpp"

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new OpeningGridania ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new OpeningLimsa ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new OpeningUldah ),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
