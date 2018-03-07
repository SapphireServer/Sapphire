#include <Script/NativeScriptApi.h>

#include "Aethernet.cpp"
#include "Aetheryte.cpp"
#include "HouFurOrchestrion.cpp"
#include "CmnDefInnBed.cpp"
#include "CmnDefCutSceneReplay.cpp"
#include "CmnDefLinkShell.cpp"

const ScriptObject* ptrs[] =
{
   static_cast< ScriptObject* >( new Aethernet ),
   static_cast< ScriptObject* >( new Aetheryte ),
   static_cast< ScriptObject* >( new HouFurOrchestrion ),
   static_cast< ScriptObject* >( new CmnDefInnBed ),
   static_cast< ScriptObject* >( new CmnDefCutSceneReplay ),
   static_cast< ScriptObject* >( new CmnDefLinkShell ),

   nullptr
};

extern "C" EXPORT const ScriptObject** getScripts()
{
   return ptrs;
}
