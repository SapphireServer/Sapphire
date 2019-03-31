#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class LordoftheInferno : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 4098741;
  static constexpr auto INIT_P_POP_A = 4098743;
  static constexpr auto INIT_P_POP_B = 4098744;
  static constexpr auto INIT_P_POP_C = 4098745;
  static constexpr auto INIT_P_POP_SER = 4098749;
  static constexpr auto INIT_POP_1ST_01 = 4098775;
  static constexpr auto INIT_POP_1ST_02 = 4098776;
  static constexpr auto INIT_POP_1ST_03 = 4098777;
  static constexpr auto INIT_POP_1ST_04 = 4098783;
  static constexpr auto INIT_POP_1ST_05 = 4098784;
  static constexpr auto INIT_POP_1ST_06 = 4098791;
  static constexpr auto INIT_POP_1ST_07 = 4098792;
  static constexpr auto INIT_POP_2ND_01 = 4098806;
  static constexpr auto INIT_POP_2ND_02 = 4098810;
  static constexpr auto INIT_POP_2ND_03 = 4098819;
  static constexpr auto INIT_POP_2ND_04 = 4098821;
  static constexpr auto INIT_POP_2ND_05 = 4098823;
  static constexpr auto INIT_POP_3RD_01 = 4098839;
  static constexpr auto INIT_POP_3RD_02 = 4098840;
  static constexpr auto INIT_POP_3RD_03 = 4098842;
  static constexpr auto INIT_POP_1ST_08 = 4098866;
  static constexpr auto INIT_POP_1ST_09 = 4098871;
  static constexpr auto INIT_POP_3RD_04 = 4098886;
  static constexpr auto INIT_POP_3RD_05 = 4098887;
  static constexpr auto INIT_POP_3RD_06 = 4098888;
  static constexpr auto INIT_POP_3RD_07 = 4098889;
  static constexpr auto INIT_ENPC_POP_01 = 4100860;
  static constexpr auto CUT_SCENE_01 = 84;
  static constexpr auto CUT_SCENE_02 = 85;
  static constexpr auto UNLOCK_IMAGE_DUNGEON = 77;

public:
  LordoftheInferno() : Sapphire::ScriptAPI::QuestBattleScript( 45 )
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

EXPOSE_SCRIPT( LordoftheInferno );