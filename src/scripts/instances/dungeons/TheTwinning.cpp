#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheTwinning : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTwinning() : Sapphire::ScriptAPI::InstanceContentScript( 68 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2010169, 0, 4, { -7.888916f, -849.027222f, -330.617310f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 0.000000f, -848.000000f, -309.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7921150, 4, { 5.779223f, -848.000000f, -312.473114f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007457, 7875578, 4, { -123.004898f, 319.996887f, 17.571791f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_3", 2007457, 7880188, 4, { -70.572998f, 299.977112f, 161.303101f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_4", 2007457, 7880206, 4, { 89.311043f, 299.977112f, 316.640015f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_5", 2007457, 7875577, 4, { 208.768707f, 319.996796f, 329.107697f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_6", 2007457, 7879255, 4, { 60.562988f, 299.977112f, 281.239014f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_7", 2007457, 7880204, 4, { -98.056664f, 299.977997f, 100.305603f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_8", 2007457, 7880205, 4, { -15.618610f, 299.978210f, 228.156296f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_9", 2007457, 7875576, 4, { 182.951202f, 319.972290f, 342.881989f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_10", 2007457, 7877558, 4, { -162.279694f, 319.996796f, 1.693726f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_11", 2007457, 7880184, 4, { 192.543304f, 24.000000f, 176.733902f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 7880183, 4, { 197.448196f, 6.000004f, 123.613297f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Ironworksdatalog25", 2010337, 0, 4, { 192.869598f, 32.000000f, 230.635605f }, 0.991760f, -0.471946f); 
    instance.registerEObj( "Ironworksdatalog35", 2010338, 0, 4, { 137.346405f, 24.000000f, 145.555801f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Ironworksdatalog45", 2010339, 0, 4, { 217.464493f, 7.972680f, 122.922501f }, 0.991760f, 0.726515f); 
    instance.registerEObj( "sgvf_n4d7_b1621", 2007457, 7984566, 4, { 200.121902f, 6.729187f, 32.394779f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_n4d7_b1621_1", 2007457, 7973305, 4, { -4.470947f, -800.045776f, 222.583405f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_n4d7_b1621_2", 2007457, 7973308, 4, { -4.348877f, -837.552490f, 19.211060f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_13", 2007457, 7829499, 4, { -4.196289f, -844.022278f, -236.102905f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_14", 2007457, 7829471, 4, { 5.142273f, -844.022278f, -104.051300f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_15", 2007457, 7876546, 4, { 4.010477f, -848.000000f, -265.485687f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_16", 2007457, 7888484, 4, { -2.090576f, -837.399902f, 108.506798f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_17", 2007457, 7888485, 4, { 5.691528f, -837.552490f, 37.460819f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_18", 2007457, 7917581, 4, { -0.076355f, -848.020081f, -280.653809f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_19", 2007457, 7895235, 4, { 182.000000f, 317.000000f, 266.838287f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_20", 2007457, 7895242, 4, { 181.994293f, 316.975586f, 276.813812f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_21", 2007457, 7895243, 4, { 181.994293f, 316.975586f, 286.823914f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_22", 2007457, 7895244, 4, { 181.994293f, 316.975586f, 296.833710f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_23", 2007457, 7895251, 4, { 217.975098f, 316.975586f, 273.121094f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_24", 2007457, 7895250, 4, { 217.975098f, 316.975586f, 283.131104f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_25", 2007457, 7895249, 4, { 217.975098f, 316.975586f, 293.110504f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_26", 2007457, 7895246, 4, { 217.975098f, 316.975586f, 303.120514f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7917879, 4, { 201.936203f, 318.000000f, 266.936188f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_27", 2002735, 0, 4, { 200.000000f, 12.000000f, 88.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7920150, 4, { 203.075806f, 12.008740f, 84.259613f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7920152, 4, { 201.483002f, 12.000000f, 52.157108f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Entrance", 2000182, 7917861, 5, { -347.300293f, 318.043701f, 8.499207f }, 0.991760f, 0.000144f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -333.089203f, 318.060394f, 6.423950f }, 0.991760f, 0.000144f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -848.000000f, -344.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheTwinning );