#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheCuffoftheFatherSavage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheCuffoftheFatherSavage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30026 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "MagitekgobwalkerGVII", 2005126, 0, 4, { -23.299919f, -27.250000f, -93.915253f }, 2.500000f, 0.000000f ); 
    instance.registerEObj( "MagitekgobwalkerGVII_1", 2005474, 0, 4, { -25.869850f, -27.250000f, -91.505951f }, 2.500000f, 0.000000f ); 
    instance.registerEObj( "MagitekgobwalkerGVII_2", 2005475, 0, 4, { -28.364830f, -27.250000f, -89.139442f }, 2.500000f, 0.000000f ); 
    instance.registerEObj( "MagitekgobwalkerGVII_3", 2005126, 0, 4, { -24.477819f, -27.250000f, -93.315643f }, 2.500000f, 0.000000f ); 
    instance.registerEObj( "MagitekgobwalkerGVII_4", 2005474, 0, 4, { -27.127260f, -27.250000f, -90.671631f }, 2.500000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2005047, 5796486, 4, { -16.006710f, 28.995720f, 121.127502f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2005047, 5796475, 4, { -15.991690f, 25.994120f, 104.104698f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2005047, 5796479, 4, { -0.042969f, -15.876210f, 39.414860f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2005047, 5796481, 4, { -0.042969f, -22.069151f, 4.294098f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Steamspoutingcontraption", 2005048, 5828187, 4, { -20.999439f, 28.890051f, 120.379700f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2005428, 5828194, 4, { -20.812780f, 25.885040f, 102.729103f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2005428, 5828205, 4, { -5.111024f, -22.178221f, 3.677231f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -19.655809f, 31.065201f, 144.212204f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_d2a2_ring1wall", 2005047, 5962936, 4, { -16.018070f, 27.033091f, 118.517899f }, 1.000000f, 0.000000f ); 
    // States -> rw01_def (id: 33) rw01_opn (id: 34) rw01_around2opn (id: 35) 
    instance.registerEObj( "sgpl_d2a2_ring3wall", 2005047, 5962937, 4, { 4.629210f, -8.535899f, 53.038620f }, 1.000000f, 0.000000f ); 
    // States -> rw03_def (id: 31) rw03_opn (id: 32) rw03_around2opn (id: 33) 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { 0.000000f, -28.000000f, -53.246899f }, 0.750000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5787859, 4, { -0.137953f, -26.000000f, -52.603008f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 5787862, 4, { 0.000000f, -26.000000f, -96.909851f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2006105, 5883005, 4, { 0.000000f, -28.000000f, -75.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2005313, 5908620, 4, { 0.000000f, -26.000000f, -110.560898f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit_1", 2000139, 0, 4, { 0.000000f, -27.991100f, -115.007500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Steamspoutingcontraption_1", 2005427, 5828202, 4, { -5.000190f, -15.985280f, 39.105530f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5787826, 5, { -16.006710f, 36.148560f, 161.008804f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Entrance_1", 2000182, 5908672, 5, { 0.002526f, -28.000019f, -23.439610f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheCuffoftheFatherSavage );