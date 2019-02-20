#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheOrbonneMonastery :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheOrbonneMonastery() :
    Sapphire::ScriptAPI::InstanceContentScript( 30077 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0250", 2007457, 7725374, 4, { 599.697021f, 0.000000f, 384.788696f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2007791, 0, 4, { 600.046814f, 0.000000f, 384.120605f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009696, 0, 4, { 581.460022f, 0.000000f, 283.458313f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 599.877808f, -31.021669f, -23.567789f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7742069, 4, { 599.994080f, -31.000000f, -20.984110f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgbg_z3r3_a2_swrd1", 2007457, 7746896, 4, { 589.026978f, -31.000000f, -64.958076f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r3_a2_swrd1_1", 2007457, 7746909, 4, { 609.340027f, -31.000000f, -43.261929f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r3_a2_shld1", 2007457, 7746912, 4, { 608.816589f, -31.000000f, -67.144180f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r3_a2_shld1_1", 2007457, 7746914, 4, { 592.940430f, -31.000000f, -41.502899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7749814, 4, { 605.816284f, -31.000000f, -87.291206f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_z3r3_b1616", 2007457, 7842482, 4, { 600.000000f, -30.000000f, -54.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r3_a2_swrd1_2", 2007457, 7844508, 4, { 300.000000f, 0.000000f, -50.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r3_a2_shld3", 2007457, 7845647, 4, { 600.000000f, -31.000000f, -49.000000f }, 1.000000f, 0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_1", 2007457, 7845648, 4, { 600.000000f, -31.000000f, -29.000000f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_2", 2007457, 7845649, 4, { 592.929016f, -31.000000f, -31.928900f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_3", 2007457, 7845650, 4, { 607.070984f, -31.000000f, -31.928900f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_4", 2007457, 7845651, 4, { 594.642517f, -31.000000f, -26.065701f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_5", 2007457, 7845652, 4, { 605.357483f, -31.000000f, -26.065701f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_6", 2007457, 7845653, 4, { 587.065674f, -31.000000f, -33.642399f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "sgbg_z3r3_a2_shld3_7", 2007457, 7845654, 4, { 612.934326f, -31.000000f, -33.642399f }, 1.000000f, -0.000000f ); 
    // States -> enable (id: 18) enable_a (id: 19) disable (id: 20) disable_a (id: 21) loop (id: 23) 
    instance.registerEObj( "unknown_3", 2007791, 0, 4, { -600.000000f, -600.000000f, -545.500000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_1", 2007457, 7740888, 4, { -606.228577f, -600.000000f, -543.124695f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2007457, 7741247, 4, { -611.437622f, -602.000000f, -586.861023f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2009684, 0, 4, { -613.782715f, -602.000000f, -582.841614f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2009685, 0, 4, { -611.078125f, -602.014221f, -583.093018f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2009681, 0, 4, { 600.000000f, -600.000000f, -630.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_8", 2009682, 0, 4, { 600.000000f, -600.000000f, -600.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_9", 2009683, 0, 4, { 605.004822f, -600.000000f, -594.049011f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2007457, 7718602, 4, { 600.000000f, -600.000000f, -600.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7718606, 4, { 600.000000f, -600.000000f, -600.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7718605, 4, { 600.000000f, -600.000000f, -605.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7739045, 4, { 600.000000f, -600.000000f, -620.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2009697, 0, 4, { 599.816895f, -600.000000f, -610.040405f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2009698, 0, 4, { 593.438599f, -600.000000f, -600.488281f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2009699, 0, 4, { 605.523682f, -600.000000f, -596.581970f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_17", 2009700, 0, 4, { 600.000000f, -600.000000f, -600.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2002735, 0, 4, { -600.000000f, -624.000000f, -779.170715f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7826278, 4, { -600.000000f, -624.000000f, -779.051880f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_z3r1_b1258", 2009735, 7790960, 4, { 600.000000f, 0.000000f, 388.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_1", 2009736, 7790961, 4, { 600.000000f, 0.000000f, 258.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_2", 2009737, 7790972, 4, { -599.687073f, -599.483093f, -542.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r1_b1258_3", 2009738, 7790976, 4, { -600.000000f, -602.000000f, -623.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2002735, 0, 4, { 504.093506f, -27.491249f, 699.526611f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7791941, 4, { 503.957397f, -27.061510f, 699.645325f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7792069, 4, { 503.000000f, -25.234091f, 659.863281f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_20", 2002735, 0, 4, { -645.511597f, -587.562500f, -431.000000f }, 1.000000f, -1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2007457, 7792412, 4, { -646.396729f, -587.562500f, -431.310394f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2007457, 7792413, 4, { -606.465515f, -587.562500f, -431.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Teleportationcrystal", 2009717, 7790245, 4, { 494.000000f, -36.900440f, 764.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_1", 2009718, 7790248, 4, { 595.000000f, -2.896687f, 404.905212f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_2", 2009719, 7790262, 4, { 597.404175f, -31.000000f, -16.571730f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_3", 2009720, 7790602, 4, { -650.538818f, -588.000000f, -436.780487f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_4", 2009721, 7790603, 4, { -604.447327f, -599.975830f, -519.493408f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Teleportationcrystal_5", 2009722, 7790604, 4, { -604.814819f, -624.000000f, -771.833679f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0286", 2007457, 7724970, 4, { 500.022797f, -38.986820f, 782.467285f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 600.027710f, -600.000000f, -620.645081f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheOrbonneMonastery );