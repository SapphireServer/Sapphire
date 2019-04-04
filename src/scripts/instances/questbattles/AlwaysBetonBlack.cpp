#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AlwaysBetonBlack : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_A_01 = 4278135;
  static constexpr auto INIT_P_POP_1ST_B_01 = 4278137;
  static constexpr auto INIT_P_POP_1ST_C_01 = 4278138;
  static constexpr auto INIT_POP_BOSS = 4278139;
  static constexpr auto INIT_POP_2ND_VOIDGATE_A = 4278142;
  static constexpr auto INIT_POP_2ND_VOIDGATE_B = 4278143;
  static constexpr auto INIT_POP_3RD_VOIDGATE_C = 4278156;
  static constexpr auto INIT_POP_3RD_C_01_RANDOM_POP = 4278157;
  static constexpr auto INIT_POP_2ND_A_01_RANDOM_POP = 4278336;
  static constexpr auto INIT_POP_2ND_B_01_RANDOM_POP = 4278337;
  static constexpr auto INIT_ENPC_POP_01 = 4284477;
  static constexpr auto CUT_START_NCUT = 344;
  static constexpr auto CUT_END_NCUT = 345;
  static constexpr auto QIB_YELL_01 = 1872;
  static constexpr auto QIB_YELL_02 = 1873;
  static constexpr auto QIB_YELL_03 = 1874;
  static constexpr auto POP_RANGE_DAZA_MOVE = 4330432;
  static constexpr auto JOB_STORY_MES = 3646;

public:
  AlwaysBetonBlack() : Sapphire::ScriptAPI::QuestBattleScript( 74 )
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

EXPOSE_SCRIPT( AlwaysBetonBlack );