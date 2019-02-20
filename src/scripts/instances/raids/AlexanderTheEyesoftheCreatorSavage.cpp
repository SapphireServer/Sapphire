#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheEyesoftheCreatorSavage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheEyesoftheCreatorSavage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30043 )
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

EXPOSE_SCRIPT( AlexanderTheEyesoftheCreatorSavage );