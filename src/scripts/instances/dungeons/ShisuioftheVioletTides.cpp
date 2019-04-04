#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ShisuioftheVioletTides :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ShisuioftheVioletTides() :
    Sapphire::ScriptAPI::InstanceContentScript( 50 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6526609, 5, { 8.208527f, 11.171570f, 362.661407f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 12.390300f, 9.221273f, 350.790100f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6709633, 4, { 0.322443f, 45.921879f, -411.857788f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -0.011370f, 45.921879f, -412.896698f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.069154f, 45.921871f, -447.611115f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2008110, 6865017, 4, { -0.060144f, 45.921879f, -430.535889f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6890670, 4, { 5.646293f, 45.921879f, -440.096588f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6709518, 4, { -0.364792f, 18.299490f, 91.107010f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 0.033326f, 18.500010f, 89.883667f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007771, 6709586, 4, { -0.180471f, 18.500010f, 50.377258f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2008311, 0, 4, { -7.074059f, 18.500019f, 72.067329f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2008312, 0, 4, { 5.212873f, 18.500019f, 72.435066f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6709598, 4, { 0.399389f, 26.954840f, -187.217804f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007772, 6709615, 4, { -17.157890f, 27.250010f, -208.294098f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { 0.044392f, 27.249910f, -188.679199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2008106, 6869249, 4, { -8.237946f, 27.250010f, -216.909500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2008107, 6869206, 4, { -7.564978f, 27.250010f, -199.660095f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2008108, 6869244, 4, { 8.748951f, 27.249981f, -199.725601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2008109, 6869228, 4, { 8.554644f, 27.250010f, -216.964706f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007745, 6496157, 4, { 6.118062f, 6.997511f, 335.203186f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_12", 2007746, 6502056, 4, { 29.832279f, -1.756603f, 291.307404f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007747, 6502057, 4, { 0.594021f, -3.646973f, 227.895996f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2007748, 6502133, 4, { 19.059891f, -3.462188f, 230.198303f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007749, 6502058, 4, { -3.533240f, -5.778060f, 244.420105f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2007750, 6502145, 4, { -55.424740f, 7.160790f, 138.440201f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2007751, 6502143, 4, { -40.800652f, 6.339986f, 152.161407f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2007752, 6502138, 4, { -42.255699f, 6.735332f, 144.687607f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2007762, 6502139, 4, { -58.166401f, 3.768957f, 197.653702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2007763, 6502141, 4, { -46.675800f, 6.647403f, 136.313400f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2007764, 0, 4, { -25.192690f, 6.973328f, 142.992203f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_22", 2007753, 6502709, 4, { -9.730975f, -4.657778f, 229.435501f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2007754, 6502794, 4, { -19.627199f, 7.090509f, 140.629501f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2007767, 6526733, 4, { -52.219410f, 6.701191f, 142.932297f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2007770, 6514679, 4, { 0.421847f, 21.000000f, 23.917980f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2007768, 6708902, 4, { -42.045250f, 6.286057f, 150.394806f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2007769, 6708901, 4, { -56.005989f, 6.588723f, 144.949600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2007755, 6504391, 4, { 0.527385f, 26.000010f, -18.338779f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2007756, 6504406, 4, { 0.118717f, 26.000010f, -49.912861f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2007757, 6504429, 4, { 0.465194f, 26.078131f, -80.333969f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2007758, 6504452, 4, { -0.073714f, 26.078131f, -165.829300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2007759, 6517284, 4, { 9.887736f, 30.921881f, -285.783295f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2007760, 6517285, 4, { 0.046282f, 40.921879f, -372.485901f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ShisuioftheVioletTides );