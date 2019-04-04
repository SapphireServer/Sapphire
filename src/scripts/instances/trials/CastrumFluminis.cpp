#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CastrumFluminis :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CastrumFluminis() :
    Sapphire::ScriptAPI::InstanceContentScript( 20055 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 7345082, 5, { 100.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 87.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404", 2007457, 7391200, 4, { 100.000000f, 0.000001f, 84.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_1", 2007457, 7391209, 4, { 116.000000f, 0.000001f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_2", 2007457, 7391210, 4, { 84.000000f, 0.000001f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_3", 2007457, 7391212, 4, { 111.313698f, 0.000000f, 88.686287f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_4", 2007457, 7391214, 4, { 88.686302f, 0.000000f, 111.313698f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_5", 2007457, 7391215, 4, { 88.686287f, 0.000000f, 88.686287f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_6", 2007457, 7391217, 4, { 100.000000f, 0.000001f, 109.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_7", 2007457, 7398352, 4, { 100.000000f, 0.000001f, 84.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_8", 2007457, 7398353, 4, { 116.000000f, 0.000001f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_9", 2007457, 7398354, 4, { 111.313698f, 0.000000f, 88.686287f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_10", 2007457, 7398355, 4, { 88.686302f, 0.000000f, 111.313698f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_e3fd_b1404_11", 2007457, 7398356, 4, { 100.000000f, 0.000001f, 109.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2007457, 7393493, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CastrumFluminis );