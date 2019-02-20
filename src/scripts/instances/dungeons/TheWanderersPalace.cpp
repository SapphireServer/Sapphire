#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheWanderersPalace :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWanderersPalace() :
    Sapphire::ScriptAPI::InstanceContentScript( 10 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2001809, 0, 4, { 134.115601f, -17.997431f, 473.641693f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 137.299393f, -17.990360f, 454.401398f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 73.105957f, 9.994568f, -475.590790f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 4177700, 5, { 130.745697f, -17.983120f, 461.438293f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_1", 2001822, 4086687, 4, { 125.014000f, -9.459579f, 64.149277f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2001811, 4259124, 4, { 127.094200f, -12.000000f, 125.826500f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0094", 2001810, 4259126, 4, { 124.986603f, -12.039370f, 125.401100f }, 0.991760f, 0.000048f ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2000277, 4259125, 4, { 125.461502f, -12.000000f, 89.079697f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2001114, 4323503, 4, { 118.000000f, -8.700125f, 65.370102f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2001823, 4323504, 4, { 117.995003f, -7.766907f, 65.232300f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Nymiandevice", 2001123, 4126926, 4, { 117.995003f, -9.001419f, 65.378754f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2002790, 4405761, 4, { 125.029999f, -13.277490f, 181.098602f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2001813, 4259128, 4, { 45.925018f, 0.000000f, -212.411499f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0094_1", 2001812, 4259127, 4, { 43.121960f, -0.015320f, -212.616592f }, 0.991760f, 0.000048f ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.registerEObj( "unknown_5", 2001824, 4086767, 4, { 43.140591f, 0.499020f, -29.383511f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2001827, 4086770, 4, { 43.011742f, 0.540422f, -152.602997f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2000278, 4259129, 4, { 43.493420f, -0.100058f, -248.056198f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2001115, 4323510, 4, { 35.000000f, 1.250271f, -5.876968f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2001116, 4323508, 4, { 35.000000f, 1.249865f, -28.099899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2001117, 4323512, 4, { 43.000000f, 1.300663f, -58.799179f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2001118, 4323515, 4, { 54.099178f, 9.249764f, -95.999512f }, 1.000000f, 1.570451f ); 
    instance.registerEObj( "unknown_11", 2001119, 4323518, 4, { 122.099899f, 1.250139f, -145.999405f }, 1.000000f, 1.570451f ); 
    instance.registerEObj( "unknown_12", 2001120, 4323522, 4, { 36.000000f, 1.299810f, -151.049896f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2001825, 4323511, 4, { 35.027500f, 2.231338f, -5.969540f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2001826, 4323509, 4, { 34.988789f, 2.301583f, -28.158291f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2001828, 4323513, 4, { 43.003689f, 2.351689f, -58.849869f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2001829, 4323516, 4, { 54.100830f, 10.258660f, -95.915703f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2001830, 4323519, 4, { 121.982201f, 2.305465f, -145.991302f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_18", 2001831, 4323523, 4, { 35.995869f, 2.276821f, -151.081100f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "RustedNymiandevice", 2001124, 4126931, 4, { 34.988892f, 0.930786f, -6.393555f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "RustedNymiandevice_1", 2001125, 4126938, 4, { 34.988892f, 0.930786f, -27.634159f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "RustedNymiandevice_2", 2001126, 4126941, 4, { 42.984619f, 0.991760f, -58.335270f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Nymiandevice_1", 2001127, 4126947, 4, { 53.613361f, 8.952527f, -95.999352f }, 1.000000f, 1.570451f ); 
    instance.registerEObj( "RustedNymiandevice_3", 2001128, 4126952, 4, { 121.629601f, 0.930786f, -146.013596f }, 0.991760f, 1.570451f ); 
    instance.registerEObj( "RustedNymiandevice_4", 2001129, 4126956, 4, { 35.995972f, 0.991760f, -150.591400f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Lanternoil", 2002789, 0, 4, { 35.621380f, -0.164260f, -23.125179f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2001832, 4086777, 4, { 73.005737f, 10.540420f, -380.487610f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_s1d3_bossline", 2001814, 4239448, 4, { 72.890900f, 9.976854f, -400.332489f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_s1d3_bosswall", 2001815, 4239449, 4, { 74.758614f, 9.976894f, -400.332489f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2001121, 4323530, 4, { 80.979607f, 11.245850f, -380.117493f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_21", 2001122, 4323528, 4, { 65.000000f, 11.249720f, -380.099792f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2001833, 4323531, 4, { 81.010132f, 12.313960f, -380.117493f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2001834, 4323529, 4, { 65.001831f, 12.381110f, -380.103790f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "RustedNymiandevice_5", 2001130, 4126964, 4, { 80.979607f, 10.940670f, -379.629211f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "RustedNymiandevice_6", 2001131, 4126966, 4, { 64.988159f, 10.940670f, -379.629211f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2005197, 5674883, 4, { 73.492577f, 6.000000f, -464.485596f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheWanderersPalace );