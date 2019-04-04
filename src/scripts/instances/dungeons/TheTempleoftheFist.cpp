#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheTempleoftheFist :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTempleoftheFist() :
    Sapphire::ScriptAPI::InstanceContentScript( 51 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 423.422485f, 65.445923f, 441.737213f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6797376, 4, { 423.331299f, 65.474983f, 444.327301f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6797378, 4, { 442.370697f, 65.474983f, 460.851013f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -249.873398f, 296.000000f, -77.899078f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6797503, 4, { -249.992004f, 296.000000f, -75.599426f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6797504, 4, { -250.001602f, 296.000000f, -116.498398f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2008209, 6769836, 4, { -249.829300f, 296.000000f, -95.249687f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -249.652893f, 275.999908f, -441.789886f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 6797511, 4, { -249.766495f, 275.999603f, -438.543091f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 380.357208f, 48.477909f, 199.450607f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 6797015, 5, { 384.232910f, 48.477909f, 190.203598f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -250.049606f, 275.999908f, -476.951202f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2007880, 6741864, 4, { 336.278503f, 53.817650f, 313.365601f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007881, 6653501, 4, { 424.189697f, 65.474983f, 415.504608f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007882, 6797118, 4, { 339.809296f, 54.757198f, 321.431305f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_7", 2007883, 6742023, 4, { 363.048401f, 59.017422f, 336.516998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007884, 6742029, 4, { 377.123596f, 62.271931f, 343.185791f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007885, 6797120, 4, { 384.602997f, 66.764778f, 371.233795f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007886, 6797121, 4, { 410.327301f, 66.278519f, 376.253693f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007887, 6797122, 4, { 424.830414f, 66.366417f, 401.730988f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007888, 6765334, 4, { -344.965302f, 288.858490f, 3.678721f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007889, 6779339, 4, { -250.141205f, 295.979187f, -44.449520f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_14", 2008288, 6852038, 4, { -371.378693f, 270.328491f, 112.430801f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_15", 2008288, 6852040, 4, { -371.275787f, 270.243988f, 109.578796f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2008288, 6852041, 4, { -370.932190f, 270.135010f, 106.583000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2008288, 6852045, 4, { -371.375702f, 270.360413f, 99.153847f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2008288, 6852043, 4, { -370.707001f, 270.230713f, 95.389702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2008288, 6852044, 4, { -370.509613f, 270.239685f, 92.297852f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2008288, 6773554, 4, { -365.927399f, 288.163910f, 5.884438f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_21", 2008288, 6852047, 4, { -362.804993f, 288.071808f, 5.945870f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2008288, 6852048, 4, { -359.589600f, 287.859314f, 5.824460f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2008288, 6852051, 4, { -352.795807f, 287.719910f, 5.701195f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2008288, 6852050, 4, { -349.930786f, 287.818604f, 5.373718f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2008288, 6852052, 4, { -346.784210f, 287.961914f, 5.057184f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2007890, 6796543, 4, { -226.703293f, 299.977112f, -260.456207f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_27", 2007891, 6796598, 4, { -250.507401f, 292.000000f, -384.725800f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_28", 2007892, 6771621, 4, { -250.875107f, 292.000000f, -436.964691f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheTempleoftheFist );