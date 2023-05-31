#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheOracleofLight : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto EOBJ_SHARED_CONTROL_A = 7995220;
  static constexpr auto EOBJ_SHARED_CONTROL_B = 7995221;
  static constexpr auto EOBJ_SHARED_CONTROL_C = 7995223;
  static constexpr auto EOBJ_SHARED_CONTROL_D = 7995224;
  static constexpr auto EOBJ_SHARED_CONTROL_E = 7995225;
  static constexpr auto EOBJ_SHARED_CONTROL_BOSS = 7995229;
  static constexpr auto EOBJ_EVENT_ACTION_1 = 8005164;
  static constexpr auto ER_RECT_A = 7995230;
  static constexpr auto ER_RECT_B = 7995231;
  static constexpr auto ER_RECT_C = 7995232;
  static constexpr auto ER_RECT_D = 7995233;
  static constexpr auto ER_RECT_E = 7995234;
  static constexpr auto ER_RECT_F = 7995235;
  static constexpr auto ER_RECT_G = 7995236;
  static constexpr auto ER_RECT_H = 8046907;
  static constexpr auto PR_BOSS_BATTLE_CENTER = 8015736;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_01 = 8015746;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_02 = 8015749;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_03 = 8015756;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_04 = 8015761;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_05 = 8015771;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_06 = 8015772;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_07 = 8015778;
  static constexpr auto PR_BOSS_BATTLE_OUTSIDE_08 = 8015779;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_01 = 8016473;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_02 = 8016475;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_03 = 8016477;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_04 = 8016479;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_05 = 8016480;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_06 = 8016481;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_07 = 8016482;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_08 = 8016484;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_09 = 8016487;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_10 = 8016490;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_11 = 8016506;
  static constexpr auto PR_BOSS_BATTLE_INSIDE_12 = 8016507;
  static constexpr auto PR_LYNA_BATTLE1_01 = 7996369;
  static constexpr auto PR_LYNA_BATTLE1_02 = 7996370;
  static constexpr auto PR_LYNA_BATTLE2_01 = 7996371;
  static constexpr auto PR_LYNA_BATTLE2_02 = 7996373;
  static constexpr auto PR_ALPHINAUD_BATTLE2_01 = 8010020;
  static constexpr auto PR_ALPHINAUD_BATTLE2_02 = 8010021;
  static constexpr auto PR_ALISAIE_BATTLE2_02 = 8010022;
  static constexpr auto PR_ALPHINAUD_BATTLE3_01 = 8010023;
  static constexpr auto PR_ALISAIE_BATTLE3_01 = 8010024;
  static constexpr auto PR_LYNA_BATTLE3_01 = 7996375;
  static constexpr auto PR_LYNA_CASTLE = 7996377;
  static constexpr auto PR_RYNE_CASTLE = 8010025;
  static constexpr auto PR_LYNA_STAIRS_01 = 7996379;
  static constexpr auto PR_LYNA_STAIRS_02 = 8010018;
  static constexpr auto PR_LYNA_STAIRS_03 = 7996380;
  static constexpr auto PR_LYNA_AFTER_LCUT = 7996381;
  static constexpr auto PR_PC_AFTER_LCUT = 8005186;
  static constexpr auto PR_LYNA_BEFORE_BOSS = 7996382;
  static constexpr auto PR_RYNE_BEFORE_BOSS = 8010038;
  static constexpr auto PR_PC_BOSS = 7996383;
  static constexpr auto PR_ALPHINAUD_BOSS = 7996388;
  static constexpr auto PR_ALISAIE_BOSS = 7996391;
  static constexpr auto PR_CARBUNCLE_BOSS = 7996392;
  static constexpr auto PR_LYNA_BOSS = 7996393;
  static constexpr auto PR_RYNE_BOSS = 7996395;
  static constexpr auto PR_BATTLE01_ACTOR_MOVE_ROUTE = 8035430;
  static constexpr auto PR_BATTLE01_ACTOR_MOVE_01 = 8035483;
  static constexpr auto PR_BATTLE01_ACTOR_MOVE_02 = 8035487;
  static constexpr auto PR_BATTLE01_ACTOR_MOVE_03 = 8035488;
  static constexpr auto PR_BATTLE01_ACTOR_MOVE_04 = 8035490;
  static constexpr auto PR_BATTLE_BOSS_CIRCLE_OUTSIDE = 8042740;
  static constexpr auto PR_BATTLE_BOSS_CIRCLE_OUTSIDE2 = 8037590;
  static constexpr auto P_BNPC_LYNA = 7995237;
  static constexpr auto P_BNPC_ALPHINAUD = 7995384;
  static constexpr auto P_BNPC_CARBUNCLE = 7995385;
  static constexpr auto P_BNPC_ALISAIE = 7995386;
  static constexpr auto P_BNPC_RYNE_RESTRAINT = 7995387;
  static constexpr auto P_BNPC_RYNE_FREE = 7995388;
  static constexpr auto BNPC_ENEMY_RANJIT = 7995432;
  static constexpr auto BNPC_ENEMY_RANJIT_PET = 7995433;
  static constexpr auto BNPC_BATTLE1_TRASH_01 = 7996339;
  static constexpr auto BNPC_BATTLE1_TRASH_02 = 7996340;
  static constexpr auto BNPC_BATTLE1_TRASH_03 = 7996341;
  static constexpr auto BNPC_BATTLE2A_TRASH_01 = 7996342;
  static constexpr auto BNPC_BATTLE2B_TRASH_02 = 7996343;
  static constexpr auto BNPC_BATTLE2B_TRASH_03 = 7996344;
  static constexpr auto BNPC_BATTLE2B_TRASH_04 = 7996345;
  static constexpr auto BNPC_BATTLE2B_TRASH_05 = 7996346;
  static constexpr auto BNPC_BATTLE3A_TRASH_01 = 7996348;
  static constexpr auto BNPC_BATTLE3A_TRASH_02 = 7996349;
  static constexpr auto BNPC_BATTLE3A_TRASH_03 = 7996350;
  static constexpr auto BNPC_BATTLE3B_TRASH_01 = 7996352;
  static constexpr auto BNPC_BATTLE3B_TRASH_02 = 7996353;
  static constexpr auto BNPC_BATTLE3B_TRASH_03 = 7996354;
  static constexpr auto BNPC_BATTLE3B_TRASH_04 = 7996355;
  static constexpr auto BNPC_BATTLE3C_TRASH_01 = 7996358;
  static constexpr auto BNPC_BATTLE3C_TRASH_02 = 7996359;
  static constexpr auto BNPC_BATTLE3C_TRASH_03 = 7996360;
  static constexpr auto BNPC_BATTLE3C_TRASH_04 = 7996361;
  static constexpr auto BNPC_BATTLE3C_TRASH_05 = 7996362;
  static constexpr auto BNPC_BATTLE4_TRASH_01 = 7996363;
  static constexpr auto BNPC_BATTLE4_TRASH_02 = 7996364;
  static constexpr auto BNPC_BATTLE5_TRASH_01 = 7996366;
  static constexpr auto BNPC_BATTLE5_TRASH_02 = 7996367;
  static constexpr auto BNPC_ACTOR_BOSS_CRYSTARIUM_01 = 8007080;
  static constexpr auto BNPC_ACTOR_BOSS_CRYSTARIUM_02 = 8007081;
  static constexpr auto BNPC_ACTOR_BOSS_CRYSTARIUM_03 = 8007105;
  static constexpr auto BNPC_TOUMEI_THUNDER_01 = 8014774;
  static constexpr auto BNPC_TOUMEI_THUNDER_02 = 8014775;
  static constexpr auto BNPC_TOUMEI_THUNDER_03 = 8014776;
  static constexpr auto BNPC_TOUMEI_THUNDER_04 = 8014777;
  static constexpr auto BNPC_TOUMEI_THUNDER_05 = 8014778;
  static constexpr auto BNPC_TOUMEI_THUNDER_06 = 8014779;
  static constexpr auto BNPC_TOUMEI_THUNDER_07 = 8014780;
  static constexpr auto BNPC_TOUMEI_THUNDER_08 = 8014781;
  static constexpr auto BNPC_TOUMEI_FLAME_01 = 8014794;
  static constexpr auto BNPC_TOUMEI_FLAME_02 = 8014797;
  static constexpr auto BNPC_TOUMEI_FLAME_03 = 8014798;
  static constexpr auto BNPC_TOUMEI_FLAME_04 = 8014799;
  static constexpr auto BNPC_TOUMEI_FLAME_05 = 8014800;
  static constexpr auto BNPC_ACTOR_01_CRYSTARIUM_01 = 8035443;
  static constexpr auto BNPC_ACTOR_01_CRYSTARIUM_02 = 8035444;
  static constexpr auto BNPC_ACTOR_01_CRYSTARIUM_03 = 8035445;
  static constexpr auto BNPC_ACTOR_01_CRYSTARIUM_04 = 8035446;
  static constexpr auto BNPC_ACTOR_01_EULMORE_01 = 8035474;
  static constexpr auto BNPC_ACTOR_01_EULMORE_02 = 8035475;
  static constexpr auto BNPC_ACTOR_01_EULMORE_03 = 8035476;
  static constexpr auto BNPC_ACTOR_01_EULMORE_04 = 8035477;
  static constexpr auto BNPC_ACTOR_03_CRYSTARIUM_01 = 8035508;
  static constexpr auto BNPC_ACTOR_03_CRYSTARIUM_02 = 8035509;
  static constexpr auto BNPC_ACTOR_03_CRYSTARIUM_03 = 8035510;
  static constexpr auto BNPC_ACTOR_03_CRYSTARIUM_04 = 8035511;
  static constexpr auto BNPC_ACTOR_03_CRYSTARIUM_05 = 8035517;
  static constexpr auto BNPC_ACTOR_03_EULMORE_01 = 8035512;
  static constexpr auto BNPC_ACTOR_03_EULMORE_02 = 8035513;
  static constexpr auto BNPC_ACTOR_03_EULMORE_03 = 8035514;
  static constexpr auto BNPC_ACTOR_03_EULMORE_04 = 8035516;
  static constexpr auto BNPC_ACTOR_03_EULMORE_05 = 8035515;
  static constexpr auto BNPC_FIREBALL_01 = 8037081;
  static constexpr auto BNPC_FIREBALL_02 = 8037082;
  static constexpr auto BNPC_FIREBALL_03 = 8037083;
  static constexpr auto BNPC_FIREBALL_04 = 8037084;
  static constexpr auto BNPC_FIREBALL_05 = 8037086;
  static constexpr auto BNPC_FIREBALL_06 = 8037088;
  static constexpr auto BNPC_FIREBALL_07 = 8037096;
  static constexpr auto BNPC_FIREBALL_08 = 8037097;
  static constexpr auto BNPC_FIREBALL_09 = 8037098;
  static constexpr auto BNPC_FIREBALL_10 = 8037100;
  static constexpr auto BNPC_FIREBALL_11 = 8037101;
  static constexpr auto BNPC_FIREBALL_12 = 8037102;
  static constexpr auto ACTION_RANJIT_THUNDER_RAID = 17618;
  static constexpr auto ACTION_RANJIT_FLAME_GT = 17619;
  static constexpr auto ACTION_RANJIT_MOVE = 17620;

public:
  TheOracleofLight() : Sapphire::ScriptAPI::QuestBattleScript( 185 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2010667, 0, 4, { -650.263123f, 89.952721f, -589.746094f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Fallenlumber", 2010630, 0, 4, { 29.187790f, 1.815447f, 119.038300f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_1", 2010630, 0, 4, { 45.682961f, 0.614276f, 125.505798f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_2", 2010630, 0, 4, { 38.706970f, -0.462432f, 159.405304f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_3", 2010630, 0, 4, { 11.188780f, -0.200020f, 153.740997f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_4", 2010630, 0, 4, { -3.919628f, -0.254497f, 137.386597f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_5", 2010630, 0, 4, { -2.069745f, 1.255232f, 119.223602f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_6", 2010630, 0, 4, { 39.870190f, -0.244128f, 144.377594f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fallenlumber_7", 2010630, 0, 4, { 24.154610f, 4.964979f, 103.976601f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_w_qic_004_04a", 2007457, 7994890, 4, { 263.660614f, 134.599701f, -229.999207f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_1", 2007457, 7995212, 4, { 198.016403f, 134.782806f, -298.512299f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_2", 2007457, 7995213, 4, { 111.253502f, 134.752396f, -335.713715f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_3", 2007457, 7995214, 4, { 43.961182f, 134.813400f, -375.783905f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_4", 2007457, 7995215, 4, { 30.134159f, 134.831406f, -382.535004f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1199", 2007457, 7995219, 4, { 126.726196f, 134.752396f, -311.207794f }, 0.991760f, 0.000048f); 
    // States -> circle_off (id: 3) circle_off (id: 4) circle_on (id: 5) circle_on (id: 6) 
    instance.registerEObj( "Personaleffects", 2010552, 0, 4, { -36.578941f, 162.065994f, -369.704315f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Bindings", 2010553, 0, 4, { -48.187710f, 161.069397f, -371.204712f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_5", 2007457, 7980089, 4, { -198.987701f, 5.761649f, -126.035004f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1199_1", 2008277, 7980246, 4, { -698.476013f, 51.352219f, -233.315308f }, 1.000000f, 0.000000f); 
    // States -> circle_off (id: 3) circle_off (id: 4) circle_on (id: 5) circle_on (id: 6) 
    instance.registerEObj( "sgbg_w_qic_004_04a_6", 2007457, 7980322, 4, { -114.683701f, 5.786800f, -83.483528f }, 1.000000f, 0.863851f); 
    instance.registerEObj( "sgbg_w_qic_004_04a_7", 2007457, 8048139, 4, { -423.913513f, 3.878270f, -159.989700f }, 0.991760f, -0.682104f); 
    instance.registerEObj( "Aethercurrent", 2010024, 0, 4, { 554.280273f, 17.950060f, 352.101807f }, 0.991760f, -0.057811f); 
    instance.registerEObj( "Aethercurrent_1", 2010031, 0, 4, { -149.797897f, 15.281160f, -102.494904f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Aethercurrent_2", 2010032, 0, 4, { -619.637329f, 51.501148f, -199.095596f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Aethercurrent_3", 2010028, 0, 4, { 613.244812f, 24.020069f, -231.128494f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination", 2010361, 0, 4, { 55.623421f, 165.432098f, -302.638306f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PortaltotheSource", 2010609, 0, 4, { 176.763596f, 4.845969f, 60.229481f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2011267, 0, 4, { -607.137817f, 71.999817f, -449.095001f }, 0.991760f, 0.111541f); 
    instance.registerEObj( "unknown_2", 2011157, 0, 4, { -358.632812f, 108.720497f, -685.328491f }, 0.991760f, -0.627032f); 
    instance.registerEObj( "unknown_3", 2011165, 0, 4, { -357.534210f, 109.544403f, -683.894104f }, 0.991760f, 1.367981f); 
    instance.registerEObj( "unknown_4", 2011126, 0, 4, { -357.794189f, 109.550697f, -684.281311f }, 1.000000f, -1.257375f); 
    instance.registerEObj( "Destination_1", 2011067, 0, 4, { -236.764999f, 3.835377f, -115.582100f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_2", 2011068, 0, 4, { -245.265503f, 3.474437f, -116.657600f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_3", 2011069, 0, 4, { -254.101807f, 3.284764f, -114.545502f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_4", 2011177, 0, 4, { -236.112000f, 21.065029f, -223.018906f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_5", 2011178, 0, 4, { -267.506012f, 14.414150f, -191.638000f }, 0.991760f, 1.328852f); 
    instance.registerEObj( "Destination_6", 2011179, 0, 4, { -304.005615f, 19.788031f, -244.159607f }, 0.991760f, 0.733959f); 
    instance.registerEObj( "Barrelofdwarvenfiresand", 2011166, 0, 4, { -721.688110f, 68.871071f, -1.500294f }, 1.000000f, 1.304802f); 
    instance.registerEObj( "Barrelofdwarvenfiresand_1", 2011167, 0, 4, { -724.746399f, 68.847870f, 1.060114f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Waywardautomaton", 2011169, 0, 4, { -95.879372f, 1.640397f, 41.262650f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Waywardautomaton_1", 2011170, 0, 4, { -84.904793f, 2.412439f, 36.863091f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Waywardautomaton_2", 2011171, 0, 4, { -68.533112f, 2.531670f, 38.040939f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Waywardautomaton_3", 2011172, 0, 4, { -70.277122f, 1.455208f, 62.222721f }, 1.000000f, -0.498092f); 
    instance.registerEObj( "unknown_5", 2011168, 0, 4, { -294.640106f, 99.750793f, -724.013489f }, 1.000000f, -0.650133f); 
    instance.registerEObj( "Targetdummy", 2011129, 0, 4, { -126.878799f, 103.209503f, -442.618500f }, 0.991760f, 1.564998f); 
    instance.registerEObj( "Targetdummy_1", 2011130, 0, 4, { -245.751907f, 101.452301f, -433.976105f }, 0.991760f, 0.810221f); 
    instance.registerEObj( "Targetdummy_2", 2011131, 0, 4, { -199.420197f, 100.413002f, -450.797302f }, 0.991760f, 0.009496f); 
    instance.registerEObj( "Targetdummy_3", 2011132, 0, 4, { -145.586395f, 85.374153f, -494.834900f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Targetdummy_4", 2011133, 0, 4, { -193.119705f, 86.076050f, -502.767212f }, 0.991760f, 0.600319f); 
    instance.registerEObj( "unknown_6", 2010838, 0, 4, { 234.228195f, 10.784070f, 738.530273f }, 0.991760f, 0.032760f); 
    instance.registerEObj( "Destination_7", 2009942, 0, 4, { 453.513306f, 13.626220f, 189.440704f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_8", 2009943, 0, 4, { 633.684570f, 21.386801f, -267.913788f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2009998, 0, 4, { 340.666687f, 3.036438f, 208.355194f }, 0.991760f, -0.136263f); 
    instance.registerEObj( "Destination_9", 2010396, 0, 4, { 195.491196f, -0.719326f, 370.954102f }, 0.991760f, 0.088637f); 
    instance.registerEObj( "Destination_10", 2010397, 0, 4, { 203.906296f, -0.534058f, 389.822113f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_8", 2010446, 0, 4, { 195.488007f, -0.708367f, 370.950989f }, 1.480042f, 0.489398f); 
    instance.registerEObj( "Destination_11", 2010215, 0, 4, { 523.992371f, -2.058699f, 795.107117f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_12", 2009924, 0, 4, { 16.933680f, 2.304394f, 669.905212f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2009808, 0, 4, { 695.357422f, 101.314598f, -723.961426f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2010711, 0, 4, { -163.408905f, 6.018582f, -84.885986f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_10", 2010712, 0, 4, { -621.600220f, 56.991909f, -151.212402f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2009815, 0, 4, { -755.651184f, 200.138794f, -293.861786f }, 0.688454f, -1.532403f); 
    instance.registerEObj( "Treatedfodder", 2009814, 0, 4, { -636.147827f, 57.363010f, -137.619797f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_13", 2009861, 0, 4, { 725.409973f, -1.990000f, -93.309998f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_14", 2010512, 0, 4, { 721.812378f, -1.993656f, -92.963120f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Timeworntablet", 2010392, 0, 4, { 697.718811f, -1.260636f, -94.609833f }, 0.991760f, -1.132444f); 
    instance.registerEObj( "Suspectrockformation", 2010137, 0, 4, { -687.800598f, -40.296421f, 729.378174f }, 0.991760f, 1.216693f); 
    instance.registerEObj( "Suspectrockformation_1", 2010138, 0, 4, { -606.455322f, -28.156269f, 768.675415f }, 0.991760f, 0.739583f); 
    instance.registerEObj( "VoyagetotheTempest", 2010140, 0, 4, { -609.691711f, 28.580070f, 819.585876f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Entrance_1", 2010808, 0, 4, { -123.552399f, -0.686768f, 647.699707f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Tenaciousbarnacle", 2010278, 0, 4, { -655.505798f, -40.282761f, 743.235229f }, 0.991760f, -1.224572f); 
    instance.registerEObj( "Tenaciousbarnacle_1", 2010280, 0, 4, { -630.396423f, -29.844629f, 752.560303f }, 0.991760f, -1.440049f); 
    instance.registerEObj( "Tenaciousbarnacle_2", 2010282, 0, 4, { -663.119019f, -25.704630f, 738.851685f }, 0.991760f, -1.247155f); 
    instance.registerEObj( "unknown_12", 2009908, 0, 4, { -692.571106f, -24.888781f, 815.195923f }, 1.000000f, -0.939239f); 
    instance.registerEObj( "Destination_15", 2011074, 0, 4, { 815.609985f, 22.812189f, 26.657471f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_16", 2011075, 0, 4, { 165.209396f, 4.409851f, 708.278015f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_17", 2011076, 0, 4, { 495.475586f, 10.299800f, 290.546997f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_18", 2011077, 0, 4, { 606.119995f, 6.330000f, 739.039978f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_19", 2011078, 0, 4, { 754.469971f, 15.900000f, 273.890015f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_20", 2011079, 0, 4, { 685.595276f, 6.898519f, 497.128113f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2011295, 0, 4, { 652.822021f, 14.544900f, 222.845200f }, 0.991760f, -0.223961f); 
    instance.registerEObj( "unknown_14", 2011296, 0, 4, { 2.607100f, 196.778702f, -300.515686f }, 1.000000f, -0.423127f); 
    instance.registerEObj( "unknown_15", 2011297, 0, 4, { 2.548157f, 195.763199f, -300.404388f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Hollow", 2011298, 0, 4, { 2.568900f, 195.763199f, -300.404114f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Polishedhornnecklace", 2010499, 0, 4, { 655.206177f, 57.736969f, -436.499390f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_21", 2010633, 0, 4, { 597.429688f, 99.599289f, -684.810486f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_22", 2010634, 0, 4, { 577.860107f, 98.697067f, -647.593384f }, 0.991760f, 0.731548f); 
    instance.registerEObj( "Knobblycane", 2010632, 0, 4, { 574.628723f, 97.904243f, -678.517822f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_16", 2010675, 0, 4, { 578.091675f, 97.754753f, -647.389771f }, 0.991760f, 0.776007f); 
    instance.registerEObj( "unknown_17", 2010749, 0, 4, { 597.640015f, 98.210022f, -684.803772f }, 0.991760f, 0.763351f); 
    instance.registerEObj( "Destination_23", 2010613, 0, 4, { -794.711975f, 115.184898f, -310.296814f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_24", 2010618, 0, 4, { -792.098877f, 115.159798f, -346.395294f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_25", 2010619, 0, 4, { -798.266418f, 115.185204f, -320.055206f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_26", 2010620, 0, 4, { -789.052673f, 146.800903f, -344.152496f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pilferedweapons", 2010628, 0, 4, { -677.484314f, 0.143502f, 220.331299f }, 0.991760f, 0.579766f); 
    instance.registerEObj( "unknown_18", 2010629, 0, 4, { -677.729492f, 0.123503f, 220.263901f }, 0.991760f, 0.579806f); 
    instance.registerEObj( "Destination_27", 2010708, 0, 4, { -0.860883f, 157.485397f, -340.690613f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_28", 2010709, 0, 4, { 132.538406f, 157.686203f, -352.261414f }, 0.991760f, -0.988986f); 
    instance.registerEObj( "Destination_29", 2010710, 0, 4, { 39.138882f, 163.656494f, -236.566101f }, 0.991760f, 1.298583f); 
    instance.registerEObj( "Destination_30", 2010681, 0, 4, { 762.919373f, 22.155460f, -168.180801f }, 0.991760f, 0.508115f); 
    instance.registerEObj( "Destination_31", 2010682, 0, 4, { 725.216370f, 22.155451f, -172.985596f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_32", 2010683, 0, 4, { 743.785095f, 22.843060f, -163.167297f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_19", 2010245, 0, 4, { 532.463501f, 4.135132f, -53.391361f }, 0.991760f, 0.220945f); 
    instance.registerEObj( "unknown_20", 2010209, 0, 4, { -506.401215f, 3.420252f, -19.821470f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_33", 2010210, 0, 4, { -370.354004f, 103.410004f, -661.180725f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_21", 2010211, 0, 4, { -447.807404f, 9.717349f, -150.793503f }, 0.991760f, 1.317864f); 
    instance.registerEObj( "Destination_34", 2010212, 0, 4, { -395.858887f, 6.212570f, -51.889042f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_35", 2010213, 0, 4, { -298.107697f, 4.371540f, 16.207621f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Destination_36", 2010510, 0, 4, { -239.951401f, 15.034830f, -196.710495f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Samplingpouch", 2010528, 0, 4, { -439.221985f, -1.127816f, 147.582108f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Walkingstick", 2010526, 0, 4, { -566.731873f, -1.233363f, 214.694702f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Supplylog", 2010527, 0, 4, { -626.092896f, 0.159731f, 243.030396f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Rustedchain", 2010529, 0, 4, { -772.975281f, 70.833641f, 113.681999f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Smallkey", 2010531, 0, 4, { -777.279297f, 70.844963f, 160.051895f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Engravedstone", 2010530, 0, 4, { -757.352112f, 73.800209f, 154.222397f }, 1.000000f, -1.169304f); 
    instance.registerEObj( "unknown_22", 2010686, 0, 4, { -747.615295f, 70.315163f, 104.254898f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pileofrubble", 2010687, 0, 4, { -781.421814f, 71.325348f, 137.509094f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_37", 2010532, 0, 4, { 382.804291f, 27.942860f, 884.647827f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Homelyharpoon", 2010657, 0, 4, { -154.171997f, -95.934624f, 870.207275f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheOracleofLight );