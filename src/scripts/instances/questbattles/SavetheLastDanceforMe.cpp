#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SavetheLastDanceforMe : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_AUDIENCE_01 = 8006017;
  static constexpr auto P_BNPC_AUDIENCE_02 = 8010041;
  static constexpr auto P_BNPC_AUDIENCE_03 = 8010042;
  static constexpr auto P_BNPC_AUDIENCE_04 = 8006021;
  static constexpr auto P_BNPC_AUDIENCE_05 = 8005989;
  static constexpr auto P_BNPC_AUDIENCE_06 = 8005995;
  static constexpr auto P_BNPC_AUDIENCE_07 = 8006005;
  static constexpr auto BNPC_DARK_ELEMENTAL_BOSS = 8006135;
  static constexpr auto BNPC_TOUMEI_01 = 8006136;
  static constexpr auto BNPC_TOUMEI_02 = 8006138;
  static constexpr auto BNPC_TOUMEI_03 = 8006139;
  static constexpr auto BNPC_TOUMEI_04 = 8006140;
  static constexpr auto BNPC_TOUMEI_05 = 8006141;
  static constexpr auto BNPC_TOUMEI_06 = 8006142;
  static constexpr auto BNPC_TOUMEI_07 = 8006143;
  static constexpr auto BNPC_TOUMEI_08 = 8006144;
  static constexpr auto BNPC_TOUMEI_09 = 8006145;
  static constexpr auto BNPC_TOUMEI_10 = 8006146;
  static constexpr auto BNPC_ADD_DARKSPRIT_01 = 8006359;
  static constexpr auto BNPC_ADD_DARKSPRIT_02 = 8006361;
  static constexpr auto BNPC_ADD_DARKSPRIT_03 = 8006362;
  static constexpr auto STATUS_INVINCIBLE = 1496;
  static constexpr auto P_BNPC_RANAAMIHGO = 8006990;
  static constexpr auto BNPC_BLACKBALL_01 = 8007108;
  static constexpr auto BNPC_BLACKBALL_02 = 8007109;
  static constexpr auto POP_RANGE_BLACKBALL_ESCAPE_POSITION_01 = 8007118;
  static constexpr auto POP_RANGE_BLACKBALL_ESCAPE_POSITION_02 = 8007125;
  static constexpr auto ACTION_SUMMON_DARKBALL = 17478;
  static constexpr auto ACTION_SHARE_ATTACK_ACTING = 17550;
  static constexpr auto ACTION_TOUMEI_SHARE_ATTACK = 17487;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_01 = 8010064;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_02 = 8010065;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_03 = 8010066;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_04 = 8010067;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_05 = 8010068;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_06 = 8010069;
  static constexpr auto BNPC_ADD_DARKSPRIT_P2_07 = 8010070;
  static constexpr auto P_BNPC_NASHMEIRA = 8010078;
  static constexpr auto POP_RANGE_NPC_NASHMEIRA_MOVE_POSITION_CENTER = 8010079;
  static constexpr auto ACTION_FLAME_DANCE = 17584;
  static constexpr auto P_BNPC_TOUMEI_NASHMEIRA_01 = 8011313;
  static constexpr auto P_BNPC_TOUMEI_NASHMEIRA_02 = 8011314;
  static constexpr auto P_BNPC_TOUMEI_NASHMEIRA_03 = 8011315;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_01 = 8012629;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_02 = 8012630;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_03 = 8012632;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_04 = 8012633;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_05 = 8012634;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_06 = 8012635;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTH_07 = 8012636;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_01 = 8012628;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_02 = 8012640;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_03 = 8012641;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_04 = 8012642;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_05 = 8012643;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_06 = 8012644;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_EAST_07 = 8012645;
  static constexpr auto ACTION_DARK_RUNWAY_ACTING = 16253;
  static constexpr auto BNPC_RAMIA = 8010072;
  static constexpr auto ACTION_DELTA_ATACK_ACTING = 17612;
  static constexpr auto POP_RANGE_DONUT_POSITION = 8013810;
  static constexpr auto POP_RANGE_CROSS_POSITION = 8013811;
  static constexpr auto ACTION_TARGETAE_DONUT = 17607;
  static constexpr auto ACTION_TARGETAE_CROSS = 17608;
  static constexpr auto BNPC_GHOST = 8010074;
  static constexpr auto CHANNELING_DARK = 1;
  static constexpr auto ACTION_ADD_POP_ACTING = 17500;
  static constexpr auto ACTION_BLIND_EFFECT = 17477;
  static constexpr auto ACTION_SHARE_ATTACK = 17487;
  static constexpr auto LOGMESSAGE_ADD_POP = 9510;
  static constexpr auto BNPCNAME_NASHMEIRA = 8488;
  static constexpr auto ACTION_BRIGHTNESS_PILLAR = 17585;
  static constexpr auto ACTION_TARGETAE_GRAVITON = 17609;
  static constexpr auto ACTION_TARGETAE_BIG = 17831;
  static constexpr auto POP_RANGE_AVOID_DARK_RUNWAY = 8025555;
  static constexpr auto POP_RANGE_RANAAMIHGO_NORMAL_POSITION = 8025557;
  static constexpr auto POP_RANGE_NASHMEIRA_NORMAL_POSITION = 8025556;
  static constexpr auto CHANNELING_GENERAL = 12;
  static constexpr auto ACTION_DANCE_FINISH2 = 17837;
  static constexpr auto BGM_SECONDHALF = 165;
  static constexpr auto POP_RANGE_RANAAMIHGO_STANDBY = 8025773;
  static constexpr auto YELL_RANAAMIHGO_NOTICE = 8569;
  static constexpr auto YELL_AUDIENCE_SHOUT_01 = 8570;
  static constexpr auto YELL_AUDIENCE_SHOUT_02 = 8571;
  static constexpr auto BNPCBASE_DARKBALL = 10955;
  static constexpr auto BNPCBASE_DARK_RUNWAY_FIRST = 10959;
  static constexpr auto BNPCBASE_DARK_RUNWAY_NEXT = 10987;
  static constexpr auto POP_RANGE_RANAAMIHGO_PULL_DARK_SPRITE = 8026217;
  static constexpr auto YELL_NASHMEIRA_FLAME_DANCE = 8559;
  static constexpr auto ACTION_TOUMEI_NASHMEIRA_TRIGGER_ACTION = 3269;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_01 = 8034301;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_02 = 8034304;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_03 = 8034305;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_04 = 8034306;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_05 = 8034307;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_06 = 8034308;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_NORTHEAST_07 = 8034309;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_WEST_01 = 8034312;
  static constexpr auto BNPC_TOUMEI_DARK_RUNWAY_WEST_07 = 8034314;
  static constexpr auto POP_RANGE_AVOID_DARK_RUNWAY_02 = 8034324;
  static constexpr auto BNPC_TOUMEI_11 = 8049676;
  static constexpr auto MODELSTATE_WEPON_IDLE = 11;

public:
  SavetheLastDanceforMe() : Sapphire::ScriptAPI::QuestBattleScript( 189 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgpl_evt_300_jobdark03", 2007457, 6941254, 4, { -613.766602f, 59.266399f, -460.085205f }, 1.000000f, 0.294434f); 
    // States -> vfx_on (id: 49) vfx_off (id: 50) 
    instance.registerEObj( "sgvf_g3f2_b2396", 2007457, 8916664, 4, { -130.022202f, 305.422394f, 129.991592f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Griffinfeather", 2008956, 0, 4, { 204.069107f, 314.519989f, 325.907501f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Griffinfeather_1", 2008956, 0, 4, { 205.549194f, 311.420197f, 357.379395f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Griffinfeather_2", 2008956, 0, 4, { 192.556000f, 312.372711f, 341.805786f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Griffinfeather_3", 2008956, 0, 4, { 217.926102f, 316.727295f, 312.017395f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Griffinfeather_4", 2008956, 0, 4, { 174.981400f, 310.754089f, 351.241913f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Griffinfeather_5", 2008956, 0, 4, { 225.482407f, 312.855591f, 356.527008f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Griffinfeather_6", 2008956, 0, 4, { 184.898193f, 315.135803f, 313.752289f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Griffinfeather_7", 2008956, 0, 4, { 232.020996f, 314.792908f, 337.539398f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2010660, 0, 4, { 82.883400f, 118.150497f, -750.531128f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2010660, 0, 4, { 63.358601f, 118.150497f, -750.481506f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aethercurrent", 2007976, 0, 4, { 202.874405f, 133.925293f, -753.118713f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Aethercurrent_1", 2007978, 0, 4, { -271.229187f, 157.942093f, -280.231995f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Aethercurrent_2", 2007984, 0, 4, { 146.627197f, 303.756592f, 460.821106f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Aethercurrent_3", 2007981, 0, 4, { -485.210602f, 304.468597f, 247.414200f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination", 2007936, 0, 4, { -284.920013f, 66.227814f, -679.059998f }, 1.000000f, 0.733038f); 
    instance.registerEObj( "Destination_1", 2008669, 0, 4, { -387.932709f, 51.839161f, -626.343811f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_2", 2008670, 0, 4, { -624.643921f, 58.459080f, -484.287201f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2008949, 0, 4, { -615.763977f, 58.981972f, -467.348114f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Strikingdummy", 2008451, 0, 4, { 46.557110f, 118.023201f, -784.215881f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_4", 2008458, 0, 4, { 46.534809f, 118.580101f, -784.267395f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Strikingdummy_1", 2008494, 0, 4, { 46.557098f, 118.023201f, -784.215881f }, 0.991800f, 0.000047f); 
    instance.registerEObj( "Charredtablet", 2008291, 0, 4, { -299.458405f, 200.719894f, -240.558502f }, 0.991760f, -0.244338f); 
    instance.registerEObj( "Chippedtablet", 2008292, 0, 4, { -262.378906f, 106.639397f, -206.836105f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Crackedtablet", 2008293, 0, 4, { -210.389893f, 109.685997f, -299.782898f }, 0.991760f, 0.837327f); 
    instance.registerEObj( "Destination_2", 2008294, 0, 4, { 782.684082f, 256.924988f, -388.293915f }, 0.991760f, -0.401382f); 
    instance.registerEObj( "unknown_5", 2009770, 0, 4, { 50.501350f, 118.348602f, -760.216003f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2008065, 0, 4, { -281.757904f, 104.478500f, -358.998993f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_7", 2008317, 0, 4, { -281.544312f, 200.701904f, -294.300812f }, 1.500000f, 0.041370f); 
    instance.registerEObj( "Destination_3", 2008681, 0, 4, { -257.690186f, 102.335297f, -381.366913f }, 0.991760f, 0.160255f); 
    instance.registerEObj( "unknown_8", 2008066, 0, 4, { -200.412598f, 95.321991f, -448.229004f }, 0.991760f, 1.381227f); 
    instance.registerEObj( "Soiledsack", 2008067, 0, 4, { -270.307892f, 104.843903f, -357.834808f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Witheredflowers", 2008068, 0, 4, { -214.486694f, 107.270103f, -328.798706f }, 0.991760f, 1.207224f); 
    instance.registerEObj( "Rottingvegetables", 2008069, 0, 4, { -259.239197f, 92.190941f, -440.399994f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Chocobofeather", 2008684, 0, 4, { -200.412598f, 95.291603f, -448.229004f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_9", 2008679, 0, 4, { -763.947388f, 81.266586f, -298.460297f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Unconscionablyheavysacks", 2008680, 0, 4, { -763.969421f, 81.909187f, -298.390015f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_4", 2008202, 0, 4, { -549.736816f, 257.404297f, 557.701782f }, 0.991760f, -1.030419f); 
    instance.registerEObj( "Destination_5", 2008203, 0, 4, { -460.904602f, 295.604401f, 256.019104f }, 0.991760f, 0.467536f); 
    instance.registerEObj( "Cermetbulkhead", 2008449, 0, 4, { -128.986694f, 306.696411f, 188.659103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Cermetbulkhead_1", 2008450, 0, 4, { -126.516296f, 306.529602f, 186.276398f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Cermetbulkhead_2", 2008944, 0, 4, { -128.967102f, 306.500305f, 188.607193f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_6", 2008211, 0, 4, { -75.456177f, 262.421906f, 661.863220f }, 0.991760f, -1.045639f); 
    instance.registerEObj( "Destination_7", 2009007, 0, 4, { -75.240028f, 262.421600f, 661.861389f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2008213, 0, 4, { 150.255493f, 308.735687f, 166.613205f }, 2.487183f, -1.488511f); 
    instance.registerEObj( "Destination_8", 2009008, 0, 4, { -171.195007f, 294.543610f, 302.457703f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_9", 2009009, 0, 4, { -115.400398f, 305.492401f, 161.333496f }, 0.991760f, -0.392465f); 
    instance.registerEObj( "Destination_10", 2009010, 0, 4, { 148.822495f, 308.744385f, 166.592697f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_11", 2008212, 0, 4, { 431.136688f, 335.657593f, 487.187988f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Entrance", 2008215, 0, 4, { 433.402008f, 335.805298f, 498.771515f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_12", 2009011, 0, 4, { 306.386688f, 318.584106f, 432.457092f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_13", 2009012, 0, 4, { 333.371185f, 322.027893f, 439.375305f }, 0.991760f, -0.942502f); 
    instance.registerEObj( "Destination_14", 2009013, 0, 4, { 422.243286f, 335.476501f, 481.767700f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_15", 2011775, 0, 4, { 577.660828f, 221.484604f, -629.297424f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Crumpledletter", 2011776, 0, 4, { 591.607422f, 222.261200f, -630.945312f }, 0.991760f, 0.319322f); 
    instance.registerEObj( "Destination_16", 2011777, 0, 4, { 161.486206f, 118.381500f, -471.702087f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Timewornweddingring", 2011778, 0, 4, { 146.760803f, 118.137398f, -470.879486f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Thavnairianlimestone", 2007957, 0, 4, { 120.683601f, 150.883804f, -843.411926f }, 0.991760f, 0.242133f); 
    instance.registerEObj( "Thavnairianlimestone_1", 2007958, 0, 4, { 124.824699f, 149.442307f, -842.243408f }, 1.000000f, -0.970569f); 
    instance.registerEObj( "Thavnairianlimestone_2", 2007959, 0, 4, { 128.339905f, 149.430893f, -838.616516f }, 1.000000f, 0.612291f); 
    instance.registerEObj( "Thavnairianlimestone_3", 2007960, 0, 4, { 137.189102f, 150.902206f, -836.634094f }, 1.000000f, -0.930734f); 
    instance.registerEObj( "Destination_17", 2007961, 0, 4, { -76.737671f, 104.471901f, -428.427612f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_18", 2007962, 0, 4, { -74.102249f, 104.456299f, -428.419708f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_19", 2007963, 0, 4, { -76.680649f, 104.471199f, -422.990112f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_20", 2007964, 0, 4, { -74.153633f, 104.470200f, -422.970886f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2008182, 0, 4, { -550.531677f, 54.755798f, -520.987610f }, 0.991760f, -1.362819f); 
    instance.registerEObj( "unknown_12", 2008820, 0, 4, { -265.556213f, 116.366096f, -119.001701f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_21", 2008792, 0, 4, { -832.139526f, 82.949623f, -349.477386f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_22", 2008634, 0, 4, { -842.539673f, 83.412987f, -355.296387f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_23", 2008635, 0, 4, { -840.024414f, 83.543091f, -341.847900f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Stolensack", 2008688, 0, 4, { 316.281586f, 199.385193f, 2.453101f }, 0.991760f, -1.238947f); 
    instance.registerEObj( "Destination_24", 2008315, 0, 4, { -535.224426f, 93.399719f, -259.841400f }, 1.000000f, -0.001953f); 
    instance.registerEObj( "Destination_25", 2008614, 0, 4, { -535.224426f, 94.750000f, -259.841400f }, 1.000000f, 0.000047f); 
    instance.registerEObj( "Destination_26", 2008316, 0, 4, { 563.815674f, 227.168701f, -747.293823f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Destination_27", 2008610, 0, 4, { 496.657288f, 224.547897f, -770.094971f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_28", 2008611, 0, 4, { 610.204285f, 222.143799f, -697.169922f }, 0.991760f, -1.502797f); 
    instance.registerEObj( "Splinteredcrate", 2008846, 0, 4, { -242.483093f, 268.606201f, 482.964294f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rottingbarrel", 2008847, 0, 4, { -239.395401f, 269.431488f, 519.585693f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rottingbarrel_1", 2008848, 0, 4, { -287.183685f, 269.634308f, 517.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rottingbarrel_2", 2008849, 0, 4, { -361.228088f, 273.483398f, 491.838013f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Splinteredcrate_1", 2008850, 0, 4, { -337.937897f, 272.596008f, 451.104095f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_29", 2008784, 0, 4, { -397.840393f, 255.616592f, 769.437500f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2008586, 0, 4, { -397.840393f, 255.435303f, 769.437500f }, 1.000000f, -0.826215f); 
    instance.registerEObj( "Destination_30", 2008851, 0, 4, { -587.609680f, 323.823608f, 199.358994f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_14", 2008797, 0, 4, { -503.664795f, 266.274597f, 622.432617f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_15", 2008360, 0, 4, { -394.597198f, 278.821991f, 398.294708f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_16", 2008367, 0, 4, { -393.257507f, 278.628815f, 399.299805f }, 0.800000f, 0.604489f); 
    instance.registerEObj( "Supplycrate", 2008368, 0, 4, { -393.257507f, 279.248688f, 399.299805f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Tarnishedneckpiece", 2008361, 0, 4, { -237.371201f, 260.688995f, 520.385376f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Stolenwares", 2008362, 0, 4, { -177.332993f, 306.396088f, 149.270401f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Stolenwares_1", 2008378, 0, 4, { -174.588898f, 306.357086f, 151.239395f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_17", 2008582, 0, 4, { -176.623199f, 305.851807f, 152.178207f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_18", 2008583, 0, 4, { -177.332993f, 305.731506f, 149.270401f }, 0.800000f, 1.400444f); 
    instance.registerEObj( "unknown_19", 2008584, 0, 4, { -174.588898f, 305.701996f, 151.239395f }, 0.800000f, -0.999056f); 
    instance.registerEObj( "Destination_31", 2008745, 0, 4, { -175.341400f, 262.662811f, 589.471191f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_20", 2008852, 0, 4, { -222.827896f, 262.804901f, 555.549377f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Spinnersweb", 2008804, 0, 4, { -480.552399f, 257.923187f, 659.510071f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_21", 2008805, 0, 4, { -634.024780f, 321.566711f, 175.270493f }, 0.991760f, -1.393788f); 
    instance.registerEObj( "Destination_32", 2008853, 0, 4, { 254.901993f, 324.063293f, 113.328697f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Unheavypackage", 2008855, 0, 4, { 63.248539f, 306.714600f, 238.269501f }, 0.991760f, -0.851708f); 
    instance.registerEObj( "Destination_33", 2008856, 0, 4, { 125.841103f, 296.092987f, 436.087494f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_34", 2008857, 0, 4, { 133.639008f, 296.221191f, 421.703705f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_22", 2008858, 0, 4, { 125.862198f, 295.870087f, 436.106415f }, 1.000000f, 0.978428f); 
    instance.registerEObj( "Weatheredcrate", 2008695, 0, 4, { 113.856697f, 306.972412f, 204.382004f }, 0.991760f, 0.411633f); 
    instance.registerEObj( "Weatheredcrate_1", 2008696, 0, 4, { 115.861702f, 306.950714f, 204.119904f }, 0.991760f, -0.480287f); 
    instance.registerEObj( "Weatheredcrate_2", 2008697, 0, 4, { 113.847504f, 306.928192f, 202.014206f }, 0.991760f, 0.210111f); 
    instance.registerEObj( "Weatheredcrate_3", 2008698, 0, 4, { 111.319702f, 306.985901f, 204.058701f }, 0.991760f, -0.346926f); 
    instance.registerEObj( "Weatheredcrate_4", 2008699, 0, 4, { 110.093803f, 307.032593f, 206.195099f }, 0.991760f, -0.102059f); 
    instance.registerEObj( "Weatheredcrate_5", 2008700, 0, 4, { 112.809898f, 307.036713f, 207.354904f }, 0.991760f, 0.264280f); 
    instance.registerEObj( "Rottedroot", 2008370, 0, 4, { 151.628906f, 302.988190f, 611.535828f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_35", 2008369, 0, 4, { 139.425995f, 299.264008f, 535.835815f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Rottedroot_1", 2008371, 0, 4, { 182.671799f, 307.129211f, 594.190796f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_36", 2008585, 0, 4, { 123.375801f, 298.251709f, 604.762024f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_37", 2008363, 0, 4, { 151.994995f, 300.068604f, 558.861572f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Thickbramble", 2008364, 0, 4, { 328.420013f, 323.375000f, 778.410095f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Thickbramble_1", 2008365, 0, 4, { 328.263885f, 322.836212f, 728.507385f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Thickbramble_2", 2008366, 0, 4, { 266.711914f, 322.836212f, 717.794128f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Earthenwarevase", 2008750, 0, 4, { 279.466400f, 323.717804f, 708.832825f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_23", 2008632, 0, 4, { 279.466400f, 322.836212f, 708.832703f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_38", 2008806, 0, 4, { 161.604202f, 310.930389f, 208.540100f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_39", 2008807, 0, 4, { 35.587620f, 305.564514f, 209.485107f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_40", 2008808, 0, 4, { 86.961182f, 305.439789f, 85.313232f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_24", 2008905, 0, 4, { 228.997894f, 310.990509f, 446.519897f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Rhalgrsgold", 2008859, 0, 4, { 366.018097f, 163.470093f, -449.851288f }, 0.991760f, -1.254288f); 
    instance.registerEObj( "Rhalgrsgold_1", 2008902, 0, 4, { 422.062805f, 172.389999f, -440.470703f }, 1.000000f, -1.515447f); 
    instance.registerEObj( "Rhalgrsgold_2", 2008903, 0, 4, { 381.083191f, 185.581497f, -505.131195f }, 1.000000f, -0.741153f); 
    instance.registerEObj( "Stonemasonshammer", 2008777, 0, 4, { 137.865204f, 115.688301f, -648.950928f }, 0.991760f, 0.644809f); 
    instance.registerEObj( "Destination_41", 2008861, 0, 4, { -866.514099f, 283.549713f, 729.610107f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_42", 2008862, 0, 4, { 524.406677f, 258.313690f, -225.696304f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Heavydoor", 2008877, 0, 4, { -32.382401f, 193.001205f, -86.722763f }, 1.000000f, 0.126536f); 
    instance.registerEObj( "Destination_43", 2008878, 0, 4, { -60.555550f, 146.425705f, -171.940506f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_44", 2008879, 0, 4, { 102.830597f, 201.321594f, -53.482910f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Gardenridge", 2008701, 0, 4, { -57.023010f, 104.430298f, -438.773193f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Gardenridge_1", 2008702, 0, 4, { -57.023010f, 104.437500f, -441.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Gardenridge_2", 2008703, 0, 4, { -54.000000f, 104.439400f, -438.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Gardenridge_3", 2008704, 0, 4, { -54.000000f, 104.451302f, -441.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Gardenridge_4", 2008705, 0, 4, { -58.956211f, 104.434502f, -425.742188f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Gardenridge_5", 2008706, 0, 4, { -59.006649f, 104.464302f, -427.695190f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Gardenridge_6", 2008707, 0, 4, { -56.419731f, 104.431801f, -425.742188f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Gardenridge_7", 2008708, 0, 4, { -56.419731f, 104.435303f, -427.680603f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SavetheLastDanceforMe );