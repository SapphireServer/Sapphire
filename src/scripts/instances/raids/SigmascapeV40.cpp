#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SigmascapeV40 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SigmascapeV40() :
    Sapphire::ScriptAPI::InstanceContentScript( 30062 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgbg_z3oa_a0_gmc01", 2007457, 7307403, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_0", 2008982, 0, 4, { -0.015320f, -0.015320f, -0.015320f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2008978, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2008979, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2008980, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_4", 2008981, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_5", 2008976, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_6", 2008977, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_z3oa_b1351", 2007457, 7296769, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_7", 2000051, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_8", 2000052, 0, 4, { 0.000000f, 0.000000f, -5.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_9", 2008626, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_10", 2008627, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_11", 2008629, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_12", 2008630, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_13", 2006821, 0, 4, { -0.015320f, -0.015320f, -0.015320f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 7181990, 5, { 0.000000f, 0.000000f, 14.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -16.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SigmascapeV40 );