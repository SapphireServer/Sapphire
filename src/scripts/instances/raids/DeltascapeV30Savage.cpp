#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class DeltascapeV30Savage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DeltascapeV30Savage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30055 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Matterrelocationdevice", 2008501, 6913059, 4, { 230.975693f, 231.836197f, -19.028080f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_0", 2007457, 6792212, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6847573, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6848219, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z3o4_a1_mto01", 2007457, 6953156, 4, { 250.000000f, 250.995605f, 0.000000f }, 1.000000f, -0.000000f ); 
    // States -> mete_hide (id: 19) mete_pre (id: 20) mete_phase_1 (id: 21) mete_phase_2 (id: 22) mete_phase_3 (id: 23) mete_phase_4 (id: 24) mete_fade (id: 25) mete_phase_5 (id: 26) 
    instance.registerEObj( "unknown_3", 2007457, 6929138, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6847577, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 6853325, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 6853774, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 6846630, 4, { -15.000000f, 0.000001f, 15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6846632, 4, { -5.000000f, 0.000000f, 15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6846634, 4, { 5.000000f, 0.000000f, 15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6846637, 4, { 15.000000f, 0.000000f, 15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 6846642, 4, { -15.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 6846643, 4, { -5.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 6846644, 4, { 5.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 6846645, 4, { 15.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6912959, 5, { 0.000000f, 0.000000f, 15.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -10.000000f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( DeltascapeV30Savage );