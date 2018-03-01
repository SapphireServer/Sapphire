#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SpecialEventII : public InstanceContentScript
{
public:
   SpecialEventII() : InstanceContentScript( 20015 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Entrance", 2000182, 6430385, 5, { -7.331871f, 0.000000f, 23.153120f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.017054f, 0.000000f, -17.456369f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};