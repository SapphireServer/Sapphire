#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheAquapolis :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAquapolis() :
    Sapphire::ScriptAPI::InstanceContentScript( 55001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Treasurecoffer", 2007190, 0, 4, { 0.001130f, 0.200000f, 340.004486f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_1", 2007191, 0, 4, { 0.002947f, -7.800000f, 215.005096f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_2", 2007192, 0, 4, { 0.002900f, -15.800000f, 90.001167f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_3", 2007193, 0, 4, { -0.000139f, -23.819401f, -34.999279f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Treasurecoffer_4", 2007194, 0, 4, { 0.001485f, -31.815121f, -160.003693f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Treasurecoffer_5", 2007195, 0, 4, { 0.004197f, -39.810791f, -284.993011f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Treasurecoffer_6", 2007196, 0, 4, { 0.000420f, -47.806580f, -409.995514f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -0.122746f, 0.000000f, 361.538513f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6288992, 4, { 0.686486f, 0.049996f, 362.050415f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Vaultdoor", 2007203, 6287388, 4, { -18.243860f, 0.099997f, 321.842285f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultdoor_1", 2007204, 6287665, 4, { 18.988001f, 0.099997f, 321.533508f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007287, 6288229, 4, { -25.275770f, 0.000000f, 340.210388f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007288, 6288231, 4, { 0.185137f, 0.000000f, 312.600098f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007289, 6288233, 4, { 25.078310f, 0.000000f, 339.623596f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultkey", 2007282, 0, 4, { 0.829522f, 0.220668f, 337.850708f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007316, 6288699, 4, { -18.478701f, -5.661133f, 279.285889f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2007317, 6286455, 4, { 15.609920f, -6.088379f, 277.302094f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2007328, 6383033, 4, { -16.922300f, 0.076233f, 321.705902f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2007329, 6383032, 4, { 18.844851f, 0.076233f, 322.468903f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_8", 2007343, 6289147, 4, { 3.738403f, 0.198364f, 339.833588f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_9", 2002735, 0, 4, { -0.120655f, -7.700002f, 236.767395f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6289205, 4, { -0.442505f, -7.827942f, 237.140396f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Vaultdoor_2", 2007205, 6288210, 4, { -18.722839f, -7.827942f, 196.063095f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Vaultdoor_3", 2007206, 6288211, 4, { 18.844851f, -7.827942f, 196.185196f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2007290, 6288342, 4, { -25.317570f, -7.980009f, 215.039398f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007291, 6288340, 4, { 0.322333f, -7.980009f, 189.283798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007292, 6288337, 4, { 24.222750f, -7.980009f, 215.066498f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultkey_1", 2007311, 0, 4, { -3.870050f, -7.800000f, 213.458496f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007318, 6288701, 4, { -16.983280f, -13.870480f, 153.185303f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2007319, 6286451, 4, { 16.678040f, -13.962040f, 152.574997f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2007330, 6383034, 4, { -17.685249f, -7.797425f, 197.619507f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2007331, 6383035, 4, { 18.509090f, -7.827942f, 197.497406f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2007344, 6289152, 4, { -1.286773f, -7.800001f, 215.448593f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6289228, 4, { -0.142505f, -15.800000f, 112.190002f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_18", 2002735, 0, 4, { 0.053155f, -15.700000f, 111.576698f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Vaultdoor_4", 2007207, 6288213, 4, { -18.719660f, -15.805200f, 71.150551f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultdoor_5", 2007208, 6288215, 4, { 18.666090f, -15.800000f, 71.347427f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007293, 6288400, 4, { -25.407360f, -15.950010f, 89.850311f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2007294, 6288402, 4, { 0.914349f, -15.950010f, 64.629997f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2007295, 6288404, 4, { 24.828060f, -15.950010f, 89.997643f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultkey_2", 2007312, 0, 4, { 0.302402f, -15.800000f, 94.839752f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2007320, 6288702, 4, { -17.441099f, -21.797001f, 28.519039f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2007321, 6286453, 4, { 16.342409f, -21.896730f, 28.458010f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_24", 2007332, 6383037, 4, { -16.861271f, -15.915160f, 70.694946f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_25", 2007333, 6383036, 4, { 18.326050f, -15.915160f, 72.465088f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_26", 2007345, 6289153, 4, { 4.112751f, -15.800000f, 94.003380f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6289248, 4, { -0.327447f, -23.797190f, -12.626270f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_27", 2002735, 0, 4, { -0.005597f, -23.697189f, -13.437240f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Vaultdoor_6", 2007209, 6288216, 4, { -18.686550f, -23.797190f, -53.735790f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultdoor_7", 2007210, 6288218, 4, { 18.561710f, -23.797190f, -53.381920f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2007296, 6288442, 4, { -24.187929f, -23.863649f, -34.945591f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2007297, 6288444, 4, { 0.165738f, -23.873119f, -62.594398f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2007298, 6288446, 4, { 25.276409f, -23.913509f, -35.549301f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultkey_3", 2007313, 0, 4, { -2.565299f, -23.799999f, -37.906879f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2007322, 6288703, 4, { -16.708679f, -29.892460f, -96.391296f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_32", 2007323, 6288689, 4, { 15.640440f, -30.075560f, -97.917236f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_33", 2007334, 6383039, 4, { -17.044371f, -23.910950f, -54.093319f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_34", 2007335, 6383038, 4, { 18.326050f, -23.910950f, -52.323238f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_35", 2007346, 6289154, 4, { 1.893377f, -23.785940f, -36.201401f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6289271, 4, { -0.402360f, -31.785391f, -137.661194f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_36", 2002735, 0, 4, { 0.026965f, -31.685390f, -138.459503f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Vaultdoor_8", 2007211, 6288221, 4, { -18.820810f, -31.785391f, -179.046600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultdoor_9", 2007212, 6288219, 4, { 18.590670f, -31.785391f, -178.683807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_37", 2007299, 6288471, 4, { -25.063971f, -31.928049f, -159.375900f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_38", 2007300, 6288469, 4, { -0.225626f, -31.950010f, -184.941803f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_39", 2007301, 6288473, 4, { 24.164009f, -31.929609f, -159.852798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultkey_4", 2007314, 0, 4, { -1.933799f, -31.799999f, -161.905502f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_40", 2007324, 6288704, 4, { -15.976260f, -38.010250f, -222.247696f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_41", 2007325, 6288690, 4, { 15.274170f, -38.071289f, -222.339203f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_42", 2007336, 6383042, 4, { -17.596230f, -31.900000f, -178.846298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_43", 2007337, 6383041, 4, { 18.875370f, -31.906679f, -177.538803f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_44", 2007347, 6289155, 4, { 1.494756f, -31.797430f, -156.976593f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2002872, 6289287, 4, { -0.102360f, -39.780590f, -262.818298f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_45", 2002735, 0, 4, { -0.061376f, -39.680592f, -263.631805f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Vaultdoor_10", 2007213, 6288224, 4, { -18.631350f, -39.810791f, -303.547699f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Vaultdoor_11", 2007214, 6288223, 4, { 18.847080f, -39.780579f, -304.087585f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_46", 2007302, 6288508, 4, { -24.544001f, -39.909939f, -284.787201f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_47", 2007303, 6288524, 4, { -0.272618f, -39.928360f, -310.519714f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_48", 2007304, 6288522, 4, { 24.354900f, -39.900742f, -285.109314f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Vaultkey_5", 2007315, 0, 4, { -2.969681f, -39.799999f, -286.637512f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_49", 2007326, 6288705, 4, { -15.793150f, -45.975460f, -346.730804f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_50", 2007327, 6288694, 4, { 16.555969f, -46.005981f, -347.859894f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_51", 2007338, 6383044, 4, { -17.091330f, -39.875000f, -302.618896f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_52", 2007339, 6383045, 4, { 17.074829f, -39.902340f, -303.334198f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_53", 2007348, 6289156, 4, { 1.662274f, -39.779591f, -284.155792f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2002872, 6289300, 4, { 0.019862f, -47.800430f, -387.795288f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_54", 2002735, 0, 4, { 0.060846f, -47.799999f, -388.568115f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.076233f, -47.887440f, -427.461304f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_55", 2007305, 6288552, 4, { -24.623159f, -47.927639f, -409.027313f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_56", 2007306, 6288548, 4, { -0.124747f, -47.950401f, -433.348785f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_57", 2007307, 6288550, 4, { 23.612570f, -47.899090f, -409.669586f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_58", 2007349, 6395686, 4, { 2.822051f, -47.754410f, -409.509888f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6289067, 5, { 1.346699f, 0.199998f, 429.462097f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 3.438223f, -0.100000f, 415.292694f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheAquapolis );