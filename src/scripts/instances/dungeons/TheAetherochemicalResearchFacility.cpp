#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheAetherochemicalResearchFacility : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheAetherochemicalResearchFacility() : Sapphire::ScriptAPI::InstanceContentScript( 38 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5782651, 5783009, 5, { -332.999207f, 400.000000f, -297.435211f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -332.999207, 402.000000, -300.435211 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -332.989410, 402.000000, -294.435211 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -329.999207, 402.000000, -297.431335 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -335.999207, 402.000000, -297.424225 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -335.099213, 402.000000, -299.535217 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -330.899200, 402.000000, -295.335205 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -330.899200, 402.000000, -299.535217 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -335.099213, 402.000000, -295.335205 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5783028, 4, { -309.444885f, 400.000000f, -287.942108f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2005295, 5698524, 5785890, 4, { -232.841797f, 402.044098f, -353.718689f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -232.677597, 409.763916, -353.631439 }, -0.000000, 12.455900, 8.144122, 2.003951 );

    pEObj = instance.addEObj( "unknown_12", 2005296, 5698521, 5785891, 4, { -177.212006f, 398.044098f, -361.393311f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -177.047806, 405.763916, -361.306061 }, -0.000000, 12.455900, 8.144122, 2.003951 );

    pEObj = instance.addEObj( "unknown_13", 2005297, 5698523, 5785892, 4, { -162.152802f, 398.044098f, -369.069885f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -161.988602, 405.763916, -368.982635 }, -0.000000, 12.455900, 8.144122, 2.003951 );

    pEObj = instance.addEObj( "unknown_14", 2005298, 5698522, 5785893, 4, { -176.852295f, 398.044098f, -382.745087f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -176.688095, 405.763916, -382.657837 }, -0.000000, 12.455900, 8.144122, 2.003951 );

    pEObj = instance.addEObj( "unknown_15", 2005299, 5886628, 5786223, 4, { -168.304993f, 394.044098f, -296.534088f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -168.304993, 396.577332, -296.534088 }, -0.000000, 8.022142, 3.236665, 2.323275 );

    pEObj = instance.addEObj( "unknown_16", 2005300, 5686456, 5786224, 4, { 28.763180f, 209.979401f, 211.474701f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2005301, 5686457, 5786226, 4, { 100.159401f, 220.000000f, 272.267090f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5786706, 4, { -133.497498f, 394.924286f, -295.299713f }, 1.400000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 5786705, 5786707, 4, { -140.602203f, 394.529388f, -295.997314f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -140.602203, 400.372833, -295.997314 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "unknown_4", 2002735, 0, 5786712, 4, { 228.611694f, 225.066895f, 272.124695f }, 1.400000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 5786711, 5786713, 4, { 220.192200f, 224.639603f, 271.691895f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 220.192200, 230.483047, 271.691895 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_2", 2002872, 5786715, 5786717, 4, { 265.170685f, 225.066895f, 271.760712f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 265.170685, 230.910339, 271.760712 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "unknown_5", 2002735, 0, 5786725, 4, { 230.175598f, -96.457947f, -160.689804f }, 1.400000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_3", 2002872, 5786724, 5786726, 4, { 231.302200f, -96.512383f, -143.853394f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 231.302200, -90.668938, -143.853394 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2005310, 5698551, 5787154, 4, { -81.047653f, 394.430786f, -296.243713f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -81.047928, 405.006531, -279.885162 }, 0.000048, 7.142378, 10.930895, 0.656411 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5858705, 4, { 230.936203f, -456.457886f, 65.952606f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2002735, 0, 5859270, 4, { 229.505203f, -456.329193f, 99.828033f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_col_char_4", 2002872, 5859273, 5859276, 4, { 229.632996f, -456.457886f, 93.179420f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 229.632996, -450.614441, 93.179420 }, -0.000000, 7.500000, 7.343446, 0.750000 );

    pEObj = instance.addEObj( "Liftterminal", 2005308, 0, 5861191, 4, { 203.525803f, -28.163019f, 195.849503f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "Liftterminal_1", 2005309, 0, 5861279, 4, { 229.755005f, -59.269020f, 94.956909f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_20", 2005306, 5815811, 5888686, 4, { -359.609406f, -299.984009f, -249.805496f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -368.324097, -296.784912, -249.195007 }, 0.000048, 0.569692, 5.495678, 5.528988 );
    pEObj->addCollisionBox( { -363.043060, -296.785583, -257.899353 }, 1.047245, 0.569692, 5.495678, 5.810368 );

    pEObj = instance.addEObj( "Liftterminal_2", 2005307, 0, 5888695, 4, { -351.717102f, -299.983887f, -250.003098f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2005293, 5889119, 5888777, 4, { 28.122299f, 209.979401f, 220.050293f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2005294, 5889137, 5888778, 4, { 111.924896f, 219.958694f, 271.931000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2006038, 5891863, 5901002, 4, { -103.765701f, 394.988708f, -312.957214f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006039, 5891860, 5901003, 4, { -102.201103f, 394.988708f, -278.118988f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2006040, 5855034, 5901005, 4, { 230.235901f, -96.457947f, -181.102600f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2007168, 0, 6265765, 4, { 248.035400f, 225.116302f, 271.869995f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2007177, 6268147, 6275961, 4, { 230.075500f, -456.357605f, 58.431438f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2007178, 6275911, 6275973, 4, { 230.467407f, -456.457886f, 79.306190f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheAetherochemicalResearchFacility );