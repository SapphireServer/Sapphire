#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ToHaveLovedandLost : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_DHIKAI_BOSS = 7941213;
  static constexpr auto BNPC_BLACKHOLE = 7941285;
  static constexpr auto P_BNPC_GRANSON = 7941253;
  static constexpr auto POP_RANGE_CENTER = 7941205;
  static constexpr auto POP_RANGE_NORTH = 7941302;
  static constexpr auto POP_RANGE_NORTHEAST = 7941396;
  static constexpr auto POP_RANGE_SOUTHEAST = 7941397;
  static constexpr auto POP_RANGE_SOUTH = 7941398;
  static constexpr auto POP_RANGE_SOUTHWEST = 7941399;
  static constexpr auto POP_RANGE_NORTHWEST = 7941400;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_01 = 7941466;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_02 = 7941472;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_03 = 7941488;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_04 = 7941489;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_05 = 7941490;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_06 = 7941491;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_07 = 7941492;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_08 = 7941493;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_09 = 7941494;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_10 = 7941495;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_11 = 7941496;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_12 = 7941497;
  static constexpr auto BNPC_BATTLE_FIELD_CENTER = 7944491;
  static constexpr auto BNPC_BATTLE_FIELD_NORTH = 7944480;
  static constexpr auto BNPC_BATTLE_FIELD_EAST = 7944482;
  static constexpr auto BNPC_BATTLE_FIELD_SOUTH = 7944483;
  static constexpr auto BNPC_BATTLE_FIELD_WEST = 7944484;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_A01 = 7944709;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_A02 = 7944710;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_A03 = 7944711;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_A04 = 7944712;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_A05 = 7944713;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_A06 = 7944714;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_B01 = 7944700;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_B02 = 7944701;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_B03 = 7944702;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_B04 = 7944703;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_B05 = 7944704;
  static constexpr auto BNPC_TOUMEI_TOWERGIMMICK_B06 = 7944705;
  static constexpr auto ACTION_TOWER_ATTACK_ACTING = 15548;
  static constexpr auto ACTION_TOWER_ATTACK_SMALL_A01 = 13207;
  static constexpr auto ACTION_TOWER_ATTACK_SMALL_A02 = 13208;
  static constexpr auto ACTION_TOWER_ATTACK_SMALL_A03 = 13209;
  static constexpr auto ACTION_TOWER_ATTACK_SMALL_A04 = 15374;
  static constexpr auto ACTION_TOWER_ATTACK_SMALL_A05 = 15576;
  static constexpr auto ACTION_TOWER_ATTACK_SMALL_A06 = 16612;
  static constexpr auto ACTION_TOWER_ATTACK_LARGE = 16613;
  static constexpr auto ACTION_DHIKAI_RAID_ATTACK_SMALL = 16132;
  static constexpr auto ACTION_DHIKAI_RAID_ATTACK_LARGE = 16133;
  static constexpr auto ACTION_DHIKAI_BLOODWEAPON_ACTING = 16135;
  static constexpr auto ACTION_DHIKAI_SHARE_ATTACK = 16134;
  static constexpr auto ACTION_BLACKHOLE_RESTRAINT = 16167;
  static constexpr auto BNPC_TOUMEI_PC_TARGET = 7994902;
  static constexpr auto BNPC_TOUMEI_NPC_TARGET = 7994928;
  static constexpr auto BNPC_BALL_01 = 7994878;
  static constexpr auto BNPC_BALL_02 = 7994880;
  static constexpr auto BNPC_BALL_03 = 7994881;
  static constexpr auto BNPC_BALL_04 = 7994882;
  static constexpr auto BNPC_BALL_05 = 7994883;
  static constexpr auto BNPC_BALL_06 = 7994884;
  static constexpr auto ACTION_DHIKAI_PBAE = 17427;
  static constexpr auto ACTION_DHIKAI_SUMMON_BALL = 17428;
  static constexpr auto ACTION_DHIKAI_TARGETAE = 17429;
  static constexpr auto BNPC_BALL_07 = 7995395;
  static constexpr auto BNPC_BALL_08 = 7995397;
  static constexpr auto BNPC_BALL_09 = 7995398;
  static constexpr auto BNPC_BALL_10 = 7995399;
  static constexpr auto ACTION_BALL_RAZER = 17432;
  static constexpr auto ACTION_BALL_DONUTS = 17470;
  static constexpr auto ACTION_BALL_CROSS = 17552;
  static constexpr auto BNPC_INV_ACTION_01 = 0;
  static constexpr auto BNPC_INV_ACTION_02 = 0;
  static constexpr auto BNPC_INV_ACTION_03 = 0;
  static constexpr auto BNPC_INV_ACTION_04 = 0;
  static constexpr auto BNPC_INV_ACTION_05 = 0;
  static constexpr auto BNPC_INV_ACTION_06 = 0;
  static constexpr auto ACTION_DHIKAI_CLEAVE = 16131;

public:
  ToHaveLovedandLost() : Sapphire::ScriptAPI::QuestBattleScript( 187 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Nectarfilledflower", 2010536, 0, 4, { -727.145813f, 31.658800f, -132.307205f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Nectarfilledflower_1", 2010536, 0, 4, { -721.540771f, 30.536470f, -124.422699f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Nectarfilledflower_2", 2010536, 0, 4, { -696.460327f, 30.168770f, -119.678902f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Nectarfilledflower_3", 2010536, 0, 4, { -681.451111f, 30.798470f, -129.551498f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Nectarfilledflower_4", 2010536, 0, 4, { -676.338074f, 32.497189f, -145.624496f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_0", 2010678, 0, 4, { -738.937683f, 36.817501f, 284.302002f }, 1.000000f, -1.396145f); 
    instance.registerEObj( "unknown_1", 2010679, 0, 4, { -741.229187f, 36.438221f, 286.532288f }, 1.000000f, -0.143655f); 
    instance.registerEObj( "unknown_2", 2010679, 0, 4, { -741.323730f, 36.933571f, 282.050903f }, 1.000000f, -0.351698f); 
    instance.registerEObj( "unknown_3", 2010680, 0, 4, { -743.779419f, 36.539551f, 284.338013f }, 1.000000f, -1.081677f); 
    instance.registerEObj( "unknown_4", 2010685, 0, 4, { -738.948730f, 36.789429f, 284.290802f }, 0.991760f, -1.396088f); 
    instance.registerEObj( "unknown_5", 2010685, 0, 4, { -741.237488f, 36.423222f, 286.518585f }, 0.991760f, -0.143573f); 
    instance.registerEObj( "unknown_6", 2010685, 0, 4, { -741.329102f, 36.911499f, 282.032501f }, 0.991760f, -0.351623f); 
    instance.registerEObj( "unknown_7", 2010685, 0, 4, { -743.801025f, 36.514771f, 284.321289f }, 0.991760f, -1.081617f); 
    instance.registerEObj( "unknown_8", 2010685, 0, 4, { 115.188400f, 15.411700f, -538.027893f }, 1.000000f, 1.046452f); 
    instance.registerEObj( "unknown_9", 2010685, 0, 4, { 116.060204f, 14.981300f, -536.365417f }, 1.000000f, 0.904978f); 
    instance.registerEObj( "unknown_10", 2010685, 0, 4, { 437.613403f, 88.059692f, -395.040802f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_11", 2010685, 0, 4, { 435.634491f, 87.641243f, -394.785095f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_12", 2010685, 0, 4, { 149.780807f, 32.676800f, -188.752396f }, 0.991760f, -0.691433f); 
    instance.registerEObj( "unknown_13", 2010685, 0, 4, { 147.019699f, 32.581501f, -191.741302f }, 0.991760f, -0.796376f); 
    instance.registerEObj( "unknown_14", 2010685, 0, 4, { 191.241302f, 21.347349f, 6.240906f }, 0.991760f, 0.316149f); 
    instance.registerEObj( "unknown_15", 2010685, 0, 4, { 180.549194f, 21.044399f, 6.075700f }, 0.991760f, -0.354162f); 
    instance.registerEObj( "sgvf_n4d2_b1712", 2007457, 8044619, 4, { 190.632004f, 21.592461f, 4.707202f }, 1.000000f, 0.316149f); 
    instance.registerEObj( "sgvf_n4d2_b1712_1", 2007457, 8044620, 4, { 180.802505f, 21.199570f, 5.112370f }, 1.000000f, -0.354115f); 
    instance.registerEObj( "unknown_16", 2010685, 0, 4, { -668.177307f, 64.164101f, -366.781097f }, 0.991760f, -0.996267f); 
    instance.registerEObj( "unknown_17", 2010685, 0, 4, { -671.534790f, 62.302700f, -356.357513f }, 0.991760f, -1.456833f); 
    instance.registerEObj( "sgvf_n4d2_b1712_2", 2007457, 8044622, 4, { -666.724182f, 64.082840f, -365.870697f }, 1.000000f, -0.996267f); 
    instance.registerEObj( "sgvf_n4d2_b1712_3", 2007457, 8044623, 4, { -669.924072f, 62.323479f, -356.024811f }, 1.000000f, -1.456833f); 
    instance.registerEObj( "unknown_18", 2010685, 0, 4, { -29.954901f, 39.400002f, -562.734070f }, 0.991760f, 0.830040f); 
    instance.registerEObj( "unknown_19", 2010685, 0, 4, { -25.024900f, 37.923901f, -558.303711f }, 0.991760f, 0.759904f); 
    instance.registerEObj( "sgvf_n4d2_b1712_4", 2007457, 8044625, 4, { -31.052120f, 38.223751f, -555.840393f }, 1.000000f, 0.743753f); 
    instance.registerEObj( "sgvf_n4d2_b1712_5", 2007457, 8044626, 4, { -23.458330f, 38.937920f, -565.013123f }, 1.000000f, 0.743677f); 
    instance.registerEObj( "unknown_20", 2010685, 0, 4, { 579.714417f, 109.399597f, -797.350220f }, 0.991760f, 0.995730f); 
    instance.registerEObj( "unknown_21", 2010685, 0, 4, { 581.228821f, 109.417000f, -793.955017f }, 0.991760f, 1.296504f); 
    instance.registerEObj( "sgvf_n4d2_b1712_6", 2007457, 8044627, 4, { 581.932007f, 109.338898f, -791.486694f }, 1.000000f, 1.288324f); 
    instance.registerEObj( "sgvf_n4d2_b1712_7", 2007457, 8044628, 4, { 594.124084f, 109.639702f, -795.677185f }, 1.000000f, 1.176480f); 
    instance.registerEObj( "unknown_22", 2009761, 0, 4, { 641.671814f, 189.030197f, 180.515701f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_23", 2000210, 0, 4, { 622.535583f, 187.814194f, 177.612793f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Summoningstone", 2010636, 0, 4, { -432.086487f, 64.206802f, 549.900879f }, 1.000000f, -0.137042f); 
    instance.registerEObj( "Summoningstone_1", 2010637, 0, 4, { 50.321701f, 101.747299f, -850.605225f }, 1.000000f, -0.137042f); 
    instance.registerEObj( "Summoningstone_2", 2010638, 0, 4, { 351.700714f, 84.165199f, -647.051697f }, 1.000000f, -0.142122f); 
    instance.registerEObj( "Aethercurrent", 2010056, 0, 4, { -231.414093f, 4.701926f, 160.843704f }, 0.991760f, -0.532635f); 
    instance.registerEObj( "Aethercurrent_1", 2010059, 0, 4, { 12.854230f, 110.753304f, -851.246521f }, 0.991760f, -0.532635f); 
    instance.registerEObj( "Aethercurrent_2", 2010062, 0, 4, { 432.480988f, 90.440590f, -770.400085f }, 0.991760f, -0.532635f); 
    instance.registerEObj( "Aethercurrent_3", 2010063, 0, 4, { -8.999450f, 89.309128f, -247.639999f }, 0.991760f, -0.532635f); 
    instance.registerEObj( "unknown_24", 2010851, 0, 4, { -461.539703f, 72.495598f, 586.480530f }, 0.500000f, -0.162221f); 
    instance.registerEObj( "Fleecywool", 2010856, 0, 4, { -271.269104f, 52.991760f, 605.950623f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Fleecywool_1", 2010857, 0, 4, { -261.120789f, 50.977940f, 585.297913f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fleecywool_2", 2010858, 0, 4, { -250.599594f, 50.977940f, 597.745178f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination", 2010859, 0, 4, { -743.841003f, 78.990967f, 457.151215f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Overgrownleafman", 2010860, 0, 4, { -340.381287f, 38.795238f, 434.094788f }, 1.000000f, -1.525505f); 
    instance.registerEObj( "Overgrownleafman_1", 2010861, 0, 4, { -332.434113f, 44.505299f, 462.157715f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Overgrownleafman_2", 2010862, 0, 4, { -276.940186f, 42.906269f, 453.695709f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Overgrownleafman_3", 2010863, 0, 4, { -293.067993f, 42.728271f, 463.644196f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_1", 2010864, 0, 4, { 3.898714f, 13.920520f, 637.257874f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Drownedrelic", 2010865, 0, 4, { -335.590393f, -53.738369f, -277.884186f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Drownedrelic_1", 2010866, 0, 4, { -335.562286f, -54.152550f, -293.406311f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Drownedrelic_2", 2010867, 0, 4, { -351.634308f, -53.616581f, -295.720398f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_2", 2010868, 0, 4, { -504.301910f, 77.244400f, -410.099701f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Minicloudmallow", 2010888, 0, 4, { -171.571899f, 5.262788f, -252.876205f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Minicloudmallow_1", 2010889, 0, 4, { -170.162598f, 4.971029f, -283.022400f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_3", 2010890, 0, 4, { 10.034240f, 32.966148f, -608.591187f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Beauteousblossom", 2010891, 0, 4, { -852.027588f, 37.685101f, 298.138214f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Beauteousblossom_1", 2010892, 0, 4, { -774.427124f, 54.545021f, 102.646599f }, 0.991760f, -0.454017f); 
    instance.registerEObj( "Beauteousblossom_2", 2010893, 0, 4, { -802.273621f, 27.141359f, -108.435799f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_4", 2010894, 0, 4, { 268.529388f, 33.707710f, -78.118851f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Muchbetterthanusualgrass", 2010895, 0, 4, { 718.308777f, 188.072495f, 296.782104f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Muchbetterthanusualgrass_1", 2010896, 0, 4, { 743.572571f, 189.867004f, 260.491791f }, 0.991760f, -0.919108f); 
    instance.registerEObj( "Muchbetterthanusualgrass_2", 2010897, 0, 4, { 769.082520f, 191.628906f, 251.898499f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Unidentifiedfloatingobject", 2010898, 0, 4, { 765.878174f, 187.328003f, 163.551498f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Unidentifiedfloatingobject_1", 2010899, 0, 4, { 783.232605f, 187.328003f, 152.016602f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Unidentifiedfloatingobject_2", 2010900, 0, 4, { 787.948181f, 187.351593f, 174.335693f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shinypebble", 2010901, 0, 4, { -413.956085f, -0.078787f, -55.748260f }, 1.000000f, 0.026921f); 
    instance.registerEObj( "Shinypebble_1", 2010902, 0, 4, { -405.905701f, -0.067648f, -28.368660f }, 1.000000f, -0.980763f); 
    instance.registerEObj( "Shinypebble_2", 2010903, 0, 4, { -395.444702f, -0.062510f, -0.139077f }, 1.000000f, 1.434684f); 
    instance.registerEObj( "Fishtrap", 2010904, 0, 4, { -164.921295f, -50.914650f, 71.154427f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fishtrap_1", 2010910, 0, 4, { -189.865494f, -66.938240f, 13.050570f }, 1.000000f, 0.953362f); 
    instance.registerEObj( "Fishtrap_2", 2010911, 0, 4, { -113.914001f, -36.061062f, 87.713387f }, 0.991760f, 0.081388f); 
    instance.registerEObj( "Destination_5", 2010905, 0, 4, { 164.029694f, 0.300000f, 640.252197f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Marchionesssmarcher", 2010906, 0, 4, { 60.163898f, 5.765929f, 404.372803f }, 1.000000f, 1.413923f); 
    instance.registerEObj( "Marchionesssmarcher_1", 2010907, 0, 4, { 50.883629f, 6.949806f, 406.543488f }, 1.000000f, 1.186502f); 
    instance.registerEObj( "Marchionesssmarcher_2", 2010908, 0, 4, { 42.898602f, 6.691264f, 397.279999f }, 1.000000f, -1.358905f); 
    instance.registerEObj( "Destination_6", 2010909, 0, 4, { -242.080994f, 0.839287f, 223.820999f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_7", 2010786, 0, 4, { 514.974670f, 97.620743f, -256.686310f }, 0.991760f, 0.141655f); 
    instance.registerEObj( "unknown_25", 2010787, 0, 4, { 219.416794f, 30.577560f, -487.628601f }, 1.000000f, 0.775856f); 
    instance.registerEObj( "Voeburtwort", 2010922, 0, 4, { -27.852989f, 30.455700f, -505.365509f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Voeburtwort_1", 2010923, 0, 4, { -53.003899f, 55.971401f, -671.264526f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Destination_8", 2010788, 0, 4, { -480.094604f, 83.451538f, 635.919678f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_9", 2009946, 0, 4, { 395.174988f, 62.088402f, -516.226379f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_26", 2009947, 0, 4, { -68.393303f, 105.294197f, -251.873505f }, 1.000000f, -0.365093f); 
    instance.registerEObj( "Destination_10", 2009948, 0, 4, { -824.864929f, 23.143120f, -56.420990f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_27", 2009949, 0, 4, { -824.864929f, 23.143101f, -56.421001f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Faescrub", 2009816, 0, 4, { -382.788513f, 60.775398f, 530.580872f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Faescrub_1", 2009817, 0, 4, { -417.972198f, 59.730000f, 492.709106f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Faescrub_2", 2009818, 0, 4, { -359.199493f, 46.508751f, 476.792114f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_11", 2009819, 0, 4, { -454.867615f, 80.146347f, 593.488770f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_12", 2009820, 0, 4, { -375.266510f, 76.066597f, 550.462402f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_13", 2009821, 0, 4, { -280.309906f, 56.242950f, 474.089996f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Belltree", 2009822, 0, 4, { -211.100098f, 38.904060f, 356.794495f }, 1.000000f, 1.275184f); 
    instance.registerEObj( "Belltree_1", 2009823, 0, 4, { -260.241699f, 38.996201f, 289.064392f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_14", 2009824, 0, 4, { -59.230000f, 0.483046f, 279.959991f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Leafman", 2009825, 0, 4, { -122.297203f, 17.836260f, 413.229492f }, 0.991760f, 1.535875f); 
    instance.registerEObj( "Leafman_1", 2009826, 0, 4, { -263.145294f, 41.872589f, 469.618195f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_15", 2009827, 0, 4, { -408.601105f, 58.020161f, 408.194885f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2009829, 0, 4, { 135.732498f, 0.000002f, 456.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "UntouchableGate", 2009828, 0, 4, { 133.435898f, 0.000002f, 455.945312f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_28", 2010295, 0, 4, { -516.988220f, 76.053162f, -416.463287f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_29", 2010296, 0, 4, { -213.512802f, 55.055599f, -562.333374f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Flamespores", 2009830, 0, 4, { -111.742699f, 103.134804f, -865.764771f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Flamespores_1", 2009831, 0, 4, { -39.824299f, 116.248901f, -839.266479f }, 1.000000f, -0.906910f); 
    instance.registerEObj( "Flamespores_2", 2009832, 0, 4, { 25.462910f, 100.696899f, -902.300415f }, 1.000000f, -1.000959f); 
    instance.registerEObj( "Flamespores_3", 2009833, 0, 4, { -181.139801f, 84.117401f, -786.190613f }, 0.991760f, 1.444661f); 
    instance.registerEObj( "Invisibleink", 2009834, 0, 4, { 496.763611f, 103.966400f, -116.382797f }, 1.000000f, -0.891381f); 
    instance.registerEObj( "Invisibleink_1", 2009835, 0, 4, { 570.002625f, 119.163902f, -145.689606f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Invisibleink_2", 2009836, 0, 4, { 514.470825f, 122.462502f, -158.261597f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Glitteringobject", 2009837, 0, 4, { -361.950409f, -52.497471f, -302.418610f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Glitteringobject_1", 2009838, 0, 4, { -358.716187f, -33.741631f, -275.944885f }, 1.000000f, 0.931250f); 
    instance.registerEObj( "Glitteringobject_2", 2009839, 0, 4, { -280.557800f, -57.413200f, -264.892487f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_16", 2009840, 0, 4, { -143.300201f, 116.881500f, -274.134888f }, 1.000000f, -1.282487f); 
    instance.registerEObj( "Entrance_1", 2009841, 0, 4, { -140.673401f, 115.271103f, -266.275208f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_30", 2010373, 0, 4, { -563.322815f, 88.748901f, 600.728210f }, 0.991760f, -0.832960f); 
    instance.registerEObj( "unknown_31", 2010669, 0, 4, { -425.859497f, 122.473602f, 729.654114f }, 0.991760f, 0.171118f); 
    instance.registerEObj( "unknown_32", 2010673, 0, 4, { -679.766113f, 132.227097f, 626.309814f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_17", 2009997, 0, 4, { -40.112141f, 24.066351f, 739.273315f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_18", 2010722, 0, 4, { -42.295422f, 24.270451f, 742.273926f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_19", 2010162, 0, 4, { -667.658508f, 42.764542f, -228.626007f }, 0.991760f, -1.396183f); 
    instance.registerEObj( "Destination_20", 2010163, 0, 4, { -659.972412f, 38.869671f, -227.248093f }, 0.991760f, -1.396264f); 
    instance.registerEObj( "Destination_21", 2010164, 0, 4, { -664.014771f, 40.665619f, -225.055801f }, 0.991760f, -1.396264f); 
    instance.registerEObj( "Whirlweed", 2010158, 0, 4, { -347.432007f, -48.244930f, -120.326302f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Whirlweed_1", 2010159, 0, 4, { -341.781097f, -56.987160f, -159.950500f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Whirlweed_2", 2010160, 0, 4, { -456.805511f, -41.144600f, -231.991196f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Whirlweed_3", 2010161, 0, 4, { -341.015503f, -34.609638f, -211.459198f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Antiquecabinet", 2010101, 0, 4, { -649.927979f, 38.240009f, -245.811401f }, 1.000000f, -0.899572f); 
    instance.registerEObj( "unknown_33", 2010677, 0, 4, { -614.923523f, 36.988770f, -243.074005f }, 0.991760f, -1.347156f); 
    instance.registerEObj( "Destination_22", 2010157, 0, 4, { -546.502625f, 48.396358f, 202.582794f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Manorlog", 2010362, 0, 4, { -622.430786f, 37.369259f, -232.349197f }, 0.991760f, -1.357642f); 
    instance.registerEObj( "Timewornchronicle", 2010363, 0, 4, { -621.851013f, 37.361099f, -234.319000f }, 0.991760f, 1.410852f); 
    instance.registerEObj( "Leatherboundtome", 2010364, 0, 4, { -627.731384f, 37.094601f, -245.624603f }, 0.991760f, 0.218452f); 
    instance.registerEObj( "Sappytree", 2010365, 0, 4, { -168.940903f, 27.468750f, 473.136200f }, 1.000000f, 1.017258f); 
    instance.registerEObj( "Sappytree_1", 2010366, 0, 4, { -94.005463f, 19.527769f, 473.223389f }, 0.991760f, -0.534103f); 
    instance.registerEObj( "Sappytree_2", 2010367, 0, 4, { -99.360573f, 18.051390f, 440.288391f }, 0.991760f, 0.858881f); 
    instance.registerEObj( "Vibrantblossom", 2010368, 0, 4, { -356.838501f, 46.677139f, 419.398407f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Vibrantblossom_1", 2010369, 0, 4, { -397.866486f, 51.787380f, 383.513489f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Vibrantblossom_2", 2010370, 0, 4, { -268.171814f, 31.903799f, 344.058685f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_34", 2010371, 0, 4, { -909.336487f, 35.614639f, 300.160400f }, 0.991760f, -0.608594f); 
    instance.registerEObj( "Bagofflowerseeds", 2010184, 0, 4, { -450.583710f, 12.924380f, 27.725590f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bagofflowerseeds_1", 2010185, 0, 4, { -428.426208f, 21.190130f, 207.225601f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bagofflowerseeds_2", 2010186, 0, 4, { -410.977295f, 18.616920f, 209.211502f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bagofflowerseeds_3", 2010187, 0, 4, { -468.462585f, 15.683260f, 8.748155f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bagofflowerseeds_4", 2010188, 0, 4, { -460.189789f, 7.397094f, -21.895210f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bagofflowerseeds_5", 2010189, 0, 4, { -426.755005f, 36.511761f, 331.819397f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_23", 2010102, 0, 4, { 3.708910f, 27.009501f, -507.384613f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_24", 2010216, 0, 4, { -6.105036f, 29.281530f, -512.036316f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_35", 2010471, 0, 4, { 3.739367f, 27.002050f, -507.293091f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Fullblownlily", 2010190, 0, 4, { 63.553829f, -0.152690f, -289.417908f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Fullblownlily_1", 2010191, 0, 4, { 48.538940f, -0.326622f, -283.619385f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Fullblownlily_2", 2010192, 0, 4, { 63.662029f, 0.155382f, -276.155212f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_25", 2010193, 0, 4, { -166.089905f, 2.356314f, -220.146896f }, 0.991760f, -0.123627f); 
    instance.registerEObj( "unknown_36", 2010478, 0, 4, { -165.689301f, 2.397336f, -220.190704f }, 1.000000f, 0.651646f); 
    instance.registerEObj( "unknown_37", 2010748, 0, 4, { -165.464005f, 2.571098f, -220.997101f }, 1.000000f, 0.677636f); 
    instance.registerEObj( "Voeburtwort_2", 2010694, 0, 4, { 103.926102f, 49.403992f, -630.319580f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Voeburtwort_3", 2010695, 0, 4, { 131.765305f, 71.495857f, -662.314575f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Voeburtwort_4", 2010696, 0, 4, { 108.228897f, 15.504890f, -540.125427f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Voeburtwort_5", 2010697, 0, 4, { 137.516403f, 21.705099f, -551.688477f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Blueflower", 2010698, 0, 4, { 54.723549f, 0.211857f, -270.131195f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Yellowflower", 2010699, 0, 4, { 55.252811f, 0.018184f, -282.368195f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Pinkflower", 2010700, 0, 4, { 52.140011f, 0.327765f, -270.405212f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_26", 2010701, 0, 4, { 238.019501f, 25.989349f, -473.128204f }, 0.991760f, 0.000144f); 
    instance.registerEObj( "Amarotracks", 2010481, 0, 4, { 238.750595f, 72.966751f, -723.706177f }, 0.991760f, 0.760435f); 
    instance.registerEObj( "Parteatenfoliage", 2010482, 0, 4, { 156.642807f, 55.593590f, -629.845825f }, 0.991760f, 0.760531f); 
    instance.registerEObj( "Fruitremains", 2010483, 0, 4, { 34.159611f, 39.906590f, -622.178101f }, 0.991760f, 0.760435f); 
    instance.registerEObj( "Destination_27", 2010484, 0, 4, { 204.923492f, 73.510353f, -756.453613f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Pixietreasure", 2010639, 0, 4, { -625.562012f, 49.372791f, 345.349396f }, 0.991760f, 0.781954f); 
    instance.registerEObj( "Pixietreasure_1", 2010640, 0, 4, { -427.006714f, 21.540489f, 216.634796f }, 0.991760f, 0.785110f); 
    instance.registerEObj( "unknown_38", 2010641, 0, 4, { -777.758423f, 47.773369f, 163.429092f }, 0.991760f, 0.068845f); 
    instance.registerEObj( "Buriedobject", 2010715, 0, 4, { -83.990013f, -86.564453f, -55.858479f }, 0.991760f, -0.599771f); 
    instance.registerEObj( "Destination_28", 2010716, 0, 4, { 671.289978f, 107.097900f, -900.857178f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_29", 2010717, 0, 4, { 264.874786f, 27.728930f, -41.932659f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Eggshell", 2010718, 0, 4, { 620.282471f, 109.173698f, -871.102173f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Eggshell_1", 2010719, 0, 4, { 642.779480f, 109.964104f, -827.472290f }, 0.991760f, 0.784345f); 
    instance.registerEObj( "Eggshell_2", 2010720, 0, 4, { 625.503479f, 109.709702f, -824.921875f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Eggshell_3", 2010721, 0, 4, { 600.430115f, 111.295303f, -857.830200f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ToHaveLovedandLost );