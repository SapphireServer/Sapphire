#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class PharosSirius :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  PharosSirius() :
    Sapphire::ScriptAPI::InstanceContentScript( 17 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2002718, 4378108, 5, { 88.730026f, 0.300000f, 69.993042f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2002719, 0, 4, { 118.749496f, 0.300000f, 70.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -18.275600f, 193.987900f, 0.000000f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 42.000000f, 30.001560f, -31.911860f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_f1d2", 2002720, 4378115, 4, { 41.977539f, 30.001610f, -32.837688f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002723, 4391376, 4, { 23.849791f, 29.984011f, -56.015869f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 21.744020f, 89.982422f, -0.015320f }, 0.991760f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002721, 4378121, 4, { 20.279169f, 89.982422f, -0.015320f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002724, 4378123, 4, { -20.870550f, 90.000008f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 25.750000f, 194.136505f, 0.000000f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002722, 4378127, 4, { 24.286779f, 194.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 76.644943f, 0.300000f, 66.422493f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2002725, 4392603, 4, { -42.923710f, 29.984011f, -56.504211f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2002726, 4392604, 4, { -19.028080f, 36.148560f, -22.110350f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2002727, 4392605, 4, { 17.898800f, 44.388432f, -22.415590f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_8", 2002728, 4392606, 4, { 26.840580f, 52.091381f, 10.055660f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_9", 2002729, 4404469, 4, { -41.947140f, 29.984011f, 55.924320f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { 0.000000f, 140.000000f, 21.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002744, 4390583, 4, { 0.213522f, 139.893402f, 22.075270f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002743, 4390585, 4, { -0.033084f, 140.000000f, -20.026180f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_11", 2002742, 4390546, 4, { -11.093380f, 1.388489f, -23.453131f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aethervalve", 2002730, 4392611, 4, { -0.015320f, 119.981598f, -32.913761f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aethervalve_1", 2002731, 4392612, 4, { -0.076355f, 139.970901f, 42.618408f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2002787, 4395239, 4, { -38.345951f, 60.593510f, 21.011600f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2003436, 4406574, 4, { 41.813019f, 29.999941f, -29.969271f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2003032, 0, 4, { 42.000000f, 30.000771f, -59.314499f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2003033, 0, 4, { 42.000000f, 30.000771f, -56.244320f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2003034, 0, 4, { 42.000000f, 30.000771f, -51.724258f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( PharosSirius );