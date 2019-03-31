#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class VictoryinPeril : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_01 = 3970651;
  static constexpr auto INIT_POP_1ST_02 = 3970655;
  static constexpr auto INIT_POP_1ST_03 = 3970671;
  static constexpr auto INIT_POP_1ST_04 = 3970673;
  static constexpr auto INIT_POP_2ST_01 = 3970684;
  static constexpr auto INIT_POP_2ST_02 = 3970685;
  static constexpr auto INIT_POP_2ST_03 = 3970686;
  static constexpr auto INIT_POP_2ST_04 = 3970675;
  static constexpr auto INIT_POP_2ST_05 = 4103658;
  static constexpr auto INIT_P_POP_1ST_01 = 3970427;
  static constexpr auto INIT_P_POP_1ST_02 = 3970428;
  static constexpr auto ER_RECT_01 = 4103659;
  static constexpr auto INIT_ENPC_POP_01 = 4103652;
  static constexpr auto ACTION_ATTACK_UP = 963;
  static constexpr auto BGM_BATTLE = 33;
  static constexpr auto LOC_ACTOR0 = 1002237;
  static constexpr auto LOC_ACTOR1 = 1002672;
  static constexpr auto LOC_ACTOR2 = 1002671;
  static constexpr auto LOC_ACTOR3 = 1002238;
  static constexpr auto LOC_ACTOR4 = 1002240;
  static constexpr auto LOC_ACTOR5 = 1002702;
  static constexpr auto LOC_POS_ACTOR0 = 4144321;
  static constexpr auto LOC_POS_ACTOR1 = 4144324;
  static constexpr auto LOC_POS_ACTOR2 = 4144325;
  static constexpr auto LOC_POS_CAM1 = 4144326;
  static constexpr auto LOC_POS_CAM2 = 3985691;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto LOC_ACTION2 = 979;
  static constexpr auto LOC_ACTION3 = 981;
  static constexpr auto INIT_POP_LOOKOUT_01 = 4167378;
  static constexpr auto INIT_POP_LOOKOUT_02 = 4167379;
  static constexpr auto INIT_POP_LOOKOUT_03 = 4167390;
  static constexpr auto INIT_POP_LOOKOUT_04 = 4167391;
  static constexpr auto ER_RECT_02 = 4167388;
  static constexpr auto ER_RECT_03 = 4167389;
  static constexpr auto BGM_MASKED_BATTLE = 37;

public:
  VictoryinPeril() : Sapphire::ScriptAPI::QuestBattleScript( 24 )
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

EXPOSE_SCRIPT( VictoryinPeril );