#include <Script/NativeScriptApi.h>

extern Sapphire::ScriptAPI::ScriptObject* makeScriptActionReturn6();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptActionSprint3();

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   makeScriptActionReturn6(),
   makeScriptActionSprint3(),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
