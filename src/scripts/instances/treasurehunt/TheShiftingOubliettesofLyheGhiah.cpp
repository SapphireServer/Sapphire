#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheShiftingOubliettesofLyheGhiah : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheShiftingOubliettesofLyheGhiah() : Sapphire::ScriptAPI::InstanceContentScript( 55008 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8508139, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2007457, 8510189, 4, { 100.000000f, -0.293948f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 8509432, 4, { 100.000000f, -0.293948f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8313642, 4, { 100.000000f, -0.293948f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 8509433, 4, { 100.000000f, -0.293948f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Arcanesphere", 2009598, 8508147, 4, { 100.000000f, -0.266413f, 108.947601f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8302294, 4, { 100.000000f, 18.916941f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8301591, 4, { 99.992310f, -0.259039f, 81.986687f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8301586, 4, { 108.995102f, -0.259039f, 84.397583f }, 0.991760f, 0.523599f); 
    instance.registerEObj( "unknown_7", 2007457, 8301582, 4, { 115.588501f, -0.259041f, 91.000023f }, 1.000000f, 1.047197f); 
    instance.registerEObj( "unknown_8", 2007457, 8301590, 4, { 118.000000f, -0.259039f, 99.993797f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "unknown_9", 2007457, 8301583, 4, { 115.588501f, -0.259047f, 109.000000f }, 1.000000f, 1.047197f); 
    instance.registerEObj( "unknown_10", 2007457, 8301587, 4, { 109.000000f, -0.259041f, 115.588501f }, 1.000000f, 0.523599f); 
    instance.registerEObj( "unknown_11", 2007457, 8301592, 4, { 100.000000f, -0.259039f, 118.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 8301593, 4, { 90.999977f, -0.259047f, 115.588501f }, 1.000000f, -0.523599f); 
    instance.registerEObj( "unknown_13", 2007457, 8301584, 4, { 84.411530f, -0.259041f, 109.000000f }, 1.000000f, -1.047197f); 
    instance.registerEObj( "unknown_14", 2007457, 8301589, 4, { 81.999977f, -0.259039f, 99.993790f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "unknown_15", 2007457, 8301585, 4, { 84.411537f, -0.259047f, 91.000000f }, 1.000000f, -1.047197f); 
    instance.registerEObj( "unknown_16", 2007457, 8301588, 4, { 91.000000f, -0.259041f, 84.411537f }, 1.000000f, -0.523599f); 
    instance.registerEObj( "unknown_17", 2009602, 0, 4, { 100.000000f, -0.293948f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_18", 2007457, 0, 4, { 100.000000f, -0.293948f, 100.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheShiftingOubliettesofLyheGhiah );