#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheLostCanalsofUznair :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheLostCanalsofUznair() :
    Sapphire::ScriptAPI::InstanceContentScript( 55002 )
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

EXPOSE_SCRIPT( TheLostCanalsofUznair );