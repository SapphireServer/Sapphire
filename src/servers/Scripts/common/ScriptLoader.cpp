#include <Script/NativeScriptApi.h>

#include "Aethernet.cpp"
#include "Aetheryte.cpp"
#include "CmnDefCutSceneReplay.cpp"
#include "CmnDefInnBed.cpp"
#include "CmnDefLinkShell.cpp"
#include "HouFurOrchestrion.cpp"

const ScriptObject* ptrs[] =
{
   static_cast< ScriptObject* >( new Aethernet ),
   static_cast< ScriptObject* >( new Aetheryte ),
   static_cast< ScriptObject* >( new CmnDefCutSceneReplay ),
   static_cast< ScriptObject* >( new CmnDefInnBed ),
   static_cast< ScriptObject* >( new CmnDefLinkShell ),
   static_cast< ScriptObject* >( new HouFurOrchestrion ),

   nullptr
};

extern "C" EXPORT const ScriptObject** getScripts()
{
   return ptrs;
}
