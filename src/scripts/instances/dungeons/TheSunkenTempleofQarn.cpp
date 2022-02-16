#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSunkenTempleofQarn : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSunkenTempleofQarn() : Sapphire::ScriptAPI::InstanceContentScript( 9 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2000413, 0, 4064745, 4, { -211.000000f, 0.000002f, 2.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "TheWarden", 2000414, 0, 4064748, 4, { -111.221802f, 14.346200f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "TheFlameofMagic", 2000415, 3878710, 4064752, 4, { 8.987488f, -17.399031f, 53.998150f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "TheFruitofKnowledge", 2000416, 3878713, 4064753, 4, { 9.005134f, -17.409531f, -53.991970f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "TheGemofAffluence", 2000417, 3878714, 4064755, 4, { -151.210800f, -10.391200f, -62.004131f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "TheHelmofMight", 2000418, 3878715, 4064756, 4, { -151.162506f, -7.407125f, 61.966801f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Stonepedestal", 2000419, 0, 4064759, 4, { 117.361099f, -3.708839f, -23.835030f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "DoortotheVaultofAether", 2000420, 3692635, 4064760, 4, { 125.343102f, -0.964693f, -20.363819f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stonepedestal_1", 2000421, 0, 4064763, 4, { 117.353203f, -3.713329f, 23.859619f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "DoortotheVaultofSecrets", 2000422, 3692636, 4064764, 4, { 125.292603f, -1.268839f, 20.414270f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stonepedestal_2", 2000423, 0, 4064767, 4, { 61.900841f, -17.710569f, 22.327250f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "DoortotheVaultofWealth", 2000424, 3692634, 4064768, 4, { 70.569122f, -15.302040f, 21.475040f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stonepedestal_3", 2000425, 0, 4064769, 4, { 61.907928f, -17.695210f, -22.335239f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "DoortotheVaultofSteel", 2000426, 3692631, 4064770, 4, { 70.709091f, -15.224650f, -21.394239f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Leftpan", 2000427, 0, 4064771, 4, { 190.478394f, -4.200000f, -0.796000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "ThePathtoRetribution", 2000429, 3692668, 4064772, 4, { 206.461700f, 0.128704f, 0.089424f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2000430, 3693498, 4064773, 4, { 191.008408f, -0.694424f, -14.489020f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sealeddoor", 2000431, 3692650, 4064775, 4, { -9.500046f, -15.008410f, 0.079636f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sealeddoor_1", 2000432, 3689141, 4064777, 4, { 9.008017f, -16.388670f, -27.499990f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sealeddoor_2", 2000433, 3692625, 4064779, 4, { 8.971441f, -16.420650f, 27.488810f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sealedentryway", 2000434, 3692683, 4064780, 4, { 75.484787f, -8.687153f, 0.065771f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sealeddoor_3", 2000435, 3692667, 4064782, 4, { 132.458893f, -1.129695f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "InnerSanctumgate", 2000436, 3689097, 4064784, 4, { -62.922180f, -9.678907f, -43.500019f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "LowerSanctumgate", 2000437, 3692684, 4064785, 4, { 48.112701f, -45.229740f, 19.500000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 4208417, 4208419, 5, { -202.000000f, 0.000002f, 2.000000f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 4208421, 4, { -173.000000f, 12.000000f, 4.500000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Rightpan", 2000428, 0, 4208424, 4, { 190.478394f, -4.200000f, 0.831205f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2000443, 4208428, 4208429, 4, { -96.278473f, -11.750040f, -58.418720f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2000444, 0, 4208431, 4, { -95.744789f, -11.997100f, -61.865219f }, 1.000000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2000445, 4208432, 4208433, 4, { 65.669456f, -45.004108f, -34.907001f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_3", 2000446, 0, 4208434, 4, { 68.223022f, -44.998901f, -35.050049f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgpl_w_lvd_b0250_w1d3", 2000447, 4208435, 4208436, 4, { 208.815399f, -4.000029f, 3.424202f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_4", 2000448, 0, 4208437, 4, { 208.268402f, -4.000159f, 0.000000f }, 1.000000f, -1.570451f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 4208439, 4, { 255.000000f, -3.999998f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "TheScalesofJudgment", 2000658, 0, 4299010, 4, { 190.569901f, -2.364499f, 0.034341f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_5", 2001156, 4069463, 4332171, 4, { 190.000000f, -4.000078f, -0.800000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2001157, 4069468, 4332172, 4, { 190.000000f, -4.000021f, 0.800000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Leftpan_1", 2001165, 0, 4333439, 4, { 190.478394f, -4.170000f, -0.796000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Rightpan_1", 2001166, 0, 4333440, 4, { 190.478394f, -4.170000f, 0.831200f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "sgbg_w_lvd_w1d3_wall", 2001765, 4334159, 4334160, 4, { -10.000000f, -18.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_btl_b0197", 2000281, 4323974, 4296230, 4, { 228.750000f, -3.999998f, -9.250000f }, 1.000000f, 0.000000f, 0); 
    // States -> floor_on (id: 5) floor_of (id: 6) wall_on (id: 7) wall_of (id: 8) col_0f (id: 28) 
    instance.addEObj( "sgvf_w_btl_b0197_1", 2000281, 4323976, 4296314, 4, { 247.250000f, -3.999998f, -9.250000f }, 1.000000f, 0.000000f, 0); 
    // States -> floor_on (id: 5) floor_of (id: 6) wall_on (id: 7) wall_of (id: 8) col_0f (id: 28) 
    instance.addEObj( "sgvf_w_btl_b0197_2", 2000281, 4323978, 4296315, 4, { 228.750000f, -3.999998f, 9.250000f }, 1.000000f, 0.000000f, 0); 
    // States -> floor_on (id: 5) floor_of (id: 6) wall_on (id: 7) wall_of (id: 8) col_0f (id: 28) 
    instance.addEObj( "sgvf_w_btl_b0197_3", 2000281, 4323979, 4296317, 4, { 247.250000f, -3.999998f, 9.250000f }, 1.000000f, 0.000000f, 0); 
    // States -> floor_on (id: 5) floor_of (id: 6) wall_on (id: 7) wall_of (id: 8) col_0f (id: 28) 
    instance.addEObj( "unknown_7", 2000655, 3947232, 4298986, 4, { 225.699997f, -2.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2000656, 3947235, 4298996, 4, { 238.000000f, -2.000000f, 12.250000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2000657, 3947234, 4299001, 4, { 238.000000f, -2.000000f, -12.250000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2000866, 4309073, 4312529, 4, { -82.750000f, -11.000000f, -61.680000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2000867, 4309075, 4312543, 4, { -69.175003f, -11.000000f, -52.720001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2000868, 4309074, 4312544, 4, { -55.514999f, -11.000000f, -61.680000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2000650, 3879215, 4298966, 4, { -20.000000f, -16.500000f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2000651, 3879238, 4298968, 4, { 9.000000f, -17.000000f, -15.500000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2000652, 3879240, 4298970, 4, { 9.000000f, -17.000000f, 15.500000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2000653, 3879241, 4298971, 4, { 50.000000f, -17.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2000654, 3879249, 4298980, 4, { 124.500000f, -2.000000f, 0.000000f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSunkenTempleofQarn );