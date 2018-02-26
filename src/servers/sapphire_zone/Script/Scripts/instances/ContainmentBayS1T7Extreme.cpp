#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ContainmentBayS1T7Extreme : public InstanceContentScript
{
public:
   ContainmentBayS1T7Extreme() : InstanceContentScript( 20038 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2006840, 6175219, 4, { 0.000000f, 0.000000f, -10.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2006841, 6175220, 4, { 7.071130f, 0.000000f, -7.071100f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2006842, 6175221, 4, { 10.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2006843, 6175222, 4, { 7.071130f, 0.000000f, 7.071130f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2006844, 6175223, 4, { 0.000000f, 0.000000f, 10.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2006845, 6175224, 4, { -7.071130f, 0.000000f, 7.071100f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2006846, 6175225, 4, { -10.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2006847, 6175226, 4, { -7.071130f, 0.000000f, -7.071130f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2006837, 6174136, 4, { 0.000000f, 0.052026f, -19.799999f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2006839, 6164929, 4, { 0.000000f, 0.002934f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2006838, 6171564, 4, { 0.116409f, 0.002934f, -0.768936f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2006840, 6175957, 4, { -0.836018f, 0.050520f, -2.055523f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2006983, 6219989, 4, { 0.000000f, 0.043380f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6173855, 5, { -0.006781f, 0.052026f, 13.691250f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.500000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};