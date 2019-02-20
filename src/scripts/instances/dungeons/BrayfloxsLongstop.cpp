#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class BrayfloxsLongstop :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BrayfloxsLongstop() :
    Sapphire::ScriptAPI::InstanceContentScript( 8 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2001694, 0, 4, { -36.384769f, 34.915119f, -234.568405f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2001461, 0, 4, { 142.567200f, -1.266762f, 67.804497f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "RunstopHeadgate", 2001462, 3996541, 4, { 105.920601f, 1.745684f, 11.445460f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "RunstopGutgate", 2001463, 3970152, 4, { 113.391296f, -0.849704f, -33.166710f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "RunstopBackgate", 2001464, 3970154, 4, { -19.424801f, 7.919373f, -71.122383f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "LongstopHeadgate", 2001465, 3970153, 4, { -113.634499f, 1.332127f, -58.144779f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "LongstopGutgate", 2001466, 3976772, 4, { -89.831360f, 14.042510f, -96.676224f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2001584, 4086949, 4, { 106.822800f, -1.629326f, 2.541263f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2001585, 0, 4, { 110.429604f, -1.663330f, 3.311157f }, 0.991760f, 0.214809f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2001586, 4088979, 4, { 8.021301f, 5.921407f, -69.090309f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2001587, 0, 4, { 6.458210f, 5.902269f, -67.560417f }, 1.000000f, -0.788830f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2001588, 4088985, 4, { -106.298798f, -2.123102f, -10.585170f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2001589, 0, 4, { -105.172897f, -2.123102f, -10.865350f }, 1.000000f, -0.043989f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2001590, 4088991, 4, { -68.039551f, 33.716820f, -232.938904f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2001591, 0, 4, { -68.693542f, 33.682091f, -234.070496f }, 1.000000f, -1.318638f ); 
    instance.registerEObj( "Entrance", 2000182, 4097104, 5, { 122.445702f, -1.119082f, 68.403687f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 113.256897f, -1.172536f, 59.115589f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -8.639429f, 35.641689f, -234.813797f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BrayfloxsLongstop );