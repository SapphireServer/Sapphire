#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheFlameintheAbyss : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_SIDURGU_01 = 5912555;
  static constexpr auto BNPC_ENEMY_PHASE_1_TANK_MOOGLE_01 = 5912556;
  static constexpr auto BNPC_ENEMY_PHASE_1_HEALER_MOOGLE_01 = 5912557;
  static constexpr auto BNPC_ENEMY_PHASE_2_SNIPER_MOOGLE_01 = 5912558;
  static constexpr auto BNPC_ENEMY_PHASE_2_NUKER_MOOGLE_01 = 5912559;
  static constexpr auto BNPC_ENEMY_PHASE_3_ATTACKER_MOOGLE_01 = 5912560;
  static constexpr auto BNPC_ENEMY_PHASE_3_BUFFER_MOOGLE_01 = 5912561;
  static constexpr auto BNPC_ENEMY_PHASE_3_DEBUFFER_MOOGLE_01 = 5912562;
  static constexpr auto CUT_SCENE_01 = 994;
  static constexpr auto LOC_ACTOR0 = 1014593;
  static constexpr auto LOC_ACTOR1 = 1014607;
  static constexpr auto LOC_ACTOR2 = 1014608;
  static constexpr auto LOC_MARKER_01 = 5959850;
  static constexpr auto LOC_BGM0 = 178;

public:
  TheFlameintheAbyss() : Sapphire::ScriptAPI::QuestBattleScript( 147 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Dravaniancoin", 2006126, 0, 5910175, 4, { 571.992798f, -9.641846f, -46.839500f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Dravaniancoin_1", 2006126, 0, 5910177, 4, { 552.354187f, -9.421217f, -30.343941f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Dravaniancoin_2", 2006126, 0, 5910178, 4, { 610.692688f, -9.529379f, -23.132589f }, 1.000000f, -0.000005f, 0); 
    instance.addEObj( "Dravaniancoin_3", 2006126, 0, 5910179, 4, { 602.207520f, -9.652254f, -4.143999f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Dravaniancoin_4", 2006126, 0, 5910180, 4, { 583.749512f, -9.697674f, -18.699930f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Dravaniancoin_5", 2006126, 0, 5910181, 4, { 568.390015f, -10.086510f, 6.712241f }, 1.000000f, -0.000099f, 0); 
    instance.addEObj( "Dravaniancoin_6", 2006126, 0, 5910182, 4, { 590.771973f, -9.796937f, 10.655310f }, 0.991760f, -0.000048f, 0); 
    instance.addEObj( "Dravaniancoin_7", 2006126, 0, 5910183, 4, { 560.656677f, -9.421229f, -10.344700f }, 0.991760f, -0.000048f, 0); 
    instance.addEObj( "Summoningstone", 2005698, 0, 5881979, 4, { 265.156006f, -42.557430f, 565.606079f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Aethericdisturbance", 2006372, 0, 5936440, 4, { 379.451813f, -69.429581f, 694.464111f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethericdisturbance_1", 2006373, 0, 5936441, 4, { 390.920807f, -72.373596f, 650.507324f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Summoningstone_1", 2005699, 0, 5881988, 4, { -50.416698f, -8.866000f, 146.561798f }, 1.000000f, -0.714339f, 0); 
    instance.addEObj( "Summoningstone_2", 2005700, 0, 5881989, 4, { -521.219727f, 50.000000f, 362.081299f }, 1.000000f, -0.651134f, 0); 
    instance.addEObj( "Aethercurrent", 2006216, 0, 5915755, 4, { 421.189392f, -43.045490f, 661.798218f }, 1.000000f, -0.017841f, 0); 
    instance.addEObj( "Aethercurrent_1", 2006217, 0, 5915756, 4, { -115.066399f, 36.394440f, 174.008804f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_2", 2006218, 0, 5915757, 4, { -775.237671f, 123.762497f, 243.705704f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_3", 2006219, 0, 5915825, 4, { -242.502701f, 40.961342f, 275.764099f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_4", 2006220, 0, 5915851, 4, { -314.117310f, 81.602097f, -90.215958f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_5", 2006221, 0, 5915852, 4, { -44.821999f, 81.816910f, -110.669998f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_6", 2006222, 0, 5915885, 4, { 601.823120f, -9.467012f, -336.298798f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_7", 2006223, 0, 5915931, 4, { 718.436279f, 34.930168f, 177.179306f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_8", 2006224, 0, 5915949, 4, { -210.702896f, 160.490601f, -726.487488f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aethercurrent_9", 2006215, 0, 5915954, 4, { 52.904469f, -33.766579f, -147.830597f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination", 2005450, 0, 5858214, 4, { 405.908203f, -72.565819f, 696.300171f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_1", 2005451, 0, 5858215, 4, { 379.256104f, -69.429741f, 690.311584f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2005452, 0, 5858216, 4, { 402.029297f, -73.136467f, 668.451782f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Cloudsbreath", 2005455, 0, 5858370, 4, { 289.942810f, -37.963081f, 483.548798f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Cloudsbreath_1", 2005454, 0, 5858371, 4, { 339.729401f, -12.450290f, 411.329712f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Cloudsbreath_2", 2005453, 0, 5858372, 4, { 223.563797f, -38.672722f, 440.663391f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_0", 2005547, 0, 5864419, 4, { 244.076706f, -40.728970f, 444.115601f }, 1.500000f, 0.000048f, 0); 
    instance.addEObj( "Paintedstone", 2005456, 0, 5858373, 4, { 261.279602f, 12.446850f, 622.073120f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_1", 2005457, 0, 5858513, 4, { 305.226196f, -41.428280f, 326.710907f }, 1.480042f, 0.173295f, 0); 
    instance.addEObj( "unknown_2", 2005458, 0, 5858514, 4, { 208.423004f, -23.331120f, 164.812607f }, 1.480042f, 0.000048f, 0); 
    instance.addEObj( "unknown_3", 2005538, 0, 5862324, 4, { -232.775101f, -12.733810f, 322.597412f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2005539, 0, 5862325, 4, { -92.723022f, -5.473404f, 379.660095f }, 0.991760f, 0.458988f, 0); 
    instance.addEObj( "Destination_3", 2005459, 0, 5858852, 4, { -758.350281f, 123.704803f, 214.524506f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2005460, 0, 5859054, 4, { -456.076904f, 43.869629f, 402.883911f }, 1.480042f, 0.000048f, 0); 
    instance.addEObj( "unknown_6", 2005461, 0, 5859056, 4, { 149.401093f, -23.331120f, 177.477707f }, 1.480042f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2005462, 0, 5859057, 4, { 396.108887f, -29.160030f, -142.534500f }, 1.052795f, 0.000048f, 0); 
    instance.addEObj( "Destination_4", 2006302, 0, 5908490, 4, { 269.970001f, -40.288368f, 398.630005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2006303, 0, 5908491, 4, { 342.160004f, -40.017700f, 288.579987f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2006304, 0, 5908492, 4, { 417.089996f, -34.539280f, 222.979996f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_7", 2006381, 0, 5937806, 4, { 421.164215f, -29.389179f, 97.184700f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tussock", 2006346, 0, 5931137, 4, { 429.989990f, -10.100000f, 708.200012f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tussock_1", 2006347, 0, 5931138, 4, { 346.500000f, 0.260000f, 565.630005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tussock_2", 2006348, 0, 5931139, 4, { 312.200012f, 17.870001f, 718.919983f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tussock_3", 2006349, 0, 5931140, 4, { 204.779999f, 4.750000f, 736.359985f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_8", 2006350, 0, 5931156, 4, { 173.870697f, -22.123760f, 160.809494f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2006351, 0, 5931162, 4, { -158.770203f, -23.453131f, 282.123993f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Descenttotheforelands", 2005371, 0, 5836078, 4, { 201.610107f, -68.678650f, 709.369629f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2006106, 0, 5910576, 4, { 770.245728f, -9.491300f, 287.973114f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Hornbloom", 2005676, 0, 5882860, 4, { 377.563385f, -26.521170f, 33.384140f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Hornbloom_1", 2005677, 0, 5882861, 4, { 411.882812f, -27.942390f, 121.839401f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Hornbloom_2", 2005678, 0, 5882862, 4, { 445.475586f, -16.344549f, 81.453812f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wovenbasket", 2005679, 0, 5883034, 4, { -255.994003f, 30.065689f, 587.651123f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wovenbasket_1", 2005680, 0, 5883035, 4, { -261.817413f, 29.272360f, 508.899902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Wovenbasket_2", 2005681, 0, 5883036, 4, { -302.354706f, 30.086981f, 507.690186f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Claypot", 2005683, 0, 5883302, 4, { -517.179321f, 60.541649f, 486.548187f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Claypot_1", 2005682, 0, 5883303, 4, { -517.179321f, 60.876301f, 486.548187f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut", 2005684, 0, 5883367, 4, { 227.162598f, 7.849481f, 688.138123f }, 1.000000f, -1.429513f, 0); 
    instance.addEObj( "Kuponut_1", 2005685, 0, 5883368, 4, { 235.742203f, 8.741125f, 693.467529f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut_2", 2005686, 0, 5883369, 4, { 374.868286f, 19.999920f, 744.781799f }, 0.991760f, 0.342604f, 0); 
    instance.addEObj( "Kuponut_3", 2005687, 0, 5883370, 4, { 372.973511f, 19.771730f, 761.619629f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut_4", 2005689, 0, 5883372, 4, { 346.273712f, -0.210060f, 540.648193f }, 0.991760f, 1.308698f, 0); 
    instance.addEObj( "Kuponut_5", 2005690, 0, 5883374, 4, { 321.105286f, 1.309799f, 549.121582f }, 1.000000f, -0.604834f, 0); 
    instance.addEObj( "unknown_10", 2006107, 0, 5910619, 4, { -473.150696f, 42.937061f, 360.223907f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2006108, 0, 5910634, 4, { -177.325104f, -21.377930f, 266.681885f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Ancienttool", 2005692, 0, 5883393, 4, { 457.341888f, 10.966200f, 79.288719f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ancienttool_1", 2005693, 0, 5883397, 4, { 513.841614f, -11.748260f, 79.998543f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ancienttool_2", 2005694, 0, 5883398, 4, { 499.689514f, -20.271420f, 143.840195f }, 1.000000f, 0.775364f, 0); 
    instance.addEObj( "Mocaleaf", 2005714, 0, 5887527, 4, { 757.455627f, -24.900770f, -218.337204f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Clearspring", 2005715, 0, 5887533, 4, { 718.401672f, -49.965321f, 437.830414f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2005716, 0, 5887540, 4, { 615.817505f, -37.677608f, -427.402802f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sparklyspillikin", 2005717, 0, 5887548, 4, { 639.009827f, 46.483170f, -113.026604f }, 1.000000f, 0.656891f, 0); 
    instance.addEObj( "Sparklyspillikin_1", 2005718, 0, 5887549, 4, { 664.399780f, -0.473089f, -3.277048f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Sparklyspillikin_2", 2005719, 0, 5887550, 4, { 522.592773f, -4.230852f, -91.770264f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sparklyspillikin_3", 2005720, 0, 5887551, 4, { 565.949829f, -9.421211f, -14.302220f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sparklyspillikin_4", 2005721, 0, 5887552, 4, { 653.863403f, -0.711572f, -70.011574f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2005724, 0, 5887562, 4, { -487.113007f, 60.541649f, 493.031189f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Dragonegg", 2005723, 0, 5887564, 4, { -487.113007f, 60.541649f, 493.031189f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Dragonegg_1", 2005722, 0, 5887565, 4, { -487.113007f, 60.541698f, 493.031189f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2005725, 0, 5887581, 4, { -115.779999f, -13.881010f, 418.722687f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2005726, 0, 5887582, 4, { -54.596958f, -8.227981f, 455.196503f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2005727, 0, 5887583, 4, { -6.715940f, -21.049061f, 409.875214f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Crackleweedseedling", 2005728, 0, 5887599, 4, { 79.542412f, 27.383591f, 286.530792f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Crackleweedseedling_1", 2005729, 0, 5887600, 4, { 114.540604f, 39.995201f, 256.540894f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Crackleweedseedling_2", 2005730, 0, 5887601, 4, { 184.496796f, 26.016600f, 249.764801f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Crackleweedseedling_3", 2005731, 0, 5887602, 4, { 145.333405f, 49.715809f, 306.048706f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Crackleweedseedling_4", 2005732, 0, 5887603, 4, { 138.971207f, 4.664304f, 349.233002f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Mogsonsbasket", 2005733, 0, 5887720, 4, { -149.356293f, 138.490601f, -641.314270f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Mogsonsbasket_1", 2005734, 0, 5887723, 4, { -244.280899f, 134.490601f, -616.995911f }, 0.991760f, -1.078160f, 0); 
    instance.addEObj( "Mogsonsbasket_2", 2005735, 0, 5887725, 4, { -214.320007f, 134.490707f, -577.309509f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut_6", 2005736, 0, 5887745, 4, { -467.963989f, 39.887741f, 146.394196f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Kuponut_7", 2005737, 0, 5887756, 4, { -471.557007f, 40.703400f, 101.547302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut_8", 2005738, 0, 5887757, 4, { -436.191406f, 41.275909f, 79.417183f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Kuponut_9", 2005739, 0, 5887758, 4, { -465.891693f, 41.144939f, 48.234348f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Kuponut_10", 2005740, 0, 5887759, 4, { -426.538513f, 40.082050f, 21.136850f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wildfowlnest", 2005741, 0, 5887768, 4, { -800.991821f, 238.574707f, 265.073914f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wildfowlnest_1", 2005742, 0, 5887769, 4, { -703.362671f, 342.977112f, 213.441193f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wildfowlnest_2", 2005743, 0, 5887770, 4, { -762.182678f, 344.228302f, 305.985687f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wildfowlnest_3", 2005744, 0, 5887771, 4, { -749.882507f, 418.750000f, 224.802704f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "Wildfowlnest_4", 2005745, 0, 5887776, 4, { -787.266418f, 73.133797f, 301.198303f }, 2.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2005746, 0, 5887873, 4, { -103.224899f, 61.924400f, -204.925201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2005747, 0, 5887874, 4, { -173.319595f, 61.924400f, -257.925415f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005748, 0, 5887875, 4, { -61.326050f, 61.936279f, -302.571198f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2005749, 0, 5887907, 4, { -201.405899f, 160.490601f, -740.380615f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2005750, 0, 5887909, 4, { -139.483597f, 160.940598f, -788.052612f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2005751, 0, 5887913, 4, { -267.600006f, 168.796906f, -706.734619f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2005752, 0, 5887935, 4, { -132.845200f, 160.936905f, -628.500427f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_24", 2005753, 0, 5887936, 4, { -182.121307f, 204.490601f, -731.043579f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2005754, 0, 5887938, 4, { -133.366196f, 246.043198f, -735.278381f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Whistleberryseedling", 2005755, 0, 5888035, 4, { -809.586121f, 90.894707f, -431.742798f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Whistleberryseedling_1", 2005756, 0, 5888036, 4, { -795.209473f, 90.893257f, -458.841400f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Whistleberryseedling_2", 2005757, 0, 5888037, 4, { -773.044800f, 90.892281f, -403.589111f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Whistleberryseedling_3", 2005758, 0, 5888038, 4, { -764.866028f, 90.894974f, -460.445312f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Whistleberryseedling_4", 2005759, 0, 5888039, 4, { -788.868225f, 90.827530f, -381.641602f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmallow", 2005760, 0, 5888047, 4, { -42.884239f, -62.796452f, 765.229675f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmallow_1", 2005761, 0, 5888048, 4, { -387.900787f, 79.123779f, 662.164673f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cloudmallow_2", 2005762, 0, 5888049, 4, { -775.461304f, 32.500000f, 483.771088f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2006085, 0, 5908403, 4, { -6.298516f, -20.661119f, 181.779297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2006086, 0, 5908417, 4, { -271.426910f, 41.098999f, 242.216599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2006087, 0, 5908432, 4, { -578.443481f, 80.997063f, 102.794800f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_29", 2006088, 0, 5908433, 4, { -627.790771f, 81.000000f, 98.924522f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2006089, 0, 5908434, 4, { -609.149719f, 81.530273f, 141.145096f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_31", 2006090, 0, 5908443, 4, { -766.678284f, 81.000000f, 405.081787f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_32", 2006091, 0, 5908444, 4, { -722.350525f, 80.999977f, 428.440094f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2006092, 0, 5908445, 4, { -721.905212f, 81.000000f, 378.439087f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_34", 2005820, 0, 5888581, 4, { 16.186529f, 81.840630f, -322.884796f }, 1.000000f, -0.310446f, 0); 
    instance.addEObj( "Sealedcrate", 2005821, 0, 5888582, 4, { 16.186501f, 82.195427f, -322.884796f }, 1.000000f, -0.310447f, 0); 
    instance.addEObj( "unknown_35", 2005786, 0, 5888291, 4, { 13.901200f, 81.840599f, -321.765015f }, 1.000000f, 0.376358f, 0); 
    instance.addEObj( "unknown_36", 2005785, 0, 5888292, 4, { 12.351700f, 81.834099f, -332.058411f }, 1.000000f, -1.167116f, 0); 
    instance.addEObj( "Anzunest", 2005787, 0, 5888448, 4, { -230.082199f, -28.884741f, 743.145874f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Anzunest_1", 2005788, 0, 5888449, 4, { -287.520599f, -30.433800f, 698.193604f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Anzunest_2", 2005789, 0, 5888450, 4, { -159.992294f, -33.519829f, 688.126526f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_37", 2005792, 0, 5888467, 4, { -37.979801f, 62.912842f, -294.422913f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_38", 2005793, 0, 5888468, 4, { -8.859003f, 76.756104f, -249.009201f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_39", 2005794, 0, 5888469, 4, { -48.163219f, 76.756104f, -351.019501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_40", 2005799, 0, 5888506, 4, { 16.186501f, 81.840599f, -322.884796f }, 1.000000f, -0.310447f, 0); 
    instance.addEObj( "unknown_41", 2005800, 0, 5888507, 4, { -129.114502f, -64.869797f, -316.302002f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer", 2005805, 0, 5888524, 4, { 161.404404f, 212.647507f, -733.703125f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer_1", 2005806, 0, 5888525, 4, { 110.530296f, 212.664307f, -785.146423f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_42", 2005810, 0, 5888568, 4, { 16.186501f, 81.840599f, -322.884796f }, 1.000000f, -0.310447f, 0); 
    instance.addEObj( "Aetherometer_2", 2005811, 0, 5888569, 4, { -815.487915f, 258.098114f, -674.921814f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "Aetherometer_3", 2005812, 0, 5888570, 4, { -757.390320f, 257.501892f, -702.556824f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer_4", 2005813, 0, 5888571, 4, { -788.023621f, 257.680389f, -644.163818f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer_5", 2005814, 0, 5888573, 4, { -755.947205f, 258.808289f, -207.721100f }, 0.472961f, 0.000048f, 0); 
    instance.addEObj( "Aetherometer_6", 2005815, 0, 5888574, 4, { -701.837280f, 258.554596f, -165.230606f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer_7", 2005816, 0, 5888575, 4, { -697.996277f, 258.302704f, -221.659103f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Sealedcrate_1", 2005817, 0, 5888577, 4, { 16.186501f, 82.195396f, -322.884796f }, 1.000000f, -0.310447f, 0); 
    instance.addEObj( "unknown_43", 2006119, 0, 5910932, 4, { 464.761810f, 5.880255f, 802.713379f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_44", 2006118, 0, 5911115, 4, { 344.813904f, 1.112148f, 554.725281f }, 0.991760f, -1.066800f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFlameintheAbyss );