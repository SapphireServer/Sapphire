#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheSouloftheCreator : public InstanceContentScript
{
public:
   AlexanderTheSouloftheCreator() : InstanceContentScript( 30042 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 400.000000f, -21.000000f }, 1.000000f );
      instance->registerEObj( "Unknown0", 2007468, 0, 4, { 14.140000f, 400.049988f, -14.140000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007468, 0, 4, { 14.140000f, 400.049988f, -14.140000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007468, 0, 4, { 14.140000f, 400.049988f, 14.140000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007468, 0, 4, { -14.140000f, 400.049988f, -14.140000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007468, 0, 4, { -14.140000f, 400.049988f, 14.140000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007519, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007520, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007521, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 6421491, 4, { 0.000000f, 400.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007516, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007457, 6487368, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 6487369, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007457, 6487367, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007457, 6487366, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 6483882, 4, { 0.000000f, -470.000000f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007457, 6421479, 4, { 0.000000f, 400.168701f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007499, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007534, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007457, 6539545, 4, { 0.024963f, -480.000000f, 52.037621f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6449508, 5, { -0.015367f, 400.000000f, 21.278250f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};