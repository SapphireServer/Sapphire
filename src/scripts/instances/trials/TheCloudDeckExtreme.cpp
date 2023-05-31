#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheCloudDeckExtreme : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheCloudDeckExtreme() : Sapphire::ScriptAPI::InstanceContentScript( 20076 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 8662834, 5, { 79.942421f, -0.015320f, 115.666298f }, 0.991760f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 80.000000f, 0.000000f, 88.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2011582, 0, 4, { 120.295700f, 5.151336f, 104.953003f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2011478, 0, 4, { 83.590973f, 0.000000f, 85.957649f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheCloudDeckExtreme );