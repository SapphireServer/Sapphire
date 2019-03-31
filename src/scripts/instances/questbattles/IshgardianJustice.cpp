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

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( IshgardianJustice );