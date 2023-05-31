#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlzadaalsLegacy : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlzadaalsLegacy() : Sapphire::ScriptAPI::InstanceContentScript( 87 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9056843, 4, { 124.000000f, 303.475098f, -70.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9056845, 4, { 124.000000f, 303.373901f, -109.380997f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 124.000000f, 303.300507f, -70.249977f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 9056846, 4, { 0.000000f, -7.600203f, -143.929398f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 0.000000f, -7.600141f, -143.379395f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 110.000000f, -350.000000f, -43.000000f }, 1.200000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 9056848, 4, { 110.000000f, -350.000000f, -43.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Saltencrustedteleporter", 2012779, 9056264, 4, { 123.979500f, 305.600006f, -149.978394f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 110.000000f, -350.026703f, -83.000000f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -149.829803f, 304.500000f, 89.851044f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 9056888, 5, { -152.725601f, 304.224487f, 99.700142f }, 0.991760f, -0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Destination", 2012837, 0, 4, { 110.032799f, -350.000000f, -82.891121f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "PassagetoThavnair", 2012841, 0, 4, { 110.024597f, -348.571594f, -45.228222f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2013041, 0, 4, { 109.995201f, -350.000000f, -86.675728f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PassagetoTroiaKeep", 2013039, 0, 4, { 110.032799f, -348.561798f, -92.313011f }, 0.991760f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlzadaalsLegacy );