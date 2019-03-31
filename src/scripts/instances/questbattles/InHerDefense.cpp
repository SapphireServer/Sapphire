#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class InHerDefense : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_OBORO_01 = 5907854;
  static constexpr auto BNPC_COMPANION_AKAGI_01 = 5907861;
  static constexpr auto BNPC_ENEMY_ROSALINDE_01 = 5907866;
  static constexpr auto BNPC_ENEMY_REDWAY_01 = 5907870;
  static constexpr auto BNPC_ENEMY_PACK_A_EXC_01 = 5907872;
  static constexpr auto BNPC_ENEMY_PACK_A_ARC_01 = 5907873;
  static constexpr auto BNPC_ENEMY_PACK_A_ARC_02 = 5907874;
  static constexpr auto BNPC_ENEMY_PACK_B_EXC_01 = 5907875;
  static constexpr auto BNPC_ENEMY_PACK_B_EXC_02 = 5907876;
  static constexpr auto BNPC_ENEMY_PACK_B_ARC_01 = 5907877;
  static constexpr auto BNPC_ENEMY_PACK_C_EXC_01 = 5907878;
  static constexpr auto BNPC_ENEMY_PACK_C_EXC_02 = 5907879;
  static constexpr auto BNPC_ENEMY_PACK_C_ARC_01 = 5907880;
  static constexpr auto BNPC_ENEMY_RANDOM_POP_01 = 5907881;
  static constexpr auto BNPC_ENEMY_RANDOM_BAT_01 = 5907882;
  static constexpr auto BNPC_ENEMY_PACK_D_EXC_01 = 5907883;
  static constexpr auto BNPC_ENEMY_PACK_D_EXC_02 = 5907884;
  static constexpr auto BNPC_ENEMY_PACK_D_EXC_03 = 5907885;
  static constexpr auto BNPC_ENEMY_PACK_E_EXC_01 = 5907887;
  static constexpr auto BNPC_ENEMY_PACK_E_EXC_02 = 5907888;
  static constexpr auto BNPC_ENEMY_PACK_E_CNJ_01 = 5907889;
  static constexpr auto ENPC_ROSALINDE_01 = 5907902;
  static constexpr auto ENPC_YUKI_01 = 5907903;
  static constexpr auto ENPC_SERVANT_01 = 5907904;
  static constexpr auto ENPC_SERVANT_02 = 5907905;
  static constexpr auto CUT_SCENE_01 = 962;
  static constexpr auto EOBJ_OBORO_HANDS_ON = 5908237;
  static constexpr auto EVENT_ACTION_01 = 42;
  static constexpr auto BAT_POP_INTERVAL_1 = 12;
  static constexpr auto MOVING_POINT_01 = 5908273;
  static constexpr auto LCUT_ACTOR0 = 1013846;
  static constexpr auto LCUT_ACTOR1 = 1013847;
  static constexpr auto LCUT_ACTOR2 = 1013850;
  static constexpr auto LCUT_ACTOR3 = 1013851;
  static constexpr auto LCUT_ACTOR4 = 1010597;
  static constexpr auto LCUT_POS_ACTOR0 = 5907903;
  static constexpr auto LCUT_POS_ACTOR1 = 5907904;
  static constexpr auto LCUT_POS_ACTOR2 = 5907905;
  static constexpr auto LCUT_BASE_ACTION0 = 1056;
  static constexpr auto LCUT_ACTION0 = 1062;
  static constexpr auto YELL_QIB_01 = 3157;
  static constexpr auto YELL_QIB_02 = 3158;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_PLAYER_01 = 5931210;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_PLAYER_02 = 5931211;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_PLAYER_03 = 5931212;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_FIXED_POINT = 5931680;
  static constexpr auto BNPC_RAITON_TARGET_01 = 5931380;
  static constexpr auto BNPC_RAITON_TARGET_02 = 5931383;
  static constexpr auto BNPC_RAITON_TARGET_03 = 5931384;
  static constexpr auto BNPC_RAITON_TARGET_04 = 5931386;
  static constexpr auto BNPC_RAITON_TARGET_05 = 5931387;
  static constexpr auto BNPC_RAITON_TARGET_06 = 5931388;
  static constexpr auto BNPC_RAITON_TARGET_07 = 5931390;
  static constexpr auto BNPC_RAITON_TARGET_08 = 5931391;
  static constexpr auto BNPC_RAITON_TARGET_09 = 5931392;
  static constexpr auto DEF_ACTION_RAITON_GT = 4977;
  static constexpr auto STATUS_HOLMGANG = 88;
  static constexpr auto BNPC_ACTION_EXECUTION = 1003;
  static constexpr auto EOBJ_MAKIBISHI = 5933081;
  static constexpr auto STATUS_MAKIBISHI_DAMAGE = 1221;
  static constexpr auto DEF_ACTION_MAKIBISHI = 4987;
  static constexpr auto BNPC_ESCAPE = 5935138;
  static constexpr auto BNPC_ACTION_OBORO_ESCAPE_TORIGGER = 3269;
  static constexpr auto STATUS_HYOUTON_BIND = 612;

public:
  InHerDefense() : Sapphire::ScriptAPI::QuestBattleScript( 131 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgvf_w_btl_b0485", 2004341, 4797423, 4, { -368.761902f, 1.900000f, 20.220869f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_1", 2004342, 4797424, 4, { -367.525085f, 1.900000f, 26.995680f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_2", 2004343, 4797425, 4, { -371.746185f, 1.900000f, 32.584270f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_3", 2004338, 4797426, 4, { -362.507385f, 1.900000f, 48.482269f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_4", 2004339, 4797427, 4, { -355.184601f, 1.899924f, 47.853260f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_5", 2004340, 4797428, 4, { -349.628601f, 1.899914f, 52.138340f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_6", 2004335, 4797429, 4, { -334.406708f, 1.899990f, 43.799950f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_7", 2004336, 4797430, 4, { -336.870087f, 1.900000f, 37.104382f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_8", 2004337, 4797431, 4, { -332.837006f, 1.900000f, 30.666309f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_9", 2004344, 4797421, 4, { -341.024414f, 1.880961f, 15.649740f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_10", 2004345, 4797419, 4, { -348.232788f, 1.900000f, 15.852800f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "sgvf_w_btl_b0485_11", 2004346, 4797422, 4, { -353.540588f, 1.899946f, 11.553900f }, 1.000000f, -0.000000f ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 
    instance.registerEObj( "Entrance", 2000182, 4685106, 5, { 320.642792f, 3.735552f, 302.314301f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 220.874298f, 64.988159f, 13.046390f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 4685143, 4, { 220.800797f, 64.801514f, 13.539410f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2004050, 4685147, 4, { 219.745102f, 64.682983f, -33.707211f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgpl_w_transparent05", 2004049, 4685157, 4, { 219.958694f, 65.018677f, 47.991199f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -60.079769f, 44.339741f, -124.669800f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 4685162, 4, { -61.990799f, 44.123230f, -125.263000f }, 1.000000f, -1.570451f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2004051, 4685163, 4, { -98.791832f, 44.299992f, -124.783699f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -315.480286f, 1.957748f, 33.432499f }, 0.991760f, -1.184874f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 4685167, 4, { -314.885803f, 1.999334f, 32.833080f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 325.360901f, 6.499028f, 292.726807f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2004052, 4584550, 4, { 165.269104f, 52.440060f, -190.280197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Stonepedestal", 2004057, 4588393, 4, { 163.784195f, 52.706680f, -185.027100f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2004053, 4584553, 4, { -35.849411f, 44.986191f, -124.177696f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Stonepedestal_1", 2004058, 4588617, 4, { -32.145729f, 44.996059f, -118.336502f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Stonepedestal_2", 2004059, 4588610, 4, { -32.404221f, 44.937031f, -128.964096f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -326.989685f, 2.000000f, 43.114891f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer", 2004074, 0, 4, { 191.947693f, 59.006939f, -163.899307f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_1", 2004075, 0, 4, { 194.472900f, 59.156731f, -165.022003f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_2", 2004076, 0, 4, { 196.017197f, 59.853050f, -161.548294f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_3", 2004077, 0, 4, { 198.798004f, 60.096630f, -162.115204f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_4", 2004078, 0, 4, { 199.929993f, 60.852970f, -158.189896f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Treasurecoffer_5", 2004079, 0, 4, { 203.014206f, 61.084290f, -158.453995f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Wildbananatree", 2004062, 4706914, 4, { 206.036896f, 65.302567f, -27.040119f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Wildbananatree_1", 2004063, 4722842, 4, { 199.376907f, 64.682983f, -11.735090f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Wildbananatree_2", 2004064, 4706915, 4, { 205.968002f, 64.690811f, 3.866779f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Wildbananatree_3", 2004065, 4706916, 4, { 236.652100f, 64.927116f, -28.061340f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2004066, 0, 4, { 206.655502f, 65.036621f, -25.903111f }, 0.991760f, -1.260904f ); 
    instance.registerEObj( "unknown_6", 2004067, 0, 4, { 200.604294f, 64.690804f, -10.987260f }, 0.991760f, -0.736456f ); 
    instance.registerEObj( "unknown_7", 2004068, 0, 4, { 206.716095f, 64.690811f, 3.346290f }, 0.991760f, -0.921409f ); 
    instance.registerEObj( "unknown_8", 2004069, 0, 4, { 235.736603f, 64.682983f, -27.115360f }, 0.991760f, 0.613842f ); 
    instance.registerEObj( "unknown_9", 2004060, 4585424, 4, { -218.153107f, -0.000002f, -6.398464f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2004061, 4585624, 4, { -307.270905f, 4.409851f, 14.023010f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Wildbananatree_4", 2004070, 4722840, 4, { 241.380005f, 64.956383f, -12.841170f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Wildbananatree_5", 2004071, 4706917, 4, { 234.644501f, 64.824364f, 2.652663f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2004072, 0, 4, { 239.884903f, 64.690811f, -12.610960f }, 1.000000f, 0.600320f ); 
    instance.registerEObj( "unknown_12", 2004073, 0, 4, { 233.623596f, 64.760551f, 2.089992f }, 1.000000f, 0.684586f ); 
    instance.registerEObj( "unknown_13", 2004129, 0, 4, { -80.000000f, 44.200001f, -124.500000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( InHerDefense );