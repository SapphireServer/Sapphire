#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class NinjaAssassin : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_OBORO_01 = 5886273;
  static constexpr auto BNPC_P1_YAMININ_01 = 5886266;
  static constexpr auto BNPC_P1_NIN_01 = 5886267;
  static constexpr auto BNPC_P1_NIN_02 = 5886268;
  static constexpr auto BNPC_P2_SUMMON_01 = 5886270;
  static constexpr auto BNPC_P2_SUMMON_02 = 5886272;
  static constexpr auto BNPC_P2_KOUMORI_01 = 5887414;
  static constexpr auto BNPC_P2_KOUMORI_02 = 5887415;
  static constexpr auto PR_P2_MOVE_TARGET_YAMININ_01 = 5891769;
  static constexpr auto EOBJ_MAKIBISHI = 5891770;
  static constexpr auto STATUS_MAKIBISHI_DAMAGE = 1221;
  static constexpr auto DEF_ACTION_MAKIBISHI = 3196;
  static constexpr auto POPTIME_KOUMORI = 30;
  static constexpr auto LCUT_ACTOR0 = 1013849;
  static constexpr auto LCUT_ACTOR1 = 1014669;
  static constexpr auto LCUT_ACTOR2 = 1014670;
  static constexpr auto LCUT_POS_ACTOR0 = 5917728;
  static constexpr auto LCUT_BGM0 = 107;

public:
  NinjaAssassin() : Sapphire::ScriptAPI::QuestBattleScript( 124 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Suspiciousfootprints", 2005711, 0, 5888470, 4, { 82.444458f, 107.886101f, -169.604095f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "Suspiciousfootprints_1", 2005712, 0, 5888471, 4, { 64.984627f, 117.230598f, -261.106598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Suspiciousfootprints_2", 2005713, 0, 5888472, 4, { 82.783508f, 122.409897f, -337.033386f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005850, 0, 5888473, 4, { 455.741089f, 157.396698f, -550.103027f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_0", 2006049, 0, 5905684, 4, { -639.116882f, 99.006371f, -431.160309f }, 0.991760f, -0.340817f, 0); 
    instance.addEObj( "unknown_1", 2005195, 0, 5886223, 4, { 461.019897f, 130.799606f, -856.343872f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_w_evt_062_01a", 2006239, 5917570, 5917573, 4, { 441.263794f, 132.120804f, -849.940613f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 4) depop (id: 5) initial_position (id: 6) 
    instance.addEObj( "sgbg_w_evt_062_01a_1", 2006240, 5917571, 5917574, 4, { 463.337311f, 132.120804f, -846.520386f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 4) depop (id: 5) initial_position (id: 6) 
    instance.addEObj( "sgbg_w_evt_062_01a_2", 2006241, 5917572, 5917575, 4, { 455.633698f, 132.120804f, -867.871887f }, 1.000000f, 0.000000f, 0); 
    // States -> pop (id: 4) depop (id: 5) initial_position (id: 6) 
    instance.addEObj( "unknown_2", 2006354, 0, 5931207, 4, { 456.085297f, 200.237701f, 668.662598f }, 1.000000f, -1.570796f, 0); 
    instance.addEObj( "unknown_3", 2006355, 0, 5931208, 4, { 456.085297f, 200.237701f, 668.662598f }, 1.000000f, -1.570796f, 0); 
    instance.addEObj( "Entrance", 2006378, 0, 5937936, 4, { -92.822998f, 88.649590f, -747.451294f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent", 2005536, 0, 5915109, 4, { 402.057800f, 191.541107f, 561.444580f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_1", 2006186, 0, 5915351, 4, { 608.951172f, 88.116852f, 186.118103f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_2", 2006187, 0, 5915357, 4, { 451.540009f, 171.226898f, -535.669983f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_3", 2006188, 0, 5915374, 4, { 84.769638f, 87.158997f, -699.125488f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_4", 2006189, 0, 5915375, 4, { -438.926788f, 110.266602f, -740.025574f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_5", 2006190, 0, 5915392, 4, { 47.747002f, 196.605698f, -677.929016f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_6", 2006191, 0, 5915399, 4, { -575.218994f, 133.975693f, -196.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_7", 2006192, 0, 5915402, 4, { 371.444000f, 165.493805f, 116.184998f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_8", 2006193, 0, 5915404, 4, { 148.118698f, 187.017807f, 232.185898f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_9", 2006194, 0, 5915413, 4, { -76.496513f, 141.844604f, 600.818726f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2005403, 0, 5856575, 4, { 430.506714f, 225.002701f, 800.932129f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2005404, 0, 5856576, 4, { 552.409973f, 228.363800f, 726.007019f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_3", 2005405, 0, 5856577, 4, { 421.592499f, 212.717194f, 708.158508f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2005406, 0, 5856590, 4, { 81.828201f, 117.198196f, 152.302597f }, 1.000000f, -0.547328f, 0); 
    instance.addEObj( "Freshfootprints", 2005408, 0, 5856593, 4, { 103.791298f, 102.329903f, -42.403690f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2005407, 0, 5856594, 4, { 103.791298f, 102.329903f, -42.403702f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005431, 0, 5853375, 4, { 455.924194f, 157.396698f, -546.257812f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Hereticepistle", 2005432, 0, 5853416, 4, { 450.858307f, 164.308304f, -544.792786f }, 0.991760f, -1.091876f, 0); 
    instance.addEObj( "Hereticepistle_1", 2005433, 0, 5853417, 4, { 443.533813f, 157.490601f, -559.471985f }, 0.991760f, 0.822658f, 0); 
    instance.addEObj( "Hereticepistle_2", 2005434, 0, 5853418, 4, { 466.788696f, 157.408295f, -540.825623f }, 0.991760f, 1.170205f, 0); 
    instance.addEObj( "unknown_7", 2005464, 0, 5854955, 4, { 617.434570f, 78.429001f, 217.266205f }, 0.595032f, 0.000048f, 0); 
    instance.addEObj( "Destination_4", 2006420, 0, 5940585, 4, { 108.352303f, 195.180206f, -48.613319f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2006412, 0, 5938889, 4, { 500.197205f, 161.613495f, -320.198700f }, 1.750000f, 0.000048f, 0); 
    instance.addEObj( "Overwhelmedcompanions", 2006415, 0, 5940566, 4, { 614.318481f, 210.882401f, -301.273010f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2006416, 0, 5940567, 4, { 610.430176f, 210.655899f, -300.965912f }, 1.000000f, 0.974363f, 0); 
    instance.addEObj( "unknown_10", 2006417, 0, 5940568, 4, { 614.144775f, 210.858200f, -301.088715f }, 1.700000f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2005472, 0, 5854901, 4, { -67.000000f, 98.000000f, 190.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2006300, 0, 5907952, 4, { 66.139999f, 103.896599f, -127.019997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2006301, 0, 5907947, 4, { -777.989990f, 112.020103f, -580.520020f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2006182, 0, 5912438, 4, { 197.426895f, 184.037994f, -102.783997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2005705, 0, 5883217, 4, { 489.838287f, 164.708496f, 266.274689f }, 0.991760f, 1.131223f, 0); 
    instance.addEObj( "unknown_13", 2005706, 0, 5883283, 4, { -159.873199f, 175.797302f, 678.757019f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2005707, 0, 5883285, 4, { -155.707199f, 175.797302f, 692.206726f }, 1.900000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2005708, 0, 5883425, 4, { -505.290710f, 120.611504f, -311.365814f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2006352, 0, 5931192, 4, { -347.517212f, 91.623962f, -558.827698f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_8", 2006272, 0, 5920969, 4, { 483.971191f, 212.539902f, 726.834473f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2006273, 0, 5921128, 4, { 319.714508f, 161.108002f, 147.447998f }, 1.000000f, -0.386335f, 0); 
    instance.addEObj( "unknown_18", 2006279, 0, 5921127, 4, { -631.281006f, 96.940552f, -461.631195f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_9", 2005967, 0, 5900051, 4, { -556.940613f, 116.691299f, -794.003113f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005979, 0, 5900158, 4, { 48.990002f, 124.449997f, 175.759995f }, 1.340293f, 0.000000f, 0); 
    instance.addEObj( "Frozenblood", 2005980, 0, 5900177, 4, { 64.682983f, 128.628906f, -397.421295f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gallantcoronet", 2005983, 0, 5900178, 4, { 108.089996f, 129.435104f, -403.500000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Frozenblood_1", 2005981, 0, 5900179, 4, { 15.490000f, 106.102402f, -419.290009f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Frozenblood_2", 2005982, 0, 5900180, 4, { -4.684570f, 94.160843f, -506.157013f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2005984, 0, 5900191, 4, { -138.353607f, 88.596428f, -577.050415f }, 1.315922f, 0.000048f, 0); 
    instance.addEObj( "unknown_21", 2005985, 0, 5900283, 4, { -788.016479f, 113.089500f, -589.788208f }, 1.000000f, 0.284314f, 0); 
    instance.addEObj( "GraveofSolkzagyltheLoyal", 2005990, 0, 5900383, 4, { 51.876450f, 125.279800f, 179.858795f }, 1.000000f, 0.382076f, 0); 
    instance.addEObj( "unknown_22", 2005991, 0, 5900397, 4, { 457.209595f, 130.799606f, -848.572388f }, 1.000000f, 1.562431f, 0); 
    instance.addEObj( "unknown_23", 2005527, 0, 5860405, 4, { 446.104187f, 139.683701f, -749.818115f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Rimeboundcrate", 2005525, 0, 5860406, 4, { 446.021301f, 140.832703f, -749.846985f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2005526, 0, 5860407, 4, { 446.009186f, 139.683701f, -749.876526f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Foultaint", 2005857, 0, 5890163, 4, { -336.402496f, 89.029999f, -586.567871f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2005858, 0, 5890170, 4, { -336.402496f, 89.029999f, -586.567871f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Foultaint_1", 2005855, 0, 5890125, 4, { -336.402496f, 89.029999f, -586.567871f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2005856, 0, 5890126, 4, { -336.402496f, 89.029114f, -586.567871f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Stolenprovisions", 2005992, 0, 5901370, 4, { 379.683899f, 167.868301f, 376.868011f }, 0.991760f, -0.556412f, 0); 
    instance.addEObj( "Snowdrift", 2006041, 0, 5901575, 4, { 481.135986f, 189.562195f, 547.508911f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Snowdrift_1", 2006042, 0, 5901577, 4, { 368.221497f, 192.100296f, 569.973206f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Snowdrift_2", 2006043, 0, 5901578, 4, { 380.422607f, 178.101700f, 491.767609f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Hemmingstrappings", 2005581, 0, 5877099, 4, { 169.816498f, 99.657356f, 27.142811f }, 0.500000f, -1.509942f, 0); 
    instance.addEObj( "Hemmingstrappings_1", 2005582, 0, 5877101, 4, { 77.979279f, 100.606102f, 11.728200f }, 0.500000f, 1.173633f, 0); 
    instance.addEObj( "Hemmingstrappings_2", 2005583, 0, 5877104, 4, { -25.563511f, 99.590752f, 64.771896f }, 1.000000f, -1.330279f, 0); 
    instance.addEObj( "Bottlefilledcrate", 2005994, 0, 5901610, 4, { 467.498901f, 224.482193f, 850.147827f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Bottlefilledcrate_1", 2005993, 0, 5901611, 4, { 467.498901f, 224.883301f, 850.147827f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Unlitbrazier", 2005995, 0, 5901838, 4, { 333.903687f, 171.103699f, -619.844971f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Litbrazier", 2005996, 0, 5901839, 4, { 333.903687f, 171.103699f, -619.844971f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_10", 2005997, 0, 5901840, 4, { 344.788300f, 168.211594f, -620.291321f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2005998, 0, 5901841, 4, { 333.903687f, 171.103699f, -619.844971f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2005999, 0, 5901842, 4, { 333.903687f, 171.103699f, -619.844971f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Unkeptgravesite", 2005586, 0, 5877109, 4, { 541.959778f, 176.804092f, -544.954407f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_29", 2005587, 0, 5877110, 4, { 541.921387f, 176.962097f, -545.059387f }, 1.500000f, -1.138921f, 0); 
    instance.addEObj( "Destination_11", 2006005, 0, 5902681, 4, { -157.689697f, 110.736603f, -52.391460f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_12", 2006006, 0, 5902682, 4, { -228.242905f, 112.497498f, -127.531502f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_13", 2006007, 0, 5902684, 4, { -348.082489f, 116.515701f, -91.932198f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2006008, 0, 5903052, 4, { -470.389893f, 93.766602f, -503.257812f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_31", 2006009, 0, 5903087, 4, { -699.943115f, 100.159897f, -602.810181f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Dragonspitspring", 2005591, 0, 5877114, 4, { -673.534973f, 99.184601f, -605.066589f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Fallenchocobo", 2005592, 0, 5877116, 4, { 113.951500f, 158.560699f, 403.434387f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_32", 2006010, 0, 5903095, 4, { -287.764893f, 76.983368f, -277.994904f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Slainaevis", 2006013, 0, 5903096, 4, { -287.764893f, 77.757156f, -277.994904f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_14", 2006014, 0, 5903097, 4, { -291.844391f, 76.983368f, -261.000885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2006011, 0, 5903100, 4, { -249.379303f, 126.803398f, 8.339031f }, 0.991760f, -1.264632f, 0); 
    instance.addEObj( "Wyvernleg", 2006015, 0, 5903102, 4, { -252.329697f, 127.016296f, 11.107950f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_34", 2005766, 0, 5888177, 4, { 638.996216f, 202.060104f, -180.769302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_35", 2005767, 0, 5888178, 4, { 650.162781f, 202.290100f, -163.426407f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2005768, 0, 5888179, 4, { 671.861328f, 202.891495f, -153.754898f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_37", 2005769, 0, 5888180, 4, { 637.334778f, 201.961105f, -203.292801f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Rimedcorpse", 2006017, 0, 5903111, 4, { -253.345596f, 221.393097f, 528.923523f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_38", 2006018, 0, 5903119, 4, { -152.397003f, 219.002899f, 669.964417f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Decayingwyvern", 2006019, 0, 5903120, 4, { -152.397003f, 219.634705f, 669.964417f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Decayingwyvern_1", 2006181, 0, 5911918, 4, { -152.397003f, 219.634705f, 669.964417f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Abandonedeffects", 2005770, 0, 5888202, 4, { -478.573486f, 162.362106f, 8.634455f }, 0.991760f, -1.383454f, 0); 
    instance.addEObj( "Abandonedeffects_1", 2005771, 0, 5888203, 4, { -456.931396f, 171.549103f, 91.921127f }, 0.991760f, 1.132097f, 0); 
    instance.addEObj( "Abandonedeffects_2", 2005772, 0, 5888204, 4, { -524.442688f, 165.094299f, 61.538990f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_39", 2006023, 0, 5903139, 4, { -533.334290f, 118.959702f, -167.634995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_40", 2006024, 0, 5903140, 4, { -525.772583f, 118.917099f, -165.737000f }, 0.750000f, -1.085283f, 0); 
    instance.addEObj( "Wyvernbone", 2006026, 0, 5903154, 4, { -525.688599f, 119.096603f, -165.728302f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_15", 2006027, 0, 5903155, 4, { -92.565598f, 96.341217f, -645.083374f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_41", 2006025, 0, 5903156, 4, { -92.565598f, 96.045303f, -645.083374f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Destination_16", 2006028, 0, 5903157, 4, { -92.489616f, 93.528954f, -623.601807f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wyvernbone_1", 2006460, 0, 5963680, 4, { -92.565598f, 96.341202f, -645.083374f }, 1.000000f, -0.000000f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( NinjaAssassin );