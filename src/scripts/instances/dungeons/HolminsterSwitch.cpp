#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HolminsterSwitch : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HolminsterSwitch() : Sapphire::ScriptAPI::InstanceContentScript( 72 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 8034851, 4, { -15.988860f, 0.000000f, 239.195007f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 7919148, 5, { -173.037598f, 0.028157f, 472.339813f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -170.169006f, -0.052084f, 465.809113f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 134.000000f, 23.000000f, -481.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -15.030150f, 0.000000f, 259.662689f }, 0.747620f, 0.000048f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 77.958252f, -0.015320f, -62.088989f }, 0.747620f, 0.000048f); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 134.000000f, 23.000000f, -445.276703f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7919159, 4, { -15.000000f, 0.001882f, 260.689209f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7919160, 4, { -15.000000f, 0.000000f, 220.626999f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7919163, 4, { 77.988770f, 0.066764f, -61.600712f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7919164, 4, { 78.000000f, 0.000000f, -101.523201f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7919167, 4, { 134.000000f, 23.000000f, -444.545105f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2007457, 7766071, 4, { -94.923630f, 0.244103f, 327.373901f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 7766073, 4, { -15.000000f, 0.058673f, 282.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 7924368, 4, { -17.676380f, 0.102258f, 283.322296f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 7924367, 4, { -11.264750f, 0.280228f, 284.311615f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 7845443, 4, { 28.000000f, -9.095052f, 32.314899f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 7845444, 4, { 78.000000f, 0.038061f, -41.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 7924600, 4, { 78.000000f, 0.054927f, -290.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 7845464, 4, { 134.000000f, 23.955830f, -423.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 7925757, 4, { 107.000000f, 0.205189f, -280.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 7925776, 4, { 41.000000f, 0.054927f, -256.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_14", 2007457, 8003818, 4, { -14.000000f, 0.135563f, 282.999908f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_15", 2007457, 8003816, 4, { -15.915160f, 0.309660f, 285.969208f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_16", 2007457, 8003819, 4, { -17.410589f, 0.221467f, 288.136108f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_17", 2007457, 8003817, 4, { -10.452450f, 0.233707f, 287.800415f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_col_wall_04", 2007457, 8049923, 4, { 29.000000f, -8.060932f, 33.000000f }, 1.000000f, 0.000000f); 
    // States -> col_on (id: 24) col_off (id: 25) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HolminsterSwitch );