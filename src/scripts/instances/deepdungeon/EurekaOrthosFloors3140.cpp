#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EurekaOrthosFloors3140 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EurekaOrthosFloors3140() : Sapphire::ScriptAPI::InstanceContentScript( 60034 )
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

EXPOSE_SCRIPT( EurekaOrthosFloors3140 );