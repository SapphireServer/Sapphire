#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CastrumMeridianum : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CastrumMeridianum() : Sapphire::ScriptAPI::InstanceContentScript( 15 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0250", 2000593, 4249703, 4249706, 4, { -67.576859f, 70.350082f, -36.382999f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2000594, 0, 4249707, 4, { -72.778549f, 70.163177f, -38.339291f }, 1.000000f, 1.406840f, 0); 
    instance.addEObj( "Magitekmissile", 2000662, 0, 4302698, 4, { -108.687798f, 70.343590f, -8.558592f }, 1.400000f, -0.605074f, 0); 
    instance.addEObj( "Magitekmissile_1", 2000663, 0, 4302699, 4, { -116.665100f, 70.390266f, -53.063919f }, 1.400000f, -0.849513f, 0); 
    instance.addEObj( "unknown_1", 2001149, 0, 4330367, 4, { -72.778549f, 70.163177f, -38.339291f }, 1.000000f, 1.406839f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2000591, 4249720, 4249717, 4, { -25.465830f, 83.385536f, -254.529602f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2000592, 0, 4249719, 4, { -25.038260f, 81.798767f, -248.906296f }, 1.100000f, 0.000000f, 0); 
    instance.addEObj( "Imperialidentificationkey", 2000870, 0, 4323068, 4, { -67.439163f, 81.798767f, -231.079102f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2000588, 0, 4249692, 4, { 34.634392f, 71.755402f, -45.910198f }, 0.900000f, 1.543478f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2000587, 4249693, 4249701, 4, { 36.526970f, 70.598427f, -46.207680f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Imperialidentificationkey_1", 2000869, 0, 4323067, 4, { -7.280443f, 69.781212f, 27.170691f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2000590, 0, 4249716, 4, { -7.938801f, 70.550377f, 55.590679f }, 1.100000f, -0.213036f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2000589, 4249713, 4249714, 4, { -5.998041f, 70.281548f, 58.349812f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Searchlightterminal", 2000564, 3169670, 4248120, 4, { 213.829102f, 89.024597f, -107.133797f }, 1.000000f, 1.045186f, 0); 
    // States -> blue_on (id: 4) red_on (id: 5) white_on (id: 6) 
    instance.addEObj( "sgbg_w_emp_015_01a", 2000565, 4204866, 4248223, 4, { 210.588501f, 88.962471f, -106.430901f }, 0.991760f, 0.000048f, 0); 
    // States -> blue_on (id: 5) red_on (id: 6) light_off (id: 7) 
    instance.addEObj( "Shortcut", 2000603, 0, 4256176, 4, { 242.256302f, 87.579422f, -95.018204f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Disposalchute", 2000597, 0, 4248289, 4, { 40.790581f, 71.410004f, -11.781850f }, 0.991760f, 1.191010f, 0); 
    instance.addEObj( "unknown_5", 2000860, 3168876, 4312442, 4, { 197.143005f, 92.716309f, -155.744797f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2000861, 3168877, 4312444, 4, { 211.024704f, 89.452042f, -70.152588f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Searchlightterminal_1", 2000873, 4317191, 4317198, 4, { 206.509399f, 90.986397f, -79.219772f }, 1.000000f, 1.466079f, 0); 
    // States -> blue_on (id: 4) red_on (id: 5) white_on (id: 6) 
    instance.addEObj( "unknown_7", 2000566, 4204867, 4248314, 4, { -62.804321f, 72.657097f, 180.368805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Searchlightterminal_2", 2000567, 4204869, 4248354, 4, { -71.896492f, 74.742790f, 151.474503f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2000569, 4204871, 4248521, 4, { 1.863623f, 71.927399f, 89.175919f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Unstablepaneling", 2000571, 3956106, 4248550, 4, { 95.737846f, 64.963051f, 103.147400f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2000573, 3149745, 4248553, 4, { 93.090912f, 66.531853f, 117.642097f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2000572, 4065604, 4248556, 4, { 83.071327f, 60.587688f, 116.300903f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Unstablepaneling_1", 2000574, 3956104, 4248609, 4, { 104.309601f, 64.941147f, 67.240013f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2000575, 4065628, 4248615, 4, { 93.616432f, 60.529831f, 51.407162f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2000576, 3149747, 4248621, 4, { 101.933800f, 66.905586f, 52.199631f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2000577, 3642024, 4248885, 4, { 20.799950f, 70.334259f, 4.277452f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2000862, 3149816, 4312445, 4, { -77.378540f, 78.416023f, 130.266205f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Incendiary#37", 2000570, 0, 4248547, 4, { 109.141098f, 64.757690f, 62.367512f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Incendiary#37_1", 2001113, 0, 4323049, 4, { 124.726898f, 64.689621f, 62.085869f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2001206, 0, 4333775, 4, { 104.233803f, 66.103699f, 68.343483f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2001205, 0, 4333776, 4, { 95.566910f, 66.188728f, 101.984398f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2000578, 3642033, 4249187, 4, { 5.540902f, 70.172447f, -68.735893f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2000586, 3169187, 4249475, 4, { -84.639374f, 86.075699f, -294.635010f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Magitekterminal", 2000582, 0, 4249481, 4, { -62.063919f, 69.259163f, -89.851593f }, 1.500000f, 0.261981f, 0); 
    instance.addEObj( "Magitekterminal_1", 2000583, 0, 4249484, 4, { -43.080639f, 69.331673f, -84.657654f }, 1.480042f, 0.271375f, 0); 
    instance.addEObj( "unknown_19", 2000584, 3642010, 4249486, 4, { -53.516090f, 69.940781f, -85.333992f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2000863, 3169178, 4312446, 4, { 31.803410f, 83.652863f, -168.188904f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Searchlightterminal_3", 2000568, 4204872, 4248391, 4, { 24.724890f, 77.701874f, -154.365402f }, 0.991760f, 0.795709f, 0); 
    // States -> blue_on (id: 4) red_on (id: 5) white_on (id: 6) 
    instance.addEObj( "sgbg_w_emp_015_01a_1", 2000874, 4317259, 4317261, 4, { 10.967040f, 74.960777f, -139.438599f }, 1.000000f, 0.000000f, 0); 
    // States -> blue_on (id: 5) red_on (id: 6) light_off (id: 7) 
    instance.addEObj( "unknown_21", 2001136, 4265914, 4328169, 4, { -18.308630f, 81.798767f, -204.730896f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2001160, 4200584, 4332661, 4, { 5.338250f, 70.502319f, -87.827461f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2001159, 4200444, 4332660, 4, { 21.572090f, 70.516617f, 9.031565f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "MarkXLIIIantiaircraftcannon", 2000595, 0, 4249683, 4, { -66.151108f, 69.594437f, -20.559780f }, 0.991760f, 1.356260f, 0); 
    instance.addEObj( "MarkXLIIIantiaircraftcannon_1", 2000600, 0, 4250311, 4, { -70.083420f, 69.122810f, -65.019180f }, 0.991760f, 0.891590f, 0); 
    instance.addEObj( "MarkXLIIIantiaircraftcannon_2", 2000601, 0, 4250312, 4, { -44.756939f, 67.998627f, -39.293011f }, 0.991760f, 1.490808f, 0); 
    instance.addEObj( "unknown_24", 2000865, 3169123, 4312448, 4, { -27.982929f, 79.754509f, -48.873550f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2000865, 3284996, 4312451, 4, { -19.120440f, 79.754509f, -11.464200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Searchlightterminal_4", 2000580, 4204877, 4249464, 4, { -26.230459f, 79.754509f, -42.167561f }, 0.991760f, 1.557559f, 0); 
    // States -> blue_on (id: 4) red_on (id: 5) white_on (id: 6) 
    instance.addEObj( "Searchlightterminal_5", 2000581, 4265903, 4249465, 4, { -23.853939f, 79.754509f, -15.348020f }, 0.991760f, 0.000048f, 0); 
    // States -> blue_on (id: 4) red_on (id: 5) white_on (id: 6) 
    instance.addEObj( "sgbg_w_emp_015_01a_2", 2000875, 4317262, 4317264, 4, { -45.087860f, 67.998833f, -39.263939f }, 1.000000f, 0.000000f, 0); 
    // States -> blue_on (id: 5) red_on (id: 6) light_off (id: 7) 
    instance.addEObj( "Entrance", 2000562, 4247977, 4248000, 5, { 257.286194f, 87.030891f, -99.538628f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_26", 2000563, 0, 4248056, 4, { 260.508087f, 86.897049f, -89.411842f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2000596, 0, 4249681, 4, { -121.432404f, 70.350082f, -28.426470f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CastrumMeridianum );