#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlphascapeV10Savage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlphascapeV10Savage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30073 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7575331, 4, { 96.398201f, 0.000000f, 100.555702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7575332, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7575333, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7575334, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 7586460, 4, { 101.415100f, -0.000000f, 101.219002f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2007457, 7574103, 5, { 105.000000f, 0.000000f, 115.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 85.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7575443, 4, { 100.300003f, 0.000000f, 100.300003f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlphascapeV10Savage );