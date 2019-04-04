#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class PharosSiriusHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  PharosSiriusHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 40 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5963936, 4, { -1.480164f, 93.003777f, -23.788879f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -0.228943f, 93.016541f, -22.052860f }, 0.869751f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 5963943, 4, { 21.051910f, 90.039482f, -0.641622f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2006551, 0, 4, { 6.820740f, 90.135010f, -0.717224f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 5963945, 4, { 20.515039f, 30.001440f, -55.973820f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 21.438900f, 30.001369f, -55.832821f }, 0.869751f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 5963948, 4, { 60.977539f, 30.000811f, -56.096581f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2006563, 0, 4, { 42.160641f, 29.984011f, -60.227360f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 5963970, 4, { -95.386551f, -5.551003f, -272.570099f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { -95.423126f, -5.551003f, -271.765991f }, 1.000000f, -0.005750f ); 
    instance.registerEObj( "Entrance", 2000182, 5963633, 5, { 39.155338f, 189.990097f, -2.100519f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 39.255451f, 188.130096f, -17.964260f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -95.418854f, -5.446677f, -305.998199f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2006461, 5961306, 4, { -42.092682f, 170.000000f, 1.321840f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2006462, 5961309, 4, { 0.142279f, 160.000000f, 41.544201f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2006463, 5965424, 4, { 1.331733f, 158.160294f, 25.044350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2006464, 5964060, 4, { 0.116699f, 139.949997f, -18.497431f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Candlekeepkey", 2006467, 0, 4, { 13.504210f, 29.984011f, -54.795170f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Lockeddoor", 2006470, 5955784, 4, { 15.219990f, 31.371090f, -56.250301f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2006465, 5963843, 4, { 32.070061f, 72.230629f, -55.058460f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2006466, 5965844, 4, { -0.253021f, 39.999969f, -21.544781f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Port3526", 2006471, 5960472, 4, { -16.647579f, 7.686357f, -153.002304f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Port3524", 2006472, 5960468, 4, { -94.266373f, -0.598898f, -227.302200f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_11", 2006528, 5967682, 4, { 10.338900f, 10.519330f, -124.110298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2006564, 5967692, 4, { -3.081049f, 5.016401f, -212.859802f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 5993225, 4, { 0.231439f, 90.039482f, -21.072599f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( PharosSiriusHard );