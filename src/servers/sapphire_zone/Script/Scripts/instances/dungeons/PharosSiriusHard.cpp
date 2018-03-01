#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class PharosSiriusHard : public InstanceContentScript
{
public:
   PharosSiriusHard() : InstanceContentScript( 40 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 5963936, 4, { -1.480164f, 93.003777f, -23.788879f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { -0.228943f, 93.016541f, -22.052860f }, 0.869751f );
      instance->registerEObj( "Unknown2", 2002872, 5963943, 4, { 21.051910f, 90.039482f, -0.641622f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2006551, 0, 4, { 6.820740f, 90.135010f, -0.717224f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2002872, 5963945, 4, { 20.515039f, 30.001440f, -55.973820f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002735, 0, 4, { 21.438900f, 30.001369f, -55.832821f }, 0.869751f );
      instance->registerEObj( "Unknown6", 2002872, 5963948, 4, { 60.977539f, 30.000811f, -56.096581f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2006563, 0, 4, { 42.160641f, 29.984011f, -60.227360f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2002872, 5963970, 4, { -95.386551f, -5.551003f, -272.570099f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2002735, 0, 4, { -95.423126f, -5.551003f, -271.765991f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5963633, 5, { 39.155338f, 189.990097f, -2.100519f }, 0.991760f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 39.255451f, 188.130096f, -17.964260f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -95.418854f, -5.446677f, -305.998199f }, 0.991760f );
      instance->registerEObj( "Unknown11", 2006461, 5961306, 4, { -42.092682f, 170.000000f, 1.321840f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2006462, 5961309, 4, { 0.142279f, 160.000000f, 41.544201f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2006463, 5965424, 4, { 1.331733f, 158.160294f, 25.044350f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2006464, 5964060, 4, { 0.116699f, 139.949997f, -18.497431f }, 1.000000f );
      instance->registerEObj( "Candlekeepkey", 2006467, 0, 4, { 13.504210f, 29.984011f, -54.795170f }, 0.991760f );
      instance->registerEObj( "Lockeddoor", 2006470, 5955784, 4, { 15.219990f, 31.371090f, -56.250301f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006465, 5963843, 4, { 32.070061f, 72.230629f, -55.058460f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2006466, 5965844, 4, { -0.253021f, 39.999969f, -21.544781f }, 1.000000f );
      instance->registerEObj( "Port3526", 2006471, 5960472, 4, { -16.647579f, 7.686357f, -153.002304f }, 0.991760f );
      instance->registerEObj( "Port3524", 2006472, 5960468, 4, { -94.266373f, -0.598898f, -227.302200f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2006528, 5967682, 4, { 10.338900f, 10.519330f, -124.110298f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2006564, 5967692, 4, { -3.081049f, 5.016401f, -212.859802f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2002618, 5993225, 4, { 0.231439f, 90.039482f, -21.072599f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};