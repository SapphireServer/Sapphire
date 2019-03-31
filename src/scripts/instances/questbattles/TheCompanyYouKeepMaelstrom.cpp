#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheCompanyYouKeepMaelstrom : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_A = 4105799;
  static constexpr auto INIT_P_POP_B = 4105800;
  static constexpr auto INIT_P_POP_C = 4105801;
  static constexpr auto INIT_POP_TOP = 4105802;
  static constexpr auto INIT_POP_THM1_1 = 4105803;
  static constexpr auto INIT_POP_LNC1_2 = 4105805;
  static constexpr auto INIT_POP_LNC1_3 = 4105804;
  static constexpr auto INIT_POP_ARC1_4 = 4105807;
  static constexpr auto INIT_POP_ARC1_5 = 4105806;
  static constexpr auto INIT_POP_ARC2_1 = 4105863;
  static constexpr auto INIT_POP_ARC2_2 = 4105864;
  static constexpr auto INIT_POP_MAC2_3 = 4105862;
  static constexpr auto DEF_ACTION_MONSTER_WHISTLE = 983;
  static constexpr auto CUT_SCENE_01 = 218;
  static constexpr auto LOC_ACTOR0 = 1003836;
  static constexpr auto LOC_ACTOR1 = 1003837;
  static constexpr auto LOC_ACTOR2 = 1005028;
  static constexpr auto LOC_POS_ACTOR0 = 4163777;
  static constexpr auto POP_RANGE_BOSS_01 = 4165248;
  static constexpr auto POP_RANGE_BOSS_02 = 4165249;
  static constexpr auto POP_RANGE_BOSS_03 = 4165250;
  static constexpr auto DEF_ACTION_DRILL_ROCKET = 525;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto LOC_ACTOR9 = 1006151;

public:
  TheCompanyYouKeepMaelstrom() : Sapphire::ScriptAPI::QuestBattleScript( 48 )
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

EXPOSE_SCRIPT( TheCompanyYouKeepMaelstrom );