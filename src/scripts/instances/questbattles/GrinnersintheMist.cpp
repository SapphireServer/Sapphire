#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class GrinnersintheMist : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_01 = 5042744;
  static constexpr auto INIT_POP_1ST_02 = 5045543;
  static constexpr auto INIT_POP_1ST_03 = 5045551;
  static constexpr auto INIT_POP_1ST_04 = 5045556;
  static constexpr auto INIT_POP_1ST_05 = 5045558;
  static constexpr auto INIT_POP_1ST_06 = 5045559;
  static constexpr auto INIT_POP_1ST_07 = 5045561;
  static constexpr auto INIT_POP_1ST_08 = 5045562;
  static constexpr auto INIT_POP_2ST_01 = 5045696;
  static constexpr auto INIT_POP_3ST_01 = 5045697;
  static constexpr auto INIT_POP_3ST_02 = 5045705;
  static constexpr auto INIT_P_POP_1ST_01 = 5042741;
  static constexpr auto INIT_P_POP_1ST_02 = 5042742;
  static constexpr auto INIT_NPC_MOVE_POINT_01 = 5046389;
  static constexpr auto INIT_NPC_MOVE_POINT_02 = 5046388;
  static constexpr auto STATUS_PARM_HIDDEN_FOR_BNPC = 1197;
  static constexpr auto STATUS_PARM_HIDDEN_FOR_PLAYER = 1240;
  static constexpr auto DEF_ACTION_TP_DAMAGE = 3114;
  static constexpr auto LCUT_ACTOR0 = 1010200;
  static constexpr auto LCUT_ACTOR1 = 1010202;
  static constexpr auto LCUT_ACTOR2 = 1010246;
  static constexpr auto LCUT_ACTOR3 = 1010247;
  static constexpr auto LCUT_ACTOR4 = 1010248;
  static constexpr auto LCUT_POS0 = 5110379;
  static constexpr auto LCUT_POS1 = 5110381;
  static constexpr auto LCUT_POS2 = 5110382;
  static constexpr auto LCUT_ACTION0 = 979;
  static constexpr auto LCUT_FACE0 = 617;
  static constexpr auto LCUT_FACE1 = 608;
  static constexpr auto LCUT_BGM1 = 130;

public:
  GrinnersintheMist() : Sapphire::ScriptAPI::QuestBattleScript( 93 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgbg_w_qic_004_01a", 2007457, 6904219, 4, { 5.684449f, 16.347240f, 3.782750f }, 1.000000f, 0.000000f ); 
    // States -> cage01_close_01 (id: 8) cage01_open_01 (id: 10) cage01_open_02 (id: 11) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( GrinnersintheMist );