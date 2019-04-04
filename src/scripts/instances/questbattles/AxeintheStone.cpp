#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AxeintheStone : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_01 = 4107368;
  static constexpr auto INIT_P_POP_2ST_01 = 4107369;
  static constexpr auto INIT_POP_1ST_01 = 4107370;
  static constexpr auto INIT_POP_1ST_02 = 4107372;
  static constexpr auto INIT_POP_1ST_03 = 4107432;
  static constexpr auto INIT_POP_2ST_01 = 4107418;
  static constexpr auto INIT_POP_2ST_02 = 4107419;
  static constexpr auto INIT_POP_2ST_03 = 4107420;
  static constexpr auto INIT_POP_2ST_04 = 4107433;
  static constexpr auto INIT_POP_3ST_01 = 4107421;
  static constexpr auto INIT_POP_3ST_02 = 4107422;
  static constexpr auto INIT_POP_3ST_03 = 4107423;
  static constexpr auto INIT_POP_3ST_04 = 4107434;
  static constexpr auto INIT_POP_3ST_05 = 4107435;
  static constexpr auto INIT_POP_4ST_01 = 4107424;
  static constexpr auto INIT_POP_4ST_02 = 4107425;
  static constexpr auto INIT_POP_4ST_03 = 4107426;
  static constexpr auto INIT_POP_4ST_04 = 4107427;
  static constexpr auto INIT_POP_4ST_05 = 4107428;
  static constexpr auto INIT_POP_4ST_06 = 4107436;
  static constexpr auto INIT_POP_4ST_07 = 4107437;
  static constexpr auto CUT_SCENE_01 = 37;
  static constexpr auto LOC_ACTOR0 = 1002674;
  static constexpr auto LOC_ACTOR1 = 1002696;
  static constexpr auto LOC_ACTOR2 = 1002112;
  static constexpr auto LOC_ACTOR3 = 1002680;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto LOC_POS_ACTOR0 = 4244349;

public:
  AxeintheStone() : Sapphire::ScriptAPI::QuestBattleScript( 25 )
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

EXPOSE_SCRIPT( AxeintheStone );