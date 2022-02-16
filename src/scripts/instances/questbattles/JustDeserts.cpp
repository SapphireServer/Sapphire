#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class JustDeserts : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 4082418;
  static constexpr auto BNPC_NAME_01 = 750;
  static constexpr auto DEF_ACTION_SAND_BREATH = 445;
  static constexpr auto LOC_ACTOR1 = 1003064;
  static constexpr auto LOC_POS_ACTOR0 = 4126749;
  static constexpr auto LOC_POS_ACTOR1 = 4126755;
  static constexpr auto DEF_BLIND = 15;
  static constexpr auto CUT_SCENE_01 = 203;
  static constexpr auto LOC_TALKSHAPE1 = 8;

public:
  JustDeserts() : Sapphire::ScriptAPI::QuestBattleScript( 29 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Exit", 2000605, 0, 4263086, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2000606, 3861081, 4263087, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000604, 4262798, 4263088, 5, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Earthspritecore", 2001221, 0, 4163769, 4, { -185.673004f, 36.598942f, 348.954987f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_1", 2001221, 0, 4163770, 4, { -144.712997f, 44.095612f, 337.720398f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_2", 2001221, 0, 4163771, 4, { -139.159897f, 44.119518f, 375.516693f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_3", 2001221, 0, 4163772, 4, { -125.920898f, 46.215401f, 364.480713f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_4", 2001221, 0, 4163773, 4, { -207.121796f, 34.620338f, 343.721710f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_5", 2001221, 0, 4163774, 4, { -177.589203f, 37.378311f, 375.839203f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_6", 2001221, 0, 4163775, 4, { -135.196198f, 45.881248f, 388.070709f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_7", 2001221, 0, 4163776, 4, { -124.855698f, 47.177441f, 336.891602f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2000205, 3841548, 3237648, 4, { -382.994202f, 25.285480f, -512.841187f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2000206, 4030543, 3237650, 4, { -382.797791f, 24.058620f, -569.999329f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2000207, 4030563, 3237652, 4, { -384.516693f, 24.065800f, -577.594116f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ironlever", 2000209, 0, 3237656, 4, { -392.499512f, 24.935869f, -487.555908f }, 1.000000f, 1.042826f, 0); 
    instance.addEObj( "sgpl_wil_w1f1_rock02", 2001705, 4165897, 4108317, 4, { -345.592102f, 15.234820f, -632.468323f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_wil_w1f1_rock03", 2001705, 4165900, 4108323, 4, { -366.638000f, 15.153470f, -651.078613f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2001710, 4138496, 4138489, 5, { -466.621002f, 22.995081f, -472.606415f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Ironlever_1", 2001805, 0, 4175817, 4, { -377.859192f, 24.185551f, -562.981689f }, 0.991760f, 1.504764f, 0); 
    instance.addEObj( "unknown_4", 2001684, 0, 4105352, 4, { 191.706497f, 53.259998f, -43.777901f }, 1.000000f, -0.943361f, 0); 
    instance.addEObj( "Curiousobject", 2003654, 0, 4622131, 4, { -68.557579f, 13.811150f, 159.184296f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2003655, 0, 4622132, 4, { -68.912437f, 13.549060f, 159.191299f }, 1.000000f, -0.118714f, 0); 
    instance.addEObj( "Preciouspotsherd", 2003656, 0, 4622218, 4, { -72.945534f, 13.527350f, 159.206696f }, 1.000000f, -0.416651f, 0); 
    instance.addEObj( "Preciouspotsherd_1", 2003657, 0, 4622219, 4, { -80.168518f, 13.427830f, 158.135193f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Preciouspotsherd_2", 2003658, 0, 4622225, 4, { -71.041443f, 13.443610f, 155.966293f }, 1.000000f, 1.114817f, 0); 
    instance.addEObj( "Preciouspotsherd_3", 2003659, 0, 4622229, 4, { -76.128853f, 13.454370f, 155.911102f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2003903, 0, 4635043, 4, { -432.590515f, 28.794950f, -383.577515f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2003904, 0, 4673429, 4, { -432.590515f, 28.795000f, -383.577515f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_8", 2005163, 0, 5655919, 4, { 364.692993f, 74.880417f, 170.318405f }, 1.000000f, 0.515260f, 0); 
    instance.addEObj( "unknown_9", 2005210, 0, 5707766, 4, { 364.667114f, 74.838120f, 170.304794f }, 0.991760f, 0.478285f, 0); 
    instance.addEObj( "Caravansack", 2001408, 0, 3972501, 4, { 154.381302f, 52.555969f, 200.925507f }, 0.991760f, -0.426474f, 0); 
    instance.addEObj( "Caravansack_1", 2001409, 0, 3972503, 4, { 141.835495f, 53.000080f, 221.575607f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2001725, 0, 4150248, 4, { 200.677505f, 52.038120f, 149.031906f }, 1.000000f, -0.840591f, 0); 
    instance.addEObj( "unknown_11", 2001726, 0, 4156166, 4, { -241.256607f, 32.476341f, 398.985504f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2005426, 0, 5852435, 4, { -156.058899f, 14.974940f, -325.202301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "×敵POPポイント", 2000240, 0, 3284826, 4, { 1.544363f, 47.733051f, 287.629486f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Trialstone", 2001541, 0, 4068717, 4, { 224.739502f, 52.070389f, 79.478127f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Trialstone_1", 2001542, 0, 4068718, 4, { 245.742493f, 52.498531f, 58.100361f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Trialstone_2", 2001543, 0, 4068719, 4, { 224.027100f, 52.244740f, 41.381931f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Trialstone_3", 2001544, 0, 4068720, 4, { 259.056488f, 53.448139f, 25.430000f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination", 2001468, 0, 4002288, 4, { -87.371643f, 50.629879f, 315.604614f }, 1.335633f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2001469, 0, 4002293, 4, { -74.943207f, 53.255798f, 336.807495f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_2", 2001472, 0, 4003482, 4, { 150.725098f, 18.805120f, -5.748842f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Shadedoutcropping", 2001474, 0, 4014193, 4, { 96.247253f, 16.975349f, 188.860504f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2001758, 0, 4175144, 4, { -269.838898f, 15.347900f, -718.118530f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_1", 2002694, 0, 4374439, 4, { -659.887085f, 62.116219f, -805.250305f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_2", 2002698, 0, 4374438, 4, { 328.773987f, 63.000000f, -228.168198f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "WakingSandsentrance", 2001711, 0, 4148333, 4, { -480.918091f, 18.001030f, -386.862000f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_14", 2003455, 0, 4672971, 4, { -520.720886f, 12.537260f, -369.257294f }, 1.000000f, -0.160624f, 0); 
    instance.addEObj( "Destination_3", 2002252, 0, 4301817, 4, { -662.345581f, 63.703388f, -805.475891f }, 1.000000f, -1.516295f, 0); 
    instance.addEObj( "unknown_15", 2002858, 0, 4502882, 4, { -470.847687f, 22.690121f, -439.597198f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_16", 2002859, 0, 4502883, 4, { -386.630493f, 24.769951f, -500.924988f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2002860, 0, 4502910, 4, { -367.215393f, 16.534220f, -628.223816f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2002861, 0, 4502913, 4, { -327.476013f, 14.770360f, -782.936218f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_4", 2003561, 0, 4620227, 4, { 175.079300f, 52.657982f, -51.644081f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2003562, 0, 4620228, 4, { 140.193497f, 55.403481f, -32.144279f }, 1.000000f, -0.431827f, 0); 
    instance.addEObj( "unknown_20", 2003563, 0, 4620916, 4, { 90.466728f, 15.128930f, 156.129196f }, 1.000000f, -0.851278f, 0); 
    instance.addEObj( "unknown_21", 2003563, 0, 4620917, 4, { 90.683792f, 15.115320f, 157.440903f }, 1.000000f, -1.528101f, 0); 
    instance.addEObj( "unknown_22", 2003563, 0, 4620918, 4, { 90.393692f, 15.986160f, 156.714096f }, 1.000000f, -0.476697f, 0); 
    instance.addEObj( "Weatheredcrate", 2003564, 0, 4622239, 4, { -494.902893f, 19.051371f, -352.231415f }, 0.750000f, -0.588395f, 0); 
    instance.addEObj( "Blackscale", 2003565, 0, 4622240, 4, { -492.155792f, 19.051319f, -356.257690f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackscale_1", 2003566, 0, 4622241, 4, { -477.134888f, 21.550840f, -362.625000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackscale_2", 2003567, 0, 4622242, 4, { -462.865997f, 23.031300f, -361.162415f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Blackscale_3", 2003568, 0, 4622243, 4, { -444.846008f, 23.021820f, -360.569000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2003573, 0, 4622363, 4, { 192.679306f, 52.578350f, 14.635490f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_23", 2003570, 0, 4677129, 4, { -390.152710f, 24.013620f, -348.136200f }, 0.750000f, 0.007942f, 0); 
    instance.addEObj( "unknown_24", 2003570, 0, 4677130, 4, { -390.079590f, 24.657551f, -348.104492f }, 0.750000f, -0.164489f, 0); 
    instance.addEObj( "unknown_25", 2003571, 0, 4677131, 4, { 122.520599f, 49.369301f, -179.912094f }, 0.750000f, 0.232433f, 0); 
    instance.addEObj( "unknown_26", 2003571, 0, 4677132, 4, { 121.849197f, 49.353828f, -180.857895f }, 0.750000f, -0.604124f, 0); 
    instance.addEObj( "unknown_27", 2003572, 0, 4677134, 4, { 256.280212f, 53.858521f, 144.223694f }, 0.750000f, 1.456685f, 0); 
    instance.addEObj( "unknown_28", 2003572, 0, 4677135, 4, { 254.908997f, 52.413540f, 144.814804f }, 0.750000f, 0.436474f, 0); 
    instance.addEObj( "Planarfissure", 2002431, 0, 4308386, 4, { -178.373398f, 15.435460f, -244.630005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Planarfissure_1", 2002432, 0, 4308387, 4, { -211.169601f, 15.408760f, -345.418488f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Planarfissure_2", 2002535, 0, 4323988, 4, { -178.373398f, 15.435420f, -244.630005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Planarfissure_3", 2002536, 0, 4323989, 4, { -211.169601f, 15.408720f, -345.418488f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Oldwoodenchest", 2002310, 0, 4295817, 4, { -283.908386f, 15.067190f, -774.671997f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Weatheredcrate_1", 2004102, 0, 4695118, 4, { -283.908386f, 15.067200f, -774.671997f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_29", 2001808, 0, 4175875, 4, { 160.723297f, 54.825562f, -45.548222f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_30", 2001714, 0, 4190129, 4, { 191.706497f, 53.206501f, -43.777901f }, 1.000000f, -0.943361f, 0); 
    instance.addEObj( "unknown_31", 2001714, 0, 4101396, 4, { 191.706497f, 53.259991f, -43.777889f }, 1.000000f, -0.943361f, 0); 
    instance.addEObj( "unknown_32", 2004690, 0, 5021395, 4, { 301.300903f, 63.558701f, 161.296494f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Winebaudsmessage", 2004132, 0, 4721955, 4, { -158.026199f, 14.901680f, -197.023407f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004136, 0, 4721965, 4, { -156.549500f, 14.974940f, -192.488205f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Winebaudsmessage_1", 2004133, 0, 4892862, 4, { -158.026199f, 14.901700f, -197.023407f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Winebaudsmessage_2", 2004134, 0, 4892863, 4, { -158.026199f, 14.901700f, -197.023407f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Listofdemands", 2004847, 0, 5071821, 4, { 323.642792f, 62.984390f, -207.887100f }, 1.000000f, -1.371537f, 0); 
    instance.addEObj( "EATCcargocrate", 2000738, 0, 3706840, 4, { 217.118195f, 60.471439f, 121.538002f }, 0.747620f, 0.830903f, 0); 
    instance.addEObj( "EATCcargocrate_1", 2000739, 0, 3706841, 4, { 212.965103f, 52.824039f, 147.999802f }, 0.747620f, 0.764395f, 0); 
    instance.addEObj( "EATCcargocrate_2", 2000740, 0, 3706842, 4, { 228.448898f, 55.569160f, 172.082993f }, 0.747620f, 0.113389f, 0); 
    instance.addEObj( "Fafafonosbaggage", 2001273, 0, 3923934, 4, { -210.864395f, 31.683620f, 370.595703f }, 0.961304f, 0.000144f, 0); 
    instance.addEObj( "Fafafonosbaggage_1", 2001274, 0, 3923935, 4, { -215.686295f, 31.992800f, 361.348907f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Fafafonosbaggage_2", 2001275, 0, 3923937, 4, { -218.890701f, 31.788309f, 365.163605f }, 0.961304f, 0.000144f, 0); 
    instance.addEObj( "Magnetite", 2001276, 0, 3923953, 4, { -162.859604f, 49.869110f, 312.336792f }, 1.300000f, -0.000000f, 0); 
    instance.addEObj( "Magnetite_1", 2001356, 0, 3949808, 4, { -118.516899f, 56.229370f, 411.123810f }, 1.296936f, 0.000048f, 0); 
    instance.addEObj( "Magnetite_2", 2001357, 0, 3949809, 4, { -99.895340f, 59.123940f, 389.090698f }, 1.300000f, 0.000000f, 0); 
    instance.addEObj( "Writofseizure", 2001456, 0, 3999587, 4, { -246.576706f, 35.180309f, 383.315613f }, 1.000000f, 1.167259f, 0); 
    instance.addEObj( "Writofseizure_1", 2001457, 0, 3999591, 4, { -218.018997f, 35.816582f, 426.025787f }, 1.000000f, -0.002433f, 0); 
    instance.addEObj( "Writofseizure_2", 2001458, 0, 3999593, 4, { -282.081604f, 35.200500f, 438.834198f }, 0.991760f, 0.407578f, 0); 
    instance.addEObj( "Writofseizure_3", 2001459, 0, 3999595, 4, { -306.982391f, 34.317501f, 396.963409f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_33", 2001852, 0, 4217254, 4, { -235.248795f, 15.910670f, -293.097198f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Trappoint", 2001374, 0, 3951678, 4, { 101.867302f, 49.365681f, -171.121094f }, 0.991760f, -1.182530f, 0); 
    instance.addEObj( "Trappoint_1", 2001375, 0, 3951683, 4, { 111.436600f, 49.171101f, -177.996506f }, 0.900208f, -0.674530f, 0); 
    instance.addEObj( "Trappoint_2", 2001376, 0, 3951862, 4, { 115.190300f, 49.143421f, -183.031998f }, 0.900208f, -0.273005f, 0); 
    instance.addEObj( "Trappoint_3", 2001377, 0, 3951883, 4, { 106.858902f, 49.335419f, -173.693497f }, 0.991760f, -0.931860f, 0); 
    instance.addEObj( "Nanaschitepebble", 2001399, 0, 3955178, 4, { 61.631142f, 46.075420f, -265.430695f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Nanaschitepebble_1", 2001400, 0, 3955182, 4, { 98.055641f, 45.213470f, -214.379593f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Nanaschitepebble_2", 2001401, 0, 3955184, 4, { 85.587769f, 46.424850f, -266.468292f }, 0.961304f, 0.000144f, 0); 
    instance.addEObj( "Nanaschitepebble_3", 2001402, 0, 3955186, 4, { 47.837040f, 45.220798f, -223.498901f }, 0.961304f, 0.000144f, 0); 
    instance.addEObj( "Splinteredcrate", 2001382, 0, 3953773, 4, { -282.520813f, 13.480670f, -145.922104f }, 0.991760f, 0.922943f, 0); 
    instance.addEObj( "Decayingvegetables", 2001383, 0, 3953775, 4, { -283.192200f, 13.480670f, -145.860992f }, 0.991760f, 1.086698f, 0); 
    instance.addEObj( "Bottomlesstoolbox", 2001384, 0, 3953776, 4, { -278.034698f, 13.480670f, -146.562897f }, 0.991760f, -0.671846f, 0); 
    instance.addEObj( "Unsoldpot", 2001475, 0, 4010998, 4, { -353.951996f, 13.900940f, -102.644096f }, 0.991760f, 0.004243f, 0); 
    instance.addEObj( "Decayingvegetables_1", 2001476, 0, 4011001, 4, { -356.013611f, 13.903760f, -100.384903f }, 0.991760f, -0.000432f, 0); 
    instance.addEObj( "Emptydecanter", 2001477, 0, 4011002, 4, { -325.368195f, 13.983500f, -109.073997f }, 0.991760f, -0.977592f, 0); 
    instance.addEObj( "Holeycup", 2001478, 0, 4011003, 4, { -324.971405f, 13.983500f, -108.587402f }, 0.991760f, 0.583399f, 0); 
    instance.addEObj( "Motheatensack", 2001479, 0, 4011004, 4, { -355.428406f, 13.900940f, -101.609901f }, 0.991760f, -0.962156f, 0); 
    instance.addEObj( "Flotsam", 2001385, 0, 3953779, 4, { -285.216705f, 19.834650f, -165.813995f }, 0.320374f, 0.081159f, 0); 
    instance.addEObj( "Flotsam_1", 2001386, 0, 3953780, 4, { -282.883209f, 19.015869f, -166.643906f }, 0.778198f, -1.349212f, 0); 
    instance.addEObj( "Flotsam_2", 2001387, 0, 3953781, 4, { -293.232697f, 19.514210f, -164.340897f }, 0.778198f, -0.018445f, 0); 
    instance.addEObj( "Oremound", 2001368, 0, 3951891, 4, { 297.566193f, 62.546749f, -194.048996f }, 0.991760f, 0.740205f, 0); 
    instance.addEObj( "Oremound_1", 2001369, 0, 3951893, 4, { 293.018890f, 63.492680f, -236.133408f }, 0.991760f, -1.090533f, 0); 
    instance.addEObj( "Oremound_2", 2001735, 0, 4161181, 4, { 318.346405f, 63.544731f, -200.930496f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sharpenedpickaxe", 2001371, 0, 3952079, 4, { 315.281891f, 62.935490f, -202.934906f }, 0.961304f, 1.229137f, 0); 
    instance.addEObj( "Oldhammer", 2001372, 0, 3952084, 4, { 324.421997f, 64.036842f, -247.028397f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Heavysledgehammer", 2001373, 0, 3952087, 4, { 291.432007f, 62.563419f, -228.564896f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( JustDeserts );