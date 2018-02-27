#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheBurdenoftheSon : public InstanceContentScript
{
public:
   AlexanderTheBurdenoftheSon() : InstanceContentScript( 30033 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 10.705920f, -21.985399f }, 1.000000f );
      instance->registerEObj( "Unknown0", 2006984, 6164617, 4, { -0.231898f, 10.500000f, -1.988388f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2006989, 6234571, 4, { 0.000000f, 10.500000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2006974, 0, 4, { -16.291439f, 10.500000f, 4.361944f }, 1.000000f );
      instance->registerEObj( "Exit", 2005313, 6076667, 4, { 0.000000f, 10.500000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6177907, 5, { 0.000000f, 10.500000f, 19.500000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};