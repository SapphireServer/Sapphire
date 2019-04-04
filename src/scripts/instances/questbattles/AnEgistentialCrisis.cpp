#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AnEgistentialCrisis : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_YMHITRA = 7585499;
  static constexpr auto P_BNPC_DANCINGWOLF = 7585497;
  static constexpr auto P_BNPC_SMN_A = 7585494;
  static constexpr auto P_BNPC_SMN_B = 7585495;
  static constexpr auto P_BNPC_SMN_C = 7585496;
  static constexpr auto P_BNPC_PRIMIE = 7585500;
  static constexpr auto BNPC_SARI = 7585498;
  static constexpr auto QIB_YELL_01 = 4626;
  static constexpr auto QIB_YELL_02 = 4627;
  static constexpr auto QIB_YELL_03 = 4628;
  static constexpr auto QIB_YELL_04 = 4629;
  static constexpr auto QIB_YELL_05 = 4630;
  static constexpr auto QIB_YELL_06 = 4631;
  static constexpr auto QIB_YELL_07 = 4847;
  static constexpr auto QIB_YELL_08 = 4848;
  static constexpr auto QIB_YELL_09 = 4849;
  static constexpr auto QIB_YELL_10 = 4850;
  static constexpr auto PR_PRIMIE_MOVE_01 = 7585501;
  static constexpr auto PR_PRIMIE_MOVE_02 = 7585510;
  static constexpr auto PR_PRIMIE_MOVE_03 = 7585515;
  static constexpr auto PR_YMHITRA_MOVE_01 = 7585502;
  static constexpr auto PR_YMHITRA_MOVE_02 = 7585509;
  static constexpr auto PR_YMHITRA_MOVE_03 = 7585514;
  static constexpr auto BEHAVIOR_YMHITRA_01 = 30932;
  static constexpr auto BEHAVIOR_YMHITRA_02 = 30933;
  static constexpr auto BNPC_PACK1_01 = 7585503;
  static constexpr auto BNPC_PACK1_02 = 7585504;
  static constexpr auto BNPC_PACK1_03 = 7585505;
  static constexpr auto BNPC_PACK1_04 = 7585506;
  static constexpr auto BNPC_PACK1_05 = 7585507;
  static constexpr auto BNPC_PACK1_06 = 7585508;
  static constexpr auto BNPC_PACK2_01 = 7585511;
  static constexpr auto BNPC_PACK2_02 = 7585512;
  static constexpr auto BNPC_PACK2_03 = 7585513;
  static constexpr auto BNPC_PACK3_01 = 7585516;
  static constexpr auto BNPC_PACK3_02 = 7585517;
  static constexpr auto ER_AROUND_BOSS = 7585518;
  static constexpr auto BNPC_TOUMEI_A = 7585519;
  static constexpr auto BNPC_TOUMEI_B_01 = 7585520;
  static constexpr auto BNPC_TOUMEI_B_02 = 7585521;
  static constexpr auto BNPC_TOUMEI_B_03 = 7585522;
  static constexpr auto BNPC_TOUMEI_B_04 = 7585523;
  static constexpr auto BNPC_DIVE_WYVERN_01 = 7585524;
  static constexpr auto BNPC_DIVE_WYVERN_02 = 7585525;
  static constexpr auto BNPC_DIVE_WYVERN_03 = 7585526;
  static constexpr auto BNPC_DIVE_WYVERN_04 = 7585527;
  static constexpr auto BNPC_DIVE_WYVERN_05 = 7585528;
  static constexpr auto ACTION_MEGA_FLARE = 8564;
  static constexpr auto ACTION_MEGA_FLARE_STRIKE = 8565;
  static constexpr auto ACTION_TRANCE_BAHAMUT = 8566;
  static constexpr auto BGM_BOSSBATTLE = 39;
  static constexpr auto BNPC_BOSS_ADD_WYVERN_01 = 7585529;
  static constexpr auto BNPC_BOSS_ADD_WYVERN_02 = 7585530;
  static constexpr auto BNPC_BOSS_ADD_WYVERN_03 = 7585531;
  static constexpr auto BNPCTYPE_ADD_WYVERN = 7319;
  static constexpr auto BNPC_BOSS_GUARD_01 = 7585532;
  static constexpr auto BNPC_BOSS_GUARD_02 = 7585533;
  static constexpr auto ER_AROUND_SMN_B = 7585557;

public:
  AnEgistentialCrisis() : Sapphire::ScriptAPI::QuestBattleScript( 170 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0286", 2005325, 7585378, 4, { 187.869202f, 8.108603f, 250.084000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgvf_w_lvd_b0286_1", 2005326, 7585380, 4, { 57.053249f, 17.165449f, -249.904694f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgvf_w_lvd_b0286_2", 2005327, 7585382, 4, { -314.464996f, 41.657890f, 126.635803f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "AllagantomelithA1", 2005338, 7585392, 4, { 18.148529f, 18.849100f, 267.572693f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1", 2005502, 7585393, 4, { 18.255230f, 16.804850f, 267.227814f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithA2", 2005339, 7585396, 4, { 8.120948f, 21.013821f, 167.772705f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_1", 2005503, 7585397, 4, { 8.225257f, 19.763350f, 167.312195f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithA3", 2005340, 7585400, 4, { 96.414833f, 34.135899f, 108.177002f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_2", 2005504, 7585401, 4, { 96.322990f, 33.288559f, 107.972397f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithA4", 2005341, 7585404, 4, { 200.335693f, 30.775141f, 68.234734f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_3", 2005505, 7585405, 4, { 200.310593f, 29.688540f, 68.217537f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithB1", 2005342, 7585408, 4, { 157.733093f, 4.437783f, -49.087921f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_4", 2005506, 7585409, 4, { 157.696793f, 2.356474f, -49.159088f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithB2", 2005343, 7585412, 4, { 51.290970f, 32.733749f, -82.673607f }, 0.991760f, 0.000000f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_5", 2005507, 7585413, 4, { 51.310070f, 31.154039f, -82.935127f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithB3", 2005344, 7585416, 4, { 74.829063f, 13.976150f, -16.412930f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_6", 2005508, 7585417, 4, { 74.846779f, 11.294810f, -16.719721f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithB4", 2005345, 7585420, 4, { -47.222630f, 31.708929f, -92.240723f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_7", 2005509, 7585421, 4, { -47.175869f, 29.272760f, -92.573776f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithC2", 2005346, 7585424, 4, { -163.868805f, 46.920021f, 1.751138f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_8", 2005510, 7585425, 4, { -164.055405f, 45.557041f, 1.093665f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithD2", 2005347, 7585428, 4, { -32.930420f, 18.645050f, 19.141041f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_9", 2005511, 7585429, 4, { -32.986580f, 17.328630f, 18.981670f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithD3", 2005348, 7585432, 4, { -62.119572f, 40.360111f, 48.813599f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_10", 2005512, 7585433, 4, { -62.187111f, 38.493420f, 48.440479f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithC4", 2005349, 7585436, 4, { -148.508499f, 43.280338f, 161.458603f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_11", 2005513, 7585437, 4, { -148.519196f, 41.333549f, 161.070908f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithC3", 2005350, 7585440, 4, { -167.072998f, 26.487570f, 71.059898f }, 0.991760f, 0.088708f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_12", 2005514, 7585441, 4, { -167.089294f, 24.449400f, 70.683212f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithC1", 2005351, 7585444, 4, { -120.087196f, 28.019110f, -46.859772f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_13", 2005515, 7585445, 4, { -120.122597f, 27.122120f, -47.061981f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 
    instance.registerEObj( "AllagantomelithD1", 2005352, 7585448, 4, { 15.841110f, 19.797770f, 101.591301f }, 0.991760f, 0.000048f ); 
    // States -> ma_off (id: 4) ma_on (id: 5) ma_off2on (id: 8) ma_on2off (id: 9) ma_on_r (id: 10) ma_off2on_r (id: 11) ma_on_r2 (id: 12) ma_off2on_r2 (id: 13) ma_on2off_r (id: 24) ma_on2off_r2 (id: 30) 
    instance.registerEObj( "sgbg_s2p1_q1_ocup1_14", 2005516, 7585449, 4, { 15.812600f, 18.748220f, 101.435699f }, 1.000000f, 0.000000f ); 
    // States -> cap_ser_off2on (id: 5) cap_ser_on (id: 6) cap_off (id: 7) cap_on2off (id: 8) cap_fla_on (id: 9) cap_fla_off2on (id: 10) cap_sto_on (id: 11) cap_sto_off2on (id: 12) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AnEgistentialCrisis );