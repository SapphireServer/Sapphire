#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SoundingOuttheAmphitheatre : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto LOC_MARKER_0 = 5855126;
  static constexpr auto LOC_ACTOR_0 = 1012442;
  static constexpr auto LOC_ACTOR_1 = 1012443;
  static constexpr auto LOC_ACTOR_2 = 1009991;
  static constexpr auto LOC_ACTOR_3 = 1009991;
  static constexpr auto LOC_ACTOR_4 = 1009991;
  static constexpr auto LOC_ACTOR_5 = 1009991;
  static constexpr auto INIT_POP_COMPANION_BNPC_ALPHINAUD = 5855526;
  static constexpr auto INIT_POP_COMPANION_BNPC_ESTINIEN = 5855527;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_A_ZAKO_KEN = 5855123;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_A_ZAKO_YARI = 5855522;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_B_ZAKO_JU = 5855524;
  static constexpr auto INIT_POP_ENEMY_BNPC_P1_B_ZAKO_GEN = 5855525;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_C_ZAKO_JU = 5855542;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_C_ZAKO_KEN_DRAGON = 5855541;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_D_ZAKO_GEN = 5855544;
  static constexpr auto SECOND_POP_ENEMY_BNPC_P2_D_ZAKO_KEN_DRAGON = 5855543;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_E_ZAKO_KEN_DRAGON = 5855643;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_E_ZAKO_JU = 5855644;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_F_ZAKO_KEN_DRAGON = 5855648;
  static constexpr auto THIRD_POP_ENEMY_BNPC_P3_F_BOSS = 5855647;
  static constexpr auto FOURTH_POP_ENEMY_BNPC_P4_G_ZAKO_KEN_DRAGON = 5855691;
  static constexpr auto FOURTH_POP_ENEMY_BNPC_P4_G_ZAKO_JU = 5855698;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_01 = 5855582;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_02 = 5855591;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_03 = 5855593;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_04 = 5855594;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_05 = 5855595;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_06 = 5855596;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_07 = 5855597;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_08 = 5855598;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_09 = 5855613;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_10 = 5855618;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_11 = 5855626;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_12 = 5855629;
  static constexpr auto INIT_POP_ENEMY_BNPC_GIMMIC_TRANS_BATTALION_NOLOG_NOHIT_13 = 5855630;
  static constexpr auto LOC_MARKER0 = 5855126;
  static constexpr auto LOC_ACTOR0 = 1013665;
  static constexpr auto LOC_ACTOR1 = 1013666;
  static constexpr auto LOC_ACTOR2 = 1013667;
  static constexpr auto LOC_ACTOR3 = 1013668;
  static constexpr auto LOC_ACTOR4 = 1013669;
  static constexpr auto LOC_ACTOR5 = 1013670;
  static constexpr auto ACTION_TRANSFORM_TO_DRAG = 3930;
  static constexpr auto ACTION_TRANSFORM_TO_MSHUFUSHU = 3994;
  static constexpr auto QIB_YELL_01 = 2652;
  static constexpr auto QIB_YELL_02 = 2653;
  static constexpr auto STATUS_PARAM_DAMAGE_UP = 385;
  static constexpr auto LOC_ACTION_HAX = 934;
  static constexpr auto LOC_ACTION_HAX_BASE = 936;
  static constexpr auto PLAY_BGM_LCUT_DRAGON = 314;
  static constexpr auto PLAY_BGM_LCUT_HANYOB = 16;
  static constexpr auto PLAY_BGM_LCUT_DRAGONWAR = 316;

public:
  SoundingOuttheAmphitheatre() : Sapphire::ScriptAPI::QuestBattleScript( 108 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2004238, 4772738, 4, { -1.210436f, 0.000000f, -0.715586f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_r1fc_b0472", 2004239, 4797573, 4, { 1.181316f, -0.000000f, 1.563968f }, 1.000000f, 0.000000f ); 
    // States -> wind_def (id: 2) wind_def_anim (id: 3) wind_pop (id: 4) wind_pop_anim (id: 5) 
    instance.registerEObj( "sgvf_r1fc_b0471", 2004240, 4841629, 4, { 11.000000f, 0.000000f, -11.000000f }, 1.000000f, 0.793709f ); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.registerEObj( "sgvf_r1fc_b0471_1", 2004349, 4841631, 4, { 12.811310f, -0.000000f, 9.376424f }, 1.000000f, 0.000000f ); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.registerEObj( "sgvf_r1fc_b0471_2", 2004350, 4841632, 4, { -8.033875f, 0.000000f, 10.406790f }, 1.000000f, 0.000000f ); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.registerEObj( "sgvf_r1fc_b0471_3", 2004351, 4841633, 4, { -8.319038f, -0.000001f, -10.997720f }, 1.000000f, 0.000000f ); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.registerEObj( "Entrance", 2000182, 4738599, 5, { 9.717670f, 0.000000f, 14.522430f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SoundingOuttheAmphitheatre );