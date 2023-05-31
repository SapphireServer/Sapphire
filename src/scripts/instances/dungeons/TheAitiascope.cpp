#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheAitiascope : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAitiascope() : Sapphire::ScriptAPI::InstanceContentScript( 81 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8860625, 4, { -6.076300f, 163.990005f, 491.024689f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -5.894696f, 164.099701f, 491.290192f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2002872, 0, 4, { -6.161700f, 164.000000f, 450.922913f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8861074, 4, { 11.265500f, -211.304596f, 164.748901f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 11.233800f, -211.304596f, 164.060699f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8861079, 4, { 10.535600f, -211.304596f, 123.263000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8861216, 4, { 10.891000f, -236.000000f, -469.521393f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 10.627130f, -236.000000f, -469.930115f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8714601, 4, { -59.800171f, 195.298904f, 471.915802f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8714897, 4, { 11.485400f, 188.117401f, 413.951294f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8714895, 4, { 42.389000f, 176.054398f, 480.888794f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aethercurrent", 2011758, 8704746, 4, { -6.000100f, 163.990005f, 471.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8756228, 4, { 18.936399f, -200.958206f, 345.754211f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8756229, 4, { 6.240906f, -211.673096f, 215.472702f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 0, 4, { -6.732378f, -176.300095f, 473.402710f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 8747490, 4, { 10.971250f, -235.870895f, -453.513397f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 8730149, 4, { 9.700000f, -212.600006f, -123.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 8730150, 4, { -19.700100f, -241.555603f, -326.699890f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 8742252, 4, { 19.299999f, -228.500000f, -198.100006f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_14", 2007457, 8742253, 4, { -11.100000f, -235.500000f, -245.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8870226, 5, { -1.636515f, 200.016006f, 602.472412f }, 1.000000f, -0.294116f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -8.697377f, 200.011597f, 557.860901f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 10.819770f, -236.000000f, -505.018890f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheAitiascope );