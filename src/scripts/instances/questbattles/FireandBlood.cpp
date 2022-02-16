#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FireandBlood : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto CUT_SCENE_N_01 = 854;
  static constexpr auto CUT_SCENE_N_02 = 855;
  static constexpr auto INIT_POP_BNPC_COMPANION_ALPHINAUD = 5866564;
  static constexpr auto INIT_POP_BNPC_COMPANION_HILDA = 5866565;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_CHARIBERT = 5866560;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_ZAKO_GEN = 5866561;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_ZAKO_JU1 = 5866562;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_ZAKO_JU2 = 5877278;
  static constexpr auto INIT_POP_BNPC_ENEMY_GIMMIC_VFX_FIREBALL = 5866580;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_A_ZAKO_JU = 5875773;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_B_ZAKO_YARI = 5866571;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_B_ZAKO_KEN = 5866572;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_C_ZAKO_YARI = 5866568;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_C_ZAKO_KEN = 5866569;
  static constexpr auto THIRD_POP_BNPC_COMPANION_HAURCHEFANT = 5866579;
  static constexpr auto THIRD_POP_BNPC_ENEMY_P3_D_ZAKO_JU = 5866577;
  static constexpr auto THIRD_POP_BNPC_ENEMY_P3_D_ZAKO_GEN = 5866578;
  static constexpr auto EOBJ_DAMAGE_AREA = 5898500;
  static constexpr auto STATUS_PARAM_FIRE_DAMAGE = 1700;
  static constexpr auto ACTION_DARK_FIREGA = 3791;
  static constexpr auto ACTION_FIRERA = 2175;
  static constexpr auto STATUS_FIRE_DOT = 267;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 4785;
  static constexpr auto BNPC_COMPANION_PET_CARBUNCLE_RED = 5898576;
  static constexpr auto LOCKON_FIRE = 25;
  static constexpr auto QIB_YELL_01 = 2659;
  static constexpr auto QIB_YELL_02 = 2660;
  static constexpr auto QIB_YELL_03 = 2661;
  static constexpr auto QIB_YELL_04 = 2662;

public:
  FireandBlood() : Sapphire::ScriptAPI::QuestBattleScript( 109 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Thalsscepter", 2003646, 0, 4620915, 4, { -270.088409f, 17.593571f, 31.956100f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_0", 2003695, 4617495, 4622404, 4, { -280.035614f, 17.622829f, 22.302071f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2003696, 4563389, 4622405, 4, { -286.231689f, 17.622749f, 20.657721f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thalsscepter_1", 2003674, 0, 4675588, 4, { -271.908386f, 17.593571f, 6.173567f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Thalsscepter_2", 2003675, 0, 4675589, 4, { -244.251801f, 17.593571f, 30.251480f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Thalsscepter_3", 2003676, 0, 4675590, 4, { -246.038696f, 17.593571f, 4.371015f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Mammetactivator", 2003641, 4616318, 4620909, 4, { -84.695412f, -10.178000f, -91.555862f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Shadowyorb", 2003642, 0, 4620910, 4, { 163.469803f, 6.240906f, 219.745102f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Shadowyorb_1", 2003643, 0, 4620912, 4, { 154.314301f, 6.558592f, 239.521896f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Shadowyorb_2", 2003644, 0, 4620913, 4, { 143.742905f, 6.263255f, 210.525208f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Shadowyorb_3", 2003645, 0, 4620914, 4, { 134.607193f, 6.243061f, 230.328094f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2003569, 4603298, 4634958, 4, { 148.951706f, 4.509544f, 224.628006f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2001610, 4569374, 4569375, 4, { -278.262390f, 17.622650f, 19.181259f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_htras1_on (id: 2) vf_htras1_of (id: 3) 
    instance.addEObj( "Shortcut", 2000700, 0, 4569432, 4, { 139.879395f, -0.228372f, -31.551029f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2000182, 4569369, 4569372, 5, { 149.187393f, -0.228943f, -35.111019f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_3", 2002575, 0, 4569370, 4, { 160.775299f, -1.641945f, -10.606120f }, 0.991760f, -1.265160f, 0); 
    instance.addEObj( "unknown_4", 2002735, 0, 4569382, 4, { -50.385818f, -10.178000f, -114.820198f }, 0.991760f, -1.005012f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4569384, 4569383, 4, { -48.920971f, -10.792460f, -116.285103f }, 0.991760f, -1.062825f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_5", 2002735, 0, 4569376, 4, { 129.072403f, 4.509535f, 216.306305f }, 1.000000f, 1.129171f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4569379, 4569378, 4, { 130.018494f, 4.509536f, 217.130295f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_6", 2002735, 0, 4569387, 4, { -233.786301f, 17.622999f, 16.764700f }, 1.000000f, -1.486617f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 4569389, 4569388, 4, { -233.389206f, 17.622990f, 16.739140f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_7", 2003506, 4594991, 4600248, 4, { 101.606300f, -4.171019f, -69.914146f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2003507, 4598981, 4600250, 4, { -41.245178f, -10.879700f, -121.934898f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_9", 2003508, 4603945, 4600252, 4, { -52.140079f, -10.696590f, -91.691528f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2003509, 4564172, 4600290, 4, { 130.022095f, -0.534058f, 5.172791f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2003510, 4594992, 4600292, 4, { 123.552200f, -2.731445f, 25.131590f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2003511, 4598084, 4600294, 4, { 89.130997f, -3.711910f, 78.724213f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2003512, 4599477, 4600296, 4, { 73.157578f, -3.335556f, 178.491302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2003513, 4594999, 4600298, 4, { 100.220802f, 0.477127f, 203.242798f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2003514, 4616527, 4600302, 4, { 167.865707f, 4.509536f, 233.584396f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_16", 2003515, 4567234, 4600354, 4, { -191.532196f, 4.456180f, 94.520203f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2003516, 4567237, 4600377, 4, { -128.869400f, 12.073380f, 96.752960f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2003517, 4567232, 4600396, 4, { -66.065460f, 14.565810f, 26.350080f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2003518, 4567230, 4600397, 4, { -171.754501f, 12.467810f, 12.301850f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2003519, 4596306, 4600399, 4, { -198.995102f, 11.315890f, 13.488570f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2003520, 4565306, 4600401, 4, { 96.452271f, -3.738525f, 39.688599f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_22", 2003521, 4565309, 4600403, 4, { 127.885902f, -3.738525f, 60.807129f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_23", 2003522, 4565307, 4600404, 4, { 82.383423f, -3.646973f, 59.189701f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_24", 2003523, 4565308, 4600406, 4, { 108.323700f, -3.738525f, 80.552368f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_25", 2003524, 4565302, 4600409, 4, { -2.324507f, 0.927634f, 144.329300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2003525, 4565303, 4600410, 4, { 27.311819f, 0.927548f, 166.238098f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2003526, 4565305, 4600411, 4, { 68.331223f, 0.927661f, 136.889404f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2003527, 4595900, 4600413, 4, { 77.372299f, -10.608900f, -91.074203f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_29", 2003528, 4595901, 4600425, 4, { 36.027271f, -9.635880f, -104.808601f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2003529, 4595903, 4600427, 4, { 2.165477f, -11.282240f, -188.867599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_31", 2003530, 4618276, 4600429, 4, { -10.216280f, -11.049250f, -152.788300f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_32", 2003531, 4595904, 4620920, 4, { -21.241859f, -11.023320f, -136.299393f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_1", 2000182, 4970117, 4970166, 5, { -243.015701f, 19.074579f, 10.923530f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit_1", 2000139, 0, 4970167, 4, { -272.688904f, 19.074579f, 18.222231f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5936468, 5936469, 4, { -50.078831f, -10.236320f, -115.087196f }, 0.991760f, -1.062825f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_33", 2005288, 0, 5870807, 4, { -44.235958f, -10.940800f, -120.225899f }, 0.991760f, 0.975291f, 0); 
    instance.addEObj( "unknown_34", 2005289, 5860310, 5872211, 4, { -46.616329f, -10.910280f, -120.836197f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_35", 2005291, 0, 5875680, 4, { -83.935143f, -10.178000f, -94.487663f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2005292, 5860309, 5888360, 4, { 158.985992f, 6.278425f, -67.290947f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_37", 2003506, 4594991, 5927467, 4, { 100.414703f, -4.114531f, -67.633453f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_38", 2003509, 4564172, 5927468, 4, { 131.425903f, -0.656189f, 4.898132f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_39", 2003510, 4594992, 5927469, 4, { 124.834000f, -2.761902f, 25.253660f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Magitekdevice", 2006332, 0, 5927557, 4, { -85.679443f, -9.720032f, -93.644653f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_40", 2005290, 0, 5935143, 4, { -85.771057f, -10.208310f, -92.973328f }, 0.991760f, -1.007025f, 0); 
    instance.addEObj( "Identificationkey", 2005546, 0, 5863326, 4, { 109.912697f, -3.372315f, 57.178600f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( FireandBlood );