#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EdensGateInundation : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EdensGateInundation() : Sapphire::ScriptAPI::InstanceContentScript( 30080 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 7945979, 5, { 100.000000f, 0.003474f, 115.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 88.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2007457, 7956562, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4g3_b1708", 2007457, 7962258, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 7956538, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( EdensGateInundation );