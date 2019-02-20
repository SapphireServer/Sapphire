#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheBattleonBekko :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheBattleonBekko() :
    Sapphire::ScriptAPI::InstanceContentScript( 5012 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2008480, 6894787, 4, { 564.783630f, -60.304729f, -136.444901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004541, 0, 4, { 800.087585f, 0.000000f, 44.317749f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheBattleonBekko );