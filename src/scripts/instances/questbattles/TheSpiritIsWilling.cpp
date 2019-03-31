#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheSpiritIsWilling : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4081071;
  static constexpr auto INIT_POP_01A_01 = 4081077;
  static constexpr auto INIT_POP_01A_02 = 4081078;
  static constexpr auto INIT_POP_01A_03 = 4081080;
  static constexpr auto INIT_POP_01A_04 = 4081081;
  static constexpr auto INIT_POP_01A_05 = 4081081;
  static constexpr auto INIT_POP_02A_01 = 4081099;
  static constexpr auto INIT_POP_02A_02 = 4081100;
  static constexpr auto INIT_POP_02C_02 = 4081102;
  static constexpr auto INIT_POP_02C_01 = 4081103;
  static constexpr auto INIT_POP_02B_02 = 4081104;
  static constexpr auto INIT_POP_02B_01 = 4081105;
  static constexpr auto INIT_POP_03C_01 = 4081113;
  static constexpr auto INIT_POP_03C_02 = 4081114;
  static constexpr auto INIT_POP_03C_03 = 4081115;
  static constexpr auto INIT_POP_03C_04 = 4081116;
  static constexpr auto INIT_POP_03D_01 = 4081117;
  static constexpr auto BNPC_C_TYPE = 690;
  static constexpr auto LOC_POS_ACTOR1 = 4087447;
  static constexpr auto LOC_POS_ACTOR2 = 4087454;
  static constexpr auto LOC_POS_ACTOR3 = 4087458;
  static constexpr auto LOC_POS_ACTOR4 = 4087478;
  static constexpr auto LOC_ACTOR0 = 1003827;
  static constexpr auto LOC_ACTOR1 = 1003817;
  static constexpr auto LOC_ACTOR2 = 1006011;
  static constexpr auto LOC_BNPC1 = 1005971;
  static constexpr auto LOC_BNPC2 = 1005972;
  static constexpr auto LOC_BNPC3 = 1005973;
  static constexpr auto LOC_BNPC4 = 1002997;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto NCUT_15010 = 164;
  static constexpr auto INIT_ENPC_POP_01 = 4107478;
  static constexpr auto INIT_ENPC_POP_02 = 4107479;

public:
  TheSpiritIsWilling() : Sapphire::ScriptAPI::QuestBattleScript( 30 )
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

EXPOSE_SCRIPT( TheSpiritIsWilling );