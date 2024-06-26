#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SastashaHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SastashaHard() : Sapphire::ScriptAPI::InstanceContentScript( 28 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2002735, 0, 4887876, 4, { 157.165298f, 14.000000f, -65.283813f }, 1.000000f, 0.443513f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4887881, 4887889, 4, { 157.156601f, 14.074050f, -62.918228f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4887882, 4887890, 4, { 143.947693f, 14.031430f, -75.422539f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2002735, 0, 4887920, 4, { -103.378998f, 15.750010f, 113.646400f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 4887934, 4887958, 4, { -102.988998f, 14.900710f, 111.903198f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2002872, 4868757, 4887973, 4, { -120.026100f, 15.610280f, 152.360199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2002735, 0, 4888025, 4, { -300.099213f, 5.569519f, 278.309296f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 4888143, 4, { -326.124603f, 5.082251f, 320.072388f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004421, 4769863, 4880492, 4, { 228.091507f, 40.730598f, -164.119293f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Drainagepump", 2004406, 4768296, 4880501, 4, { 179.233200f, 33.911160f, -25.225599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2004405, 4768239, 4880503, 4, { 164.693695f, 26.418791f, -51.467159f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2004407, 4877642, 4880620, 4, { 116.227898f, 13.992490f, -60.624149f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2004408, 4867860, 4880621, 4, { 94.502289f, 14.098320f, -72.764816f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2004409, 4867859, 4880622, 4, { 61.426201f, 16.933029f, -87.107803f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2004410, 4878592, 4880685, 4, { -14.773780f, 12.568780f, -21.590240f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004411, 4878584, 4880687, 4, { -34.366249f, 12.620500f, -10.794950f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2004412, 4878593, 4880688, 4, { -38.197849f, 12.744050f, -32.694260f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2004422, 4770074, 4880723, 4, { -47.051659f, 12.731530f, -15.329430f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2004413, 4878605, 4880804, 4, { -75.129097f, 7.724828f, -3.396252f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2004414, 4878604, 4880805, 4, { -67.776993f, 7.424381f, 10.125570f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2004415, 4878603, 4880806, 4, { -74.879089f, 7.540010f, 24.726391f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2004416, 4878609, 4880807, 4, { -92.286110f, 7.701883f, 26.123421f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2004417, 4878523, 4880808, 4, { -103.974098f, 8.528216f, 17.928379f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2004418, 4878606, 4880810, 4, { -107.137001f, 7.762873f, 7.250639f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2004419, 4878607, 4880811, 4, { -97.134842f, 7.622185f, -4.976304f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2004420, 4878608, 4880813, 4, { -83.913422f, 7.926591f, -9.813313f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2004423, 4770075, 4880848, 4, { -84.640503f, 7.804197f, 29.907909f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "DoortotheDeadMansDrink", 2004424, 4765267, 4880864, 4, { -96.240341f, 19.268089f, 87.404861f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2004425, 4761283, 4880887, 4, { -188.014496f, 7.483281f, 252.162704f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2004426, 4762024, 4880943, 4, { -299.676086f, 5.576687f, 280.853699f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2004429, 0, 4880945, 4, { -302.662689f, 5.569519f, 269.489502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_25", 2004441, 4765263, 4889756, 4, { -130.635300f, 16.327169f, 156.933502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgpl_w_lvd_board_col_on_off", 2004428, 4890021, 4890022, 4, { -295.493286f, 5.576687f, 275.610901f }, 1.000000f, 0.000000f, 0); 
    // States -> col_on (id: 17) col_off (id: 18) 
    instance.addEObj( "Entrance", 2000182, 4878710, 4878735, 5, { 347.674713f, 44.019909f, -221.552002f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 4878767, 4, { 328.774994f, 44.119980f, -229.481705f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SastashaHard );