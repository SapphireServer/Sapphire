#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheLostCityofAmdaporHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheLostCityofAmdaporHard() : Sapphire::ScriptAPI::InstanceContentScript( 42 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 6158913, 6158914, 4, { -262.326813f, -278.432312f, -241.982407f }, 1.000000f, -0.424392f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -262.326813, -275.932312, -241.982407 }, -2.717201, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 6158915, 4, { -261.926788f, -278.586792f, -242.680695f }, 0.800000f, -0.511830f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6158916, 4, { 228.895599f, -854.546082f, 420.274109f }, 0.991760f, -0.919204f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2003373, 6159063, 6159059, 4, { -238.928894f, 12.100000f, -279.455688f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -238.928894, 14.600000, -279.455688 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6159060, 6159061, 4, { -199.881607f, 11.999990f, -280.139313f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -199.881485, 14.479391, -280.139435 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 6159062, 4, { -200.009201f, 12.116690f, -280.037506f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 6159123, 6159128, 5, { 73.070312f, 100.000000f, -376.644592f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 73.070549, 101.983376, -379.619965 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 73.079987, 101.983665, -373.669403 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 76.045685, 101.983376, -376.640686 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 70.095123, 101.983665, -376.633942 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 70.987808, 101.983521, -378.727478 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 75.153008, 101.983521, -374.561890 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 75.153206, 101.983322, -378.727295 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 70.987610, 101.983719, -374.562103 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6159129, 4, { 65.173607f, 100.000000f, -382.604614f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2006825, 6173434, 6174253, 4, { -45.716091f, 57.999512f, -311.654205f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -45.716007, 60.211678, -311.158417 }, 0.209487, 6.942322, 4.958802, 0.991760 );
    pEObj->addCollisionBox( { -45.469547, 64.727776, -312.023773 }, 0.209487, 8.871345, 8.149120, 0.208542 );

    pEObj = instance.addEObj( "unknown_15", 2006826, 6173447, 6174254, 4, { -174.685303f, 6.271362f, -302.651215f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -174.685242, 7.615979, -302.651276 }, 0.000048, 5.950562, 3.967041, 0.991760 );

    pEObj = instance.addEObj( "unknown_16", 2006827, 6173458, 6174255, 4, { -174.227493f, 6.973328f, -299.721588f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -174.227325, 10.333928, -299.721741 }, 0.000048, 4.162595, 3.839805, 0.991760 );

    pEObj = instance.addEObj( "unknown_17", 2006828, 6155704, 6174258, 4, { -74.714241f, 58.247410f, -327.713287f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -74.714035, 62.544609, -327.723206 }, 0.000048, 3.277212, 4.726919, 0.123769 );

    pEObj = instance.addEObj( "unknown_18", 2006829, 6184879, 6174290, 4, { -170.839996f, -252.613205f, -408.640503f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -167.618683, -247.654572, -408.920959 }, 0.594782, 2.823773, 5.950562, 0.509028 );
    pEObj->addCollisionBox( { -170.801361, -247.654572, -412.006287 }, 0.989155, 2.112732, 5.950562, 0.509028 );
    pEObj->addCollisionBox( { -171.269089, -247.654709, -415.295929 }, 1.875725, 2.052743, 5.950562, 0.509028 );

    pEObj = instance.addEObj( "unknown_19", 2006830, 6184881, 6174291, 4, { -163.902496f, -272.319397f, -294.726501f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -160.654663, -267.319397, -295.009216 }, 0.594735, 2.847233, 6.000000, 0.513257 );
    pEObj->addCollisionBox( { -163.863937, -267.319397, -298.119995 }, 0.989107, 2.130285, 6.000000, 0.513257 );
    pEObj->addCollisionBox( { -164.335724, -267.319397, -301.436981 }, 1.875677, 2.069798, 6.000000, 0.513257 );

    pEObj = instance.addEObj( "unknown_20", 2006831, 6162191, 6174292, 4, { -243.942093f, -280.660706f, -273.564789f }, 1.000000f, -0.000000f, 0 ); 
    pEObj->addCollisionBox( { -243.942093, -276.327820, -273.574585 }, -0.000000, 3.304440, 4.766191, 0.124797 );

    pEObj = instance.addEObj( "Stoneoftransference", 2006834, 6173379, 6174346, 4, { -295.032104f, -273.037506f, -185.082397f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2006848, 0, 6175672, 4, { -227.145905f, 11.978270f, -284.676086f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2006850, 6161174, 6175687, 4, { -281.669495f, -278.783203f, -207.507401f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -281.669495, -276.283203, -207.507401 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2006851, 0, 6175902, 4, { -287.205292f, -278.675507f, -219.428604f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2006852, 0, 6175906, 4, { -285.709991f, -278.675507f, -222.022598f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2006853, 0, 6175908, 4, { -284.489288f, -278.675507f, -217.719604f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2006854, 0, 6175910, 4, { -282.932892f, -278.675507f, -220.527298f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2006855, 0, 6176589, 4, { 245.654495f, -854.500000f, 408.186615f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2006856, 0, 6176590, 4, { 245.602402f, -854.500000f, 408.203186f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2006857, 0, 6176591, 4, { 217.570694f, -854.500000f, 414.970306f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_21", 2006832, 6177949, 6177172, 4, { 166.001007f, -844.999817f, 265.365814f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 166.001007, -839.999817, 265.365814 }, -0.000000, 8.000000, 6.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_22", 2006833, 6177947, 6177173, 4, { 226.690002f, -856.247681f, 262.675415f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 226.690002, -851.247681, 262.675415 }, -0.000000, 8.000000, 6.000000, 1.000000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 6177873, 6177874, 4, { 236.391098f, -854.348206f, 388.999908f }, 0.991760f, -0.424392f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 236.391235, -851.868774, 389.000122 }, -2.717201, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_7", 2002735, 0, 6177875, 4, { 236.928299f, -854.301025f, 388.437988f }, 0.991760f, -0.272621f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2006867, 0, 6185535, 4, { 238.696899f, -854.398376f, 400.472900f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2006868, 0, 6185536, 4, { 225.070404f, -854.520508f, 402.559692f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_23", 2006835, 6202096, 6210886, 4, { 255.720200f, -865.873474f, 319.853210f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 255.720200, -860.873474, 319.853210 }, -0.000000, 8.000000, 6.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_13", 2007000, 6217077, 6229354, 4, { 230.880493f, -854.459717f, 414.889313f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Guardianstatue", 2006976, 0, 6241185, 4, { 231.118698f, -852.800171f, 414.090088f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Guardianstatue_1", 2006977, 0, 6242529, 4, { 231.113907f, -852.801514f, 414.085785f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Guardianstatue_2", 2006978, 0, 6242530, 4, { 231.101898f, -852.801514f, 414.089111f }, 1.000000f, 0.000000f, 0 ); 


  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, Entity::EventObject& eobj, uint32_t eventId ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint64_t actorId ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

  void onLeaveTerritory( InstanceContent& instance, Entity::Player& player ) override
  {

  }

};

EXPOSE_SCRIPT( TheLostCityofAmdaporHard );