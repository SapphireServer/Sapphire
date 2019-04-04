#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class HellsKierExtreme :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HellsKierExtreme() :
    Sapphire::ScriptAPI::InstanceContentScript( 20058 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009599, 0, 4, { 98.496948f, -2.000000f, 103.288200f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2009600, 0, 4, { 101.619202f, -2.000000f, 103.096199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7537726, 4, { 99.992310f, 0.991760f, 99.992310f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_e3fe_b1521", 2007457, 7669820, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523", 2007457, 7679422, 4, { 100.000000f, 0.000000f, 92.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_1", 2007457, 7679423, 4, { 105.699997f, 0.000000f, 94.300003f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_2", 2007457, 7679424, 4, { 108.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_3", 2007457, 7679425, 4, { 105.699997f, 0.000000f, 105.699997f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_4", 2007457, 7679426, 4, { 100.000000f, 0.000000f, 108.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_5", 2007457, 7679427, 4, { 94.300003f, 0.000000f, 105.699997f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_6", 2007457, 7679428, 4, { 92.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fe_b1523_7", 2007457, 7679429, 4, { 94.300003f, 0.000000f, 94.300003f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Entrance", 2007457, 7591190, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, -0.000000f ); 
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

EXPOSE_SCRIPT( HellsKierExtreme );