#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class BrayfloxsLongstopHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BrayfloxsLongstopHard() : Sapphire::ScriptAPI::InstanceContentScript( 20 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2003103, 0, 4621687, 4, { -16.800230f, 25.375731f, -171.007904f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "RunstopHeadgate", 2002182, 4542379, 4543713, 4, { 105.912804f, 1.724182f, 11.428960f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118", 2002183, 4621964, 4543714, 4, { 111.650299f, 0.228821f, -49.790279f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Shortcut", 2000700, 0, 4543758, 4, { -75.025421f, -1.210333f, 73.659332f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2000182, 4543753, 4543754, 5, { -77.622681f, 0.605630f, 95.628304f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_1", 2002326, 0, 4599119, 4, { -3.491464f, -0.354560f, -24.718349f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Tinykey", 2002325, 0, 4615188, 4, { -62.769581f, -0.332854f, 36.199650f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_w_lvd_b0118_wide", 2002872, 4543726, 4543727, 4, { 111.888000f, -2.109839f, -6.942894f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2002735, 0, 4543728, 4, { 114.658699f, -2.093417f, -6.149437f }, 1.100000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2002109, 4549243, 4598145, 4, { 92.977211f, 5.002774f, -110.975502f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2002150, 4549448, 4598146, 4, { 30.497520f, 8.248112f, -82.096916f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2002180, 4549459, 4598147, 4, { 27.134510f, 7.114878f, -120.719704f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2002181, 4574849, 4598148, 4, { 45.695850f, 7.015042f, -129.344604f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenwares", 2002262, 4598415, 4598414, 4, { -28.610241f, 25.192631f, -174.631195f }, 0.991760f, -0.000527f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_7", 2002735, 0, 4543731, 4, { 44.686901f, 7.015000f, -131.547394f }, 0.500000f, -0.532325f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 4543729, 4543730, 4, { 44.232769f, 7.015042f, -129.352997f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_8", 2003429, 0, 4663860, 4, { 44.358749f, 7.554582f, -132.341095f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 4543759, 4, { -25.894650f, 35.019409f, -222.949600f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "SwiftmakeCheckgate", 2002184, 4549240, 4598149, 4, { -95.264717f, 12.888430f, -122.593300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "SwiftmakeCheckgate_1", 2002665, 4549241, 4598150, 4, { -100.273201f, 20.310730f, -163.513397f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "SwiftmakeCheckgate_2", 2002884, 4572942, 4598151, 4, { -102.647499f, 21.011600f, -187.365494f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250", 2002872, 4543735, 4543736, 4, { -48.175251f, 34.706921f, -234.463196f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_9", 2002735, 0, 4543737, 4, { -48.271229f, 34.918541f, -235.574203f }, 1.000000f, -1.497719f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BrayfloxsLongstopHard );