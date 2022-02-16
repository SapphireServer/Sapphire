#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ASeriesofUnfortunateEvents : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_GOAL_POS_01 = 5886177;
  static constexpr auto BNPC_COMPANION_EMMANELLAIN = 5886178;
  static constexpr auto BNPC_COMPANION_HAURCHEFANT = 5886179;
  static constexpr auto BNPC_COMPANION_SOLDIER = 5886180;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_01 = 5886181;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_02 = 5886182;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_03 = 5886191;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_04 = 5886193;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_05 = 5886194;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_06 = 5886196;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_07 = 5886197;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_08 = 5886198;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_09 = 5886200;
  static constexpr auto BNPC_ENEMY_THAUMATURGE_VANUVANU_10 = 5886201;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_11 = 5886207;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_12 = 5886208;
  static constexpr auto BNPC_ENEMY_THAUMATURGE_VANUVANU_13 = 5886209;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_14 = 5886211;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_15 = 5886212;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_16 = 5886213;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_17 = 5886214;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_18 = 5886217;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_19 = 5886218;
  static constexpr auto BNPC_ENEMY_THAUMATURGE_VANUVANU_20 = 5886219;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_21 = 5891945;
  static constexpr auto BNPC_ENEMY_PUGILIST_VANUVANU_22 = 5891946;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_23 = 5891947;
  static constexpr auto BNPC_ENEMY_ROGUE_VANUVANU_24 = 5891948;
  static constexpr auto ENPC_GOAL_SOLDIER = 5886176;
  static constexpr auto ENPC_ELDER_VANUVANU = 5886237;
  static constexpr auto POPRANGE_HAURCHEFANT_MOVE_POS_01 = 5886220;
  static constexpr auto POPRANGE_SOLDIER_MOVE_POS_01 = 5886221;
  static constexpr auto ERANGE_VANUVANU_TERRITORY_01 = 5886222;
  static constexpr auto EOBJ_ARREST_01 = 5886226;
  static constexpr auto QIB_YELL_01 = 2647;
  static constexpr auto QIB_YELL_02 = 2692;
  static constexpr auto QIB_YELL_03 = 2693;
  static constexpr auto QIB_YELL_04 = 2695;
  static constexpr auto QIB_YELL_05 = 2696;
  static constexpr auto QIB_YELL_06 = 2697;
  static constexpr auto EVENT_ACTION_ARREST = 42;
  static constexpr auto CUT_SCENE_N_01 = 794;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto BGM_LATE_BATTLE = 39;
  static constexpr auto BEHAVIOR_EMMANELLAIN_RELEASED = 30600;
  static constexpr auto BNPC_WAY_STOP = 5904722;
  static constexpr auto BNPC_STATE_CAUGHT = 118;
  static constexpr auto BNPC_STATE_NORMAL = 0;
  static constexpr auto LOC_POS_ACTOR0 = 5908313;
  static constexpr auto LOC_POS_ACTOR1 = 5908314;
  static constexpr auto LOC_POS_ACTOR2 = 5908315;
  static constexpr auto LOC_ACTOR0 = 1012438;
  static constexpr auto LOC_ACTOR1 = 1012472;
  static constexpr auto LOC_ACTOR2 = 1012471;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_CAUTION = 4227;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_KNEE_SEACH = 1014;

public:
  ASeriesofUnfortunateEvents() : Sapphire::ScriptAPI::QuestBattleScript( 104 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Springcore", 2006356, 0, 5935427, 4, { -503.756012f, -58.509480f, -503.033691f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Springcore_1", 2006356, 0, 5935428, 4, { -499.300415f, -58.214001f, -463.584412f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Springcore_2", 2006356, 0, 5935429, 4, { -512.484192f, -56.971661f, -479.306091f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Springcore_3", 2006356, 0, 5935430, 4, { -476.787994f, -58.587841f, -514.616882f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Springcore_4", 2006356, 0, 5935431, 4, { -480.780212f, -57.274231f, -496.720612f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Springcore_5", 2006356, 0, 5935432, 4, { -469.194702f, -57.906929f, -495.066803f }, 1.000000f, 0.008036f, 0); 
    instance.addEObj( "Springcore_6", 2006356, 0, 5935433, 4, { -494.337402f, -57.733509f, -482.052185f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Springcore_7", 2006356, 0, 5935434, 4, { -478.165985f, -58.167671f, -472.125214f }, 1.000000f, 0.008036f, 0); 
    instance.addEObj( "Brambleweedrope", 2005710, 0, 5886226, 4, { 654.976929f, -65.052856f, -128.584305f }, 1.000000f, -0.158530f, 0); 
    instance.addEObj( "Entrance", 2005517, 0, 5861483, 4, { -151.981705f, -14.711070f, -538.561279f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance_1", 2006308, 0, 5921843, 4, { 363.927795f, 134.083405f, 247.741898f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_2", 2006375, 0, 5937939, 4, { 880.675110f, -97.850777f, -743.209229f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Summoningstone", 2005695, 0, 5881756, 4, { -621.500000f, -58.500000f, -319.399994f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "AirshiptoIshgard", 2005370, 0, 5916122, 4, { -812.001282f, -57.849281f, 162.789505f }, 0.991760f, -1.317327f, 0); 
    instance.addEObj( "Aethercurrent", 2006225, 0, 5916002, 4, { -595.001404f, -166.226303f, 582.444214f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_1", 2006226, 0, 5916005, 4, { 484.737091f, -142.446198f, 689.117920f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_2", 2006227, 0, 5916022, 4, { -505.576508f, -217.550903f, 329.869293f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_3", 2006228, 0, 5916030, 4, { 157.968094f, -177.265594f, 785.124023f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_4", 2006229, 0, 5916032, 4, { -631.148071f, -59.062820f, -159.611298f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_5", 2006230, 0, 5916037, 4, { 180.448303f, 30.010010f, -471.095093f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_6", 2006231, 0, 5916039, 4, { 486.183105f, 113.107101f, -185.697006f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_7", 2006232, 0, 5916043, 4, { 64.102600f, 150.498993f, -139.863495f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_8", 2006233, 0, 5916044, 4, { 231.301407f, -82.111038f, 261.017792f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_9", 2006234, 0, 5916045, 4, { 616.022888f, -65.536537f, -111.587196f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005409, 0, 5857517, 4, { -254.657806f, -185.675507f, 662.684082f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2005410, 0, 5857520, 4, { -81.154419f, -136.979996f, 468.536591f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2005411, 0, 5857522, 4, { -122.764702f, -165.979996f, 646.509521f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Springcrystal", 2005412, 0, 5857545, 4, { 408.895905f, -124.000000f, 718.562500f }, 0.991760f, -0.074735f, 0); 
    instance.addEObj( "Springcrystal_1", 2005413, 0, 5857553, 4, { 208.222595f, -124.000000f, 632.809814f }, 0.991760f, -1.356326f, 0); 
    instance.addEObj( "Springcrystal_2", 2005414, 0, 5857719, 4, { 334.798096f, -124.000000f, 751.346985f }, 0.991760f, -0.060929f, 0); 
    instance.addEObj( "Springcrystal_3", 2005415, 0, 5857721, 4, { 216.934006f, -124.000000f, 611.786072f }, 0.991760f, -0.789964f, 0); 
    instance.addEObj( "Springcrystal_4", 2005416, 0, 5857722, 4, { 326.497192f, -123.500000f, 564.446411f }, 0.991760f, -0.100717f, 0); 
    instance.addEObj( "Springcrystal_5", 2005417, 0, 5857723, 4, { 398.367188f, -124.000000f, 584.375977f }, 0.991760f, 1.357258f, 0); 
    instance.addEObj( "Springcrystal_6", 2005492, 0, 5857953, 4, { 270.801788f, -124.000000f, 725.520630f }, 0.991760f, -1.460420f, 0); 
    instance.addEObj( "Destination_3", 2005418, 0, 5857954, 4, { 418.429901f, -121.445297f, 630.648376f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_4", 2005419, 0, 5857955, 4, { 299.825409f, -115.810898f, 424.747192f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_0", 2005420, 0, 5857994, 4, { 531.181580f, -99.870361f, 349.965607f }, 0.700000f, -0.455839f, 0); 
    instance.addEObj( "unknown_1", 2005493, 0, 5858080, 4, { -678.950195f, -109.697098f, 463.157013f }, 0.991760f, 1.486976f, 0); 
    instance.addEObj( "Destination_5", 2005497, 0, 5858719, 4, { -703.861328f, -62.007809f, 113.504204f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_6", 2005500, 0, 5912435, 4, { -761.806702f, -39.109440f, 77.622681f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "Destination_7", 2005501, 0, 5912436, 4, { -761.806702f, -39.109402f, 77.622704f }, 1.000000f, 0.000047f, 0); 
    instance.addEObj( "Vunduaetheryte", 2006288, 0, 5921844, 4, { 369.562103f, 143.181702f, 260.719086f }, 1.000000f, -1.165264f, 0); 
    instance.addEObj( "×エンタープライズ2", 2006411, 0, 5938130, 4, { -818.035889f, -57.642361f, 151.719193f }, 1.000000f, 0.525521f, 0); 
    instance.addEObj( "unknown_2", 2006361, 0, 5932883, 4, { -447.867615f, -4.226807f, -703.730774f }, 0.991760f, -1.469720f, 0); 
    instance.addEObj( "unknown_3", 2006366, 0, 5935261, 4, { -179.437195f, 19.436171f, -855.977722f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Exit", 2006413, 0, 5939318, 4, { -448.501007f, -3.653519f, -710.402710f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_8", 2006342, 0, 5930944, 4, { 533.531677f, -100.114502f, 367.544098f }, 0.991760f, 0.632537f, 0); 
    instance.addEObj( "Lockedbasket", 2006274, 0, 5921163, 4, { 305.073608f, 71.063919f, -413.412689f }, 0.991760f, 0.093047f, 0); 
    instance.addEObj( "Lockedbasket_1", 2006275, 0, 5921164, 4, { 384.054199f, 71.411461f, -311.909698f }, 0.991760f, -0.149134f, 0); 
    instance.addEObj( "unknown_4", 2006379, 0, 5937776, 4, { 305.073608f, 70.664551f, -413.443207f }, 0.991760f, -0.670162f, 0); 
    instance.addEObj( "unknown_5", 2006380, 0, 5937778, 4, { 384.060913f, 70.956978f, -311.882385f }, 0.991760f, -0.434402f, 0); 
    instance.addEObj( "×", 2006452, 0, 5960937, 4, { 304.926910f, 70.665611f, -413.570312f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "×_1", 2006453, 0, 5960945, 4, { 383.787811f, 70.938828f, -311.500092f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005987, 0, 5900345, 4, { -44.083370f, -176.806305f, 753.291992f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2005988, 0, 5900346, 4, { 98.863159f, -175.280396f, 780.758301f }, 2.000000f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2005989, 0, 5900347, 4, { 207.493607f, -176.705399f, 720.764221f }, 1.998901f, 0.000048f, 0); 
    instance.addEObj( "×エンタープライズ", 2005495, 0, 5859576, 4, { -815.343079f, -57.546211f, 153.558701f }, 1.000000f, 0.544800f, 0); 
    instance.addEObj( "unknown_9", 2005625, 0, 5883652, 4, { -151.302307f, -14.708430f, -529.897095f }, 0.991760f, -1.432712f, 0); 
    instance.addEObj( "unknown_10", 2005585, 0, 5877118, 4, { -248.982605f, -182.409195f, 744.884521f }, 1.000000f, 1.540455f, 0); 
    instance.addEObj( "Packedmeal", 2005584, 0, 5877119, 4, { -249.044800f, -182.342606f, 744.852478f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmushroom", 2006000, 0, 5901886, 4, { -181.020493f, -165.176804f, 536.618774f }, 2.000000f, 1.377967f, 0); 
    instance.addEObj( "Gnawedbone", 2006001, 0, 5901925, 4, { -131.252304f, -137.676498f, 512.280823f }, 2.000000f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2006002, 0, 5901960, 4, { -709.681885f, -105.180496f, 448.386200f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2006003, 0, 5901961, 4, { -709.681824f, -105.165497f, 448.412811f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Provisions", 2006004, 0, 5901962, 4, { -709.681824f, -104.727798f, 448.412811f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "RoseKnightweapons", 2005588, 0, 5877121, 4, { 710.219299f, -65.536522f, -120.625198f }, 1.250000f, 0.969732f, 0); 
    instance.addEObj( "RoseKnightweapons_1", 2005589, 0, 5877123, 4, { 643.904419f, -65.536522f, -126.372498f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "RoseKnightarmor", 2005590, 0, 5877126, 4, { 687.856689f, -65.536522f, -162.828400f }, 1.500000f, -0.724929f, 0); 
    instance.addEObj( "unknown_13", 2005773, 0, 5888247, 4, { 113.908600f, -85.587891f, 443.717010f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Blackloam", 2005774, 0, 5888252, 4, { -21.168360f, -175.254898f, 737.757324f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Blackloam_1", 2005775, 0, 5888253, 4, { 55.786098f, -175.254898f, 723.008789f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Blackloam_2", 2005776, 0, 5888254, 4, { 36.870640f, -175.254898f, 774.079895f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Blackloam_3", 2005777, 0, 5888256, 4, { 1.261036f, -175.254898f, 705.787415f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Blackloam_4", 2005778, 0, 5888258, 4, { 95.929237f, -175.254898f, 769.107971f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2005780, 0, 5888261, 4, { -143.817795f, -176.801193f, 743.886597f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2005781, 0, 5888262, 4, { -115.285500f, -176.801102f, 741.692993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2005782, 0, 5888263, 4, { -101.519997f, -176.801193f, 755.577515f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_17", 2005783, 0, 5888264, 4, { -109.223198f, -176.806305f, 771.924316f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_18", 2005784, 0, 5888266, 4, { -129.711807f, -176.801102f, 773.815186f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gastornisnest", 2005779, 0, 5888273, 4, { -101.519997f, -175.848602f, 755.577515f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gastornisnest_1", 2006445, 0, 5960887, 4, { -143.817795f, -175.830704f, 743.886597f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gastornisnest_2", 2006446, 0, 5960888, 4, { -115.285500f, -175.832001f, 741.692993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gastornisnest_3", 2006447, 0, 5960889, 4, { -109.223198f, -175.848907f, 771.924316f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gastornisnest_4", 2006448, 0, 5960890, 4, { -129.711807f, -175.832901f, 773.815186f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_9", 2006255, 0, 5927107, 4, { -586.130981f, -165.927094f, 607.534912f }, 1.000000f, -1.389183f, 0); 
    instance.addEObj( "unknown_19", 2006256, 0, 5927108, 4, { -586.130981f, -165.927094f, 607.534912f }, 1.000000f, -1.389183f, 0); 
    instance.addEObj( "Gurglegrass", 2005824, 0, 5890519, 4, { 204.853897f, 12.762570f, -596.195679f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gurglegrass_1", 2005825, 0, 5890520, 4, { 244.353607f, 38.357929f, -564.352722f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gurglegrass_2", 2005826, 0, 5890521, 4, { 224.959595f, 12.879210f, -653.325623f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_10", 2006033, 0, 5905827, 4, { -275.213593f, -14.240420f, -690.286926f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005830, 0, 5890524, 4, { -569.233887f, -50.650410f, -449.845490f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Zunduoffering", 2005827, 0, 5890527, 4, { 86.063919f, 98.585579f, -335.142914f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Zunduoffering_1", 2005828, 0, 5890528, 4, { 180.820496f, 98.585579f, -309.500610f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Zunduoffering_2", 2005829, 0, 5890529, 4, { 80.252533f, 98.585579f, -309.043793f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2005831, 0, 5890587, 4, { -238.233795f, 103.114799f, -241.734100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut", 2006109, 0, 5910999, 4, { 685.164673f, -98.847237f, -675.329285f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Kuponut_1", 2006110, 0, 5911000, 4, { 734.973389f, -98.140648f, -684.319214f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Kuponut_2", 2006111, 0, 5911001, 4, { 778.835815f, -98.576317f, -669.549622f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Kuponut_3", 2006112, 0, 5911002, 4, { 835.825073f, -97.819618f, -685.877075f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut_4", 2006113, 0, 5911092, 4, { 784.129272f, -11.396840f, -419.154907f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackfeather", 2006114, 0, 5911093, 4, { 749.614807f, -11.396870f, -349.976715f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackfeather_1", 2006115, 0, 5911094, 4, { 715.360779f, -11.396840f, -397.289001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2006116, 0, 5911102, 4, { 650.836487f, -136.622803f, 655.090576f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2006117, 0, 5911103, 4, { 650.505981f, -136.621399f, 654.912170f }, 1.500000f, -0.955060f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ASeriesofUnfortunateEvents );