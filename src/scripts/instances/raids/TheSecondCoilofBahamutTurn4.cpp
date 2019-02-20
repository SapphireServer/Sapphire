#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSecondCoilofBahamutTurn4 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSecondCoilofBahamutTurn4() :
    Sapphire::ScriptAPI::InstanceContentScript( 30010 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2003412, 0, 4, { -1.586798f, 0.000000f, 6.322940f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2003413, 4592650, 4, { 0.246630f, 0.000000f, -0.575616f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2003414, 4596280, 4, { 2.330916f, 0.000000f, 1.675908f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2003411, 4585907, 4, { -0.036626f, -0.000000f, -0.514996f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2003392, 4632812, 4, { 0.000000f, -0.000002f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2003393, 0, 4, { 16.296391f, -0.000002f, -4.751545f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2003394, 0, 4, { 11.781120f, -0.000001f, 4.780689f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2003391, 0, 4, { 8.938168f, 0.060000f, -11.440830f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_btl_b0427", 2003427, 4664504, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    // States -> on (id: 2) off (id: 3) 
    instance.registerEObj( "Entrance", 2000182, 4614314, 5, { -0.059309f, -0.000001f, 15.090750f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Allaganterminal", 2003419, 4682784, 4, { -15.104980f, 0.572263f, -27.316570f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2003452, 4615853, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2003678, 4663755, 4, { 16.207529f, 0.571903f, 28.091551f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSecondCoilofBahamutTurn4 );