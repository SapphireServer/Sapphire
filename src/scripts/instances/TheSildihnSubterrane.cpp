#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheSildihnSubterrane : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSildihnSubterrane() : Sapphire::ScriptAPI::InstanceContentScript( 36001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -213.000000f, -32.000000f, 126.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9326736, 4, { -213.000000f, -32.000000f, 126.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9326737, 4, { -213.000000f, -32.000000f, 76.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 183.000000f, -21.000000f, 197.750000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 9326742, 4, { 183.000000f, -21.000000f, 200.729797f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 9326743, 4, { 183.000000f, -21.000000f, 153.731903f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 0.000000f, -0.004100f, 20.750000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 9326749, 4, { 0.000000f, -0.004023f, 22.924641f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2002872, 9326750, 4, { 0.000000f, 0.306310f, -23.030140f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -335.000000f, -29.000071f, -125.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2002872, 9322670, 4, { -335.000000f, -29.000071f, -124.500000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_7", 2002872, 9322671, 4, { -335.000000f, -29.045799f, -185.699997f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_8", 2002872, 9318492, 4, { 289.000000f, 32.750031f, -74.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 288.983307f, 32.750031f, -75.500000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_9", 2002872, 9326730, 4, { -35.000000f, 21.000000f, -251.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { -35.019470f, 20.981079f, -249.949997f }, 1.388489f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2002872, 0, 4, { 288.994110f, 27.999870f, -182.491501f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2002735, 0, 4, { 288.994110f, 27.991760f, -182.491501f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Culvertswitch", 2013036, 9321655, 4, { -189.105103f, -14.999630f, 178.087997f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Stoneplinth", 2013085, 0, 4, { -289.661987f, -28.000000f, -37.186279f }, 0.991760f, -0.010000f); 
    instance.registerEObj( "Stoneplinth_1", 2013086, 0, 4, { -300.465393f, -28.000000f, -37.155701f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Barreddoor", 2013087, 9309838, 4, { -417.013885f, -16.525570f, -104.966797f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Oresack", 2013123, 0, 4, { -287.604492f, -27.745890f, -50.460171f }, 1.000000f, -1.745329f); 
    instance.registerEObj( "Oresack_1", 2013124, 0, 4, { -283.019104f, -28.609631f, -24.302820f }, 0.991760f, -0.349066f); 
    instance.registerEObj( "Oresack_2", 2013125, 0, 4, { -305.313904f, -28.999981f, -28.384150f }, 1.000000f, -0.872665f); 
    instance.registerEObj( "Oresack_3", 2013126, 0, 4, { -300.301788f, -27.744690f, -51.948040f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Oresack_4", 2013127, 0, 4, { -287.915314f, -28.999981f, -46.243950f }, 1.000000f, 0.785398f); 
    instance.registerEObj( "Oresack_5", 2013128, 0, 4, { -299.653412f, -26.828320f, -43.211761f }, 1.000000f, 0.127440f); 
    instance.registerEObj( "Oresack_6", 2013129, 0, 4, { -288.229492f, -28.999981f, -25.480480f }, 0.991760f, 1.048342f); 
    instance.registerEObj( "Oresack_7", 2013130, 0, 4, { -294.004913f, -28.999981f, -34.243118f }, 1.000000f, -3.141593f); 
    instance.registerEObj( "Rustywinch", 2013133, 0, 4, { 201.464798f, 0.198364f, 90.318123f }, 0.991760f, 0.626113f); 
    instance.registerEObj( "Forebodingdoor", 2013134, 0, 4, { 286.614594f, 20.859100f, -20.161699f }, 0.991760f, 0.785398f); 
    instance.registerEObj( "Myrrhincenseburner", 2013135, 9321786, 4, { 317.708099f, 18.356569f, -18.295650f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Cisternswitch", 2013138, 9396005, 4, { 75.076027f, 4.998652f, 118.241203f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Bulkheadhandle", 2013139, 0, 4, { 12.065390f, -1.001856f, 70.005051f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "TheScalesofJudgment", 2013140, 0, 4, { -38.651119f, 19.211060f, -187.609695f }, 0.991760f, -1.570451f); 
    instance.registerEObj( "Leftpan", 2013141, 0, 4, { -38.654221f, 18.518789f, -186.750397f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rightpan", 2013142, 0, 4, { -38.654221f, 18.518789f, -188.392593f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Conspicuouslevers", 2013143, 0, 4, { -37.285351f, 17.508631f, -213.557907f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Antiqueteleporter", 2013144, 0, 4, { -48.832249f, 18.500000f, -187.455307f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "StatueofNald", 2013145, 0, 4, { -89.952698f, 16.856440f, -232.715393f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "StatueofThal", 2013146, 0, 4, { -89.952698f, 16.700029f, -219.251801f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Leftpan_1", 2013152, 0, 4, { -38.654202f, 18.518801f, -186.750397f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Rightpan_1", 2013153, 0, 4, { -38.654221f, 18.518789f, -188.392593f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Scrawlednote", 2013166, 0, 4, { -100.114502f, 16.678040f, -245.533005f }, 0.991760f, 0.595517f); 
    instance.registerEObj( "Entrance", 2000182, 9316802, 5, { 5.000000f, -3.995500f, 246.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -329.034698f, -28.198090f, -239.940796f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit_1", 2000139, 0, 4, { 289.000000f, 33.000000f, -120.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit_2", 2000139, 0, 4, { -35.000000f, 21.000000f, -286.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Exit_3", 2000139, 0, 4, { 293.005310f, 31.000010f, -331.194214f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 0.500734f, -4.001427f, 232.607101f }, 0.991760f, 0.000048f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheSildihnSubterrane );