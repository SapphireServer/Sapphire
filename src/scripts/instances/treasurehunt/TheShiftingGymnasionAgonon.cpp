#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheShiftingGymnasionAgonon : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheShiftingGymnasionAgonon() : Sapphire::ScriptAPI::InstanceContentScript( 55011 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 9413509, 5, { 100.000000f, -0.300000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, -0.300000f, 85.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1886", 2007457, 9510564, 4, { 100.000000f, -0.300000f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_0", 2007457, 9562810, 4, { 100.000000f, -0.300000f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 9445285, 4, { 100.000000f, -0.300000f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 9562811, 4, { 100.000000f, -0.300000f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Arcanesphere", 2009598, 9413557, 4, { 100.000000f, -0.300000f, 108.947601f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 9445284, 4, { 100.000000f, -0.300004f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 9415088, 4, { 99.992310f, -0.300000f, 81.986687f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 9415091, 4, { 108.995102f, -0.300000f, 84.397583f }, 0.991760f, 0.523599f); 
    instance.registerEObj( "unknown_6", 2007457, 9415092, 4, { 115.588402f, -0.300000f, 91.000023f }, 1.000000f, 1.047197f); 
    instance.registerEObj( "unknown_7", 2007457, 9415094, 4, { 118.000000f, -0.300000f, 99.993797f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "unknown_8", 2007457, 9415095, 4, { 115.588501f, -0.300000f, 109.000000f }, 1.000000f, 1.047198f); 
    instance.registerEObj( "unknown_9", 2007457, 9415096, 4, { 109.000000f, -0.300000f, 115.588501f }, 1.000000f, 0.523599f); 
    instance.registerEObj( "unknown_10", 2007457, 9415097, 4, { 99.999901f, -0.300000f, 118.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 9415098, 4, { 90.999878f, -0.300000f, 115.588501f }, 1.000000f, -0.523599f); 
    instance.registerEObj( "unknown_12", 2007457, 9415099, 4, { 84.411430f, -0.300000f, 109.000000f }, 1.000000f, -1.047197f); 
    instance.registerEObj( "unknown_13", 2007457, 9415100, 4, { 81.999977f, -0.300000f, 99.993790f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "unknown_14", 2007457, 9415101, 4, { 84.411453f, -0.300000f, 91.000000f }, 1.000000f, -1.047197f); 
    instance.registerEObj( "unknown_15", 2007457, 9415102, 4, { 90.999924f, -0.300000f, 84.411537f }, 1.000000f, -0.523599f); 
    instance.registerEObj( "unknown_16", 2009602, 0, 4, { 100.000000f, -0.300001f, 100.000000f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheShiftingGymnasionAgonon );