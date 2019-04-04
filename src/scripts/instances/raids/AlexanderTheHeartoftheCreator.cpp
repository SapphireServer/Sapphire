#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheHeartoftheCreator :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheHeartoftheCreator() :
    Sapphire::ScriptAPI::InstanceContentScript( 30041 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Openduct", 2007466, 0, 4, { 0.000000f, -79.986076f, 42.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Openduct_1", 2007466, 0, 4, { 10.000000f, -79.986076f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Openduct_2", 2007466, 0, 4, { 0.000000f, -79.986076f, 62.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Openduct_3", 2007466, 0, 4, { -10.000000f, -79.986076f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_d2ab_syougai_col", 2007457, 6516055, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_1", 2007457, 6516054, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_2", 2007457, 6516050, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_3", 2007457, 6516150, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_4", 2007457, 6516057, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_5", 2007457, 6516049, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_6", 2007457, 6516058, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "sgpl_d2ab_syougai_col_7", 2007457, 6516056, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f, 0.000000f ); 
    // States -> chrcol_on (id: 35) chrcol_off (id: 44) 
    instance.registerEObj( "unknown_0", 2007457, 6433752, 4, { 0.000000f, -79.986076f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6498824, 4, { 0.000000f, -79.986076f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6494083, 4, { -12.120000f, -79.986076f, 45.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 6494060, 4, { 12.120000f, -79.986076f, 45.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6494084, 4, { 0.000000f, -79.986076f, 66.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007497, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgpl_d2ab_magic", 2007457, 6572855, 4, { 0.000000f, -80.000000f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 6573190, 4, { 0.000000f, -79.986076f, 52.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007507, 0, 4, { 0.000000f, -79.986076f, 2.957292f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6433738, 4, { 26.696230f, 0.000000f, 11.513790f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6433741, 4, { -57.433731f, -40.000000f, -0.807872f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -79.986076f, 40.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6485880, 4, { -58.072899f, -39.959671f, -0.860951f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { -59.879780f, -40.078049f, 0.248821f }, 0.500000f, 0.055177f ); 
    instance.registerEObj( "sgpl_d2ab_navi", 2006981, 6588684, 4, { 0.000000f, -80.000000f, 51.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6449497, 5, { 5.000000f, 0.060100f, 29.472811f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 15.893050f, -0.000000f, 20.165380f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2000182, 6449499, 5, { -46.692200f, -40.000000f, -16.064711f }, 2.000000f, 0.332888f ); 
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

EXPOSE_SCRIPT( AlexanderTheHeartoftheCreator );