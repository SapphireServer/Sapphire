#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheShiftingAltarsofUznair :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheShiftingAltarsofUznair() :
    Sapphire::ScriptAPI::InstanceContentScript( 55004 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 7598712, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2007457, 7610562, 4, { 100.000000f, 0.100000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7610560, 4, { 100.000000f, 0.100000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7623148, 4, { 100.000000f, 0.100000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7610561, 4, { 100.000000f, 0.100000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Arcanesphere", 2009598, 7621803, 4, { 100.000000f, 0.084079f, 108.947601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 7575335, 4, { 100.000000f, 18.916941f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7541027, 4, { 99.999992f, -0.000000f, 82.000008f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 7541023, 4, { 109.000000f, 0.000000f, 84.411560f }, 1.000000f, 0.523599f ); 
    instance.registerEObj( "unknown_7", 2007457, 7541029, 4, { 115.588501f, 0.000000f, 91.000023f }, 1.000000f, 1.047197f ); 
    instance.registerEObj( "unknown_8", 2007457, 7541025, 4, { 118.000000f, 0.000000f, 99.993782f }, 1.000000f, 1.570451f ); 
    instance.registerEObj( "unknown_9", 2007457, 7541030, 4, { 115.588501f, 0.000000f, 109.000000f }, 1.000000f, 1.047197f ); 
    instance.registerEObj( "unknown_10", 2007457, 7541031, 4, { 109.000000f, -0.000000f, 115.588501f }, 1.000000f, 0.523599f ); 
    instance.registerEObj( "unknown_11", 2007457, 7541026, 4, { 100.000000f, -0.000000f, 118.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7541028, 4, { 91.000000f, -0.000000f, 115.588501f }, 1.000000f, -0.523599f ); 
    instance.registerEObj( "unknown_13", 2007457, 7541032, 4, { 84.411537f, -0.000000f, 109.000000f }, 1.000000f, -1.047197f ); 
    instance.registerEObj( "unknown_14", 2007457, 7541034, 4, { 82.000000f, 0.000000f, 99.993782f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_15", 2007457, 7541033, 4, { 84.411537f, 0.000000f, 91.000000f }, 1.000000f, -1.047197f ); 
    instance.registerEObj( "unknown_16", 2007457, 7541024, 4, { 91.000000f, -0.000000f, 84.411537f }, 1.000000f, -0.523599f ); 
    instance.registerEObj( "unknown_17", 2009602, 0, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_18", 2007457, 7541112, 4, { 100.000000f, 0.100000f, 100.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheShiftingAltarsofUznair );