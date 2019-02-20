#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SigmascapeV40Savage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SigmascapeV40Savage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30066 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {

  }

  void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SigmascapeV40Savage );