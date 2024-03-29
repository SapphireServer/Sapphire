#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class DzemaelDarkhold : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DzemaelDarkhold() : Sapphire::ScriptAPI::InstanceContentScript( 13 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2000033, 3328371, 4229633, 4, { 79.909241f, 1.268266f, 161.509598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2000066, 3328664, 4229634, 4, { 144.020004f, -6.834667f, 162.001907f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "GrandHallgate", 2000438, 3328665, 4229635, 4, { 98.210373f, -6.834594f, 111.974403f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2000453, 0, 4229636, 4, { 79.384338f, -10.733530f, 106.701599f }, 1.000000f, -0.706750f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2000452, 4229638, 4229637, 4, { 76.745064f, -11.090400f, 105.321198f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Magitektransporter", 2000458, 0, 4229639, 4, { 23.358509f, -12.304620f, 57.612831f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "MagitekterminalI", 2000476, 4256808, 4233731, 4, { 80.927979f, 1.365243f, 173.289703f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_tarmn1_on (id: 3) vf_tarmn1_of (id: 4) vf_tarmn2_on (id: 12) vf_bg_on (id: 18) vf_bg_of (id: 28) 
    instance.addEObj( "MagitekterminalIII", 2000478, 4256810, 4233733, 4, { 124.023804f, -13.794070f, 123.296898f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_tarmn1_on (id: 3) vf_tarmn1_of (id: 4) vf_tarmn2_on (id: 12) vf_bg_on (id: 18) vf_bg_of (id: 28) 
    instance.addEObj( "MagitekterminalIV", 2000479, 4256811, 4233734, 4, { 140.853195f, -11.962310f, 113.256302f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_tarmn1_on (id: 3) vf_tarmn1_of (id: 4) vf_tarmn2_on (id: 12) vf_bg_on (id: 18) vf_bg_of (id: 28) 
    instance.addEObj( "sgvf_r1r1_b0173", 2000276, 4255636, 4255649, 4, { 36.155140f, 8.079000f, 207.374298f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0173_1", 2000276, 4255639, 4255651, 4, { 112.091797f, -3.877179f, 176.216904f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0173_2", 2000276, 4255640, 4255652, 4, { 139.427399f, -10.726720f, 108.501404f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0173_3", 2000276, 4255644, 4255653, 4, { 67.860687f, -14.328120f, 84.076920f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0173_4", 2000276, 4255645, 4255654, 4, { 51.562908f, -11.769940f, 111.841400f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0173_5", 2000276, 4255646, 4255655, 4, { 18.496250f, -15.965690f, 87.930252f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0173_6", 2000276, 4255648, 4255656, 4, { 19.309570f, -10.954800f, 51.356911f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_b_on (id: 5) vfbright_b_off (id: 6) 
    instance.addEObj( "unknown_2", 2000279, 4247600, 4260481, 4, { 35.302368f, 8.108457f, 206.288605f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2000279, 4247601, 4260542, 4, { 111.093102f, -3.403727f, 176.495895f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2000279, 4247603, 4260592, 4, { 68.310699f, -14.257320f, 83.756592f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2000279, 4247604, 4260596, 4, { 52.317631f, -11.815490f, 110.621300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2000279, 4247605, 4260597, 4, { 18.860821f, -14.036660f, 88.283234f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2000279, 4247606, 4260598, 4, { 20.972610f, -11.172370f, 51.726391f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2000279, 4247602, 4260625, 4, { 138.802094f, -10.764680f, 110.383400f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Magitektransporter_1", 2000474, 0, 4233741, 4, { -96.800278f, -30.000010f, -41.821941f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2000455, 0, 4233742, 4, { -106.309601f, -26.688049f, -16.372990f }, 0.991760f, 0.737616f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2000454, 4233746, 4233744, 4, { -107.679703f, -26.639919f, -15.815070f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_10", 2000487, 4184823, 4233750, 4, { -111.157799f, -22.833250f, 2.271249f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_r1r1_b0174", 2000490, 4255705, 4236228, 4, { -242.711304f, -24.146959f, -32.381401f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_1", 2000490, 4255691, 4236251, 4, { -261.321289f, -25.547960f, -34.986919f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_2", 2000490, 4255694, 4236255, 4, { -261.811310f, -26.640051f, -20.854830f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_3", 2000490, 4255706, 4236320, 4, { -237.266907f, -48.000000f, -0.833767f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_4", 2000490, 4255707, 4236321, 4, { -217.921600f, -18.200211f, 20.315559f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_5", 2000490, 4255708, 4236323, 4, { -169.460999f, -33.749729f, 51.753731f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_6", 2000490, 4255709, 4236324, 4, { -166.205704f, -33.174091f, 41.379780f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_7", 2000490, 4255710, 4236326, 4, { -136.133698f, -24.761801f, 11.194330f }, 1.000000f, 0.000000f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "unknown_11", 2000280, 4247607, 4260626, 4, { -260.415710f, -25.404510f, -36.083500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2000280, 4247608, 4260627, 4, { -262.467896f, -26.663879f, -21.408119f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2000280, 4247609, 4260641, 4, { -241.470901f, -24.060431f, -29.972530f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2000280, 4247611, 4260649, 4, { -238.320496f, -47.903111f, -3.008399f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2000280, 4247610, 4260650, 4, { -219.957108f, -17.854340f, 18.911011f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2000280, 4247613, 4260651, 4, { -168.223907f, -33.658329f, 50.704330f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2000280, 4247612, 4260652, 4, { -165.114899f, -32.678890f, 41.844219f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2000280, 4247614, 4260654, 4, { -133.651001f, -24.416229f, 10.934760f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_emp_b0021", 2000488, 4233760, 4233762, 4, { 13.842580f, -15.160090f, -143.072693f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_baria_on (id: 1) vf_baria_off (id: 2) 
    instance.addEObj( "MagitekterminalVIII", 2000483, 4256818, 4233766, 4, { -16.049601f, -17.297310f, -177.329498f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_tarmn1_on (id: 3) vf_tarmn1_of (id: 4) vf_tarmn2_on (id: 12) vf_bg_on (id: 18) vf_bg_of (id: 28) 
    instance.addEObj( "MagitekterminalIX", 2000484, 4256819, 4233768, 4, { -14.914310f, -21.075211f, -144.145996f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_tarmn1_on (id: 3) vf_tarmn1_of (id: 4) vf_tarmn2_on (id: 12) vf_bg_on (id: 18) vf_bg_of (id: 28) 
    instance.addEObj( "unknown_19", 2000457, 0, 4233769, 4, { 56.778809f, -36.148682f, -150.835495f }, 0.991760f, 0.957075f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2000456, 4233771, 4233770, 4, { 55.222290f, -35.782471f, -150.255600f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_r1r1_b0174_8", 2000490, 4255718, 4236416, 4, { -48.459080f, -19.742540f, -176.405197f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_9", 2000490, 4255720, 4236418, 4, { -11.239590f, -21.204630f, -144.906204f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_10", 2000490, 4255721, 4236421, 4, { -15.353870f, -17.228140f, -178.818893f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_11", 2000490, 4255722, 4236578, 4, { 29.525160f, -23.532890f, -108.452202f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_12", 2000490, 4255723, 4236579, 4, { 27.773970f, -23.532040f, -114.936401f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_13", 2000490, 4255725, 4236580, 4, { 64.981979f, -38.499950f, -172.408997f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_14", 2000490, 4255728, 4236581, 4, { 70.785149f, -37.665981f, -203.212097f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "sgvf_r1r1_b0174_15", 2000490, 4255729, 4236582, 4, { 105.072098f, -38.024330f, -158.260803f }, 0.991760f, 0.000048f, 0); 
    // States -> vfbright_o_on (id: 5) vfbright_o_off (id: 6) 
    instance.addEObj( "unknown_20", 2000280, 4246846, 4260657, 4, { -45.950432f, -19.312410f, -177.762207f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2000280, 4246848, 4260659, 4, { -14.610830f, -21.218700f, -145.140900f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2000280, 4246847, 4260660, 4, { -16.411739f, -16.383909f, -180.914902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2000280, 4246849, 4260661, 4, { 26.993160f, -23.453131f, -107.682999f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_24", 2000280, 0, 4260662, 4, { 32.493099f, -24.000099f, -113.021797f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2000280, 4246850, 4260663, 4, { 66.021332f, -38.500019f, -172.238098f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2000280, 4246851, 4260664, 4, { 70.452782f, -37.655048f, -202.913803f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2000280, 4246852, 4260665, 4, { 103.330498f, -38.100510f, -159.167999f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit_1", 2000139, 0, 4233773, 4, { 79.243332f, -38.930771f, -182.480194f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 4229601, 4229612, 5, { -48.620270f, 19.892130f, 221.013596f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 4229630, 4, { -44.993790f, 14.002300f, 204.521896f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( DzemaelDarkhold );