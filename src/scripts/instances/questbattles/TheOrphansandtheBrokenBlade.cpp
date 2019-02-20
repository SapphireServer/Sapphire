#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheOrphansandtheBrokenBlade :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheOrphansandtheBrokenBlade() :
    Sapphire::ScriptAPI::InstanceContentScript( 5019 )
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

EXPOSE_SCRIPT( TheOrphansandtheBrokenBlade );