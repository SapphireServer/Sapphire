#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheExcitatron6000 : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheExcitatron6000() : Sapphire::ScriptAPI::InstanceContentScript( 55009 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 8858855, 5, { -0.000000f, 20.000000f, 298.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -0.000000f, 20.000000f, 292.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_u5c1_b2501", 2007457, 8858929, 4, { 122.500000f, -10.000000f, 130.000000f }, 1.000000f, 1.570451f); 
    instance.registerEObj( "sgvf_u5c1_b2501_1", 2007457, 8858927, 4, { 97.489868f, -10.025270f, 129.991592f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "sgvf_u5c1_b2501_2", 2007457, 8858928, 4, { 109.971703f, -10.025270f, 117.479202f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 110.000000f, -10.000000f, 150.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8858917, 4, { 110.000000f, -10.000000f, 150.250000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b2502", 2007457, 8858930, 4, { 106.675797f, -10.025270f, 129.991592f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b2503", 2007457, 8858931, 4, { 110.699997f, -9.999992f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Treasurecoffer", 2012402, 0, 4, { 109.971703f, -10.025270f, 129.991592f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "High", 2012414, 8858925, 4, { 110.978798f, -10.025270f, 134.996597f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Low", 2012415, 8858926, 4, { 112.992996f, -10.025270f, 134.996597f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_u5c1_b2501_3", 2007457, 8858969, 4, { 122.500000f, -10.000000f, -20.000000f }, 1.000000f, 1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_4", 2007457, 8858967, 4, { 97.500000f, -10.000000f, -20.000000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_5", 2007457, 8858968, 4, { 110.000000f, -10.000000f, -32.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 110.000000f, -9.999965f, 0.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8858957, 4, { 110.000000f, -10.000000f, 0.250000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b2502_1", 2007457, 8858970, 4, { 108.000000f, -10.000000f, -20.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b2503_1", 2007457, 8858971, 4, { 112.000000f, -10.000030f, -20.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Treasurecoffer_1", 2012403, 0, 4, { 110.000000f, -9.999999f, -20.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_1", 2012416, 8858963, 4, { 110.800102f, -9.999983f, -15.600000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low_1", 2012417, 8858964, 4, { 112.800102f, -9.999997f, -15.600010f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_u5c1_b2501_6", 2007457, 8859010, 4, { -97.500000f, 20.000000f, -140.000000f }, 1.000000f, 1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_7", 2007457, 8859008, 4, { -122.500000f, 20.000000f, -140.000000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_8", 2007457, 8859009, 4, { -110.000000f, 20.000000f, -152.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -110.000000f, 20.000000f, -119.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 8858998, 4, { -110.000000f, 19.999981f, -119.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b2502_2", 2007457, 8859011, 4, { -112.000000f, 20.000000f, -140.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b2503_2", 2007457, 8859012, 4, { -108.000000f, 20.000000f, -140.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Treasurecoffer_2", 2012404, 0, 4, { -110.000000f, 20.000000f, -140.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_2", 2012418, 8859004, 4, { -109.000000f, 20.000000f, -135.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Low_2", 2012419, 8859005, 4, { -107.000000f, 20.000000f, -135.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_u5c1_b2501_9", 2007457, 8859051, 4, { -97.500000f, 20.000000f, -290.000000f }, 1.000000f, 1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_10", 2007457, 8859049, 4, { -122.500000f, 20.000000f, -290.000000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_11", 2007457, 8859050, 4, { -110.000000f, 20.000000f, -302.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -110.000000f, 20.000000f, -269.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8859039, 4, { -110.000000f, 19.999990f, -269.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b2502_3", 2007457, 8859052, 4, { -112.000000f, 20.000000f, -290.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b2503_3", 2007457, 8859053, 4, { -108.000000f, 20.000000f, -290.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Treasurecoffer_3", 2012405, 0, 4, { -110.002403f, 19.974060f, -290.028290f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "High_3", 2012420, 8859045, 4, { -109.000000f, 20.000000f, -285.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Low_3", 2012421, 8859046, 4, { -107.000000f, 20.000000f, -285.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_u5c1_b2501_12", 2007457, 8859092, 4, { 12.500000f, 23.999990f, -460.000000f }, 1.000000f, 1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_13", 2007457, 8859090, 4, { -12.500000f, 23.999990f, -460.000000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "sgvf_u5c1_b2501_14", 2007457, 8859091, 4, { 0.000017f, 24.000010f, -472.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000017f, 24.000010f, -474.600006f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 0.000000f, 24.000000f, -439.500000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 8859083, 4, { 0.000017f, 24.000000f, -439.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b2502_4", 2007457, 8859093, 4, { -2.000000f, 23.999990f, -460.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b2503_4", 2007457, 8859094, 4, { 2.000000f, 23.999990f, -460.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "High_4", 2012422, 8859086, 4, { 1.000000f, 24.000010f, -455.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Low_4", 2012423, 8859087, 4, { 3.000000f, 24.000010f, -455.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8950266, 4, { 134.000000f, -10.000000f, 105.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8950265, 4, { 85.000000f, -10.000000f, 105.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8949906, 4, { 110.000000f, -10.000000f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8949914, 4, { 110.000000f, -10.000000f, -20.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 8950274, 4, { 134.000000f, -10.000000f, -44.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 8950273, 4, { 85.000000f, -10.000000f, -45.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 8949916, 4, { -110.000000f, 20.000000f, -140.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 8950280, 4, { -85.000000f, 20.000000f, -164.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 8950279, 4, { -135.000000f, 20.000000f, -165.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_14", 2007457, 8949917, 4, { -110.000000f, 20.000000f, -290.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_15", 2007457, 8950287, 4, { -85.000000f, 20.000000f, -314.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_16", 2007457, 8950286, 4, { -135.000000f, 20.000000f, -315.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_17", 2007457, 8949918, 4, { 0.000000f, 24.000000f, -460.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Stagedoor", 2012407, 8950264, 4, { 131.567001f, -10.000000f, 108.432999f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_1", 2012406, 8950263, 4, { 88.432999f, -10.000000f, 108.432999f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_2", 2012409, 8950272, 4, { 131.567001f, -10.000000f, -41.567001f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_3", 2012408, 8950271, 4, { 88.432999f, -10.000000f, -41.567001f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_4", 2012411, 8950278, 4, { -88.432999f, 20.000000f, -161.567001f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_5", 2012410, 8950277, 4, { -131.567001f, 20.000000f, -161.567001f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_6", 2012413, 8950285, 4, { -88.432999f, 20.000000f, -311.566986f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Stagedoor_7", 2012412, 8950284, 4, { -131.567001f, 20.000000f, -311.566986f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheExcitatron6000 );