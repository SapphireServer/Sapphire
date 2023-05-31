#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EdensGateSepultureSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EdensGateSepultureSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30085 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7943876, 4, { 100.174500f, 0.488514f, 103.262299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 7943871, 4, { 100.174500f, 0.488514f, 103.262299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 7943877, 4, { 100.174500f, 0.488514f, 103.262299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 7943870, 4, { 100.174500f, 0.488514f, 103.262299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 7972914, 4, { 100.000000f, 5.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 7943146, 4, { 100.174500f, 0.488514f, 103.262299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 7943004, 4, { 100.174500f, 0.488514f, 103.262299f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 7963739, 5, { 96.182877f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EdensGateSepultureSavage );