#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AgainsttheShadow : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_WIDARGELT = 5886248;
  static constexpr auto BNPC_P1_KEGEMNK_01 = 5886249;
  static constexpr auto BNPC_P1_KEGEMNK_02 = 5886250;
  static constexpr auto BNPC_P1_ENERGY_01 = 5887413;
  static constexpr auto BNPC_P1_ENERGY_02 = 5916107;
  static constexpr auto ACTION_ENERGY_SUMMON = 1094;
  static constexpr auto LOC_POP_0 = 5919819;
  static constexpr auto LOC_POP_1 = 5919820;
  static constexpr auto LOC_ACTOR_0 = 1014543;
  static constexpr auto LOC_ACTOR_1 = 1014540;
  static constexpr auto LOC_ACTOR_2 = 1014541;
  static constexpr auto BGM_BATTLE = 107;
  static constexpr auto LOC_ACTION1 = 1071;
  static constexpr auto LOC_ACTION2 = 173;
  static constexpr auto LOCKON_BY_ENERGY_BALL_THUNDER = 1;

public:
  AgainsttheShadow() : Sapphire::ScriptAPI::QuestBattleScript( 123 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Whizzlepop", 2006178, 0, 5914865, 4, { 468.955414f, 83.634644f, 75.028557f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Whizzlepop_1", 2006178, 0, 5914866, 4, { 484.702789f, 83.634644f, 79.209473f }, 0.991760f, 1.353711f, 0); 
    instance.addEObj( "Whizzlepop_2", 2006178, 0, 5914867, 4, { 449.484985f, 78.324463f, 94.804321f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Whizzlepop_3", 2006178, 0, 5914868, 4, { 496.635315f, 78.324463f, 95.017822f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Whizzlepop_4", 2006178, 0, 5914869, 4, { 508.445801f, 78.324463f, 83.848267f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Whizzlepop_5", 2006178, 0, 5914870, 4, { 478.019287f, 82.200317f, 89.585693f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tornfolio", 2006177, 0, 5918890, 4, { -469.077606f, 147.960098f, 37.094601f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tornfolio_1", 2006177, 0, 5918891, 4, { -447.521790f, 147.960098f, 44.959572f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tornfolio_2", 2006177, 0, 5918894, 4, { -499.840210f, 147.124603f, 74.760567f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tornfolio_3", 2006177, 0, 5918895, 4, { -448.233795f, 148.655899f, 106.340103f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tornfolio_4", 2006177, 0, 5918897, 4, { -487.540985f, 147.936203f, 104.173203f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tornfolio_5", 2006177, 0, 5918898, 4, { -445.640594f, 148.075302f, 74.881439f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tornfolio_6", 2006177, 0, 5918899, 4, { -468.033112f, 147.534698f, 65.401581f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "×テスト用タロットカード", 2006327, 5926325, 5926254, 4, { -364.156586f, 148.638107f, 72.007202f }, 0.991760f, 0.000048f, 0); 
    // States -> pop (id: 2) depop (id: 3) initial_position (id: 4) depop2 (id: 14) 
    instance.addEObj( "×テスト用タロットカード_1", 2006327, 5939341, 5939358, 4, { -388.050995f, 147.304398f, 61.335800f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 2) depop (id: 3) initial_position (id: 4) 
    instance.addEObj( "×テスト用タロットカード_2", 2006327, 5939343, 5939361, 4, { -381.060913f, 147.961197f, 48.224800f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 2) depop (id: 3) initial_position (id: 4) 
    instance.addEObj( "×テスト用タロットカード_3", 2006327, 5939347, 5939365, 4, { -364.126099f, 147.942001f, 48.592800f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 2) depop (id: 3) initial_position (id: 4) 
    instance.addEObj( "×テスト用タロットカード_4", 2006327, 5939351, 5939367, 4, { -355.883301f, 147.344498f, 59.922100f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 2) depop (id: 3) initial_position (id: 4) 
    instance.addEObj( "×テスト用タロットカード_5", 2006327, 5939354, 5939371, 4, { -380.330902f, 148.399994f, 72.418503f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 2) depop (id: 3) initial_position (id: 4) depop2 (id: 15) 
    instance.addEObj( "Miningpoint", 2005948, 0, 5896354, 4, { 350.385193f, 103.481201f, 333.905701f }, 0.991760f, -0.502449f, 0); 
    instance.addEObj( "Miningpoint_1", 2005949, 0, 5896355, 4, { 386.178009f, 77.173691f, 286.532898f }, 0.991760f, 0.539922f, 0); 
    instance.addEObj( "Miningpoint_2", 2005950, 0, 5896356, 4, { 338.867310f, 92.510757f, 314.268585f }, 0.991760f, -0.695240f, 0); 
    instance.addEObj( "Entrance", 2006170, 0, 5910294, 4, { 66.847069f, 53.518860f, 206.442093f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Summoningstone", 2005697, 0, 5881964, 4, { -50.200001f, 100.699997f, -203.000000f }, 1.000000f, -0.986647f, 0); 
    instance.addEObj( "Aethercurrent", 2006205, 0, 5915602, 4, { 675.618591f, 135.766693f, 197.819199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_1", 2006206, 0, 5915604, 4, { 744.640198f, 136.651398f, -50.351330f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_2", 2006207, 0, 5915606, 4, { 34.459450f, 52.695290f, 33.240330f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_3", 2006208, 0, 5915608, 4, { -236.356995f, 123.322701f, -218.482895f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_4", 2006209, 0, 5915611, 4, { -827.153870f, 163.863297f, -35.545269f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_5", 2006210, 0, 5915612, 4, { -570.765625f, 147.103806f, 67.313904f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Aethercurrent_6", 2006211, 0, 5915614, 4, { -854.554993f, 200.848495f, 531.080017f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_7", 2006212, 0, 5915615, 4, { -85.253738f, 202.540497f, 766.753174f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_8", 2006213, 0, 5915619, 4, { 239.161697f, 101.922401f, 210.727097f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_9", 2006214, 0, 5915621, 4, { -175.834000f, 201.449600f, 460.726990f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2005422, 0, 5860158, 4, { 365.858002f, 80.111427f, 6.336100f }, 0.700000f, -1.242511f, 0); 
    instance.addEObj( "Icywall", 2005532, 0, 5860200, 4, { -488.753510f, 139.000000f, 742.140625f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_1", 2005424, 0, 5860265, 4, { 302.480103f, 232.541000f, 769.685791f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Junkpile", 2006124, 0, 5909567, 4, { -43.184841f, 100.860100f, -181.803406f }, 1.500000f, 0.000048f, 0); 
    instance.addEObj( "Glowstone", 2006180, 0, 5911714, 4, { -43.691639f, 101.511597f, -181.605194f }, 0.300000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2006120, 0, 5909562, 4, { 67.954803f, 53.337669f, 199.524597f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2006121, 0, 5909563, 4, { -35.829231f, 100.968903f, -182.818405f }, 0.991760f, -1.267423f, 0); 
    instance.addEObj( "unknown_3", 2006122, 0, 5909564, 4, { -43.015411f, 100.863297f, -181.850601f }, 1.000000f, -0.618664f, 0); 
    instance.addEObj( "unknown_4", 2006123, 0, 5909565, 4, { -43.015400f, 100.863297f, -181.850601f }, 1.000000f, -0.618663f, 0); 
    instance.addEObj( "unknown_5", 2006377, 0, 5937554, 4, { -370.451996f, 147.343506f, 59.130798f }, 1.000000f, 1.430050f, 0); 
    instance.addEObj( "unknown_6", 2005976, 0, 5900028, 4, { 277.140015f, 232.540695f, 760.147705f }, 1.000000f, 1.453210f, 0); 
    instance.addEObj( "Caveentrance", 2005336, 0, 5822037, 4, { -488.776215f, 138.939499f, 741.083679f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2006097, 0, 5910209, 4, { 263.362305f, 65.640320f, -293.500885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2005868, 0, 5891905, 4, { 55.846031f, 83.322662f, -218.278305f }, 1.250000f, -0.000000f, 0); 
    instance.addEObj( "unknown_9", 2005869, 0, 5891906, 4, { 104.551102f, 63.322899f, -218.278305f }, 1.250000f, -0.000000f, 0); 
    instance.addEObj( "Cumbersomesack", 2005870, 0, 5891912, 4, { 295.317688f, 81.681519f, -91.096786f }, 0.991760f, -0.942303f, 0); 
    instance.addEObj( "Cumbersomesack_1", 2005871, 0, 5891913, 4, { 345.199493f, 89.982986f, -65.423737f }, 1.000000f, -1.160410f, 0); 
    instance.addEObj( "Cumbersomesack_2", 2005872, 0, 5891914, 4, { 282.068298f, 89.360260f, -12.468200f }, 1.000000f, 0.456910f, 0); 
    instance.addEObj( "Cumbersomesack_3", 2005873, 0, 5891915, 4, { 302.078796f, 89.048439f, 35.632370f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005874, 0, 5891917, 4, { 245.354599f, 76.590141f, 66.343246f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2005875, 0, 5891918, 4, { 238.972794f, 78.387543f, -66.320671f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2005876, 0, 5891919, 4, { 342.064606f, 74.754539f, -115.019501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2006098, 0, 5910241, 4, { 302.477692f, 68.258797f, -151.692093f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Illuminatipot", 2005877, 0, 5891925, 4, { 458.717285f, 83.734993f, 34.751110f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Illuminatipot_1", 2005878, 0, 5891926, 4, { 490.792603f, 83.734993f, -14.838050f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Illuminatipot_2", 2005879, 0, 5891927, 4, { 496.438385f, 83.734993f, 18.637409f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2005880, 0, 5891935, 4, { 428.829315f, 77.958679f, 123.093903f }, 1.000000f, 0.000237f, 0); 
    instance.addEObj( "unknown_12", 2005881, 0, 5891936, 4, { 560.914185f, 77.492340f, 58.516762f }, 0.991760f, -0.001129f, 0); 
    instance.addEObj( "unknown_13", 2005882, 0, 5891937, 4, { 535.353088f, 77.941689f, -103.999199f }, 0.991760f, -0.000334f, 0); 
    instance.addEObj( "unknown_14", 2006099, 0, 5910271, 4, { 302.477692f, 68.258797f, -151.692093f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2006100, 0, 5910339, 4, { -194.384003f, 106.599998f, -283.763885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2006101, 0, 5910340, 4, { -214.634399f, 106.737602f, -275.883606f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_17", 2006102, 0, 5910341, 4, { -204.562500f, 106.599998f, -298.463898f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2006103, 0, 5910368, 4, { -408.899506f, 150.641296f, -173.987595f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Bonfire", 2006104, 0, 5910369, 4, { -408.897797f, 150.861603f, -174.005997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005883, 0, 5891973, 4, { -492.578796f, 154.833893f, -54.580910f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005884, 0, 5891981, 4, { -403.280701f, 154.833298f, 82.841187f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_21", 2005886, 0, 5891985, 4, { -403.264008f, 154.854202f, 82.870903f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenitems", 2005885, 0, 5891986, 4, { -403.264008f, 155.378601f, 82.870903f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2005887, 0, 5891998, 4, { -894.438110f, 215.228394f, 155.870804f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_23", 2005888, 0, 5892023, 4, { -618.736877f, 153.852798f, 349.298096f }, 1.000000f, -1.155719f, 0); 
    instance.addEObj( "Medicinalherbs", 2006061, 0, 5908212, 4, { -486.902008f, 137.429703f, 701.342102f }, 1.200000f, 0.881142f, 0); 
    instance.addEObj( "Medicinalherbs_1", 2006062, 0, 5908220, 4, { -471.824493f, 137.407501f, 705.582581f }, 1.174927f, 0.941831f, 0); 
    instance.addEObj( "Medicinalherbs_2", 2006063, 0, 5908221, 4, { -473.474915f, 137.429703f, 685.415283f }, 1.200000f, -0.735027f, 0); 
    instance.addEObj( "Shatteredaetheryte", 2006064, 0, 5908227, 4, { -599.666077f, 192.387100f, 496.895386f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_1", 2006065, 0, 5908228, 4, { -170.563293f, 200.106003f, 785.351013f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_2", 2006066, 0, 5908229, 4, { 183.243805f, 220.296402f, 746.857788f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_3", 2006067, 0, 5908230, 4, { -635.898193f, 151.933502f, 258.842712f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_4", 2006068, 0, 5908231, 4, { -588.560425f, 147.960098f, -53.630131f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_5", 2006069, 0, 5908232, 4, { -284.291595f, 147.960098f, -17.666050f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_6", 2006070, 0, 5908233, 4, { 132.313004f, 61.211311f, -206.626907f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Shatteredaetheryte_7", 2006071, 0, 5908234, 4, { 360.438904f, 78.409119f, 24.533991f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Untaintedspring", 2006072, 0, 5908235, 4, { -876.746887f, 167.078598f, 42.687580f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Untaintedspring_1", 2006073, 0, 5908236, 4, { -924.618286f, 223.969406f, 266.099487f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Untaintedspring_2", 2006074, 0, 5908238, 4, { -782.166992f, 176.273605f, 391.587585f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Untaintedspring_3", 2006075, 0, 5908239, 4, { -883.822815f, 200.346603f, 495.039612f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Untaintedspring_4", 2006076, 0, 5908240, 4, { -786.308411f, 157.753998f, 613.195618f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Woodenbridge", 2006077, 0, 5908242, 4, { -843.795410f, 214.039902f, 360.664795f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "×未使用", 2006078, 0, 5908245, 4, { -81.739700f, 152.540802f, 747.876770f }, 1.000000f, -0.000211f, 0); 
    instance.addEObj( "×未使用_1", 2006079, 0, 5908246, 4, { -81.739700f, 152.540802f, 747.876770f }, 1.000000f, -0.000211f, 0); 
    instance.addEObj( "Destination_3", 2006080, 0, 5908247, 4, { -81.739700f, 152.540802f, 747.876770f }, 1.000000f, -0.000211f, 0); 
    instance.addEObj( "Destination_4", 2006081, 0, 5908257, 4, { -327.220490f, 137.129700f, 664.798584f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2006082, 0, 5908258, 4, { -437.388489f, 137.102295f, 604.897095f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_6", 2006083, 0, 5908259, 4, { -363.290009f, 137.129700f, 555.723206f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AgainsttheShadow );