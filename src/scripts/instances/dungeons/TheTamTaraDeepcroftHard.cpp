#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheTamTaraDeepcroftHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTamTaraDeepcroftHard() : Sapphire::ScriptAPI::InstanceContentScript( 24 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2001085, 0, 4660134, 4, { -68.771881f, 15.144450f, -3.840616f }, 0.539465f, 1.095248f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4660133, 4710025, 4, { -67.088028f, 14.657070f, -5.210713f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2004286, 4745117, 4753843, 4, { -60.778740f, 14.055000f, -22.019831f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2004287, 4745111, 4753844, 4, { -42.778549f, 14.055000f, -12.943500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2004288, 4745124, 4753845, 4, { -48.035992f, 14.055000f, -5.265638f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004289, 4745125, 4753846, 4, { -57.996319f, 14.055000f, -5.661358f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2004290, 4745126, 4753847, 4, { -59.234348f, 14.055000f, -15.781390f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2004291, 4745127, 4753848, 4, { -50.008671f, 14.055000f, -22.601339f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_w_lvd_void01_large", 2004285, 4867481, 4867475, 4, { -55.031620f, 14.055000f, 5.443754f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_1", 2004285, 4867482, 4867476, 4, { -41.704861f, 14.055000f, 2.969403f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_2", 2004285, 4867483, 4867477, 4, { -33.780270f, 14.055000f, -9.729918f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_3", 2004285, 4867484, 4867478, 4, { -39.301521f, 14.055000f, -26.615370f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_4", 2004285, 4867485, 4867479, 4, { -55.347961f, 14.055000f, -30.450310f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_5", 2004285, 4867486, 4867480, 4, { -65.834686f, 14.055000f, -19.944820f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4660142, 4709988, 4, { 19.425310f, 16.400459f, 72.640419f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2004084, 4660138, 4709989, 4, { 47.314381f, 16.403030f, 108.679100f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_7", 2002735, 0, 4710001, 4, { 20.629601f, 16.280300f, 75.420700f }, 1.000000f, 0.688908f, 0); 
    instance.addEObj( "unknown_8", 2002735, 0, 4710008, 4, { 88.048500f, 22.493870f, -21.533701f }, 1.000000f, -0.001870f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 4660145, 4710018, 4, { 88.376717f, 21.338551f, -19.283840f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgpl_w_lvd_void01_large_6", 2004285, 4771300, 4752993, 4, { 84.103310f, 22.101000f, -58.390091f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_7", 2004285, 4771301, 4752994, 4, { 96.234253f, 22.101000f, -56.482040f }, 1.000000f, 0.723667f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_8", 2004285, 4771302, 4752995, 4, { 105.255798f, 22.101000f, -44.764778f }, 1.000000f, 1.518654f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_9", 2004285, 4771303, 4752996, 4, { 102.038200f, 22.101000f, -32.837021f }, 1.000000f, 0.857277f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_10", 2004285, 4771304, 4752997, 4, { 91.888603f, 22.101000f, -25.882389f }, 1.000000f, -0.007381f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_11", 2004285, 4771305, 4752998, 4, { 80.039169f, 22.101000f, -26.985500f }, 1.000000f, -0.690998f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_12", 2004285, 4771306, 4752999, 4, { 71.290688f, 22.101000f, -37.049461f }, 1.000000f, -1.482906f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "sgpl_w_lvd_void01_large_13", 2004285, 4771307, 4753000, 4, { 71.819580f, 22.079769f, -49.945210f }, 0.991760f, -0.798114f, 0); 
    // States -> vfx_on (id: 47) vfx_off (id: 48) 
    instance.addEObj( "Tornfolio", 2004297, 0, 4757535, 4, { -47.454521f, 44.378349f, -68.195801f }, 0.991760f, -1.194174f, 0); 
    instance.addEObj( "Tornfolio_1", 2004298, 0, 4757536, 4, { -11.833840f, 29.549919f, -15.995260f }, 1.000000f, 1.058869f, 0); 
    instance.addEObj( "Tornfolio_2", 2004299, 0, 4757537, 4, { -28.185230f, 24.286421f, 20.665119f }, 0.991760f, -0.909425f, 0); 
    instance.addEObj( "Tornfolio_3", 2004300, 0, 4757538, 4, { 72.129387f, 16.396311f, 132.066803f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tornfolio_4", 2004301, 0, 4757539, 4, { 80.744392f, 16.907101f, 57.719940f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tornfolio_5", 2004302, 0, 4757540, 4, { 147.103104f, 18.005850f, 69.150192f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tornfolio_6", 2004303, 0, 4757541, 4, { -147.644699f, 15.900680f, 113.328697f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_9", 2004086, 4656964, 4695644, 4, { -7.602334f, 30.454849f, -18.853220f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004088, 4656965, 4695645, 4, { -20.840630f, 24.342739f, 19.409069f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_f1d6_lvd_barr1", 2004087, 4671678, 4695646, 4, { 11.105700f, 29.275560f, -8.141251f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 4) vfx_off (id: 5) 
    instance.addEObj( "sgbg_f1d6_barr2", 2004089, 4671683, 4695647, 4, { -6.673915f, 23.630680f, 39.042259f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 5) vfx_off (id: 6) 
    instance.addEObj( "sgbg_f1d6_barr1", 2004093, 4671679, 4695649, 4, { 74.836761f, 16.445829f, 108.252800f }, 1.000000f, 0.000000f, 0); 
    // States -> vfx_on (id: 4) vfx_off (id: 5) 
    instance.addEObj( "sgbg_f1d6_barr1_1", 2004094, 4671680, 4695650, 4, { 100.083900f, 17.257870f, 47.440189f }, 0.991760f, 0.000048f, 0); 
    // States -> vfx_on (id: 4) vfx_off (id: 5) 
    instance.addEObj( "Defiledcoffin", 2004090, 4695648, 4695651, 4, { 78.676689f, 17.793221f, 150.248901f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_moya_on (id: 3) vf_moya_off (id: 5) vf_moya_off2 (id: 6) 
    instance.addEObj( "Defiledcoffin_1", 2004091, 4671204, 4695652, 4, { 72.424454f, 18.387079f, 48.386349f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_moya_on (id: 3) vf_moya_off (id: 5) vf_moya_off2 (id: 6) 
    instance.addEObj( "Defiledcoffin_2", 2004092, 4668899, 4695653, 4, { 146.684906f, 17.990360f, 69.562866f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_moya_on (id: 3) vf_moya_off (id: 5) vf_moya_off2 (id: 6) 
    instance.addEObj( "Aetherialflow", 2004095, 4696055, 4696056, 4, { 96.409500f, 22.100000f, -49.506569f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2004099, 0, 4695670, 4, { -85.344437f, 15.048210f, 7.188452f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2004096, 4656966, 4695672, 4, { -89.972237f, 14.236630f, 16.250851f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_13", 2004097, 4656967, 4695674, 4, { -97.824608f, 14.083040f, 2.446555f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_f1b6_b0446", 2004098, 4660132, 4695675, 4, { -89.234444f, 13.859010f, 8.573526f }, 1.000000f, 0.000000f, 0); 
    // States -> mayu_on (id: 2) mayu_off (id: 3) mayu_off_anim (id: 4) 
    instance.addEObj( "Exit", 2000139, 0, 4660156, 4, { -42.771080f, 14.067750f, -17.288521f }, 0.991789f, 0.000144f, 0); 
    instance.addEObj( "Entrance", 2000182, 4660224, 4660225, 5, { -57.606178f, 49.507038f, -142.170105f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 4660154, 4, { -57.755428f, 47.653931f, -120.622597f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheTamTaraDeepcroftHard );