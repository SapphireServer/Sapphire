#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Snowcloak :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Snowcloak() :
    Sapphire::ScriptAPI::InstanceContentScript( 27 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -25.554501f, 40.000000f, 65.525902f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 4729361, 4, { -29.985430f, 40.000000f, 65.539711f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "DoortoSilence", 2004203, 4680394, 4, { 57.114368f, 4.480070f, -45.937630f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004204, 4682554, 4, { 40.009041f, 0.491693f, -60.195160f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_r1d3_t2_ball1", 2004206, 4725471, 4, { 32.621071f, -4.715674f, -117.578201f }, 1.000000f, 0.000000f ); 
    // States -> s_ball_def (id: 2) s_ball_anim (id: 3) 
    instance.registerEObj( "sgbg_r1d3_t2_ball1_1", 2004206, 4731431, 4, { 5.652817f, -1.779197f, -107.755600f }, 1.000000f, 0.000000f ); 
    // States -> s_ball_def (id: 2) s_ball_anim (id: 3) 
    instance.registerEObj( "sgvf_r1d3_b0435", 2004208, 4895362, 4, { -30.982800f, -10.047770f, -162.841003f }, 1.000000f, 0.000000f ); 
    // States -> wind_sw_anim (id: 2) wind_def (id: 3) wind_strong (id: 6) wind_ws_anim (id: 7) 
    instance.registerEObj( "unknown_2", 2004209, 4685130, 4, { -39.827599f, -10.619430f, -155.585907f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_r1d3_b0435_1", 2004210, 4895363, 4, { -53.244961f, 3.577940f, -135.326797f }, 1.000000f, 0.000000f ); 
    // States -> wind_sw_anim (id: 2) wind_def (id: 3) wind_strong (id: 6) wind_ws_anim (id: 7) 
    instance.registerEObj( "unknown_3", 2004211, 4685137, 4, { -57.355659f, 4.520907f, -101.443703f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_r1d3_t2_ball1_2", 2004212, 4731432, 4, { -50.192619f, 6.129761f, -94.793358f }, 1.000000f, 0.000000f ); 
    // States -> s_ball_def (id: 2) s_ball_anim (id: 3) 
    instance.registerEObj( "sgvf_r1d3_b0435_2", 2004692, 5018298, 4, { 1.842873f, -9.975479f, -135.724899f }, 1.000000f, 0.000000f ); 
    // States -> wind_sw_anim (id: 2) wind_def (id: 3) wind_strong (id: 6) wind_ws_anim (id: 7) 
    instance.registerEObj( "unknown_4", 2004214, 4680578, 4, { -76.946297f, 28.400000f, -25.080601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2004215, 4680579, 4, { -76.355118f, 28.400000f, -0.768542f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2004216, 4680574, 4, { -71.720413f, 28.400000f, 2.866590f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2004217, 4680909, 4, { -59.031670f, 28.399969f, 6.586658f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2004218, 4680572, 4, { -46.184601f, 27.650000f, 1.393153f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2004219, 4680571, 4, { -41.333439f, 28.400000f, -9.966988f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2004220, 4680577, 4, { -81.969833f, 38.540291f, -11.185970f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2004221, 4680576, 4, { -82.257988f, 38.540291f, -0.033865f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2004222, 4680575, 4, { -73.807869f, 38.540279f, 8.961772f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2004223, 4680573, 4, { -44.264439f, 38.540291f, 9.105038f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "DoortoOblivion", 2004224, 4680395, 4, { -52.060501f, 40.000000f, 65.066193f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2002735, 0, 4, { 46.358002f, -2.246400f, -72.299896f }, 0.800000f, 0.554992f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 4725552, 4, { 48.054039f, -2.500000f, -74.312141f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2004205, 4725555, 4, { 59.417969f, -1.480164f, -102.836304f }, 0.991760f, 0.126302f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_r1d3_b0498", 2004577, 4982369, 4, { 44.252331f, -2.500000f, -89.438400f }, 1.000000f, 0.000000f ); 
    // States -> ring_off (id: 2) ring_off_anim (id: 3) ring_pop (id: 4) ring_pop_anim (id: 5) 
    instance.registerEObj( "unknown_15", 2002735, 0, 4, { -79.379898f, 10.614600f, -109.116402f }, 1.000000f, -1.195699f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 4725659, 4, { -83.147453f, 10.501150f, -112.069199f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2004213, 4725660, 4, { -107.265800f, 10.450760f, -103.052803f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Entrance", 2000182, 4725473, 5, { 116.416702f, -9.665442f, 114.240799f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 117.194199f, -11.854060f, 106.498703f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 18.403561f, 40.000000f, 67.026413f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Snowcloak );