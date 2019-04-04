#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HistoryRepeating : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_LNC_01 = 4294343;
  static constexpr auto INIT_POP_1_LNC_02 = 4294344;
  static constexpr auto INIT_POP_1_THM_01 = 4294345;
  static constexpr auto INIT_POP_1_EXC_01 = 4294347;
  static constexpr auto INIT_POP_1_EXC_02 = 4294348;
  static constexpr auto INIT_POP_1_SEI_01 = 4294351;
  static constexpr auto INIT_POP_2_LNC_01 = 4294439;
  static constexpr auto INIT_POP_2_THM_01 = 4294440;
  static constexpr auto INIT_POP_2_EXC_01 = 4294441;
  static constexpr auto INIT_POP_3_SKE_01 = 4294750;
  static constexpr auto INIT_POP_3_SKE_02 = 4294751;
  static constexpr auto INIT_POP_3_LNC_01 = 4294752;
  static constexpr auto INIT_POP_3_EXC_01 = 4294754;
  static constexpr auto INIT_POP_4_LNC_01 = 4294755;
  static constexpr auto INIT_POP_4_THM_01 = 4294756;
  static constexpr auto INIT_POP_4_EXC_01 = 4294758;
  static constexpr auto INIT_POP_5_THM_01 = 4294763;
  static constexpr auto INIT_POP_5_LNC_02 = 4294764;
  static constexpr auto INIT_POP_5_SKE_01 = 4294766;
  static constexpr auto DEF_ACTION_CHARM_SONG = 1329;
  static constexpr auto QIB_YELL_01 = 1321;
  static constexpr auto QIB_YELL_02 = 1342;
  static constexpr auto QIB_YELL_03 = 1343;
  static constexpr auto QIB_YELL_04 = 1344;
  static constexpr auto INIT_POP_SONG_BALL_A = 4317589;
  static constexpr auto INIT_POP_SONG_BALL_A_2 = 4317648;
  static constexpr auto INIT_POP_SONG_BALL_B = 4317650;
  static constexpr auto BNPC_TYPE_SONG_BALL_A = 1633;
  static constexpr auto BNPC_TYPE_SONG_BALL_B = 1634;
  static constexpr auto INIT_P_POP_KEEP_TARGETING = 4317701;
  static constexpr auto LOC_ACTOR0 = 1007700;
  static constexpr auto LOC_ACTOR1 = 1002236;
  static constexpr auto LOC_POS_ACTOR0 = 4334457;
  static constexpr auto LOC_POS_ACTOR1 = 4334458;
  static constexpr auto LOC_POS_ACTOR2 = 4334459;
  static constexpr auto LOC_POS_CAM1 = 4334460;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 619;
  static constexpr auto LOC_BGM1 = 112;

public:
  HistoryRepeating() : Sapphire::ScriptAPI::QuestBattleScript( 86 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6228959, 5, { 457.583801f, 5.680784f, 280.512787f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2000608, 2807920, 4, { -95.322441f, -25.054260f, 61.518002f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HistoryRepeating );