#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class InterdimensionalRift :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  InterdimensionalRift() :
    Sapphire::ScriptAPI::InstanceContentScript( 5023 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_z3o1_b1212", 2007457, 6944598, 4, { -14.915330f, -256.500000f, 385.545197f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3o1_b1212_1", 2007457, 6944604, 4, { -280.000000f, -239.750000f, 196.500000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_z3o1_b1212_2", 2007457, 6944605, 4, { -255.313797f, -226.000000f, -187.394394f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z3o1_b1212_3", 2007457, 6944606, 4, { -246.604706f, -226.000000f, -192.211807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000046, 0, 4, { 843.573914f, 427.000000f, 948.472290f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit_1", 2000046, 0, 4, { -207.965302f, -224.000000f, -147.401306f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_0", 2007457, 6889957, 4, { 1.846330f, -271.700012f, 428.457886f }, 0.991760f, 0.000049f ); 
    instance.registerEObj( "Matterrelocationdevice", 2008501, 6938814, 4, { -16.956310f, -256.250000f, 382.407898f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_z3o1_a1_cub01", 2007457, 6954336, 4, { -7.878613f, -256.250000f, 385.557495f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Matterrelocationdevice_1", 2000048, 6938826, 4, { -286.946014f, -239.764999f, 192.797699f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( InterdimensionalRift );