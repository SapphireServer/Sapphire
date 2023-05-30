#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheStigmaDreamscape : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheStigmaDreamscape() : Sapphire::ScriptAPI::InstanceContentScript( 79 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8805253, 4, { -144.000000f, 684.000000f, -110.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -144.000000f, 684.000000f, -110.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8805980, 4, { 0.000000f, -712.000000f, 20.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 0.000000f, -712.000000f, 20.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8806564, 4, { 0.000000f, -4.000000f, 25.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 0.000000f, -4.000000f, 25.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Teleportationconstruct", 2011703, 8871143, 4, { -144.000000f, 685.000000f, -154.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Teleportationconstruct_1", 2011704, 8871214, 4, { 0.000000f, -711.000000f, -15.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -4.000000f, -21.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0095_fly", 2007457, 8805117, 4, { -44.000000f, 742.000000f, 355.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -44.000000f, 742.000000f, 352.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheStigmaDreamscape );