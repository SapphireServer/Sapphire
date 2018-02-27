#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ARelicReborntheChimera : public InstanceContentScript
{
public:
   ARelicReborntheChimera() : InstanceContentScript( 20019 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2006993, 6235274, 4, { -35.822102f, 298.899994f, -205.263199f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2006952, 0, 4, { -35.712589f, 298.899994f, -204.878006f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 556.049377f, 348.102509f, -752.435730f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4600289, 5, { 523.532471f, 348.223389f, -736.685730f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002332, 0, 4, { 533.090881f, 348.691895f, -742.750916f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002333, 0, 4, { 539.940430f, 348.836395f, -734.401489f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2000608, 3967803, 4, { 202.369598f, 257.761108f, 80.435272f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2000608, 3976993, 4, { 273.634705f, 254.600204f, 106.048500f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2000608, 3986797, 4, { 205.504898f, 246.188995f, 194.875702f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2000608, 3986798, 4, { 326.313385f, 239.193497f, 221.138901f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2000608, 2718481, 4, { 240.552307f, 302.769714f, -199.979996f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2000608, 4065433, 4, { 204.970001f, 302.119995f, -216.311600f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2000608, 2814617, 4, { 205.869995f, 302.219086f, -276.681396f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2000608, 2763112, 4, { -433.000000f, 211.007706f, -216.148605f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2000608, 4187649, 4, { -453.000000f, 211.000000f, -281.046600f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2000608, 4187961, 4, { -416.000000f, 210.788193f, -279.813812f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};