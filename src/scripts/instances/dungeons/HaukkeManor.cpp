#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HaukkeManor : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HaukkeManor() : Sapphire::ScriptAPI::InstanceContentScript( 6 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "Voidlamp", 2000366, 3873151, 3632950, 4, { 19.527651f, 17.000000f, 22.036671f }, 0.991789f, 0.785398f, 0); 
    // States -> vf_slamp_on (id: 6) vf_slamp_of (id: 12) 
    instance.addEObj( "Voidlamp_1", 2000367, 3873152, 3632951, 4, { -24.524000f, 16.999901f, 22.023741f }, 1.000000f, -0.785398f, 0); 
    // States -> vf_slamp_on (id: 6) vf_slamp_of (id: 12) 
    instance.addEObj( "Voidlamp_2", 2000368, 3873153, 3632952, 4, { 19.541849f, 16.999950f, -13.996940f }, 1.000000f, 0.785398f, 0); 
    // States -> vf_slamp_on (id: 6) vf_slamp_of (id: 12) 
    instance.addEObj( "Voidlamp_3", 2000369, 3873154, 3632953, 4, { -24.503330f, 16.999889f, -14.014120f }, 1.000000f, -0.785398f, 0); 
    // States -> vf_slamp_on (id: 6) vf_slamp_of (id: 12) 
    instance.addEObj( "Exit", 2000370, 0, 3632954, 4, { -2.517786f, 16.952730f, 21.011629f }, 0.930753f, 0.000240f, 0); 
    instance.addEObj( "unknown_0", 2000371, 0, 3633032, 4, { 81.895119f, 0.228838f, -0.106860f }, 0.900235f, 0.000336f, 0); 
    instance.addEObj( "Tinykey", 2000302, 0, 3633090, 4, { 71.396912f, -0.001627f, 28.641140f }, 0.869717f, 0.932147f, 0); 
    instance.addEObj( "Tinykey_1", 2000303, 0, 3633091, 4, { -26.322651f, -0.005771f, 50.722679f }, 0.778163f, -0.528574f, 0); 
    instance.addEObj( "Tinykey_2", 2000304, 0, 3633092, 4, { -52.424351f, -0.002903f, 22.515909f }, 0.930753f, 0.987942f, 0); 
    instance.addEObj( "Tinykey_3", 2000305, 0, 3633093, 4, { -68.498917f, -16.795919f, -8.967492f }, 0.869717f, 1.115077f, 0); 
    instance.addEObj( "Tinykey_4", 2000306, 0, 3633094, 4, { -46.234051f, -18.800501f, 38.557331f }, 0.900235f, 0.549108f, 0); 
    instance.addEObj( "Tinykey_5", 2000307, 0, 3633097, 4, { 14.015370f, -18.796499f, -43.227589f }, 0.900235f, 0.868678f, 0); 
    instance.addEObj( "Tinykey_6", 2000308, 0, 3633101, 4, { -11.804590f, -18.800249f, -50.647060f }, 0.991789f, 0.312732f, 0); 
    instance.addEObj( "Lockeddoor", 2000329, 3457073, 3633134, 4, { 0.509394f, 0.143553f, 56.976101f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Lockeddoor_1", 2000331, 3457076, 3633136, 4, { -16.586599f, 0.172088f, 84.043991f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Lockeddoor_2", 2000337, 3457070, 3633142, 4, { -48.657558f, 0.174862f, -36.017189f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Lockeddoor_3", 2000338, 3457071, 3633144, 4, { -48.701061f, 0.167371f, 36.007271f }, 0.930753f, 0.000240f, 0); 
    instance.addEObj( "Lockeddoor_4", 2000339, 3457083, 3633146, 4, { -25.116051f, -18.616779f, -34.637550f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Lockeddoor_5", 2000343, 3457090, 3633152, 4, { -1.899940f, -18.615101f, 34.620899f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Lockeddoor_6", 2000344, 3457093, 3633154, 4, { 25.192600f, -18.692350f, 34.531120f }, 0.930753f, 0.000240f, 0); 
    instance.addEObj( "IvyDoor", 2000355, 3457081, 3633175, 4, { -48.382030f, 0.425044f, -0.015306f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "CarnationDoor", 2000356, 3457082, 3633176, 4, { -25.558910f, -18.570280f, -0.076342f }, 0.930753f, 0.000240f, 0); 
    instance.addEObj( "LilyDoor", 2000357, 3449005, 3633179, 4, { 22.842710f, 17.196871f, -0.015306f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_1", 2001080, 0, 3873516, 4, { 22.000000f, 17.000000f, 0.000000f }, 0.575000f, -1.570451f, 0); 
    instance.addEObj( "unknown_2", 2001236, 3852702, 3909524, 4, { 24.498400f, 0.449216f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sealedbarrier", 2001233, 3909497, 3909543, 4, { 46.699810f, 9.875019f, -0.253856f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_baria1_off (id: 3) vf_baria_on (id: 6) 
    instance.addEObj( "Yellowkey", 2000325, 0, 3633129, 4, { -12.348700f, -18.803230f, 52.290878f }, 1.000000f, -0.839410f, 0); 
    instance.addEObj( "Lockeddoor_7", 2000345, 3457077, 3633158, 4, { 16.464439f, 17.135830f, 84.153458f }, 0.930753f, 0.000240f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0094", 2001604, 4103506, 4103515, 4, { -23.510660f, -0.000664f, 0.588553f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgvf_w_lvd_b0118", 2001605, 4103511, 4103516, 4, { -23.446470f, -0.000633f, -0.525669f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0094_1", 2001606, 4103508, 4103520, 4, { -24.734859f, -18.800381f, 0.630995f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgpl_w_lvd_b0118_f1d2", 2001607, 4103512, 4103522, 4, { -24.765221f, -18.800400f, -0.546668f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Entrance", 2000182, 4143756, 4143749, 5, { 73.330597f, 0.000000f, 0.000000f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Greenkey", 2000324, 0, 3633128, 4, { 1.500000f, 0.007936f, -0.000000f }, 0.961271f, 0.638080f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HaukkeManor );