#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheFieldsofGloryShatter : public InstanceContentScript
{
public:
   TheFieldsofGloryShatter() : InstanceContentScript( 50005 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007022, 6245702, 4, { -263.444885f, 52.175270f, -209.921402f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007023, 6245745, 4, { -91.249367f, 27.082781f, 248.251297f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007024, 6245744, 4, { 262.704590f, 7.555402f, -83.636391f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2007038, 6246503, 4, { -33.290001f, 8.500000f, -64.930000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007039, 6246502, 4, { -29.181200f, 4.895900f, -181.130005f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007040, 6246500, 4, { 49.409801f, 1.000000f, 95.446404f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007041, 6246488, 4, { -139.203201f, 2.000000f, 42.698399f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007042, 6246517, 4, { 10.250100f, 7.501600f, -73.703102f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007126, 6260293, 4, { -21.009300f, 6.445800f, -124.468399f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007044, 6246516, 4, { -57.941700f, 7.532000f, -89.861702f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007043, 6246515, 4, { -28.053699f, 7.586800f, -20.808001f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007124, 6260291, 4, { -81.065201f, 8.327300f, -23.711300f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007122, 6260289, 4, { 17.876400f, 7.001300f, 11.047300f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007053, 6246513, 4, { -126.529999f, 35.526501f, -132.360001f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007125, 6260292, 4, { -224.454102f, 30.212000f, -33.290001f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007052, 6246514, 4, { -148.077499f, 48.772800f, -3.141700f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007051, 6246505, 4, { -195.641693f, 37.440800f, 80.677399f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007123, 6260290, 4, { -107.700996f, 10.249100f, 150.690598f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007050, 6246507, 4, { -8.180000f, 31.300200f, 107.550003f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2007049, 6246508, 4, { 75.684898f, 35.111000f, 149.223801f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2007048, 6246509, 4, { 174.059998f, 30.587099f, 122.660004f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2007047, 6246510, 4, { 175.149307f, 0.118000f, 8.585100f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2007046, 6246511, 4, { 121.235901f, 29.898701f, -190.225006f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2007121, 6260294, 4, { 29.201799f, 37.825001f, -217.776505f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2007045, 6246512, 4, { -43.203499f, 42.615501f, -229.343597f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};