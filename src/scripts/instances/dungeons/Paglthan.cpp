#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Paglthan : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Paglthan() : Sapphire::ScriptAPI::InstanceContentScript( 77 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8665745, 4, { -540.000000f, 0.000000f, 145.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -540.000000f, 0.000000f, 145.000397f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8665764, 4, { -500.000000f, 0.000000f, 145.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8682383, 4, { -175.000000f, -25.059500f, 58.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -175.000000f, -25.059500f, 58.750000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8628238, 4, { -165.000000f, -25.000000f, 27.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8638394, 4, { 775.846130f, -56.979500f, -97.505699f }, 1.000000f, -1.570796f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 775.846130f, -56.979500f, -97.505699f }, 1.000000f, 1.562061f); 
    instance.registerEObj( "unknown_4", 2011467, 8506564, 4, { -736.690308f, 5.966248f, 215.442093f }, 0.991760f, 0.850671f); 
    instance.registerEObj( "unknown_5", 2007457, 8506579, 4, { -596.931274f, -0.007685f, 138.764496f }, 1.000000f, 1.221731f); 
    instance.registerEObj( "unknown_6", 2007457, 8459734, 4, { -376.028687f, -10.319310f, 203.657593f }, 1.000000f, -0.631267f); 
    instance.registerEObj( "unknown_7", 2007457, 8507863, 4, { -324.495300f, -10.280260f, 180.994293f }, 1.000000f, 1.570796f); 
    instance.registerEObj( "unknown_8", 2007457, 8507864, 4, { -192.487305f, -21.655430f, 100.836197f }, 1.000000f, 1.518437f); 
    instance.registerEObj( "unknown_9", 2007457, 8507870, 4, { 752.925903f, -55.500172f, -101.029999f }, 0.991760f, 1.570451f); 
    instance.registerEObj( "Dragon", 2011493, 0, 4, { -71.244400f, -24.887501f, -23.453100f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Dragon_1", 2011494, 0, 4, { -69.352287f, -24.887510f, -17.227421f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Dragon_2", 2011495, 0, 4, { -70.176300f, -24.887501f, -10.147300f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Dragon_3", 2011496, 0, 4, { -72.709297f, -24.948601f, -3.708000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 8638184, 5, { -829.000000f, 2.803500f, 277.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -820.232727f, 3.070385f, 271.821899f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 812.500000f, -57.118500f, -97.494469f }, 1.000000f, -1.570451f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Paglthan );