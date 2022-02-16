#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SohmAl : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SohmAl() : Sapphire::ScriptAPI::InstanceContentScript( 37 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2002735, 0, 5777774, 4, { -142.306107f, 11.741690f, 188.300797f }, 1.000000f, 0.660768f, 0); 
    instance.addEObj( "sgpl_w_lvd_b0118_col_char", 2002872, 5777776, 5777775, 4, { -146.759598f, 9.382987f, 191.177994f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgpl_w_lvd_b0118_col_char_1", 2002872, 5777778, 5777777, 4, { -126.024696f, 11.736150f, 144.580200f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2002735, 0, 5777976, 4, { 165.208603f, 137.478806f, -62.228100f }, 1.000000f, -0.155188f, 0); 
    instance.addEObj( "sgpl_w_lvd_b0118_col_char_2", 2002872, 5777792, 5777977, 4, { 166.178696f, 137.607697f, -62.706631f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgpl_w_lvd_b0118_wide", 2002872, 5777793, 5777978, 4, { 180.090302f, 138.237793f, -115.812103f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2002735, 0, 5777992, 4, { -112.464798f, 348.165985f, -368.176514f }, 1.000000f, 0.335726f, 0); 
    instance.addEObj( "sgpl_w_lvd_b0118_col_char_3", 2002872, 5777990, 5777994, 4, { -112.426399f, 348.165985f, -371.392487f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgpl_w_lvd_b0118_col_char_4", 2002872, 5777991, 5777995, 4, { -89.965149f, 348.204498f, -416.112213f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Exit", 2000139, 0, 5777996, 4, { -92.610641f, 348.164886f, -410.511993f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_3", 2005284, 5773453, 5777688, 4, { -274.538086f, -4.016628f, 191.237701f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2005278, 5772621, 5777691, 4, { -253.212296f, -2.894600f, 189.267303f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2005285, 5773460, 5777689, 4, { -196.123306f, 3.106796f, 187.990906f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005286, 5773461, 5777690, 4, { -171.931305f, 2.815973f, 206.485794f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2005279, 5772623, 5777692, 4, { -165.063995f, 4.074061f, 197.945007f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2005280, 5852453, 5777697, 4, { 335.063385f, 114.335999f, -89.093300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2005281, 5777403, 5777718, 4, { 247.495102f, 126.954300f, -30.577419f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2005282, 5773504, 5777723, 4, { -173.859894f, 324.834686f, -273.653503f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2005283, 5773503, 5777725, 4, { -191.639694f, 329.656799f, -321.158691f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 5777084, 5777389, 5, { -267.602997f, -18.376320f, 282.751190f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 5777414, 4, { -278.421387f, -17.669189f, 277.700714f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SohmAl );