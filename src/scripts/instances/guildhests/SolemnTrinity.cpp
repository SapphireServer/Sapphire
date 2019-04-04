#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SolemnTrinity :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SolemnTrinity() :
    Sapphire::ScriptAPI::InstanceContentScript( 10014 )
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

EXPOSE_SCRIPT( SolemnTrinity );