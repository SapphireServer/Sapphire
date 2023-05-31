#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AnamnesisAnyder : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AnamnesisAnyder() : Sapphire::ScriptAPI::InstanceContentScript( 74 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8239763, 4, { -39.991852f, 95.040092f, 312.140900f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -40.005638f, 95.000000f, 310.534485f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8239770, 4, { -40.005638f, 95.996338f, 266.030487f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2010988, 0, 4, { -40.000000f, 95.000000f, 275.577515f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2007457, 8240235, 4, { 20.000000f, 110.000000f, -60.992142f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8240242, 4, { 20.000000f, 112.000000f, -100.414803f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007791, 0, 4, { 19.900000f, 110.000000f, -64.440002f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 8241401, 4, { -0.021303f, -200.000000f, -427.542297f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 0.000000f, -200.000000f, -429.250885f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_4", 2007457, 8258050, 4, { -90.088837f, 103.593300f, 372.060608f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2010989, 0, 4, { -98.535629f, 103.486504f, 415.876587f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8258061, 4, { 39.566650f, 99.000000f, 107.835403f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8258062, 4, { 19.882509f, 109.971703f, -27.490009f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8258077, 4, { 19.882509f, 91.996582f, -301.655609f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8241591, 5, { -98.687363f, 102.707397f, 404.640106f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -105.451401f, 103.590500f, 381.790894f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000026f, -200.000000f, -465.000000f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "ExittoKholusia", 2010954, 0, 4, { 0.000000f, -198.000000f, -404.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "ExittoKholusia_1", 2011084, 0, 4, { 0.000000f, -198.000000f, -405.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aetherialstream", 2011085, 0, 4, { 1.822433f, -200.000107f, -448.332489f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Aetherialstream_1", 2013421, 0, 4, { 1.822400f, -200.000107f, -448.332489f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AnamnesisAnyder );