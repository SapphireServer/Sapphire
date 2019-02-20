#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class DomaCastle :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DomaCastle() :
    Sapphire::ScriptAPI::InstanceContentScript( 54 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002872, 6889640, 4, { -239.375000f, 67.999496f, -175.164597f }, 0.991760f, 1.326264f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2007791, 0, 4, { -240.158905f, 67.039032f, -177.843399f }, 0.750000f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_1", 2007457, 6889642, 4, { -241.910706f, 67.000000f, -215.185699f }, 1.000000f, 1.326214f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2007457, 6794570, 4, { 287.722412f, 21.499981f, 115.300598f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6739699, 4, { 262.936493f, 21.500010f, 110.142799f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 6777815, 4, { 261.315491f, 25.500010f, -10.943810f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6851198, 4, { 248.248901f, 20.000000f, 78.568604f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2007457, 6928399, 4, { 264.958405f, 24.750000f, 121.939598f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 6952007, 4, { 285.857391f, 24.500000f, 90.541313f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2007457, 6973643, 4, { 189.428497f, 36.749840f, 50.824680f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6735489, 4, { 33.135330f, 40.000000f, 88.297363f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6679193, 4, { -183.423004f, 44.000000f, 125.024200f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6735529, 4, { -193.153900f, 46.551128f, 128.625107f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_11", 2007457, 6732692, 4, { -240.779297f, 64.000023f, -93.377197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 6732698, 4, { -240.802704f, 66.000023f, -140.615494f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2007457, 6880936, 4, { -243.716507f, 48.000000f, 37.417641f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 6739904, 4, { -239.397202f, 45.467159f, 60.631378f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 6901296, 4, { -239.515396f, 44.299999f, 93.293831f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007457, 6928755, 4, { -243.442398f, 56.000000f, -37.595749f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_2", 2002872, 6889553, 4, { 148.284103f, 41.499981f, 20.913610f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_17", 2007791, 0, 4, { 145.028793f, 40.575001f, 21.644630f }, 1.000000f, -1.335177f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_3", 2007457, 6889570, 4, { 110.384399f, 41.489140f, 13.189620f }, 0.991760f, 0.063599f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0250_4", 2002872, 6889631, 4, { -222.430801f, 45.500000f, 129.655899f }, 0.991760f, -0.233408f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_18", 2007791, 0, 4, { -219.254501f, 45.500000f, 130.342697f }, 1.000000f, -1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250_5", 2007457, 6889633, 4, { -242.418503f, 45.500000f, 113.102501f }, 1.000000f, -0.233499f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Entrance", 2000182, 6881291, 5, { 341.375793f, 13.500000f, 180.479599f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 336.598785f, 16.739140f, 178.515305f }, 0.991760f, 0.158242f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -239.781799f, 67.000000f, -212.105698f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( DomaCastle );