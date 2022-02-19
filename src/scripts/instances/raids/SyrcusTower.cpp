#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SyrcusTower : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SyrcusTower() : Sapphire::ScriptAPI::InstanceContentScript( 30011 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2002587, 0, 4738754, 4, { -370.000000f, 500.115387f, -199.956299f }, 0.700000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250", 2002872, 4738783, 4738784, 4, { -394.730194f, 500.000000f, -199.572800f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Exit", 2000139, 0, 4738818, 4, { -415.668213f, 500.000000f, -200.003296f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_l1r2_d2_mete2", 2004244, 4757482, 4741321, 4, { -390.384705f, 500.000000f, -194.533203f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_come_off_01 (id: 2) b4_come_off_02 (id: 3) b4_come_on_01 (id: 4) b4_come_off_03 (id: 5) b4_come_on_02 (id: 6) b4_come_on_03 (id: 7) b4_come_on_04 (id: 8) b4_come_on_05 (id: 9) b4_come_on_06 (id: 10) b4_come_fdout (id: 15) 
    instance.addEObj( "sgbg_l1r2_d2_mete2_1", 2004292, 4757483, 4757493, 4, { -401.338287f, 500.000000f, -196.787003f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_come_off_01 (id: 2) b4_come_off_02 (id: 3) b4_come_on_01 (id: 4) b4_come_off_03 (id: 5) b4_come_on_02 (id: 6) b4_come_on_03 (id: 7) b4_come_on_04 (id: 8) b4_come_on_05 (id: 9) b4_come_on_06 (id: 10) b4_come_fdout (id: 15) 
    instance.addEObj( "sgbg_l1r2_d2_mete2_2", 2004293, 4757484, 4757494, 4, { -403.504913f, 500.000000f, -196.539597f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_come_off_01 (id: 2) b4_come_off_02 (id: 3) b4_come_on_01 (id: 4) b4_come_off_03 (id: 5) b4_come_on_02 (id: 6) b4_come_on_03 (id: 7) b4_come_on_04 (id: 8) b4_come_on_05 (id: 9) b4_come_on_06 (id: 10) b4_come_fdout (id: 15) 
    instance.addEObj( "sgbg_l1r2_d2_mete2_3", 2004294, 4757485, 4757495, 4, { -405.170593f, 500.000000f, -202.118393f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_come_off_01 (id: 2) b4_come_off_02 (id: 3) b4_come_on_01 (id: 4) b4_come_off_03 (id: 5) b4_come_on_02 (id: 6) b4_come_on_03 (id: 7) b4_come_on_04 (id: 8) b4_come_on_05 (id: 9) b4_come_on_06 (id: 10) b4_come_fdout (id: 15) 
    instance.addEObj( "sgbg_l1r2_d2_mete2_4", 2004295, 4757486, 4757496, 4, { -400.173798f, 500.000000f, -200.892807f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_come_off_01 (id: 2) b4_come_off_02 (id: 3) b4_come_on_01 (id: 4) b4_come_off_03 (id: 5) b4_come_on_02 (id: 6) b4_come_on_03 (id: 7) b4_come_on_04 (id: 8) b4_come_on_05 (id: 9) b4_come_on_06 (id: 10) b4_come_fdout (id: 15) 
    instance.addEObj( "sgbg_l1r2_d2_mete2_5", 2004296, 4757487, 4757497, 4, { -395.280304f, 500.000000f, -200.854401f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_come_off_01 (id: 2) b4_come_off_02 (id: 3) b4_come_on_01 (id: 4) b4_come_off_03 (id: 5) b4_come_on_02 (id: 6) b4_come_on_03 (id: 7) b4_come_on_04 (id: 8) b4_come_on_05 (id: 9) b4_come_on_06 (id: 10) b4_come_fdout (id: 15) 
    instance.addEObj( "sgbg_l1r2_d2_mete1", 2004243, 4757498, 4741320, 4, { -400.242615f, 500.000000f, -197.116501f }, 1.000000f, 0.000000f, 0); 
    // States -> b4_mete_off_01 (id: 1) b4_mete_off_02 (id: 2) b4_mete_on_01 (id: 3) b4_mete_off_03 (id: 4) b4_mete_on_02 (id: 5) b4_mete_on_03 (id: 6) b4_mete_on_04 (id: 7) b4_mete_on_05 (id: 8) b4_mete_on_06 (id: 9) b4_mete_fdout (id: 18) 
    instance.addEObj( "unknown_1", 2004354, 0, 4866725, 4, { -397.029785f, 500.000000f, -196.979202f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2004355, 0, 4867501, 4, { -459.071411f, 506.001801f, -196.468506f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2004236, 4759659, 4725455, 4, { -1.397732f, -589.900085f, -194.801498f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004237, 0, 4725457, 4, { 2.182007f, -589.929077f, -198.077499f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2002587, 0, 4725483, 4, { -0.015320f, -590.000000f, -152.513794f }, 0.686646f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250_1", 2002872, 4725495, 4725572, 4, { 0.228821f, -590.000000f, -174.995300f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_6", 2002587, 0, 4738652, 4, { -0.883440f, -4.000000f, -141.001801f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250_2", 2002872, 4738653, 4738679, 4, { -0.991882f, 0.000000f, -196.720993f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_7", 2004245, 4711823, 4741385, 4, { -0.379705f, 0.000000f, -145.342300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2004246, 4711824, 4741386, 4, { 0.710614f, 0.000000f, -199.171204f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_9", 2004247, 4711825, 4741387, 4, { 0.439319f, 0.000001f, -201.553802f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004248, 4711828, 4741388, 4, { 0.202690f, 0.000000f, -199.270599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2004250, 4867789, 4741937, 4, { -0.142451f, -0.000001f, -199.916000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2004251, 4771487, 4741939, 4, { 6.207808f, 0.025001f, -197.716293f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2004252, 4771488, 4741940, 4, { 0.912855f, 0.000000f, -200.229401f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2004253, 4771264, 4741995, 4, { -0.249095f, 0.000000f, -200.632095f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2004540, 0, 4894129, 4, { 2.310606f, 0.000000f, -199.315903f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2002587, 0, 4738749, 4, { 16.500000f, 600.000000f, -175.000000f }, 0.700000f, -0.584685f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250_3", 2002872, 4738751, 4738752, 4, { 6.038667f, 600.000000f, -191.625595f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_17", 2004249, 0, 4741821, 4, { 0.534058f, 600.000000f, -204.089493f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_18", 2004372, 0, 4876906, 4, { 2.491530f, 600.000000f, -197.343201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2004498, 0, 4890510, 4, { 7.797371f, 600.000000f, -197.855301f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2002587, 0, 4725556, 4, { 0.000000f, -700.000000f, 79.955803f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250_4", 2002872, 4725557, 4725558, 4, { -0.328611f, -700.000000f, 53.732899f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_21", 2002587, 0, 4725578, 4, { 29.805300f, -400.000000f, -200.000000f }, 0.700000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250_5", 2002872, 4725580, 4725586, 4, { 5.249963f, -400.000000f, -199.878006f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_22", 2002587, 0, 4738680, 4, { 0.000000f, 200.000000f, -229.757797f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250_6", 2002872, 4738682, 4738720, 4, { 0.542766f, 199.899994f, -231.713898f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Entrance", 2000182, 4723157, 4723158, 5, { -0.325782f, -897.940918f, 371.584106f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Allaganteleporter", 2004154, 4645409, 4723186, 4, { -5.014030f, -894.781982f, 324.891296f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_1", 2004155, 4645410, 4724049, 4, { 8.084772f, -708.339111f, 175.045898f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_2", 2004158, 4645412, 4724066, 4, { 7.971835f, -598.362915f, -76.990211f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_3", 2004156, 4652344, 4724154, 4, { 72.370857f, -402.456696f, -206.931000f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_4", 2004159, 4645415, 4724182, 4, { -6.906353f, -2.365848f, -126.353897f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_5", 2004157, 4645417, 4724203, 4, { -6.845924f, 197.827805f, -274.836700f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_6", 2004160, 4651219, 4724229, 4, { 29.220949f, 599.725220f, -140.581406f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Allaganteleporter_7", 2004161, 4636419, 4724240, 4, { -317.290192f, 500.821808f, -189.288193f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_23", 2004164, 4738634, 4895649, 4, { 0.448093f, -700.000000f, 104.558601f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2004173, 4720323, 4895650, 4, { 0.019809f, -590.000000f, -150.897903f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2004167, 4711138, 4895651, 4, { 44.295219f, -403.598602f, -199.389694f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_26", 2004176, 4710992, 4895652, 4, { 0.045776f, 0.000000f, -180.284607f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_27", 2004170, 4710494, 4895653, 4, { 0.449279f, 196.100006f, -262.072296f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_28", 2004179, 4742340, 4895654, 4, { 28.708071f, 598.000183f, -156.658600f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SyrcusTower );