#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ASeriesofUnfortunateEvents : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_GOAL_POS_01 = 5886177;
  static constexpr auto BNPC_COMPANION_EMMANELLAIN = 5886178;
  static constexpr auto BNPC_COMPANION_HAURCHEFANT = 5886179;
  static constexpr auto BNPC_COMPANION_SOLDIER = 5886180;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_01 = 5886181;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_02 = 5886182;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_03 = 5886191;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_04 = 5886193;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_05 = 5886194;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_06 = 5886196;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_07 = 5886197;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_08 = 5886198;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_09 = 5886200;
  static constexpr auto BNPC_ENEMY_THAUMATURGE_VANUVANU_10 = 5886201;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_11 = 5886207;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_12 = 5886208;
  static constexpr auto BNPC_ENEMY_THAUMATURGE_VANUVANU_13 = 5886209;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_14 = 5886211;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_15 = 5886212;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_16 = 5886213;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_17 = 5886214;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_18 = 5886217;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_19 = 5886218;
  static constexpr auto BNPC_ENEMY_THAUMATURGE_VANUVANU_20 = 5886219;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_21 = 5891945;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_22 = 5891946;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_23 = 5891947;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_24 = 5891948;
  static constexpr auto ENPC_GOAL_SOLDIER = 5886176;
  static constexpr auto ENPC_ELDER_VANUVANU = 5886237;
  static constexpr auto POPRANGE_HAURCHEFANT_MOVE_POS_01 = 5886220;
  static constexpr auto POPRANGE_SOLDIER_MOVE_POS_01 = 5886221;
  static constexpr auto ERANGE_VANUVANU_TERRITORY_01 = 5886222;
  static constexpr auto EOBJ_ARREST_01 = 5886226;
  static constexpr auto QIB_YELL_01 = 2647;
  static constexpr auto QIB_YELL_02 = 2692;
  static constexpr auto QIB_YELL_03 = 2693;
  static constexpr auto QIB_YELL_04 = 2695;
  static constexpr auto QIB_YELL_05 = 2696;
  static constexpr auto QIB_YELL_06 = 2697;
  static constexpr auto EVENT_ACTION_ARREST = 42;
  static constexpr auto CUT_SCENE_N_01 = 794;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto BGM_LATE_BATTLE = 39;
  static constexpr auto BEHAVIOR_EMMANELLAIN_RELEASED = 30600;
  static constexpr auto BNPC_WAY_STOP = 5904722;
  static constexpr auto BNPC_STATE_CAUGHT = 118;
  static constexpr auto BNPC_STATE_NORMAL = 0;
  static constexpr auto LOC_POS_ACTOR0 = 5908313;
  static constexpr auto LOC_POS_ACTOR1 = 5908314;
  static constexpr auto LOC_POS_ACTOR2 = 5908315;
  static constexpr auto LOC_ACTOR0 = 1012438;
  static constexpr auto LOC_ACTOR1 = 1012472;
  static constexpr auto LOC_ACTOR2 = 1012471;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_CAUTION = 4227;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_KNEE_SEACH = 1014;

public:
  ASeriesofUnfortunateEvents() : Sapphire::ScriptAPI::QuestBattleScript( 104 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ASeriesofUnfortunateEvents );