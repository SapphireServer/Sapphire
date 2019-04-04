#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ThePraetorium :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePraetorium() :
    Sapphire::ScriptAPI::InstanceContentScript( 16 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2000828, 4305694, 4, { -784.536987f, -344.000000f, 0.121873f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2000829, 0, 4, { -781.198120f, -344.000000f, 0.127798f }, 0.900000f, -1.570451f ); 
    instance.registerEObj( "Shortcut", 2000848, 0, 4, { -788.420593f, -400.046387f, -601.281189f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2000832, 4303065, 4, { -703.485413f, -185.734299f, 461.314697f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2000833, 4303324, 4, { -721.744019f, -185.531204f, 478.978302f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2000834, 4303325, 4, { -704.359924f, -185.731995f, 498.390015f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2000831, 0, 4, { -781.198120f, -344.000000f, 0.127800f }, 0.900000f, -1.570451f ); 
    instance.registerEObj( "unknown_5", 2002538, 0, 4, { -781.198120f, -344.000000f, 0.127800f }, 0.900000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2000828, 4305491, 4, { 212.974304f, 75.866501f, -0.668073f }, 1.000000f, 1.568613f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_6", 2000829, 0, 4, { 215.905304f, 76.000000f, -0.131676f }, 0.700000f, 1.568640f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2000822, 4305462, 4, { -135.017593f, -103.976402f, -1.129792f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2000823, 0, 4, { -129.654205f, -104.027000f, -0.290400f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2000826, 4305555, 4, { -216.218002f, -103.997398f, -3.836082f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_8", 2000827, 0, 4, { -208.879593f, -103.997398f, -0.252325f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "Shortcut_1", 2000848, 0, 4, { -577.757812f, -268.000000f, 218.871399f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w1d5_bossA_lvd_b0118", 2000876, 4317513, 4, { 180.458893f, 76.089233f, -0.360356f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_9", 2000976, 0, 4, { 180.548401f, 76.089943f, 0.959593f }, 1.000000f, -0.000248f ); 
    instance.registerEObj( "sgvf_w_btl_b0216", 2001134, 4326317, 4, { -166.447800f, -104.221901f, 16.976521f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2001135, 4326381, 4, { -196.318497f, -104.078903f, -0.786835f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_10", 2001766, 4175265, 4, { -570.270081f, -268.000000f, 217.461197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "仮シド指令", 2000806, 0, 4, { 217.957397f, 46.000000f, -11.597380f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal", 2000851, 0, 4, { 133.745193f, 22.964720f, -0.015320f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_1", 2000852, 0, 4, { 134.477707f, 7.614197f, -0.045776f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_2", 2000856, 0, 4, { 145.769394f, 21.988159f, 7.095398f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_11", 2000813, 0, 4, { 136.430801f, 22.354429f, -0.137390f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_3", 2000858, 0, 4, { 121.995796f, -104.020798f, 3.707886f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekarmor", 2000872, 0, 4, { 12.002250f, -107.811699f, -78.686447f }, 2.578735f, -1.562172f ); 
    instance.registerEObj( "Magitekarmor_1", 2000872, 0, 4, { 108.952103f, -106.029999f, -7.573757f }, 2.578735f, -0.369535f ); 
    instance.registerEObj( "unknown_12", 2000791, 4118536, 4, { 226.850998f, 155.775497f, 3.640267f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2000836, 4178897, 4, { 230.933899f, 156.818100f, 25.887810f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_4", 2000792, 0, 4, { 240.527893f, 155.626495f, 4.989798f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2000793, 4243244, 4, { 187.994705f, 152.227097f, -80.103348f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2000794, 4178131, 4, { 157.029907f, 155.725204f, -56.634510f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2000795, 4118533, 4, { 171.986206f, 160.259903f, -32.392151f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent06", 2000796, 4317691, 4, { 177.690002f, 155.500000f, -35.500401f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Imperialidentificationkey", 2000837, 0, 4, { 226.065094f, 155.807800f, 7.053694f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2000855, 4178132, 4, { 224.098007f, 156.000000f, -26.999870f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent04", 2000845, 4316977, 4, { 221.255707f, 156.000000f, 6.591867f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_5", 2001145, 4329956, 4, { 196.345398f, 186.275101f, -3.980006f }, 1.000000f, 0.000000f ); 
    // States -> ele_off (id: 10) ele_on (id: 11) 
    instance.registerEObj( "Magitekterminal_6", 2001146, 4329960, 4, { 196.312805f, 155.999893f, 4.083439f }, 1.000000f, 0.000000f ); 
    // States -> ele_off (id: 10) ele_on (id: 11) 
    instance.registerEObj( "Magitektransporter", 2001147, 0, 4, { 204.421494f, 120.000000f, -60.006229f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitektransporter_1", 2001148, 0, 4, { 228.831696f, 71.500000f, -28.156210f }, 1.000000f, 0.827528f ); 
    instance.registerEObj( "unknown_18", 2002628, 4305528, 4, { 221.126099f, 153.428696f, -69.269623f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2000871, 0, 4, { 174.414993f, 102.515198f, -88.973930f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2000797, 4118552, 4, { 227.155396f, 72.000000f, -43.219952f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2000798, 4119463, 4, { 190.957703f, 72.355438f, -64.773132f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_7", 2000799, 0, 4, { 268.474396f, 67.031410f, -49.967129f }, 0.991760f, -0.501567f ); 
    instance.registerEObj( "Imperialidentificationkey_1", 2000838, 0, 4, { 263.129395f, 66.381569f, -71.274437f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2000667, 4119461, 4, { 271.022614f, 68.049881f, -45.787529f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2000800, 4124814, 4, { 237.461395f, 72.250000f, 33.809959f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2000843, 4119464, 4, { 190.731094f, 67.877243f, -85.008949f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2000844, 0, 4, { 254.749405f, 72.098747f, -36.545410f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_8", 2000841, 0, 4, { 234.100006f, 72.101990f, -5.516209f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Imperialidentificationkey_2", 2000840, 0, 4, { 242.130798f, 72.250000f, 26.153481f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2000842, 4186210, 4, { 224.041794f, 75.715820f, -0.347510f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_9", 2000802, 4299253, 4, { 177.904907f, 76.066162f, -5.569580f }, 0.991760f, -0.010379f ); 
    instance.registerEObj( "Magitekterminal_10", 2000803, 0, 4, { 173.805496f, 76.081238f, 4.123073f }, 1.000000f, 0.729448f ); 
    instance.registerEObj( "unknown_27", 2000804, 4175899, 4, { 172.537292f, 76.600563f, -0.941921f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_11", 2000849, 0, 4, { 173.793900f, 47.632881f, 4.163035f }, 0.991760f, 0.694225f ); 
    instance.registerEObj( "unknown_28", 2001020, 4119459, 4, { 236.713104f, 68.589233f, 77.256348f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_29", 2001021, 4119458, 4, { 214.862198f, 47.531738f, 39.169922f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_transparent05", 2000877, 4317555, 4, { 178.867599f, 76.089233f, -0.117565f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent05_1", 2000878, 4317536, 4, { 168.665405f, 46.519169f, 1.801311f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2002629, 4305536, 4, { 241.707993f, 66.877907f, -82.835068f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_31", 2002630, 4305537, 4, { 112.046898f, 67.002319f, 46.555180f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_12", 2000805, 4299251, 4, { 167.034500f, 46.199989f, 8.192681f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2000811, 4175901, 4, { 149.577499f, 46.799969f, -30.579741f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2000807, 4309445, 4, { 146.929092f, 45.975342f, -50.736271f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Identificationkeyreader", 2000808, 4182427, 4, { 128.409805f, 47.799999f, -49.366180f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_13", 2000809, 4298905, 4, { 150.029999f, 46.723068f, -39.001339f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_14", 2000810, 0, 4, { 154.199600f, 46.894550f, -34.215000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2000812, 4119481, 4, { 208.043594f, 43.053101f, 0.003599f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Imperialidentificationkey_3", 2000839, 0, 4, { 155.484695f, 46.000000f, -57.763378f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_15", 2000850, 0, 4, { 154.192307f, 101.909103f, -34.226189f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Magitekterminal_16", 2000857, 0, 4, { 142.995895f, 46.047619f, -53.038639f }, 0.991760f, -0.743907f ); 
    instance.registerEObj( "Magitekarmor_2", 2000872, 0, 4, { 140.619904f, 102.000000f, -50.628609f }, 2.600000f, -0.817672f ); 
    instance.registerEObj( "Magitekterminal_17", 2000904, 4298910, 4, { 150.108398f, 102.204201f, -39.998730f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent05_2", 2000879, 4317581, 4, { 145.143005f, 46.118488f, -33.631050f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent05_3", 2000880, 4317584, 4, { 144.416595f, 102.000000f, -35.715260f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_35", 2002539, 4323543, 4, { 191.892395f, 46.000000f, -42.993431f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_36", 2001205, 0, 4, { 134.810394f, 21.910000f, -0.001021f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_37", 2001205, 0, 4, { 133.078400f, -102.979202f, 0.123506f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekarmor_3", 2000872, 0, 4, { 129.111298f, 68.261063f, -59.929440f }, 2.578735f, -0.094404f ); 
    instance.registerEObj( "unknown_38", 2000815, 4190796, 4, { 81.888397f, -107.400002f, -45.959042f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent05_4", 2000816, 4323560, 4, { 38.618160f, -107.400002f, -72.955917f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_39", 2000817, 4190794, 4, { 37.580742f, -107.400002f, -70.481018f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_transparent05_5", 2000819, 4323562, 4, { -38.041451f, -103.786201f, 0.069122f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_40", 2000818, 4200594, 4, { -31.718330f, -103.400002f, 2.561740f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_41", 2000820, 4190789, 4, { -31.696360f, -103.400002f, -2.409777f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_42", 2000821, 4189149, 4, { -68.916000f, -102.759399f, -0.015143f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_43", 2000824, 4119565, 4, { -184.609695f, -104.221901f, -2.135104f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Magitekterminal_18", 2000825, 0, 4, { -238.152893f, -104.051300f, -19.744539f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_44", 2000854, 4119564, 4, { -117.637398f, -103.993301f, 0.252331f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut_2", 2000853, 0, 4, { -228.197906f, -103.997398f, 0.789458f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_transparent05_6", 2000814, 4323557, 4, { 84.611214f, -107.408302f, -51.255131f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_45", 2001138, 4125125, 4, { -249.059494f, -104.000000f, -3.238936f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut_3", 2000846, 0, 4, { -788.508728f, -344.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut_4", 2000847, 0, 4, { -788.751892f, -344.014587f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "PortaDecumanaentryway", 2001045, 0, 4, { -792.387329f, -343.440887f, -0.126096f }, 1.500000f, -1.570451f ); 
    instance.registerEObj( "sgbg_w1d5_q6_lift2", 2001139, 4328790, 4, { -765.431274f, -343.997589f, 1.749690f }, 1.000000f, 0.000000f ); 
    // States -> down_Ncut (id: 58) arrival_Ncut (id: 59) upstairs (id: 61) gate1_open (id: 62) gate1_close (id: 63) gate2_open (id: 64) gate2_close (id: 65) start (id: 66) stop (id: 67) ele_off (id: 72) ele_on (id: 73) down_Ncut_hide (id: 74) hide (id: 75) 
    instance.registerEObj( "unknown_46", 2000787, 0, 4, { 147.015701f, 186.100006f, -4.199400f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000788, 0, 4, { -721.074524f, -185.731598f, 478.324890f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut_5", 2000789, 0, 4, { 167.870895f, 186.000000f, -0.104399f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000790, 4301608, 5, { 152.054794f, 187.039200f, 3.392751f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut_6", 2000789, 0, 4, { -237.161896f, -104.020897f, -21.575460f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut_7", 2000789, 0, 4, { 115.949501f, 67.588867f, -74.186333f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ThePraetorium );