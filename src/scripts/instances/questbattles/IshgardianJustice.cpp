#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class IshgardianJustice : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_FRAY_01 = 5909968;
  static constexpr auto BNPC_ENEMY_PHASE_1_GLA_01 = 5909971;
  static constexpr auto BNPC_ENEMY_PHASE_1_LNC_01 = 5909972;
  static constexpr auto BNPC_ENEMY_PHASE_1_LNC_02 = 5909973;
  static constexpr auto WARP_PC_POINT_01 = 5909978;
  static constexpr auto BNPC_COMPANION_FRAY_02 = 5909979;
  static constexpr auto BNPC_ENEMY_PHASE_2_DARK_FIRE_01 = 5909981;
  static constexpr auto BNPC_ENEMY_PHASE_2_DARK_FIRE_02 = 5909982;
  static constexpr auto BNPC_ENEMY_PHASE_2_DARK_FIRE_03 = 5909983;
  static constexpr auto ER_RECT_01 = 5909984;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_GLA_01 = 5909990;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_LNC_01 = 5909992;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_LNC_02 = 5909993;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_CNJ_01 = 5909994;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_DARK_FIRE_01 = 5910058;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_DARK_FIRE_02 = 5910059;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_DARK_FIRE_03 = 5910060;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_A_DARK_FIRE_04 = 5910061;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_GLA_01 = 5910062;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_LNC_01 = 5910063;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_LNC_02 = 5910064;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_CNJ_01 = 5910065;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_DARK_FIRE_01 = 5910066;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_DARK_FIRE_02 = 5910067;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_DARK_FIRE_03 = 5910068;
  static constexpr auto BNPC_ENEMY_PHASE_3_PACK_B_DARK_FIRE_04 = 5910070;
  static constexpr auto ER_RECT_02 = 5910073;
  static constexpr auto BNPC_ENEMY_PHASE_4_LEADER_01 = 5910079;
  static constexpr auto BNPC_ENEMY_PHASE_4_LNC_01 = 5910080;
  static constexpr auto BNPC_ENEMY_PHASE_4_CNJ_01 = 5910081;
  static constexpr auto ENPC_DAUGHTER_01 = 5910082;
  static constexpr auto ENPC_DAUGHTER_02 = 5911134;
  static constexpr auto EOBJ_DAUGHTER_HANDS_ON = 5910084;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_01 = 5910085;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_02 = 5910086;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_03 = 5910087;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_04 = 5910088;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_05 = 5910089;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_06 = 5910090;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_07 = 5910091;
  static constexpr auto BNPC_ENEMY_PHASE_4_DARK_FIRE_08 = 5910092;
  static constexpr auto BNPC_ENEMY_PHASE_5_LNC_01 = 5910093;
  static constexpr auto BNPC_ENEMY_PHASE_5_CNJ_01 = 5910094;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_01 = 5910096;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_02 = 5910097;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_03 = 5910145;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_04 = 5910146;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_05 = 5910147;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_06 = 5910148;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_07 = 5910149;
  static constexpr auto BNPC_ENEMY_PHASE_5_DARK_FIRE_08 = 5910150;
  static constexpr auto BNPC_ENEMY_BIG_DARK_FIRE_01 = 5910172;
  static constexpr auto EVENT_ACTION_01 = 34;
  static constexpr auto LOGMESSAGE_DARK_HEART_30 = 3276;
  static constexpr auto LOGMESSAGE_DARK_HEART_60 = 3277;
  static constexpr auto LOGMESSAGE_DARK_HEART_100 = 3278;
  static constexpr auto LOGMESSAGE_DARK_FIRE_POP = 3279;
  static constexpr auto ACTION_DARK_FIRE = 4736;
  static constexpr auto BNPC_TYPE_01_DARK_FIRE = 4643;
  static constexpr auto BNPC_TOUMEI_FOLLOW_PLAYER = 5912186;
  static constexpr auto BEHAVIOR_FRAY_01 = 30607;
  static constexpr auto ER_RECT_03 = 5912223;
  static constexpr auto QIB_YELL_01 = 2770;
  static constexpr auto QIB_YELL_02 = 2771;
  static constexpr auto QIB_YELL_03 = 2772;
  static constexpr auto POP_RANGE_ENEMY_RETREAT = 5912400;
  static constexpr auto ER_RECT_04 = 5912508;
  static constexpr auto STATUS_PARAM_KNOCK_DOWN = 1414;
  static constexpr auto LOC_ACTOR1 = 1014592;
  static constexpr auto LOC_ACTOR2 = 1014985;
  static constexpr auto LOC_ACTOR3 = 1014986;
  static constexpr auto LOC_ACTOR4 = 1014987;
  static constexpr auto LOC_ACTOR5 = 1014988;
  static constexpr auto LOC_ACTOR6 = 1014989;
  static constexpr auto LOC_POS = 5927429;

public:
  IshgardianJustice() : Sapphire::ScriptAPI::QuestBattleScript( 145 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Frightenedmaid", 2006125, 0, 5910084, 4, { 137.239105f, 14.553130f, -150.328796f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2005421, 0, 5853399, 4, { 120.661400f, 14.953100f, -156.627701f }, 0.600000f, -0.758220f, 0); 
    instance.addEObj( "Entrance", 2005548, 0, 5864780, 4, { -3.824143f, 42.343750f, -207.975098f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "×エンタープライズ", 2005537, 0, 5862288, 4, { 142.961700f, -14.267210f, 81.864616f }, 0.991760f, 1.262533f, 0); 
    instance.addEObj( "×エンタープライズ_1", 2005496, 0, 5859607, 4, { 191.696899f, -14.358760f, 56.672119f }, 0.991760f, -0.696368f, 0); 
    instance.addEObj( "unknown_1", 2006290, 0, 5922578, 4, { 151.634705f, -9.185400f, -64.945099f }, 1.000000f, -0.565068f, 0); 
    instance.addEObj( "×荷物", 2006261, 0, 5919081, 4, { -246.376404f, -20.034920f, -64.671799f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Heavysack", 2006262, 0, 5919181, 4, { -246.355606f, -20.034920f, -64.667526f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2006263, 0, 5919187, 4, { -15.228990f, 16.009670f, -7.465327f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2006264, 0, 5919190, 4, { -15.229000f, 16.009670f, -7.465300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2006276, 0, 5938056, 4, { 71.847321f, 10.122830f, -107.188301f }, 1.000000f, -1.489029f, 0); 
    instance.addEObj( "unknown_5", 2006277, 0, 5938057, 4, { 84.444199f, 10.054900f, -122.395401f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005398, 0, 5837940, 4, { 192.984497f, -14.347900f, 56.339401f }, 1.000000f, 0.628319f, 0); 
    instance.addEObj( "unknown_7", 2005399, 0, 5837944, 4, { 192.984497f, -14.347900f, 56.339401f }, 1.000000f, 0.628319f, 0); 
    instance.addEObj( "Chocobofodder", 2006242, 0, 5926953, 4, { -245.428207f, -20.034920f, -87.637817f }, 1.000000f, 0.444177f, 0); 
    instance.addEObj( "Elaissestrap", 2006246, 0, 5926965, 4, { -218.386597f, -16.034901f, -34.677299f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2006257, 0, 5926966, 4, { -218.386597f, -16.034901f, -34.677299f }, 0.500000f, 1.473381f, 0); 
    instance.addEObj( "Elaissestrap_1", 2006247, 0, 5926967, 4, { -229.219406f, -20.034901f, -83.054001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2006258, 0, 5926968, 4, { -229.219406f, -20.034901f, -83.053993f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Elaissestrap_2", 2006248, 0, 5926969, 4, { -252.145706f, -20.034920f, -57.655361f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Counterfeitcoin", 2006249, 0, 5926970, 4, { -164.690704f, -12.598410f, -25.944920f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Counterfeitcoin_1", 2006250, 0, 5926971, 4, { -117.031898f, -4.511617f, -24.726210f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Counterfeitcoin_2", 2006251, 0, 5926972, 4, { -87.077316f, -4.710484f, -13.968680f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Counterfeitcoin_3", 2006252, 0, 5926973, 4, { 46.372070f, 11.997600f, 43.778080f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Counterfeitcoin_4", 2006253, 0, 5926974, 4, { 116.746696f, -4.712837f, -26.627081f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2006331, 0, 5926976, 4, { 118.821701f, -11.634940f, -13.348590f }, 0.500000f, -1.178418f, 0); 
    instance.addEObj( "Bottomlesspurse", 2006330, 0, 5926977, 4, { 118.821701f, -11.634900f, -13.348600f }, 0.750000f, 0.000000f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( IshgardianJustice );