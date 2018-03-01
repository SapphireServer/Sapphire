#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheSirensongSea : public InstanceContentScript
{
public:
   TheSirensongSea() : InstanceContentScript( 52 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 6819364, 4, { -44.318520f, 7.751197f, 441.540314f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { -44.500000f, 7.751200f, 442.849213f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -44.500000f, 7.751197f, 479.639496f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007807, 6538465, 4, { -47.414162f, 7.761197f, 460.423798f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007808, 0, 4, { -47.907341f, 7.761197f, 468.566406f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002872, 6799021, 4, { -0.932950f, 2.896456f, -244.606796f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007805, 6799028, 4, { -3.967087f, 2.901603f, -197.601196f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002735, 0, 4, { -0.941400f, 2.840884f, -239.721100f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002872, 6815429, 4, { -2.123292f, 4.050672f, 57.244740f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007805, 6815430, 4, { -8.575331f, 3.826778f, 103.254997f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2002735, 0, 4, { -1.497813f, 4.446609f, 60.548241f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007793, 6532641, 4, { 2.243042f, 18.326050f, -408.926514f }, 0.991760f );
      instance->registerEObj( "Unknown11", 2007794, 6563600, 4, { 41.646648f, 2.171033f, -286.870514f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007796, 6532642, 4, { 3.723403f, 2.665442f, -271.541992f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007800, 6532643, 4, { -60.279049f, 11.703340f, -43.075298f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007792, 6532645, 4, { -22.236191f, 16.347031f, 23.168619f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007809, 0, 4, { 22.290779f, 4.298793f, -79.014076f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007801, 6531305, 4, { -9.013880f, 2.088060f, 112.314201f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007802, 6531303, 4, { -11.146170f, 0.410454f, 129.890305f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007803, 6536676, 4, { -27.389811f, -1.621430f, 174.494598f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2007804, 6536677, 4, { 8.575519f, -2.552741f, 200.835098f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2007795, 6536431, 4, { 14.781270f, -3.423584f, 241.748199f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2007797, 6786442, 4, { 11.182830f, 9.875385f, 302.008087f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2007798, 6786460, 4, { -44.133888f, 5.932619f, 395.955688f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2007799, 6516590, 4, { -45.003849f, 7.341055f, 413.088501f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6793848, 5, { 0.380240f, 21.347240f, -469.744507f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 0.000000f, 21.511560f, -462.178009f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};