#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheFistoftheFatherSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheFistoftheFatherSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30025 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5786793, 5787757, 5, { -0.057753f, -21.358721f, 88.563942f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -0.057753, -19.358721, 85.563942 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -0.047951, -19.358721, 91.563942 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.942247, -19.358721, 88.567833 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.057753, -19.358721, 88.574921 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.157753, -19.358721, 86.463943 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.042247, -19.358721, 90.663940 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.042247, -19.358721, 86.463943 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.157753, -19.358721, 90.663940 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 5787762, 4, { 0.000000f, 8.000000f, -39.386002f }, 0.750000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5787763, 4, { -1.141299f, -16.781481f, 74.122673f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5787765, 5787764, 4, { -0.007763f, 8.000001f, -38.723202f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.007763, 10.500001, -38.723202 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5787769, 5787768, 4, { -0.007763f, 8.000002f, -76.255096f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.007763, 10.500002, -76.255096 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5787778, 5787776, 4, { 0.000000f, 12.000000f, -107.839302f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, 14.500000, -107.839302 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_21", 2002735, 0, 5787777, 4, { 0.000000f, 11.993800f, -108.070297f }, 0.500000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5787786, 4, { 0.035584f, -24.311769f, -187.660599f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2005032, 0, 5787797, 4, { -10.154560f, -23.900000f, -171.851105f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2005046, 0, 5787801, 4, { -13.656920f, -24.002501f, -180.132797f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2005033, 0, 5787819, 4, { -16.466789f, -24.000000f, -176.308197f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2005402, 5815199, 5840149, 4, { 1.317244f, -23.900000f, -173.937302f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_20", 2005401, 5837182, 5840150, 4, { -0.350596f, -23.900000f, -171.328796f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -0.350596, -23.900000, -171.328796 }, -0.000000, 16.000000, 16.000000, 1.200000 );

    pEObj = instance.addEObj( "unknown_23", 2005147, 5912244, 5907907, 4, { -0.186450f, 8.755365f, -27.952221f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2005148, 5835158, 5907936, 4, { -5.000000f, -4.351456f, 18.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2005149, 5835159, 5907937, 4, { 5.000000f, -4.368736f, 18.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2005150, 5835148, 5907939, 4, { -4.000000f, -3.485719f, 13.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2005151, 5835149, 5907940, 4, { 4.000000f, -3.483227f, 13.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2005315, 5835144, 5907941, 4, { -4.000000f, -2.619212f, 8.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2006035, 5835145, 5907942, 4, { 4.000000f, -2.621703f, 8.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2006053, 5835143, 5907943, 4, { -3.000000f, -1.918940f, 4.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2006054, 5835135, 5907944, 4, { 3.000000f, -1.911465f, 4.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2006055, 5835141, 5907945, 4, { -3.000000f, -1.231334f, 0.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2006056, 5835136, 5907946, 4, { 3.000000f, -1.231335f, 0.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2006058, 5835152, 5907948, 4, { -9.000000f, -3.309154f, 12.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2006057, 5835153, 5907949, 4, { -9.000000f, -3.642947f, 14.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2006060, 5835150, 5907950, 4, { 9.000000f, -3.310075f, 12.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2006059, 5835151, 5907951, 4, { 9.000000f, -3.666079f, 14.500000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2006093, 5858144, 5908324, 4, { -0.006211f, 12.000000f, -107.218903f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance_1", 2000182, 5911084, 5911086, 5, { -0.057753f, 8.090733f, -31.639650f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -0.057753, 10.090733, -34.639648 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -0.047951, 10.090733, -28.639650 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.942247, 10.090733, -31.635759 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.057753, 10.090733, -31.628674 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.157753, 10.090733, -33.739651 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.042247, 10.090733, -29.539650 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.042247, 10.090733, -33.739651 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.157753, 10.090733, -29.539650 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_colwithnavi", 2000608, 5911088, 5911227, 4, { -0.300161f, 5.743856f, -19.072269f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -0.300161, 5.743856, -19.072269 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_22", 2005147, 5905927, 5912432, 4, { -0.186450f, -20.599979f, 84.260910f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit_1", 2005313, 5908619, 5941355, 4, { 0.000000f, -23.476339f, -186.888397f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( AlexanderTheFistoftheFatherSavage );