#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class StarcrossedRivals : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4082301;
  static constexpr auto INIT_POP_BOSS = 4082299;
  static constexpr auto INIT_POP_01A_01 = 4082315;
  static constexpr auto INIT_POP_01A_02 = 4082316;
  static constexpr auto INIT_POP_01A_03 = 4082317;
  static constexpr auto INIT_POP_02A_01 = 4082311;
  static constexpr auto INIT_POP_02A_02 = 4082312;
  static constexpr auto INIT_POP_02B_01 = 4082314;
  static constexpr auto INIT_POP_03C_01 = 4082323;
  static constexpr auto BNPC_01_A_TYPE = 700;
  static constexpr auto LOC_POS_ACTOR0 = 4083826;
  static constexpr auto LOC_POS_ACTOR1 = 4083827;
  static constexpr auto LOC_ACTOR0 = 1003827;
  static constexpr auto LOC_ACTOR1 = 1006011;
  static constexpr auto LOC_BNPC0 = 1004482;
  static constexpr auto LOC_ACTION1 = 934;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto DEF_ACTION_MONSTER_WHISTLE = 983;

public:
  StarcrossedRivals() : Sapphire::ScriptAPI::QuestBattleScript( 32 )
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

EXPOSE_SCRIPT( StarcrossedRivals );