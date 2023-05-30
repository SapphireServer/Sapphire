#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AnotherSildihnSubterraneSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AnotherSildihnSubterraneSavage() : Sapphire::ScriptAPI::InstanceContentScript( 37002 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -335.000000f, 470.999908f, -125.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9323292, 4, { -335.000000f, 471.181610f, -125.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9326752, 4, { -35.000000f, 521.004028f, -250.179993f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -35.019470f, 520.988770f, -250.202194f }, 1.480042f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 9349222, 5, { -334.928589f, 470.995789f, -43.165600f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Aetherialflow", 2013163, 9349249, 4, { -335.000000f, 470.999908f, -155.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Aetherialflow_1", 2013164, 9392045, 4, { -35.000000f, 521.004028f, -271.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 288.942200f, 533.000000f, -129.683701f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -340.347595f, 471.020996f, -48.584969f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AnotherSildihnSubterraneSavage );