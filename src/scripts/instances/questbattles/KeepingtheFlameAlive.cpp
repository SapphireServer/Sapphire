#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class KeepingtheFlameAlive : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_ALPHINAUD = 5855176;
  static constexpr auto BNPC_COMPANION_YUGIRI = 5855177;
  static constexpr auto BNPC_COMPANION_RAUBAHN = 5855194;
  static constexpr auto BNPC_ENEMY_ILBERD = 5856053;
  static constexpr auto BNPC_ENEMY_YUYUHASE = 5856054;
  static constexpr auto BNPC_ENEMY_LAURENTIUS = 5856055;
  static constexpr auto BNPC_ENEMY_01_03 = 5855179;
  static constexpr auto BNPC_ENEMY_01_04 = 5855184;
  static constexpr auto BNPC_ENEMY_01_05 = 5855190;
  static constexpr auto BNPC_ENEMY_01_06 = 5855192;
  static constexpr auto BNPC_ENEMY_FANCE_01_08 = 5855628;
  static constexpr auto BNPC_ENEMY_POISON_015_01 = 5855616;
  static constexpr auto BNPC_ENEMY_015_02 = 5855710;
  static constexpr auto BNPC_ENEMY_015_03 = 5855713;
  static constexpr auto BNPC_ENEMY_015_04 = 5855716;
  static constexpr auto BNPC_ENEMY_015_05 = 5855717;
  static constexpr auto BNPC_ENEMY_015_06 = 5855719;
  static constexpr auto BNPC_ENEMY_02_01 = 5855722;
  static constexpr auto BNPC_ENEMY_02_02 = 5855723;
  static constexpr auto BNPC_ENEMY_04_01 = 5856047;
  static constexpr auto BNPC_ENEMY_04_02 = 5856048;
  static constexpr auto BNPC_ENEMY_04_03 = 5856050;
  static constexpr auto BNPC_ENEMY_05_01 = 5856051;
  static constexpr auto BNPC_ENEMY_05_02 = 5856052;
  static constexpr auto BNPC_ENEMY_YUYUHASE_ENSHUTSU = 5872397;
  static constexpr auto CUT_SCENE_N_heavna20310 = 800;
  static constexpr auto CUT_SCENE_N_heavna20320 = 801;
  static constexpr auto CUT_SCENE_N_heavna20330 = 802;
  static constexpr auto INIT_WARP_POINT_001 = 5856633;
  static constexpr auto POP_RANGE_YUGIRI_MOVE_1 = 5868421;
  static constexpr auto POP_RANGE_ALPHINAUD_MOVE_1 = 5868423;
  static constexpr auto POP_RANGE_YUYUHASE_MOVE_1 = 5872399;
  static constexpr auto RECT_RAUBAHN_FLOOR_OKU = 5856639;
  static constexpr auto RECT_RAUBAHN_FLOOR_TEMAE = 5868403;
  static constexpr auto EOBJ_KEY = 5863326;
  static constexpr auto EOBJ_POISON_GAS = 5870807;
  static constexpr auto YELL_QIB_ZAKO_01 = 2620;
  static constexpr auto YELL_QIB_ZAKO_02 = 2621;
  static constexpr auto YELL_QIB_ALPHINAUD_01 = 3059;
  static constexpr auto YELL_QIB_YUGIRI_01 = 3060;
  static constexpr auto STATUS_PARAM_POISON_GAS = 1413;
  static constexpr auto STATUS_PARAM_POISON_GAS_RAUBAHN = 1401;
  static constexpr auto WEATHER_POISON_GAS = 52;
  static constexpr auto EOBJ_DOOR_A = 5927467;
  static constexpr auto EOBJ_DOOR_B = 5872211;
  static constexpr auto EOBJ_DOOR_C = 5927468;
  static constexpr auto EOBJ_DOOR_D = 5927469;
  static constexpr auto LOC_ACTOR_YU = 1011896;
  static constexpr auto LOC_ACTOR_RA = 1012451;
  static constexpr auto LOC_ACTOR_AL = 1008181;
  static constexpr auto LOC_MARKER_PC = 5877895;
  static constexpr auto LOC_MARKER_YU = 5878129;
  static constexpr auto LOC_MARKER_AL = 5878132;
  static constexpr auto LOC_MARKER_RA = 5878330;
  static constexpr auto LOC_ACTOR_ZI = 1012452;
  static constexpr auto EOBJ_KOUSOKU_BARRIER = 5875680;
  static constexpr auto LOC_EOBJ_KOSOKU = 2005907;
  static constexpr auto LOC_MARKER_YUYU = 5892038;
  static constexpr auto LOC_MARKER_ILU = 5892039;
  static constexpr auto LOC_ACTOR_YUYU = 1012447;
  static constexpr auto LOC_ACTOR_ROR = 1012454;
  static constexpr auto LOC_ACTOR_ILU = 1008191;
  static constexpr auto LOC_MARKER_KAGI = 5900433;
  static constexpr auto LOC_MARKER_YUYU_2 = 5905985;
  static constexpr auto LOC_MARKER_ROL_2 = 5905987;
  static constexpr auto SE_HIRAKU = 95;
  static constexpr auto SE_TOZIRU = 96;
  static constexpr auto SE_AKERU = 63;
  static constexpr auto ACTION_TOHO_SUIYAKU = 3202;
  static constexpr auto RECT_PHASE4_PACK_E = 5927556;
  static constexpr auto EVENT_ACTION_01 = 21;
  static constexpr auto LOG_MESSAGE_01 = 3292;
  static constexpr auto EOBJ_RAUBAHN_RELEASED = 5927557;
  static constexpr auto EVENT_ACTION_02 = 46;
  static constexpr auto EOBJ_POISON_GAS_DEVICE = 5888360;
  static constexpr auto BGM_LATE_BATTLE = 107;
  static constexpr auto LOC_MARKER_KUSARI_RAU = 5935156;
  static constexpr auto LOC_EOBJ_KASE = 2006368;
  static constexpr auto LOC_MARKER_AL_2 = 5936095;
  static constexpr auto LOC_MARKER_YUGI_2 = 5936096;
  static constexpr auto EOBJ_BOSS_COVERED = 5936469;
  static constexpr auto LOC_MARKER_SHIELD = 5941245;
  static constexpr auto EOBJ_CHAIN = 5935143;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_01 = 5961632;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_02 = 5961633;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_03 = 5961634;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_04 = 5961635;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_05 = 5961636;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_06 = 5961637;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_07 = 5961638;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_08 = 5961639;
  static constexpr auto BNPC_FOR_JUMP_01 = 5961655;
  static constexpr auto BNPC_FOR_JUMP_02 = 5961656;
  static constexpr auto BNPC_FOR_JUMP_03 = 5961657;
  static constexpr auto BNPC_FOR_JUMP_04 = 5961658;

public:
  KeepingtheFlameAlive() : Sapphire::ScriptAPI::QuestBattleScript( 106 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2004238, 4772738, 4738623, 4, { -1.210436f, 0.000000f, -0.715586f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_r1fc_b0472", 2004239, 4797573, 4738624, 4, { 1.181316f, -0.000000f, 1.563968f }, 1.000000f, 0.000000f, 0); 
    // States -> wind_def (id: 2) wind_def_anim (id: 3) wind_pop (id: 4) wind_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471", 2004240, 4841629, 4841628, 4, { 11.000000f, 0.000000f, -11.000000f }, 1.000000f, 0.793709f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471_1", 2004349, 4841631, 4841634, 4, { 12.811310f, -0.000000f, 9.376424f }, 1.000000f, 0.000000f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471_2", 2004350, 4841632, 4841635, 4, { -8.033875f, 0.000000f, 10.406790f }, 1.000000f, 0.000000f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471_3", 2004351, 4841633, 4841636, 4, { -8.319038f, -0.000001f, -10.997720f }, 1.000000f, 0.000000f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "Entrance", 2000182, 4738599, 4738602, 5, { 9.717670f, 0.000000f, 14.522430f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 4738604, 4, { 0.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( KeepingtheFlameAlive );