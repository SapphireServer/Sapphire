#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CloudNine : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CloudNine() : Sapphire::ScriptAPI::InstanceContentScript( 40032 )
  { }

  void onInit( InstanceContent& instance ) override
  {

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CloudNine );