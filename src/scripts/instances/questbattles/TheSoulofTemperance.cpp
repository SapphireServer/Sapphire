#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheSoulofTemperance : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_GIOTT = 7978408;
  static constexpr auto BNPC_SOPHROSYNE = 7978410;
  static constexpr auto BNPC_INV_ACTION_01 = 7978411;
  static constexpr auto POP_RANGE_CENTER = 7978529;
  static constexpr auto BNPC_GARGOYLE_01 = 8006319;
  static constexpr auto BNPC_GARGOYLE_02 = 8006358;
  static constexpr auto BNPC_GARGOYLE_03 = 8007294;
  static constexpr auto BNPC_GARGOYLE_04 = 8006373;
  static constexpr auto BNPC_GARGOYLE_05 = 8007301;
  static constexpr auto ACTION_SOPHROSYNE_REVIVE = 16865;
  static constexpr auto ACTION_DUMMY_SEQUENCE_PROGRESS_01 = 3269;
  static constexpr auto BNPC_DUMMY_BOSS_TARGET = 8006875;
  static constexpr auto ACTION_COVER_MET = 17549;
  static constexpr auto ACTION_TRIGGER_A = 3269;
  static constexpr auto ACTION_TRIGGER_B = 4777;
  static constexpr auto ACTION_TRIGGER_C = 17293;
  static constexpr auto ACTION_TRIGGER_D = 17294;
  static constexpr auto ACTION_SOPHROSYNE_ANCIENT_AERO = 16910;
  static constexpr auto ACTION_TOUMEI_ANCIENT_AERO = 16911;
  static constexpr auto ACTION_SOPHROSYNE_ANCIENT_STONE = 17322;
  static constexpr auto ACTION_TOUMEI_ANCIENT_STONE = 17329;
  static constexpr auto ACTION_SOPHROSYNE_HOLY = 16909;
  static constexpr auto ACTION_TOUMEI_HOLY = 17604;
  static constexpr auto ACTION_SOPHROSYNE_SUMMON_ROD = 15928;
  static constexpr auto ACTION_ROD_RAZER = 15603;
  static constexpr auto ACTION_ROD_DONUTS = 15604;
  static constexpr auto ACTION_GARGOYLE_DISPEL_STATUS = 17581;
  static constexpr auto ACTION_SOPHROSYNE_REVIVE_02 = 17910;
  static constexpr auto ACTION_SOPHROSYNE_REVIVE_03 = 17911;
  static constexpr auto ACTION_SOPHROSYNE_REVIVE_04 = 17912;
  static constexpr auto P_BNPC_GIOTT_NOMET = 8034362;
  static constexpr auto BNPC_SOPHROSYNE_MET = 8034361;
  static constexpr auto BNPC_INV_ACTION_02 = 8034363;
  static constexpr auto BNPC_INV_ACTION_03 = 8034364;
  static constexpr auto BNPC_INV_ACTION_04 = 8034365;
  static constexpr auto BNPC_INV_ACTION_05 = 8034366;
  static constexpr auto BNPC_INV_ACTION_06 = 8034367;
  static constexpr auto BNPC_INV_ACTION_07 = 8034368;
  static constexpr auto BNPC_INV_ACTION_08 = 8034369;
  static constexpr auto BNPC_INV_ACTION_09 = 8034370;
  static constexpr auto BNPC_INV_ACTION_10 = 8034371;
  static constexpr auto BNPC_INV_ACTION_11 = 8034372;
  static constexpr auto BNPC_INV_ACTION_12 = 8034373;
  static constexpr auto BNPC_INV_ACTION_13 = 8034374;
  static constexpr auto BNPC_INV_ACTION_14 = 8034375;
  static constexpr auto BNPC_INV_ACTION_15 = 8034376;
  static constexpr auto BNPC_INV_ACTION_16 = 8034377;
  static constexpr auto BNPC_INV_ACTION_17 = 8034378;
  static constexpr auto BNPC_INV_ACTION_18 = 8034379;
  static constexpr auto PR_HOLY_02_01 = 8034419;
  static constexpr auto PR_HOLY_02_02 = 8034420;
  static constexpr auto PR_HOLY_02_03 = 8034421;
  static constexpr auto PR_HOLY_02_04 = 8034422;
  static constexpr auto PR_HOLY_02_05 = 8034423;
  static constexpr auto PR_HOLY_02_06 = 8034424;
  static constexpr auto PR_HOLY_03_01 = 8034425;
  static constexpr auto PR_HOLY_03_02 = 8034426;
  static constexpr auto PR_HOLY_03_03 = 8034427;
  static constexpr auto PR_HOLY_03_04 = 8034428;
  static constexpr auto PR_HOLY_03_05 = 8034429;
  static constexpr auto PR_HOLY_03_06 = 8034430;
  static constexpr auto PR_HOLY_04_01 = 8034431;
  static constexpr auto PR_HOLY_04_02 = 8034432;
  static constexpr auto PR_HOLY_04_03 = 8034433;
  static constexpr auto PR_HOLY_04_04 = 8034434;
  static constexpr auto PR_HOLY_04_05 = 8034435;
  static constexpr auto PR_HOLY_04_06 = 8034436;
  static constexpr auto BNPC_ROD_01 = 8034503;
  static constexpr auto BNPC_ROD_02 = 8034504;
  static constexpr auto BNPC_ROD_03 = 8034505;
  static constexpr auto BNPC_ROD_04 = 8034506;
  static constexpr auto BNPC_ROD_05 = 8034507;
  static constexpr auto BNPC_ROD_06 = 8034508;
  static constexpr auto BNPC_ROD_07 = 8034509;
  static constexpr auto BNPC_ROD_08 = 8034510;
  static constexpr auto P_BNPC_INV_ACTION_01 = 8034610;
  static constexpr auto P_BNPC_INV_ACTION_02 = 8034611;
  static constexpr auto P_BNPC_INV_ACTION_03 = 8034618;
  static constexpr auto P_BNPC_INV_ACTION_04 = 8034656;
  static constexpr auto P_BNPC_INV_ACTION_05 = 8034684;
  static constexpr auto PR_START_POSITION = 8048892;
  static constexpr auto YELL_GIOTT_01 = 8211;
  static constexpr auto ACTION_GIOTT_EXECUTION = 17484;
  static constexpr auto CUT_SCENE_00 = 2100;
  static constexpr auto BGM_LATTER_HALF = 91;

public:
  TheSoulofTemperance() : Sapphire::ScriptAPI::QuestBattleScript( 195 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2010604, 0, 4, { 594.488403f, 289.169312f, -95.759979f }, 0.991760f, -1.151507f); 
    instance.registerEObj( "unknown_1", 2010605, 0, 4, { 602.973877f, 290.023102f, -109.050797f }, 0.991760f, -0.523599f); 
    instance.registerEObj( "unknown_2", 2010606, 0, 4, { 599.294495f, 289.245209f, -100.949402f }, 0.991760f, -1.087761f); 
    instance.registerEObj( "unknown_3", 2010607, 0, 4, { 593.374084f, 290.320587f, -109.374702f }, 0.991760f, -1.542803f); 
    instance.registerEObj( "Prismaticore", 2010631, 0, 4, { 213.222794f, 312.007507f, -237.315506f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_1", 2010631, 0, 4, { 204.182602f, 314.888885f, -219.862503f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_2", 2010631, 0, 4, { 220.116699f, 310.749298f, -223.786606f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_3", 2010631, 0, 4, { 230.419601f, 307.344696f, -240.141006f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_4", 2010631, 0, 4, { 235.801300f, 306.510010f, -227.390793f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_5", 2010631, 0, 4, { 229.174301f, 309.219910f, -208.412903f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_6", 2010631, 0, 4, { 204.353897f, 315.377197f, -199.237106f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Prismaticore_7", 2010631, 0, 4, { 215.248093f, 312.703186f, -206.427902f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_w_qic_004_04a", 2007457, 7967975, 4, { -281.538788f, 382.771393f, -421.025787f }, 1.000000f, 1.125020f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_1", 2007457, 7970625, 4, { -90.043518f, 363.668213f, -360.738586f }, 0.991760f, -0.800798f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_2", 2007457, 7983702, 4, { -216.479797f, 371.206207f, -360.158813f }, 0.991760f, -1.120830f); 
    instance.registerEObj( "Aethercurrent", 2010034, 0, 4, { 650.568176f, 0.354777f, 556.389587f }, 0.991760f, -1.364832f); 
    instance.registerEObj( "Aethercurrent_1", 2010041, 0, 4, { 623.751526f, 285.942200f, -555.250427f }, 0.991760f, -1.364928f); 
    instance.registerEObj( "Aethercurrent_2", 2010038, 0, 4, { -651.164917f, 0.000015f, 588.411682f }, 0.991760f, -1.364832f); 
    instance.registerEObj( "Aethercurrent_3", 2010042, 0, 4, { -62.897701f, 345.124695f, -16.533300f }, 0.991760f, -1.364832f); 
    instance.registerEObj( "Accesspoint", 2010839, 0, 4, { -137.828506f, 11.952200f, 336.468903f }, 0.991760f, -0.962252f); 
    instance.registerEObj( "unknown_4", 2010792, 0, 4, { -137.736496f, 11.940450f, 336.420197f }, 0.991760f, 1.380586f); 
    instance.registerEObj( "unknown_5", 2009950, 0, 4, { -173.632401f, 15.060610f, 388.510010f }, 0.991760f, 1.332591f); 
    instance.registerEObj( "Destination", 2009999, 0, 4, { 529.396606f, 11.979110f, 370.866486f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_1", 2010000, 0, 4, { 342.500000f, 16.564791f, 454.265106f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_2", 2010006, 0, 4, { -115.294197f, 428.210114f, -621.440918f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_3", 2010007, 0, 4, { 21.210150f, 348.912415f, -251.868500f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2010008, 0, 4, { -650.333374f, 352.448486f, -129.001205f }, 1.000000f, 0.968895f); 
    instance.registerEObj( "Destination_4", 2010402, 0, 4, { -550.750977f, 29.177151f, 363.499786f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_5", 2010403, 0, 4, { -550.977112f, 41.362350f, 252.272598f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_6", 2009806, 0, 4, { 125.616600f, 361.178009f, -471.290710f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_7", 2009956, 0, 4, { 687.952881f, 30.105961f, 279.438385f }, 0.991760f, 0.063584f); 
    instance.registerEObj( "Blightedcrop", 2009957, 0, 4, { 663.172424f, 53.665890f, 60.288330f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Blightedcrop_1", 2009958, 0, 4, { 694.036011f, 53.763100f, 12.937090f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Barreddoor", 2009959, 0, 4, { 703.520020f, 53.783482f, 52.147560f }, 1.000000f, 0.467226f); 
    instance.registerEObj( "unknown_7", 2009960, 0, 4, { 337.788788f, 31.876101f, 203.143295f }, 0.991760f, 1.156495f); 
    instance.registerEObj( "Destination_8", 2009961, 0, 4, { 168.383301f, 40.118992f, 567.223511f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bubblingcookpot", 2009962, 0, 4, { 175.746597f, 50.007648f, 771.493713f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_9", 2009963, 0, 4, { -276.147003f, 17.832960f, 656.985229f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_8", 2010513, 0, 4, { -636.545288f, 0.126414f, 572.912903f }, 0.850000f, 0.000000f); 
    instance.registerEObj( "Destination_10", 2009964, 0, 4, { 168.985397f, 41.007099f, 677.322388f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2010087, 0, 4, { 167.650894f, 40.012562f, 563.195129f }, 0.808655f, 0.000048f); 
    instance.registerEObj( "Lumberstack", 2010088, 0, 4, { -448.178192f, 8.339294f, 546.261780f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Lumberstack_1", 2010089, 0, 4, { -458.228088f, 20.021669f, 481.601196f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_11", 2010124, 0, 4, { -482.061707f, 65.778152f, 93.148453f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_12", 2010090, 0, 4, { -416.259003f, 354.341400f, 22.488600f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Door", 2010091, 0, 4, { -120.050003f, 353.475098f, -206.686295f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "Driedvictuals", 2010092, 0, 4, { -151.397293f, 353.564911f, -188.879196f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Halfemptycup", 2010093, 0, 4, { -132.516602f, 355.258789f, -176.250504f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_13", 2010094, 0, 4, { -279.072296f, 378.683105f, -404.379303f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_14", 2010095, 0, 4, { -168.902100f, 396.810791f, -468.314606f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_10", 2010096, 0, 4, { -467.761993f, 417.197205f, -649.017212f }, 0.595032f, 0.000048f); 
    instance.registerEObj( "unknown_11", 2010100, 0, 4, { 610.911621f, 278.336700f, -514.361328f }, 0.991760f, -0.846107f); 
    instance.registerEObj( "unknown_12", 2010097, 0, 4, { -137.590607f, 352.346100f, -192.492599f }, 0.991760f, -0.014908f); 
    instance.registerEObj( "Familiarheartstone", 2010098, 0, 4, { -137.590607f, 353.543396f, -192.523102f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_13", 2009844, 0, 4, { -141.130707f, 352.358185f, -190.539505f }, 0.991760f, 0.006663f); 
    instance.registerEObj( "Destination_15", 2010714, 0, 4, { -19.051430f, 330.208008f, -46.734348f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Entrance", 2010233, 0, 4, { -169.764694f, 460.827789f, -810.153625f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_14", 2010812, 0, 4, { -422.393494f, 334.052612f, -26.238100f }, 1.000000f, -0.999041f); 
    instance.registerEObj( "Destination_16", 2010813, 0, 4, { -421.683105f, 339.619995f, -161.455704f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Entrance_1", 2010952, 0, 4, { -539.065186f, 63.971809f, 738.860779f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "EntrancetoNoesis", 2010953, 0, 4, { -534.447327f, 64.936798f, 736.965027f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_15", 2011106, 0, 4, { -492.287415f, 0.000000f, 606.572327f }, 1.000000f, -0.328583f); 
    instance.registerEObj( "Entrancetotheexcavationtunnels", 2010832, 0, 4, { 738.336182f, 285.617493f, -82.865646f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance_2", 2011138, 0, 4, { 695.184082f, 295.530212f, -162.019394f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Puppetsentrance", 2011154, 0, 4, { 703.179626f, 295.408813f, -160.198196f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_16", 2010837, 0, 4, { 215.289597f, 315.458313f, -22.686069f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Burnishedbracelet", 2010833, 0, 4, { 545.495300f, 296.140198f, -218.772705f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Metallicglint", 2010844, 0, 4, { 238.205002f, 308.526215f, -120.185699f }, 0.991760f, -0.434075f); 
    instance.registerEObj( "Entrancetotheexcavationtunnels_1", 2010855, 0, 4, { 738.336182f, 285.617493f, -82.865700f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Destination_17", 2011151, 0, 4, { 467.811401f, 311.025604f, -189.079803f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_18", 2011152, 0, 4, { 345.351898f, 320.178589f, -317.577393f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_19", 2011153, 0, 4, { 466.269806f, 298.145996f, -398.794586f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Meadbottle", 2011273, 0, 4, { 574.968872f, 296.728302f, -175.541595f }, 0.991760f, 0.110473f); 
    instance.registerEObj( "Destination_20", 2011447, 0, 4, { 711.628601f, 286.138306f, -121.507401f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Automatoncore", 2010753, 0, 4, { 631.971008f, 325.839203f, -228.665207f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Mininglantern", 2010754, 0, 4, { 542.932678f, 296.207489f, -217.006195f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Cloudednecklace", 2010270, 0, 4, { 781.726685f, -0.252673f, 394.639313f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Snappedfishingrod", 2010271, 0, 4, { 733.341675f, 0.497674f, 459.897095f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Corrodedring", 2010272, 0, 4, { 758.978699f, -0.059695f, 431.614685f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Oversizedtideclam", 2010273, 0, 4, { 783.768005f, 0.007552f, 376.732513f }, 1.000000f, -0.264126f); 
    instance.registerEObj( "Destination_21", 2010248, 0, 4, { 143.279999f, 49.618069f, 773.444275f }, 0.991760f, -1.522739f); 
    instance.registerEObj( "Kholusiansage", 2010246, 0, 4, { -15.515950f, 44.008862f, 729.720581f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Kholusiansage_1", 2010247, 0, 4, { -29.109171f, 44.088612f, 734.717773f }, 0.991760f, 1.351111f); 
    instance.registerEObj( "unknown_17", 2010310, 0, 4, { 143.663696f, 49.295361f, 773.008728f }, 0.991760f, 1.211336f); 
    instance.registerEObj( "Driedbark", 2010267, 0, 4, { 36.782028f, 12.473460f, 400.156586f }, 0.991760f, -1.133198f); 
    instance.registerEObj( "Driedbark_1", 2010268, 0, 4, { 25.514339f, 13.417980f, 413.235291f }, 0.991760f, -0.905206f); 
    instance.registerEObj( "Driedbark_2", 2010269, 0, 4, { 12.787380f, 14.249190f, 419.243286f }, 0.991760f, 0.217110f); 
    instance.registerEObj( "Destination_22", 2010249, 0, 4, { 16.267281f, 47.923592f, 783.791016f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_23", 2010250, 0, 4, { -1.451060f, 45.514931f, 802.256714f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_24", 2010251, 0, 4, { -115.709198f, 11.245850f, 670.252380f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_25", 2010252, 0, 4, { -89.023567f, 41.551960f, 709.063110f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_26", 2010253, 0, 4, { -17.908800f, 42.721359f, 687.422913f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Scatteredgrain", 2010254, 0, 4, { -21.783251f, 5.597071f, 364.595703f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Scatteredgrain_1", 2010255, 0, 4, { 103.524696f, 13.495080f, 365.786407f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_27", 2010256, 0, 4, { 403.585602f, 45.291592f, 51.900360f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Stalkofgoldenbarley", 2010257, 0, 4, { -220.927902f, 18.141600f, 453.727112f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Stalkofgoldenbarley_1", 2010258, 0, 4, { -240.700104f, 18.262369f, 459.230591f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Stalkofgoldenbarley_2", 2010259, 0, 4, { -232.329102f, 18.344419f, 457.068695f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Keeljoint", 2010260, 0, 4, { -444.386993f, 9.002046f, 532.707581f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Keeljoint_1", 2010261, 0, 4, { -444.620697f, 8.827697f, 544.518494f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Keeljoint_2", 2010286, 0, 4, { -443.005188f, 8.802373f, 535.994202f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Keeljoint_3", 2010287, 0, 4, { -442.901794f, 8.898221f, 538.690613f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Keeljoint_4", 2010288, 0, 4, { -441.868713f, 8.613468f, 542.372681f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Keeljoint_5", 2010289, 0, 4, { -443.469299f, 8.511166f, 548.309875f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_18", 2010330, 0, 4, { -226.976898f, 21.278419f, 299.107788f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "DerelictTalos", 2010303, 0, 4, { -481.519104f, 26.112530f, 333.283112f }, 0.991760f, 0.010156f); 
    instance.registerEObj( "Beautifulbloom", 2010304, 0, 4, { -546.677429f, 62.137230f, 681.989685f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Beautifulbloom_1", 2010305, 0, 4, { -532.185303f, 62.803150f, 693.395081f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Beautifulbloom_2", 2010306, 0, 4, { -524.050293f, 61.539749f, 674.464783f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_19", 2010113, 0, 4, { 383.388092f, 4.545356f, 603.281372f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_28", 2010312, 0, 4, { -65.214577f, 345.920105f, -162.695602f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_29", 2010311, 0, 4, { -41.306210f, 343.221100f, -170.702805f }, 0.991760f, -1.398605f); 
    instance.registerEObj( "unknown_20", 2010313, 0, 4, { 394.949188f, 276.264496f, -104.203903f }, 0.991760f, 1.479020f); 
    instance.registerEObj( "unknown_21", 2010314, 0, 4, { 386.312592f, 273.622894f, -75.242310f }, 0.991760f, 0.294097f); 
    instance.registerEObj( "unknown_22", 2010315, 0, 4, { 366.670013f, 279.945190f, -146.561905f }, 0.991760f, 0.669737f); 
    instance.registerEObj( "Soppingsack", 2010316, 0, 4, { 394.945404f, 276.856903f, -104.308899f }, 0.991760f, 1.479020f); 
    instance.registerEObj( "Soppingsack_1", 2010317, 0, 4, { 386.313385f, 274.149109f, -75.257912f }, 0.991760f, 0.294097f); 
    instance.registerEObj( "Soppingsack_2", 2010318, 0, 4, { 366.609894f, 280.533112f, -146.621902f }, 0.991760f, 0.669737f); 
    instance.registerEObj( "Abandonedtimber", 2010319, 0, 4, { -417.727997f, 334.052612f, -24.876699f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Abandonedtimber_1", 2010320, 0, 4, { -416.039307f, 334.052612f, -49.148399f }, 1.000000f, -1.555762f); 
    instance.registerEObj( "Abandonedtimber_2", 2010321, 0, 4, { -433.371490f, 335.255890f, -39.383598f }, 1.000000f, -1.325286f); 
    instance.registerEObj( "Abandonedtimber_3", 2010322, 0, 4, { -448.094391f, 334.052612f, -21.158800f }, 1.000000f, -0.379834f); 
    instance.registerEObj( "unknown_23", 2010329, 0, 4, { -106.910698f, 352.344604f, -190.615097f }, 1.000000f, -0.011689f); 
    instance.registerEObj( "unknown_24", 2010323, 0, 4, { -172.929794f, 328.761993f, -9.720032f }, 0.991760f, 0.000144f); 
    instance.registerEObj( "unknown_25", 2010324, 0, 4, { -178.043701f, 329.514099f, -11.764770f }, 0.991760f, 1.152469f); 
    instance.registerEObj( "unknown_26", 2010325, 0, 4, { -174.456100f, 329.394409f, -12.736500f }, 0.991760f, -1.457928f); 
    instance.registerEObj( "unknown_27", 2010326, 0, 4, { -179.673599f, 329.464813f, -10.680550f }, 0.991760f, -0.701224f); 
    instance.registerEObj( "unknown_28", 2010327, 0, 4, { -174.320007f, 328.604706f, -7.972749f }, 0.991760f, -1.267164f); 
    instance.registerEObj( "Dirtmound", 2010331, 0, 4, { -172.908096f, 329.290009f, -9.691940f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Dirtmound_1", 2010332, 0, 4, { -178.005402f, 330.093109f, -11.736740f }, 0.991760f, 1.152469f); 
    instance.registerEObj( "Dirtmound_2", 2010333, 0, 4, { -174.454193f, 329.917297f, -12.767080f }, 0.991760f, -1.457928f); 
    instance.registerEObj( "Dirtmound_3", 2010334, 0, 4, { -179.722504f, 330.083313f, -10.599580f }, 0.991760f, -0.430911f); 
    instance.registerEObj( "Dirtmound_4", 2010335, 0, 4, { -174.328598f, 329.138885f, -8.018270f }, 0.991760f, 0.558042f); 
    instance.registerEObj( "unknown_29", 2010328, 0, 4, { 85.740356f, 330.159302f, 36.880981f }, 0.991760f, -1.108653f); 
    instance.registerEObj( "Destination_30", 2010342, 0, 4, { 469.270111f, 292.241486f, -144.435501f }, 0.991760f, 1.358408f); 
    instance.registerEObj( "Destination_31", 2010343, 0, 4, { 452.607513f, 291.697296f, -154.897095f }, 0.991760f, 1.358505f); 
    instance.registerEObj( "Temptingbedrock", 2010344, 0, 4, { 104.728500f, 393.298309f, -686.701782f }, 0.991760f, 1.218910f); 
    instance.registerEObj( "Chunkoftwinklingore", 2010345, 0, 4, { 97.669884f, 392.361908f, -676.644226f }, 0.991760f, 1.218910f); 
    instance.registerEObj( "Chunkoftwinklingore_1", 2010346, 0, 4, { 104.426903f, 390.984894f, -681.502197f }, 0.991760f, 1.218910f); 
    instance.registerEObj( "Chunkoftwinklingore_2", 2010347, 0, 4, { 102.248299f, 392.999512f, -690.214478f }, 0.991760f, 1.218910f); 
    instance.registerEObj( "Slickpebble", 2010357, 0, 4, { 238.066101f, 324.745605f, -608.265076f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Slickpebble_1", 2010358, 0, 4, { 258.882690f, 319.169403f, -579.917175f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Slickpebble_2", 2010359, 0, 4, { 234.829102f, 333.739899f, -651.787903f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_30", 2010360, 0, 4, { 361.562500f, 280.659088f, -158.861801f }, 0.991760f, 1.322743f); 
    instance.registerEObj( "Ziguttsstatue", 2010736, 0, 4, { -437.606598f, 418.514496f, -598.906677f }, 0.991760f, 0.166679f); 
    instance.registerEObj( "Ziguttsstatue_1", 2010737, 0, 4, { -434.520111f, 418.449707f, -601.037598f }, 0.991760f, -1.433856f); 
    instance.registerEObj( "Ziguttsstatue_2", 2010738, 0, 4, { -436.728485f, 418.490204f, -604.217712f }, 0.991760f, -0.215000f); 
    instance.registerEObj( "Ziguttsstatue_3", 2010739, 0, 4, { -439.791992f, 418.584991f, -602.044678f }, 0.991760f, 1.386884f); 
    instance.registerEObj( "DiligentSpiritsfuelchute", 2010336, 0, 4, { -407.128387f, 417.895996f, -633.177979f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_31", 2010308, 0, 4, { -405.844208f, 362.111786f, -289.478912f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Weatheredtradingcrate", 2010309, 0, 4, { -109.668701f, 353.523285f, -181.630402f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Magmagrass", 2010516, 0, 4, { -441.033508f, 415.541199f, -560.859619f }, 0.991760f, 1.342161f); 
    instance.registerEObj( "Magmagrass_1", 2010517, 0, 4, { -439.859589f, 414.538208f, -552.166321f }, 0.991760f, -1.552487f); 
    instance.registerEObj( "Magmagrass_2", 2010518, 0, 4, { -507.888702f, 386.070312f, -443.625488f }, 0.991760f, -0.604553f); 
    instance.registerEObj( "Magmagrass_3", 2010519, 0, 4, { -495.385895f, 391.795410f, -469.962585f }, 0.991760f, -1.568506f); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSoulofTemperance );