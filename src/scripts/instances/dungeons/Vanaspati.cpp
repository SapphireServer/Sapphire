#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Vanaspati : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Vanaspati() : Sapphire::ScriptAPI::InstanceContentScript( 83 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8864955, 4, { -376.172485f, 14.502600f, 105.058701f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -375.215912f, 14.502600f, 105.058701f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8864966, 4, { -383.422699f, 14.500000f, 66.780800f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8865013, 4, { -295.040588f, 41.000000f, -329.217499f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002587, 0, 4, { -295.832703f, 41.550289f, -328.444092f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8865021, 4, { -294.877502f, 41.500000f, -378.931610f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 8865091, 4, { 300.242493f, 56.192299f, -131.260300f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 299.957306f, 56.337181f, -130.419403f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8804089, 5, { -187.736496f, 1.446700f, 383.882111f }, 1.000000f, 0.757682f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -186.260498f, 1.365554f, 373.340912f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 300.747101f, 55.505829f, -176.064102f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Vanaspati );