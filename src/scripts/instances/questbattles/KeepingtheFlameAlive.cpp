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
    instance.registerEObj( "Thalsscepter", 2003646, 0, 4, { -270.088409f, 17.593571f, 31.956100f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_0", 2003695, 4617495, 4, { -280.035614f, 17.622829f, 22.302071f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2003696, 4563389, 4, { -286.231689f, 17.622749f, 20.657721f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Thalsscepter_1", 2003674, 0, 4, { -271.908386f, 17.593571f, 6.173567f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Thalsscepter_2", 2003675, 0, 4, { -244.251801f, 17.593571f, 30.251480f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Thalsscepter_3", 2003676, 0, 4, { -246.038696f, 17.593571f, 4.371015f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Mammetactivator", 2003641, 4616318, 4, { -84.695412f, -10.178000f, -91.555862f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shadowyorb", 2003642, 0, 4, { 163.469803f, 6.240906f, 219.745102f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shadowyorb_1", 2003643, 0, 4, { 154.283905f, 6.240900f, 239.520905f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shadowyorb_2", 2003644, 0, 4, { 143.742905f, 6.240900f, 210.525208f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shadowyorb_3", 2003645, 0, 4, { 134.607193f, 6.240900f, 230.328094f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2003569, 4603298, 4, { 148.951706f, 4.509544f, 224.628006f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2001610, 4569374, 4, { -278.262390f, 17.622650f, 19.181259f }, 0.991760f, 0.000048f ); 
    // States -> vf_htras1_on (id: 2) vf_htras1_of (id: 3) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 139.879395f, -0.228372f, -31.551029f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 4569369, 5, { 149.187393f, -0.228943f, -35.111019f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_3", 2002575, 0, 4, { 160.775299f, -1.641945f, -10.606120f }, 0.991760f, -1.265160f ); 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { -50.385818f, -10.178000f, -114.820198f }, 0.991760f, -1.005012f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 4569384, 4, { -48.920971f, -10.792460f, -116.285103f }, 0.991760f, -1.062825f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { 129.072403f, 4.509535f, 216.306305f }, 1.000000f, 1.129171f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 4569379, 4, { 130.018494f, 4.509536f, 217.130295f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { -233.786301f, 17.622999f, 16.764700f }, 1.000000f, -1.486617f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 4569389, 4, { -233.389206f, 17.622990f, 16.739140f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2003506, 4594991, 4, { 101.606300f, -4.171019f, -69.914146f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2003507, 4598981, 4, { -41.245178f, -10.879700f, -121.934898f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_9", 2003508, 4603945, 4, { -52.140079f, -10.696590f, -91.691528f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2003509, 4564172, 4, { 130.022095f, -0.534058f, 5.172791f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_11", 2003510, 4594992, 4, { 123.552200f, -2.731445f, 25.131590f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2003511, 4598084, 4, { 89.130997f, -3.711910f, 78.724213f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2003512, 4599477, 4, { 73.157578f, -3.335556f, 178.491302f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2003513, 4594999, 4, { 100.220802f, 0.477127f, 203.242798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2003514, 4616527, 4, { 167.865707f, 4.509536f, 233.584396f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2003515, 4567234, 4, { -191.532196f, 4.456180f, 94.520203f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2003516, 4567237, 4, { -128.869400f, 12.073380f, 96.752960f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2003517, 4567232, 4, { -66.065460f, 14.565810f, 26.350080f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2003518, 4567230, 4, { -171.754501f, 12.467810f, 12.301850f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2003519, 4596306, 4, { -198.995102f, 11.315890f, 13.488570f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2003520, 4565306, 4, { 96.452271f, -3.738525f, 39.688599f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2003521, 4565309, 4, { 127.885902f, -3.738525f, 60.807129f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2003522, 4565307, 4, { 82.383423f, -3.646973f, 59.189701f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_24", 2003523, 4565308, 4, { 108.323700f, -3.738525f, 80.552368f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_25", 2003524, 4565302, 4, { -2.324507f, 0.927634f, 144.329300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2003525, 4565303, 4, { 27.311819f, 0.927548f, 166.238098f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2003526, 4565305, 4, { 68.331223f, 0.927661f, 136.889404f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2003527, 4595900, 4, { 77.372299f, -10.608900f, -91.074203f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2003528, 4595901, 4, { 36.027271f, -9.635880f, -104.808601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2003529, 4595903, 4, { 2.165477f, -11.282240f, -188.867599f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2003530, 4618276, 4, { -10.216280f, -11.049250f, -152.788300f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_32", 2003531, 4595904, 4, { -21.241859f, -11.023320f, -136.299393f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2000182, 4970117, 5, { -243.015701f, 19.074579f, 10.923530f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit_1", 2000139, 0, 4, { -272.688904f, 19.074579f, 18.222231f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( KeepingtheFlameAlive );