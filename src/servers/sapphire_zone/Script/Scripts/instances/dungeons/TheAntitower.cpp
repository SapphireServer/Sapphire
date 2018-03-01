#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheAntitower : public InstanceContentScript
{
public:
   TheAntitower() : InstanceContentScript( 43 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002735, 0, 4, { 252.045807f, -9.475893f, -181.933304f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2002872, 6169321, 4, { 255.394501f, -8.467778f, -179.715897f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002872, 6169306, 4, { -367.917297f, 325.000000f, -225.755905f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002735, 0, 4, { -365.057709f, 325.000000f, -230.778107f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2006816, 6169309, 4, { -367.727386f, 325.000000f, -267.544891f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2006858, 0, 4, { -364.583893f, 324.971405f, -250.263199f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2006817, 6169316, 4, { 207.573303f, -22.000000f, 137.064407f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002872, 6169315, 4, { 163.478195f, -21.493710f, 135.478806f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2002735, 0, 4, { 165.865494f, -22.000000f, 137.572006f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2006767, 6215870, 4, { -319.905396f, 220.000000f, 144.542892f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2006771, 6215871, 4, { -351.689087f, 255.000000f, 14.809160f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2006778, 6215872, 4, { -361.023285f, 290.000000f, -120.754402f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2006781, 6112286, 4, { 202.549393f, 2.000032f, 188.466202f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2006782, 6112287, 4, { 190.864197f, 1.999979f, 180.727493f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2006783, 6112293, 4, { 181.429306f, 1.899876f, 187.239197f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006786, 6112290, 4, { 138.231400f, -16.006710f, 145.799896f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2006787, 6112291, 4, { 125.191902f, -16.000000f, 143.181503f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2006788, 6112288, 4, { 124.527199f, -16.000000f, 132.912994f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2006789, 6112289, 4, { 137.132797f, -16.006710f, 128.862396f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2006790, 6168912, 4, { 143.049393f, -16.000000f, 136.666702f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2006994, 6220274, 4, { 156.748901f, -3.960001f, 175.039703f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2006995, 6220275, 4, { 151.476196f, -3.952148f, 182.940308f }, 0.991760f );
      instance->registerEObj( "Unknown22", 2006996, 6220281, 4, { 154.570801f, -3.951959f, 179.952393f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2006997, 6220282, 4, { 132.225601f, -15.960000f, 142.602600f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2007012, 6107601, 4, { 215.289795f, -22.099991f, 137.138306f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2006791, 6215456, 4, { 141.712997f, 22.840740f, -75.213570f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2006792, 6215659, 4, { 143.769394f, 22.262880f, -82.780273f }, 0.991760f );
      instance->registerEObj( "Unknown27", 2006793, 6215458, 4, { 176.529694f, 12.734810f, -76.608017f }, 0.991760f );
      instance->registerEObj( "Unknown28", 2006794, 6215660, 4, { 175.971298f, 13.065370f, -83.629440f }, 0.991760f );
      instance->registerEObj( "Unknown29", 2006795, 6140680, 4, { 262.401794f, -0.700000f, -74.295052f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2006796, 6140674, 4, { 262.532196f, -0.700000f, -86.662819f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2006797, 6123756, 4, { 262.633514f, -0.700000f, -79.584007f }, 1.000000f );
      instance->registerEObj( "Unknown32", 2006798, 0, 4, { 291.762695f, -2.200014f, -76.847649f }, 1.000000f );
      instance->registerEObj( "Unknown33", 2006799, 0, 4, { 298.066406f, -2.151550f, -76.649200f }, 1.000000f );
      instance->registerEObj( "Unknown34", 2006800, 0, 4, { 298.579895f, -2.037392f, -84.721710f }, 1.000000f );
      instance->registerEObj( "Unknown35", 2006801, 6215463, 4, { 298.707794f, -2.062215f, -111.243301f }, 1.000000f );
      instance->registerEObj( "Unknown36", 2006802, 6215464, 4, { 291.473785f, -2.200000f, -111.318298f }, 1.000000f );
      instance->registerEObj( "Unknown37", 2006803, 6215465, 4, { 298.705597f, -2.065336f, -116.301102f }, 1.000000f );
      instance->registerEObj( "Unknown38", 2006804, 6215466, 4, { 291.648193f, -2.200000f, -116.725502f }, 1.000000f );
      instance->registerEObj( "Unknown39", 2006805, 6215467, 4, { 303.031708f, -0.700000f, -133.974594f }, 1.000000f );
      instance->registerEObj( "Unknown40", 2006806, 6215468, 4, { 286.195709f, -0.700000f, -132.797195f }, 1.000000f );
      instance->registerEObj( "Unknown41", 2006807, 6215469, 4, { 303.791687f, -0.717224f, -138.384094f }, 0.991760f );
      instance->registerEObj( "Unknown42", 2006808, 6215470, 4, { 286.152313f, -0.717224f, -136.736099f }, 0.991760f );
      instance->registerEObj( "Unknown43", 2006809, 6215471, 4, { 303.913788f, -0.717224f, -142.473495f }, 0.991760f );
      instance->registerEObj( "Unknown44", 2006810, 6215472, 4, { 286.518585f, -0.717224f, -140.550903f }, 0.991760f );
      instance->registerEObj( "Unknown45", 2006811, 6140683, 4, { 300.845215f, -0.700000f, -149.810699f }, 1.000000f );
      instance->registerEObj( "Unknown46", 2006812, 6140685, 4, { 289.275787f, -0.700000f, -149.729401f }, 1.000000f );
      instance->registerEObj( "Unknown47", 2006813, 6123759, 4, { 294.959503f, -0.700000f, -149.563904f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6168791, 5, { -303.646912f, 230.000000f, 280.401703f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -293.381012f, 230.000000f, 269.617188f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 216.878998f, -9.458686f, -181.220200f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};