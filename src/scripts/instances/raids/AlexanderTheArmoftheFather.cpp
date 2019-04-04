#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheArmoftheFather :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheArmoftheFather() :
    Sapphire::ScriptAPI::InstanceContentScript( 30023 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005400, 0, 4, { 39.638931f, -9.000000f, -67.173187f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2005314, 5878653, 4, { 17.839520f, 42.000000f, 14.681990f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_d2a3_wall", 2005314, 6048829, 4, { 17.839520f, 42.000000f, 14.681990f }, 1.000000f, 0.000000f ); 
    // States -> wall_on (id: 24) wall_off (id: 25) 
    instance.registerEObj( "unknown_2", 2006094, 5864098, 4, { 58.027489f, -0.000134f, -20.193150f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 58.000000f, -0.000003f, -20.943159f }, 0.600000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5787963, 4, { 58.043961f, -0.000054f, -20.107550f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.941902f, -10.500000f, -63.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2002872, 0, 4, { 87.814133f, -9.000000f, -61.109859f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2005911, 5814854, 4, { 58.000000f, -8.999999f, -63.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_d2a2_b0721", 2006095, 5905878, 4, { 58.000000f, -9.000000f, -63.000000f }, 1.000000f, 0.000000f ); 
    // States -> thunder_off (id: 2) thunder_on2off (id: 3) thunder_on (id: 4) thunder_off2on (id: 5) 
    instance.registerEObj( "Entrance", 2000182, 5787948, 5, { -0.015320f, -0.015320f, 43.037189f }, 0.778198f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 3.252589f, 0.000000f, 30.523800f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2000182, 5911899, 5, { 58.000000f, -0.000049f, -11.175000f }, 0.800000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgpl_w_lvd_colwithnavi", 2000608, 5911895, 4, { 58.000000f, 0.841694f, -1.705941f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheArmoftheFather );