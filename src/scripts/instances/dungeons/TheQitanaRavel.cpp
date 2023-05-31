#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheQitanaRavel : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheQitanaRavel() : Sapphire::ScriptAPI::InstanceContentScript( 66 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7705609, 4, { -7.223356f, 5.350000f, 328.780701f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 7705610, 4, { 8.010925f, 5.325378f, 328.780212f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7881195, 4, { -3.150560f, 5.037637f, 337.800293f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7881202, 4, { -3.807557f, 5.120782f, 287.481293f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 0.000000f, 5.350000f, 333.825989f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7881620, 4, { 68.445648f, -21.000000f, -20.501869f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7881626, 4, { 67.833878f, -21.000000f, -54.058590f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002587, 0, 4, { 61.552200f, -21.000000f, -20.588791f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_4", 2007457, 0, 4, { 60.507851f, -10.834170f, 45.405231f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7881987, 4, { 13.380650f, -58.058571f, -433.455597f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2002587, 0, 4, { 16.983280f, -58.462502f, -436.011505f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_6", 2007457, 7717952, 4, { -7.217590f, 0.076233f, 658.075684f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_7", 2007457, 7718678, 4, { -7.248047f, 0.076233f, 649.927490f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_8", 2007457, 7681385, 4, { -7.248047f, 0.076233f, 642.969421f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_9", 2007457, 7718679, 4, { -7.248047f, 0.076233f, 635.492371f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_10", 2007457, 7681387, 4, { -7.248047f, 0.076233f, 627.710327f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_11", 2007457, 7718680, 4, { -7.217590f, 0.076233f, 620.233398f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_12", 2007457, 7681391, 4, { 7.217468f, 0.076233f, 627.710327f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_13", 2007457, 7717958, 4, { 7.248049f, 0.076233f, 620.233398f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_14", 2007457, 7717959, 4, { 7.217468f, 0.076233f, 635.492371f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_15", 2007457, 7681395, 4, { 7.217468f, 0.076233f, 642.969421f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_16", 2007457, 7717960, 4, { 7.217468f, 0.076233f, 649.927490f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_17", 2007457, 7717951, 4, { 7.217468f, 0.076233f, 658.045288f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_18", 2007457, 7723622, 4, { -7.248047f, 2.090454f, 451.926392f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_19", 2007457, 7723627, 4, { -7.248047f, 1.968323f, 443.778107f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_20", 2007457, 7723623, 4, { -7.248047f, 2.090454f, 436.819885f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_21", 2007457, 7723624, 4, { -7.248047f, 1.968323f, 429.343109f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_22", 2007457, 7723625, 4, { -7.248047f, 5.416931f, 421.560913f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_23", 2007457, 7723626, 4, { -7.187073f, 1.998901f, 414.114502f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_24", 2007457, 7722121, 4, { 7.217468f, 2.090454f, 421.560913f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_25", 2007457, 7681414, 4, { 7.248047f, 1.998901f, 414.114502f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_26", 2007457, 7681413, 4, { 7.217468f, 1.968323f, 429.343109f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_27", 2007457, 7722120, 4, { 7.217468f, 2.090454f, 436.819885f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_28", 2007457, 7701532, 4, { 7.217468f, 1.968323f, 443.778107f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_29", 2007457, 7722119, 4, { 7.217468f, 2.029419f, 451.926392f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgbg_n4d3_a1_gmc01", 2007457, 7885048, 4, { -1.265310f, 0.003401f, 639.075989f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4d3_a1_gmc01_1", 2007457, 7885090, 4, { -1.265310f, 2.043664f, 432.974213f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_30", 2007457, 7693045, 4, { 0.000000f, 4.967093f, 376.702698f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_31", 2007457, 7923571, 4, { 0.000000f, 5.009568f, 276.046600f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_32", 2007457, 7716070, 4, { 100.144897f, -2.000000f, 159.441406f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_33", 2007457, 7718743, 4, { 60.776611f, -11.001830f, 54.672970f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_n4d3_b1582", 2007457, 7933086, 4, { 5.000000f, 3.897611f, 248.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d3_b1582_1", 2007457, 7933128, 4, { 86.000000f, -2.000000f, 165.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d3_b1582_2", 2007457, 7933133, 4, { 132.000000f, -11.000000f, 110.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_n4d3_b1582_3", 2007457, 7933142, 4, { 70.747627f, -11.000000f, 75.545021f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_34", 2007457, 7923706, 4, { 13.351620f, -60.044312f, -333.485992f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_35", 2007457, 7923707, 4, { -0.006478f, -56.930901f, -411.478394f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_36", 2007457, 7722099, 4, { 38.454460f, -21.981951f, -155.466293f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2000182, 7881140, 5, { -3.127450f, 8.180656f, 729.805908f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 4.055151f, 8.180655f, 711.399902f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 16.750610f, -77.000076f, -557.086121f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheQitanaRavel );