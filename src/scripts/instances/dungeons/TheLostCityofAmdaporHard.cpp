#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheLostCityofAmdaporHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheLostCityofAmdaporHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 42 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6159060, 4, { -199.881607f, 11.999990f, -280.139313f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -200.009201f, 12.116690f, -280.037506f }, 0.991760f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2003373, 6159063, 4, { -238.928894f, 12.100000f, -279.455688f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2006848, 0, 4, { -227.145905f, 11.978270f, -284.676086f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6158913, 4, { -262.326813f, -278.432312f, -241.982407f }, 1.000000f, -0.424392f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -261.926788f, -278.586792f, -242.680695f }, 0.800000f, -0.511830f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2006850, 6161174, 4, { -281.669495f, -278.783203f, -207.507401f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2006851, 0, 4, { -287.205292f, -278.675507f, -219.428604f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2006852, 0, 4, { -285.709991f, -278.675507f, -222.022598f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2006853, 0, 4, { -284.489288f, -278.675507f, -217.719604f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2006854, 0, 4, { -282.932892f, -278.675507f, -220.527298f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6177873, 4, { 236.391098f, -854.348206f, 388.999908f }, 0.991760f, -0.424392f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2002735, 0, 4, { 236.928299f, -854.301025f, 388.437988f }, 0.991760f, -0.272621f ); 
    instance.registerEObj( "unknown_8", 2006855, 0, 4, { 245.654495f, -854.500000f, 408.186615f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_9", 2006856, 0, 4, { 245.602402f, -854.500000f, 408.203186f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2006857, 0, 4, { 217.570694f, -854.500000f, 414.970306f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_11", 2006867, 0, 4, { 238.696899f, -854.398376f, 400.472900f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2006868, 0, 4, { 225.070404f, -854.520508f, 402.559692f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2007000, 6217077, 4, { 230.880493f, -854.459717f, 414.889313f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Guardianstatue", 2006976, 0, 4, { 231.118698f, -852.800171f, 414.090088f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Guardianstatue_1", 2006977, 0, 4, { 231.113907f, -852.801514f, 414.085785f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Guardianstatue_2", 2006978, 0, 4, { 231.101898f, -852.801514f, 414.089111f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6159123, 5, { 73.070312f, 100.000000f, -376.644592f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 65.173607f, 100.000000f, -382.604614f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 228.895599f, -854.546082f, 420.274109f }, 0.991760f, -0.919204f ); 
    instance.registerEObj( "unknown_14", 2006825, 6173434, 4, { -45.716091f, 57.999512f, -311.654205f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2006826, 6173447, 4, { -174.685303f, 6.271362f, -302.651215f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2006827, 6173458, 4, { -174.227493f, 6.973328f, -299.721588f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2006828, 6155704, 4, { -74.714241f, 58.247410f, -327.713287f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_18", 2006829, 6184879, 4, { -170.839996f, -252.613205f, -408.640503f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_19", 2006830, 6184881, 4, { -163.902496f, -272.319397f, -294.726501f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2006831, 6162191, 4, { -243.942093f, -280.660706f, -273.564789f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Stoneoftransference", 2006834, 6173379, 4, { -295.032104f, -273.037506f, -185.082397f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2006832, 6177949, 4, { 166.001007f, -844.999817f, 265.365814f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2006833, 6177947, 4, { 226.690002f, -856.247681f, 262.675415f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2006835, 6202096, 4, { 255.720200f, -865.873474f, 319.853210f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a", 2002872, 6904891, 4, { 236.391205f, -854.348083f, 388.999908f }, 0.991760f, -0.424392f ); 
    instance.registerEObj( "unknown_24", 2002735, 0, 4, { 236.928299f, -854.301025f, 388.437988f }, 0.991760f, -0.272621f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a_1", 2007457, 6904603, 4, { 249.195099f, -856.351624f, 343.526215f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_25", 2007457, 6217077, 4, { 233.497299f, -854.546021f, 414.179413f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheLostCityofAmdaporHard );