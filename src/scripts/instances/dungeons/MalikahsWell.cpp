#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class MalikahsWell : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  MalikahsWell() : Sapphire::ScriptAPI::InstanceContentScript( 69 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7903337, 4, { 277.821014f, 16.978960f, 224.841995f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 278.003998f, 17.000000f, 223.834793f }, 0.800000f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7903340, 4, { 277.040710f, 16.068750f, 180.798203f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7903347, 4, { 208.087296f, -86.015198f, 295.368805f }, 0.991760f, 0.033508f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 208.088898f, -86.000000f, 294.663605f }, 1.000000f, 0.033507f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7903350, 4, { 207.604294f, -86.000000f, 255.212799f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2009801, 0, 4, { 202.705704f, -85.999947f, 280.167786f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d4_b1596", 2007457, 7941423, 4, { 208.102905f, -85.999969f, 274.903900f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7903353, 4, { 196.703995f, -93.043617f, -72.797668f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 196.608093f, -93.166077f, -73.804749f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_4", 2007457, 7857425, 4, { -8.732307f, 120.000000f, 60.079208f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 7857727, 4, { 67.783493f, 120.000000f, -39.419670f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_6", 2007457, 7885080, 4, { 195.473602f, 12.000050f, 154.575394f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 7901572, 4, { 145.540100f, -20.000010f, 289.657013f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 7914962, 4, { 203.698898f, -84.246307f, 233.489304f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 7934998, 4, { 196.013199f, -83.999939f, 172.289398f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 7935020, 4, { 191.126297f, -79.999931f, 28.636410f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d4_b1598", 2007457, 7936455, 4, { 180.105896f, -84.036713f, 100.969803f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d4_b1598_1", 2007457, 7936531, 4, { 188.922607f, -79.999931f, 46.923031f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 7903192, 5, { 86.914360f, 118.610397f, 163.245697f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 196.358505f, -93.399933f, -110.378998f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 85.880577f, 118.456001f, 151.447006f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MalikahsWell );