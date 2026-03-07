#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class Sastasha : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Sastasha() : Sapphire::ScriptAPI::InstanceContentScript( 4 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "unknown_0", 2000211, 0, 3280858, 4, { 367.827087f, 47.400051f, -226.694305f }, 4.714991f, 0.000432f, 0 ); 

    pEObj = instance.addEObj( "Bluecoralformation", 2000213, 3668215, 3280868, 4, { 75.869797f, 35.101421f, -32.537209f }, 0.930753f, 0.000240f, 0 ); 

    pEObj = instance.addEObj( "Redcoralformation", 2000214, 3668214, 3280879, 4, { 88.769371f, 31.135691f, -40.869640f }, 0.930753f, 0.000240f, 0 ); 

    pEObj = instance.addEObj( "Greencoralformation", 2000215, 3668216, 3280932, 4, { 64.988159f, 33.672821f, -56.690559f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Inconspicuousswitch", 2000216, 3653858, 3280956, 4, { 62.907951f, 33.969521f, -31.172279f }, 1.000000f, -1.396264f, 0 ); 

    pEObj = instance.addEObj( "Hiddendoor", 2000217, 3653517, 3280959, 4, { 59.000000f, 32.000000f, -35.000000f }, 1.000000f, -2.007129f, 0 ); 
    pEObj->addCollisionBox( { 59.048332, 39.016666, -35.022537 }, -2.007129, 8.800000, 7.718333, 0.738304 );

    pEObj = instance.addEObj( "Rambadedoor", 2000225, 3653865, 3281037, 4, { -35.299999f, 24.000000f, 60.799999f }, 1.000000f, -2.007129f, 0 ); 
    pEObj->addCollisionBox( { -35.299999, 29.043749, 60.799999 }, -2.007129, 7.260001, 5.795626, 0.300003 );

    pEObj = instance.addEObj( "Captainsquarters", 2000227, 3687697, 3281045, 4, { -95.044670f, 20.513069f, 172.039597f }, 0.991789f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -95.044525, 23.561892, 172.039444 }, 0.000048, 3.685471, 3.353819, 0.486778 );

    pEObj = instance.addEObj( "WaveriderGate", 2000231, 3655909, 3281133, 4, { -130.600006f, 16.000000f, 156.800003f }, 1.000000f, -2.007129f, 0 ); 
    pEObj->addCollisionBox( { -130.600006, 21.043749, 156.800003 }, -2.007129, 7.260001, 5.795626, 0.300003 );

    pEObj = instance.addEObj( "TheHole", 2000232, 3656260, 3281161, 4, { -36.000000f, 16.500000f, 163.300003f }, 1.000000f, 1.047198f, 0 ); 
    pEObj->addCollisionBox( { -36.000000, 22.125000, 163.300003 }, 2.094395, 7.590004, 6.187500, 0.525011 );

    pEObj = instance.addEObj( "Rambadedoor_1", 2000236, 3655908, 3281175, 4, { -190.000000f, 7.000000f, 252.000000f }, 1.000000f, -2.443461f, 0 ); 
    pEObj->addCollisionBox( { -190.000000, 12.043749, 252.000000 }, -2.443461, 7.260001, 5.795626, 0.300003 );

    pEObj = instance.addEObj( "unknown_3", 2000235, 3656262, 3281178, 4, { -156.500000f, 8.600000f, 252.500000f }, 1.000000f, 1.134464f, 0 ); 
    pEObj->addCollisionBox( { -156.500000, 14.225000, 252.500000 }, 2.007129, 7.590004, 6.187500, 0.525011 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 3281180, 4, { -314.279114f, 5.630589f, 348.735596f }, 0.900235f, 0.000336f, 0 ); 

    pEObj = instance.addEObj( "Giantclam", 2000222, 4208408, 3284776, 4, { 181.170303f, 32.104599f, -128.069000f }, 0.991789f, -0.862350f, 0 ); 
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8) 

    pEObj = instance.addEObj( "WaveriderGatekey", 2000255, 0, 3332312, 4, { -95.515343f, 20.000000f, 177.197800f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "KeytotheHole", 2000256, 0, 3332313, 4, { -38.076599f, 17.232731f, 158.839401f }, 0.991760f, 1.561760f, 0 ); 

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1", 2000260, 4208409, 3424283, 4, { 166.318695f, 30.735420f, -128.312103f }, 0.991789f, 0.481030f, 0 ); 
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8) 

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_1", 2000261, 4208410, 3425471, 4, { 158.800598f, 28.586321f, -76.340927f }, 0.991789f, 1.471638f, 0 ); 
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8) 

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_2", 2000262, 4208411, 3425472, 4, { 125.463402f, 29.260550f, -51.934608f }, 0.991789f, -0.375975f, 0 ); 
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8) 

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_3", 2000263, 4208412, 3425473, 4, { 126.070198f, 28.913260f, -99.908722f }, 1.000000f, 0.020540f, 0 ); 
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8) 

    pEObj = instance.addEObj( "sgbg_s1d1_p1_shel1_4", 2000264, 4208413, 3425474, 4, { 97.055313f, 27.081551f, -70.264381f }, 0.991789f, -0.618915f, 0 ); 
    // States -> vf_kai_off (id: 4) vf_kai_on (id: 5) vf_kai_pop (id: 6) close_open (id: 7) open_close (id: 8) 

    pEObj = instance.addEObj( "Unnaturalripples", 2000405, 3992454, 3741845, 4, { -301.973206f, 6.500000f, 300.029388f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Unnaturalripples_1", 2000406, 3992452, 3741894, 4, { -302.037598f, 6.500000f, 336.047302f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Unnaturalripples_2", 2000407, 3992449, 3741895, 4, { -338.036499f, 6.500000f, 300.206512f }, 0.991789f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Unnaturalripples_3", 2000408, 3992453, 3741897, 4, { -337.929596f, 6.500000f, 335.975311f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4033735, 4, { 344.705688f, 43.781551f, -217.365997f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2001504, 4323996, 4036038, 4, { 94.597588f, 26.865030f, -68.584061f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 94.597588, 29.365030, -68.584061 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0249", 2001505, 4323997, 4036039, 4, { 95.510597f, 26.620729f, -67.853653f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_line_on (id: 10) vf_line_of (id: 11) 

    pEObj = instance.addEObj( "unknown_2", 2001539, 3653864, 4036041, 4, { -158.560898f, 8.099012f, 214.344803f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -158.546890, 11.053966, 214.344666 }, 0.000048, 3.063308, 3.700636, 0.505798 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094_1", 2001540, 4056793, 4036043, 4, { -163.598602f, 8.026373f, 214.030106f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgpl_s1d1_bosswall", 2001508, 4236989, 4036045, 4, { -303.983612f, 5.576412f, 276.214111f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -303.969604, 8.076412, 276.214111 }, -0.000000, 5.250000, 4.000000, 0.750000 );
    pEObj->addCollisionBox( { -259.041504, 7.546412, 276.214111 }, -0.000000, 10.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgpl_s1d1_bossline", 2001509, 4236990, 4036046, 4, { -305.302002f, 5.542851f, 275.750885f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2001506, 3653862, 4056797, 4, { -9.239832f, 24.789940f, 35.778252f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -9.225822, 27.744892, 35.778111 }, 0.000048, 3.063308, 3.700636, 0.505798 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094", 2001507, 4035750, 4056798, 4, { -2.841087f, 23.114571f, 38.090420f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "Bloodymemo", 2000212, 0, 4072691, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f, -0.898762f, 0 ); 

    pEObj = instance.addEObj( "Bloodymemo_1", 2001548, 0, 4072692, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f, -0.898762f, 0 ); 

    pEObj = instance.addEObj( "Bloodymemo_2", 2001549, 0, 4072693, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f, -0.898762f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 4096706, 4096707, 5, { 361.881714f, 46.092751f, -225.181305f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 361.881714, 48.092751, -228.181305 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 361.891510, 48.092751, -222.181305 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 364.881714, 48.092751, -225.177414 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 358.881714, 48.092751, -225.170334 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 359.781708, 48.092751, -227.281311 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 363.981720, 48.092751, -223.081299 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 363.981720, 48.092751, -227.281311 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 359.781708, 48.092751, -223.081299 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Captainsquarterskey", 2000250, 0, 4192068, 4, { -100.625000f, 15.600010f, 137.150696f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1d1_sghit_ctrl", 2000223, 4200832, 4200772, 4, { -24.018980f, 18.475060f, 111.404900f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -24.018980, 18.475060, 111.404900 }, -0.000000, 1.000000, 1.000000, 1.000000 );


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

EXPOSE_SCRIPT( Sastasha );