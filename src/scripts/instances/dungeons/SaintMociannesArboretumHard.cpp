#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SaintMociannesArboretumHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SaintMociannesArboretumHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 62 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7559255, 4, { 17.974501f, 3.000000f, -90.677597f }, 1.000000f, 1.125737f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7559254, 4, { -0.052845f, 2.999999f, -62.073700f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 17.974501f, 3.000000f, -90.677597f }, 1.000000f, 1.125738f ); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 70.045998f, -358.660889f, -67.820099f }, 1.688311f, 0.785398f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7559344, 4, { 70.045998f, -358.660889f, -67.820099f }, 1.000000f, 0.785398f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7559345, 4, { 102.958000f, -358.631592f, -100.732101f }, 1.000000f, 0.785398f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 7559351, 4, { 338.763000f, -345.520905f, -336.862915f }, 1.000000f, 0.785398f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 338.763000f, -345.520905f, -336.862915f }, 1.400000f, 0.785398f ); 
    instance.registerEObj( "unknown_3", 2007457, 7515300, 4, { 102.128502f, 2.975464f, 35.873901f }, 0.991760f, 1.004917f ); 
    instance.registerEObj( "unknown_4", 2007457, 7400978, 4, { 65.087173f, -0.256883f, -77.312302f }, 1.000000f, -0.647398f ); 
    instance.registerEObj( "unknown_5", 2009584, 0, 4, { 86.116272f, -3.500000f, -58.246311f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2009584, 0, 4, { 87.258659f, -3.500000f, -55.799931f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2009584, 0, 4, { 87.003143f, -3.500000f, -64.240150f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2009584, 0, 4, { 85.276199f, -3.500000f, -62.320759f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2009584, 0, 4, { 69.948387f, -3.500000f, -54.553860f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2009584, 0, 4, { 71.547699f, -3.500000f, -53.240009f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2009584, 0, 4, { 70.050743f, -3.500000f, -57.845982f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2009584, 0, 4, { 69.676193f, -3.500000f, -61.626770f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7447179, 4, { -44.805130f, -358.181885f, -123.967300f }, 1.000000f, 1.080362f ); 
    instance.registerEObj( "unknown_14", 2007457, 7447178, 4, { 34.771999f, -359.432800f, -63.961380f }, 1.000000f, 1.325989f ); 
    instance.registerEObj( "unknown_15", 2007457, 7509045, 4, { 221.466904f, -355.000092f, -183.157898f }, 1.000000f, 1.483875f ); 
    instance.registerEObj( "unknown_16", 2007457, 7509048, 4, { 290.509186f, -355.000000f, -247.817902f }, 1.000000f, 0.479966f ); 
    instance.registerEObj( "unknown_17", 2007457, 7515074, 4, { 242.213501f, -355.000000f, -209.642807f }, 1.000000f, -0.523599f ); 
    instance.registerEObj( "unknown_18", 2007457, 7515073, 4, { 283.367798f, -355.000000f, -227.097702f }, 1.000000f, 0.427606f ); 
    instance.registerEObj( "Waterconduit", 2009585, 7515078, 4, { 248.199799f, -353.799988f, -211.263702f }, 1.000000f, -0.358281f ); 
    instance.registerEObj( "Waterconduit_1", 2009586, 7515076, 4, { 287.357208f, -353.810913f, -230.909302f }, 0.991760f, 0.573861f ); 
    instance.registerEObj( "Entrance", 2000182, 7403516, 5, { -0.091100f, 0.000000f, 140.477798f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 4.219900f, 0.000000f, 131.545197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 363.235107f, -345.525208f, -361.334991f }, 1.000000f, -0.785398f ); 
    instance.registerEObj( "unknown_19", 2007457, 7575616, 4, { 352.620697f, -345.510101f, -350.728607f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SaintMociannesArboretumHard );