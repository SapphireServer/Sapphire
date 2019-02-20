#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFaceofTrueEvil :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFaceofTrueEvil() :
    Sapphire::ScriptAPI::InstanceContentScript( 5010 )
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

EXPOSE_SCRIPT( TheFaceofTrueEvil );