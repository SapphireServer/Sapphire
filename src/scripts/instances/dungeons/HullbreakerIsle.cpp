#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class HullbreakerIsle : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  HullbreakerIsle() : Sapphire::ScriptAPI::InstanceContentScript( 23 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 4685106, 4685107, 5, { 320.642792f, 3.735552f, 302.314301f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 320.643036, 5.718930, 299.338928 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 320.652466, 5.719215, 305.289490 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 323.618164, 5.718930, 302.318207 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 317.667603, 5.719216, 302.324951 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 318.560303, 5.719073, 300.231415 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 322.725494, 5.719073, 304.397003 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 322.725677, 5.718873, 300.231598 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 318.560089, 5.719272, 304.396790 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 4685142, 4, { 220.874298f, 64.988159f, 13.046390f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4685143, 4685145, 4, { 220.800797f, 64.801514f, 13.539410f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 220.800797, 67.301514, 13.539410 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2004050, 4685147, 4685149, 4, { 219.745102f, 64.682983f, -33.707211f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 219.745224, 67.162384, -33.707329 }, 0.000048, 14.876405, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgpl_w_transparent05", 2004049, 4685157, 4685156, 4, { 219.958694f, 65.018677f, 47.991199f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 219.958878, 68.811516, 47.991016 }, 0.000048, 5.950562, 3.967041, 0.991760 );

    pEObj = instance.addEObj( "unknown_1", 2002735, 0, 4685160, 4, { -60.079769f, 44.339741f, -124.669800f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4685162, 4685161, 4, { -61.990799f, 44.123230f, -125.263000f }, 1.000000f, -1.570451f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -61.990799, 46.623230, -125.263000 }, -1.570451, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2004051, 4685163, 4685164, 4, { -98.791832f, 44.299992f, -124.783699f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -98.791832, 46.799992, -124.783699 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 4685166, 4, { -315.480286f, 1.957748f, 33.432499f }, 0.991760f, -1.184874f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 4685167, 4685168, 4, { -314.885803f, 1.999334f, 32.833080f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -314.885803, 4.499334, 32.833080 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4685192, 4, { 325.360901f, 6.499028f, 292.726807f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2004052, 4584550, 4685202, 4, { 165.269104f, 52.440060f, -190.280197f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 165.269089, 57.819199, -190.280182 }, -0.000000, 4.400017, 6.182945, 0.719620 );

    pEObj = instance.addEObj( "Stonepedestal", 2004057, 4588393, 4685203, 4, { 163.784195f, 52.706680f, -185.027100f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2004053, 4584553, 4685204, 4, { -35.849411f, 44.986191f, -124.177696f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -35.849426, 50.365334, -124.177681 }, -0.000000, 4.400017, 6.182945, 0.719620 );

    pEObj = instance.addEObj( "Stonepedestal_1", 2004058, 4588617, 4685205, 4, { -32.145729f, 44.996059f, -118.336502f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Stonepedestal_2", 2004059, 4588610, 4685206, 4, { -32.404221f, 44.937031f, -128.964096f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Wildbananatree", 2004062, 4706914, 4719758, 4, { 206.036896f, 65.302567f, -27.040119f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Wildbananatree_1", 2004063, 4722842, 4719759, 4, { 199.376907f, 64.682983f, -11.735090f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Wildbananatree_2", 2004064, 4706915, 4719760, 4, { 205.968002f, 64.690811f, 3.866779f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Wildbananatree_3", 2004065, 4706916, 4719762, 4, { 236.652100f, 64.927116f, -28.061340f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2004066, 0, 4719773, 4, { 206.655502f, 65.036621f, -25.903111f }, 0.991760f, -1.260904f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2004067, 0, 4719775, 4, { 200.604294f, 64.690804f, -10.987260f }, 0.991760f, -0.736456f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2004068, 0, 4719776, 4, { 206.716095f, 64.690811f, 3.346290f }, 0.991760f, -0.921409f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2004069, 0, 4719777, 4, { 235.736603f, 64.682983f, -27.115360f }, 0.991760f, 0.613842f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2004060, 4585424, 4719782, 4, { -218.153107f, -0.000002f, -6.398464f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -217.242203, 16.191057, -7.011746 }, -0.000000, 4.422839, 9.631213, 0.530723 );

    pEObj = instance.addEObj( "unknown_10", 2004061, 4585624, 4719783, 4, { -307.270905f, 4.409851f, 14.023010f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -306.366699, 20.467428, 13.414055 }, 0.000048, 4.386396, 9.551855, 0.526350 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4724934, 4, { -326.989685f, 2.000000f, 43.114891f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Wildbananatree_4", 2004070, 4722840, 4725258, 4, { 241.380005f, 64.956383f, -12.841170f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Wildbananatree_5", 2004071, 4706917, 4725259, 4, { 234.644501f, 64.824364f, 2.652663f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2004072, 0, 4725260, 4, { 239.884903f, 64.690811f, -12.610960f }, 1.000000f, 0.600320f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2004073, 0, 4725261, 4, { 233.623596f, 64.760551f, 2.089992f }, 1.000000f, 0.684586f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer", 2004074, 0, 4725267, 4, { 191.947693f, 59.006939f, -163.899307f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer_1", 2004075, 0, 4725268, 4, { 194.472900f, 59.156731f, -165.022003f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer_2", 2004076, 0, 4725269, 4, { 196.017197f, 59.853050f, -161.548294f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer_3", 2004077, 0, 4725270, 4, { 198.798004f, 60.096630f, -162.115204f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer_4", 2004078, 0, 4725271, 4, { 199.929993f, 60.852970f, -158.189896f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Treasurecoffer_5", 2004079, 0, 4725272, 4, { 203.014206f, 61.084290f, -158.453995f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485", 2004341, 4797423, 4797433, 4, { -368.761902f, 1.900000f, 20.220869f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_1", 2004342, 4797424, 4797435, 4, { -367.525085f, 1.900000f, 26.995680f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_2", 2004343, 4797425, 4797436, 4, { -371.746185f, 1.900000f, 32.584270f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_3", 2004338, 4797426, 4797437, 4, { -362.507385f, 1.900000f, 48.482269f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_4", 2004339, 4797427, 4797438, 4, { -355.184601f, 1.899924f, 47.853260f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_5", 2004340, 4797428, 4797439, 4, { -349.628601f, 1.899914f, 52.138340f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_6", 2004335, 4797429, 4797440, 4, { -334.406708f, 1.899990f, 43.799950f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_7", 2004336, 4797430, 4797442, 4, { -336.870087f, 1.900000f, 37.104382f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_8", 2004337, 4797431, 4797443, 4, { -332.837006f, 1.900000f, 30.666309f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_9", 2004344, 4797421, 4797444, 4, { -341.024414f, 1.880961f, 15.649740f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_10", 2004345, 4797419, 4797445, 4, { -348.232788f, 1.900000f, 15.852800f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "sgvf_w_btl_b0485_11", 2004346, 4797422, 4797446, 4, { -353.540588f, 1.899946f, 11.553900f }, 1.000000f, -0.000000f, 0 ); 
    // States -> omen (id: 3) fukidasi (id: 4) end_0f (id: 5) end_anm (id: 6) omen1 (id: 8) 

    pEObj = instance.addEObj( "unknown_13", 2004129, 0, 4895780, 4, { -80.000000f, 44.200001f, -124.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Ropebindings", 2006084, 0, 5908237, 4, { 236.916901f, 65.539688f, -23.214291f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2004812, 0, 5933081, 4, { 220.599594f, 64.682983f, -5.874817f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( HullbreakerIsle );