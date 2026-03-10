#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheThousandMawsofTotoRak : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheThousandMawsofTotoRak() : Sapphire::ScriptAPI::InstanceContentScript( 1 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Waterstainednote", 2000093, 0, 2281176, 4, { -241.596100f, 4.936373f, -72.770317f }, 0.930753f, 0.000240f, 0 ); 

    pEObj = instance.addEObj( "Waterstainednote_1", 2000094, 0, 2281179, 4, { -211.121002f, 2.082635f, -67.117737f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Waterstainednote_2", 2000095, 0, 2281180, 4, { -204.427002f, -1.617569f, 21.831829f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Waterstainednote_3", 2000096, 0, 2281182, 4, { -149.074097f, -2.569309f, 101.795403f }, 0.930753f, 0.000240f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell", 2000100, 0, 2281193, 4, { -202.105804f, 0.318934f, -79.179108f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_1", 2000101, 0, 2281194, 4, { -221.659195f, -4.425579f, 54.985451f }, 0.869717f, 0.000432f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_2", 2000102, 0, 2281196, 4, { -204.699799f, -4.926546f, 88.822723f }, 0.900235f, 0.000336f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_3", 2000103, 0, 2281197, 4, { -104.023300f, -3.463795f, 104.075897f }, 0.839199f, 0.000527f, 0 ); 

    pEObj = instance.addEObj( "Magitekterminal", 2000116, 0, 2281214, 4, { -112.013199f, -4.132327f, 112.031403f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2000117, 1699196, 2281215, 4, { -95.990372f, -4.125101f, 111.985901f }, 0.991789f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -95.990372, -4.125101, 111.985901 }, 0.000048, 5.950737, 5.950737, 0.991789 );

    pEObj = instance.addEObj( "Magitekterminal_1", 2000118, 0, 2281218, 4, { -80.026077f, -8.132326f, -47.971760f }, 0.961271f, 0.000144f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2000121, 1699201, 2281240, 4, { -95.538803f, -8.133920f, -48.020191f }, 0.991789f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -95.538803, -8.133920, -48.020191 }, 0.000048, 5.950737, 5.950737, 0.991789 );

    pEObj = instance.addEObj( "unknown_1", 2000133, 0, 2339551, 4, { 185.564896f, -34.195511f, -144.640305f }, 0.900235f, 0.000336f, 0 ); 

    pEObj = instance.addEObj( "Accusationchamberdoor", 2000384, 3302267, 3642059, 4, { -207.996994f, 0.110343f, -95.749359f }, 0.961271f, 0.000144f, 0 ); 
    pEObj->addCollisionBox( { -207.996719, 2.032886, -95.749634 }, 0.000144, 2.066733, 2.114797, 0.230705 );

    pEObj = instance.addEObj( "Abacinationchamberdoor", 2000385, 3302270, 3642060, 4, { 96.210892f, -19.927860f, -112.002098f }, 0.961271f, 0.000144f, 0 ); 
    pEObj->addCollisionBox( { 96.211166, -18.005318, -112.002373 }, 0.000144, 2.066733, 2.114797, 0.230705 );

    pEObj = instance.addEObj( "unknown_6", 2000389, 3302276, 3642066, 4, { -223.993698f, 2.170142f, -111.314598f }, 0.900235f, 0.000336f, 0 ); 
    pEObj->addCollisionBox( { -223.992706, 5.140812, -111.302071 }, 0.000336, 4.951293, 4.951293, 0.900235 );

    pEObj = instance.addEObj( "unknown_7", 2000390, 3302281, 3642068, 4, { 15.396310f, -12.161490f, -31.967699f }, 0.961271f, 0.000144f, 0 ); 
    pEObj->addCollisionBox( { 15.396764, -8.989410, -31.953716 }, 0.000144, 5.286992, 5.286992, 0.961271 );

    pEObj = instance.addEObj( "unknown_8", 2000391, 3302277, 3642069, 4, { -111.986000f, -11.694670f, -63.677799f }, 0.961271f, 0.000144f, 0 ); 
    pEObj->addCollisionBox( { -111.985550, -8.522590, -63.663815 }, 0.000144, 5.286992, 5.286992, 0.961271 );

    pEObj = instance.addEObj( "unknown_9", 2000392, 3302279, 3642070, 4, { -54.326931f, -12.619540f, -135.517899f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -54.326931, -9.319662, -135.502884 }, -0.000000, 5.500000, 5.500000, 1.000000 );

    pEObj = instance.addEObj( "unknown_10", 2000393, 3302283, 3642071, 4, { 127.918297f, -24.124969f, -112.616798f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 127.918297, -20.825092, -112.601776 }, -0.000000, 5.500000, 5.500000, 1.000000 );

    pEObj = instance.addEObj( "unknown_11", 2000397, 3302282, 3649710, 4, { -66.330208f, -8.057444f, -48.020191f }, 0.961271f, 0.000144f, 0 ); 
    pEObj->addCollisionBox( { -66.329758, -4.885364, -48.006207 }, 0.000144, 5.286992, 5.286992, 0.961271 );

    pEObj = instance.addEObj( "unknown_12", 2000398, 3302278, 3649711, 4, { -103.188698f, -12.587360f, -137.701004f }, 0.991789f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -103.188545, -9.314575, -137.686264 }, 0.000048, 5.454842, 5.454842, 0.991789 );

    pEObj = instance.addEObj( "unknown_13", 2000399, 3302280, 3649712, 4, { -7.119315f, -12.783910f, -137.865402f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -7.119316, -9.484032, -137.850388 }, -0.000000, 5.500000, 5.500000, 1.000000 );

    pEObj = instance.addEObj( "unknown_14", 2000400, 3302275, 3649713, 4, { 175.723206f, -34.137970f, -140.074005f }, 0.930753f, 0.000240f, 0 ); 
    pEObj->addCollisionBox( { 175.723938, -31.066595, -140.060760 }, 0.000240, 5.119143, 5.119143, 0.930753 );

    pEObj = instance.addEObj( "Magitekphotocell_4", 2000104, 0, 3656558, 4, { -130.358597f, -8.977930f, -71.240982f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2000404, 0, 3668230, 4, { 216.937500f, -35.568851f, -142.076797f }, 0.961304f, 0.000144f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2000111, 0, 3684699, 4, { -221.057495f, -0.076355f, -113.847603f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2000112, 0, 3684701, 4, { 18.393040f, -12.250300f, -28.183680f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2000113, 0, 3684702, 4, { -109.852501f, -11.441870f, -58.962391f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2000114, 0, 3684703, 4, { -55.111301f, -12.534730f, -140.141006f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2000115, 0, 3684704, 4, { 121.910698f, -23.325809f, -110.515297f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_5", 2000105, 0, 3842620, 4, { -130.724106f, -9.414856f, -68.131592f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_6", 2000106, 0, 3842621, 4, { -130.418900f, -9.567444f, -67.856873f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_7", 2000107, 0, 3842622, 4, { -130.101807f, -9.739193f, -67.526657f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_8", 2000107, 0, 3842623, 4, { -129.796707f, -9.914070f, -67.221481f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2000041, 3879345, 3873128, 4, { 191.261795f, -36.122822f, -143.910904f }, 1.267374f, -1.570451f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 191.261795, -33.622822, -143.910904 }, -1.570451, 9.505305, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000683, 0, 3877346, 4, { 237.565506f, -38.900299f, -144.195099f }, 1.000000f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 3907927, 4, { -311.485504f, 9.496978f, -76.989082f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2000040, 0, 3910748, 4, { 191.150696f, -36.117340f, -144.592300f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_9", 2000039, 0, 3910775, 4, { -73.754570f, -6.333896f, 21.536640f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_10", 2000108, 0, 3910776, 4, { -186.655807f, -0.160111f, -10.531350f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_11", 2000109, 0, 3910777, 4, { -143.922195f, 0.079653f, 1.801933f }, 0.961271f, 0.000144f, 0 ); 

    pEObj = instance.addEObj( "Magitekphotocell_12", 2000110, 0, 3910778, 4, { -233.539398f, -0.167908f, -103.013702f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2001005, 0, 3943637, 4, { 188.864594f, -35.987011f, -144.216095f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1r1_subboss1line", 2000131, 4126014, 4126024, 4, { -117.593002f, -4.171226f, 107.608299f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1r1_subboss2line", 2000132, 4127292, 4127302, 4, { -76.504066f, -8.171217f, -41.161350f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_f1r1_subboss1wall", 2000137, 4127387, 4127388, 4, { -119.798599f, -4.165526f, 104.508904f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -119.798477, -1.686125, 104.508781 }, 0.000048, 7.438202, 3.967041, 0.743820 );
    pEObj->addCollisionBox( { -135.444214, -1.684659, 119.457832 }, -1.570748, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgpl_f1r1_subboss2wall", 2000138, 4127414, 4127421, 4, { -78.310173f, -8.133030f, -44.002850f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -78.310173, -5.633030, -44.002850 }, -0.000000, 7.500000, 4.000000, 0.750000 );
    pEObj->addCollisionBox( { -66.533173, -5.633030, -60.255852 }, -1.570451, 5.779858, 4.000000, 0.510000 );

    pEObj = instance.addEObj( "Entrance", 2000182, 4127435, 4127446, 5, { -322.238495f, 11.991770f, -78.470192f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -322.238251, 13.975148, -81.445572 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -322.228821, 13.975432, -75.495003 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -319.263123, 13.975148, -78.466286 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -325.213684, 13.975433, -78.459541 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -324.320984, 13.975290, -80.553085 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -320.155792, 13.975290, -76.387489 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -320.155609, 13.975091, -80.552887 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -324.321198, 13.975490, -76.387688 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "sgpl_f1r1_bossplusfloor", 2001152, 4374098, 4374100, 4, { 197.405899f, -39.475101f, -147.966705f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 197.405899, -39.475101, -147.966705 }, 0.000048, 0.991760, 0.991760, 0.991760 );


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

EXPOSE_SCRIPT( TheThousandMawsofTotoRak );