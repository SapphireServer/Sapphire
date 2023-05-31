#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ThePhantomsFeast : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePhantomsFeast() : Sapphire::ScriptAPI::InstanceContentScript( 25003 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Aetherialflow", 2011615, 8756087, 4, { -9.300000f, 30.829100f, -16.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aetherialflow_1", 2011616, 8756093, 4, { 466.234985f, 19.271021f, -64.283958f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aetherialflow_2", 2011617, 8756106, 4, { 415.799988f, 16.410801f, 69.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aetherialflow_3", 2011618, 8756118, 4, { 70.202812f, 23.770479f, 4.961242f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8734191, 5, { -55.998619f, 49.509418f, -141.762100f }, 0.991760f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2011851, 0, 4, { -41.500000f, 14.047740f, -19.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2012682, 0, 4, { -58.100151f, 49.141178f, -136.111893f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8883380, 4, { 474.880890f, 22.100000f, -55.221199f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8883381, 4, { 488.188995f, 22.100000f, -21.553499f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 474.880890f, 22.100000f, -55.221199f }, 1.000000f, -0.785398f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8883399, 4, { 445.880707f, 16.283739f, 105.467697f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 8883400, 4, { 420.864807f, 16.283701f, 75.341499f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 445.880798f, 16.283739f, 105.467697f }, 1.000000f, -0.698132f); 
    instance.registerEObj( "Exquisitedish", 2011934, 0, 4, { 430.929901f, 16.281309f, 90.897949f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Standarddish", 2011935, 0, 4, { 434.129486f, 16.283739f, 87.909691f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 8883414, 4, { -68.482002f, 14.048400f, -3.891300f }, 0.991760f, -1.079090f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -68.481979f, 14.048400f, -3.891297f }, 1.000000f, -1.079090f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ThePhantomsFeast );