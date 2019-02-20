#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class InThalsName :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  InThalsName() :
    Sapphire::ScriptAPI::InstanceContentScript( 5006 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2004364, 0, 4, { -93.101089f, -13.129550f, 6.845694f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Companychest", 2000470, 4255822, 4, { 128.974701f, 5.067919f, -40.913502f }, 1.000000f, -0.343160f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( InThalsName );