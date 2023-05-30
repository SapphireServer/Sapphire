#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class EdensVerseRefulgence : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  EdensVerseRefulgence() : Sapphire::ScriptAPI::InstanceContentScript( 30094 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 8308967, 4, { 93.456909f, 0.000001f, 108.575699f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4g8_b1929", 2007457, 8340796, 4, { 100.000000f, 0.000000f, 100.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 84.018768f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8267752, 5, { 103.236702f, 0.000000f, 114.530701f }, 1.000000f, 0.000000f); 
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

EXPOSE_SCRIPT( EdensVerseRefulgence );