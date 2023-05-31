#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class KtisisHyperboreia : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  KtisisHyperboreia() : Sapphire::ScriptAPI::InstanceContentScript( 82 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8862405, 4, { -141.008499f, 498.893707f, 29.708380f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -143.824493f, 496.320496f, 69.169884f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8862404, 4, { -144.021393f, 498.471985f, 68.224693f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8864377, 4, { -0.434494f, 631.045227f, 28.421841f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 0.132812f, 629.840271f, 68.283722f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8864376, 4, { -0.105941f, 631.792480f, 68.034637f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 8864457, 4, { 0.667652f, -0.490447f, -70.997223f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -0.028526f, 0.275627f, -28.003469f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2002872, 8864456, 4, { -0.156951f, 0.635187f, -27.880369f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_n5d1_b2351", 2007457, 8804114, 4, { 0.000000f, 0.016100f, -50.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 7.094823f, 517.999695f, 308.190399f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.058405f, -0.301556f, -66.263603f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "GuidetoKtisisHyperboreia", 2011715, 0, 4, { -32.358978f, 507.014709f, 226.148895f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8865012, 5, { 4.684509f, 520.564270f, 317.677490f }, 0.991760f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Observationjournal", 2011716, 0, 4, { -94.048378f, 624.977783f, 153.242905f }, 1.000000f, 1.513912f); 
    instance.registerEObj( "FlyingLifeformsAnIntroduction", 2011717, 0, 4, { -17.563169f, -139.452194f, 5.752625f }, 0.991760f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( KtisisHyperboreia );