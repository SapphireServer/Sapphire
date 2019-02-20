#include <Script/NativeScriptApi.h>

extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefCutSceneReplay();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefInnBed();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefLinkShell();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefMarketBoardGridania();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefMogLetter();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefNpcRepair();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefWeatherForeCast();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptComDefMobHuntBoard();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptGilShop();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptHouFurOrchestrion();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptAetheryte();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptHousingAethernet();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptHousingEstateEntrance();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefHousingPersonalRoomEntrance();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptCmnDefHousingSignboard();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptHousingWarpTaxiExitEstate();
extern Sapphire::ScriptAPI::ScriptObject* makeScriptWarpTaxi();

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   makeScriptCmnDefCutSceneReplay(),
   makeScriptCmnDefInnBed(),
   makeScriptCmnDefLinkShell(),
   makeScriptCmnDefMarketBoardGridania(),
   makeScriptCmnDefMogLetter(),
   makeScriptCmnDefNpcRepair(),
   makeScriptCmnDefWeatherForeCast(),
   makeScriptComDefMobHuntBoard(),
   makeScriptGilShop(),
   makeScriptHouFurOrchestrion(),
   makeScriptAetheryte(),
   makeScriptHousingAethernet(),
   makeScriptHousingEstateEntrance(),
   makeScriptCmnDefHousingPersonalRoomEntrance(),
   makeScriptCmnDefHousingSignboard(),
   makeScriptHousingWarpTaxiExitEstate(),
   makeScriptWarpTaxi(),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
