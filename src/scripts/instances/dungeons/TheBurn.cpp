#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheBurn :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheBurn() :
    Sapphire::ScriptAPI::InstanceContentScript( 63 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7562183, 4, { -295.336395f, 19.206579f, -349.383911f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -299.301788f, 19.167589f, -351.730499f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2007457, 7359163, 4, { 259.879608f, 82.591408f, 308.727203f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2007457, 7359164, 4, { 240.794296f, 81.018692f, 315.201813f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2007457, 7359165, 4, { 213.139801f, 80.655479f, 309.588501f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2007457, 7371780, 4, { 180.792404f, 65.073128f, 298.607605f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7359160, 4, { 344.319214f, 96.692558f, 375.705902f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2007457, 7359161, 4, { 326.647186f, 92.636917f, 388.177490f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2007457, 7359162, 4, { 301.141815f, 90.127007f, 384.239014f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_8", 2007457, 7371782, 4, { 277.238098f, 77.736717f, 361.668091f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 7390924, 4, { 43.728119f, 20.060129f, 106.101601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 7390916, 4, { 0.052692f, 36.060131f, -24.711960f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7384891, 4, { -169.030502f, 28.326990f, -242.422897f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7393691, 4, { -171.168304f, 28.175030f, -240.856293f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7384892, 4, { -306.576202f, 20.664431f, -338.984406f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 7393692, 4, { -293.959106f, 20.483391f, -340.855804f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7561681, 4, { 177.235596f, 12.985350f, 195.044403f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7561686, 4, { 176.322296f, 13.041980f, 159.747299f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_15", 2002735, 0, 4, { 174.092300f, 12.950240f, 197.852005f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7562060, 4, { 2.190432f, 34.066490f, -57.807091f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7562061, 4, { 1.902058f, 34.159721f, -82.991417f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_16", 2002735, 0, 4, { 0.000000f, 34.176800f, -59.299999f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2007457, 7546643, 4, { 0.000000f, 34.000000f, -70.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7558759, 5, { 428.524994f, 88.401329f, 447.618286f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 423.779907f, 86.908783f, 424.929901f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -300.334290f, 10.000000f, -414.183411f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheBurn );