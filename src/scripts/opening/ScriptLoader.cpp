#include <Script/NativeScriptApi.h>

extern Sapphire::ScriptAPI::ScriptObject* makeScriptOpeningGridania();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptOpeningLimsa();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptOpeningUldah();

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   makeScriptOpeningGridania(),
   makeScriptOpeningLimsa(),
   makeScriptOpeningUldah(),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
