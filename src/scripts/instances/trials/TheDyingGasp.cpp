#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDyingGasp : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDyingGasp() : Sapphire::ScriptAPI::InstanceContentScript( 20066 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7924648, 4, { 91.611221f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 7951241, 4, { 91.611221f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 7956688, 4, { 93.150467f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 7941539, 4, { 91.611221f, 0.000000f, 108.424103f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2010408, 0, 4, { 88.010696f, -24.822630f, 102.827003f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2010409, 0, 4, { 85.725616f, -24.822630f, 91.427147f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 7968294, 4, { 98.017128f, -0.000000f, 98.795761f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8034946, 4, { 91.119682f, 0.000000f, 95.498703f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8034947, 4, { 91.119682f, 0.000000f, 95.498703f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.000000f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 7958675, 5, { 97.074989f, -0.000000f, 115.178299f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "ExittotheTempest", 2010602, 0, 4, { 100.000397f, 1.000000f, 119.366699f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2010236, 0, 4, { 100.038200f, 0.000000f, 106.007599f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PortaltotheOcular", 2013423, 0, 4, { 100.038101f, 0.000000f, 96.391632f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheDyingGasp );