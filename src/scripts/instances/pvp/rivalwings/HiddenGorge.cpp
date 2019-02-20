#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HiddenGorge :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HiddenGorge() :
    Sapphire::ScriptAPI::InstanceContentScript( 51002 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7677877, 4, { 99.992310f, 16.299459f, 89.982422f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2007457, 7677876, 4, { 100.000000f, 16.299459f, -110.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7677878, 4, { -100.000000f, 16.299500f, 110.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7677879, 4, { -100.000000f, 16.299459f, -90.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Steamcannon", 2009040, 0, 4, { 121.355103f, 19.959841f, -0.442573f }, 0.991760f, 0.785458f ); 
    instance.registerEObj( "Steamcannon_1", 2009041, 0, 4, { 121.392403f, 19.999960f, -19.606091f }, 1.000000f, 0.785398f ); 
    instance.registerEObj( "Steamcannon_2", 2009032, 0, 4, { -121.390701f, 20.005421f, 0.356093f }, 0.991760f, -0.785362f ); 
    instance.registerEObj( "Steamcannon_3", 2009033, 0, 4, { -121.391502f, 20.000010f, 19.612690f }, 1.000000f, -0.785398f ); 
    instance.registerEObj( "Hangarterminal", 2009035, 7553226, 4, { -189.989395f, 16.493401f, 34.331669f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "Hangarterminal_1", 2009062, 7553225, 4, { -189.969498f, 16.519770f, -14.365560f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "Hangarterminal_2", 2009063, 7558250, 4, { 189.990799f, 16.518669f, -34.362301f }, 0.991760f, 1.570451f ); 
    instance.registerEObj( "Hangarterminal_3", 2009064, 7558251, 4, { 189.993805f, 16.299999f, 13.374650f }, 1.000000f, 1.570451f ); 
    instance.registerEObj( "Ceruleumtank", 2009031, 0, 4, { 0.000000f, 18.434999f, 0.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HiddenGorge );