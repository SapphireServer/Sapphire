#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThePoolofTributeExtreme : public InstanceContentScript
{
public:
   ThePoolofTributeExtreme() : InstanceContentScript( 20047 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Bladesshadow", 2008185, 6849163, 4, { -0.015320f, 0.206439f, -5.020264f }, 0.991760f );
      instance->registerEObj( "Unknown0", 2008184, 6843593, 4, { -4.501404f, 0.200000f, 8.957031f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 6847132, 5, { -3.489120f, 0.200000f, 16.024530f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.357571f, 0.200000f, -11.800290f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};