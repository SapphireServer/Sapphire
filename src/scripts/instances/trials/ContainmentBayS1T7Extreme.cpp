#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ContainmentBayS1T7Extreme :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ContainmentBayS1T7Extreme() :
    Sapphire::ScriptAPI::InstanceContentScript( 20038 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_a2fd_b0818", 2006840, 6175219, 4, { 0.000000f, 0.000000f, -10.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_1", 2006841, 6175220, 4, { 7.071130f, 0.000000f, -7.071100f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_2", 2006842, 6175221, 4, { 10.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_3", 2006843, 6175222, 4, { 7.071130f, 0.000000f, 7.071130f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_4", 2006844, 6175223, 4, { 0.000000f, 0.000000f, 10.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_5", 2006845, 6175224, 4, { -7.071130f, 0.000000f, 7.071100f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_6", 2006846, 6175225, 4, { -10.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_7", 2006847, 6175226, 4, { -7.071130f, 0.000000f, -7.071130f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2006837, 6174136, 4, { 0.000000f, 0.052026f, -19.799999f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2006839, 6164929, 4, { 0.000000f, 0.002934f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2006838, 6171564, 4, { 0.116409f, 0.002934f, -0.768936f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2006840, 6175957, 4, { -0.836018f, 0.050520f, -2.055523f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_a2fd_b0818_8", 2006983, 6219989, 4, { 0.000000f, 0.043380f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6173855, 5, { -0.006781f, 0.052026f, 13.691250f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.500000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ContainmentBayS1T7Extreme );