#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheKeytoVictory : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto EOBJ_ALARM = 6978148;
  static constexpr auto EOBJ_BARREL = 6978149;
  static constexpr auto EOBJ_IRON = 6978150;
  static constexpr auto EOBJ_POT = 6978151;
  static constexpr auto EOBJ_LUMBER = 6978152;
  static constexpr auto EOBJ_DIARY = 6978154;
  static constexpr auto BNPC_P1_TRASH_01 = 6978191;
  static constexpr auto BNPC_P1_TRASH_02 = 6978193;
  static constexpr auto BNPC_P1_TRASH_03 = 6978194;
  static constexpr auto BNPC_P1_TRASH_04 = 6978195;
  static constexpr auto BNPC_P1_TRASH_05 = 6978196;
  static constexpr auto BNPC_P1_TRASH_06 = 6978199;
  static constexpr auto BNPC_P1_TRASH_07 = 6978201;
  static constexpr auto P_BNPC_WISCAR = 6978206;
  static constexpr auto P_BNPC_LYSE = 6978207;
  static constexpr auto P_BNPC_ALPHINAUD = 6978208;
  static constexpr auto P_BNPC_THANCRED = 6978209;
  static constexpr auto PR_P1_ALLY_MOVE_01 = 6978215;
  static constexpr auto PR_P1_ALLY_MOVE_02 = 6978239;
  static constexpr auto PR_P1_ALLY_MOVE_03 = 6978333;
  static constexpr auto PR_P1_ALLY_MOVE_04 = 6978240;
  static constexpr auto PR_P1_ALLY_MOVE_05 = 6978241;
  static constexpr auto PR_P1_ALLY_MOVE_06 = 6978341;
  static constexpr auto PR_P1_ALLY_MOVE_07 = 6978342;
  static constexpr auto PR_P2_ALLY_MOVE_01 = 6978405;
  static constexpr auto PR_P2_ALLY_MOVE_02 = 6978406;
  static constexpr auto PR_P2_ALLY_MOVE_03 = 6978407;
  static constexpr auto PR_P2_ALLY_MOVE_04 = 6978408;
  static constexpr auto EVENT_ACTION_01 = 21;
  static constexpr auto EVENT_ACTION_02 = 41;
  static constexpr auto BNPC_P2_IRONMAN_DIARY = 6978255;
  static constexpr auto BNPC_P2_VANGUARD_01 = 6978438;
  static constexpr auto BNPC_P2_VANGUARD_02 = 6978439;
  static constexpr auto BNPC_P2_VANGUARD_03 = 6978440;
  static constexpr auto BNPC_P2_VANGUARD_04 = 6978441;
  static constexpr auto BNPC_P2_VANGUARD_05 = 6978490;
  static constexpr auto BNPC_P2_KAMAKIRI_01 = 6978445;
  static constexpr auto BNPC_P2_KAMAKIRI_02 = 6978446;
  static constexpr auto BNPC_P2_KAMAKIRI_03 = 6978447;
  static constexpr auto BNPC_P2_KAMAKIRI_04 = 6978448;
  static constexpr auto BNPC_P2_KAMAKIRI_05 = 6978449;
  static constexpr auto BNPC_P2_KAMAKIRI_06 = 6978450;
  static constexpr auto BNPC_P2_KAMAKIRI_07 = 6978451;
  static constexpr auto SE_ALARM = 97;
  static constexpr auto BEHAVIOR_LOOK_AROUND = 30471;
  static constexpr auto BEHAVIOR_THINK_SET = 30475;
  static constexpr auto BEHAVIOR_LOOK_AROUND_THINK = 30784;
  static constexpr auto BEHAVIOR_THINK_BASE = 30858;
  static constexpr auto BEHAVIOR_BASIC_STAND = 30064;
  static constexpr auto BGM_AFTER_ALARM = 39;
  static constexpr auto BGM_NORMAL = 317;
  static constexpr auto BGM_BOSS_BATTLE = 39;
  static constexpr auto YELL_LYSE_SEARCH = 5907;
  static constexpr auto YELL_THANCRED_SEARCH = 5908;
  static constexpr auto YELL_WISCAR_SEARCH = 5909;
  static constexpr auto YELL_ALPHINAUD_SEARCH = 5910;
  static constexpr auto YELL_WISCAR_ALARM_BATTLE = 5911;
  static constexpr auto BNPC_P3_TRASH_01 = 6989316;
  static constexpr auto BNPC_P3_TRASH_02 = 6989317;
  static constexpr auto BNPC_P3_TRASH_03 = 6989318;
  static constexpr auto BNPC_P3_TRASH_04 = 6989319;
  static constexpr auto BNPC_P3_TRASH_05 = 6989320;
  static constexpr auto BNPC_P3_TRASH_06 = 6989321;
  static constexpr auto BNPC_P3_TRASH_07 = 6989322;
  static constexpr auto BNPC_P3_TRASH_08 = 6989323;
  static constexpr auto BNPC_P3_TRASH_09 = 6989324;
  static constexpr auto BNPC_BOSS = 6989325;
  static constexpr auto BNPC_ENERGY_TOOL_01 = 6989326;
  static constexpr auto BNPC_ENERGY_TOOL_02 = 6989327;
  static constexpr auto CHANNELING_BOSS_TOOL = 22;
  static constexpr auto STATUS_PARAM_BOSS_TOOL = 3313;
  static constexpr auto ER_AROUND_BOSS = 6989587;
  static constexpr auto ER_NEAR_TEMPLE = 6997563;
  static constexpr auto BNPCBASE_BOSS_TOOL = 7859;
  static constexpr auto EOBJ_LOOK_AROUND = 6990528;
  static constexpr auto PR_AROUND_BOSS = 6990533;
  static constexpr auto P_BNPC_CARBUNCLE = 6990542;

public:
  TheKeytoVictory() : Sapphire::ScriptAPI::QuestBattleScript( 158 )
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

EXPOSE_SCRIPT( TheKeytoVictory );