#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheTimebetweentheSeconds : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_YUGIRI = 6797684;
  static constexpr auto BNPC_ENEMY_ZENOS = 6797683;
  static constexpr auto BNPC_ENEMY_ZENOS_02 = 6958602;
  static constexpr auto BNPC_ENEMY_EMPIRE_SWORD_01 = 6815860;
  static constexpr auto BNPC_ENEMY_EMPIRE_SWORD_02 = 6815865;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_03 = 6815862;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_01 = 6815863;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_02 = 6815861;
  static constexpr auto ENPC_ENEMY_YOTSUYU = 6816541;
  static constexpr auto CUT_SCENE_N_StmAct03230 = 1431;
  static constexpr auto BNPC_TOUMEI_ACTION_01 = 6904473;
  static constexpr auto BNPC_TOUMEI_ACTION_02 = 6904474;
  static constexpr auto BNPC_TOUMEI_ACTION_03 = 6904475;
  static constexpr auto BNPC_TOUMEI_ACTION_04 = 6904476;
  static constexpr auto BNPC_TOUMEI_ACTION_05 = 6904477;
  static constexpr auto BNPC_TOUMEI_ACTION_06 = 6904478;
  static constexpr auto BNPC_TOUMEI_ACTION_07 = 6904480;
  static constexpr auto BNPC_TOUMEI_ACTION_08 = 6904481;
  static constexpr auto BNPC_TOUMEI_TRANCEFORM = 6906735;
  static constexpr auto BNPC_BLACKFIRE_01 = 6904405;
  static constexpr auto BNPC_BLACKFIRE_02 = 6904410;
  static constexpr auto BNPC_BLACKFIRE_03 = 6904412;
  static constexpr auto BNPC_BLACKFIRE_04 = 6951085;
  static constexpr auto BNPC_BLACKFIRE_05 = 6951091;
  static constexpr auto BNPC_BLACKFIRE_06 = 6951094;
  static constexpr auto BNPC_BLACKFIRE_07 = 6951103;
  static constexpr auto BNPC_ENEMY_ZENOS_BUNSHIN_01 = 6903720;
  static constexpr auto BNPC_ENEMY_ZENOS_BUNSHIN_02 = 6905018;
  static constexpr auto ACTION_SYUKUCHI_CAST = 8999;
  static constexpr auto ACTION_IDLE_TRRIGER = 3269;
  static constexpr auto ACTION_IDLE_TRRIGER_B = 4777;
  static constexpr auto ACTION_EXECUTION = 8994;
  static constexpr auto ACTION_FULLPOWER_DAMEGE = 9016;
  static constexpr auto ACTION_FULLPOWER = 8997;
  static constexpr auto ACTION_KURONOTACHI = 8992;
  static constexpr auto ACTION_SYUKUCHI = 8690;
  static constexpr auto LINEVOICE_ZENOS_001 = 8201342;
  static constexpr auto LINEVOICE_ZENOS_003 = 8201343;
  static constexpr auto LINEVOICE_ZENOS_004 = 8201344;
  static constexpr auto LINEVOICE_ZENOS_006 = 8201346;
  static constexpr auto LINEVOICE_ZENOS_008 = 8201348;
  static constexpr auto LINEVOICE_YUGIRI_004 = 8201144;
  static constexpr auto LINEVOICE_YUGIRI_009 = 8201338;
  static constexpr auto LINEVOICE_YUGIRI_010 = 8201339;
  static constexpr auto YELL_ZENOS_001 = 4838;
  static constexpr auto YELL_ZENOS_003 = 4946;
  static constexpr auto YELL_ZENOS_004 = 4944;
  static constexpr auto YELL_ZENOS_006 = 4837;
  static constexpr auto YELL_ZENOS_008 = 4945;
  static constexpr auto YELL_YUGIRI_008 = 4946;
  static constexpr auto YELL_YUGIRI_010 = 4948;
  static constexpr auto YELL_YUGIRI_004 = 4949;
  static constexpr auto YELL_EMPIRE_DEAD_01 = 4938;
  static constexpr auto YELL_EMPIRE_DEAD_02 = 4939;
  static constexpr auto YELL_EMPIRE_DEAD_03 = 4940;
  static constexpr auto YELL_ZENOS_REACTION_TO_YUGIRI = 4596;
  static constexpr auto YELL_ZENOS_REACTION_TO_YUGIRI_02 = 6320;
  static constexpr auto STATUS_KNOCKDOWN_ETERNAL = 3000;
  static constexpr auto STATUS_STUN = 2991;
  static constexpr auto STATUS_KNOCKDOWN = 3122;
  static constexpr auto STATUS_YOUTOUKAIHOU = 3119;
  static constexpr auto BGM_NO_MUSIC = 1;
  static constexpr auto BGM_ZENOS_BATTLE = 152;
  static constexpr auto WEATHER_SQUL = 8;
  static constexpr auto POPRANGE_YUGIRI_MOVE = 6797686;
  static constexpr auto POPRANGE_ROOM_CENTER = 6903399;
  static constexpr auto BNPC_STATE_ATTRIBUTE_CHANGE_A1_B1_C0_KEEP = 139;
  static constexpr auto BNPC_STATE_OVER_RAY_CHANGE1_SLOT1 = 117;
  static constexpr auto BEHAVIOR_SCARED = 30865;

public:
  TheTimebetweentheSeconds() : Sapphire::ScriptAPI::QuestBattleScript( 163 )
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

EXPOSE_SCRIPT( TheTimebetweentheSeconds );