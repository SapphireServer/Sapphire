#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HeavenonHighFloors6170 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HeavenonHighFloors6170() :
    Sapphire::ScriptAPI::InstanceContentScript( 60027 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0959", 2000608, 7375355, 4, { -300.897095f, 0.442359f, -324.271790f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_on2off (id: 4) vf_bextwall_off (id: 10) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HeavenonHighFloors6170 );