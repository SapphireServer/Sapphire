#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Smileton : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Smileton() : Sapphire::ScriptAPI::InstanceContentScript( 85 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -45.000000f, 195.850006f, -4.250000f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8872751, 4, { -45.059940f, 196.000000f, -5.172852f }, 0.991760f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002872, 8880065, 4, { -45.029419f, 196.000000f, -34.880070f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 64.000000f, -38.921249f, -92.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8872752, 4, { 64.000000f, -38.967758f, -91.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8872772, 4, { 64.000000f, -39.000000f, -133.250198f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -6.250000f, -465.011993f, -44.000000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8872753, 4, { -7.000000f, -464.999908f, -44.000000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2007457, 8685813, 4, { 105.302498f, 225.543594f, 83.421021f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8685818, 4, { 6.973328f, 211.029495f, -24.979059f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8685820, 4, { -45.029400f, 195.849304f, -50.068100f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8687354, 4, { -0.341362f, 1.000001f, 136.534500f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8687356, 4, { -48.112720f, -23.429371f, 58.178242f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 8687359, 4, { 6.093195f, -15.107590f, 14.067370f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 8687360, 4, { 54.570000f, -22.859770f, -16.676491f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 8645999, 4, { -0.141362f, 1.000001f, 136.834503f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 8677819, 4, { -47.928589f, -23.666809f, 58.457279f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 8679548, 4, { 6.293195f, -15.107690f, 14.367370f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_14", 2007457, 8679549, 4, { 54.770000f, -22.859770f, -16.376490f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_15", 2007457, 8644906, 4, { 55.263432f, -448.149902f, 131.830093f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_16", 2007457, 8644908, 4, { 118.996399f, -445.149902f, 74.249496f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_17", 2007457, 8644909, 4, { 31.953560f, -460.149902f, -44.370529f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8872208, 5, { 10.000000f, 199.788803f, 120.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 12.445600f, 199.873703f, 109.536201f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -32.000000f, -464.999908f, -44.000000f }, 0.991760f, 1.570796f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Smileton );