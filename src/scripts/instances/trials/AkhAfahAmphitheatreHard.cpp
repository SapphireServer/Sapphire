#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AkhAfahAmphitheatreHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AkhAfahAmphitheatreHard() : Sapphire::ScriptAPI::InstanceContentScript( 20024 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2004238, 4772738, 4738623, 4, { -1.210436f, 0.000000f, -0.715586f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_r1fc_b0472", 2004239, 4797573, 4738624, 4, { 1.181316f, -0.000000f, 1.563968f }, 1.000000f, 0.000000f, 0); 
    // States -> wind_def (id: 2) wind_def_anim (id: 3) wind_pop (id: 4) wind_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471", 2004240, 4841629, 4841628, 4, { 11.000000f, 0.000000f, -11.000000f }, 1.000000f, 0.793709f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471_1", 2004349, 4841631, 4841634, 4, { 12.811310f, -0.000000f, 9.376424f }, 1.000000f, 0.000000f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471_2", 2004350, 4841632, 4841635, 4, { -8.033875f, 0.000000f, 10.406790f }, 1.000000f, 0.000000f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "sgvf_r1fc_b0471_3", 2004351, 4841633, 4841636, 4, { -8.319038f, -0.000001f, -10.997720f }, 1.000000f, 0.000000f, 0); 
    // States -> magi_def (id: 2) magi_def_anim (id: 3) magi_pop (id: 4) magi_pop_anim (id: 5) 
    instance.addEObj( "Entrance", 2000182, 4738599, 4738602, 5, { 9.717670f, 0.000000f, 14.522430f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 4738604, 4, { 0.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AkhAfahAmphitheatreHard );