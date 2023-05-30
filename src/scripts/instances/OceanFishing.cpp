#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class OceanFishing : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  OceanFishing() : Sapphire::ScriptAPI::InstanceContentScript( 63017 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0286", 2007457, 9908415, 4, { 0.000000f, 6.750146f, -4.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OceanFishing );