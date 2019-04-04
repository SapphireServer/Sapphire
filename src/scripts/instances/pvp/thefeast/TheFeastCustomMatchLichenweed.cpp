#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFeastCustomMatchLichenweed :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFeastCustomMatchLichenweed() :
    Sapphire::ScriptAPI::InstanceContentScript( 40021 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007657, 6632432, 4, { -64.289970f, 8.262049f, 13.375790f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2007658, 6632431, 4, { 39.169922f, 8.194031f, -45.822941f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFeastCustomMatchLichenweed );