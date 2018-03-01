#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheJadeStoaExtreme : public InstanceContentScript
{
public:
   TheJadeStoaExtreme() : InstanceContentScript( 20052 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2009431, 0, 4, { -2.722647f, -0.000001f, 7.311604f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 7174720, 5, { 5.504887f, 0.000000f, 14.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -14.500000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 7181535, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2009214, 0, 4, { 2.987230f, 0.000000f, -2.908927f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};