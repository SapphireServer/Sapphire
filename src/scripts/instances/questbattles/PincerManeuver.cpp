#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class PincerManeuver : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4256744;
  static constexpr auto INIT_P_POP_02 = 4256746;
  static constexpr auto INIT_P_POP_03 = 4256747;
  static constexpr auto INIT_P_POP_PET = 4256749;
  static constexpr auto INIT_POP_A_01 = 4256750;
  static constexpr auto INIT_POP_A_02 = 4256751;
  static constexpr auto INIT_POP_B_01 = 4256753;
  static constexpr auto INIT_POP_B_02 = 4256754;
  static constexpr auto INIT_POP_B_03 = 4256755;
  static constexpr auto INIT_POP_A_03 = 4256758;
  static constexpr auto INIT_POP_A_04 = 4256759;
  static constexpr auto INIT_POP_A_05 = 4256760;
  static constexpr auto INIT_POP_B_04 = 4256761;
  static constexpr auto INIT_POP_B_05 = 4256762;
  static constexpr auto INIT_POP_B_06 = 4256763;
  static constexpr auto INIT_POP_C_01 = 4256766;
  static constexpr auto INIT_POP_C_02 = 4256772;
  static constexpr auto INIT_POP_A_06 = 4256776;
  static constexpr auto INIT_POP_A_07 = 4256777;
  static constexpr auto INIT_POP_B_07 = 4256782;
  static constexpr auto INIT_POP_B_08 = 4256783;
  static constexpr auto INIT_POP_D_01 = 4256788;
  static constexpr auto INIT_POP_D_02 = 4304848;
  static constexpr auto INIT_POP_E_01 = 4256789;
  static constexpr auto INIT_POP_ENPC_01 = 4257118;
  static constexpr auto LOC_FACE0 = 612;
  static constexpr auto LOC_FACE1 = 620;
  static constexpr auto LOC_ACTOR1 = 1005192;
  static constexpr auto LOC_ACTOR2 = 1005193;
  static constexpr auto LOC_ACTOR3 = 1005194;
  static constexpr auto LOC_ACTOR4 = 1005190;
  static constexpr auto LOC_ACTOR0 = 1005250;
  static constexpr auto LOC_POS_ACTOR0 = 4273868;
  static constexpr auto LOC_POS_ACTOR1 = 4273880;
  static constexpr auto LOC_POS_ACTOR2 = 4273891;
  static constexpr auto LOC_POS_ACTOR3 = 4277041;
  static constexpr auto LOC_POS_ACTOR10 = 4278520;
  static constexpr auto LOC_POS_ACTOR11 = 4278527;
  static constexpr auto LOC_POS_ACTOR12 = 4278563;
  static constexpr auto LOC_ACTOR10 = 1008051;
  static constexpr auto LOC_ACTOR11 = 1008052;
  static constexpr auto LOC_ACTOR12 = 1008053;
  static constexpr auto LOC_ACTOR13 = 1008049;
  static constexpr auto LOC_ACTOR14 = 1008050;
  static constexpr auto LOC_ACTION0 = 937;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 1307;
  static constexpr auto BGM_BOSSBATTLE = 39;
  static constexpr auto INIT_EOBJ_LUGGAGE = 4322719;
  static constexpr auto INIT_EOBJ_BOOK_CHARA = 4322716;
  static constexpr auto INIT_EOBJ_BOOK_TARGET = 4322717;
  static constexpr auto EVENT_QIB_CLSACN200_01 = 3223;
  static constexpr auto EVENT_ACTION_01 = 31;
  static constexpr auto POP_RANGE_MOVE_AERSTHOTA = 4323244;
  static constexpr auto POP_RANGE_MOVE_THUBYRGEIM = 4323248;
  static constexpr auto POP_RANGE_MOVE_GEISSFRYN = 4323251;
  static constexpr auto LOC_ACTION1 = 1006;
  static constexpr auto LOC_ACTOR20 = 1005267;

public:
  PincerManeuver() : Sapphire::ScriptAPI::QuestBattleScript( 52 )
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

EXPOSE_SCRIPT( PincerManeuver );