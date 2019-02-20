#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFieldsofGloryShatter :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFieldsofGloryShatter() :
    Sapphire::ScriptAPI::InstanceContentScript( 50005 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0286", 2007022, 7583664, 4, { -263.444885f, 52.175270f, -209.921402f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgvf_w_lvd_b0286_1", 2007023, 7583666, 4, { -91.249367f, 27.082781f, 248.251297f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgvf_w_lvd_b0286_2", 2007024, 7583668, 4, { 262.704590f, 7.555402f, -83.636391f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "sgbg_r2p1_q0_col02", 2007038, 7583676, 4, { -33.290001f, 8.500000f, -64.930000f }, 1.000000f, 0.345772f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col02_1", 2007039, 7583680, 4, { -29.181200f, 4.895900f, -181.130005f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col02_2", 2007040, 7583684, 4, { 49.409801f, 1.000000f, 95.446404f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col02_3", 2007041, 7583688, 4, { -139.203201f, 2.000000f, 42.698399f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01", 2007042, 7583692, 4, { 10.250100f, 7.501600f, -73.703102f }, 1.000000f, -0.207694f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_1", 2007126, 7583696, 4, { -21.009300f, 6.445800f, -124.468399f }, 1.000000f, -1.350824f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_2", 2007044, 7583700, 4, { -57.941700f, 7.532000f, -89.861702f }, 1.000000f, -0.478128f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_3", 2007043, 7583704, 4, { -28.053699f, 7.586800f, -20.808001f }, 1.000000f, -0.207694f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_4", 2007124, 7583708, 4, { -81.065201f, 8.327300f, -23.711300f }, 1.000000f, 0.491354f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_5", 2007122, 7583712, 4, { 17.876400f, 7.001300f, 11.047300f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_6", 2007053, 7583716, 4, { -126.529999f, 35.526501f, -132.360001f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_7", 2007125, 7583720, 4, { -224.454102f, 30.212000f, -33.290001f }, 1.000000f, 0.001382f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_8", 2007052, 7583724, 4, { -148.077499f, 48.772800f, -3.141700f }, 1.000000f, -0.003491f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_9", 2007051, 7583728, 4, { -195.641693f, 37.440800f, 80.677399f }, 1.000000f, 1.473960f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_10", 2007123, 7583732, 4, { -107.700996f, 10.249100f, 150.690598f }, 1.000000f, -0.528624f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_11", 2007050, 7583736, 4, { -8.180000f, 31.300200f, 107.550003f }, 1.000000f, -0.207694f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_12", 2007049, 7583740, 4, { 75.684898f, 35.111000f, 149.223801f }, 1.000000f, -0.207694f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_13", 2007048, 7583744, 4, { 174.059998f, 30.587099f, 122.660004f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_14", 2007047, 7583748, 4, { 175.149307f, 0.118000f, 8.585100f }, 1.000000f, -0.383869f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_15", 2007046, 7583752, 4, { 121.235901f, 29.898701f, -190.225006f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_16", 2007121, 7583756, 4, { 29.201799f, 37.825001f, -217.776505f }, 1.000000f, 1.518110f ); 
    instance.registerEObj( "sgbg_r2p1_q0_col01_17", 2007045, 7583760, 4, { -43.203499f, 42.615501f, -229.343597f }, 1.000000f, 0.535781f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFieldsofGloryShatter );