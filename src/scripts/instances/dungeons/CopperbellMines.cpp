#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CopperbellMines : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CopperbellMines() : Sapphire::ScriptAPI::InstanceContentScript( 3 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2000068, 0, 4056146, 4, { 44.405670f, -9.596272f, -115.661201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2001526, 4056196, 4056201, 4, { 42.862770f, -9.734462f, -118.006302f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2000069, 0, 4056691, 4, { 35.776779f, -38.010250f, 86.627357f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2001527, 4056695, 4056693, 4, { 34.781620f, -38.026581f, 85.051003f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2001528, 4056696, 4056746, 4, { -93.129417f, -57.842449f, 54.637360f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2000037, 0, 4056747, 4, { -90.569702f, -57.860081f, 55.157581f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2000266, 3163462, 3445358, 4, { -73.202423f, -55.895020f, 1.983328f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2000267, 3163472, 3445359, 4, { -123.490501f, -56.689388f, 36.337471f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Improvedblastingdevice", 2000184, 4093714, 4086977, 4, { 30.553780f, -37.974628f, 110.802399f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2000239, 4093740, 4094345, 4, { 34.836300f, -38.021832f, 115.035202f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 2790306, 4, { -100.877403f, -56.042820f, -15.206130f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_6", 2000186, 3163464, 4217260, 4, { -127.532204f, -56.557701f, 13.108460f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tinykey", 2000159, 0, 2790159, 4, { -209.307999f, 23.619301f, -210.254105f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Sealedblastingdoor", 2000160, 4025573, 2790160, 4, { -205.498901f, 23.819269f, -208.536697f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2000161, 4024332, 2790162, 4, { -184.037094f, 13.828580f, -208.114502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Liftlever", 2000162, 4018210, 2790163, 4, { -191.827606f, 23.433090f, -205.127106f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Liftlever_1", 2000163, 0, 4055428, 4, { -183.969498f, 24.006029f, -205.712097f }, 0.991760f, 1.570451f, 0); 
    instance.addEObj( "unknown_8", 2001559, 4023678, 4075277, 4, { -189.593399f, 23.392031f, -208.209396f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2000182, 4085080, 4086827, 5, { -253.156403f, 23.528379f, -174.613998f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 4087033, 4, { -237.184906f, 21.988159f, -166.420502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_9", 2000167, 0, 2790171, 4, { -81.437439f, -5.447510f, -171.343597f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2000168, 3163094, 2790172, 4, { -74.540337f, -5.935791f, -162.462799f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Firesand", 2000169, 0, 2790176, 4, { -20.828609f, -8.071711f, -161.638901f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Blastingdevice", 2000170, 4053820, 2790177, 4, { 41.374290f, -9.249741f, -135.238800f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Firesand_1", 2000172, 0, 2790180, 4, { 53.101452f, -3.845266f, -153.826401f }, 0.991760f, 0.901467f, 0); 
    instance.addEObj( "Sealedblastingdoor_1", 2000173, 4025574, 2790181, 4, { 43.376751f, -9.109680f, -58.134281f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Liftlever_2", 2000174, 4018213, 2790184, 4, { 55.344479f, -8.804504f, -1.751919f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Liftlever_3", 2000175, 0, 2790185, 4, { 55.965420f, -8.264337f, 6.017679f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Liftlever_4", 2000166, 0, 2790166, 4, { -183.969498f, -6.008533f, -205.992905f }, 0.991760f, -1.570451f, 0); 
    instance.addEObj( "Liftlever_5", 2000165, 4018211, 4055460, 4, { -176.318695f, -6.546204f, -210.956100f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tinykey_1", 2000178, 0, 2790239, 4, { 42.903980f, -9.979086f, -69.086594f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2001529, 4024331, 4056538, 4, { 58.267658f, -19.085461f, 6.177349f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Powderchamber", 2001536, 0, 4056732, 4, { 43.821098f, -8.847800f, -128.329102f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2001560, 4023676, 4075279, 4, { -178.386200f, -6.605137f, -207.831696f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2001561, 4023677, 4075280, 4, { 58.670898f, -8.835022f, 0.472961f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_14", 2000171, 3163067, 2790178, 4, { 43.472900f, -9.262273f, -126.115898f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Liftlever_6", 2000176, 4018212, 2790225, 4, { 61.119492f, -37.911671f, 13.438640f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Liftlever_7", 2000177, 0, 2790226, 4, { 55.985229f, -38.263531f, 6.003702f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Firesand_2", 2000179, 0, 2790240, 4, { 14.572330f, -42.069149f, 43.503422f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Blastingdevice_1", 2000180, 4053821, 2790241, 4, { 56.726372f, -37.999741f, 47.990452f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Firesand_3", 2001531, 0, 4056589, 4, { 93.184647f, -41.640049f, 67.395599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Firesand_4", 2001532, 0, 4056659, 4, { 38.064529f, -38.712662f, 60.511768f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Firesand_5", 2001533, 0, 4056699, 4, { 31.755930f, -37.938789f, 114.646599f }, 1.000000f, -1.263692f, 0); 
    instance.addEObj( "Blastingdevice_2", 2001534, 4053822, 4056715, 4, { 10.162710f, -36.846409f, 106.696999f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_15", 2001535, 3163445, 4056716, 4, { 5.569519f, -38.040829f, 111.711197f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Powderchamber_1", 2001537, 0, 4056734, 4, { 58.852821f, -37.774250f, 55.076962f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Powderchamber_2", 2001538, 0, 4056736, 4, { 6.485046f, -37.171558f, 113.633904f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_16", 2001562, 4023675, 4075282, 4, { 57.846920f, -38.864811f, 11.550960f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_17", 2000181, 3163079, 2790242, 4, { 57.479050f, -38.038540f, 56.536980f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2000185, 3163454, 2790295, 4, { -55.588661f, -37.033691f, 94.193893f }, 0.991789f, 0.000048f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CopperbellMines );