#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheCompanyYouKeepTwinAdder : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_A = 4103768;
  static constexpr auto INIT_P_POP_B = 4103769;
  static constexpr auto INIT_P_POP_C = 4103770;
  static constexpr auto INIT_POP_TOP = 4103775;
  static constexpr auto INIT_POP_THM1_1 = 4103777;
  static constexpr auto INIT_POP_LNC1_2 = 4103779;
  static constexpr auto INIT_POP_LNC1_3 = 4103793;
  static constexpr auto INIT_POP_ARC1_4 = 4103781;
  static constexpr auto INIT_POP_ARC1_5 = 4103782;
  static constexpr auto INIT_POP_ARC2_1 = 4103786;
  static constexpr auto INIT_POP_ARC2_2 = 4103787;
  static constexpr auto INIT_POP_MAC2_3 = 4103788;
  static constexpr auto DEF_ACTION_MONSTER_WHISTLE = 983;
  static constexpr auto CUT_SCENE_01 = 217;
  static constexpr auto LOC_ACTOR0 = 1003836;
  static constexpr auto LOC_ACTOR1 = 1003837;
  static constexpr auto LOC_ACTOR2 = 1005026;
  static constexpr auto LOC_POS_ACTOR0 = 4161958;
  static constexpr auto POP_RANGE_BOSS_01 = 4165238;
  static constexpr auto POP_RANGE_BOSS_02 = 4165240;
  static constexpr auto POP_RANGE_BOSS_03 = 4165241;
  static constexpr auto DEF_ACTION_DRILL_ROCKET = 525;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto LOC_ACTOR9 = 1006149;

public:
  TheCompanyYouKeepTwinAdder() : Sapphire::ScriptAPI::QuestBattleScript( 46 )
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

EXPOSE_SCRIPT( TheCompanyYouKeepTwinAdder );