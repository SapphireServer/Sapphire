#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFractalContinuumHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFractalContinuumHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 60 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -0.015320f, 46.585819f, -330.098389f }, 1.693726f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7178420, 4, { 0.000000f, 46.597000f, -330.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2007457, 7154681, 4, { -336.809601f, -4.091716f, 270.330200f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7154670, 4, { -356.951599f, -4.091716f, 262.314697f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7154683, 4, { -357.732788f, -4.091716f, 240.942001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7178527, 4, { -322.993408f, -14.000000f, 237.739197f }, 1.000000f, 0.942478f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { -323.681213f, -13.915580f, 238.152405f }, 0.520000f, 0.942478f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7178530, 4, { -363.058411f, -14.000000f, 250.964600f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2009284, 0, 4, { -334.828705f, -13.901060f, 251.636505f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_6", 2009285, 0, 4, { -348.204712f, -13.892940f, 243.150803f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2009286, 0, 4, { -341.067108f, -13.892940f, 237.005600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7178955, 4, { -0.015300f, -0.015300f, 318.593109f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_8", 2002735, 0, 4, { -0.015320f, -0.015320f, 318.593109f }, 1.388489f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 7170984, 5, { -168.370193f, 53.116581f, -447.149506f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -165.940704f, 53.142620f, -435.801300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -0.000000f, 285.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 7141324, 4, { -0.193053f, 53.508301f, -157.354904f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2007457, 7174264, 4, { 57.117458f, 53.142620f, -213.119202f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7170395, 4, { -0.015320f, 46.597000f, -350.082092f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Allaganteleporter", 2009278, 0, 4, { 0.002865f, 46.599701f, -377.001007f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2007457, 7141398, 4, { -147.123795f, 53.529110f, -369.004913f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2007457, 7141397, 4, { -82.715157f, 42.516201f, -199.536606f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2007457, 7141396, 4, { 57.117241f, 53.527908f, -213.116699f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Tornnavigatorslogpage", 2009412, 0, 4, { -132.524704f, 53.177608f, -407.217499f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2007457, 7141895, 4, { -305.774811f, -0.751164f, 94.720772f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007457, 7167075, 4, { -291.432098f, -0.015320f, 191.088593f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Tornnavigatorslogpage_1", 2009413, 0, 4, { -202.481003f, 0.052476f, 171.440704f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007457, 7170446, 4, { 78.733200f, 20.000000f, 245.622299f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_18", 2007457, 7170445, 4, { 29.878000f, 12.000000f, 404.197998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Securityterminal", 2009276, 7188820, 4, { 67.426903f, 12.000000f, 331.441711f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Securityterminal_1", 2009277, 7188819, 4, { 0.000000f, 12.000000f, 370.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007457, 7336140, 4, { 69.068199f, 12.000000f, 332.207001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2007457, 7336141, 4, { 0.000000f, 12.000000f, 371.396515f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 7548894, 4, { -291.105286f, 0.234064f, 193.068497f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFractalContinuumHard );