#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CopperbellMinesHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CopperbellMinesHard() : Sapphire::ScriptAPI::InstanceContentScript( 18 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2002930, 0, 4507082, 4, { -90.674911f, -57.698959f, 55.099388f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002929, 4481287, 4507085, 4, { -93.494362f, -57.942631f, 52.914669f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Crystallizedrock", 2002947, 0, 4508135, 4, { -104.992798f, -53.764061f, -21.253201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Crystallizedrock_1", 2003150, 0, 4534567, 4, { -131.401993f, -56.204762f, 0.851171f }, 0.991760f, -0.745382f, 0); 
    instance.addEObj( "Crystallizedrock_2", 2003151, 0, 4534568, 4, { -62.481171f, -59.339249f, 24.728519f }, 0.991760f, 1.004150f, 0); 
    instance.addEObj( "Crystallizedrock_3", 2003152, 0, 4534569, 4, { -86.379723f, -58.526180f, 47.109539f }, 0.991760f, 0.098224f, 0); 
    instance.addEObj( "Crystallizedrock_4", 2003153, 0, 4534570, 4, { -114.249298f, -57.590469f, 38.164780f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Crystallizedrock_5", 2003154, 0, 4534571, 4, { -78.472977f, -56.144230f, -6.125785f }, 0.991760f, 0.703581f, 0); 
    instance.addEObj( "unknown_1", 2002735, 0, 4497366, 4, { 66.489433f, -9.196375f, -91.109978f }, 1.000000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4481282, 4497374, 4, { 69.178787f, -9.885409f, -91.345154f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 4497376, 4497378, 4, { 64.314568f, -9.885409f, -48.220890f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2002866, 4498423, 4497388, 4, { 73.371529f, -11.611810f, -91.558388f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2002867, 4498424, 4497389, 4, { 79.777977f, -11.999900f, -79.149048f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2002868, 4498425, 4497390, 4, { 91.175873f, -12.124900f, -66.404877f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2002869, 4498426, 4497391, 4, { 77.390869f, -12.124900f, -55.604710f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2002735, 0, 4498636, 4, { 35.741501f, -38.003502f, 86.637199f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 4481286, 4498637, 4, { 34.816029f, -37.807098f, 89.653633f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Improvedblastingdevice", 2002870, 4500271, 4498667, 4, { 39.532532f, -37.026131f, 113.598297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_4", 2002948, 4508121, 4508126, 4, { 6.729187f, -37.796692f, 112.748901f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Liftlever", 2002902, 0, 4504890, 4, { -184.034393f, 23.988701f, -205.737198f }, 1.000000f, -1.554668f, 0); 
    instance.addEObj( "Liftlever_1", 2002904, 0, 4504891, 4, { -183.968002f, -6.010950f, -205.991592f }, 1.000000f, 1.545402f, 0); 
    instance.addEObj( "unknown_7", 2002905, 4478636, 4504894, 4, { -192.156906f, 22.842710f, -208.392502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2002900, 4498399, 4504908, 4, { -209.037796f, 23.594311f, -208.732300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Liftlever_2", 2002901, 4478628, 4504917, 4, { -191.601700f, 23.360180f, -205.152100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Liftlever_3", 2002903, 4478629, 4504918, 4, { -176.329803f, -6.592807f, -210.900894f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2002906, 4478634, 4504920, 4, { -177.598907f, -6.741823f, -208.024597f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2002907, 4478650, 4505305, 4, { -183.958496f, 8.816254f, -208.023193f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2002908, 4498400, 4505342, 4, { -50.309021f, -3.189148f, -200.885101f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2002909, 4498416, 4505343, 4, { 21.741100f, -9.932099f, -141.413300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2002910, 4498406, 4505344, 4, { -12.649780f, -6.958161f, -219.043304f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_14", 2002911, 4498409, 4505345, 4, { 18.035469f, -6.958161f, -209.711594f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2002912, 4498410, 4505346, 4, { 17.977119f, -7.000057f, -185.896194f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2002923, 4498451, 4506598, 4, { 60.402431f, -38.719849f, 51.888512f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2002924, 4498457, 4506603, 4, { 65.252907f, -38.455730f, 39.846581f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2002925, 4498456, 4506604, 4, { 55.235111f, -38.564739f, 39.248360f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2002926, 4500996, 4506651, 4, { -82.288239f, -39.313419f, 101.057198f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 4481330, 4481331, 5, { -253.156403f, 23.528379f, -174.613998f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Exit", 2000139, 0, 4481310, 4, { -100.877403f, -56.042820f, -15.206130f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Shortcut", 2000700, 0, 4481333, 4, { -237.184906f, 21.988159f, -166.420502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2002899, 0, 4510398, 4, { -267.241791f, 23.005880f, -170.712494f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CopperbellMinesHard );