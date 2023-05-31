#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SteelagainstSteel : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_VITUS = 8007473;
  static constexpr auto P_BNPC_RADOVAN = 8007476;
  static constexpr auto P_BNPC_SOPHIE = 8007477;
  static constexpr auto BNPC_TRASH_RASER_001 = 8007480;
  static constexpr auto BNPC_TRASH_RASER_002 = 8007481;
  static constexpr auto BNPC_TRASH_RASER_003 = 8007482;
  static constexpr auto BNPC_TRASH_CANNON_001 = 8007484;
  static constexpr auto BNPC_TRASH_CANNON_002 = 8007487;
  static constexpr auto BNPC_TRASH_CANNON_003 = 8007488;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_001 = 8010353;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_002 = 8010354;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_003 = 8010355;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_004 = 8010356;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_005 = 8010357;
  static constexpr auto BNPC_TOMEI_BREAK_FRAGMENTS_BLADE_006 = 8010358;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_ABOVE_SMALL = 8010367;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_ABOVE_MIDDLE = 8010368;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_ABOVE_BIG = 8010369;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_BELOW_SMALL = 8010371;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_BELOW_MIDDLE = 8010372;
  static constexpr auto BNPC_TOMEI_DIMENSION_BLADE_BELOW_BIG = 8010373;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_001 = 8010380;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_002 = 8010381;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_003 = 8010382;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_004 = 8010383;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_005 = 8010384;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_006 = 8010385;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_007 = 8010386;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_FIRST_008 = 8010387;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_001 = 8010388;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_002 = 8010392;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_003 = 8010393;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_004 = 8010394;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_005 = 8010395;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_006 = 8010396;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_007 = 8010397;
  static constexpr auto BNPC_TOMEI_OCT_EXPLOSION_BLADE_SECOND_008 = 8010398;
  static constexpr auto BNPC_LANDMINE_001 = 8010469;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_12 = 8010470;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_12 = 8010475;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_2 = 8010491;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_2 = 8010492;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_3 = 8010493;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_3 = 8010494;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_4 = 8010495;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_4 = 8010496;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_6 = 8010502;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_6 = 8010503;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_8 = 8010511;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_8 = 8010512;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_9 = 8010547;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_9 = 8010548;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_INSIDE_10 = 8010549;
  static constexpr auto BNPC_TOMEI_MOVE_TO_TRAP_OUTSIDE_10 = 8010550;
  static constexpr auto BNPC_TOMEI_VITUS_FINAL_RAIDDAMAGE = 8010594;
  static constexpr auto BNPC_TOMEI_VITUS_NOMAL_ACTION = 8010596;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_ABOVE_LEFT = 8010597;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_ABOVE_RIGHT = 8010598;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_BELOW_LEFT = 8010599;
  static constexpr auto BNPC_TOMEI_CROSS_BLADE_BELOW_RIGHT = 8010600;
  static constexpr auto BGM_BOSS = 165;
  static constexpr auto ACTION_VITUS_OCT_EXPLOSION_BLADE1 = 17551;
  static constexpr auto ACTION_VITUS_TRAP_POP = 17554;
  static constexpr auto ACTION_VITUS_SHARE_ATTACK = 17557;
  static constexpr auto ACTION_VITUS_BREAK_FRAGMENTS_BLADE = 17560;
  static constexpr auto ACTION_VITUS_DIMENSION_BLADE = 17562;
  static constexpr auto ACTION_VITUS_CROSS_BLADE = 17566;
  static constexpr auto ACTION_VITUS_ALL_ORDER = 17568;
  static constexpr auto ACTION_VITUS_FINAL_RAIDDAMAGE = 17572;
  static constexpr auto ACTION_VITUS_SHARE_ATTACK_HIT = 17558;
  static constexpr auto ACTION_PLAYER_GUNBREAKER_COMBO3 = 16145;
  static constexpr auto ACTION_PLAYER_GUNBREAKER_MAGICBULLET = 16150;
  static constexpr auto STATUS_PARAM_NPC_KNOCKDOWN = 5210;
  static constexpr auto ACTION_SOPHIE_BENEDICTION = 17587;
  static constexpr auto STATUS_PARAM_NPC_KNOCKDOWN_SHORT = 5206;
  static constexpr auto BGM_NO_MUSIC = 1;
  static constexpr auto PR_P2_VITUS_FINAL_RAIDDAMAGE_TOMEI_WARP_001 = 8012542;
  static constexpr auto ACTION_VITUS_QUICKSTEP = 17556;
  static constexpr auto ACTION_VITUS_WIDERANGE_EXPLOSION_SHOTGUN = 17569;
  static constexpr auto STATUS_NPC_KNOCKDOWN = 774;
  static constexpr auto ACTION_VITUS_FINAL_RAIDDAMAGE_HIT = 17573;
  static constexpr auto YELL_SOPHIE_003 = 8300;
  static constexpr auto ACTION_SOPHIE_STONE3 = 17603;
  static constexpr auto YELL_VITUS_002 = 8291;
  static constexpr auto YELL_VITUS_006 = 8299;
  static constexpr auto YELL_SOPHIE_004 = 8302;
  static constexpr auto ACTION_SOPHIE_MAGICPOW_DISTRIBUTION = 17589;
  static constexpr auto YELL_RADOVAN_003 = 8303;
  static constexpr auto YELL_RADOVAN_004 = 8304;
  static constexpr auto ACTION_RADOVAN_TANK_LIMITBREAK = 17576;
  static constexpr auto YELL_RADOVAN_002 = 8294;
  static constexpr auto YELL_SOPHIE_002 = 8295;
  static constexpr auto ACTION_VITUS_MOTIONCENCER_BOMB_NOMAL = 17580;
  static constexpr auto ACTION_VITUS_MOTIONCENCER_BOMB_SHORT = 17634;
  static constexpr auto ACTION_VITUS_MOTIONCENCER_BOMB_EXPLOSION = 17630;
  static constexpr auto STATUS_MOTION_CENCER_BOMB = 1072;
  static constexpr auto ACTION_TOMEI_DIMENSION_BLADE = 17563;
  static constexpr auto ACTION_VITUS_WIDERANGE_BLADE = 17559;
  static constexpr auto ACTION_VITUS_BLADE_FORCE = 17988;
  static constexpr auto BNPC_TOMEI_BLADE_FORCE = 8034825;
  static constexpr auto PR_RADVAN_LIMITBREAK_MOVE_RANGE = 8035357;
  static constexpr auto PR_SOPHIE_LIMITBREAK_MOVE_RANGE = 8035984;

public:
  SteelagainstSteel() : Sapphire::ScriptAPI::QuestBattleScript( 194 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Suspiciousfootprints", 2005711, 0, 4, { 82.444458f, 107.886101f, -169.604095f }, 1.000000f, 0.000048f); 
    instance.registerEObj( "Suspiciousfootprints_1", 2005712, 0, 4, { 64.984627f, 117.230598f, -261.106598f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Suspiciousfootprints_2", 2005713, 0, 4, { 82.783508f, 122.409897f, -337.033386f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination", 2005850, 0, 4, { 455.741089f, 157.396698f, -550.103027f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_0", 2006049, 0, 4, { -639.116882f, 99.006371f, -431.160309f }, 0.991760f, -0.340817f); 
    instance.registerEObj( "unknown_1", 2005195, 0, 4, { 461.019897f, 130.799606f, -856.343872f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_w_evt_062_01a", 2006239, 5917570, 4, { 441.263794f, 132.120804f, -849.940613f }, 1.000000f, 0.000000f); 
    // States -> pop (id: 4) depop (id: 5) initial_position (id: 6) 
    instance.registerEObj( "sgbg_w_evt_062_01a_1", 2006240, 5917571, 4, { 463.337311f, 132.120804f, -846.520386f }, 1.000000f, 0.000000f); 
    // States -> pop (id: 4) depop (id: 5) initial_position (id: 6) 
    instance.registerEObj( "sgbg_w_evt_062_01a_2", 2006241, 5917572, 4, { 455.633698f, 132.120804f, -867.871887f }, 1.000000f, 0.000000f); 
    // States -> pop (id: 4) depop (id: 5) initial_position (id: 6) 
    instance.registerEObj( "Destination_1", 2011548, 0, 4, { -92.575699f, 87.189003f, -737.858704f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2011549, 0, 4, { -92.575699f, 87.189003f, -737.858704f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Destination_2", 2013439, 0, 4, { -92.575699f, 87.189003f, -737.858704f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Destination_3", 2006877, 0, 4, { -276.611511f, 122.295898f, -45.028431f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2006959, 0, 4, { -276.569794f, 122.268600f, -45.181950f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_4", 2006603, 0, 4, { 782.208313f, 216.657394f, 219.770599f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_5", 2006617, 0, 4, { 782.208313f, 216.657394f, 219.770599f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_6", 2006753, 0, 4, { -217.042206f, 88.103859f, -585.253479f }, 0.991760f, 0.000240f); 
    instance.registerEObj( "unknown_4", 2006760, 0, 4, { 789.272827f, 185.992203f, -529.350708f }, 0.991760f, 1.394841f); 
    instance.registerEObj( "Gentlemanlylegs", 2006763, 0, 4, { 789.272827f, 186.449997f, -529.350708f }, 0.991760f, 1.394841f); 
    instance.registerEObj( "Footprints", 2007179, 0, 4, { 406.118896f, 195.658905f, 585.564880f }, 0.991760f, -0.955157f); 
    instance.registerEObj( "Footprints_1", 2007180, 0, 4, { 262.104187f, 163.327194f, 295.674103f }, 0.991760f, -0.233216f); 
    instance.registerEObj( "unknown_5", 2007215, 0, 4, { 262.134613f, 163.408798f, 295.674103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2006354, 0, 4, { 456.085297f, 200.237701f, 668.662598f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "unknown_7", 2006355, 0, 4, { 456.085297f, 200.237701f, 668.662598f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "Entrance", 2006378, 0, 4, { -92.822998f, 88.649590f, -747.451294f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aethercurrent", 2005536, 0, 4, { 402.029297f, 191.536499f, 561.425171f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Aethercurrent_1", 2006187, 0, 4, { 424.957794f, 164.308304f, -536.905029f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aethercurrent_2", 2006190, 0, 4, { -660.143677f, 135.545502f, -376.630188f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Aethercurrent_3", 2006189, 0, 4, { -332.887512f, 126.844200f, -29.952240f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_7", 2005403, 0, 4, { 430.506714f, 225.002701f, 800.932129f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_8", 2005404, 0, 4, { 552.409973f, 228.363800f, 726.007019f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_9", 2005405, 0, 4, { 421.592499f, 212.717194f, 708.158508f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2005406, 0, 4, { 81.828201f, 117.198196f, 152.302597f }, 1.000000f, -0.547328f); 
    instance.registerEObj( "Freshfootprints", 2005408, 0, 4, { 103.791298f, 102.329903f, -42.403690f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2005407, 0, 4, { 103.791298f, 102.329903f, -42.403702f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2005431, 0, 4, { 455.924194f, 157.396698f, -546.257812f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Hereticepistle", 2005432, 0, 4, { 450.858307f, 164.308304f, -544.792786f }, 0.991760f, -1.091876f); 
    instance.registerEObj( "Hereticepistle_1", 2005433, 0, 4, { 443.533813f, 157.490601f, -559.471985f }, 0.991760f, 0.822658f); 
    instance.registerEObj( "Hereticepistle_2", 2005434, 0, 4, { 466.788696f, 157.408295f, -540.825623f }, 0.991760f, 1.170205f); 
    instance.registerEObj( "unknown_11", 2005464, 0, 4, { 617.434570f, 78.429001f, 217.266205f }, 0.595032f, 0.000048f); 
    instance.registerEObj( "Destination_10", 2006869, 0, 4, { 334.805908f, 186.134598f, 442.234314f }, 0.991760f, 0.459961f); 
    instance.registerEObj( "Destination_11", 2006870, 0, 4, { 439.993896f, 165.457794f, 344.777496f }, 0.991760f, -1.567594f); 
    instance.registerEObj( "Destination_12", 2006420, 0, 4, { 108.352303f, 195.180206f, -48.613319f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_12", 2006412, 0, 4, { 500.197205f, 161.613495f, -320.198700f }, 1.750000f, 0.000048f); 
    instance.registerEObj( "Overwhelmedcompanions", 2006415, 0, 4, { 614.318481f, 210.882401f, -301.273010f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2006416, 0, 4, { 610.430176f, 210.655899f, -300.965912f }, 1.000000f, 0.974363f); 
    instance.registerEObj( "unknown_14", 2006417, 0, 4, { 614.144775f, 210.858200f, -301.088715f }, 1.700000f, 0.000048f); 
    instance.registerEObj( "unknown_15", 2005472, 0, 4, { -67.000000f, 98.000000f, 190.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_13", 2006300, 0, 4, { 66.139999f, 103.896599f, -127.019997f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_14", 2006301, 0, 4, { -777.989990f, 112.020103f, -580.520020f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_15", 2006182, 0, 4, { 197.426895f, 184.037994f, -102.783997f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_16", 2005705, 0, 4, { 489.838287f, 164.708496f, 266.274689f }, 0.991760f, 1.131223f); 
    instance.registerEObj( "unknown_17", 2005706, 0, 4, { -159.873199f, 175.797302f, 678.757019f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_18", 2005707, 0, 4, { -155.707199f, 175.797302f, 692.206726f }, 1.900000f, 0.000000f); 
    instance.registerEObj( "unknown_19", 2005708, 0, 4, { -505.290710f, 120.611504f, -311.365814f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_20", 2006352, 0, 4, { -347.517212f, 91.623962f, -558.827698f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Swirlingabyss", 2008661, 0, 4, { 380.025909f, 169.811401f, 416.586487f }, 0.991760f, -0.097265f); 
    instance.registerEObj( "Destination_16", 2006272, 0, 4, { 483.971191f, 212.539902f, 726.834473f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_21", 2006273, 0, 4, { 319.714508f, 161.108002f, 147.447998f }, 1.000000f, -0.386335f); 
    instance.registerEObj( "unknown_22", 2006279, 0, 4, { -631.281006f, 96.940552f, -461.631195f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_23", 2008386, 0, 4, { 662.980713f, 202.510498f, -177.133804f }, 1.500000f, 0.000000f); 
    instance.registerEObj( "Destination_17", 2005967, 0, 4, { -556.940613f, 116.691299f, -794.003113f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_24", 2005979, 0, 4, { 48.990002f, 124.449997f, 175.759995f }, 1.340293f, 0.000000f); 
    instance.registerEObj( "Frozenblood", 2005980, 0, 4, { 64.682983f, 128.628906f, -397.421295f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Gallantcoronet", 2005983, 0, 4, { 108.089996f, 129.435104f, -403.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Frozenblood_1", 2005981, 0, 4, { 15.490000f, 106.102402f, -419.290009f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Frozenblood_2", 2005982, 0, 4, { -4.684570f, 94.160843f, -506.157013f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_25", 2005984, 0, 4, { -138.353607f, 88.596428f, -577.050415f }, 1.315922f, 0.000048f); 
    instance.registerEObj( "unknown_26", 2005985, 0, 4, { -788.016479f, 113.089500f, -589.788208f }, 1.000000f, 0.284314f); 
    instance.registerEObj( "GraveofSolkzagyltheLoyal", 2005990, 0, 4, { 51.876450f, 125.279800f, 179.858795f }, 1.000000f, 0.382076f); 
    instance.registerEObj( "unknown_27", 2005991, 0, 4, { 457.209595f, 130.799606f, -848.572388f }, 1.000000f, 1.562431f); 
    instance.registerEObj( "unknown_28", 2008326, 0, 4, { 362.315704f, 161.108002f, 27.931511f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_29", 2008329, 0, 4, { -217.821106f, 112.328201f, -243.916504f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_30", 2005527, 0, 4, { 446.104187f, 139.683701f, -749.818115f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rimeboundcrate", 2005525, 0, 4, { 446.021301f, 140.832703f, -749.846985f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_31", 2005526, 0, 4, { 446.009186f, 139.683701f, -749.876526f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Foultaint", 2005857, 0, 4, { -336.402496f, 89.029999f, -586.567871f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_32", 2005858, 0, 4, { -336.402496f, 89.029999f, -586.567871f }, 1.500000f, 0.000000f); 
    instance.registerEObj( "Foultaint_1", 2005855, 0, 4, { -336.402496f, 89.029999f, -586.567871f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_33", 2005856, 0, 4, { -336.402496f, 89.029114f, -586.567871f }, 1.500000f, 0.000000f); 
    instance.registerEObj( "unknown_34", 2010244, 0, 4, { -266.409210f, 92.167953f, -501.851196f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_18", 2009740, 0, 4, { 348.012512f, 158.373306f, 153.032700f }, 0.991760f, -1.433575f); 
    instance.registerEObj( "Destination_19", 2009741, 0, 4, { 504.741699f, 121.658203f, 162.035400f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_35", 2011697, 0, 4, { 667.746704f, 185.035599f, -452.942291f }, 0.991760f, 0.284606f); 
    instance.registerEObj( "Stolensupplies", 2005992, 0, 4, { 379.683899f, 167.868301f, 376.868011f }, 0.991760f, -0.556412f); 
    instance.registerEObj( "Snowdrift", 2006041, 0, 4, { 481.135986f, 189.562195f, 547.508911f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Snowdrift_1", 2006042, 0, 4, { 368.221497f, 192.100296f, 569.973206f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Snowdrift_2", 2006043, 0, 4, { 380.422607f, 178.101700f, 491.767609f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Hemmingstrappings", 2005581, 0, 4, { 169.787094f, 99.656616f, 27.115231f }, 0.472961f, -1.509942f); 
    instance.registerEObj( "Hemmingstrappings_1", 2005582, 0, 4, { 77.979279f, 100.606102f, 11.728200f }, 0.500000f, 1.173633f); 
    instance.registerEObj( "Hemmingstrappings_2", 2005583, 0, 4, { -25.563511f, 99.590752f, 64.771896f }, 1.000000f, -1.330279f); 
    instance.registerEObj( "Bottlefilledcrate", 2005994, 0, 4, { 467.498901f, 224.482193f, 850.147827f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Bottlefilledcrate_1", 2005993, 0, 4, { 467.498901f, 224.883301f, 850.147827f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Unlitbrazier", 2005995, 0, 4, { 333.903687f, 171.103699f, -619.844971f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Litbrazier", 2005996, 0, 4, { 333.903687f, 171.103699f, -619.844971f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_20", 2005997, 0, 4, { 344.788300f, 168.211594f, -620.291321f }, 1.500000f, 0.000000f); 
    instance.registerEObj( "unknown_36", 2005998, 0, 4, { 333.903687f, 171.103699f, -619.844971f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_37", 2005999, 0, 4, { 333.903687f, 171.103699f, -619.844971f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Unkeptgravesite", 2005586, 0, 4, { 541.959778f, 176.804092f, -544.954407f }, 1.500000f, 0.000000f); 
    instance.registerEObj( "unknown_38", 2005587, 0, 4, { 541.921387f, 176.962097f, -545.059387f }, 1.500000f, -1.138921f); 
    instance.registerEObj( "Destination_21", 2006005, 0, 4, { -157.689697f, 110.736603f, -52.391460f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_22", 2006006, 0, 4, { -228.242905f, 112.497498f, -127.531502f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_23", 2006007, 0, 4, { -348.082489f, 116.515701f, -91.932198f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_39", 2006008, 0, 4, { -470.389893f, 93.766602f, -503.257812f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_40", 2006009, 0, 4, { -699.943115f, 100.159897f, -602.810181f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Dragonspitspring", 2005591, 0, 4, { -673.534973f, 99.184601f, -605.066589f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenchocobo", 2005592, 0, 4, { 113.951500f, 158.560699f, 403.434387f }, 1.500000f, 0.000000f); 
    instance.registerEObj( "unknown_41", 2006010, 0, 4, { -287.764893f, 76.983368f, -277.994904f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Slainaevis", 2006013, 0, 4, { -287.764893f, 77.757156f, -277.994904f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_24", 2006014, 0, 4, { -291.844391f, 76.983368f, -261.000885f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_42", 2006011, 0, 4, { -249.379303f, 126.803398f, 8.339031f }, 0.991760f, -1.264632f); 
    instance.registerEObj( "Wyvernleg", 2006015, 0, 4, { -252.329697f, 127.016296f, 11.107950f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_43", 2005766, 0, 4, { 638.996216f, 202.060104f, -180.769302f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_44", 2005767, 0, 4, { 650.162781f, 202.290100f, -163.426407f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_45", 2005768, 0, 4, { 671.861328f, 202.891495f, -153.754898f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_46", 2005769, 0, 4, { 637.334778f, 201.961105f, -203.292801f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rimedcorpse", 2006017, 0, 4, { -253.345596f, 221.393097f, 528.923523f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_47", 2006018, 0, 4, { -152.397003f, 219.002899f, 669.964417f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Decayingwyvern", 2006019, 0, 4, { -152.397003f, 219.634705f, 669.964417f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Decayingwyvern_1", 2006181, 0, 4, { -152.397003f, 219.634705f, 669.964417f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Abandonedeffects", 2005770, 0, 4, { -478.573486f, 162.362106f, 8.634455f }, 0.991760f, -1.383454f); 
    instance.registerEObj( "Abandonedeffects_1", 2005771, 0, 4, { -456.931396f, 171.549103f, 91.921127f }, 0.991760f, 1.132097f); 
    instance.registerEObj( "Abandonedeffects_2", 2005772, 0, 4, { -524.442688f, 165.094299f, 61.538990f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_48", 2006023, 0, 4, { -533.334290f, 118.959702f, -167.634995f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_49", 2006024, 0, 4, { -525.772583f, 118.917099f, -165.737000f }, 0.750000f, -1.085283f); 
    instance.registerEObj( "Wyvernbone", 2006026, 0, 4, { -525.688599f, 119.096603f, -165.728302f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_25", 2006027, 0, 4, { -92.565598f, 96.341217f, -645.083374f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_50", 2006025, 0, 4, { -92.565598f, 96.045303f, -645.083374f }, 0.750000f, 0.000000f); 
    instance.registerEObj( "Destination_26", 2006028, 0, 4, { -92.489616f, 93.528954f, -623.601807f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Wyvernbone_1", 2006460, 0, 4, { -92.565598f, 96.341202f, -645.083374f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SteelagainstSteel );