#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class PullingPoisonPosies :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  PullingPoisonPosies() :
    Sapphire::ScriptAPI::InstanceContentScript( 10005 )
  { }

  void onInit( InstanceContent& instance ) override
  {

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( PullingPoisonPosies );