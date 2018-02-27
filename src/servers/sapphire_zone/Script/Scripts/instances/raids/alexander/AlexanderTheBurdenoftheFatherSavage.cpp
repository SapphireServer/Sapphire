#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheBurdenoftheFatherSavage : public InstanceContentScript
{
public:
   AlexanderTheBurdenoftheFatherSavage() : InstanceContentScript( 30028 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005494, 5863691, 4, { 102.000000f, 43.646099f, 16.000000f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 5788043, 5, { -0.001985f, 10.900000f, 20.255680f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -0.015320f, 10.561610f, -23.025881f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};