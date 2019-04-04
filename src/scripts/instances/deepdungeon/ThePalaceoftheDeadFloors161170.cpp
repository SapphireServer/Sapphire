#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ThePalaceoftheDeadFloors161170 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ThePalaceoftheDeadFloors161170() :
    Sapphire::ScriptAPI::InstanceContentScript( 60017 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0959", 2000608, 6534547, 4, { -301.179504f, 0.130118f, -301.014709f }, 1.000000f, -0.000000f ); 
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

EXPOSE_SCRIPT( ThePalaceoftheDeadFloors161170 );