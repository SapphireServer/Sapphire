#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheMinstrelsBalladShinryusDomain :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheMinstrelsBalladShinryusDomain() :
    Sapphire::ScriptAPI::InstanceContentScript( 20050 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 7034110, 5, { -21.048290f, -380.000092f, 1.297991f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 620.000000f, 20.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2007457, 7023869, 4, { -16.594919f, -380.000092f, -17.432211f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7023871, 4, { -0.213646f, -380.000092f, -17.432211f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7023870, 4, { 19.761841f, -380.000092f, -17.432211f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7023865, 4, { -16.594919f, -380.000092f, 0.746161f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 7023864, 4, { 20.591261f, -380.000092f, 1.852063f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7023866, 4, { -16.594919f, -380.000092f, 20.030439f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 7023868, 4, { 1.859938f, -380.000092f, 20.168671f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 7023867, 4, { 21.489799f, -380.000092f, 20.306919f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 7023863, 4, { 0.270193f, -380.000092f, 0.884399f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 7024624, 4, { -5.336151f, -380.000000f, 8.195240f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 7024837, 4, { 17.385090f, 620.000000f, -3.965453f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7024899, 4, { 15.077030f, 620.000000f, -79.248016f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7032157, 4, { 7.331779f, 620.000000f, 0.488136f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7032193, 4, { 9.743866f, 620.000000f, -5.475266f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2009049, 0, 4, { 20.000000f, 620.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2009065, 0, 4, { -0.015030f, 619.988770f, -6.068220f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2009073, 0, 4, { -20.000000f, 620.000000f, 0.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheMinstrelsBalladShinryusDomain );