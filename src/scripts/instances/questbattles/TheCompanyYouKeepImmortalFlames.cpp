#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheCompanyYouKeepImmortalFlames : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_A = 4105366;
  static constexpr auto INIT_P_POP_B = 4105365;
  static constexpr auto INIT_P_POP_C = 4105364;
  static constexpr auto INIT_POP_TOP = 4105369;
  static constexpr auto INIT_POP_THM1_1 = 4105370;
  static constexpr auto INIT_POP_LNC1_2 = 4105373;
  static constexpr auto INIT_POP_LNC1_3 = 4105375;
  static constexpr auto INIT_POP_ARC1_4 = 4105371;
  static constexpr auto INIT_POP_ARC1_5 = 4105372;
  static constexpr auto INIT_POP_ARC2_1 = 4105390;
  static constexpr auto INIT_POP_ARC2_2 = 4105392;
  static constexpr auto INIT_POP_MAC2_3 = 4105368;
  static constexpr auto DEF_ACTION_MONSTER_WHISTLE = 983;
  static constexpr auto CUT_SCENE_01 = 219;
  static constexpr auto LOC_ACTOR0 = 1003836;
  static constexpr auto LOC_ACTOR1 = 1003837;
  static constexpr auto LOC_ACTOR2 = 1005027;
  static constexpr auto LOC_POS_ACTOR0 = 4163972;
  static constexpr auto POP_RANGE_BOSS_01 = 4165244;
  static constexpr auto POP_RANGE_BOSS_02 = 4165245;
  static constexpr auto POP_RANGE_BOSS_03 = 4165246;
  static constexpr auto DEF_ACTION_DRILL_ROCKET = 525;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto LOC_ACTOR9 = 1006150;

public:
  TheCompanyYouKeepImmortalFlames() : Sapphire::ScriptAPI::QuestBattleScript( 47 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Exit", 2000605, 0, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000606, 3861081, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000604, 4262798, 5, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheCompanyYouKeepImmortalFlames );