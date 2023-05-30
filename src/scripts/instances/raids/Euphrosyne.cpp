#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Euphrosyne : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Euphrosyne() : Sapphire::ScriptAPI::InstanceContentScript( 30125 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2010506, 0, 4, { -0.197918f, 90.000000f, -204.673706f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 9553523, 4, { -0.800713f, 90.000000f, -266.746613f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 9553485, 4, { 0.126350f, 90.000000f, -208.459702f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 72.173302f, 214.688400f, -681.670227f }, 2.200000f, -0.403255f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 9564225, 4, { 73.401833f, 214.688400f, -679.439026f }, 1.000000f, -0.244346f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -700.000000f, -942.150879f, 723.869385f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 9574616, 4, { -700.000000f, -942.150879f, 723.869385f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2010506, 0, 4, { 350.115387f, -845.665222f, 118.727699f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 9561209, 4, { 349.660889f, -845.791626f, 120.805199f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0286", 2007457, 9453570, 4, { -19.525551f, 95.000000f, -132.744598f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 800.000000f, -946.013611f, 730.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Frostwreathedportal", 2013210, 0, 4, { 50.000000f, 210.000000f, -769.539673f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2007457, 9635228, 4, { -788.968689f, -950.000000f, 788.013977f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Pedestalofpassage", 2013204, 0, 4, { -8.900000f, 95.000000f, -132.785004f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_1", 2013205, 0, 4, { -8.000000f, 130.000000f, -422.230988f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_2", 2013206, 0, 4, { 81.277603f, 214.951599f, -671.758484f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_3", 2013207, 0, 4, { -807.000000f, -950.000000f, 836.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_4", 2013208, 0, 4, { -693.000000f, -942.000000f, 732.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_5", 2013209, 0, 4, { 346.000000f, -846.000000f, 123.500000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Euphrosyne );