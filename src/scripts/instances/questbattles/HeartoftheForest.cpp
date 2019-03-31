#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HeartoftheForest : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_ATOWA_01 = 4290072;
  static constexpr auto INIT_P_POP_RAYAO_01 = 4290082;
  static constexpr auto INIT_P_POP_ARUN_01 = 4290083;
  static constexpr auto INIT_P_POP_MOTHER_TREE_01 = 4290091;
  static constexpr auto INIT_POP_1_TRENT_01 = 4290093;
  static constexpr auto INIT_POP_1_TRENT_02 = 4290094;
  static constexpr auto INIT_POP_1_TRENT_03 = 4290095;
  static constexpr auto INIT_POP_1_CRAB_02 = 4290106;
  static constexpr auto INIT_POP_1_CRAB_01 = 4290109;
  static constexpr auto INIT_POP_1_CRAB_03 = 4290111;
  static constexpr auto INIT_POP_2_TRENT_01 = 4292762;
  static constexpr auto INIT_POP_2_TRENT_02 = 4292763;
  static constexpr auto INIT_POP_2_TRENT_03 = 4292764;
  static constexpr auto INIT_POP_2_OTYU_02 = 4292765;
  static constexpr auto INIT_POP_2_OTYU_01 = 4292766;
  static constexpr auto INIT_POP_2_OTYU_03 = 4292767;
  static constexpr auto INIT_POP_3_TREE_ANGER_01 = 4290117;
  static constexpr auto INIT_POP_3_TREE_ANGER_02 = 4290118;
  static constexpr auto INIT_POP_3_TREE_ANGER_03 = 4290120;
  static constexpr auto INIT_POP_3_TREE_ANGER_04 = 4290121;
  static constexpr auto INIT_POP_3_TREE_ANGER_05 = 4290122;
  static constexpr auto INIT_POP_3_TREE_ANGER_06 = 4290123;
  static constexpr auto INIT_POP_3_TREE_ANGER_07 = 4290124;
  static constexpr auto INIT_POP_3_TREE_ANGER_08 = 4290126;
  static constexpr auto INIT_POP_3_TREE_ANGER_09 = 4290127;
  static constexpr auto INIT_POP_3_TREE_ANGER_10 = 4290128;
  static constexpr auto INIT_POP_3_TREE_ANGER_11 = 4290129;
  static constexpr auto INIT_POP_3_TREE_ANGER_12 = 4290130;
  static constexpr auto INIT_POP_3_TREE_ANGER_13 = 4290132;
  static constexpr auto INIT_POP_3_TREE_ANGER_14 = 4290133;
  static constexpr auto INIT_POP_3_TREE_ANGER_15 = 4290134;
  static constexpr auto INIT_POP_3_TREE_ANGER_16 = 4290136;
  static constexpr auto INIT_POP_3_TREE_ANGER_17 = 4290137;
  static constexpr auto INIT_POP_3_TRENT_01 = 4292906;
  static constexpr auto INIT_POP_3_TRENT_02 = 4292907;
  static constexpr auto INIT_POP_3_TRENT_03 = 4292908;
  static constexpr auto BNPC_BASE_TYPE_TRENT = 1701;
  static constexpr auto BNPC_BASE_TYPE_OTYU = 1703;
  static constexpr auto BNPC_BASE_TYPE_CRAB = 1705;
  static constexpr auto BNPC_BASE_TYPE_ANGER = 1704;
  static constexpr auto STATUS_CUSTOM_TREE_DOT1 = 689;
  static constexpr auto STATUS_CUSTOM_TREE_DOT2 = 690;
  static constexpr auto QIB_YELL_01 = 1173;
  static constexpr auto INIT_POP_KEEP_TARGETING = 4306921;
  static constexpr auto QIB_LOGMESSAGE_01 = 3210;
  static constexpr auto QIB_LOGMESSAGE_02 = 3211;
  static constexpr auto CUT_START_NCUT = 348;
  static constexpr auto CUT_END_NCUT = 349;
  static constexpr auto JOB_STORY_MES = 3656;

public:
  HeartoftheForest() : Sapphire::ScriptAPI::QuestBattleScript( 76 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HeartoftheForest );