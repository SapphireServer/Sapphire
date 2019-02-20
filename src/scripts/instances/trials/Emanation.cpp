#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Emanation :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Emanation() :
    Sapphire::ScriptAPI::InstanceContentScript( 20048 )
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

EXPOSE_SCRIPT( Emanation );