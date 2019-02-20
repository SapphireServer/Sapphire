#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheRidoranaLighthouse :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheRidoranaLighthouse() :
    Sapphire::ScriptAPI::InstanceContentScript( 30068 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7377897, 4, { -200.000305f, 5.000000f, 101.000000f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2007791, 0, 4, { -200.000305f, 5.000000f, 101.000000f }, 0.880000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7377900, 4, { -200.000107f, 4.999996f, 30.600080f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2009485, 0, 4, { -211.062103f, 5.000000f, 63.169151f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r2_b1409", 2007457, 7379112, 4, { -210.250793f, 5.000000f, 72.932854f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -200.002106f, 584.000000f, -510.574188f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7388431, 4, { -200.002106f, 584.000000f, -509.807709f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2009508, 0, 4, { -200.000000f, 584.000000f, -541.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_4", 2009509, 0, 4, { -200.000000f, 584.000000f, -541.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7448801, 4, { -200.002106f, 584.000000f, -570.796204f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7387054, 4, { 800.000000f, -968.000000f, -110.439796f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2007457, 7387076, 4, { 800.000000f, -968.000000f, -171.377106f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2007457, 7387494, 4, { 777.444885f, -440.500000f, 812.995483f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 7387496, 4, { 800.000000f, -440.500000f, 774.175781f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 7387498, 4, { 822.724609f, -440.500000f, 812.995483f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 7370829, 4, { 800.000000f, -968.000000f, -141.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 7401445, 4, { 800.000000f, -440.000000f, 800.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3r2_b1444", 2007457, 7409377, 4, { 800.000000f, -968.000000f, -141.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { 800.000000f, -968.000000f, -109.954399f }, 1.200000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2007457, 7380261, 4, { 799.984619f, -815.518372f, -369.771912f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_11", 2002735, 0, 4, { 800.000000f, -815.500000f, -370.055695f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7359055, 5, { -181.813400f, 14.312280f, 237.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 800.146179f, -815.500000f, -417.868286f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_col_wall_02", 2007457, 7447710, 4, { -200.061096f, 12.985350f, -21.103331f }, 0.991760f, 0.000048f ); 
    // States -> col_on (id: 24) col_off (id: 25) 
    instance.registerEObj( "Ancientclockworkdevice", 2009544, 7334375, 4, { -269.105011f, 122.000000f, -438.046509f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7404715, 4, { -268.778900f, 123.000000f, -449.397705f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2007457, 7447787, 4, { -269.825287f, 278.980713f, -520.805725f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_col_wall_02_1", 2007457, 7447840, 4, { -226.977997f, 429.983887f, -438.986786f }, 0.991760f, 0.000048f ); 
    // States -> col_on (id: 24) col_off (id: 25) 
    instance.registerEObj( "unknown_14", 2007457, 7447789, 4, { -199.398300f, 432.999908f, -475.179199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Ancientclockworkdevice_1", 2009545, 7371810, 4, { -199.628098f, 584.000000f, -585.090027f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 7404716, 4, { -199.364105f, 584.999817f, -599.228027f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Ancientclockworkdevice_2", 2009546, 7377745, 4, { 837.565613f, -984.000000f, 96.709007f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Ancientclockworkdevice_3", 2009547, 7377746, 4, { 772.549072f, -979.951721f, -38.537811f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_col_wall_02_2", 2007457, 7447954, 4, { 840.023987f, -984.000000f, 103.811798f }, 1.000000f, 0.000000f ); 
    // States -> col_on (id: 24) col_off (id: 25) 
    instance.registerEObj( "sgbg_col_wall_02_3", 2007457, 7447962, 4, { 770.034485f, -979.851624f, -46.041550f }, 1.000000f, 0.000000f ); 
    // States -> col_on (id: 24) col_off (id: 25) 
    instance.registerEObj( "unknown_16", 2007457, 7447790, 4, { 800.592407f, -967.000000f, -202.262695f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3r1_a4_stn03", 2007457, 7450744, 4, { 798.167419f, -815.500000f, -404.830505f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Ancientengraving", 2009579, 0, 4, { -194.500000f, 15.000000f, -19.750000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Crudescrawling", 2009580, 0, 4, { 835.500000f, -986.500000f, 68.750000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Crudescrawling_1", 2009581, 0, 4, { 764.500000f, -983.000000f, -16.250000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Teleportationcrystal", 2009534, 7359613, 4, { -187.989700f, 14.788980f, 218.822296f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_1", 2009535, 7359705, 4, { -204.159302f, 112.000000f, -395.631805f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_2", 2009536, 7359716, 4, { -251.343994f, 428.000000f, -517.234192f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_3", 2009537, 7359767, 4, { -203.934204f, 582.000122f, -493.438599f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_4", 2009538, 7359772, 4, { 844.205322f, -988.006409f, 73.136467f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Teleportationcrystal_5", 2009539, 7359776, 4, { 767.945312f, -968.000000f, 90.974548f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_6", 2009540, 7359779, 4, { 795.302795f, -972.000000f, -95.739433f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Teleportationcrystal_7", 2009541, 7359782, 4, { 792.833984f, -806.109985f, -299.344299f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2002735, 0, 4, { 769.949524f, -964.000000f, 77.562500f }, 0.700000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_7", 2007457, 7407058, 4, { 769.975586f, -964.000000f, 76.127197f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgbg_col_wall_02_4", 2007457, 7445782, 4, { 770.168579f, -964.019226f, 37.949100f }, 0.991760f, 0.000048f ); 
    // States -> col_on (id: 24) col_off (id: 25) 
    instance.registerEObj( "unknown_18", 2007457, 7409325, 4, { 761.133728f, -964.000000f, 38.468330f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_19", 2007457, 7409326, 4, { 766.931396f, -964.000000f, 38.589489f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_20", 2007457, 7409327, 4, { 772.973328f, -964.000000f, 38.480419f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_21", 2007457, 7409328, 4, { 779.146301f, -964.000000f, 38.587101f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2007457, 7407517, 4, { 751.235291f, -964.000000f, 66.028107f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2007457, 7408156, 4, { 751.337280f, -964.000000f, 59.946270f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_24", 2007457, 7409322, 4, { 751.462219f, -964.000000f, 53.939960f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_25", 2007457, 7409323, 4, { 751.451477f, -964.000000f, 47.949421f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_26", 2007457, 7409332, 4, { 788.401917f, -963.999878f, 65.974800f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_27", 2007457, 7409331, 4, { 788.503784f, -963.999878f, 59.892960f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_28", 2007457, 7409330, 4, { 788.601318f, -964.019226f, 53.879639f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_29", 2007457, 7409329, 4, { 788.618225f, -964.000000f, 47.896111f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheRidoranaLighthouse );