#include <Script/NativeScriptApi.h>

#include "CmnDefCutSceneReplay.cpp"
#include "CmnDefInnBed.cpp"
#include "CmnDefLinkShell.cpp"
#include "CmnDefMarketBoardGridania.cpp"
#include "CmnDefMogLetter.cpp"
#include "CmnDefNpcRepair.cpp"
#include "CmnDefWeatherForeCast.cpp"
#include "ComDefMobHuntBoard.cpp"
#include "GilShop.cpp"
#include "HouFurOrchestrion.cpp"
#include "aethernet/Aetheryte.cpp"
#include "aethernet/HousingAethernet.cpp"
#include "eobj/HousingEstateEntrance.cpp"
#include "housing/CmnDefHousingPersonalRoomEntrance.cpp"
#include "housing/CmnDefHousingSignboard.cpp"
#include "warptaxi/HousingWarpTaxiExitEstate.cpp"
#include "warptaxi/WarpTaxi.cpp"

const Sapphire::ScriptAPI::ScriptObject* ptrs[] =
{
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefCutSceneReplay ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefInnBed ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefLinkShell ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefMarketBoardGridania ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefMogLetter ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefNpcRepair ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefWeatherForeCast ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new ComDefMobHuntBoard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new GilShop ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HouFurOrchestrion ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new Aetheryte ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HousingAethernet ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HousingEstateEntrance ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefHousingPersonalRoomEntrance ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new CmnDefHousingSignboard ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new HousingWarpTaxiExitEstate ),
   static_cast< Sapphire::ScriptAPI::ScriptObject* >( new WarpTaxi ),

   nullptr
};

extern "C" EXPORT const Sapphire::ScriptAPI::ScriptObject** getScripts()
{
   return ptrs;
}
