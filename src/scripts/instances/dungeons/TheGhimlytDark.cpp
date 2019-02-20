#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheGhimlytDark :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheGhimlytDark() :
    Sapphire::ScriptAPI::InstanceContentScript( 64 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_g3d5_b1487", 2007457, 7721506, 4, { -175.569107f, 59.999989f, 59.862808f }, 1.000000f, -0.523599f ); 
    instance.registerEObj( "sgvf_g3d5_b1487_1", 2007457, 7721519, 4, { -170.569107f, 59.999989f, 68.526520f }, 1.000000f, -1.570796f ); 
    instance.registerEObj( "sgvf_g3d5_b1487_2", 2007457, 7721520, 4, { -175.569107f, 59.999989f, 77.183289f }, 1.000000f, -0.523599f ); 
    instance.registerEObj( "sgvf_g3d5_b1487_3", 2007457, 7721521, 4, { -185.569199f, 59.999989f, 77.183327f }, 1.000000f, 0.523599f ); 
    instance.registerEObj( "sgvf_g3d5_b1487_4", 2007457, 7721522, 4, { -190.569000f, 59.999989f, 68.526497f }, 1.000000f, 1.570796f ); 
    instance.registerEObj( "sgvf_g3d5_b1487_5", 2007457, 7721523, 4, { -185.569107f, 59.999989f, 59.862801f }, 1.000000f, 0.523599f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7724516, 4, { -163.378296f, 59.999989f, 64.744011f }, 0.991760f, 1.347288f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7724515, 4, { -180.569107f, 60.037628f, 90.162064f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -180.569107f, 59.999989f, 88.463638f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7705901, 4, { 139.729706f, 30.000000f, -48.877701f }, 1.000000f, 0.392699f ); 
    instance.registerEObj( "unknown_2", 2007457, 7705900, 4, { 147.847595f, 30.000000f, -40.759789f }, 1.000000f, 1.178098f ); 
    instance.registerEObj( "unknown_3", 2007457, 7705899, 4, { 147.847595f, 30.000000f, -29.279261f }, 1.000000f, 1.178097f ); 
    instance.registerEObj( "unknown_4", 2007457, 7705898, 4, { 139.729706f, 30.000000f, -21.161320f }, 1.000000f, 0.392699f ); 
    instance.registerEObj( "unknown_5", 2007457, 7705897, 4, { 128.249207f, 30.000000f, -21.161289f }, 1.000000f, -0.392699f ); 
    instance.registerEObj( "unknown_6", 2007457, 7705896, 4, { 120.131203f, 30.000000f, -29.279249f }, 1.000000f, -1.178097f ); 
    instance.registerEObj( "unknown_7", 2007457, 7705895, 4, { 120.131203f, 30.000000f, -40.759762f }, 1.000000f, -1.178097f ); 
    instance.registerEObj( "unknown_8", 2007457, 7705892, 4, { 128.249100f, 30.000000f, -48.877689f }, 1.000000f, -0.392699f ); 
    instance.registerEObj( "unknown_9", 2007457, 7706030, 4, { 133.989395f, 29.983999f, -35.019501f }, 1.000000f, 0.000047f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7724537, 4, { 159.954803f, 30.000000f, -60.694111f }, 0.991760f, 0.795487f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7724536, 4, { 134.000000f, 30.475479f, 7.876453f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { 134.000000f, 29.999981f, 4.287893f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7730799, 4, { 370.999512f, -15.000000f, -265.005005f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 7724557, 4, { 370.229187f, 13.917020f, -237.466904f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_12", 2002735, 0, 4, { 370.229187f, 13.833620f, -238.717896f }, 0.600000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7598910, 4, { -291.394592f, 86.251953f, 197.855392f }, 0.991760f, -1.569070f ); 
    instance.registerEObj( "unknown_14", 2007457, 7691067, 4, { -192.308197f, 66.698097f, 120.723701f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 7604094, 4, { 20.660540f, 60.425789f, 43.816551f }, 1.000000f, 0.947097f ); 
    instance.registerEObj( "unknown_16", 2007457, 7604733, 4, { 131.345901f, 35.000259f, 25.139370f }, 1.000000f, 0.296706f ); 
    instance.registerEObj( "unknown_17", 2007457, 7603911, 4, { -116.000000f, 53.488338f, 59.999962f }, 1.000000f, -0.523599f ); 
    instance.registerEObj( "unknown_18", 2007457, 7604084, 4, { -86.049500f, 57.959660f, 64.131699f }, 1.000000f, 0.959931f ); 
    instance.registerEObj( "unknown_19", 2007457, 7604086, 4, { -86.437569f, 56.909809f, 30.212589f }, 1.000000f, -0.645772f ); 
    instance.registerEObj( "unknown_20", 2007457, 7638321, 4, { -42.599991f, 55.776421f, 14.799990f }, 1.000000f, -1.361357f ); 
    instance.registerEObj( "unknown_21", 2007457, 7686957, 4, { -15.355400f, 57.836029f, 16.085300f }, 1.000000f, -0.191754f ); 
    instance.registerEObj( "unknown_22", 2007457, 7686959, 4, { -19.532499f, 58.489460f, 44.765591f }, 1.000000f, -1.529152f ); 
    instance.registerEObj( "unknown_23", 2007457, 7820490, 4, { 317.389313f, 14.592110f, -118.072304f }, 1.000000f, 1.235276f ); 
    instance.registerEObj( "unknown_24", 2007457, 7733551, 4, { 371.195312f, 5.036287f, -161.166000f }, 1.000000f, 1.235276f ); 
    instance.registerEObj( "sgvf_g3d5_b1617", 2007457, 7842118, 4, { 233.771500f, 20.000000f, -93.090919f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7705976, 5, { -414.021515f, 106.963402f, 158.088501f }, 1.000000f, 0.354109f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 371.029907f, -15.000000f, -278.640900f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -410.192993f, 107.021599f, 165.150101f }, 0.991760f, 0.354115f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheGhimlytDark );