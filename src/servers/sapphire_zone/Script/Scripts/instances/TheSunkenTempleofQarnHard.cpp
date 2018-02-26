#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheSunkenTempleofQarnHard : public InstanceContentScript
{
public:
   TheSunkenTempleofQarnHard() : InstanceContentScript( 26 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Entrance", 2000182, 4876828, 5, { -201.196701f, 0.682657f, 0.238411f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000603, 0, 4, { -172.011398f, 12.472960f, 3.615232f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 128.831894f, -3.999020f, -0.076355f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2004381, 4688136, 4, { -62.950489f, -9.042180f, -43.471519f }, 1.000000f );
      instance->registerEObj( "Lockeddoor", 2004382, 4686911, 4, { -52.102619f, -15.747660f, 0.003015f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2004383, 4880940, 4, { -32.646118f, -15.322760f, -0.535999f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2004384, 4688144, 4, { -9.445859f, -15.431120f, 0.091173f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2002735, 0, 4, { -24.503120f, -51.014042f, -2.151611f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2002872, 4877209, 4, { -24.127260f, -49.149910f, -1.216785f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2004385, 4877211, 4, { -33.270012f, -49.495350f, -17.436060f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2004576, 4880984, 4, { -32.350761f, -15.369120f, 1.208490f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2004386, 4877345, 4, { 47.455811f, -46.541481f, 18.191370f }, 1.000000f );
      instance->registerEObj( "Lockeddoor", 2004388, 4688151, 4, { 166.535797f, -43.147060f, 0.015993f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2004402, 4877619, 4, { 213.946701f, -42.801571f, -0.015320f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2004389, 4688148, 4, { 207.414703f, -1.759183f, 0.009065f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2002735, 0, 4, { 256.782104f, -3.999999f, 0.025025f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2002872, 4877953, 4, { 257.319305f, -2.265031f, 0.350891f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2004431, 4879695, 4, { 218.928802f, -2.699499f, 0.015198f }, 0.991760f );
      instance->registerEObj( "Unknown14", 2004391, 4742442, 4, { -44.851521f, -16.474951f, -61.569599f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2004392, 4742441, 4, { -34.082909f, -16.222090f, -39.745499f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2004403, 4688145, 4, { -9.412401f, -14.700150f, -48.979301f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2004393, 4685534, 4, { 13.954340f, -16.478741f, -36.432899f }, 0.991760f );
      instance->registerEObj( "Unknown18", 2004394, 4688137, 4, { 8.975560f, -14.432130f, -28.492041f }, 0.991760f );
      instance->registerEObj( "Magickedpedestal", 2004396, 4688166, 4, { 53.655460f, -15.371500f, 0.015198f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2004397, 4688139, 4, { 70.286049f, -14.700250f, -20.531210f }, 0.991760f );
      instance->registerEObj( "Magickedpedestal", 2004398, 4685848, 4, { 79.511627f, -15.096250f, -36.674881f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2004399, 4688140, 4, { 70.381950f, -14.689050f, 20.486361f }, 0.991760f );
      instance->registerEObj( "Magickedpedestal", 2004400, 4685849, 4, { 79.392357f, -14.749610f, 36.721691f }, 0.991760f );
      instance->registerEObj( "Unknown21", 2002872, 4981816, 4, { 97.856079f, -4.013123f, -1.052917f }, 0.991760f );
      instance->registerEObj( "Unknown22", 2004772, 4878447, 4, { 98.950607f, -4.000012f, -2.245166f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2004602, 0, 4, { 133.195908f, -4.013123f, -0.015320f }, 0.991760f );
      instance->registerEObj( "Unknown24", 2004603, 0, 4, { 133.195908f, -4.013123f, 12.924380f }, 0.991760f );
      instance->registerEObj( "Unknown25", 2004709, 0, 4, { 128.074203f, -4.000000f, 18.223900f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2004710, 0, 4, { 115.087196f, -4.000000f, 18.223900f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2004711, 0, 4, { 102.068398f, -4.000000f, 18.223900f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2004712, 0, 4, { 97.276253f, -4.013123f, 12.893800f }, 0.991760f );
      instance->registerEObj( "Unknown29", 2004713, 0, 4, { 97.276253f, -4.013123f, -0.045776f }, 0.991760f );
      instance->registerEObj( "Unknown30", 2004714, 0, 4, { 97.293999f, -4.000000f, -12.961500f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2004715, 0, 4, { 102.037003f, -4.013123f, -17.868410f }, 0.991760f );
      instance->registerEObj( "Unknown32", 2004716, 0, 4, { 115.069099f, -4.000000f, -17.860500f }, 1.000000f );
      instance->registerEObj( "Unknown33", 2004717, 0, 4, { 128.038498f, -4.013123f, -17.898861f }, 0.991760f );
      instance->registerEObj( "Unknown34", 2004718, 0, 4, { 133.195908f, -4.013123f, -12.954960f }, 0.991760f );
      instance->registerEObj( "Unknown35", 2004604, 0, 4, { 130.266205f, -4.013123f, 15.518430f }, 0.991760f );
      instance->registerEObj( "Unknown36", 2004719, 0, 4, { 99.982773f, -4.000000f, 15.879740f }, 1.000000f );
      instance->registerEObj( "Unknown37", 2004720, 0, 4, { 100.288803f, -4.000000f, -15.013530f }, 1.000000f );
      instance->registerEObj( "Unknown38", 2004721, 0, 4, { 130.501694f, -4.000000f, -14.939790f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};