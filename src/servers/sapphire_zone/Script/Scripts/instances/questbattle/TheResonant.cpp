#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheResonant : public InstanceContentScript
{
public:
   TheResonant() : InstanceContentScript( 5017 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 6927333, 4, { 503.255096f, 70.000000f, 589.613708f }, 1.000000f );
      instance->registerEObj( "Gatewinch", 2008907, 0, 4, { 508.261505f, 71.415131f, 575.156982f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2007457, 7012282, 4, { 702.654602f, 70.000000f, 532.514282f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2008678, 0, 4, { -139.654007f, 69.993042f, 667.066772f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2008678, 0, 4, { -187.638397f, 69.993042f, 634.666504f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2008678, 0, 4, { -73.946472f, 69.993042f, 652.456177f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};