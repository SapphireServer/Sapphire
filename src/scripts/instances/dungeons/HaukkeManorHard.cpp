#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HaukkeManorHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HaukkeManorHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 19 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -26.487801f, 17.000000f, -0.008300f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgpl_w_lvd_b0118_f1d2", 2002872, 4497628, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgbg_f1d4_c1_ori01", 2002873, 4498555, 4, { -1.869557f, 17.000000f, 15.055300f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on0 (id: 9) vf_fire_on (id: 10) vf_fire_oｆ0 (id: 11) vf_fire_oｆ (id: 12) 
    instance.registerEObj( "sgbg_f1d4_c1_ori01_1", 2002874, 4498556, 4, { -5.211004f, 17.000000f, -10.575720f }, 1.000000f, 0.000000f ); 
    // States -> vf_fire_on0 (id: 9) vf_fire_on (id: 10) vf_fire_oｆ0 (id: 11) vf_fire_oｆ (id: 12) 
    instance.registerEObj( "unknown_1", 2003318, 4484553, 4, { 23.178410f, 16.983280f, 0.137329f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 25.786711f, 0.000000f, 0.119909f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 4505837, 4, { 23.084200f, 0.000000f, -1.591900f }, 1.000000f, -1.570796f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2003126, 4521780, 4, { -20.141510f, -0.000000f, -0.141697f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -24.169260f, -18.905939f, -0.137390f }, 0.991760f, -1.551983f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 4509134, 4, { -22.072941f, -18.814390f, -0.320496f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002997, 0, 4, { -20.433430f, -18.936470f, 0.755735f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "LilyDoor", 2002915, 4484551, 4, { -28.152889f, 16.983280f, 0.015198f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_f1d4_d1_gago1", 2002917, 4505698, 4, { -36.195190f, 16.983280f, -5.685384f }, 0.991760f, 0.000048f ); 
    // States -> bg_gago1_on (id: 2) bg_gago1_oｆｆ (id: 3) bg_gago1_out (id: 4) 
    instance.registerEObj( "Crystalball", 2002916, 4488372, 4, { 28.044069f, 16.983280f, 0.168350f }, 0.991760f, 0.811345f ); 
    instance.registerEObj( "sgbg_f1d4_d1_gago1_1", 2003319, 4544200, 4, { -36.143250f, 17.000000f, 7.445584f }, 1.000000f, 0.000000f ); 
    // States -> bg_gago1_on (id: 2) bg_gago1_oｆｆ (id: 3) bg_gago1_out (id: 4) 
    instance.registerEObj( "Lockeddoor", 2003315, 4484546, 4, { 15.988830f, 17.000000f, -82.166763f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Tinykey", 2003312, 0, 4, { 23.053480f, 17.000000f, -63.610909f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Lockeddoor_1", 2003316, 4484554, 4, { 0.701762f, 17.000000f, -96.124260f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Lockeddoor_2", 2003317, 4484573, 4, { -15.941600f, 17.000000f, -86.214546f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Tinykey_1", 2003314, 0, 4, { 11.497100f, 17.000000f, -97.655212f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Tinykey_2", 2003430, 0, 4, { -10.688510f, 17.000000f, -98.849060f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2002938, 4484560, 4, { 16.478939f, 0.000000f, -83.923622f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Crystalball_1", 2002941, 4488371, 4, { -43.455170f, -0.000000f, 13.580270f }, 1.000000f, -1.392958f ); 
    instance.registerEObj( "RoseDoor", 2002943, 0, 4, { 27.084721f, -0.015320f, 0.045776f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Redkey", 2002942, 0, 4, { 58.672710f, 0.000000f, -30.483391f }, 1.000000f, -0.000345f ); 
    instance.registerEObj( "unknown_6", 2002937, 4484569, 4, { -16.476231f, 0.000000f, -69.988670f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2002944, 4499358, 4, { -16.603889f, 0.000000f, -68.606903f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2002945, 4499362, 4, { 16.527910f, 0.000000f, -85.147072f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Voidlamp", 2002939, 4488368, 4, { -29.871300f, -0.015320f, -70.456650f }, 0.991760f, 1.074421f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "Voidlamp_1", 2002940, 4488367, 4, { -17.039709f, 0.000000f, -84.537079f }, 1.000000f, -1.569551f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "Sealedbarrier", 2003321, 4545173, 4, { 29.337740f, 0.000000f, -1.101776f }, 1.000000f, 0.000000f ); 
    // States -> bg_barrier1_on (id: 3) bg_barrier1_off (id: 4) bg_barrier1_out (id: 5) 
    instance.registerEObj( "Lockeddoor_3", 2003320, 4484571, 4, { 46.738281f, -0.015320f, -35.965580f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Tinykey_3", 2003313, 0, 4, { 43.982948f, 0.000000f, -34.342270f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1", 2003463, 4588435, 4, { -5.889304f, 0.000000f, -71.199730f }, 1.000000f, 0.000000f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1_1", 2003464, 4588440, 4, { 6.823740f, 0.000000f, -82.895660f }, 1.000000f, 0.000000f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1_2", 2003465, 4588441, 4, { 16.834749f, 0.000000f, -70.555031f }, 1.000000f, 0.000000f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1_3", 2003466, 4588442, 4, { 27.007900f, 0.000000f, -82.771332f }, 1.000000f, 0.000000f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1_4", 2003467, 4588444, 4, { 34.488140f, -0.000000f, -61.907959f }, 1.000000f, 0.010569f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1_5", 2003468, 4588448, 4, { 48.546879f, 0.000000f, -53.979691f }, 1.000000f, 0.009430f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "sgbg_f1d4_v1_lmp1_6", 2003469, 4588445, 4, { 24.192520f, 0.000000f, -55.798260f }, 1.000000f, 0.000000f ); 
    // States -> vf_slamp_on0 (id: 6) vf_slamp_of (id: 12) vf_slamp_hide (id: 22) vf_slamp_on1 (id: 23) 
    instance.registerEObj( "unknown_9", 2002951, 4486667, 4, { -25.301229f, -18.799990f, -33.673420f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2002952, 4486668, 4, { 1.978515f, -18.799990f, -34.167542f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2002953, 0, 4, { 25.467291f, -18.814390f, 33.859741f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2002954, 4486671, 4, { -2.139196f, -18.799990f, 34.235821f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Sealedbarrier_1", 2002955, 4508183, 4, { -25.881571f, -18.799999f, 0.041033f }, 1.000000f, 0.000000f ); 
    // States -> bg_barrier1_on (id: 3) bg_barrier1_off (id: 4) bg_barrier1_out (id: 5) 
    instance.registerEObj( "unknown_13", 2003322, 4486669, 4, { 28.549561f, -18.799999f, -33.402039f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 4488394, 5, { 73.319580f, -0.015320f, -0.015320f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 17.397711f, -18.804060f, 0.066881f }, 0.900200f, 0.000335f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 72.756577f, 0.000000f, 5.215310f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2002913, 0, 4, { 81.361702f, 0.249998f, -0.409441f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HaukkeManorHard );