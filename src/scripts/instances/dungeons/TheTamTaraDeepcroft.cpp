#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheTamTaraDeepcroft :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTamTaraDeepcroft() :
    Sapphire::ScriptAPI::InstanceContentScript( 2 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Cultistorb", 2000061, 3816929, 4, { -8.115554f, 31.427530f, -15.950320f }, 1.000000f, -1.570451f ); 
    // States -> vf_beam1_on (id: 10) vf_beam1_off (id: 11) all_off (id: 22) 
    instance.registerEObj( "Cultistorb_1", 2000062, 3817025, 4, { -22.784361f, 25.526300f, 20.482220f }, 1.000000f, -0.625840f ); 
    // States -> vf_beam2_off (id: 5) vf_beam2_on (id: 6) all_off (id: 16) 
    instance.registerEObj( "Sealedbarrier", 2000060, 2065984, 4, { -103.196800f, 16.825590f, 15.152160f }, 0.950000f, -1.044062f ); 
    instance.registerEObj( "Cultistrosary", 2000057, 0, 4, { -179.952606f, 14.711600f, -4.996500f }, 0.750000f, -1.570796f ); 
    instance.registerEObj( "Cultistorb_2", 2000063, 3817039, 4, { -89.733833f, 15.701490f, 13.923830f }, 0.991789f, 0.925052f ); 
    // States -> vf_beam3_off (id: 6) vf_beam3_on (id: 7) all_off (id: 17) 
    instance.registerEObj( "Cultistorb_3", 2000067, 3817052, 4, { -94.766899f, 15.709600f, 3.820237f }, 1.000000f, 1.227256f ); 
    // States -> vf_beam3_off (id: 6) vf_beam3_on (id: 7) all_off (id: 17) 
    instance.registerEObj( "unknown_0", 2000054, 0, 4, { -53.345570f, 49.647820f, -146.799103f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2001085, 0, 4, { -68.772461f, 15.121640f, -3.860596f }, 0.534058f, 1.095327f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2001697, 4108043, 4, { 13.157160f, 29.280100f, -7.370761f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2001698, 4108046, 4, { -18.524361f, 23.342850f, 42.375740f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2001699, 4108055, 4, { 19.811380f, 30.119770f, -20.717630f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2001700, 0, 4, { 19.739401f, 30.119801f, -19.838511f }, 1.000000f, 1.409320f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2001701, 4108071, 4, { -3.087158f, 23.754129f, 40.895020f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2001702, 0, 4, { -3.984208f, 23.754129f, 41.874859f }, 1.000000f, -0.675014f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2001703, 4108078, 4, { -95.779678f, 14.524550f, 45.017761f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2001704, 0, 4, { -97.035683f, 14.524550f, 44.317101f }, 1.000000f, 0.656244f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -57.755428f, 47.653931f, -120.622597f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2001741, 3860684, 4, { -64.377808f, 15.030030f, -4.745544f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -42.771080f, 14.067750f, -17.288521f }, 0.991789f, 0.000144f ); 
    instance.registerEObj( "Entrance", 2000182, 4108136, 5, { -57.606178f, 49.507038f, -142.170105f }, 1.000000f, 0.000000f ); 
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

EXPOSE_SCRIPT( TheTamTaraDeepcroft );