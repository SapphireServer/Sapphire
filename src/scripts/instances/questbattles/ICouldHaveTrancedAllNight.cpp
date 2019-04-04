#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ICouldHaveTrancedAllNight : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_ROEGA_01 = 5919002;
  static constexpr auto P_BNPC_YAMITRA_01 = 5919004;
  static constexpr auto BNPC_CUP_01 = 5919028;
  static constexpr auto BNPC_IF_EGI_A = 5919032;
  static constexpr auto BNPC_TAI_EGI_A = 5919041;
  static constexpr auto BNPC_GAL_EGI_A = 5919042;
  static constexpr auto BNPC_IF_EGI_B = 5919046;
  static constexpr auto BNPC_TAI_EGI_B = 5919047;
  static constexpr auto BNPC_GAL_EGI_B = 5919048;
  static constexpr auto EOBJ_BAHA_AETHER_AREA_01 = 5919142;
  static constexpr auto EOBJ_BAHA_AETHER_AREA_02 = 5919143;
  static constexpr auto EOBJ_BAHA_AETHER_AREA_03 = 5919144;
  static constexpr auto EOBJ_BAHA_AETHER_AREA_04 = 5919145;
  static constexpr auto EOBJ_BAHA_AETHER_AREA_05 = 5919146;
  static constexpr auto EOBJ_BAHA_AETHER_AREA_06 = 5919147;
  static constexpr auto STATUS_PARAM_BAHA_AETHER = 1754;
  static constexpr auto STATUS_BAHA_TRANS = 1750;
  static constexpr auto EVENT_ACTION_01 = 19;
  static constexpr auto LOG_MESSAGE_BAHA_FIRE_SENSE_01 = 3280;
  static constexpr auto LOG_MESSAGE_BAHA_WING_SENSE_01 = 3282;
  static constexpr auto LOG_MESSAGE_BAHA_CLAW_SENSE_01 = 3284;
  static constexpr auto LOG_MESSAGE_BAHA_IMAGE_01 = 3281;
  static constexpr auto LOG_MESSAGE_BAHA_IMAGE_02 = 3283;
  static constexpr auto LOG_MESSAGE_BAHA_IMAGE_03 = 3285;
  static constexpr auto LOG_MESSAGE_BAHA_IMAGE_04 = 3286;
  static constexpr auto LOG_MESSAGE_BAHA_IMAGE_05 = 3287;
  static constexpr auto LOG_MESSAGE_BAHA_IMAGE_06 = 3288;
  static constexpr auto LOG_MESSAGE_TRANS_SUCCESS = 3289;
  static constexpr auto NCUT_01 = 967;
  static constexpr auto POPRANGE_EGI_01 = 5923525;
  static constexpr auto POPRANGE_EGI_02 = 5923528;
  static constexpr auto POPRANGE_EGI_03 = 5923529;
  static constexpr auto POPRANGE_EGI_04 = 5923531;
  static constexpr auto POPRANGE_EGI_05 = 5923532;
  static constexpr auto POPRANGE_EGI_06 = 5923533;
  static constexpr auto LCUT_ACTOR0 = 1014921;
  static constexpr auto LCUT_ACTOR1 = 1013845;
  static constexpr auto LCUT_ACTOR2 = 1014636;
  static constexpr auto LCUT_POS_ACTOR0 = 5923743;
  static constexpr auto LCUT_POS_ACTOR1 = 5918992;
  static constexpr auto LCUT_POS_ACTOR2 = 5919028;
  static constexpr auto BNPC_BASE_ID_CUP_01 = 4897;
  static constexpr auto LCUT_ACTION0 = 983;
  static constexpr auto BNPC_TOUMEI_TRANCE_EFFECT = 5959636;
  static constexpr auto BNPC_ACTION_TRANCE_EFFECT = 5074;
  static constexpr auto LCUT_BGM0 = 114;
  static constexpr auto LCUT_POS_CAM0 = 5963631;
  static constexpr auto LOC_VFX0 = 251;
  static constexpr auto LOC_SE0 = 52;
  static constexpr auto BNPC_HATE_SCAPEGOAT = 7022197;

public:
  ICouldHaveTrancedAllNight() : Sapphire::ScriptAPI::QuestBattleScript( 149 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgbg_l1p1_q3_swhu1", 2005078, 5573675, 4, { -150.601807f, -15.195440f, 86.396042f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_1", 2005079, 5573676, 4, { -160.177505f, -15.426880f, 111.877502f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_2", 2005080, 5573677, 4, { -178.133102f, -15.426880f, 85.038406f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_3", 2005081, 5573687, 4, { 147.790497f, -15.205700f, 85.606216f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_4", 2005082, 5573688, 4, { 181.170303f, -15.426880f, 81.284790f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_5", 2005083, 5573689, 4, { 160.730392f, -15.457460f, 117.518303f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_6", 2005084, 5573690, 4, { -0.015289f, -15.426890f, -162.924103f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_7", 2005085, 5573691, 4, { 19.010250f, -15.416970f, -200.015396f }, 1.000000f, -0.000000f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "sgbg_l1p1_q3_swhu1_8", 2005086, 5573692, 4, { -18.994480f, -15.426890f, -199.992798f }, 0.991760f, 0.000048f ); 
    // States -> magic_go (id: 33) magic_down (id: 56) magic_2down (id: 57) magic_on (id: 58) magic_2on (id: 59) 
    instance.registerEObj( "unknown_0", 2004187, 4724282, 4, { 0.000000f, -7.200000f, -268.700012f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004188, 4724284, 4, { 232.307495f, -7.200000f, 134.122894f }, 1.000000f, 0.542586f ); 
    instance.registerEObj( "unknown_2", 2004189, 4724283, 4, { -232.837494f, -7.217590f, 134.416702f }, 0.991760f, 1.033762f ); 
    instance.registerEObj( "sgvf_l1p1_lvd_b0441", 2004202, 4797506, 4, { -0.101569f, 30.000000f, 1.413736f }, 1.000000f, 0.000000f ); 
    // States -> STAGE_def (id: 2) STAGE_pop_anim (id: 3) 
    instance.registerEObj( "Magitekreaper", 2007710, 0, 4, { -0.135500f, 28.501801f, 18.021700f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007722, 6642830, 4, { 7.805808f, 29.000000f, 0.239120f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ICouldHaveTrancedAllNight );