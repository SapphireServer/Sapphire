#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheBurdenoftheSonSavage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheBurdenoftheSonSavage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30037 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 10.705920f, -21.985399f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2006984, 6164617, 4, { -0.231898f, 10.500000f, -1.988388f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_d2a8_b0882", 2006989, 6234571, 4, { 0.000000f, 10.500000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2006974, 0, 4, { -16.291439f, 10.500000f, 4.361944f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit_1", 2005313, 6076667, 4, { 0.000000f, 10.500000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6177907, 5, { 0.000000f, 10.500000f, 19.500000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheBurdenoftheSonSavage );