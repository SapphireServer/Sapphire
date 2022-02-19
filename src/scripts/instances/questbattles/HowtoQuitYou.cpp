#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HowtoQuitYou : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_A_01 = 4272556;
  static constexpr auto INIT_POP_1ST_A_02 = 4272557;
  static constexpr auto INIT_POP_1ST_A_03 = 4272558;
  static constexpr auto INIT_POP_1ST_A_04 = 4272559;
  static constexpr auto INIT_POP_1ST_A_05 = 4272560;
  static constexpr auto INIT_P_POP_01 = 4329195;
  static constexpr auto INIT_P_POP_02 = 4272571;
  static constexpr auto INIT_P_POP_03 = 4272573;
  static constexpr auto INIT_POP_2ND_B_01 = 4272579;
  static constexpr auto INIT_POP_2ND_B_02 = 4272580;
  static constexpr auto INIT_POP_2ND_B_03 = 4272581;
  static constexpr auto INIT_POP_2ND_B_04 = 4272582;
  static constexpr auto INIT_POP_2ND_B_05 = 4272583;
  static constexpr auto INIT_POP_BOSS = 4273307;
  static constexpr auto WARP_01 = 4273310;
  static constexpr auto INIT_POP_3RD_C_01 = 4273323;
  static constexpr auto INIT_POP_3RD_C_02 = 4273324;
  static constexpr auto INIT_POP_3RD_C_03 = 4273327;
  static constexpr auto INIT_POP_3RD_C_04 = 4273328;
  static constexpr auto INIT_POP_3RD_C_05 = 4273331;
  static constexpr auto INIT_POP_3RD_C_06 = 4273332;
  static constexpr auto INIT_POP_3RD_C_07 = 4273334;
  static constexpr auto INIT_POP_3RD_C_08 = 4273335;
  static constexpr auto INIT_POP_3RD_C_09 = 4273336;
  static constexpr auto INIT_POP_3RD_C_10 = 4273338;
  static constexpr auto INIT_POP_3RD_C_11 = 4273341;
  static constexpr auto INIT_POP_3RD_C_12 = 4273343;
  static constexpr auto INIT_POP_3RD_C_13 = 4273344;
  static constexpr auto INIT_POP_4TH_D_01 = 4273694;
  static constexpr auto INIT_POP_4TH_D_02 = 4273695;
  static constexpr auto INIT_POP_4TH_D_03 = 4273696;
  static constexpr auto INIT_POP_4TH_D_04 = 4273697;
  static constexpr auto INIT_POP_4TH_D_05 = 4273700;
  static constexpr auto INIT_POP_4TH_D_06 = 4273701;
  static constexpr auto INIT_POP_4TH_D_07 = 4273702;
  static constexpr auto INIT_POP_4TH_D_08 = 4273704;
  static constexpr auto INIT_POP_4TH_D_09 = 4273705;
  static constexpr auto INIT_POP_4TH_D_10 = 4273706;
  static constexpr auto INIT_POP_4TH_D_11 = 4273708;
  static constexpr auto INIT_POP_4TH_C_01 = 4273709;
  static constexpr auto INIT_POP_4TH_C_02 = 4273710;
  static constexpr auto INIT_POP_4TH_C_03 = 4273713;
  static constexpr auto INIT_POP_4TH_C_04 = 4273714;
  static constexpr auto INIT_POP_4TH_C_05 = 4273715;
  static constexpr auto INIT_POP_4TH_C_06 = 4273716;
  static constexpr auto INIT_POP_4TH_C_07 = 4273727;
  static constexpr auto INIT_POP_4TH_C_08 = 4273729;
  static constexpr auto INIT_POP_4TH_C_09 = 4273732;
  static constexpr auto INIT_POP_4TH_C_10 = 4273733;
  static constexpr auto INIT_POP_4TH_C_11 = 4273735;
  static constexpr auto INIT_POP_4TH_C_12 = 4273738;
  static constexpr auto INIT_POP_4TH_C_13 = 4273740;
  static constexpr auto INIT_POP_4TH_C_14 = 4302586;
  static constexpr auto INIT_POP_4TH_C_15 = 4302587;
  static constexpr auto INIT_POP_4TH_C_16 = 4302589;
  static constexpr auto INIT_POP_4TH_C_17 = 4302590;
  static constexpr auto INIT_ENPC_POP_01 = 4274643;
  static constexpr auto INIT_ENPC_POP_02 = 4274644;
  static constexpr auto LOG_EVENT_QIB_WAR500_BTL_01 = 3204;
  static constexpr auto LOG_EVENT_QIB_WAR500_BTL_02 = 3205;
  static constexpr auto BGM_JOB_SHIREN = 91;
  static constexpr auto LOC_ACTOR0 = 1007128;
  static constexpr auto LOC_ACTOR1 = 1007141;
  static constexpr auto LOC_ACTOR2 = 1007142;
  static constexpr auto LOC_ACTOR3 = 1007143;
  static constexpr auto LOC_POS_ACTOR0 = 4312944;
  static constexpr auto CUT_INSART_NCUT = 323;
  static constexpr auto CUT_END_NCUT = 324;
  static constexpr auto INIT_ENPC_POP_03 = 4322368;
  static constexpr auto INIT_ENPC_POP_04 = 4322688;
  static constexpr auto JOB_STORY_MES = 3606;

public:
  HowtoQuitYou() : Sapphire::ScriptAPI::QuestBattleScript( 67 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2001225, 0, 4323569, 4, { 23.333300f, 53.571999f, 106.354698f }, 1.000000f, 0.649343f, 0); 
    instance.addEObj( "unknown_1", 2001225, 0, 4323570, 4, { 21.551701f, 51.794300f, 121.154800f }, 1.000000f, 0.517916f, 0); 
    instance.addEObj( "unknown_2", 2001225, 0, 4323571, 4, { 8.403500f, 49.262901f, 135.839706f }, 1.000000f, -1.043878f, 0); 
    instance.addEObj( "unknown_3", 2001225, 0, 4323572, 4, { 24.120800f, 55.250999f, 94.305801f }, 1.000000f, -1.130911f, 0); 
    instance.addEObj( "unknown_4", 2001225, 0, 4323573, 4, { 13.908300f, 48.692402f, 141.292801f }, 1.000000f, -1.291134f, 0); 
    instance.addEObj( "Pelicanegg", 2001226, 0, 4326233, 4, { 24.856930f, 58.243649f, 514.396912f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Pelicanegg_1", 2001226, 0, 4326236, 4, { 32.791630f, 56.748291f, 497.337189f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Pelicanegg_2", 2001226, 0, 4326238, 4, { 15.762570f, 59.159180f, 529.930420f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Pelicanegg_3", 2001226, 0, 4326242, 4, { 2.120972f, 61.875240f, 569.115601f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Pelicanegg_4", 2001226, 0, 4326243, 4, { -4.409851f, 60.654541f, 570.794189f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Pelicanegg_5", 2001226, 0, 4326245, 4, { -9.842102f, 60.044189f, 575.280273f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Pelicanegg_6", 2001226, 0, 4326246, 4, { -32.591129f, 55.394451f, 579.160217f }, 0.991760f, 0.349066f, 0); 
    instance.addEObj( "Pelicanegg_7", 2001226, 0, 4326247, 4, { -20.072981f, 45.049290f, 486.681396f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Rainbowlipoyster", 2001761, 0, 4178264, 4, { 542.626282f, 9.000001f, 140.538696f }, 1.000000f, 0.766292f, 0); 
    instance.addEObj( "Rainbowlipoyster_1", 2001761, 0, 4178265, 4, { 535.067200f, 9.526894f, 168.054001f }, 1.000000f, 0.954200f, 0); 
    instance.addEObj( "Rainbowlipoyster_2", 2001761, 0, 4178266, 4, { 558.090515f, 9.000001f, 166.795898f }, 1.000000f, -0.459148f, 0); 
    instance.addEObj( "Rainbowlipoyster_3", 2001761, 0, 4178267, 4, { 528.797485f, 9.000001f, 120.626404f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Raincatchernectar", 2001207, 0, 4322373, 4, { -257.718292f, 39.721359f, 285.297607f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Raincatchernectar_1", 2001207, 0, 4322375, 4, { -278.129089f, 46.972820f, 266.881012f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Raincatchernectar_2", 2001207, 0, 4322376, 4, { -286.473602f, 42.541382f, 320.362701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Raincatchernectar_3", 2001207, 0, 4322390, 4, { -240.302597f, 39.150990f, 331.519806f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2004812, 0, 5327263, 4, { -85.610252f, 37.412331f, 481.616302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolencrate", 2002375, 0, 4305018, 4, { 32.230679f, 34.078800f, 225.482193f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolencrate_1", 2002522, 0, 4322850, 4, { 32.316509f, 34.478161f, 225.494904f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2000608, 3640871, 4324111, 4, { -27.662939f, 71.794006f, -27.473471f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2000608, 3640869, 4324113, 4, { -56.442101f, 71.794792f, -27.793831f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2003776, 0, 4629967, 4, { 516.093323f, 8.895996f, 251.327499f }, 2.000000f, 0.346127f, 0); 
    instance.addEObj( "unknown_9", 2003777, 0, 4629968, 4, { 512.718323f, 8.927683f, 280.140289f }, 2.000000f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2003778, 0, 4629969, 4, { 529.576599f, 8.561299f, 265.513702f }, 1.250000f, -0.750309f, 0); 
    instance.addEObj( "unknown_11", 2003820, 0, 4630856, 4, { 529.198120f, 9.201172f, 242.481094f }, 0.991760f, -1.170110f, 0); 
    instance.addEObj( "Foodsupply", 2004317, 0, 4771276, 4, { 515.994873f, 9.407423f, 525.813416f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2004318, 0, 4771277, 4, { 516.158081f, 9.128445f, 526.723083f }, 1.000000f, 0.096815f, 0); 
    instance.addEObj( "unknown_13", 2004319, 0, 4771278, 4, { 516.158081f, 9.128400f, 526.723083f }, 1.000000f, 0.096815f, 0); 
    instance.addEObj( "unknown_14", 2004320, 0, 4771282, 4, { 516.158081f, 9.128400f, 526.723083f }, 1.000000f, 0.096815f, 0); 
    instance.addEObj( "unknown_15", 2004321, 0, 4771283, 4, { 520.051819f, 9.435795f, 516.643616f }, 0.991760f, -0.042620f, 0); 
    instance.addEObj( "unknown_16", 2004371, 0, 4876869, 4, { 580.773621f, 15.531930f, 376.546906f }, 0.991760f, -0.841353f, 0); 
    instance.addEObj( "Destination", 2004328, 0, 4771407, 4, { 523.488281f, 17.865311f, 455.256500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2004330, 0, 4772280, 4, { 379.995209f, 28.915890f, 346.547607f }, 0.991760f, -1.371351f, 0); 
    instance.addEObj( "unknown_18", 2001897, 0, 4265826, 4, { 684.271484f, 9.000001f, 415.753601f }, 1.000000f, -1.562855f, 0); 
    instance.addEObj( "unknown_19", 2002012, 0, 4265904, 4, { 684.290771f, 11.581540f, 411.920593f }, 0.600000f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2002274, 0, 4277237, 4, { 684.271484f, 9.000000f, 415.753601f }, 1.000000f, -1.562855f, 0); 
    instance.addEObj( "unknown_21", 2002274, 0, 4277238, 4, { 689.574280f, 9.000001f, 400.914886f }, 1.000000f, -0.012971f, 0); 
    instance.addEObj( "unknown_22", 2004912, 0, 5110338, 4, { 450.849487f, 16.182400f, 406.701202f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2002702, 0, 4374461, 4, { -338.582886f, 69.044937f, 159.661407f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_1", 2002713, 0, 4374656, 4, { 15.521610f, 65.719597f, 43.040970f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Storehouseexit", 2004966, 0, 5341512, 4, { -16.112141f, -23.285440f, 258.157806f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2002035, 0, 4291559, 4, { 666.710022f, 9.020000f, 509.640015f }, 0.991760f, 1.498000f, 0); 
    instance.addEObj( "unknown_23", 2002638, 0, 4334883, 4, { 666.710022f, 9.020000f, 509.640015f }, 1.000000f, 1.477691f, 0); 
    instance.addEObj( "Destination_2", 2002639, 0, 4334884, 4, { 652.252625f, 12.068800f, 519.859985f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2002036, 0, 4293171, 4, { 425.837097f, 16.485470f, 417.937408f }, 1.000000f, 1.106464f, 0); 
    instance.addEObj( "Destination_3", 2002050, 0, 4293247, 4, { 548.570312f, 14.587070f, 393.890015f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_4", 2002291, 0, 4293248, 4, { 562.894226f, 14.587070f, 393.881805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2002292, 0, 4293249, 4, { 564.620789f, 17.553440f, 406.029602f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2002293, 0, 4293250, 4, { 567.083801f, 17.741619f, 415.529694f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2002294, 0, 4293251, 4, { 577.486511f, 17.732130f, 421.654694f }, 1.000000f, 1.554731f, 0); 
    instance.addEObj( "Destination_8", 2002051, 0, 4293252, 4, { 565.182190f, 18.167570f, 424.421387f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Unsavoryshoreline", 2002052, 0, 4293257, 4, { 472.932098f, 10.008150f, 743.534973f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Brasscontraption", 2002053, 0, 4293259, 4, { 381.607208f, 27.669050f, 375.790588f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Brasscontraption_1", 2002054, 0, 4293260, 4, { 367.043396f, 29.521481f, 352.437592f }, 0.991760f, -0.307062f, 0); 
    instance.addEObj( "Brasscontraption_2", 2002055, 0, 4293261, 4, { 379.476593f, 30.507351f, 314.076385f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Sturdypillar", 2002415, 0, 4307709, 4, { 561.533691f, 8.701095f, 452.273499f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Sturdypillar_1", 2002416, 0, 4307710, 4, { 531.456421f, 8.712640f, 452.870789f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Sturdypillar_2", 2002417, 0, 4307711, 4, { 565.072388f, 8.698009f, 514.778015f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Lionmedal", 2002056, 0, 4293281, 4, { 380.514191f, 40.152382f, 636.972473f }, 0.686646f, 0.000048f, 0); 
    instance.addEObj( "Lionmedal_1", 2002057, 0, 4293282, 4, { 386.617798f, 38.286720f, 608.239929f }, 0.686646f, 0.000048f, 0); 
    instance.addEObj( "Lionmedal_2", 2002058, 0, 4293283, 4, { 365.173615f, 36.082169f, 643.988770f }, 0.686646f, 0.000048f, 0); 
    instance.addEObj( "Destination_9", 2002547, 0, 4325246, 4, { 398.597412f, 79.368210f, 620.597778f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Palmwine", 2002059, 0, 4293291, 4, { -282.886993f, 33.977188f, 308.247406f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Palmwine_1", 2002060, 0, 4293292, 4, { -298.278900f, 33.907021f, 276.548798f }, 1.000000f, 1.146737f, 0); 
    instance.addEObj( "Palmwine_2", 2002061, 0, 4293293, 4, { -248.393402f, 33.989380f, 299.413300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_10", 2002062, 0, 4293296, 4, { -242.633804f, 45.222340f, 495.323090f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_11", 2002063, 0, 4293301, 4, { 558.113770f, 43.793941f, 553.655396f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_12", 2002064, 0, 4293304, 4, { 458.457306f, 12.898400f, 216.845901f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "Destination_13", 2002065, 0, 4293308, 4, { 458.548798f, 12.610610f, 190.478394f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_14", 2002066, 0, 4293310, 4, { 458.182587f, 12.357100f, 163.042603f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_15", 2002677, 0, 4335617, 4, { 446.421295f, 13.901680f, 239.544907f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2002295, 0, 4293331, 4, { 667.000183f, 9.000001f, 492.105011f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Emptyspace", 2002067, 0, 4293427, 4, { 524.835876f, 18.168390f, 457.080902f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Emptyspace_1", 2002068, 0, 4293428, 4, { 524.437317f, 18.229990f, 456.992310f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Emptyspace_2", 2002069, 0, 4293429, 4, { 524.623779f, 18.168390f, 457.447296f }, 0.991760f, 1.219334f, 0); 
    instance.addEObj( "Feastingtable", 2002070, 0, 4293431, 4, { 524.592773f, 18.168390f, 456.620605f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Feastingtable_1", 2002071, 0, 4293432, 4, { 524.594727f, 18.168390f, 455.171112f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Feastingtable_2", 2002072, 0, 4293433, 4, { 525.162415f, 18.142941f, 457.861908f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Feastingtable_3", 2002073, 0, 4293435, 4, { 524.514526f, 18.168390f, 456.139313f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Feastingtable_4", 2002074, 0, 4293437, 4, { 524.625916f, 18.142941f, 454.532806f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Feastingtable_5", 2002675, 0, 4335453, 4, { 524.398376f, 18.168390f, 455.325714f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Feastingtable_6", 2002676, 0, 4335455, 4, { 524.437317f, 18.142941f, 456.168488f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_26", 2002075, 0, 4293459, 4, { 524.835876f, 18.168400f, 457.080902f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "unknown_27", 2002076, 0, 4293460, 4, { 524.449280f, 18.229990f, 456.994598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2002077, 0, 4293461, 4, { 524.623779f, 18.168400f, 457.447296f }, 0.991800f, 1.219334f, 0); 
    instance.addEObj( "Feastingtable_7", 2002078, 0, 4293462, 4, { 524.592773f, 18.168400f, 456.620605f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "Feastingtable_8", 2002079, 0, 4293463, 4, { 524.594727f, 18.168400f, 455.171112f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "Feastingtable_9", 2002080, 0, 4293464, 4, { 525.162415f, 18.142900f, 457.861908f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "Feastingtable_10", 2002081, 0, 4293466, 4, { 524.514526f, 18.168400f, 456.139313f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "Feastingtable_11", 2002082, 0, 4293467, 4, { 524.668518f, 18.168400f, 454.569794f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "Exoticfeast", 2002598, 0, 4331560, 4, { 524.634827f, 18.168390f, 457.148895f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_29", 2002687, 0, 4373897, 4, { 524.668518f, 18.167810f, 454.569794f }, 0.991800f, -0.047964f, 0); 
    instance.addEObj( "ExploratorySitegate", 2002609, 0, 4332170, 4, { 356.991302f, 77.743134f, -99.819702f }, 1.000000f, -0.785204f, 0); 
    instance.addEObj( "unknown_30", 2002841, 0, 4500970, 4, { 26.993160f, 54.062618f, 486.167603f }, 1.235901f, 0.000048f, 0); 
    instance.addEObj( "Destination_16", 2005064, 0, 5584487, 4, { 603.016602f, 8.987488f, 577.677917f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_17", 2002366, 0, 4305561, 4, { -143.053101f, 68.201988f, 586.154297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Rankbox", 2006265, 0, 5920744, 4, { 425.145386f, 15.332490f, 706.618530f }, 1.000000f, 0.059461f, 0); 
    instance.addEObj( "unknown_31", 2006266, 0, 5920794, 4, { 427.084595f, 15.167400f, 706.736877f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_18", 2002441, 0, 4308152, 4, { 689.530029f, 9.771100f, 483.348206f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer", 2002442, 0, 4308153, 4, { 689.530029f, 9.771100f, 483.348206f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Mokujin", 2004927, 0, 5327246, 4, { -10.579870f, 41.421200f, 267.889496f }, 1.000000f, 1.541772f, 0); 
    instance.addEObj( "unknown_32", 2004937, 0, 5327249, 4, { -4.330000f, 39.530960f, 247.669098f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2005015, 0, 5405101, 4, { -10.990750f, 39.927109f, 267.945007f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Mokujin_1", 2004928, 0, 5327251, 4, { -10.579900f, 41.421200f, 267.889496f }, 1.000000f, 1.541772f, 0); 
    instance.addEObj( "Mokujin_2", 2004929, 0, 5327252, 4, { -10.579900f, 41.421200f, 267.889496f }, 1.000000f, 1.541772f, 0); 
    instance.addEObj( "unknown_34", 2005016, 0, 5405106, 4, { -10.990800f, 39.927101f, 267.945007f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Weatheredcrate", 2005007, 0, 5392163, 4, { 515.565979f, 9.494328f, 349.957886f }, 0.564514f, 0.803235f, 0); 
    instance.addEObj( "unknown_35", 2005011, 0, 5392176, 4, { 515.565979f, 9.646916f, 349.957886f }, 0.991760f, -0.541168f, 0); 
    instance.addEObj( "unknown_36", 2004933, 0, 5327265, 4, { -9.567444f, 40.211140f, 256.946686f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "unknown_37", 2004934, 0, 5327266, 4, { -13.148160f, 41.669079f, 258.948914f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "unknown_38", 2004939, 0, 5327269, 4, { -70.972137f, 36.047710f, 475.535095f }, 1.000000f, 0.810401f, 0); 
    instance.addEObj( "unknown_39", 2004933, 0, 5367659, 4, { -10.897120f, 40.824310f, 259.833893f }, 0.500000f, -0.000000f, 0); 
    instance.addEObj( "unknown_40", 2004934, 0, 5367660, 4, { -14.115410f, 42.042549f, 253.442505f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "unknown_41", 2004933, 0, 5367661, 4, { -15.315400f, 43.625488f, 259.357513f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "unknown_42", 2004934, 0, 5367662, 4, { -12.338870f, 42.020039f, 255.634399f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "Destination_19", 2005932, 0, 5895605, 4, { 483.373108f, 10.909970f, 348.898987f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_20", 2005940, 0, 5895699, 4, { -4.840000f, 39.430000f, 263.799988f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_21", 2005941, 0, 5895700, 4, { -47.099998f, 39.750000f, 255.679993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_43", 2002378, 0, 4305760, 4, { -8.006777f, 40.556461f, 192.751205f }, 0.400000f, 0.000000f, 0); 
    instance.addEObj( "unknown_44", 2002377, 0, 4305767, 4, { 32.203011f, 34.087700f, 225.454102f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_45", 2002300, 0, 4295527, 4, { 494.979401f, 10.213230f, 329.967712f }, 1.400000f, 0.000000f, 0); 
    instance.addEObj( "Destination_22", 2002307, 0, 4295557, 4, { 95.820000f, 74.905693f, -45.730000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldwoodenchest", 2002311, 0, 4295692, 4, { -282.707886f, 33.828941f, 300.993103f }, 0.991760f, -0.768458f, 0); 
    instance.addEObj( "unknown_46", 2002313, 0, 4296271, 4, { 89.844643f, 66.152702f, 18.650360f }, 0.700000f, -0.388439f, 0); 
    instance.addEObj( "unknown_47", 2004693, 0, 5018606, 4, { 408.633698f, 79.069107f, 623.345703f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_48", 2004665, 0, 5018611, 4, { 338.742493f, 37.838001f, 750.804504f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004111, 0, 4722117, 4, { -266.399292f, 35.381519f, 305.709595f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???_1", 2004121, 0, 4722747, 4, { -52.781071f, 34.942009f, 445.304108f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_23", 2004284, 0, 4757306, 4, { 517.332581f, 12.572820f, 78.961166f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_24", 2004858, 0, 5071850, 4, { -252.745895f, 49.679340f, 460.716797f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_49", 2005155, 0, 5650640, 4, { 534.387085f, 44.182201f, 540.224609f }, 0.991760f, -1.545450f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HowtoQuitYou );