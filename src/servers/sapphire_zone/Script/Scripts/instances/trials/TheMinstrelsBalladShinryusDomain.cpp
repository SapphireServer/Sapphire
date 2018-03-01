#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheMinstrelsBalladShinryusDomain : public InstanceContentScript
{
public:
   TheMinstrelsBalladShinryusDomain() : InstanceContentScript( 20050 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Entrance", 2000182, 7034110, 5, { -21.048290f, -380.000092f, 1.297991f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 620.000000f, 20.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 7023869, 4, { -16.594919f, -380.000092f, -17.432211f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 7023871, 4, { -0.213646f, -380.000092f, -17.432211f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 7023870, 4, { 19.761841f, -380.000092f, -17.432211f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 7023865, 4, { -16.594919f, -380.000092f, 0.746161f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007457, 7023864, 4, { 20.591261f, -380.000092f, 1.852063f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007457, 7023866, 4, { -16.594919f, -380.000092f, 20.030439f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007457, 7023868, 4, { 1.859938f, -380.000092f, 20.168671f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 7023867, 4, { 21.489799f, -380.000092f, 20.306919f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007457, 7023863, 4, { 0.270193f, -380.000092f, 0.884399f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007457, 7024624, 4, { -5.336151f, -380.000000f, 8.195240f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 7024837, 4, { 17.385090f, 620.000000f, -3.965453f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007457, 7024899, 4, { 15.077030f, 620.000000f, -79.248016f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007457, 7032157, 4, { 7.331779f, 620.000000f, 0.488136f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 7032193, 4, { 9.743866f, 620.000000f, -5.475266f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2009049, 0, 4, { 20.000000f, 620.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2009065, 0, 4, { -0.015030f, 619.988770f, -6.068220f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2009073, 0, 4, { -20.000000f, 620.000000f, 0.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};