#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class SohmAl : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SohmAl() : Sapphire::ScriptAPI::InstanceContentScript( 37 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5777084, 5777389, 5, { -267.602997f, -18.376320f, 282.751190f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -267.602997, -16.376320, 279.751190 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -267.593201, -16.376320, 285.751190 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -264.602997, -16.376320, 282.755066 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -270.602997, -16.376320, 282.762177 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -269.703003, -16.376320, 280.651184 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -265.502991, -16.376320, 284.851196 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -265.502991, -16.376320, 280.651184 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -269.703003, -16.376320, 284.851196 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5777414, 4, { -278.421387f, -17.669189f, 277.700714f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2005284, 5773453, 5777688, 4, { -274.538086f, -4.016628f, 191.237701f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2005285, 5773460, 5777689, 4, { -196.123306f, 3.106796f, 187.990906f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2005286, 5773461, 5777690, 4, { -171.931305f, 2.815973f, 206.485794f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2005278, 5772621, 5777691, 4, { -253.212296f, -2.894600f, 189.267303f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -253.119431, 2.064025, 189.498550 }, -0.000000, 8.512714, 7.871510, 1.222825 );
    pEObj->addCollisionBox( { -247.932724, -1.760577, 189.226959 }, -0.000000, 0.615152, 2.677956, 0.615152 );
    pEObj->addCollisionBox( { -258.844513, -0.137214, 189.526947 }, -0.000000, 0.772843, 4.310667, 0.772843 );

    pEObj = instance.addEObj( "unknown_7", 2005279, 5772623, 5777692, 4, { -165.063995f, 4.074061f, 197.945007f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -164.971130, 9.032686, 198.176254 }, -0.000000, 8.512714, 7.871510, 1.222825 );
    pEObj->addCollisionBox( { -159.784424, 5.208084, 197.904663 }, -0.000000, 0.615152, 2.677956, 0.615152 );
    pEObj->addCollisionBox( { -170.696213, 6.831447, 198.204651 }, -0.000000, 0.772843, 4.310667, 0.772843 );

    pEObj = instance.addEObj( "unknown_8", 2005280, 5852453, 5777697, 4, { 335.063385f, 114.335999f, -89.093300f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 335.070221, 116.850571, -89.100006 }, -0.000000, 8.016415, 3.514576, 1.999545 );

    pEObj = instance.addEObj( "unknown_9", 2005281, 5777403, 5777718, 4, { 247.495102f, 126.954300f, -30.577419f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 247.733902, 137.542404, -30.329664 }, -0.000000, 12.000000, 14.800000, 4.300000 );

    pEObj = instance.addEObj( "unknown_10", 2005282, 5773504, 5777723, 4, { -173.859894f, 324.834686f, -273.653503f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -173.128143, 329.840698, -271.609772 }, 0.258359, 13.154850, 7.755812, 5.415190 );

    pEObj = instance.addEObj( "unknown_11", 2005283, 5773503, 5777725, 4, { -191.639694f, 329.656799f, -321.158691f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -190.907944, 334.662811, -319.114960 }, 0.258359, 13.154850, 7.755812, 5.415190 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5777774, 4, { -142.306107f, 11.741690f, 188.300797f }, 1.000000f, 0.660768f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 5777776, 5777775, 4, { -146.759598f, 9.382987f, 191.177994f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -146.759598, 15.226433, 191.177994 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 5777778, 5777777, 4, { -126.024696f, 11.736150f, 144.580200f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -126.024696, 17.579596, 144.580200 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2002735, 0, 5777976, 4, { 165.208603f, 137.478806f, -62.228100f }, 1.000000f, -0.155188f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_2", 2002872, 5777792, 5777977, 4, { 166.178696f, 137.607697f, -62.706631f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 166.178696, 143.451141, -62.706631 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_wide", 2002872, 5777793, 5777978, 4, { 180.090302f, 138.237793f, -115.812103f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 180.090302, 140.737793, -115.812103 }, -0.000000, 16.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 5777992, 4, { -112.464798f, 348.165985f, -368.176514f }, 1.000000f, 0.335726f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_3", 2002872, 5777990, 5777994, 4, { -112.426399f, 348.165985f, -371.392487f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -112.426399, 354.009430, -371.392487 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_4", 2002872, 5777991, 5777995, 4, { -89.965149f, 348.204498f, -416.112213f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -89.965149, 354.047943, -416.112213 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5777996, 4, { -92.610641f, 348.164886f, -410.511993f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( SohmAl );