#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BrotherfromAnotherMother : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_ENPC_POP_1_ERIC_01 = 4306244;
  static constexpr auto INIT_EOBJ_POP_1_MACHIN_01 = 4306245;
  static constexpr auto INIT_POP_1_IMP_01 = 4306246;
  static constexpr auto INIT_POP_1_IMP_02 = 4306247;
  static constexpr auto INIT_POP_1_IMP_03 = 4306248;
  static constexpr auto INIT_POP_1_IMP_04 = 4306249;
  static constexpr auto INIT_POP_1_IMP_05 = 4306250;
  static constexpr auto INIT_POP_1_IMP_06 = 4306251;
  static constexpr auto INIT_POP_2_IMP_BOSS_01 = 4306253;
  static constexpr auto INIT_POP_3_MASEKIKUN_01 = 4306259;
  static constexpr auto INIT_POP_3_MASEKIKUN_02 = 4306260;
  static constexpr auto INIT_POP_3_MASEKIKUN_03 = 4306261;
  static constexpr auto CUT_END_NCUT = 338;
  static constexpr auto LOC_POS_ACTOR0 = 4324013;
  static constexpr auto LOC_ACTOR0 = 1006749;
  static constexpr auto LOC_ACTOR1 = 1007892;
  static constexpr auto LOC_ACTOR2 = 1007893;
  static constexpr auto LOC_ACTOR3 = 1007894;
  static constexpr auto LOC_POS_ACTOR1 = 4325065;
  static constexpr auto LOC_POS_ACTOR2 = 4325150;

public:
  BrotherfromAnotherMother() : Sapphire::ScriptAPI::QuestBattleScript( 70 )
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

EXPOSE_SCRIPT( BrotherfromAnotherMother );