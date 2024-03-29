#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheLostCityofAmdapor : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheLostCityofAmdapor() : Sapphire::ScriptAPI::InstanceContentScript( 22 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4579298, 4579300, 4, { 9.791200f, -279.967285f, 21.616301f }, 0.700000f, -0.494801f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2002735, 0, 4579301, 4, { 8.967742f, -279.844086f, 22.640949f }, 1.000000f, -0.407391f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 4579302, 4, { -6.668615f, -279.989990f, -16.121090f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Diabolicalgate", 2003262, 0, 4617274, 4, { -11.735310f, -279.600006f, 1.146639f }, 1.000000f, -0.357945f, 0); 
    instance.addEObj( "Diabolicalgate_1", 2003263, 0, 4617275, 4, { -5.801897f, -279.600006f, -2.180922f }, 1.000000f, -0.579334f, 0); 
    instance.addEObj( "Diabolicalgate_2", 2003264, 0, 4617276, 4, { -9.593593f, -279.600006f, 5.704061f }, 1.000000f, -0.499409f, 0); 
    instance.addEObj( "Diabolicalgate_3", 2003265, 0, 4617277, 4, { -3.149769f, -279.600006f, 2.478353f }, 1.000000f, -0.520267f, 0); 
    instance.addEObj( "Dubiouscoffer", 2003266, 0, 4617288, 4, { 8.612234f, -279.989990f, -20.760429f }, 1.000000f, 0.406471f, 0); 
    instance.addEObj( "Dubiouscoffer_1", 2003267, 0, 4617290, 4, { 20.769291f, -279.989990f, -8.610124f }, 1.000000f, 1.180338f, 0); 
    instance.addEObj( "Dubiouscoffer_2", 2003268, 0, 4617294, 4, { -20.776131f, -279.989990f, 8.642863f }, 0.991760f, -1.160291f, 0); 
    instance.addEObj( "Dubiouscoffer_3", 2003269, 0, 4617295, 4, { -20.738871f, -279.989990f, -8.552890f }, 1.000000f, -1.185745f, 0); 
    instance.addEObj( "Dubiouscoffer_4", 2003270, 0, 4617296, 4, { 20.683531f, -279.989990f, 8.612939f }, 1.000000f, 1.247274f, 0); 
    instance.addEObj( "Dubiouscoffer_5", 2003271, 0, 4617297, 4, { -8.611513f, -279.989990f, 20.715059f }, 1.000000f, -0.423025f, 0); 
    instance.addEObj( "unknown_1", 2003361, 4538596, 4574938, 4, { 146.386597f, 68.131821f, -32.655411f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2003431, 4577623, 4577468, 4, { 141.929794f, 66.690971f, -22.680590f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2003362, 4577620, 4577470, 4, { 124.650101f, 58.000000f, 21.475590f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Treasurecoffer", 2003800, 0, 4630853, 4, { 125.169800f, 58.259232f, 24.765381f }, 0.991760f, -1.568190f, 0); 
    instance.addEObj( "unknown_4", 2003364, 4538597, 4577670, 4, { 1.248910f, 34.305920f, -96.145103f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2003432, 4577625, 4577671, 4, { 7.652231f, 33.999989f, -83.909409f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_f1d5_a3_kin03", 2003365, 4572307, 4577672, 4, { 16.420071f, 30.172510f, -53.162449f }, 1.000000f, 0.000000f, 0); 
    // States -> plant_def (id: 2) plant_action_anim (id: 3) 
    instance.addEObj( "sgvf_f1d5_b0360", 2003366, 4629067, 4577673, 4, { 13.762910f, 27.170670f, -29.499069f }, 1.000000f, 0.000000f, 0); 
    // States -> liq_def (id: 2) liq_on (id: 3) liq_on_anim (id: 4) liq_off_anim (id: 6) 
    instance.addEObj( "unknown_6", 2003367, 4577622, 4577674, 4, { -35.077301f, 20.181410f, -5.543382f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_f1d5_a3_kin03_1", 2003368, 4572310, 4577687, 4, { -36.282841f, 10.771230f, 27.777269f }, 1.000000f, 0.000000f, 0); 
    // States -> plant_def (id: 2) plant_action_anim (id: 3) 
    instance.addEObj( "sgvf_f1d5_b0359", 2003369, 4629073, 4577688, 4, { -38.452469f, 10.771230f, 26.955620f }, 1.000000f, 0.000000f, 0); 
    // States -> liq_def (id: 2) liq_on (id: 3) liq_on_anim (id: 4) liq_off_anim (id: 6) 
    instance.addEObj( "unknown_7", 2003370, 4538791, 4577692, 4, { 11.000470f, 7.980469f, 18.231581f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgbg_f1d5_a3_kin03_2", 2003371, 4572309, 4577693, 4, { 15.090590f, 6.133745f, 32.735611f }, 1.000000f, 0.000000f, 0); 
    // States -> plant_def (id: 2) plant_action_anim (id: 3) 
    instance.addEObj( "sgvf_f1d5_b0358", 2003372, 4629074, 4577694, 4, { 11.812460f, 6.045094f, 32.012810f }, 1.000000f, 0.000000f, 0); 
    // States -> liq_def (id: 2) liq_on (id: 3) liq_on_anim (id: 4) liq_off_anim (id: 6) 
    instance.addEObj( "unknown_8", 2003433, 4577626, 4577698, 4, { 25.308140f, 6.141701f, 43.055359f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Treasurecoffer_1", 2003801, 0, 4630877, 4, { -39.169922f, 18.680960f, -1.968445f }, 0.991760f, -0.789868f, 0); 
    instance.addEObj( "unknown_9", 2003374, 4583478, 4579227, 4, { 23.827320f, -252.500000f, -65.956993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2003375, 4583476, 4579228, 4, { 9.536644f, -252.394394f, -55.117130f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2003376, 4583473, 4579231, 4, { 47.898071f, -270.801910f, 54.428829f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2003377, 4583472, 4579234, 4, { 35.751831f, -270.679901f, 43.045650f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_13", 2003378, 4583471, 4579235, 4, { 42.832031f, -270.801910f, 35.995972f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_14", 2003379, 4583474, 4579236, 4, { 54.564331f, -270.899994f, 47.591949f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4577505, 4577500, 4, { 100.376602f, 43.960560f, 2.708986f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_15", 2002735, 0, 4577510, 4, { 97.980797f, 42.137150f, -0.222000f }, 0.900000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2003363, 4578411, 4577515, 4, { 86.630951f, 42.801220f, -47.240730f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2003373, 4578103, 4577696, 4, { -38.428570f, 12.100000f, 70.544273f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 4578066, 4578098, 4, { 6.156913f, 11.249960f, 70.316727f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_17", 2002735, 0, 4578101, 4, { 4.235116f, 12.085570f, 69.965263f }, 1.000000f, -1.570451f, 0); 
    instance.addEObj( "unknown_18", 2003360, 0, 4574829, 4, { 284.752808f, 100.000000f, -31.765209f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 4574610, 4574831, 5, { 270.581207f, 100.000000f, -17.202379f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Shortcut", 2000700, 0, 4574832, 4, { 265.173615f, 100.000000f, -32.604542f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheLostCityofAmdapor );