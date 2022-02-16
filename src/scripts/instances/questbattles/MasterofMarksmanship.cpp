#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class MasterofMarksmanship : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_ROSTNSTHAL_01 = 5895579;
  static constexpr auto BNPC_JOYE_01 = 5895580;
  static constexpr auto BNPC_ROSTNSTHAL_02 = 5895760;
  static constexpr auto BNPC_01_CONDOR_01 = 5895588;
  static constexpr auto BNPC_01_CONDOR_02 = 5895590;
  static constexpr auto BNPC_01_CONDOR_03 = 5895592;
  static constexpr auto BNPC_01_CONDOR_04 = 5895593;
  static constexpr auto BNPC_01_CONDOR_05 = 5895594;
  static constexpr auto BNPC_01_CONDOR_06 = 5895595;
  static constexpr auto BNPC_01_CONDOR_07 = 5895596;
  static constexpr auto BNPC_01_CONDOR_08 = 5895598;
  static constexpr auto BNPC_01_COEURL_01 = 5895601;
  static constexpr auto BNPC_01_COEURL_02 = 5895602;
  static constexpr auto BNPC_01_COEURL_03 = 5895603;
  static constexpr auto BNPC_01_COEURL_04 = 5895604;
  static constexpr auto BNPC_01_COEURL_05 = 5895634;
  static constexpr auto BNPC_01_COEURL_06 = 5895635;
  static constexpr auto BNPC_01_COEURL_07 = 5895636;
  static constexpr auto BNPC_01_RINGTAIL_01 = 5895606;
  static constexpr auto BNPC_01_RINGTAIL_02 = 5895607;
  static constexpr auto BNPC_01_RINGTAIL_03 = 5895608;
  static constexpr auto BNPC_01_RINGTAIL_04 = 5895609;
  static constexpr auto BNPC_01_RINGTAIL_05 = 5895610;
  static constexpr auto BNPC_01_RINGTAIL_06 = 5895612;
  static constexpr auto BNPC_01_RINGTAIL_07 = 5895613;
  static constexpr auto BNPC_01_RINGTAIL_08 = 5895614;
  static constexpr auto BNPC_01_SPRITE_01 = 5895615;
  static constexpr auto BNPC_01_SPRITE_02 = 5895616;
  static constexpr auto BNPC_01_SPRITE_03 = 5895618;
  static constexpr auto BNPC_01_SPRITE_04 = 5895619;
  static constexpr auto BNPC_01_SPRITE_05 = 5895620;
  static constexpr auto BNPC_01_SPRITE_06 = 5895623;
  static constexpr auto BNPC_01_SPRITE_07 = 5895624;
  static constexpr auto BNPC_01_SPRITE_08 = 5895625;
  static constexpr auto BNPC_01_GOLEM_01 = 5895626;
  static constexpr auto BNPC_01_GOLEM_02 = 5895627;
  static constexpr auto BNPC_01_GOLEM_03 = 5895628;
  static constexpr auto BNPC_01_GOLEM_04 = 5895629;
  static constexpr auto BNPC_01_GOLEM_05 = 5895630;
  static constexpr auto BNPC_01_GOLEM_06 = 5895631;
  static constexpr auto BNPC_01_GOLEM_07 = 5895632;
  static constexpr auto BNPC_02_BOMB_01 = 5895642;
  static constexpr auto BNPC_02_BOMB_02 = 5895646;
  static constexpr auto BNPC_02_BOMB_03 = 5895648;
  static constexpr auto BNPC_03_WEASEL_01 = 5895752;
  static constexpr auto BNPC_03_WEASEL_02 = 5895755;
  static constexpr auto BNPC_03_TIGER_01 = 5895753;
  static constexpr auto BNPC_03_TIGER_02 = 5895756;
  static constexpr auto MOVING_POINT_01 = 5895586;
  static constexpr auto MOVING_POINT_02 = 5895757;
  static constexpr auto ER_RECT_01 = 5895759;
  static constexpr auto WARP_PC_POINT_01 = 5895762;
  static constexpr auto MOVING_POINT_JOYE_01 = 5908268;
  static constexpr auto BNPC_TYPE_01_GOLEM = 4287;
  static constexpr auto BNPC_TYPE_02_BOMB = 4291;
  static constexpr auto BNPC_TYPE_03_WEASEL = 4294;
  static constexpr auto BNPC_TYPE_03_TIGER = 4295;
  static constexpr auto ENPC_STEPHANIVIEN_01 = 5899500;
  static constexpr auto ENPC_JOYE_01 = 5899501;
  static constexpr auto BEHAVIOR_ROSTNSTHAL_01 = 30601;
  static constexpr auto BEHAVIOR_JOYE_01 = 30602;
  static constexpr auto BEHAVIOR_JOYE_02 = 30603;
  static constexpr auto BEHAVIOR_JOYE_03 = 30604;
  static constexpr auto BEHAVIOR_JOYE_04 = 30605;
  static constexpr auto QIB_YELL_01 = 2723;
  static constexpr auto QIB_YELL_02 = 2724;
  static constexpr auto QIB_YELL_03 = 2725;
  static constexpr auto QIB_YELL_04 = 2726;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto ACTION_HEART_SHOT = 2875;
  static constexpr auto BGM_BOSS_BATTLE = 39;
  static constexpr auto LOC_MARKER_01 = 5923224;
  static constexpr auto LOC_ACTOR0 = 1014580;
  static constexpr auto LOC_ACTOR1 = 1015124;
  static constexpr auto LOC_ACTOR2 = 1014579;

public:
  MasterofMarksmanship() : Sapphire::ScriptAPI::QuestBattleScript( 127 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Wildchocobofeather", 2006422, 0, 5941686, 4, { 516.932922f, -44.187210f, -98.982674f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildchocobofeather_1", 2006422, 0, 5941687, 4, { 472.726501f, -45.171822f, -112.890099f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildchocobofeather_2", 2006422, 0, 5941688, 4, { 477.643311f, -45.755428f, -126.500702f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildchocobofeather_3", 2006422, 0, 5941689, 4, { 510.077789f, -45.101700f, -120.259598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildchocobofeather_4", 2006422, 0, 5941690, 4, { 488.586792f, -38.384258f, -101.526398f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildchocobofeather_5", 2006422, 0, 5941691, 4, { 488.555695f, -45.958611f, -149.020706f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildchocobofeather_6", 2006422, 0, 5941692, 4, { 517.363586f, -43.852039f, -132.255005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sylviel", 2005765, 0, 5886231, 4, { 287.891998f, -94.590698f, 606.653015f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2006309, 0, 5921850, 4, { 258.169189f, -112.938103f, 924.143127f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Summoningstone", 2005696, 0, 5881743, 4, { -209.348602f, -35.408501f, 162.933701f }, 1.000000f, 1.160675f, 0); 
    instance.addEObj( "Aethercurrent", 2006195, 0, 5915503, 4, { 765.023804f, -15.794190f, 289.109985f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_1", 2006196, 0, 5915514, 4, { 384.908600f, -41.682480f, 74.280647f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_2", 2006197, 0, 5915515, 4, { 707.739990f, -41.098549f, -14.556910f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_3", 2006198, 0, 5915520, 4, { 208.020004f, -36.530590f, 3.510000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_4", 2006199, 0, 5915554, 4, { 256.851013f, -104.575600f, 834.320984f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_5", 2006200, 0, 5915555, 4, { -143.666107f, -83.664749f, 611.140076f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_6", 2006201, 0, 5915557, 4, { 18.673340f, -25.857100f, -103.856598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_7", 2006202, 0, 5915563, 4, { -487.920105f, 223.904205f, -135.417007f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_8", 2006203, 0, 5915571, 4, { -662.596802f, -102.896400f, 680.746582f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_9", 2006204, 0, 5915573, 4, { 167.248901f, -4.219567f, -479.438995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2005436, 0, 5856230, 4, { 634.515930f, -40.054932f, -295.094208f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_1", 2005437, 0, 5856231, 4, { 234.424301f, -56.626282f, -259.144012f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination", 2005489, 0, 5856306, 4, { 169.604507f, -63.221840f, -11.797100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2005440, 0, 5856256, 4, { -245.075195f, -84.550232f, 450.919312f }, 0.991760f, -0.000432f, 0); 
    instance.addEObj( "unknown_3", 2005441, 0, 5856257, 4, { -282.734497f, -63.645390f, 335.866211f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "�未使用", 2005442, 0, 5856604, 4, { 480.330505f, -51.141399f, 29.976990f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2005443, 0, 5856628, 4, { 262.836700f, -97.215271f, 614.343384f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2005444, 0, 5856629, 4, { 190.531998f, -118.362396f, 567.849182f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2006423, 0, 5941705, 4, { 394.380707f, -93.953697f, 731.830078f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sacrificialchamberentrance", 2005446, 0, 5857218, 4, { -9.079163f, -127.702797f, 734.004578f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2005448, 0, 5857899, 4, { -688.380188f, 4.898132f, -794.857727f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance_1", 2005449, 0, 5857900, 4, { -710.902588f, 8.865417f, -817.990417f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gnathicaetheryte", 2006289, 0, 5921851, 4, { 257.777802f, -111.917900f, 925.410583f }, 1.000000f, 0.294291f, 0); 
    instance.addEObj( "unknown_6", 2006418, 0, 5940583, 4, { 728.111389f, -49.955700f, 34.930500f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Destination_3", 2006419, 0, 5940584, 4, { 610.290405f, 2.980188f, -488.439301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2006371, 0, 5935793, 4, { 731.599426f, -40.967651f, -27.382580f }, 1.000000f, 1.331372f, 0); 
    instance.addEObj( "unknown_8", 2006365, 0, 5933556, 4, { 218.432907f, -104.753197f, 592.004211f }, 0.991760f, -0.932818f, 0); 
    instance.addEObj( "Gronahlm", 2006344, 0, 5931052, 4, { -557.799072f, -92.219543f, 595.180908f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_9", 2006345, 0, 5931053, 4, { -557.763123f, -92.118767f, 595.056030f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2005936, 0, 5895657, 4, { 229.313705f, -56.830971f, -245.088303f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2005937, 0, 5895658, 4, { 229.480804f, -56.887650f, -247.526901f }, 1.000000f, 0.875572f, 0); 
    instance.addEObj( "Destination_4", 2005938, 0, 5895663, 4, { 163.289993f, -64.230003f, -102.879997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2005939, 0, 5895664, 4, { 237.623703f, -54.039879f, -216.999405f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Mysteriousbox", 2005986, 0, 5900315, 4, { 507.869995f, -21.900000f, -524.409973f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2006096, 0, 5908628, 4, { 507.869995f, -21.888580f, -524.409973f }, 0.500000f, -1.570451f, 0); 
    instance.addEObj( "Whilomsalmon", 2005574, 0, 5871822, 4, { 447.096893f, -47.693359f, -283.663208f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_13", 2005575, 0, 5871824, 4, { 303.262512f, -39.067390f, -351.145813f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2005576, 0, 5871825, 4, { 291.912903f, -34.329288f, -402.159607f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2005573, 0, 5871826, 4, { 441.970001f, -21.520000f, -545.030029f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Foultaint", 2005859, 0, 5890199, 4, { -561.804626f, -46.684330f, 300.491913f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2005860, 0, 5890200, 4, { -561.820312f, -46.699799f, 300.461914f }, 1.700000f, 0.000048f, 0); 
    instance.addEObj( "Foultaint_1", 2005861, 0, 5890212, 4, { -678.370422f, -100.572304f, 778.133728f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_16", 2005862, 0, 5890214, 4, { -678.370422f, -100.602798f, 777.462280f }, 1.693726f, 0.000048f, 0); 
    instance.addEObj( "unknown_17", 2005863, 0, 5890309, 4, { -122.399498f, 0.718000f, -615.806030f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2005595, 0, 5877224, 4, { 671.460815f, -54.068909f, 66.306671f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Chocobosnare", 2005593, 0, 5877225, 4, { 671.405212f, -53.811642f, 66.355766f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005596, 0, 5877227, 4, { 441.898102f, -43.531910f, -189.219696f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Chocobosnare_1", 2005594, 0, 5877228, 4, { 441.933289f, -43.276440f, -189.211502f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005598, 0, 5877230, 4, { 645.507385f, -46.717941f, -119.879501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Chocobonest", 2005597, 0, 5877231, 4, { 645.498474f, -46.417881f, -119.742897f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Chandlerswick", 2006127, 0, 5911376, 4, { 871.893188f, -20.589050f, 193.615997f }, 2.500000f, 0.603846f, 0); 
    instance.addEObj( "Chandlerswick_1", 2006128, 0, 5911378, 4, { 872.651794f, -16.411329f, 216.772293f }, 2.500000f, -1.032810f, 0); 
    instance.addEObj( "Chandlerswick_2", 2006129, 0, 5911379, 4, { 841.119507f, -5.216516f, 216.280701f }, 2.500000f, 1.351055f, 0); 
    instance.addEObj( "Chandlerswick_3", 2006456, 0, 5961683, 4, { 832.490417f, -7.366076f, 222.718597f }, 2.500000f, 1.453138f, 0); 
    instance.addEObj( "Chandlerswick_4", 2006457, 0, 5961684, 4, { 870.413696f, -4.702106f, 216.245895f }, 3.000000f, -0.796728f, 0); 
    instance.addEObj( "Destination_7", 2006130, 0, 5911448, 4, { 378.766388f, -42.534740f, -373.084015f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2006131, 0, 5911449, 4, { 378.766388f, -42.534698f, -373.084015f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_8", 2006132, 0, 5911457, 4, { 312.808807f, -47.151348f, -256.267914f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_9", 2006133, 0, 5911458, 4, { 360.049500f, -44.426041f, -284.003204f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_10", 2006134, 0, 5911460, 4, { 319.137604f, -48.184250f, -318.072815f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2006135, 0, 5911461, 4, { 312.808807f, -47.151402f, -256.267914f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2006136, 0, 5911462, 4, { 360.049500f, -44.425999f, -284.003204f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2006137, 0, 5911463, 4, { 319.137604f, -48.184299f, -318.072815f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2006138, 0, 5911465, 4, { 833.283386f, -22.196520f, 212.935806f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Lampshade", 2005599, 0, 5877233, 4, { 577.659790f, -34.492710f, 492.738312f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "unknown_26", 2005601, 0, 5877240, 4, { 441.898102f, -43.531898f, -189.219696f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Destination_11", 2005600, 0, 5877241, 4, { 441.933289f, -43.276402f, -189.211502f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_27", 2005602, 0, 5877242, 4, { 441.941193f, -43.259651f, -189.154205f }, 1.000000f, -0.226108f, 0); 
    instance.addEObj( "Decayingtree", 2005603, 0, 5877247, 4, { 641.914795f, -34.114819f, 332.062805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Decayingtree_1", 2005604, 0, 5877248, 4, { 665.376770f, -30.704359f, 340.694885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Decayingtree_2", 2005605, 0, 5877249, 4, { 663.437622f, -32.470852f, 321.370789f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2006139, 0, 5911481, 4, { 792.037170f, -33.547161f, -272.795685f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_29", 2006140, 0, 5911482, 4, { 792.037170f, -33.547199f, -272.795685f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2006142, 0, 5911547, 4, { 664.581726f, -24.510180f, -289.013885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Dravanianlily", 2006141, 0, 5911550, 4, { 664.581726f, -24.274321f, -289.013885f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_31", 2006179, 0, 5911568, 4, { 663.513672f, -24.524200f, -289.013885f }, 1.000000f, -0.507401f, 0); 
    instance.addEObj( "unknown_32", 2006144, 0, 5911566, 4, { 162.432297f, -18.039400f, -566.704773f }, 0.991760f, -1.068423f, 0); 
    instance.addEObj( "Dravanianlily_1", 2006143, 0, 5911567, 4, { 162.432495f, -17.929890f, -566.683777f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2006311, 0, 5922984, 4, { 663.513672f, -24.524200f, -289.013885f }, 1.000000f, -0.507400f, 0); 
    instance.addEObj( "Woodenhuntingbow", 2005607, 0, 5877260, 4, { 419.648499f, -26.321560f, -507.586487f }, 0.991760f, -0.886611f, 0); 
    instance.addEObj( "Destination_12", 2005609, 0, 5877264, 4, { 44.494431f, -37.000000f, -309.631592f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Caelumtreefruit", 2005610, 0, 5877281, 4, { 171.524796f, -19.650120f, -385.330414f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Caelumtreefruit_1", 2005611, 0, 5877282, 4, { 175.733902f, -15.616510f, -398.489899f }, 1.500000f, 0.520462f, 0); 
    instance.addEObj( "Caelumtreefruit_2", 2005612, 0, 5877283, 4, { 195.135193f, -19.160139f, -389.558197f }, 1.500000f, 1.346569f, 0); 
    instance.addEObj( "unknown_34", 2005613, 0, 5877285, 4, { 169.342407f, -7.593880f, -392.226013f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_35", 2005614, 0, 5877286, 4, { 177.389404f, -7.544930f, -397.649994f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2005615, 0, 5877287, 4, { 183.948593f, -6.957005f, -381.401306f }, 1.480042f, 0.000048f, 0); 
    instance.addEObj( "Dravanianclay", 2005617, 0, 5877290, 4, { 197.253296f, -99.922897f, 644.495178f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Dravanianclay_1", 2005618, 0, 5877291, 4, { 287.652496f, -94.082764f, 597.964417f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Silverdew", 2005619, 0, 5877293, 4, { 352.361298f, -48.011971f, 68.510696f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Silverdew_1", 2005620, 0, 5877297, 4, { 388.302887f, -41.159180f, 80.777161f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Silverdew_2", 2005621, 0, 5877299, 4, { 413.320312f, -50.885071f, 98.354424f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Silverdew_3", 2005622, 0, 5877300, 4, { 435.438507f, -51.141399f, 56.281158f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Silverdew_4", 2005623, 0, 5877301, 4, { 414.505188f, -50.993450f, 35.833912f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Silverdew_5", 2005624, 0, 5877302, 4, { 437.668396f, -51.141399f, 80.113113f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Yellowpebble", 2005633, 0, 5881642, 4, { -273.518005f, -82.473663f, 644.647827f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Yellowpebble_1", 2005634, 0, 5881643, 4, { -307.295288f, -80.151993f, 665.678284f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Yellowpebble_2", 2005635, 0, 5881644, 4, { -187.212997f, -84.833908f, 733.516418f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Yellowpebble_3", 2005636, 0, 5881645, 4, { -247.181000f, -77.603989f, 819.485718f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Yellowpebble_4", 2005637, 0, 5881646, 4, { -443.045685f, -83.750954f, 714.289917f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Yellowpebble_5", 2005638, 0, 5881647, 4, { -605.920471f, -96.042122f, 625.390930f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Abandonedwain", 2005641, 0, 5881662, 4, { -44.750900f, -120.862297f, 603.062927f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_37", 2005642, 0, 5881663, 4, { -44.750900f, -120.862297f, 603.062927f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Flintlockfiresand", 2005643, 0, 5881678, 4, { 500.177704f, -98.974777f, 819.508972f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Flintlockfiresand_1", 2005644, 0, 5881679, 4, { 475.514191f, -99.721092f, 818.738770f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Flintlockfiresand_2", 2005645, 0, 5881681, 4, { 462.993103f, -101.126297f, 841.599609f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_38", 2005646, 0, 5881683, 4, { 69.722977f, -49.254311f, -141.703796f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_39", 2005648, 0, 5881694, 4, { 705.916504f, -36.330410f, 197.842407f }, 0.750000f, -0.976767f, 0); 
    instance.addEObj( "unknown_40", 2005647, 0, 5881695, 4, { 707.094788f, -36.249470f, 198.869202f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_41", 2005649, 0, 5881706, 4, { 705.916504f, -36.330399f, 197.842407f }, 0.750000f, -0.976768f, 0); 
    instance.addEObj( "Gallimimusegg", 2005650, 0, 5881789, 4, { -330.293610f, 133.621399f, -185.218704f }, 1.000000f, -1.445890f, 0); 
    instance.addEObj( "Gallimimusegg_1", 2005651, 0, 5881790, 4, { -327.347687f, 142.803894f, -209.968201f }, 1.000000f, 1.370044f, 0); 
    instance.addEObj( "Gallimimusegg_2", 2005652, 0, 5881791, 4, { -271.523499f, 151.840698f, -237.072098f }, 1.000000f, -0.843781f, 0); 
    instance.addEObj( "Gallimimusegg_3", 2005653, 0, 5881792, 4, { -273.847992f, 156.307007f, -311.701385f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gallimimusegg_4", 2005654, 0, 5881793, 4, { -245.277893f, 159.599304f, -342.428802f }, 1.000000f, 0.855362f, 0); 
    instance.addEObj( "Gallimimusegg_5", 2005655, 0, 5881794, 4, { -223.470306f, 155.702805f, -303.318512f }, 1.000000f, -0.957691f, 0); 
    instance.addEObj( "Gallimimusegg_6", 2005656, 0, 5881795, 4, { -217.129807f, 160.043503f, -327.483307f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gallimimusegg_7", 2005657, 0, 5881799, 4, { -302.394714f, 151.810699f, -245.929703f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_42", 2005703, 0, 5884497, 4, { 706.776428f, -35.225159f, 202.539307f }, 1.000000f, 0.410813f, 0); 
    instance.addEObj( "unknown_43", 2005702, 0, 5884498, 4, { 706.776428f, -35.225201f, 202.539307f }, 1.000000f, 0.410813f, 0); 
    instance.addEObj( "Friedchocobothigh", 2005701, 0, 5884499, 4, { 706.776428f, -35.225159f, 202.539307f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "unknown_44", 2006444, 0, 5960731, 4, { -431.132111f, -34.623280f, 249.832397f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_45", 2005661, 0, 5882000, 4, { -354.409393f, -90.725830f, 520.208313f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_46", 2005662, 0, 5882003, 4, { -245.652405f, -96.738762f, 537.535889f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_47", 2005663, 0, 5882004, 4, { -242.450607f, -79.199348f, 431.967712f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Peculiarcenser", 2005658, 0, 5882006, 4, { -354.409393f, -90.725800f, 520.208313f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Peculiarcenser_1", 2005659, 0, 5882007, 4, { -245.652405f, -96.738808f, 537.535889f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Peculiarcenser_2", 2005660, 0, 5882008, 4, { -242.438507f, -79.181282f, 431.971008f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_48", 2005664, 0, 5882227, 4, { 136.678299f, -68.460800f, 12.190100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_49", 2005665, 0, 5882228, 4, { 174.466003f, -61.077202f, -32.657009f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_50", 2005666, 0, 5882229, 4, { 189.546204f, -64.695503f, 17.492210f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_51", 2005670, 0, 5882349, 4, { 188.639694f, -95.246208f, 296.191986f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gnathicsupplies", 2005667, 0, 5882350, 4, { 188.639694f, -95.246208f, 296.191986f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_52", 2005671, 0, 5882354, 4, { 261.611603f, -90.738136f, 267.202301f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gnathicsupplies_1", 2005668, 0, 5882355, 4, { 261.611603f, -90.738136f, 267.202301f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_53", 2005672, 0, 5882357, 4, { 266.817688f, -78.851227f, 221.699997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gnathicsupplies_2", 2005669, 0, 5882358, 4, { 266.817596f, -78.851219f, 221.699997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gronahlm_1", 2005673, 0, 5882374, 4, { -114.158600f, 130.228699f, -558.110718f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_13", 2006029, 0, 5905506, 4, { 27.010031f, -138.504395f, 718.679688f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_14", 2006030, 0, 5905519, 4, { 125.252899f, -111.178596f, 300.757690f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Begrimedtablet", 2006031, 0, 5905538, 4, { -43.852001f, 272.620697f, -812.533081f }, 1.000000f, -0.651911f, 0); 
    instance.addEObj( "Wyverntails", 2006032, 0, 5905605, 4, { 377.650299f, 25.240480f, -624.573730f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_54", 2006145, 0, 5911603, 4, { 868.156372f, -3.603497f, 243.737396f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_55", 2006146, 0, 5911604, 4, { 838.501709f, -6.457367f, 237.524902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_56", 2006147, 0, 5911605, 4, { 847.048584f, -4.942038f, 275.282593f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_57", 2006148, 0, 5911621, 4, { 839.845215f, -31.582861f, -319.536987f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ironlegtrap", 2006149, 0, 5911657, 4, { 431.278015f, -39.337189f, -413.650391f }, 1.000000f, 0.971629f, 0); 
    instance.addEObj( "Ironlegtrap_1", 2006150, 0, 5911658, 4, { 465.621307f, -34.758308f, -417.698486f }, 1.000000f, 1.024385f, 0); 
    instance.addEObj( "Ironlegtrap_2", 2006151, 0, 5911659, 4, { 439.464813f, -34.988701f, -444.104614f }, 1.000000f, 0.127129f, 0); 
    instance.addEObj( "unknown_58", 2006153, 0, 5911677, 4, { 661.781616f, -24.278730f, -473.932007f }, 0.991760f, 0.593244f, 0); 
    instance.addEObj( "unknown_59", 2006154, 0, 5911678, 4, { 662.348328f, -24.399229f, -470.023712f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_60", 2006155, 0, 5911680, 4, { 661.091919f, -24.399229f, -470.115204f }, 0.991760f, 1.054272f, 0); 
    instance.addEObj( "unknown_61", 2006156, 0, 5911682, 4, { 663.234924f, -24.272650f, -473.506012f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_62", 2006162, 0, 5911697, 4, { 184.618301f, -27.767099f, -443.247894f }, 1.000000f, -0.000488f, 0); 
    instance.addEObj( "unknown_63", 2006157, 0, 5911701, 4, { 97.062500f, -2.059998f, -497.306793f }, 0.747620f, 0.000048f, 0); 
    instance.addEObj( "unknown_64", 2006158, 0, 5911702, 4, { 95.428200f, -2.139925f, -495.812500f }, 0.991760f, 0.387710f, 0); 
    instance.addEObj( "unknown_65", 2006159, 0, 5911703, 4, { 95.304787f, -2.235441f, -494.276489f }, 0.991760f, 0.551611f, 0); 
    instance.addEObj( "unknown_66", 2006160, 0, 5911704, 4, { 98.927711f, -2.085159f, -495.695190f }, 0.991760f, 0.703503f, 0); 
    instance.addEObj( "unknown_67", 2006161, 0, 5911705, 4, { 98.437538f, -2.188295f, -495.226990f }, 0.600000f, 0.000048f, 0); 
    instance.addEObj( "unknown_68", 2006163, 0, 5911717, 4, { 97.062500f, -2.060000f, -497.306793f }, 0.747600f, 0.000047f, 0); 
    instance.addEObj( "unknown_69", 2006164, 0, 5911718, 4, { 95.428200f, -2.139900f, -495.812500f }, 0.991800f, 0.387709f, 0); 
    instance.addEObj( "unknown_70", 2006165, 0, 5911719, 4, { 95.304802f, -2.235400f, -494.276489f }, 0.991800f, 0.551611f, 0); 
    instance.addEObj( "unknown_71", 2006166, 0, 5911720, 4, { 98.927696f, -2.085200f, -495.695190f }, 0.991800f, 0.703504f, 0); 
    instance.addEObj( "unknown_72", 2006167, 0, 5911721, 4, { 98.437500f, -2.188300f, -495.226990f }, 0.600000f, 0.000047f, 0); 
    instance.addEObj( "unknown_73", 2006168, 0, 5911759, 4, { 346.223907f, -29.674240f, -420.993500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_74", 2006169, 0, 5911761, 4, { 352.520813f, -29.001480f, -414.552307f }, 1.000000f, -0.042022f, 0); 
    instance.addEObj( "Destination_15", 2005833, 0, 5890610, 4, { 227.289307f, -22.262100f, -499.106689f }, 1.000000f, -0.000984f, 0); 
    instance.addEObj( "unknown_75", 2005832, 0, 5890611, 4, { 227.289200f, -22.262070f, -499.106689f }, 2.500000f, 0.741923f, 0); 
    instance.addEObj( "Destination_16", 2005834, 0, 5890612, 4, { 215.953201f, -22.026630f, -500.313385f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MasterofMarksmanship );