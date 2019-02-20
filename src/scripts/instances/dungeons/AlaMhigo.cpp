#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlaMhigo :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlaMhigo() :
    Sapphire::ScriptAPI::InstanceContentScript( 56 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6894813, 4, { -209.363495f, 35.017460f, 72.069672f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6894812, 4, { -172.226807f, 35.017342f, 72.369667f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -210.219406f, 35.017460f, 72.000000f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "unknown_1", 2008685, 0, 4, { -192.767105f, 34.867069f, 71.984734f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6894833, 4, { 250.000000f, 106.496902f, -50.489590f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6894834, 4, { 250.000000f, 106.496902f, -89.516243f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 250.000000f, 106.496902f, -50.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2002872, 6895342, 4, { 248.500000f, 122.000000f, -329.291107f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2007457, 6865535, 4, { 249.561295f, 121.995796f, -352.681793f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0249", 2007457, 6895343, 4, { 249.487595f, 122.005699f, -330.083801f }, 0.991760f, 0.000048f ); 
    // States -> vf_line_on (id: 10) vf_line_of (id: 11) 
    instance.registerEObj( "sgvf_w_lvd_b0250_1", 2002872, 6904529, 4, { 248.937500f, 122.000000f, -377.252899f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2008350, 0, 4, { 250.000000f, 122.000000f, -353.000000f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_5", 2007168, 0, 4, { 250.018997f, 121.995796f, -353.109009f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 6879593, 5, { -408.611298f, 2.500000f, 233.977905f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -398.118408f, 2.500000f, 236.857193f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 250.007294f, 122.000000f, -370.492889f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2008319, 6844583, 4, { -342.881104f, 24.000010f, 149.680099f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2008319, 6844584, 4, { -258.130402f, 27.000010f, 99.970268f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6840800, 4, { -100.167801f, 44.750629f, 73.001747f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6853103, 4, { 193.710297f, 106.000000f, 128.847397f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6847102, 4, { 263.424286f, 106.400002f, -8.750051f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 6847104, 4, { 249.800797f, 106.428101f, -108.873100f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2008335, 6844579, 4, { 233.630905f, 109.971703f, -155.596298f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2008335, 6844578, 4, { 233.295197f, 109.971703f, -144.792892f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2008335, 6844581, 4, { 224.912094f, 120.000000f, -248.707504f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2008335, 6844580, 4, { 210.809296f, 120.000000f, -248.716202f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2008336, 6845038, 4, { 249.895905f, 122.099899f, -294.475403f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007457, 6942278, 4, { 233.967697f, 110.000000f, -150.215607f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2007457, 6942279, 4, { 217.761505f, 119.889999f, -247.455597f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlaMhigo );