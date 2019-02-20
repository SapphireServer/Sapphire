#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SohmAlHard :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SohmAlHard() :
    Sapphire::ScriptAPI::InstanceContentScript( 49 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6610531, 4, { 171.484497f, 137.748795f, 239.483704f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 174.120697f, 137.590607f, 236.701706f }, 0.991760f, 0.698132f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007599, 6610540, 4, { 162.998398f, 137.748596f, 274.239502f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6613704, 4, { 299.153107f, 111.986000f, 138.189499f }, 0.991760f, 0.000048f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 301.151306f, 112.000000f, 141.222107f }, 0.991760f, -0.556715f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007600, 6613798, 4, { 284.901794f, 112.000000f, 109.136398f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007648, 6621383, 4, { 128.328293f, 107.293800f, -303.903107f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007649, 0, 4, { 169.258698f, 106.695999f, -298.126007f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2007650, 0, 4, { 168.423599f, 108.900002f, -315.103485f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_5", 2007651, 0, 4, { 167.744797f, 109.165802f, -335.555908f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6631462, 4, { 128.893707f, 107.000000f, -274.034393f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { 127.962402f, 107.223801f, -277.597412f }, 0.991760f, -0.000000f ); 
    instance.registerEObj( "sgvf_d2d8_b1031", 2007706, 6653690, 4, { -198.779297f, 329.243896f, 33.463009f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1031_1", 2007706, 6653700, 4, { -206.605194f, 329.253998f, 59.786411f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1031_2", 2007706, 6653718, 4, { -190.572800f, 329.253998f, 54.758789f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1031_3", 2007706, 6653721, 4, { -169.511398f, 324.396088f, 88.214813f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1031_4", 2007706, 6653723, 4, { -154.978302f, 324.396088f, 84.108612f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1031_5", 2007706, 6653726, 4, { -115.709198f, 318.959412f, 108.811996f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2007735, 6572900, 4, { -188.843201f, 329.253998f, 66.614899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007736, 6572901, 4, { -95.983841f, 318.012787f, 134.955994f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007765, 0, 4, { -166.002899f, 324.396088f, 99.648300f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1096", 2007785, 6735263, 4, { -113.389900f, 346.242401f, -11.429080f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2007784, 0, 4, { -185.825699f, 329.150208f, 67.756607f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007784, 0, 4, { -95.353699f, 317.812805f, 138.109406f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2007737, 6572914, 4, { 271.778503f, 120.866699f, 247.657700f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2007738, 6572915, 4, { 318.409912f, 114.000099f, 174.170197f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2007784, 0, 4, { 271.381592f, 121.015800f, 246.143295f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2007784, 0, 4, { 317.092896f, 114.000000f, 172.080200f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_16", 2007739, 6583747, 4, { 170.824707f, 125.108597f, -116.025803f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_17", 2007740, 6583766, 4, { 87.968140f, 114.976700f, -165.190399f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_18", 2007741, 6583828, 4, { 128.564804f, 107.608704f, -252.169403f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007761, 0, 4, { 107.591301f, 114.427399f, -119.840599f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_20", 2007773, 6583797, 4, { 137.386398f, 120.578796f, -148.604599f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2007774, 6583799, 4, { 91.874512f, 115.007202f, -129.728394f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2007775, 6648314, 4, { 79.667358f, 113.878098f, -201.079605f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_23", 2007776, 6648318, 4, { 104.478500f, 109.971703f, -225.310898f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_d2d8_b1096_1", 2007785, 6735374, 4, { 202.686295f, 126.422096f, -89.904701f }, 0.991760f, 0.698132f ); 
    instance.registerEObj( "unknown_24", 2007784, 0, 4, { 87.159088f, 115.000000f, -167.944199f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_25", 2007784, 0, 4, { 128.283905f, 106.994301f, -255.937302f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 6610262, 5, { -108.575996f, 348.171692f, -39.539310f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -115.366699f, 348.201599f, -26.746000f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 127.929398f, 107.364899f, -323.381989f }, 0.991760f, -0.017306f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SohmAlHard );