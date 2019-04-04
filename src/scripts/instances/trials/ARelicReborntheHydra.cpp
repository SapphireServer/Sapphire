#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ARelicReborntheHydra :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ARelicReborntheHydra() :
    Sapphire::ScriptAPI::InstanceContentScript( 20020 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 4600269, 5, { -245.383194f, 17.225630f, 16.103081f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -279.773407f, 17.233170f, 19.434681f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2001609, 0, 4, { 241.292603f, 11.057950f, 9.784212f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2001649, 4097866, 5, { 238.950500f, 9.900879f, -1.209344f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit_1", 2001610, 4097973, 4, { -280.512299f, 17.240601f, 20.057501f }, 1.000000f, 0.000000f ); 
    // States -> vf_htras1_on (id: 2) vf_htras1_of (id: 3) 
    instance.registerEObj( "sgvf_w_lvd_b0094", 2001611, 4097992, 4, { 19.113859f, 0.900208f, 98.170502f }, 0.991760f, 0.000048f ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2001612, 4098036, 4, { 17.948280f, 0.925217f, 99.310219f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0094_1", 2001613, 4098064, 4, { -120.074501f, -5.801239f, -111.402496f }, 1.000000f, 0.000000f ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2001614, 4098077, 4, { -121.598503f, -5.727614f, -112.049599f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0094_2", 2001615, 4098237, 4, { -228.286301f, 17.565599f, 16.208900f }, 1.000000f, 0.000048f ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2001616, 4098241, 4, { -229.136703f, 17.565599f, 16.208900f }, 1.000000f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2001618, 4014394, 4, { 29.098881f, 1.785278f, 130.418793f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Aetherialflow", 2001619, 0, 4, { 32.968849f, 3.815735f, 131.179199f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2001620, 2815987, 4, { 120.471397f, -0.516086f, -57.500610f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2001621, 4098194, 4, { -95.942581f, -9.659227f, -101.942596f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2001622, 4043181, 4, { -94.468628f, -2.151611f, -68.864014f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Ludusdoor", 2001623, 4005252, 4, { -172.249695f, 12.559910f, 12.742130f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Chainwinch", 2001624, 4016950, 4, { 74.518059f, -10.988300f, -107.067703f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Chainwinch_1", 2001625, 4016951, 4, { 42.154171f, -10.941640f, -84.664078f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Chainwinch_2", 2001626, 4016952, 4, { 17.515020f, -10.957320f, -190.023102f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Chainwinch_3", 2001627, 4016953, 4, { -39.127491f, -11.066550f, -129.097504f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Chainwinch_4", 2001628, 4016954, 4, { -82.474548f, -10.952540f, -113.137199f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2001634, 4082420, 4, { -129.441193f, 9.833186f, -0.625334f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2001635, 3629276, 4, { -3.044897f, 0.927666f, 144.884506f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2001636, 3629274, 4, { 27.769211f, 0.954134f, 166.929398f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2001637, 3629277, 4, { 69.039284f, 0.968122f, 137.080902f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2001638, 4016486, 4, { -19.781490f, 2.187618f, 152.349899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2001639, 4016487, 4, { 24.469919f, 2.233563f, 180.853195f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2001640, 4016488, 4, { 89.225769f, 2.247621f, 140.072006f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2001641, 4018090, 4, { -277.600494f, 17.568609f, 40.599701f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2001642, 4018091, 4, { -255.703506f, 17.578291f, 47.590672f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2001643, 4018092, 4, { -237.108002f, 17.604349f, 38.970459f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2001644, 4018089, 4, { -279.140015f, 17.555901f, -2.742105f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2001645, 4018088, 4, { -261.194214f, 17.568060f, -11.064940f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2001646, 4018087, 4, { -239.163101f, 17.568661f, -4.435994f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Aetherialflow_1", 2001647, 4103310, 4, { -177.996506f, -14.694460f, -133.043503f }, 0.991760f, 0.000048f ); 
    // States -> tornade_off (id: 2) tornade_on (id: 3) 
    instance.registerEObj( "unknown_18", 2001648, 4105956, 4, { -171.435196f, -14.633480f, -127.946999f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_19", 2001650, 0, 4, { -230.125793f, 17.157061f, 16.380630f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 242.225601f, 9.970665f, -11.333600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2001712, 0, 4, { -131.216003f, 10.073990f, -1.326215f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2000210, 0, 4, { -256.084503f, 17.537910f, 17.740490f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ARelicReborntheHydra );