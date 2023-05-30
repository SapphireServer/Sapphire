#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheHeroesGauntlet : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheHeroesGauntlet() : Sapphire::ScriptAPI::InstanceContentScript( 75 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b1673a", 2002872, 8366270, 4, { -680.000000f, -24.026699f, 470.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2010506, 0, 4, { -680.000000f, -24.026699f, 470.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Faeportal", 2011119, 8367427, 4, { -679.634583f, -24.026699f, 439.857391f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8371977, 4, { -470.000000f, 0.073400f, -531.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -470.000000f, 0.073399f, -531.000000f }, 1.000000f, -1.570451f); 
    instance.registerEObj( "unknown_2", 2007457, 8321905, 4, { -429.434814f, -1.000000f, -529.212219f }, 1.000000f, 1.605703f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8376083, 4, { 750.000000f, 7.999869f, 505.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 750.000000f, 7.999869f, 505.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8466241, 4, { 738.000000f, 8.000000f, 482.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8466242, 4, { 738.000000f, 8.000000f, 482.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8466243, 4, { 762.000000f, 8.000000f, 482.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8466244, 4, { 762.000000f, 8.000000f, 482.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8315242, 4, { -574.057312f, 4.299284f, 656.966125f }, 1.000000f, 0.640149f); 
    instance.registerEObj( "unknown_9", 2007457, 8318460, 4, { -660.443115f, -17.000000f, 534.447876f }, 1.000000f, -0.349066f); 
    instance.registerEObj( "unknown_10", 2007457, 8321591, 4, { -623.760681f, 1.000000f, -682.297180f }, 1.000000f, 0.959931f); 
    instance.registerEObj( "unknown_11", 2007457, 8321937, 4, { -499.537292f, 1.200000f, -532.813477f }, 1.000000f, 1.483530f); 
    instance.registerEObj( "unknown_12", 2007457, 8321301, 4, { 549.342773f, 5.396739f, 519.236084f }, 1.000000f, -1.134464f); 
    instance.registerEObj( "unknown_13", 2007457, 8321892, 4, { 675.093872f, 7.000000f, 532.000000f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "Entrance", 2000182, 8366251, 5, { -616.000000f, 4.999900f, 795.265503f }, 0.991760f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 749.882324f, 7.999994f, 466.731689f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -616.386475f, 5.479228f, 785.608276f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheHeroesGauntlet );