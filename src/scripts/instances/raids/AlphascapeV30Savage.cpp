#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlphascapeV30Savage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlphascapeV30Savage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30075 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009609, 0, 4, { 92.761772f, 0.000000f, 106.354897f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009610, 0, 4, { 93.034180f, -0.015320f, 106.645302f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2007457, 7604877, 4, { 103.128403f, 0.000000f, 107.047600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7624116, 4, { 105.371498f, 0.000000f, 104.860802f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2009653, 0, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2007457, 7593474, 5, { 104.466499f, 0.000000f, 114.605797f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlphascapeV30Savage );