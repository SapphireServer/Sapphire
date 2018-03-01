#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class OneLifeforOneWorld : public InstanceContentScript
{
public:
   OneLifeforOneWorld() : InstanceContentScript( 5003 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Entrance", 2000182, 4177874, 5, { -16.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 16.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007452, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "BladeofLight", 2007454, 0, 4, { 0.000000f, 0.000000f, 11.300000f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};