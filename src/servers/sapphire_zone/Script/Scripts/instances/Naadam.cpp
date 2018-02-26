#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class Naadam : public InstanceContentScript
{
public:
   Naadam() : InstanceContentScript( 5008 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2008290, 6894789, 4, { 375.272888f, -4.893838f, 290.605011f }, 1.000000f );
      instance->registerEObj( "Yol", 2008330, 0, 4, { 466.995514f, 21.157949f, -328.188995f }, 1.000000f );
      instance->registerEObj( "Ovoo", 2008289, 6872570, 4, { 354.000000f, -0.790344f, 296.500000f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2004967, 0, 4, { -187.899506f, 1.653982f, 760.298279f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};