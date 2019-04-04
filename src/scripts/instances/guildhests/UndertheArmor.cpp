#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class UndertheArmor :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  UndertheArmor() :
    Sapphire::ScriptAPI::InstanceContentScript( 10002 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( UndertheArmor );