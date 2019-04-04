#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CapeWestwind :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CapeWestwind() :
    Sapphire::ScriptAPI::InstanceContentScript( 20007 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Exit", 2000605, 0, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000606, 3861081, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000604, 4262798, 5, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f, 0.000000f ); 
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

EXPOSE_SCRIPT( CapeWestwind );