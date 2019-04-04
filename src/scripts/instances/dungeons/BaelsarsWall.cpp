#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class BaelsarsWall :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BaelsarsWall() :
    Sapphire::ScriptAPI::InstanceContentScript( 48 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -173.966797f, 3.049999f, 52.443710f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6588628, 4, { -173.612198f, 3.049997f, 52.688000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6588629, 4, { -154.029907f, 3.049906f, 72.262756f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 95.577843f, -300.028412f, 0.707827f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6588652, 4, { 95.163948f, -300.028198f, 0.952097f }, 1.000000f, -1.570451f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6588653, 4, { 135.748398f, -300.000092f, 0.172490f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6588667, 4, { 371.527588f, 212.000000f, 391.566010f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 371.795685f, 212.000000f, 391.643097f }, 1.000000f, -1.570451f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -230.764297f, -0.932137f, -173.143600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 352.071411f, 212.000000f, 391.988892f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 6562675, 5, { -228.044006f, -0.901261f, -183.153198f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Imperialidentificationkey", 2007567, 0, 4, { -202.837997f, -0.966086f, -62.488140f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Securityterminal", 2007571, 6640773, 4, { -206.023102f, 2.815013f, -48.897739f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007575, 6501039, 4, { -203.861694f, 1.804717f, -49.827511f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Imperialidentificationkey_1", 2007568, 0, 4, { -176.569397f, 2.150000f, 17.400681f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Securityterminal_1", 2007572, 6516973, 4, { -187.083206f, 2.707914f, 19.031469f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007576, 6502290, 4, { -174.854904f, 2.100000f, 23.458460f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007776, 6500492, 4, { -126.770897f, 2.000089f, 72.952606f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Controlpanel", 2007580, 0, 4, { -0.003809f, -299.760315f, 0.024599f }, 2.000000f, 0.000048f ); 
    instance.registerEObj( "Controlpanel_1", 2007581, 0, 4, { 177.511993f, -298.963196f, 4.224624f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Controlpanel_2", 2007582, 6523203, 4, { 177.434006f, -298.072601f, 6.243333f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007601, 6516974, 4, { 176.321396f, -299.105713f, 0.250570f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Imperialidentificationkey_2", 2007569, 0, 4, { 317.032288f, 169.000107f, 230.153503f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Securityterminal_2", 2007573, 6488516, 4, { 320.921600f, 169.867996f, 243.976807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007577, 6488509, 4, { 328.225189f, 169.000107f, 244.581894f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007578, 6777152, 4, { 382.790100f, 203.000000f, 357.169403f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BaelsarsWall );