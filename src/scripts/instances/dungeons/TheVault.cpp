#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheVault : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheVault() : Sapphire::ScriptAPI::InstanceContentScript( 34 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5588600, 5588601, 4, { 0.359463f, 300.000000f, 26.171600f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2002735, 0, 5588602, 4, { 0.428600f, 300.000000f, 24.562250f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2005580, 5873754, 5873755, 4, { 0.360928f, 300.000000f, -15.306860f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5581166, 5581161, 4, { -18.416611f, -292.000000f, -99.614120f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2002735, 0, 5581162, 4, { -20.099001f, -292.000000f, -98.859291f }, 0.700000f, -1.570796f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250", 2005106, 5581173, 5581182, 4, { -0.494135f, -292.000000f, -117.713799f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2002735, 0, 5583052, 4, { 18.757099f, 0.000000f, 72.079903f }, 1.000000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5583050, 5583053, 4, { 17.161560f, 0.000000f, 73.880867f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_3", 2005087, 5474300, 5579442, 4, { 37.735470f, -300.007690f, 30.228149f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2005088, 5499954, 5579463, 4, { 51.884090f, -300.000000f, -35.577080f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2005089, 5474303, 5579464, 4, { 44.255379f, -300.000000f, -31.015051f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005090, 5474308, 5579478, 4, { -36.242680f, -300.000000f, -29.871010f }, 1.000000f, -0.000345f, 0); 
    instance.addEObj( "unknown_7", 2005091, 5474306, 5579537, 4, { -37.591751f, -300.000000f, -69.819733f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2005092, 5499959, 5579540, 4, { -33.701191f, -300.000000f, -79.843872f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2005093, 5499966, 5579647, 4, { 6.953651f, -281.975708f, -150.744995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2005094, 5476161, 5580240, 4, { 101.518402f, -263.140503f, -12.115350f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2005095, 5476162, 5580241, 4, { 101.390800f, -263.204315f, 11.842000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2005096, 5474532, 5580265, 4, { 99.222763f, -264.000000f, -0.362554f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2005097, 5499987, 5580413, 4, { 22.634041f, 0.000000f, 71.960167f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2005098, 5499980, 5580417, 4, { -17.585621f, 0.000000f, 72.136276f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2005099, 5444302, 5580677, 4, { -92.607063f, -0.015320f, 0.076233f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_16", 2005100, 5499663, 5580709, 4, { -52.663239f, 291.000000f, 42.623951f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2005101, 5499660, 5580710, 4, { -67.359016f, 291.000000f, 42.656231f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2005102, 5499645, 5580711, 4, { -66.869476f, 291.000000f, 55.587841f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005103, 5499653, 5580712, 4, { -53.398609f, 291.000000f, 55.570320f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005104, 5499600, 5580718, 4, { -46.140011f, 291.000000f, 48.667049f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 5578486, 5578515, 5, { -5.010592f, -300.000000f, 86.198753f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 5578521, 4, { 11.135890f, -300.000000f, 78.862717f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 5578561, 4, { 0.136796f, 299.977112f, -9.654591f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheVault );