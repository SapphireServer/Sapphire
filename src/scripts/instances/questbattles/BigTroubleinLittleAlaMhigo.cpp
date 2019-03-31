#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BigTroubleinLittleAlaMhigo : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4251863;
  static constexpr auto INIT_P_POP_02 = 4251864;
  static constexpr auto INIT_P_POP_03 = 4251867;
  static constexpr auto INIT_P_POP_04 = 4251873;
  static constexpr auto INIT_P_POP_05 = 4251874;
  static constexpr auto INIT_POP_1ST_01 = 4252035;
  static constexpr auto INIT_POP_1ST_02 = 4252772;
  static constexpr auto INIT_POP_1ST_03 = 4252773;
  static constexpr auto INIT_POP_1ST_04 = 4252774;
  static constexpr auto INIT_POP_1ST_05 = 4252775;
  static constexpr auto INIT_POP_1ST_06 = 4252776;
  static constexpr auto INIT_POP_2ST_01 = 4252781;
  static constexpr auto INIT_POP_2ST_02 = 4252782;
  static constexpr auto INIT_POP_2ST_03 = 4252783;
  static constexpr auto INIT_POP_2ST_04 = 4252784;
  static constexpr auto INIT_POP_2ST_05 = 4252785;
  static constexpr auto INIT_POP_3ST_01 = 4252786;
  static constexpr auto INIT_POP_3ST_02 = 4252787;
  static constexpr auto INIT_POP_3ST_03 = 4252788;
  static constexpr auto INIT_POP_3ST_04 = 4252789;
  static constexpr auto INIT_POP_3ST_05 = 4252790;
  static constexpr auto YELL_QIB_01 = 1127;
  static constexpr auto YELL_QIB_02 = 1128;
  static constexpr auto LOC_ACTOR0 = 1006215;
  static constexpr auto LOC_ACTOR1 = 1008116;
  static constexpr auto LOC_ACTOR2 = 1007661;
  static constexpr auto LOC_ACTOR3 = 1007662;
  static constexpr auto LOC_ACTOR4 = 1007663;
  static constexpr auto LOC_ACTOR5 = 1003230;
  static constexpr auto LOC_ACTOR6 = 1003228;
  static constexpr auto LOC_ACTOR7 = 1003228;
  static constexpr auto LOC_POS_ACTOR0 = 4316733;
  static constexpr auto LOC_POS_ACTOR1 = 4316734;
  static constexpr auto LOC_POS_ACTOR2 = 4316737;
  static constexpr auto LOC_POS_ACTOR3 = 4316740;
  static constexpr auto LOC_POS_ACTOR4 = 4316745;
  static constexpr auto LOC_ACTION1 = 936;
  static constexpr auto LOC_ACTION2 = 985;
  static constexpr auto LOC_BGM1 = 83;

public:
  BigTroubleinLittleAlaMhigo() : Sapphire::ScriptAPI::QuestBattleScript( 58 )
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

EXPOSE_SCRIPT( BigTroubleinLittleAlaMhigo );